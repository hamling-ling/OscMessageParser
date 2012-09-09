#include "IntParser.h"
#include <algorithm>

using namespace std;

namespace OscMessageParser {

#pragma region public

	IntParser::IntParser() {
		_stateMatrix[INT_PARSER_STATE0] = &IntParser::Read0thByte;
		_stateMatrix[INT_PARSER_STATE1] = &IntParser::Read1stByte;
		_stateMatrix[INT_PARSER_STATE2] = &IntParser::Read2ndByte;
		_stateMatrix[INT_PARSER_STATE3] = &IntParser::Read3rdByte;
		_stateMatrix[INT_PARSER_STATE_DON] = &IntParser::DoNothing;
	}

	IntParser::~IntParser() {}

	int IntParser::Push(char c, int offset) {
		return (this->*(_stateMatrix[_state]))(c, offset);
	}

	int32_t IntParser::GetValue() {
		int32_t ret = 0;
		// supposing byte-order is same
		memcpy(&ret, _buf, sizeof(ret));
		return ret;
	}

#pragma endregion public

#pragma region private

	int IntParser::Read0thByte(char c, int offset) {
		PushBuf(c);
		_state = INT_PARSER_STATE1;
		return VALUE_PARSER_RESPONSE_RCV;
	}
	int IntParser::Read1stByte(char c, int offset) {
		PushBuf(c);
		_state = INT_PARSER_STATE2;
		return VALUE_PARSER_RESPONSE_RCV;
	}
	int IntParser::Read2ndByte(char c, int offset) {
		PushBuf(c);
		_state = INT_PARSER_STATE3;
		return VALUE_PARSER_RESPONSE_RCV;
	}
	int IntParser::Read3rdByte(char c, int offset) {
		PushBuf(c);
		if(sys_is_little_endian()) {
			swap(_buf[0], _buf[3]);
			swap(_buf[1], _buf[2]);
		}
		return VALUE_PARSER_RESPONSE_DON;
	}
	int IntParser::DoNothing(char c, int offset) {
		return VALUE_PARSER_RESPONSE_DON;
	}

#pragma endregion private
}