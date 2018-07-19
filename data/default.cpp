#include "default.h"

void MyOutputDebugString(PCHAR lpszFormat, ...)
{
	va_list arglist;
	va_start(arglist, lpszFormat);
	char outputstr[4095];
	vsprintf(outputstr, lpszFormat, arglist);
	va_end(arglist);
	OutputDebugStringA(outputstr);
}