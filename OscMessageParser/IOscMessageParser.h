#ifndef _IOSCMESSAGEPARSER_H_
#define _IOSCMESSAGEPARSER_H_

#include "source\OscCommon.h"

using namespace std::tr1;

namespace OscMessageParser {

	class IOscMessageParser {
	public:
		IOscMessageParser(){}
		virtual ~IOscMessageParser(){};
		virtual bool Push(char c, int offset) = 0;
		virtual void Read(OscMessage *msg) = 0;
		static shared_ptr<IOscMessageParser> Create();
	};

	class A {
	public:
		A(){}
		static std::tr1::shared_ptr<A> Create();
		virtual ~A(){};
	};
}

#endif
