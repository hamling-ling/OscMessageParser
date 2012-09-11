#ifndef _BASEPARSER_H_
#define _BASEPARSER_H_

#include "OscCommon.h"

namespace OscMessageParser {

	class BaseParser {
	public:
		BaseParser();
		virtual ~BaseParser();
		virtual int Push(char c, int offset) = 0;
		virtual void Read(char* outBuf, int size);
		virtual void Flush();
	protected:
		int _state;
		char _buf[BUF_SIZE];
		void PushBuf(char c);
		int GetIdx();
	private:
		int idx;
	};

}
#endif // _BASEPARSER_H_
