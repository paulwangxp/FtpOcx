#if !defined(AFX_MDFTPOCXPPG_H__486B3C8B_5845_4029_9475_049E65C903BA__INCLUDED_)
#define AFX_MDFTPOCXPPG_H__486B3C8B_5845_4029_9475_049E65C903BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// MDFtpOcxPpg.h : Declaration of the CMDFtpOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxPropPage : See MDFtpOcxPpg.cpp.cpp for implementation.

class CMDFtpOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CMDFtpOcxPropPage)
	DECLARE_OLECREATE_EX(CMDFtpOcxPropPage)

// Constructor
public:
	CMDFtpOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CMDFtpOcxPropPage)
	enum { IDD = IDD_PROPPAGE_MDFTPOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CMDFtpOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDFTPOCXPPG_H__486B3C8B_5845_4029_9475_049E65C903BA__INCLUDED)
