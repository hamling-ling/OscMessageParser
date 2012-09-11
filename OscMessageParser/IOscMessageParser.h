#ifndef _IOSCMESSAGEPARSER_H_
#define _IOSCMESSAGEPARSER_H_

#include "utility/OscCommon.h"

namespace OscMessageParser {

	class IOscMessageParser {
	public:
		IOscMessageParser(){}
		virtual ~IOscMessageParser(){};
		virtual bool Push(char c) = 0;
		virtual void Read(OscMessage *msg) = 0;
		static IOscMessageParser* Create();
	};
}

#endif
