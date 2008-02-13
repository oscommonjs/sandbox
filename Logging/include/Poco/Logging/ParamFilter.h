//
// ParamFilter.h
//
// $Id: //poco/Main/Logging/include/Poco/Logging/ParamFilter.h#2 $
//
// Library: Logging
// Package: Filters
// Module:  ParamFilter
//
// Definition of the ParamFilter class.
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


#ifndef Logging_ParamFilter_INCLUDED
#define Logging_ParamFilter_INCLUDED


#include "Poco/Logging/Logging.h"
#include "Poco/Logging/RegExpFilter.h"


namespace Poco {
namespace Logging {


class Logging_API ParamFilter: public RegExpFilter
	/// A filter that matches a message's parameter agains a regular expression.
{
public:
	ParamFilter();
		/// Creates the SourceFilter.

	ParamFilter(const std::string& param, const std::string& expr);
		/// Creates the SourceFilter with the given regular expression.

	ParamFilter(const std::string& param, const std::string& expr, int options);
		/// Creates the SourceFilter with the given regular expression and
		/// options. 
		/// See the Poco::RegularExpression class for a list of
		/// valid options.

	~ParamFilter();
		/// Destroys the SourceFilter.

	void log(const Poco::Message& msg);
		/// Passes the message on to the next channel,
		/// its source matches the regular expression.

	void setProperty(const std::string& name, const std::string& value);
		/// Only the "param" property is supported.

	std::string getProperty(const std::string& name);
		/// Only the "param" property is supported.

	static void registerChannel();
		/// Registers the channel with the global LoggingFactory.

private:
	std::string _param;
};


} } // namespace Poco::Logging


#endif // Logging_ParamFilter_INCLUDED
