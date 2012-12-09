#if !defined(AFX_MDFTPOCX_H__653359F2_3A2F_417D_BE83_84EDDC8B690A__INCLUDED_)
#define AFX_MDFTPOCX_H__653359F2_3A2F_417D_BE83_84EDDC8B690A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MDFtpOcx.h : main header file for MDFTPOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxApp : See MDFtpOcx.cpp for implementation.

class CMDFtpOcxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDFTPOCX_H__653359F2_3A2F_417D_BE83_84EDDC8B690A__INCLUDED)
