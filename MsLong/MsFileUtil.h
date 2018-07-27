#pragma once
class CFileUtil
{
public:
	CFileUtil();
	~CFileUtil();

private:
	//��ȡ������·�� true = ����� /
	CString GetCurpath(BOOL slash);
	CString GetFilePathName(CString strFileName);
public:
	//����Ϸ·��.txt�ļ��л�ȡ��Ϸ·��
	CString GetKV_ToFileGamePath();
	//���˺��ļ��л�ȡ�����˺���Ϣ
	bool GetKV_ToFileAccountPath(vector<CString> &list);
	//���ļ���ѡ����ѡ���ļ��� ��ȡ·��
	CString GetFileDirDlg();
	//���ļ�ѡ����ѡ���ļ� ��ȡ·��
	CString GetFileDlg();
	//��ȡ������Ϣ
	vector<CString> GetBigServer();
	//��ȡС����Ϣ
	vector<CString> GetSmallServer(CString serverName);

	//�����˺���Ϣ 1 Ϊ�ɹ�   0Ϊ����ʧ��  2Ϊ�ļ���ַ������
	int SaveAccountFile(CString txt);
	//������Ϸ·�� 1 Ϊ�ɹ�   0Ϊ����ʧ�� 
	int SaveGamePath(CString GamePath);
private:
	CString m_GameFile_Path;
	CString m_AccountFile_Path;
	CString m_ServerFile_Path;
};