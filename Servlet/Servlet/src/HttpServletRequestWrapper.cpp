//
// HttpServletRequestWrapper.cpp
//
//
// Library: Servlet
// Package: Http
// Module:  HttpServletRequestWrapper
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
// Copyright (c) 2004 The Apache Software Foundation.
// http://www.apache.org/licenses/LICENSE-2.0
// 


#include "Poco/Servlet/HttpServletRequest.h"
#include "Poco/Servlet/HttpServletRequestWrapper.h"


namespace Poco {
namespace Servlet {


HttpServletRequestWrapper::HttpServletRequestWrapper(HttpServletRequest& request) :
	_request(request), 
	ServletRequestWrapper(request)
{
}


std::string HttpServletRequestWrapper::getAuthType() 
{
	return _request.getAuthType();
}


const std::vector<Cookie>& HttpServletRequestWrapper::getCookies() 
{
	return _request.getCookies();
}


long HttpServletRequestWrapper::getDateHeader(const std::string& name) 
{
	return _request.getDateHeader(name);
}


std::string HttpServletRequestWrapper::getHeader(const std::string& name) 
{
	return _request.getHeader(name);
}


std::vector<std::string> HttpServletRequestWrapper::getHeaders(const std::string& name) 
{
	return _request.getHeaders(name);
}  


std::vector<std::string> HttpServletRequestWrapper::getHeaderNames() 
{
	return _request.getHeaderNames();
}


int HttpServletRequestWrapper::getIntHeader(const std::string& name) 
{
	return _request.getIntHeader(name);
}


std::string HttpServletRequestWrapper::getMethod() 
{
	return _request.getMethod();
}


std::string HttpServletRequestWrapper::getPathInfo() 
{
	return _request.getPathInfo();
}


std::string HttpServletRequestWrapper::getPathTranslated() 
{
	return _request.getPathTranslated();
}


std::string HttpServletRequestWrapper::getContextPath() 
{
	return _request.getContextPath();
}


std::string HttpServletRequestWrapper::getQueryString() 
{
	return _request.getQueryString();
}


std::string HttpServletRequestWrapper::getRemoteUser() 
{
	return _request.getRemoteUser();
}


bool HttpServletRequestWrapper::isUserInRole(const std::string& role) 
{
	return _request.isUserInRole(role);
}


/*    java.security.Principal getUserPrincipal() {
	return _request.getUserPrincipal();
		}
	*/  


std::string HttpServletRequestWrapper::getRequestedSessionId() 
{
	return _request.getRequestedSessionId();
}


std::string HttpServletRequestWrapper::getRequestURI() 
{
	return _request.getRequestURI();
}


std::string HttpServletRequestWrapper::getRequestURL() 
{
	return _request.getRequestURL();
}


std::string HttpServletRequestWrapper::getServletPath() 
{
	return _request.getServletPath();
}


const HttpSession* HttpServletRequestWrapper::getSession(bool create) 
{
	return _request.getSession(create);
}


const HttpSession* HttpServletRequestWrapper::getSession() 
{
	return _request.getSession();
}


bool HttpServletRequestWrapper::isRequestedSessionIdValid() 
{
	return _request.isRequestedSessionIdValid();
}


bool HttpServletRequestWrapper::isRequestedSessionIdFromCookie() 
{
	return _request.isRequestedSessionIdFromCookie();
}


bool HttpServletRequestWrapper::isRequestedSessionIdFromURL() 
{
	return _request.isRequestedSessionIdFromURL();
}


bool HttpServletRequestWrapper::isRequestedSessionIdFromUrl() 
{
	return _request.isRequestedSessionIdFromUrl();
}


} } // namespace Poco::Servlet