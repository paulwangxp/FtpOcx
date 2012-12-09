// MyFtpClient.h: interface for the CMyFtpClient class.
//
//////////////////////////////////////////////////////////////////////

#include <afxinet.h>


#if !defined(AFX_MYFTPCLIENT_H__A9FC4CC7_20CE_4700_B93F_8381A3E3F5C5__INCLUDED_)
#define AFX_MYFTPCLIENT_H__A9FC4CC7_20CE_4700_B93F_8381A3E3F5C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyFtpClient  
{
public:
	CMyFtpClient();
	CMyFtpClient(CString str_ip, CString str_user, CString str_pwd, UINT port);
	virtual ~CMyFtpClient();

	void setParm(CString str_ip, CString str_user, CString str_pwd, UINT port);
	void setPassive(BOOL state){ m_passive = state;}//设定FTP Passive

	static bool login();//登录
	bool logout();//退出

	//上传文件
	static DWORD WINAPI UploadFile(LPVOID lpParameter);
	bool UploadFileThread(CString str_remoteFileName/*远程文件名，必须是当前路径下的文件*/,
		CString str_LocalFileName/*本地文件名，全路径*/);

	//上传文件列表，参数参考 UploadFile
	bool UploadFileList(CStringList str_remoteFileNameList, CStringList str_LocalFileList);//上传

	//设置远程当前路径
	bool SetRemoteDir(CString str_remoteDir);

	//设置远程当前路径为根目录
	bool SetRemoteRoot(){ return SetRemoteDir(_T("/"));}

	//得到远程当前路径
	CString GetRemoteDir(){  
		m_pConnect->GetCurrentDirectory(m_remoteCurrentDir); 
		return m_remoteCurrentDir; }

	//创建远程目录，不会改变当前远程路径
	bool CreateRemoteDir(CString str_dirName);

	//删除远程目录及目录下的子文件,子文件夹
	bool DelRemoteDir(CString str_dirName);

	//删除远程文件
	bool DelRemoteFile(CString str_FileName);

	//重命名远程文件
	bool RenameRemoteFile(CString str_OldFileName,CString str_NewFileName);


	//下载远程文件
	bool DownloadFile(CString str_remoteFileName/*远程文件名*/, CString str_LocalFileName/*本地文件名*/);

	//下载远程文件列表
	bool DownloadFileList(CStringList str_remoteFileNameList, CStringList str_LocalFileList);

	//得到错误信息
	CString GetErrorMsg();
	
	//上传进度百分比
	DWORD GetUploadFilePercent();

	//上传速度 bytes/s
	DWORD  GetUploadSpeed();

	//下载进度百分比
	DWORD GetDownloadFilePercent();

	//下载速度 bytes/s
	DWORD  GetDownloadSpeed();

	//设定文件每次读写大小,网速越快，值设置越大
	void SetFileStepSize(DWORD dSize){ m_FileLenStep = dSize*1024; }

	// 取得目录下的所有文件
	void GetFileInPath(LPCTSTR lpszPath, CStringArray &arrstrFile, 
		BOOL bFindSubDir/* = FALSE*/,
		LPCTSTR lpszFileExt);

private:
	static BOOL m_passive;
	static CString m_errorMsg;
	static BOOL m_bLogin;
	CString m_remoteCurrentDir;

	static CFile m_CFile;


	static CInternetSession m_session;
	static CFtpConnection * m_pConnect;
	static CInternetFile * m_pRemoteFile;

	static CString m_Ip,m_user,m_pwd;
	static UINT m_port;
	static DWORD m_FileLenStep;

	static DWORD m_TotalUploadSize, m_TotalDownloadSize;
	static DWORD m_CurUploadSize, m_CurDownloadSize;

	DWORD m_UploadSpeed, m_DownloadSpeed;

	void Init();
	static void CloseRemoteFile();
	static void SetErrorMsg();
	
	static CString m_str_remoteFileName, m_str_LocalFileName;
};

#endif // !defined(AFX_MYFTP_H__A9FC4CC7_20CE_4700_B93F_8381A3E3F5C5__INCLUDED_)
