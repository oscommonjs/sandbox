//
// NoBodyResponse.h
//
//
// Library: Servlet
// Package: Http
// Module:  NoBodyResponse
//
// Definition of the NoBodyResponse class.
//
// Copyright (c) 2006, Aleksandar Fabijanic and Contributors.
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
//
// The code in this file is derived from Apache Tomcat project
// Copyright (c) 2004 The Apache Software Foundation.
// http://www.apache.org/licenses/LICENSE-2.0
// 


#ifndef Servlet_Http_NoBodyResponse_INCLUDED
#define Servlet_Http_NoBodyResponse_INCLUDED


#include "Poco/Servlet/ServletBase.h"
#include "Poco/Servlet/HttpServletResponse.h"
#include "Poco/NullStream.h"


namespace Poco {
namespace Servlet {


class Servlet_API NoBodyResponse : public HttpServletResponse 
	/// A response that includes no body, for use in (dumb) "HEAD" support.
	/// This response just swallows the body, counting the bytes in order to set
	/// the content length appropriately.  All other methods delegate directly
	/// to the HTTP Servlet Response object used to construct this one.
{
public:
	NoBodyResponse(HttpServletResponse& r);

	~NoBodyResponse();

	/// ServletResponse interface methods

	void setContentLength(int len);

	void setCharacterEncoding(const std::string& charset);

	void setContentType(const std::string& type);

	std::string getContentType();

	ServletOutputStream& getOutputStream();

	const std::string getCharacterEncoding() const;

	PrintWriter& getWriter();

	void setBufferSize(int size);

	int getBufferSize();

	void reset();

	void resetBuffer();

	bool isCommitted();

	void flushBuffer();

	void setLocale(const std::locale& loc);

	std::locale getLocale();

	/// HttpServletResponse interface methods

	void addCookie(const Cookie& cookie);

	bool containsHeader(const std::string& name);

	void setStatus(int sc, const std::string& sm);// deprecated

	void setStatus(int sc);

	void setHeader(const std::string& name, const std::string& value);

	void setIntHeader(const std::string& name, int value);

	void setDateHeader(const std::string& name, long date);

	void sendError(int sc, const std::string& msg);

	void sendError(int sc);

	void sendRedirect(const std::string& location);

	std::string encodeURL(const std::string& url);

	std::string encodeRedirectURL(const std::string& url);

	void addHeader(const std::string& name, const std::string& value);

	void addDateHeader(const std::string& name, long value);

	void addIntHeader(const std::string& name, int value);

private:
	HttpServletResponse&   _resp;
	ServletOutputStream*   _pNoBody;
	Poco::NullOutputStream _nullOutputStream;
};


///
/// inlines
///


/// ServletResponse interface methods

inline void NoBodyResponse::setContentLength(int len) 
{
	_resp.setContentLength(len);
}


inline void NoBodyResponse::setCharacterEncoding(const std::string& charset)
{ 
	_resp.setCharacterEncoding(charset); 
}


inline void NoBodyResponse::setContentType(const std::string& type)
{ 
	_resp.setContentType(type); 
}


inline std::string NoBodyResponse::getContentType()
{ 
	return _resp.getContentType(); 
}


inline const std::string NoBodyResponse::getCharacterEncoding() const
{ 
	return _resp.getCharacterEncoding(); 
}


inline PrintWriter& NoBodyResponse::getWriter()
{
	throw ServletException("Invalid call to NoBodyResponse::getWriter()");
}


inline void NoBodyResponse::setBufferSize(int size)
{ 
	_resp.setBufferSize(size); 
}


inline int NoBodyResponse::getBufferSize()
{ 
	return _resp.getBufferSize(); 
}


inline void NoBodyResponse::reset()
{ 
	_resp.reset(); 
}


inline void NoBodyResponse::resetBuffer()
{ 
	_resp.resetBuffer(); 
}


inline bool NoBodyResponse::isCommitted()
{ 
	return _resp.isCommitted(); 
}


inline void NoBodyResponse::flushBuffer()
{ 
	_resp.flushBuffer(); 
}


inline void NoBodyResponse::setLocale(const std::locale& loc)
{ 
	_resp.setLocale(loc); 
}


inline std::locale NoBodyResponse::getLocale()
{ 
	return _resp.getLocale(); 
}


// HttpServletResponse interface methods

inline void NoBodyResponse::addCookie(const Cookie& cookie)
{ 
	_resp.addCookie(cookie); 
}


inline bool NoBodyResponse::containsHeader(const std::string& name)
{ 
	return _resp.containsHeader(name); 
}


inline void NoBodyResponse::setStatus(int sc, const std::string& sm)
{ 
	_resp.setStatus(sc, sm); 
}


inline void NoBodyResponse::setStatus(int sc)
{ 
	_resp.setStatus(sc); 
}


inline void NoBodyResponse::setHeader(const std::string& name, const std::string& value)
{ 
	_resp.setHeader(name, value); 
}


inline void NoBodyResponse::setIntHeader(const std::string& name, int value)
{ 
	_resp.setIntHeader(name, value); 
}


inline void NoBodyResponse::setDateHeader(const std::string& name, long date)
{ 
	_resp.setDateHeader(name, date); 
}


inline void NoBodyResponse::sendError(int sc, const std::string& msg)
{ 
	_resp.sendError(sc, msg); 
}


inline void NoBodyResponse::sendError(int sc)
{ 
	_resp.sendError(sc); 
}


inline void NoBodyResponse::sendRedirect(const std::string& location)
{ 
	_resp.sendRedirect(location); 
}


inline std::string NoBodyResponse::encodeURL(const std::string& url) 
{ 
	return _resp.encodeURL(url); 
}


inline std::string NoBodyResponse::encodeRedirectURL(const std::string& url)
{ 
	return _resp.encodeRedirectURL(url); 
}


inline void NoBodyResponse::addHeader(const std::string& name, const std::string& value)
{ 
	_resp.addHeader(name, value); 
}


inline void NoBodyResponse::addDateHeader(const std::string& name, long value)
{ 
	_resp.addDateHeader(name, value); 
}


inline void NoBodyResponse::addIntHeader(const std::string& name, int value)
{ 
	_resp.addIntHeader(name, value); 
}


} } // namespace Poco::Servlet


#endif // Servlet_Http_NoBodyResponse_INCLUDED
