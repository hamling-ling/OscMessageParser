#include "OscCommon.h"

bool sys_is_little_endian(){
#if defined(__LITTLE_ENDIAN__)
	return true;
#elif defined(__BIG_ENDIAN__)
	return false;
#else
	int i = 1;
	return (*(char*)&i) != 0;
#endif
}
