#include "TypetagParser.h"

namespace OscMessageParser {

#pragma region public
	TypetagParser::TypetagParser() {
		_stateMatrix[TYPETAG_PARSER_STATE_IDL] = &TypetagParser::FuncForStateIdle;
		_stateMatrix[TYPETAG_PARSER_STATE_TAG] = &TypetagParser::FuncForStateTag;
		_stateMatrix[TYPETAG_PARSER_STATE_PAD] = &TypetagParser::FuncForStatePadding;
		_stateMatrix[TYPETAG_PARSER_STATE_DON] = &TypetagParser::FuncForStateDone;
		_stateMatrix[TYPETAG_PARSER_STATE_ERR] = &TypetagParser::FuncForStateError;
	}

	TypetagParser::~TypetagParser(){}

	int TypetagParser::Push(char c, int offset) {
		return (this->*(_stateMatrix[_state]))(c, offset);
	}
#pragma endregion public

#pragma region private

	int TypetagParser::FuncForStateIdle(char c, int offset) {
		int result = TYPETAG_PARSER_RESPONSE_RCV;
		if( ',' == c) {
			_state = TYPETAG_PARSER_STATE_TAG;
		}
		else if( '\0' == c) {
		}
		else {
			_state = TYPETAG_PARSER_STATE_ERR;
			result = TYPETAG_PARSER_RESPONSE_ERR;
		}
		return result;
	}

	int TypetagParser::FuncForStateTag(char c, int offset) {
		int result = TYPETAG_PARSER_RESPONSE_RCV;
		if( ',' == c) {
			_state = TYPETAG_PARSER_STATE_ERR;
			result = TYPETAG_PARSER_RESPONSE_ERR;
		}
		else if( '\0' == c) {
			if( (offset+1)%4 == 0) {
				_state = TYPETAG_PARSER_STATE_DON;
				if(_buf[0] == '\0')
					result = TYPETAG_PARSER_RESPONSE_NON;
				else
					result = TYPETAG_PARSER_RESPONSE_PRM;
			}
			else {
				PushBuf(c);
				_state = TYPETAG_PARSER_STATE_PAD;
			}
		}
		else {
			if( 'i' == c) {
				PushBuf(c);
			}
			else if ('s' == c) {
				PushBuf(c);
			}
			else if ('f' == c) {
				PushBuf(c);
			}
			else if ('b' == c) {
				PushBuf(c);
			}
			else {
				_state = TYPETAG_PARSER_STATE_ERR;
				result = TYPETAG_PARSER_RESPONSE_ERR;
			}
		}
		return result;
	}

	int TypetagParser::FuncForStatePadding(char c, int offset) {
		int result = TYPETAG_PARSER_RESPONSE_RCV;
		if( ',' == c) {
			_state = TYPETAG_PARSER_STATE_ERR;
			result = TYPETAG_PARSER_RESPONSE_ERR;
		}
		else if( '\0' == c) {
			PushBuf(c);
			if( (offset+1)%4 == 0) {
				_state = TYPETAG_PARSER_STATE_DON;
				if(_buf[0] == '\0')
					result = TYPETAG_PARSER_RESPONSE_NON;
				else
					result = TYPETAG_PARSER_RESPONSE_PRM;
			}
		}
		else {
			_state = TYPETAG_PARSER_STATE_ERR;
			result = TYPETAG_PARSER_RESPONSE_ERR;
		}
		return result;
	}

	int TypetagParser::FuncForStateDone(char c, int offset) {
		int result = TYPETAG_PARSER_RESPONSE_RCV;
		if( ',' == c) {
			Flush();
			_state = TYPETAG_PARSER_STATE_TAG;
		}
		else if( '\0' == c) {
			// do nothing
		}
		else {
			_state = TYPETAG_PARSER_STATE_ERR;
			int result = TYPETAG_PARSER_RESPONSE_ERR;
		}
		return result;
	}

	int TypetagParser::FuncForStateError(char c, int offset) {
		if( ',' == c) {
			Flush();
			_state = TYPETAG_PARSER_STATE_TAG;
		}
		return TYPETAG_PARSER_RESPONSE_RCV;
	}

#pragma endregion private
}