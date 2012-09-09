#ifndef _INTPARSER_H_
#define _INTPARSER_H_

#include "ValueParser.h"

namespace OscMessageParser {

	typedef enum INT_PARSER_STATE {
		INT_PARSER_STATE0,
		INT_PARSER_STATE1,
		INT_PARSER_STATE2,
		INT_PARSER_STATE3,
		INT_PARSER_STATE_DON,
		INT_PARSER_STATE_MAX
	} IntParserState;

	class IntParser : public ValueParser {
	public:
		typedef int (IntParser::*IntParserStateFunc)(char c, int offset);
		IntParser();
		~IntParser();
		int Push(char c, int offset);
		int32_t GetValue();
	private:
		IntParserStateFunc _stateMatrix[INT_PARSER_STATE_MAX];
	private:
		int Read0thByte(char c, int offset);
		int Read1stByte(char c, int offset);
		int Read2ndByte(char c, int offset);
		int Read3rdByte(char c, int offset);
		int DoNothing(char c, int offset);
	};

}

#endif // _INTPARSER_H_
