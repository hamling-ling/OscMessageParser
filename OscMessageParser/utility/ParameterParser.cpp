#include "ParameterParser.h"
#include "IntParser.h"

namespace OscMessageParser {

#pragma region public

	ParameterParser::ParameterParser() : _pPsr(NULL) {
		Flush();
		_stateMatrix[PARAM_PARSER_STATE_IDLE] = &ParameterParser::FuncForStateIdle;
		_stateMatrix[PARAM_PARSER_STATE_INPROCESS] = &ParameterParser::FuncForStateInProcess;
		_stateMatrix[PARAM_PARSER_STATE_DON] = &ParameterParser::FuncForStateDone;
	}

	ParameterParser::~ParameterParser() {
		SafeDelete(_pPsr);
	}
	
	void ParameterParser::SetTypeList(const char* typeList) {
		Flush();
		int sz = sizeof(_typeList);
		memcpy(_typeList, typeList, sizeof(typeList));
	}

	int ParameterParser::Push(char c, int offset) {
		return (this->*(_stateMatrix[_state]))(c, offset);
	}

	void ParameterParser::Flush() {
		_typeIdx = 0;
		SafeDelete(_pPsr);
		memset(_params, 0, sizeof(_params));
		memset(_typeList, 0, sizeof(_typeList));
		BaseParser::Flush();
	}

	void ParameterParser::Read(char* outBuf, int size) {
		memcpy(outBuf, &_params, size);
	}

	int ParameterParser::GetParamNum() {
		return _typeIdx;
	}

#pragma endregion public

#pragma region private

	int ParameterParser::FuncForStateIdle(char c, int offset) {
		int res = PARAM_PARSER_RESPONSE_RCV;
		if(_typeList[_typeIdx] == 'i') {
			_pPsr = new IntParser();
			_state = PARAM_PARSER_STATE_INPROCESS;
			_pPsr->Push(c, offset);
			_params[_typeIdx].Value.TypeTag = _typeList[_typeIdx];
			_params[_typeIdx].Length = 1;
			_typeIdx++;
		}
		else {
			_state = PARAM_PARSER_STATE_DON;
			res = PARAM_PARSER_RESPONSE_DON;
		}
		return res;
	}

	int ParameterParser::FuncForStateInProcess(char c, int offset) {
		int res = PARAM_PARSER_RESPONSE_RCV;
		int response = _pPsr->Push(c, offset);
		if(response == VALUE_PARSER_RESPONSE_DON) {

			_pPsr->Read(_params[_typeIdx-1].Value.BlobValue, BUF_SIZE);

			if(_typeIdx < MAX_PARAM && sizeof(_typeList) && _typeList[_typeIdx] != '\0') {
				_state = PARAM_PARSER_STATE_IDLE;
			}
			else {
				_state = PARAM_PARSER_STATE_DON;
				res = PARAM_PARSER_RESPONSE_DON;
			}
		}
		return res;
	}

	int ParameterParser::FuncForStateDone(char c, int offset) {
		return PARAM_PARSER_RESPONSE_DON;
	}

#pragma endregion private

}
