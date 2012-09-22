#include "AddressParser.h"

namespace OscMessageParser {

#pragma region public

	AddressParser::AddressParser() {
		_stateMatrix[ADDRESS_PARSER_STATE_IDL] = &AddressParser::FuncForStateIdle;
		_stateMatrix[ADDRESS_PARSER_STATE_NSL] = &AddressParser::FuncForStateNoslash;
		_stateMatrix[ADDRESS_PARSER_STATE_STR] = &AddressParser::FuncForStateString;
		_stateMatrix[ADDRESS_PARSER_STATE_PAD] = &AddressParser::FuncForStatePadding;
		_stateMatrix[ADDRESS_PARSER_STATE_DON] = &AddressParser::FuncForStateDone;
		_stateMatrix[ADDRESS_PARSER_STATE_ERR] = &AddressParser::FuncForStateError;
	}

	AddressParser::~AddressParser() {}
	int AddressParser::Push(char c, int offset) {
		return (this->*(_stateMatrix[_state]))(c, offset);
	}

#pragma endregion public

#pragma region private

	int AddressParser::FuncForStateIdle(char c, int offset) {
		if('/' == c) {
			_state = ADDRESS_PARSER_STATE_NSL;
			PushBuf(c);
		}
		else {
			_state = ADDRESS_PARSER_STATE_ERR;
			return ADDRESS_PARSER_RESPONSE_ERR;
		}

		return ADDRESS_PARSER_RESPONSE_RCV;
	}

	int AddressParser::FuncForStateNoslash(char c, int offset) {
		int result = ADDRESS_PARSER_RESPONSE_ERR;
		if('/' == c) {
			_state = ADDRESS_PARSER_STATE_ERR;
		}
		else if( '\0' == c){
			_state = ADDRESS_PARSER_STATE_ERR;
		}
		else {
			PushBuf(c);
			_state = ADDRESS_PARSER_STATE_STR;
			result = ADDRESS_PARSER_RESPONSE_RCV;
		}

		return result;
	}

	int AddressParser::FuncForStateString(char c, int offset) {
		int result = ADDRESS_PARSER_RESPONSE_RCV;

		PushBuf(c);
		if('/' == c) {
			_state = ADDRESS_PARSER_STATE_NSL;
		}
		else if( '\0' == c){
			if((offset+1)%4 == 0) {
				_state = ADDRESS_PARSER_STATE_DON;
				result = ADDRESS_PARSER_RESPONSE_DON;
			}
			else {
				_state = ADDRESS_PARSER_STATE_PAD;
			}
		}

		return result;
	}

	int AddressParser::FuncForStatePadding(char c, int offset) {
		int result = ADDRESS_PARSER_RESPONSE_RCV;
		if( '\0' == c){
			PushBuf(c);
			if((offset+1)%4 == 0) {
				_state = ADDRESS_PARSER_STATE_DON;
				result = ADDRESS_PARSER_RESPONSE_DON;
			}
			else {
				_state = ADDRESS_PARSER_STATE_PAD;
			}
		}
		else {
			_state = ADDRESS_PARSER_STATE_ERR;
			result = ADDRESS_PARSER_RESPONSE_ERR;
		}

		return result;
	}

	int AddressParser::FuncForStateDone(char c, int offset) {
		int result = ADDRESS_PARSER_RESPONSE_RCV;
		if('/' == c) {
			Flush();
			PushBuf(c);
			_state = ADDRESS_PARSER_STATE_IDL;
		}
		else if( '\0' == c){
		}
		else {
			_state = ADDRESS_PARSER_STATE_ERR;
			result = ADDRESS_PARSER_RESPONSE_ERR;
		}
		return result;
	}

	int AddressParser::FuncForStateError(char c, int offset) {
		int result = ADDRESS_PARSER_RESPONSE_RCV;
		if('/' == c) {
			Flush();
			PushBuf(c);
			_state = ADDRESS_PARSER_STATE_NSL;
		}

		return result;
	}

#pragma endregion private

}
