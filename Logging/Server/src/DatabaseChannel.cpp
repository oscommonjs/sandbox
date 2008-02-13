//
// DatabaseChannel.cpp
//
// $Id: //poco/Main/Logging/Server/src/DatabaseChannel.cpp#2 $
//
// Copyright (c) 2006-2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "DatabaseChannel.h"
#include "Poco/Exception.h"
#include "Poco/Message.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/LoggingFactory.h"
#include "Poco/Data/Common.h"
#include "Poco/Data/SessionFactory.h"


using namespace Poco::Data;


const std::string DatabaseChannel::PROP_DB("database");
const std::string DatabaseChannel::PROP_CONNSTRING("connectionString");
const std::string DatabaseChannel::SQL_CREATE_TABLE("CREATE TABLE LogMessages (source VARCHAR(30), text VARCHAR(100), prio INTEGER, time VARCHAR(30), threadID INTEGER, threadName VARCHAR(30), pid INTEGER, addinfo VARCHAR(60))");
const std::string DatabaseChannel::SQL_INSERT_MESSAGE("INSERT INTO LogMessages VALUES(:src, :txt, :prio, :time, :tid, :name, :pid, :addnfo)");


DatabaseChannel::DatabaseChannel():
	_databaseType(),
	_connectionString(),
	_ptrSession()
{
}


DatabaseChannel::DatabaseChannel(const std::string& dbType, const std::string& connString):
	_databaseType(dbType),
	_connectionString(connString),
	_ptrSession()
{
}


DatabaseChannel::~DatabaseChannel()
{
}


void DatabaseChannel::log(const Poco::Message& msg)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!_ptrSession)
		open();
	//"INSERT INTO LogMessages VALUES(:src, :txt, :prio, :time, :tid, :name, :pid, :addnfo)");
	int prio = static_cast<int>(msg.getPriority());
	std::string dateTime = Poco::DateTimeFormatter::format(msg.getTime(), Poco::DateTimeFormat::SORTABLE_FORMAT);
	std::string empty;
	*_ptrSession << SQL_INSERT_MESSAGE, use(msg.getSource()), use(msg.getText()), use(prio), use(dateTime), use(msg.getTid()), use(msg.getThread()), use(msg.getPid()), use(empty), now;
}


void DatabaseChannel::setProperty(const std::string& name, const std::string& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (name == PROP_DB)
		_databaseType = value;
	else if (name == PROP_CONNSTRING)
		_connectionString = value;
	else
		Poco::Channel::setProperty(name, value);
}


std::string DatabaseChannel::getProperty(const std::string& name) const
{
	Poco::Mutex::ScopedLock lock(_mutex);
	if (name == PROP_DB)
		return _databaseType;
	else if (name == PROP_CONNSTRING)
		return _connectionString;
	else
		return Poco::Channel::getProperty(name);
}


void DatabaseChannel::open()
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_ptrSession = new Poco::Data::Session(Poco::Data::SessionFactory::instance().create(_databaseType, _connectionString));
	// Create the table if necessary!
	//Message: source, text, prio, time, threadid, threadname, processid, addinfo
	try 
	{
		*_ptrSession << SQL_CREATE_TABLE, now; 
	}
	catch(Poco::Exception&)
	{
		// Table exists
	}
}


void DatabaseChannel::close()
{
	Poco::Mutex::ScopedLock lock(_mutex);
	_ptrSession = 0;
}


void DatabaseChannel::registerChannel()
{
	Poco::LoggingFactory::defaultFactory().registerChannelClass("DatabaseChannel", new Poco::Instantiator<DatabaseChannel, Poco::Channel>);
}

