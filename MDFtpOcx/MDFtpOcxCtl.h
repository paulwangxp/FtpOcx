#if !defined(AFX_MDFTPOCXCTL_H__4417C4CF_F6AE_4125_A80D_326C30A05845__INCLUDED_)
#define AFX_MDFTPOCXCTL_H__4417C4CF_F6AE_4125_A80D_326C30A05845__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <objsafe.h>
#include "MyFtpClient.h"

// MDFtpOcxCtl.h : Declaration of the CMDFtpOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl : See MDFtpOcxCtl.cpp for implementation.

class CMDFtpOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CMDFtpOcxCtrl)

	DECLARE_INTERFACE_MAP()
		
		BEGIN_INTERFACE_PART(ObjSafe, IObjectSafety)
		STDMETHOD_(HRESULT, GetInterfaceSafetyOptions) (
		REFIID riid,
		DWORD __RPC_FAR *pdwSupportedOptions,
		DWORD __RPC_FAR *pdwEnabledOptions
		);
	
	STDMETHOD_(HRESULT, SetInterfaceSafetyOptions) (
		REFIID riid,
		DWORD dwOptionSetMask,
		DWORD dwEnabledOptions
		);
	END_INTERFACE_PART(ObjSafe);

// Constructor
public:
	CMDFtpOcxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDFtpOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CMDFtpOcxCtrl();

	DECLARE_OLECREATE_EX(CMDFtpOcxCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CMDFtpOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CMDFtpOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CMDFtpOcxCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CMDFtpOcxCtrl)
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CMDFtpOcxCtrl)
	afx_msg BSTR getVersion();
	afx_msg short setParm(LPCTSTR strIP, LPCTSTR strUser, LPCTSTR strPwd, short uPort);
	afx_msg short ftpLogin();
	afx_msg short ftpLogout();
	afx_msg short ftpSetPassive(BOOL bMode);
	afx_msg short ftpSetFileStepSize(short speed);
	afx_msg short ftpCreateRemoteDir(LPCTSTR strDir);
	afx_msg short ftpDelRemoteDir(LPCTSTR strDir);
	afx_msg BSTR ftpGetRemoteDir();
	afx_msg short ftpSetRemoteRoot();
	afx_msg short ftpSetRemoteDir(LPCTSTR strDir);
	afx_msg short ftpUploadFile(LPCTSTR strLocalFileName, LPCTSTR strRemoteFileName);
	afx_msg BSTR ftpGetErrorMsg();
	afx_msg short ftpGetUploadFilePercent();
	afx_msg short DelLocalFile(LPCTSTR strFileName);
	afx_msg BSTR getLocalDirFiles(LPCTSTR strDir, BOOL bAllSubDir);
	afx_msg long ftpGetUploadSpeed();
	afx_msg long ftpGetDownloadSpeed();
	afx_msg BSTR getUsbDriver();
	afx_msg short getLocalDirFilesNum(LPCTSTR strDir, BOOL  bAllSubDir);
	afx_msg BSTR getLocalFileCreateTime(LPCTSTR fileName1);
	afx_msg BSTR getLocalFirstFile(LPCTSTR strDir, BOOL  bAllSubDir);
	afx_msg short setLocalSaveDir(LPCTSTR strLocalDir);
	afx_msg BSTR selectLocalSaveDir();
	afx_msg short copyLocalFile(LPCTSTR strUsbFileName, LPCTSTR strLocalDir);
	afx_msg BSTR getLocalFileModifyTime(LPCTSTR filename1);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CMDFtpOcxCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	int ShowDiskInfo(CString &diskDeviceName/*ÅÌ·û,ÓÃ#·Ö¸ô*/);
	enum {
	//{{AFX_DISP_ID(CMDFtpOcxCtrl)
	dispidGetVersion = 1L,
	dispidSetParm = 2L,
	dispidFtpLogin = 3L,
	dispidFtpLogout = 4L,
	dispidFtpSetPassive = 5L,
	dispidFtpSetFileStepSize = 6L,
	dispidFtpCreateRemoteDir = 7L,
	dispidFtpDelRemoteDir = 8L,
	dispidFtpGetRemoteDir = 9L,
	dispidFtpSetRemoteRoot = 10L,
	dispidFtpSetRemoteDir = 11L,
	dispidFtpUploadFile = 12L,
	dispidFtpGetErrorMsg = 13L,
	dispidFtpGetUploadFilePercent = 14L,
	dispidDelLocalFile = 15L,
	dispidGetLocalDirFiles = 16L,
	dispidFtpGetUploadSpeed = 17L,
	dispidFtpGetDownloadSpeed = 18L,
	dispidGetUsbDriver = 19L,
	dispidGetLocalDirFilesNum = 20L,
	dispidGetLocalFileCreateTime = 21L,
	dispidGetLocalFirstFile = 22L,
	dispidSetLocalSaveDir = 23L,
	dispidSelectLocalSaveDir = 24L,
	dispidCopyLocalFile = 25L,
	dispidGetLocalFileModifyTime = 26L,
	//}}AFX_DISP_ID
	};
private:
	
	CMyFtpClient m_ftpclient;
	DWORD m_totalFileNum;
	CString m_strLocalDir;
	UINT m_uploadTimer;
	DWORD m_speed, m_speed1;


	BOOL IsPathExist(LPCTSTR lpszPathName);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDFTPOCXCTL_H__4417C4CF_F6AE_4125_A80D_326C30A05845__INCLUDED)
