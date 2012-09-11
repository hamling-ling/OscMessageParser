#include "BaseParser.h"

namespace OscMessageParser {

#pragma region public
	BaseParser::BaseParser() : idx(0), _state(0) {
		memset(_buf, 0, sizeof(_buf));
	}
	BaseParser::~BaseParser(){};
	void BaseParser::Read(char* outBuf, int size) {
		memcpy(outBuf, _buf, size);
		Flush();
	}
	void BaseParser::Flush() {
		_state = 0;
		idx = 0;
		memset(_buf, 0, sizeof(_buf));
	}

#pragma endregion public

#pragma region protected

	void BaseParser::PushBuf(char c) {
		if(idx < sizeof(_buf)) {
			_buf[idx++] = c;
		}
	}

	int BaseParser::GetIdx() { return idx; }

#pragma endregion protected
}
