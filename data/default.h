#pragma once
#include <Windows.h>
#include <stdarg.h>
#include <string>
struct TMsTree
{
	TMsTree* left;//×ó×ÓÊ÷
	TMsTree* root;//Ê÷
	TMsTree* right;//ÓÒ×ÓÊ÷
};

void MyOutputDebugString(PCHAR lpszFormat, ...);