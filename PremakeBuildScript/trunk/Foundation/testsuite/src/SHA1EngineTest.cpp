//
// SHA1EngineTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/SHA1EngineTest.cpp#1 $
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


#include "SHA1EngineTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/SHA1Engine.h"


using Poco::SHA1Engine;
using Poco::DigestEngine;


SHA1EngineTest::SHA1EngineTest(const std::string& name): CppUnit::TestCase(name)
{
}


SHA1EngineTest::~SHA1EngineTest()
{
}


void SHA1EngineTest::testSHA1()
{
	SHA1Engine engine;

	// test vectors from FIPS 180-1

	engine.update("abc");
	assert (DigestEngine::digestToHex(engine.digest()) == "a9993e364706816aba3e25717850c26c9cd0d89d");

	engine.update("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq");
	assert (DigestEngine::digestToHex(engine.digest()) == "84983e441c3bd26ebaae4aa1f95129e5e54670f1");

	for (int i = 0; i < 1000000; ++i)
		engine.update('a');
	assert (DigestEngine::digestToHex(engine.digest()) == "34aa973cd4c4daa4f61eeb2bdbad27316534016f");
}


void SHA1EngineTest::setUp()
{
}


void SHA1EngineTest::tearDown()
{
}


CppUnit::Test* SHA1EngineTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("SHA1EngineTest");

	CppUnit_addTest(pSuite, SHA1EngineTest, testSHA1);

	return pSuite;
}
