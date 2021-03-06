//
// HttpServer.h
//
//
// Library: ServletEx
// Package: Http
// Module:  HttpServer
//
// Definition of the HttpServer class.
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


#ifndef ServletEx_Http_HttpServer_INCLUDED
#define ServletEx_Http_HttpServer_INCLUDED


#include "Poco/Servlet/ServletBase.h"
#include "Poco/Servlet/Ex/GenericServer.h"
#include "Poco/Servlet/Ex/HttpServerConfig.h"
#include "Poco/Servlet/Ex/HttpServletDispatcher.h"


namespace Poco {
namespace Servlet {
namespace Ex {


class Servlet_API HttpServer : public GenericServer
	/// Abstract class for containable http servers.
	/// Implementations must override start() method.
{
public:
	HttpServer();
		///constructor

	HttpServer(const HttpServerConfig& config, HttpServletDispatcher& dispatcher, Poco::Logger* pLogger=0);
		///constructor

	virtual ~HttpServer();
		///destructor

	virtual void init(const HttpServerConfig& config, HttpServletDispatcher& dispatcher, Poco::Logger* pLogger=0);
		/// Initializes the http server.

	virtual void destroy();
		/// Does nothing.

	virtual void start() = 0;
		/// Starts the server;

	virtual void stop();
		/// Stops the server;

	void setName(const std::string& name);
		/// Sets the http server name.

	void setGlobalDir(const std::string& globalDir);
		/// Sets the http server global directory.
		/// (See HttpServerConfig documentation for explanation on global directory).

	std::string getName();
		/// Returns the http server name.

	const std::vector<std::string>& interfaces();
		/// Returns the http server listening addresses.

	int getPort();
		/// Returns the http server listening port.

	std::string HttpServer::getGlobalDir();
		/// Returns the http server global directory.
		/// (See HttpServerConfig documentation for explanation on global directory).

	bool isRunning() const;
		/// Returns true if the server is running.

	bool isStopped() const;
		/// Returns true if the server is stopped.

protected:
	 const HttpServerConfig* config() const;
	 HttpServletDispatcher* dispatcher() const;
	 void running(bool status);

private:
	 bool _running;
	  /// Member indicating whether server is up and running.
	  /// Important: 
	  /// In order to properly indicate the server status, an 
	  /// implementation must set it to true after starting up the server.

	 HttpServerConfig* _pConfig;
	 HttpServletDispatcher* _pDispatcher;
	 bool _stop;
};


///
/// inlines
///


inline void HttpServer::running(bool status)
{
	_running = status;
}


inline bool HttpServer::isRunning() const
{
  return _running;
}


inline bool HttpServer::isStopped() const
{
	return _stop;
}


inline const HttpServerConfig* HttpServer::config() const
{
	return _pConfig;
}


inline HttpServletDispatcher* HttpServer::dispatcher() const
{
	return _pDispatcher;
}


} } } // namespace Poco::Servlet::Ex


#endif //ServletEx_Http_HttpServer_INCLUDED
