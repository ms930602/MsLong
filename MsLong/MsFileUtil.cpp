#include "stdafx.h"
#include "MsFileUtil.h"

vector<CString>  cstring_substr(IN  CString _Source, IN  CString _Sub, BOOL bAll)
{
	/************************************************************************
	// ���ܣ� ��ȡCString��ȫ��ƥ���_Subָ�����ַ��м���ִ� �������ַ�������
	// ����:  _Source���ַ���Դ
	//        _Erase:  �ָ����ַ���
	************************************************************************/
	vector<CString> _AllSubstr;
	if (_Source.IsEmpty())//�մ�ֱ�ӷ���
		return _AllSubstr;

	//���һ���ַ�����Ϊ_Sub
	CString str = _Source;
	CString str2 = str.Right(1);

	if (str2 != _Sub)
	{
		str = str + _Sub;
		////dbgPrint("�ַ���׷�� %s",_Sub);
	}

	int nStart = 0, nFirst = 0;
	while ((nFirst = str.Find(_Sub, nStart)) != -1)
	{
		CString _substr = str.Mid(nStart, nFirst - nStart);//�и��ַ���
		nStart = nFirst + 1;

		if (!bAll)//���ַ�����Ҫ
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
	m_GameFile_Path = GetFilePathName(_T("��Ϸ·��.txt"));
	m_AccountFile_Path = GetFilePathName(_T("�˺�.txt"));
	m_ServerFile_Path = GetFilePathName(_T("����������.txt"));
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
	int npos = CStrPath.ReverseFind(_T('\\'));//�������
	if (npos != -1)
	{
		if (slash == TRUE)
			CStrPath = CStrPath.Mid(0, npos + 1);//��ȡ��0��ʼ���ַ�������б��
		else
			CStrPath = CStrPath.Mid(0, npos);//��ȡ��0��ʼ���ַ�����Ҫб��
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
	GetPrivateProfileString(_T("·��"), _T("��Ϸ·��"), _T(""), strPathName.GetBuffer(MAX_PATH), MAX_PATH, m_GameFile_Path);
	strPathName.ReleaseBuffer();
	return strPathName;
}

bool CFileUtil::GetKV_ToFileAccountPath(vector<CString> &list)
{
	CStdioFile file(m_AccountFile_Path, CFile::modeRead);
	CString CStr;
	while (file.ReadString(CStr))//���ж��ļ�
	{
		list.push_back(CString(CStr));
	}
	return true;
}

CString CFileUtil::GetFileDirDlg()
{
	/************************************************************************
	��ȡĿ¼�б�Ի���
	************************************************************************/
	BROWSEINFO  bi;
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;
	bi.ulFlags = 0;
	bi.lpfn = NULL;
	bi.iImage = 0;

	//�����ȷ����ť����ֵ,ȡ����ť��ֵ
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
	TCHAR szFilter[] = _T("��Ϸ�ļ�(Game.exe)|*.exe||");
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
	ö��ָ����ǩ�����еļ�ֵ���ı�����
	************************************************************************/
	vector<CString> AllServer;
	CString CStrAppName(_T("ȫ������"));
	TCHAR strKeyNameTemp[1024] = { 0 };//��Ӧÿ��AppName������KeyName�ķ���ֵ
	DWORD dwKeyNameSize = GetPrivateProfileString(CStrAppName, NULL, NULL, strKeyNameTemp, 1024, CString(m_ServerFile_Path));
	TCHAR *pKeyName = new TCHAR[dwKeyNameSize];
	TCHAR strReturnTemp[1024] = { 0 };//����ֵ
	int nKeyNameLen = 0;    //ÿ��KeyName�ĳ���
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
	TCHAR strKeyNameTemp[1024] = { 0 };//��Ӧÿ��AppName������KeyName�ķ���ֵ
	GetPrivateProfileString(serverName, _T("����"), _T(""), strKeyNameTemp, 1024, m_ServerFile_Path);
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
	WritePrivateProfileString(_T("·��"), _T("��Ϸ·��"), GamePath.GetBuffer(), m_GameFile_Path);
	return TRUE;
}