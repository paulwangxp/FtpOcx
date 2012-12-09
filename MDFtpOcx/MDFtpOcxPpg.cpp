// MDFtpOcxPpg.cpp : Implementation of the CMDFtpOcxPropPage property page class.

#include "stdafx.h"
#include "MDFtpOcx.h"
#include "MDFtpOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMDFtpOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMDFtpOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CMDFtpOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMDFtpOcxPropPage, "MDFTPOCX.MDFtpOcxPropPage.1",
	0xfa60b320, 0x1d91, 0x4d4d, 0xb1, 0xe7, 0x48, 0x55, 0x35, 0x3e, 0x15, 0x75)


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxPropPage::CMDFtpOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CMDFtpOcxPropPage

BOOL CMDFtpOcxPropPage::CMDFtpOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_MDFTPOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxPropPage::CMDFtpOcxPropPage - Constructor

CMDFtpOcxPropPage::CMDFtpOcxPropPage() :
	COlePropertyPage(IDD, IDS_MDFTPOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CMDFtpOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxPropPage::DoDataExchange - Moves data between page and properties

void CMDFtpOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CMDFtpOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxPropPage message handlers
