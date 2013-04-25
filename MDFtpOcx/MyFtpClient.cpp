// MyFtpClient.cpp: implementation of the CMyFtpClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyFtpClient.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD CMyFtpClient::m_TotalUploadSize = 0, CMyFtpClient::m_TotalDownloadSize = 0;
DWORD CMyFtpClient::m_CurUploadSize = 0, CMyFtpClient::m_CurDownloadSize = 0;
DWORD CMyFtpClient::m_FileLenStep = 1024*1024;


CFtpConnection * CMyFtpClient::m_pConnect = NULL;
CInternetFile * CMyFtpClient::m_pRemoteFile = NULL;
CInternetSession CMyFtpClient::m_session;

CFile CMyFtpClient::m_CFile;

CString CMyFtpClient::m_str_remoteFileName = "", CMyFtpClient::m_str_LocalFileName = "";
CString CMyFtpClient::m_errorMsg = "";
CString CMyFtpClient::m_Ip = "", CMyFtpClient::m_user = "", CMyFtpClient::m_pwd = "";
BOOL CMyFtpClient::m_passive = FALSE;
BOOL CMyFtpClient::m_bLogin = FALSE;
UINT CMyFtpClient::m_port = 20;


CMyFtpClient::CMyFtpClient()
{
	Init();
}

CMyFtpClient::~CMyFtpClient()
{
	logout();
}

CMyFtpClient::CMyFtpClient(CString str_ip, CString str_user, CString str_pwd, UINT port)
{
	m_Ip = str_ip;
	m_user = str_user;
	m_pwd = str_pwd;
	m_port = port;
	
	Init();
}

void CMyFtpClient::Init()
{
	m_pConnect = NULL;
	m_pRemoteFile = NULL;
	m_FileLenStep = 1024*1024;
	
	
	m_CurUploadSize = m_TotalUploadSize = m_CurDownloadSize = m_TotalDownloadSize = 0;
	
	setPassive(FALSE);
}

void CMyFtpClient::setParm(CString str_ip, CString str_user, CString str_pwd, UINT port)
{

	m_Ip = str_ip;
	m_user = str_user;
	m_pwd = str_pwd;
	m_port = port;
	
}

bool CMyFtpClient::login()
{

	
	try
	{

		if(m_bLogin)
			return true;
		
	
		//m_pConnect = m_session.GetFtpConnection( m_Ip, m_user,
			//m_pwd, m_port, m_passive);
		m_pConnect = m_session.GetFtpConnection( m_Ip, m_user,
			m_pwd, m_port, m_passive);
		if(m_pConnect == NULL)
		{
			SetErrorMsg();
			return false;
		}
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		delete m_pConnect;
		m_pConnect = NULL;
		m_session.Close();
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		delete m_pConnect;
		m_pConnect = NULL;
		m_session.Close();
		return false;
	}
	
	m_bLogin = TRUE;
	return true;
	
}
bool CMyFtpClient::logout()
{
	try
	{
		if(m_pRemoteFile)
		{
			m_pRemoteFile->Close();
			delete m_pRemoteFile;
			m_pRemoteFile = NULL;
		}
		
		if(m_pConnect)
		{
			m_pConnect->Close();
			delete m_pConnect;
			m_pConnect = NULL;
		}

		m_bLogin = FALSE;
		
		//m_session.Close();
		
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		delete m_pRemoteFile;
		m_pRemoteFile = NULL;
		delete m_pConnect;
		m_pConnect = NULL;
		m_bLogin = FALSE;
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		return false;
	}
	
	
	
	m_bLogin = FALSE;
	return true;
}

void CMyFtpClient::CloseRemoteFile()
{
	try
	{
		if(m_pRemoteFile)
		{
			m_pRemoteFile->Close();
			delete m_pRemoteFile;
			m_pRemoteFile = NULL;
		}
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
	}
	catch (...)
	{
		SetErrorMsg();
	}
	
	
}

bool CMyFtpClient::UploadFileThread(CString str_remoteFileName, CString str_LocalFileName)
{

	DWORD      _i;

	m_str_remoteFileName = str_remoteFileName;
	m_str_LocalFileName = str_LocalFileName;

	m_CurUploadSize = m_TotalUploadSize = m_CurDownloadSize = m_TotalDownloadSize = 0;

	::CreateThread (NULL, 0, UploadFile, this, 0,&_i);

	return 1;
}

