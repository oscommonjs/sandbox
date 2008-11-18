//
// ConsoleChannel.h
//
// $Id: //poco/svn/Foundation/include/Poco/ConsoleChannel.h#2 $
//
// Library: Foundation
// Package: Logging
// Module:  ConsoleChannel
//
// Definition of the ConsoleChannel class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Foundation_ConsoleChannel_INCLUDED
#define Foundation_ConsoleChannel_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Channel.h"
#include "Poco/Mutex.h"
#include <ostream>


namespace Poco {


class Foundation_API ConsoleChannel: public Channel
	/// A channel that writes to an ostream.
	///
	/// Only the message's text is written, followed
	/// by a newline.
	///
	/// Chain this channel to a FormattingChannel with an
	/// appropriate Formatter to control what is contained 
	/// in the text.
	///
	/// Similar to StreamChannel, except that a static
	/// mutex is used to protect against multiple
	/// console channels concurrently writing to the
	/// same stream.
{
public:
	ConsoleChannel();
		/// Creates the channel and attached std::clog.
		
	ConsoleChannel(std::ostream& str);
		/// Creates the channel.

	void log(const Message& msg);
		/// Logs the given message to the channel's stream.
		
protected:
	~ConsoleChannel();

private:
	std::ostream& _str;
	static FastMutex _mutex;
};


} // namespace Poco


#endif // Foundation_ConsoleChannel_INCLUDED