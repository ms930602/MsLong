#pragma once
#include <Windows.h>

struct TMsTree
{
	TMsTree* left;//������
	TMsTree* root;//��
	TMsTree* right;//������
};



#define def__debug__lib 1
#undef  dPrintA
#if     def__debug__lib
#define dPrintA(_x_) OutputDebugStringA("[WG][dll]"_x_)
#else
#define dPrintA( _x_ )
#endif