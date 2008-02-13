//
// PriorityFilter.h
//
// $Id: //poco/Main/Logging/include/Poco/Logging/PriorityFilter.h#3 $
//
// Library: Logging
// Package: Filters
// Module:  PriorityFilter
//
// Definition of the PriorityFilter class.
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


#ifndef Logging_PriorityFilter_INCLUDED
#define Logging_PriorityFilter_INCLUDED


#include "Poco/Logging/Logging.h"
#include "Poco/Logging/AbstractFilter.h"
#include "Poco/Message.h"


namespace Poco {
namespace Logging {


class Logging_API PriorityFilter: public AbstractFilter
	/// A Filter that filters messages based on their
	/// priority. A minimum and a maximum priority
	/// can be specified.
	///
	/// Only messages with a priority of at least the
	/// specified minimum and at most the specified maximum
	/// priority will pass.
{
public:
	PriorityFilter();
		/// Creates the PriorityFilter.

	PriorityFilter(Poco::Message::Priority minPrio, Poco::Message::Priority maxPrio = Poco::Message::PRIO_FATAL);
		/// Creates the PriorityFilter.

	~PriorityFilter();
		/// Destroys the PriorityFilter.

	void log(const Poco::Message& msg);
		/// Passes the message on to the next channel,
		/// if is lies within the given priority range.

	void setProperty(const std::string& name, const std::string& value);
		/// Supports the properties "min" and "max" for setting
		/// the minimum and maximum	priority.
		///
		/// See mapPriority() for a list of valid priority values.
		///
		/// The "min" and "max" properties are set-only.

	static void registerChannel();
		/// Registers the channel with the global LoggingFactory.

protected:
	Poco::Message::Priority mapPriority(const std::string& prio);
		/// Maps a priority, given as a string, to its corresponding enum value.
		///
		/// Valid values are:
		///   - fatal
		///   - critical
		///   - error
		///   - warning
		///   - notice
		///   - information
		///   - debug
		///   - trace

private:
	Poco::Message::Priority _minPrio;
	Poco::Message::Priority _maxPrio;
};


} } // namespace Poco::Logging


#endif // Logging_PriorityFilter_INCLUDED
