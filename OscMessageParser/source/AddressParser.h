#ifndef _ADDRESSPARSER_H_
#define _ADDRESSPARSER_H_

#include "BaseParser.h"

namespace OscMessageParser {

	typedef enum ADDRESS_PARSER_STATE {
		ADDRESS_PARSER_STATE_IDL,
		ADDRESS_PARSER_STATE_NSL,
		ADDRESS_PARSER_STATE_STR,
		ADDRESS_PARSER_STATE_PAD,
		ADDRESS_PARSER_STATE_DON,
		ADDRESS_PARSER_STATE_ERR,
		ADDRESS_PARSER_STATE_MAX,
	} AddressParserState;

	typedef enum ADDRESS_PARSER_RESPONSE {
		ADDRESS_PARSER_RESPONSE_RCV,
		ADDRESS_PARSER_RESPONSE_DON,
		ADDRESS_PARSER_RESPONSE_ERR
	} AddressParserResponse;

	class AddressParser : public BaseParser {
	public:

		typedef int (AddressParser::*AddressParserStateFunc)(char c, int offset);

		AddressParser();
		virtual ~AddressParser();
		int Push(char c, int offset);

	private:
	
		AddressParserStateFunc _stateMatrix[ADDRESS_PARSER_STATE_MAX];

		int FuncForStateIdle(char c, int offset);
		int FuncForStateNoslash(char c, int offset);
		int FuncForStateString(char c, int offset);
		int FuncForStatePadding(char c, int offset);
		int FuncForStateDone(char c, int offset);
		int FuncForStateError(char c, int offset);
	};

}
#endif // _ADDRESSPARSER_H_
