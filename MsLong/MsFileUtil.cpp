#include "stdafx.h"
#include "MsFileUtil.h"

vector<CString>  cstring_substr(IN  CString _Source, IN  CString _Sub, BOOL bAll)
{
	/************************************************************************
	// 功能： 提取CString中全部匹配的_Sub指定的字符中间的字串 返回子字符串容器
	// 参数:  _Source：字符串源
	//        _Erase:  分隔符字符串
	************************************************************************/
	vector<CString> _AllSubstr;
	if (_Source.IsEmpty())//空串直接返回
		return _AllSubstr;

	//最后一个字符设置为_Sub
	CString str = _Source;
	CString str2 = str.Right(1);

	if (str2 != _Sub)
	{
		str = str + _Sub;
		////dbgPrint("字符串追加 %s",_Sub);
	}

	int nStart = 0, nFirst = 0;
	while ((nFirst = str.Find(_Sub, nStart)) != -1)
	{
		CString _substr = str.Mid(nStart, nFirst - nStart);//切割字符串
		nStart = nFirst + 1;

		if (!bAll)//空字符串不要
		{
			if (_substr.IsEmpty())
			{
				continue;
			}
		}

		////dbgPrint(_T("%s \n"), _substr);
		_AllSubstr.push_back(_substr);
	}

	return _AllSubstr;
}

CFileUtil::CFileUtil()
{
	m_GameFile_Path = GetFilePathName(_T("游戏路径.txt"));
	m_AccountFile_Path = GetFilePathName(_T("账号.txt"));
	m_ServerFile_Path = GetFilePathName(_T("服务器配置.txt"));
}

CFileUtil::~CFileUtil()
{
}

CString CFileUtil::GetCurpath(BOOL slash)
{
	TCHAR lpBuffer[MAX_PATH] = { 0 };
	if (GetModuleFileName(
		NULL,
		lpBuffer,
		MAX_PATH
	) == NULL)
	{
		return CString();
	}

	CString CStrPath(lpBuffer);
	int npos = CStrPath.ReverseFind(_T('\\'));//逆向查找
	if (npos != -1)
	{
		if (slash == TRUE)
			CStrPath = CStrPath.Mid(0, npos + 1);//截取从0开始的字符串保留斜杠
		else
			CStrPath = CStrPath.Mid(0, npos);//截取从0开始的字符串不要斜杠
	}

	return CStrPath;
}

CString CFileUtil::GetFilePathName(CString strFileName)
{
	auto strPath = GetCurpath(TRUE);
	strPath += "\\binx\\";
	strPath += strFileName;

	return strPath;
}

CString CFileUtil::GetKV_ToFileGamePath()
{
	CString	strPathName;
	TRACE(m_GameFile_Path);
	GetPrivateProfileString(_T("路径"), _T("游戏路径"), _T(""), strPathName.GetBuffer(MAX_PATH), MAX_PATH, m_GameFile_Path);
	strPathName.ReleaseBuffer();
	return strPathName;
}

bool CFileUtil::GetKV_ToFileAccountPath(vector<CString> &list)
{
	CStdioFile file(m_AccountFile_Path, CFile::modeRead);
	CString CStr;
	while (file.ReadString(CStr))//按行读文件
	{
		list.push_back(CString(CStr));
	}
	return true;
}

CString CFileUtil::GetFileDirDlg()
{
	/************************************************************************
	获取目录列表对话框
	************************************************************************/
	BROWSEINFO  bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.iImage = 0;

	//这里点确定按钮非零值,取消按钮零值
	LPCITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (!pidl)
		return FALSE;

	TCHAR  szDisplayName[255] = { 0 };
	if (SHGetPathFromIDList(pidl, szDisplayName))
	{
		CString _Path(szDisplayName);
		_Path += _T("\\");
		return _Path;
	}

	return CString();
}

CString CFileUtil::GetFileDlg()
{
	CString CStrScript;
	TCHAR szFilter[] = _T("游戏文件(Game.exe)|*.exe||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT, szFilter);
	if (dlg.DoModal() == IDOK)
	{
		CStrScript = dlg.GetPathName();
		if (!CStrScript.IsEmpty()) {
			return CStrScript;
		}
	}
	return CString();
}

vector<CString> CFileUtil::GetBigServer()
{
	/************************************************************************
	枚举指定标签下所有的键值的文本内容
	************************************************************************/
	vector<CString> AllServer;
	CString CStrAppName(_T("全部大区"));
	TCHAR strKeyNameTemp[1024] = { 0 };//对应每个AppName的所有KeyName的返回值
	DWORD dwKeyNameSize = GetPrivateProfileString(CStrAppName, NULL, NULL, strKeyNameTemp, 1024, CString(m_ServerFile_Path));
	TCHAR *pKeyName = new TCHAR[dwKeyNameSize];
	TCHAR strReturnTemp[1024] = { 0 };//返回值
	int nKeyNameLen = 0;    //每个KeyName的长度
	for (UINT j = 0; j < dwKeyNameSize; j++)
	{
		pKeyName[nKeyNameLen++] = strKeyNameTemp[j];
		if (strKeyNameTemp[j] == _T('\0'))
		{
			if (GetPrivateProfileString(CStrAppName, pKeyName, NULL, strReturnTemp, 1024, CString(m_ServerFile_Path)))
			{
				memset(pKeyName, 0, dwKeyNameSize);
			}
			nKeyNameLen = 0;
			AllServer.push_back(strReturnTemp);
		}
	}
	delete[]pKeyName;

	return AllServer;
}

vector<CString> CFileUtil::GetSmallServer(CString serverName)
{
	TCHAR strKeyNameTemp[1024] = { 0 };//对应每个AppName的所有KeyName的返回值
	GetPrivateProfileString(serverName, _T("名称"), _T(""), strKeyNameTemp, 1024, m_ServerFile_Path);
	vector<CString> AllName = cstring_substr(strKeyNameTemp, _T(","), 1);

	return AllName;
}

int CFileUtil::SaveAccountFile(CString txt)
{
	CStdioFile outFile(m_AccountFile_Path, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite | CFile::typeText);
	outFile.SetLength(0);
	outFile.WriteString(txt);
	outFile.Close();

	return TRUE;
}

int CFileUtil::SaveGamePath(CString GamePath)
{
	WritePrivateProfileString(_T("路径"), _T("游戏路径"), GamePath.GetBuffer(), m_GameFile_Path);
	return TRUE;
}