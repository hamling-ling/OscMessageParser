#ifndef _PARAMETERPARSER_H_
#define _PARAMETERPARSER_H_

#include "BaseParser.h"
#include "OscCommon.h"
#include "ValueParser.h"

namespace OscMessageParser {

	typedef enum PARAM_PARSER_STATE {
		PARAM_PARSER_STATE_IDLE,
		PARAM_PARSER_STATE_INPROCESS,
		PARAM_PARSER_STATE_DON,
		PARAM_PARSER_STATE_MAX
	} PARAMParserState;

	typedef enum PARAM_PARSER_RESPONSE {
		PARAM_PARSER_RESPONSE_RCV,
		PARAM_PARSER_RESPONSE_DON,
		PARAM_PARSER_RESPONSE_ERR
	} ParameterParserResponse;

	class ParameterParser : public BaseParser {
	public:
		typedef int (ParameterParser::*ParameterParserStateFunc)(char c, int offset);
		ParameterParser();
		virtual ~ParameterParser();
		void SetTypeList(const char* typeList);
		int Push(char c, int offset);
		void Flush();
		void Read(char* outBuf, int size);
		int GetParamNum();
	private:
		OscParam _params[MAX_PARAM];
		char _typeList[MAX_PARAM];
		int _typeIdx;
		ParameterParserStateFunc _stateMatrix[PARAM_PARSER_STATE_MAX];
		ValueParser *_pPsr;
		int FuncForStateIdle(char c, int offset);
		int FuncForStateInProcess(char c, int offset);
		int FuncForStateDone(char c, int offset);
	};

}

#endif // _PARAMETERPARSER_H_
