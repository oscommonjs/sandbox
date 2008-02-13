//
// AbstractFilter.h
//
// $Id: //poco/Main/Logging/include/Poco/Logging/AbstractFilter.h#2 $
//
// Library: Logging
// Package: Filters
// Module:  AbstractFilter
//
// Definition of the AbstractFilter class.
//
// Copyright (c) 2005-2008, Applied Informatics Software Engineering GmbH.
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


#ifndef Logging_AbstractFilter_INCLUDED
#define Logging_AbstractFilter_INCLUDED


#include "Poco/Logging/Logging.h"
#include "Poco/Channel.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace Logging {


class Logging_API AbstractFilter: public Channel
	/// This is a base class for all filter channels.
	///
	/// Two channels can be attached to an AbstractFilter.
	/// The first channel, known as the pass channel, receives
	/// all messages passing the filter.
	/// The other channel, known as the fail channel, receives
	/// all messages failing to pass the filter.
{
public:
	AbstractFilter();
		/// Creates the AbstractFilter.

	AbstractFilter(Poco::Channel* pPassChannel);
		/// Creates the AbstractFilter and sets the pass channel.

	AbstractFilter(Poco::Channel* pPassChannel, Poco::Channel* pFailChannel);
		/// Creates the AbstractFilter and sets the pass and fail channels.

	~AbstractFilter();
		/// Destroys the AbstractFilter.

	void setPassChannel(Poco::Channel* pChannel);
		/// Sets the channel to which the messages passing 
		/// the filter are passed on.
		
	Poco::Channel* getPassChannel() const;
		/// Returns the channel to which the messages passing 
		/// the filter are passed on.

	void setFailChannel(Poco::Channel* pChannel);
		/// Sets the channel to which the messages failing to pass 
		/// the filter are passed on.
		
	Poco::Channel* getFailChannel() const;
		/// Returns the channel to which the messages failing to pass 
		/// the filter are passed on.

	void log(const Poco::Message& msg);
		/// Passes the message on to the pass channel,
		/// if one has been set.

	void logFail(const Poco::Message& msg);
		/// Passes the message on to the fail channel,
		/// if one has been set.

	void setProperty(const std::string& name, const std::string& value);
		/// Only the "passChannel" and "failChannel" properties are supported, which allow
		/// setting the pass and fail channels, via the LoggingRegistry.
		/// The "passChannel" and "failChannel" properties are set-only.

private:
	Poco::AutoPtr<Poco::Channel> _pPassNext;
	Poco::AutoPtr<Poco::Channel> _pFailNext;
};


} } // namespace Poco::Logging


#endif // Logging_AbstractFilter_INCLUDED
