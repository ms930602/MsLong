#include "stdafx.h"
#include "ScriptSystem.h"

void CScriptSystem::Initial()
{
	m_pMsLua = new CMsLua();
	pState = new LuaStateOwner(true);
	LuaObject objGlobal = (*pState)->GetGlobals();

	//注册全局函数
	objGlobal.Register("ShowMessage", *m_pMsLua,
		&CMsLua::LUA_ShowMessage);//调试输出字符串函数

	objGlobal.Register("Stop", *m_pMsLua,
		&CMsLua::LUA_Stop);//停止lua脚本的命令函数

	//-------------------------------------------------------------------------------------
	//注册System函数对象///////////////////////////////////////////////////////////////////////
	LuaObject metatable_System = objGlobal.CreateTable("MetaTableSystem");
	metatable_System.SetObject("__index", metatable_System);
	metatable_System.RegisterObjectFunctor("Sleep", &CMsLua::LUA_Sleep);//延迟函数
	metatable_System.RegisterObjectFunctor("GetTickCount", &CMsLua::LUA_GetTickCount);//
	metatable_System.RegisterObjectFunctor("LoadScript", &CMsLua::LUA_LoadScript);//
	metatable_System.RegisterObjectFunctor("MessageBox", &CMsLua::LUA_MessageBox);//

	LuaObject obj_System = (*pState)->BoxPointer(&m_pMsLua);
	obj_System.SetMetatable(metatable_System);
	objGlobal.SetObject("System", obj_System);

	//-------------------------------------------------------------------------------------
	//注册DataBase函数对象///////////////////////////////////////////////////////////////////////
	LuaObject metatable_DataBase = objGlobal.CreateTable("MetaTableDataBase");
	metatable_DataBase.SetObject("__index", metatable_DataBase);

	//...


	LuaObject obj_DataBase = (*pState)->BoxPointer(&m_pMsLua);
	obj_DataBase.SetMetatable(metatable_DataBase);
	objGlobal.SetObject("DataBase", obj_DataBase);
	//-------------------------------------------------------------------------------------
}
