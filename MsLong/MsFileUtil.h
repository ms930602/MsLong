#pragma once
class CFileUtil
{
public:
	CFileUtil();
	~CFileUtil();

private:
	//获取本进程路径 true = 后面带 /
	CString GetCurpath(BOOL slash);
	CString GetFilePathName(CString strFileName);
public:
	//从游戏路径.txt文件中获取游戏路径
	CString GetKV_ToFileGamePath();
	//从账号文件中获取所有账号信息
	bool GetKV_ToFileAccountPath(vector<CString> &list);
	//打开文件夹选择器选择文件夹 获取路径
	CString GetFileDirDlg();
	//打开文件选择器选择文夹 获取路径
	CString GetFileDlg();
	//获取大区信息
	vector<CString> GetBigServer();
	//获取小区信息
	vector<CString> GetSmallServer(CString serverName);

	//保存账号信息 1 为成功   0为保存失败  2为文件地址不存在
	int SaveAccountFile(CString txt);
	//保存游戏路径 1 为成功   0为保存失败 
	int SaveGamePath(CString GamePath);
private:
	CString m_GameFile_Path;
	CString m_AccountFile_Path;
	CString m_ServerFile_Path;
};