DWORD CMyFtpClient::UploadFile(LPVOID lpParameter)
{
	
	
	BOOL bOpen = FALSE;

	char *pBuf = NULL;
	
	
	try
	{
		if(m_pConnect == NULL)
		{
			if ( !login() )
			{
				return false;
			}
		}
		
		m_pRemoteFile =  m_pConnect->OpenFile(m_str_remoteFileName, GENERIC_WRITE);
		if(m_pRemoteFile == NULL)
		{
			AfxMessageBox(m_str_remoteFileName + "  :远程文件创建失败");
			return false;
		}
		
		
		bOpen = m_CFile.Open( m_str_LocalFileName , CFile::modeRead );
		if(!bOpen)
		{
			AfxMessageBox(m_str_LocalFileName + "  :本地文件打开失败");
			return false;
		}

		m_TotalUploadSize =  m_CFile.GetLength();

		
		m_FileLenStep = m_FileLenStep > m_TotalUploadSize ? m_TotalUploadSize : m_FileLenStep;
		
		DWORD dwRead = m_FileLenStep;

		pBuf = new char[m_FileLenStep+1];
		memset(pBuf, 0x00, m_FileLenStep+1);
		
		while( (dwRead = m_CFile.Read(pBuf, m_FileLenStep)) > 0 )
		{
			m_pRemoteFile->Write( pBuf, dwRead );
			
			m_CurUploadSize += dwRead;
		}
		
		delete pBuf;		
		m_CFile.Close();
		
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		
		delete pBuf;
		if(bOpen)
			m_CFile.Close();
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		delete pBuf;
		if(bOpen)
			m_CFile.Close();
		
		return false;
	}
	
	CloseRemoteFile();
	
	return true;
	
	
}
bool CMyFtpClient::UploadFileList(CStringList str_remoteFileNameList, CStringList str_LocalFileList)
{
	for(int i = 0; i< str_remoteFileNameList.GetCount(); i++)
	{
		CString remoteFile = str_remoteFileNameList.GetAt(str_remoteFileNameList.FindIndex(i));
		CString localFile = str_LocalFileList.GetAt(str_LocalFileList.FindIndex(i));

		UploadFileThread( remoteFile, localFile );
	}

	return true;
}
bool CMyFtpClient::CreateRemoteDir(CString str_dirName)
{
	try
	{
		if(m_pConnect == NULL)
			return false;
		
		if ( m_pConnect->CreateDirectory(str_dirName) <= 0 )
			return false;

		return SetRemoteDir(str_dirName);
		

	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		return false;
	}
	
	
	
	return true;
}

bool CMyFtpClient::SetRemoteDir(CString str_remoteDir)
{ 
	try
	{
		if(m_pConnect == NULL)
			return false;

		
		if( m_pConnect->SetCurrentDirectory( str_remoteDir) <= 0 )
				return false;

		m_pConnect->GetCurrentDirectory(m_remoteCurrentDir);
		
		
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		return false;
	}
	
	return true;
	
}

bool CMyFtpClient::DelRemoteDir(CString str_remoteDir/*全路径或当前路径下的文件夹*/)
{ 

_RECALL:
	CFtpFileFind ftpFind(m_pConnect);


	try
	{
		if(m_pConnect == NULL)
			return false;
		
		if(str_remoteDir.Left(1) != "/")//不是全路径
		{
			CString strPath;
			m_pConnect->GetCurrentDirectory(strPath);
			str_remoteDir = strPath + _T("/") + str_remoteDir + _T("/*");
		}

		SetRemoteDir(str_remoteDir);
			
		
		
		
		BOOL bContinue = ftpFind.FindFile(str_remoteDir);


		if (!bContinue)//是个空目录，删除
		{
			SetRemoteDir("..");//返回上层
			m_pConnect->RemoveDirectory(str_remoteDir);//删除
			goto _QUIT;
		}
		

		
		bContinue = ftpFind.FindFile();
		if (!bContinue)//文件未找到
		{
			goto _QUIT;
		}


		do 
		{
			bContinue =  ftpFind.FindNextFile();

			if (ftpFind.IsDirectory())
			{
				CString strPath = ftpFind.GetFilePath();
				ftpFind.Close();

				DelRemoteDir( strPath );//递归调用
				SetRemoteDir("..");//返回上层
				goto _RECALL;
			}
			else
			{				
				DelRemoteFile(ftpFind.GetFileName());
			}
		}
		while (bContinue);
		
		
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		goto _FAIL;
	}
	catch (...)
	{
		SetErrorMsg();
		goto _FAIL;
	}
	

_QUIT:
	ftpFind.Close();
	return true;
	
_FAIL:

	ftpFind.Close();
	return false;
}

