#ifndef _VALUEPARSER_H_
#define _VALUEPARSER_H_

#include "BaseParser.h"

namespace OscMessageParser {

	typedef enum VALUE_PARSER_RESPONSE {
		VALUE_PARSER_RESPONSE_RCV,
		VALUE_PARSER_RESPONSE_DON,
	} IntParserResponse;

	class ValueParser : public BaseParser {
	public:
		ValueParser();
		virtual ~ValueParser();
	};

}

#endif // _VALUEPARSER_H_
