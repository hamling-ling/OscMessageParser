#ifndef _OSCCOMMON_H_
#define _OSCCOMMON_H_

#include <cstdint>
#include <memory>

#define BUF_SIZE	32
#define MAX_PARAM	8

#define	INT_TAG	'i'
#define	FLT_TAG	'f'
#define BLB_TAG	'b'

typedef char osctag_t;

namespace OscMessageParser {

	typedef union OSCVALUE {
		int32_t	IntValue;
		float	FloatValue;
		char BlobValue[BUF_SIZE];
		osctag_t TypeTag;
	} OscValue;

	typedef struct OSCPARAM {
		int Length;
		OscValue Value;
	} OscParam;

	typedef struct OSCMESSAGE {
		char Address[BUF_SIZE];
		int ParamNum;
		OscParam Params[MAX_PARAM]; 
	} OscMessage;

}

template< class T > void SafeDelete( T*& pVal )
{
	delete pVal;
	pVal = NULL;
}

template< class T > void SafeDeleteArray( T*& pVal )
{
	delete[] pVal;
	pVal = NULL;
}

bool sys_is_little_endian();

#endif // _OSCCOMMON_H_
