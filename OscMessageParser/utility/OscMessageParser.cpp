
#include "OscMessageParser.h"

namespace OscMessageParser {

#pragma region public

	IOscMessageParser* IOscMessageParser::Create() {
		OscMessageParser *p = new OscMessageParser();
		IOscMessageParser* ip = static_cast<IOscMessageParser*>(p);
		return ip;
	}

	OscMessageParser::OscMessageParser() {
		_stateMatrix[OSC_MESSAGE_PARSER_STATE_IDL] = &OscMessageParser::FuncForStateIdle;
		_stateMatrix[OSC_MESSAGE_PARSER_STATE_ADR] = &OscMessageParser::FuncForStateAddress;
		_stateMatrix[OSC_MESSAGE_PARSER_STATE_TAG] = &OscMessageParser::FuncForStateTypetag;
		_stateMatrix[OSC_MESSAGE_PARSER_STATE_PRM] = &OscMessageParser::FuncForStateParameter;
		_stateMatrix[OSC_MESSAGE_PARSER_STATE_SRD] = &OscMessageParser::FuncForStateStored;
		Flush();
	}

	OscMessageParser::~OscMessageParser() {}

	bool OscMessageParser::Push(char c) {
		bool result = (this->*(_stateMatrix[_state]))(c,_offset++);
		return result;
	}

	void OscMessageParser::Read(OscMessage *msg) {
		memcpy(msg, &_msg, sizeof(_msg));
		Flush();
	}

#pragma endregion public

#pragma region private

	bool OscMessageParser::FuncForStateIdle(char c, int offset) {
		int res = _addPsr.Push(c,offset);
		if(res == ADDRESS_PARSER_RESPONSE_RCV) {
			_state = OSC_MESSAGE_PARSER_STATE_ADR;
		}
		else if(res == ADDRESS_PARSER_RESPONSE_ERR) {
			Flush();
		}
		return false;
	}

	bool OscMessageParser::FuncForStateAddress(char c, int offset) {
		int res = _addPsr.Push(c,offset);
		if(res == ADDRESS_PARSER_RESPONSE_RCV) {
			// stay
		}
		else if(res == ADDRESS_PARSER_RESPONSE_DON) {
			_addPsr.Read(_msg.Address, BUF_SIZE);
			_state = OSC_MESSAGE_PARSER_STATE_TAG;
		}
		else {
			Flush();
		}
		return false;
	}

	bool OscMessageParser::FuncForStateTypetag(char c, int offset) {
		int res = _tagPsr.Push(c,offset);
		if(res == TYPETAG_PARSER_RESPONSE_RCV) {
			// stay
		}
		else if (res == TYPETAG_PARSER_RESPONSE_PRM) {
			char buf[BUF_SIZE];
			memset(buf, 0, sizeof(buf));
			_tagPsr.Read(buf, sizeof(buf));
			_prmPsr.SetTypeList(buf);
			_state = OSC_MESSAGE_PARSER_STATE_PRM;
		}
		else if (res == TYPETAG_PARSER_RESPONSE_NON) {
			_state = OSC_MESSAGE_PARSER_STATE_SRD;
		}
		else {
			Flush();
		}
		return false;
	}

	bool OscMessageParser::FuncForStateParameter(char c, int offset) {
		int res = _prmPsr.Push(c,offset);
		if(res == PARAM_PARSER_RESPONSE_RCV) {
			// stay
		}
		else if(res == PARAM_PARSER_RESPONSE_DON) {
			_msg.ParamNum = _prmPsr.GetParamNum();
			_prmPsr.Read(reinterpret_cast<char*>(_msg.Params), sizeof(_msg.Params));
			_state = OSC_MESSAGE_PARSER_STATE_SRD;
			return true;
		}
		else {
			Flush();
		}
		return false;
	}

	bool OscMessageParser::FuncForStateStored(char c, int offset) {
		return 0;
	}

	void OscMessageParser::Flush() {
		_addPsr.Flush();
		_tagPsr.Flush();
		_prmPsr.Flush();

		memset(&_msg, 0, sizeof(_msg));

		_state = OSC_MESSAGE_PARSER_STATE_IDL;

		_offset = 0;
	}

#pragma endregion private
}