bool CMyFtpClient::DelRemoteFile(CString str_FileName)
{ 
	try
	{
		if(m_pConnect == NULL)
			return false;
		
		if( m_pConnect->Remove( str_FileName ) <= 0 )
			return false;
		
		
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		return false;
	}
	
	return true;
	
}

bool CMyFtpClient::RenameRemoteFile(CString str_OldFileName,CString str_NewFileName)
{ 
	try
	{
		if(m_pConnect == NULL)
			return false;
		
		if( m_pConnect->Rename( str_OldFileName,  str_NewFileName ) <= 0 )
			return false;
		
		
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		return false;
	}
	
	return true;
	
}

bool CMyFtpClient::DownloadFile(CString str_remoteFileName, CString str_LocalFileName)
{
	LPBYTE pBuffer = new BYTE[m_FileLenStep+1];
	memset(pBuffer, 0, m_FileLenStep+1);
	
	CFile wrireFile;
	
	try
	{
		if(m_pConnect == NULL)
		{
			if ( !login() )
			{
				return false;
			}
		}
		
		if( !wrireFile.Open(str_LocalFileName, CFile::modeCreate|CFile::modeWrite|CFile::typeBinary))
		{
			AfxMessageBox(str_LocalFileName + "  :文件创建失败");
			
			CloseRemoteFile();
			return false;
		}
		
		
		m_pRemoteFile =  m_pConnect->OpenFile(str_remoteFileName, GENERIC_READ);
		if(m_pRemoteFile == NULL)
		{
			AfxMessageBox(str_remoteFileName + "  :远程文件打开失败");
			return false;
		}
		
		
		
		
		
		m_TotalDownloadSize = m_pRemoteFile->GetLength();//远程文件总长度
		
		m_FileLenStep = m_FileLenStep > m_TotalDownloadSize ? m_TotalDownloadSize : m_FileLenStep;
		
		
		
		DWORD dRead = 0;
		while( (dRead = m_pRemoteFile->Read( pBuffer, m_FileLenStep)) > 0  ) 
		{
			wrireFile.Write( pBuffer, dRead );
			
			m_CurDownloadSize += dRead;
		}
		
		wrireFile.Close();
		
		
	}
	catch(CInternetException *pEx)
	{
		pEx->GetErrorMessage( m_errorMsg.GetBuffer(0), 1024 );
		pEx->Delete();
		
		wrireFile.Close();
		return false;
	}
	catch (...)
	{
		SetErrorMsg();
		
		wrireFile.Close();
		return false;
	}
	
	
	
	
	delete pBuffer;
	CloseRemoteFile();
	
	
	return true;
	
	
	
	
	
}
bool CMyFtpClient::DownloadFileList(CStringList str_remoteFileNameList, CStringList str_LocalFileList)
{
	for(int i = 0; i< str_remoteFileNameList.GetCount(); i++)
	{
		CString remoteFile = str_remoteFileNameList.GetAt(str_remoteFileNameList.FindIndex(i));
		CString localFile = str_LocalFileList.GetAt(str_LocalFileList.FindIndex(i));

		DownloadFile( remoteFile, localFile );
	}

	return true;
}

DWORD CMyFtpClient::GetUploadFilePercent()
{
	if(m_TotalUploadSize <=0)
		return 0;

	
	double d1,d2,d3;
	d2 = m_CurUploadSize;
	d3 = m_TotalUploadSize;
	d1 = d2  / d3;

	return d1 * 100 ;	
}

DWORD CMyFtpClient::GetDownloadFilePercent()
{
	return m_CurDownloadSize * 100 / m_TotalDownloadSize;
}

CString CMyFtpClient::GetErrorMsg()
{
	return "";
	return m_errorMsg;
}

void CMyFtpClient::SetErrorMsg()
{
	return;

	LPVOID lpMsgBuf; 
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS, 
		NULL, 
		GetLastError(), 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language 
		(LPTSTR) &lpMsgBuf, 
		0, 
		NULL 
		); 
	
	m_errorMsg.Format("%s",lpMsgBuf);
	
	LocalFree(   lpMsgBuf   );
}


