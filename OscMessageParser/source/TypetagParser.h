#ifndef _TYPETAGPARSER_H_
#define _TYPETAGPARSER_H_

#include "BaseParser.h"

namespace OscMessageParser {

	typedef enum TYPETAG_PARSER_STATE {
		TYPETAG_PARSER_STATE_IDL,
		TYPETAG_PARSER_STATE_TAG,
		TYPETAG_PARSER_STATE_PAD,
		TYPETAG_PARSER_STATE_DON,
		TYPETAG_PARSER_STATE_ERR,
		TYPETAG_PARSER_STATE_MAX
	} TypetagParserState;

	typedef enum TYPETAG_PARSER_RESPONSE {
		TYPETAG_PARSER_RESPONSE_RCV,
		TYPETAG_PARSER_RESPONSE_PRM,
		TYPETAG_PARSER_RESPONSE_NON,
		TYPETAG_PARSER_RESPONSE_ERR
	} TypetagParserResponse;


	class TypetagParser : public BaseParser {
	public :
		typedef int (TypetagParser::*TypetagParserStateFunc)(char c, int offset);

		TypetagParser();
		virtual ~TypetagParser();
		int Push(char c, int offset);

	private :

		TypetagParserStateFunc _stateMatrix[TYPETAG_PARSER_STATE_MAX];

		int FuncForStateIdle(char c, int offset);
		int FuncForStateTag(char c, int offset);
		int FuncForStatePadding(char c, int offset);
		int FuncForStateDone(char c, int offset);
		int FuncForStateError(char c, int offset);
	};

}

#endif // _TYPETAGPARSER_H_
