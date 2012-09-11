#ifndef _OSCMESSAGEPARSER_H_
#define _OSCMESSAGEPARSER_H_

#include "../IOscMessageParser.h"
#include "AddressParser.h"
#include "TypetagParser.h"
#include "ParameterParser.h"

namespace OscMessageParser {

	typedef enum OSC_MESSAGE_PARSER_STATE {
		OSC_MESSAGE_PARSER_STATE_IDL,
		OSC_MESSAGE_PARSER_STATE_ADR,
		OSC_MESSAGE_PARSER_STATE_TAG,
		OSC_MESSAGE_PARSER_STATE_PRM,
		OSC_MESSAGE_PARSER_STATE_SRD,
		OSC_MESSAGE_PARSER_STATE_MAX
	} OscMessageParserState;

	class OscMessageParser : public IOscMessageParser {
	public:
		typedef bool (OscMessageParser::*ReceiverStateFunc)(char c, int offset);

		OscMessageParser();
		virtual ~OscMessageParser();
		bool Push(char c);
		void Read(OscMessage *msg);

	private:
		OscMessageParserState _state;
		ReceiverStateFunc _stateMatrix[OSC_MESSAGE_PARSER_STATE_MAX];

		OscMessage _msg;
		AddressParser _addPsr;
		TypetagParser _tagPsr;
		ParameterParser _prmPsr;
		int _offset;

		bool FuncForStateIdle(char c, int offset);
		bool FuncForStateAddress(char c, int offset);
		bool FuncForStateTypetag(char c, int offset);
		bool FuncForStateParameter(char c, int offset);
		bool FuncForStateStored(char c, int offset);
		void Flush();
	};

}

#endif // _OSCMESSAGEPARSER_H_