// 判断路径是否存在
BOOL IsPathExist(LPCTSTR lpszPathName)
{
	CString strTemp;
	if(GetCurrentDirectory(MAX_PATH,strTemp.GetBuffer(MAX_PATH)) == 0 )
	{
		strTemp.ReleaseBuffer();
		return FALSE;
	}
	strTemp.ReleaseBuffer(MAX_PATH);
	BOOL bRes = SetCurrentDirectory(lpszPathName);
	SetCurrentDirectory(strTemp.GetBuffer(MAX_PATH));
	strTemp.ReleaseBuffer(MAX_PATH);
	return bRes;
}

// 判断是否是路径
BOOL IsDirPath(LPCTSTR lpszPathName)
{
	HANDLE hFindFile;
	WIN32_FIND_DATA stuFindData;

	CString strName(lpszPathName);
	strName  += _T("\\*");
	hFindFile = FindFirstFile(strName, &stuFindData);
	if (hFindFile == INVALID_HANDLE_VALUE)	return FALSE;
	else
	{
		FindClose(hFindFile);
		return TRUE;
	}
}

// 取得目录下的所有文件
void CMyFtpClient::GetFileInPath(LPCTSTR lpszPath, CStringArray &arrstrFile, 
								 BOOL bFindSubDir/* = FALSE*/, LPCTSTR lpszFileExt)
{
	if (!IsPathExist(lpszPath))	return ;

	arrstrFile.RemoveAll();

	WIN32_FIND_DATA		stuFindData;
	HANDLE				hFindFile;
	CString strName(lpszPath);

	//modify by paul strName  += _T("\\*");
	//strName  += _T(lpszFileExt);
	strName  += _T("\\*");

	hFindFile = FindFirstFile(strName, &stuFindData);

	if (hFindFile == INVALID_HANDLE_VALUE)	return ;
	else
	{
		strName = stuFindData.cFileName;
		if (strName.CompareNoCase(_T(".")) != 0 && strName.CompareNoCase(_T("..")) != 0)
		{
			strName  = lpszPath;
			strName += _T("\\");
			strName += stuFindData.cFileName;
			if (!IsDirPath(strName) && strName.CompareNoCase(_T(lpszFileExt)) != 0 )
				arrstrFile.Add(strName);
			else if (bFindSubDir)
			{
				CStringArray arrstrTemp;
				GetFileInPath(strName, arrstrTemp, bFindSubDir,lpszFileExt);
				for (int i=0; i<arrstrTemp.GetSize() && strName.CompareNoCase(_T(lpszFileExt)) != 0; i++)
					arrstrFile.Add(arrstrTemp[i]);
				arrstrTemp.RemoveAll();
			}
		}
		while (FindNextFile(hFindFile, &stuFindData)) 
		{
			strName = stuFindData.cFileName;
			if (strName.CompareNoCase(_T(".")) != 0 && strName.CompareNoCase(_T("..")) != 0)
			{
				strName  = lpszPath;
				strName += _T("\\");
				strName += stuFindData.cFileName;
				if (!IsDirPath(strName) && strName.CompareNoCase(_T(lpszFileExt)) != 0 )
					arrstrFile.Add(strName);
				else if (bFindSubDir)
				{
					CStringArray arrstrTemp;
					GetFileInPath(strName, arrstrTemp, bFindSubDir,lpszFileExt);
					for (int i=0; i<arrstrTemp.GetSize() && strName.CompareNoCase(_T(lpszFileExt)) != 0; i++)
						arrstrFile.Add(arrstrTemp[i]);
					arrstrTemp.RemoveAll();
				}
			}
		}
		FindClose(hFindFile);
	}


}

//上传速度 bytes/s
DWORD  CMyFtpClient::GetUploadSpeed()
{
	/*
	m_UploadSpeed = m_CurUploadSize;
	Sleep(1000);
	m_UploadSpeed = m_CurUploadSize - m_UploadSpeed;
	return m_UploadSpeed;
	*/

	return m_CurUploadSize;
}

//下载速度 bytes/s
DWORD  CMyFtpClient::GetDownloadSpeed()
{
	/*
	m_DownloadSpeed = m_CurDownloadSize;
	Sleep(1000);
	m_DownloadSpeed = m_CurDownloadSize - m_DownloadSpeed;
	return m_DownloadSpeed;
	*/

	return m_CurDownloadSize;
}