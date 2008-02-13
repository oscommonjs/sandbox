//
// CachingChannel.cpp
//
// $Id: //poco/Main/Logging/Server/src/CachingChannel.cpp#2 $
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


#include "CachingChannel.h"
#include "Poco/Exception.h"
#include "Poco/LoggingFactory.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"


const std::string CachingChannel::PROP_SIZE("size");


CachingChannel::CachingChannel():
	_cache(),
	_size(0),
	_maxSize(100),
	_mutex()
{
}


CachingChannel::CachingChannel(std::size_t n):
	_cache(),
	_size(0),
	_maxSize(n),
	_mutex()
{
}


CachingChannel::~CachingChannel()
{
}


void CachingChannel::log(const Poco::Message& msg)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	_cache.push_front(msg);
	if (_size == _maxSize)
	{
		_cache.pop_back();
	}
	else
		++_size;
}


void CachingChannel::getMessages(std::vector<Poco::Message>& msg, int offset, int numEntries) const
{
	msg.clear();
	Messages::const_iterator it = _cache.begin();

	while (offset > 0 && it != _cache.end())
	{
		++it;
		--offset;
	}

	while (numEntries > 0 && it != _cache.end())
	{
		msg.push_back(*it);
		++it;
		--numEntries;
	}
}


void CachingChannel::setProperty(const std::string& name, const std::string& value)
{
	if (name == PROP_SIZE)
	{
		int val(0);
		bool ok = Poco::NumberParser::tryParse(value, val);
		if (ok && val > 0)
			_maxSize = val;
	}
	else
		Poco::Channel::setProperty(name, value);
}


std::string CachingChannel::getProperty(const std::string& name) const
{
	if (name == PROP_SIZE)
	{
		return Poco::NumberFormatter::format(static_cast<Poco::UInt32>(_maxSize));
	}
	
	return Poco::Channel::getProperty(name);
}


void CachingChannel::registerChannel()
{
	Poco::LoggingFactory::defaultFactory().registerChannelClass("CachingChannel", new Poco::Instantiator<CachingChannel, Poco::Channel>);
}
