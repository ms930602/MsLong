#pragma once
#include <Windows.h>
#include <stdarg.h>
#include <string>
struct TMsTree
{
	TMsTree* left;//������
	TMsTree* root;//��
	TMsTree* right;//������
};

void MyOutputDebugString(PCHAR lpszFormat, ...);