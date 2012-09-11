// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IOscMessageParser.h"
#include <iostream>

using namespace std;
using namespace OscMessageParser;
using namespace std::tr1;

void TestMessageParser(char* data, int size, IOscMessageParser *psr) {
	// message will be stored here
	OscMessage msg;

	// parse data
	for(int i = 0; i < size; i++) {
		if(psr->Push(data[i], i)) {
			psr->Read(&msg);
			break;
		}
	}

	// output result
	cout << "OSC Address:" << msg.Address << endl;
	for(int i = 0; i < msg.ParamNum; i++) {
		cout << "param" << i << ":" << msg.Params[i].Value.IntValue << endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	// create parser
	IOscMessageParser *p = IOscMessageParser::Create();

	char data1[] = {
		0x2f, 0x6f, 0x73, 0x63, 0x2f, 0x62, 0x75, 0x74,
		0x74, 0x6f, 0x6e, 0x32, 0x00, 0x00, 0x00, 0x00,
		0x2c, 0x69, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
	};
	TestMessageParser(data1, sizeof(data1), p);

	char data2[] = {
		0x2f, 0x6f, 0x73, 0x63, 0x2f, 0x62, 0x00, 0x00,
		0x2c, 0x69, 0x69, 0x00, 0x00, 0x00, 0x00, 0x01,
		0x00, 0x00, 0x00, 0x02
	};
	TestMessageParser(data2, sizeof(data2), p);

	return 0;
}

