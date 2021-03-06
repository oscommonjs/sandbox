//
// SSHChannelStream.cpp
//
// $Id: //poco/Main/SSH/src/SSHChannelStream.cpp#6 $
//
// Library: SSH
// Package: SSHCore
// Module:  SSHChannelStream
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
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


#include "Poco/SSH/SSHChannelStream.h"
#include "libssh2.h"


namespace Poco {
namespace SSH {


SSHChannelStreamBuf::SSHChannelStreamBuf(const SSHChannel& channel, StreamType type, Poco::BufferedStreamBuf::openmode mode):
	Poco::BufferedStreamBuf(STREAM_BUFFER_SIZE, mode),
	_channel(channel),
	_type(type)
{
}


SSHChannelStreamBuf::~SSHChannelStreamBuf()
{
}


bool SSHChannelStreamBuf::data()
{
	// first check the number of bytes cached internally
	if (in_avail() > 0)
		return true;

	LIBSSH2_POLLFD fd;
	fd.type = LIBSSH2_POLLFD_CHANNEL;
	fd.fd.channel = _channel.channel();

	if (_type == ST_STD)
		fd.events = LIBSSH2_POLLFD_POLLIN;
	else
		fd.events = LIBSSH2_POLLFD_POLLEXT;
	fd.revents = 0;

	int val = libssh2_poll(&fd, 1, 1000);

	return (val != 0);
}


int SSHChannelStreamBuf::sync()
{
	int tmp = Poco::BufferedStreamBuf::sync();

	if (_type == ST_STD)
		libssh2_channel_flush(_channel.channel());
	else
		libssh2_channel_flush_stderr(_channel.channel());

	return tmp;
}


void SSHChannelStreamBuf::close()
{
	sync();
}

int SSHChannelStreamBuf::readFromDevice(char* buffer, std::streamsize length)
{
	if (_type == ST_STD)
		return libssh2_channel_read(_channel.channel(), buffer, length);

	return libssh2_channel_read_stderr(_channel.channel(), buffer, length);
}


int SSHChannelStreamBuf::writeToDevice(const char* buffer, std::streamsize length)
{
	if (_type == ST_STD)
		return libssh2_channel_write(_channel.channel(), buffer, length);

	return libssh2_channel_write_stderr(_channel.channel(), buffer, length);
}


SSHChannelStreamIOS::SSHChannelStreamIOS(const SSHChannel& channel, SSHChannelStreamIOS::StreamType type, std::ios_base::openmode mode):
	_buf(channel, type, mode)
{
}


SSHChannelStreamIOS::~SSHChannelStreamIOS()
{
}


SSHChannelStreamBuf* SSHChannelStreamIOS::rdbuf()
{
	return &_buf;
}


SSHChannelInputStream::SSHChannelInputStream(const SSHChannel& channel, StreamType type):
	SSHChannelStreamIOS(channel, type, std::ios::in),
	std::istream(&_buf)
{
}


SSHChannelInputStream::~SSHChannelInputStream()
{
}


bool SSHChannelInputStream::data()
{
	return _buf.data();
}


SSHChannelOutputStream::SSHChannelOutputStream(const SSHChannel& channel, StreamType type):
	SSHChannelStreamIOS(channel, type, std::ios::out),
	std::ostream(&_buf)
{
}


SSHChannelOutputStream::~SSHChannelOutputStream()
{
	close();
}


void SSHChannelOutputStream::close()
{
	_buf.close();
}


SSHChannelStream::SSHChannelStream(const SSHChannel& channel, StreamType type):
	SSHChannelStreamIOS(channel, type, std::ios::out|std::ios::in),
	std::iostream(&_buf)
{
}


SSHChannelStream::~SSHChannelStream()
{
	close();
}


void SSHChannelStream::close()
{
	_buf.close();
}



bool SSHChannelStream::data()
{
	return _buf.data();
}


} } // namespace Poco::SSH
