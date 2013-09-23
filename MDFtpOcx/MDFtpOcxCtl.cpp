// MDFtpOcxCtl.cpp : Implementation of the CMDFtpOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "MDFtpOcx.h"
#include "MDFtpOcxCtl.h"
#include "MDFtpOcxPpg.h"
#include "usbhead.h"

#define GET_SPEED_TIMER 1000+201


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMDFtpOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMDFtpOcxCtrl, COleControl)
//{{AFX_MSG_MAP(CMDFtpOcxCtrl)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMDFtpOcxCtrl, COleControl)
//{{AFX_DISPATCH_MAP(CMDFtpOcxCtrl)
DISP_FUNCTION(CMDFtpOcxCtrl, "getVersion", getVersion, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "setParm", setParm, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpLogin", ftpLogin, VT_I2, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpLogout", ftpLogout, VT_I2, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpSetPassive", ftpSetPassive, VT_I2, VTS_BOOL)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpSetFileStepSize", ftpSetFileStepSize, VT_I2, VTS_I2)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpCreateRemoteDir", ftpCreateRemoteDir, VT_I2, VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpDelRemoteDir", ftpDelRemoteDir, VT_I2, VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpGetRemoteDir", ftpGetRemoteDir, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpSetRemoteRoot", ftpSetRemoteRoot, VT_I2, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpSetRemoteDir", ftpSetRemoteDir, VT_I2, VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpUploadFile", ftpUploadFile, VT_I2, VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpGetErrorMsg", ftpGetErrorMsg, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpGetUploadFilePercent", ftpGetUploadFilePercent, VT_I2, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "DelLocalFile", DelLocalFile, VT_I2, VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "getLocalDirFiles", getLocalDirFiles, VT_BSTR, VTS_BSTR VTS_BOOL)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpGetUploadSpeed", ftpGetUploadSpeed, VT_I4, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "ftpGetDownloadSpeed", ftpGetDownloadSpeed, VT_I4, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "getUsbDriver", getUsbDriver, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "getLocalDirFilesNum", getLocalDirFilesNum, VT_I2, VTS_BSTR VTS_BOOL)
DISP_FUNCTION(CMDFtpOcxCtrl, "getLocalFileCreateTime", getLocalFileCreateTime, VT_BSTR, VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "getLocalFirstFile", getLocalFirstFile, VT_BSTR, VTS_BSTR VTS_BOOL)
DISP_FUNCTION(CMDFtpOcxCtrl, "setLocalSaveDir", setLocalSaveDir, VT_I2, VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "selectLocalSaveDir", selectLocalSaveDir, VT_BSTR, VTS_NONE)
DISP_FUNCTION(CMDFtpOcxCtrl, "copyLocalFile", copyLocalFile, VT_I2, VTS_BSTR VTS_BSTR)
DISP_FUNCTION(CMDFtpOcxCtrl, "getLocalFileModifyTime", getLocalFileModifyTime, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION(CMDFtpOcxCtrl, "getFileSize", getFileSize, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CMDFtpOcxCtrl, "ftpDownloadFile", ftpDownloadFile, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CMDFtpOcxCtrl, "ftpGetDownloadFilePercent", ftpGetDownloadFilePercent, VT_I2, VTS_NONE)
	//}}AFX_DISPATCH_MAP
DISP_FUNCTION_ID(CMDFtpOcxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMDFtpOcxCtrl, COleControl)
//{{AFX_EVENT_MAP(CMDFtpOcxCtrl)
// NOTE - ClassWizard will add and remove event map entries
//    DO NOT EDIT what you see in these blocks of generated code !
//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMDFtpOcxCtrl, 1)
PROPPAGEID(CMDFtpOcxPropPage::guid)
END_PROPPAGEIDS(CMDFtpOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMDFtpOcxCtrl, "MDFTPOCX.MDFtpOcxCtrl.1",
					   0x8b2ce00d, 0xfee7, 0x4b4a, 0xb6, 0xa4, 0xbd, 0xcf, 0x5a, 0xb, 0xa6, 0x24)
					   
					   
					   /////////////////////////////////////////////////////////////////////////////
					   // Type library ID and version
					   
					   IMPLEMENT_OLETYPELIB(CMDFtpOcxCtrl, _tlid, _wVerMajor, _wVerMinor)
					   
					   
					   /////////////////////////////////////////////////////////////////////////////
					   // Interface IDs
					   
					   const IID BASED_CODE IID_DMDFtpOcx =
{ 0xefadf3e1, 0x2e3c, 0x4ff5, { 0x9d, 0x14, 0xcf, 0x49, 0xaf, 0xea, 0x58, 0x1 } };
const IID BASED_CODE IID_DMDFtpOcxEvents =
{ 0x7b35740d, 0x8c3d, 0x4dc5, { 0x87, 0xb7, 0x23, 0x5c, 0x86, 0x36, 0x88, 0x3c } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMDFtpOcxOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMDFtpOcxCtrl, IDS_MDFTPOCX, _dwMDFtpOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl::CMDFtpOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMDFtpOcxCtrl

/////////////////////////////////////////////////////////////////////////////
// Interface map for IObjectSafety

BEGIN_INTERFACE_MAP( CMDFtpOcxCtrl, COleControl )
INTERFACE_PART(CMDFtpOcxCtrl, IID_IObjectSafety, ObjSafe)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IObjectSafety member functions

// Delegate AddRef, Release, QueryInterface

ULONG FAR EXPORT CMDFtpOcxCtrl::XObjSafe::AddRef()
{
    METHOD_PROLOGUE(CMDFtpOcxCtrl, ObjSafe)
		return pThis->ExternalAddRef();
}

ULONG FAR EXPORT CMDFtpOcxCtrl::XObjSafe::Release()
{
    METHOD_PROLOGUE(CMDFtpOcxCtrl, ObjSafe)
		return pThis->ExternalRelease();
}

HRESULT FAR EXPORT CMDFtpOcxCtrl::XObjSafe::QueryInterface(
														   REFIID iid, void FAR* FAR* ppvObj)
{
    METHOD_PROLOGUE(CMDFtpOcxCtrl, ObjSafe)
		return (HRESULT)pThis->ExternalQueryInterface(&iid, ppvObj);
}

const DWORD dwSupportedBits =
INTERFACESAFE_FOR_UNTRUSTED_CALLER |
INTERFACESAFE_FOR_UNTRUSTED_DATA;
const DWORD dwNotSupportedBits = ~ dwSupportedBits;

/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::XObjSafe::GetInterfaceSafetyOptions
// Allows container to query what interfaces are safe for what. We're
// optimizing significantly by ignoring which interface the caller is
// asking for.
HRESULT STDMETHODCALLTYPE
CMDFtpOcxCtrl::XObjSafe::GetInterfaceSafetyOptions(
												   REFIID riid,
												   DWORD __RPC_FAR *pdwSupportedOptions,
												   DWORD __RPC_FAR *pdwEnabledOptions)
{
	METHOD_PROLOGUE(CMDFtpOcxCtrl, ObjSafe)
		
		HRESULT retval = ResultFromScode(S_OK);
	
	// does interface exist?
	IUnknown FAR* punkInterface;
	retval = pThis->ExternalQueryInterface(&riid,
		(void * *)&punkInterface);
	if (retval != E_NOINTERFACE) { // interface exists
		punkInterface->Release(); // release it--just checking!
	}
	
	// we support both kinds of safety and have always both set,
	// regardless of interface
	*pdwSupportedOptions = *pdwEnabledOptions = dwSupportedBits;
	
	return retval; // E_NOINTERFACE if QI failed
}

/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::XObjSafe::SetInterfaceSafetyOptions
// Since we're always safe, this is a no-brainer--but we do check to make
// sure the interface requested exists and that the options we're asked to
// set exist and are set on (we don't support unsafe mode).
HRESULT STDMETHODCALLTYPE
CMDFtpOcxCtrl::XObjSafe::SetInterfaceSafetyOptions(
												   REFIID riid,
												   DWORD dwOptionSetMask,
												   DWORD dwEnabledOptions)
{
    METHOD_PROLOGUE(CMDFtpOcxCtrl, ObjSafe)
		
		// does interface exist?
		IUnknown FAR* punkInterface;
	pThis->ExternalQueryInterface(&riid, (void * *)&punkInterface);
	if (punkInterface) { // interface exists
		punkInterface->Release(); // release it--just checking!
	}
	else { // interface doesn't exist
		return ResultFromScode(E_NOINTERFACE);
	}
	
	// can't set bits we don't support
	if (dwOptionSetMask & dwNotSupportedBits) {
		return ResultFromScode(E_FAIL);
	}
	
	// can't set bits we do support to zero
	dwEnabledOptions &= dwSupportedBits;
	// (we already know there are no extra bits in mask )
	if ((dwOptionSetMask & dwEnabledOptions) !=
		dwOptionSetMask) {
		return ResultFromScode(E_FAIL);
	}       
	
	// don't need to change anything since we're always safe
	return ResultFromScode(S_OK);
}
/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrlCtrl::CMDFtpOcxCtrlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMDFtpOcxCtrlCtrl

BOOL CMDFtpOcxCtrl::CMDFtpOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.
	
	if (bRegister)
		return AfxOleRegisterControlClass(
		AfxGetInstanceHandle(),
		m_clsid,
		m_lpszProgID,
		IDS_MDFTPOCX, //这里的工程名为大写
		IDB_MDFTPOCX, //这里的工程名为大写
		afxRegApartmentThreading,
		_dwMDFtpOcxOleMisc,
		_tlid,
		_wVerMajor,
		_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}




char chFirstDriveFromMask(ULONG unitmask)
{
	char i;
	for (i = 0; i < 26; ++i)  
	{
		if (unitmask & 0x1) 
			break;
		unitmask = unitmask >> 1;
	}
    return (i + 'A');
}

BOOL GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc)
{
	STORAGE_PROPERTY_QUERY	Query;	
	DWORD dwOutBytes;				
	BOOL bResult;					
	
	Query.PropertyId = StorageDeviceProperty;
	Query.QueryType = PropertyStandardQuery;
	
	bResult = ::DeviceIoControl(hDevice,			
		IOCTL_STORAGE_QUERY_PROPERTY,			
		&Query, sizeof(STORAGE_PROPERTY_QUERY),	
		pDevDesc, pDevDesc->Size,				
		&dwOutBytes,							
		(LPOVERLAPPED)NULL);					
	
	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl::CMDFtpOcxCtrl - Constructor

CMDFtpOcxCtrl::CMDFtpOcxCtrl()
{
	InitializeIIDs(&IID_DMDFtpOcx, &IID_DMDFtpOcxEvents);
	
	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl::~CMDFtpOcxCtrl - Destructor

CMDFtpOcxCtrl::~CMDFtpOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl::OnDraw - Drawing function

void CMDFtpOcxCtrl::OnDraw(
						   CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl::DoPropExchange - Persistence support

void CMDFtpOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	
	// TODO: Call PX_ functions for each persistent custom property.
	
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl::OnResetState - Reset control to default state

void CMDFtpOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
	
	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl::AboutBox - Display an "About" box to the user

void CMDFtpOcxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MDFTPOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMDFtpOcxCtrl message handlers

BSTR CMDFtpOcxCtrl::getVersion() 
{
	CString strResult;
	// TODO: Add your dispatch handler code here
	
	strResult = "1.0.0.7";
	
	return strResult.AllocSysString();
}

short CMDFtpOcxCtrl::setParm(LPCTSTR strIP, LPCTSTR strUser, LPCTSTR strPwd, short uPort) 
{

	m_ftpclient.setParm( strIP, strUser, strPwd, uPort );
	return 1;
	
}

short CMDFtpOcxCtrl::ftpLogin() 
{
	return m_ftpclient.login();
}

short CMDFtpOcxCtrl::ftpLogout() 
{
	return m_ftpclient.logout();
	
}

short CMDFtpOcxCtrl::ftpSetPassive(BOOL bMode) 
{
	m_ftpclient.setPassive(bMode);
	return 1;
}

short CMDFtpOcxCtrl::ftpSetFileStepSize(short speed) 
{
	m_ftpclient.SetFileStepSize(speed);
	return 1;
}

short CMDFtpOcxCtrl::ftpCreateRemoteDir(LPCTSTR strDir) 
{
	return m_ftpclient.CreateRemoteDir(strDir);
}

short CMDFtpOcxCtrl::ftpDelRemoteDir(LPCTSTR strDir) 
{
	return m_ftpclient.DelRemoteDir(strDir);
	
}

BSTR CMDFtpOcxCtrl::ftpGetRemoteDir() 
{
	CString strResult;
	strResult = m_ftpclient.GetRemoteDir();
	return strResult.AllocSysString();
}

short CMDFtpOcxCtrl::ftpSetRemoteRoot() 
{
	return m_ftpclient.SetRemoteRoot();
	
}

short CMDFtpOcxCtrl::ftpSetRemoteDir(LPCTSTR strDir) 
{
	return m_ftpclient.SetRemoteDir(strDir);
	
}

short CMDFtpOcxCtrl::ftpUploadFile(LPCTSTR strLocalFileName, LPCTSTR strRemoteFileName) 
{
	//KillTimer(m_uploadTimer);
	m_speed = 0;
	m_speed1 = 0;
	//m_uploadTimer = SetTimer( GET_SPEED_TIMER, 1000, NULL );
	return m_ftpclient.UploadFileThread( strRemoteFileName, strLocalFileName);
	
}

long CMDFtpOcxCtrl::ftpGetDownloadSpeed() 
{
	//return m_ftpclient.GetUploadSpeed();
	
	int fix = 1;//解决在有些网页调用时不能启动timer的问题
	if(fix)
	{
		DWORD sp1 = m_speed1;
		m_speed1 = m_ftpclient.GetDownloadSpeed();

		if(m_speed1 - sp1 > 0)
			m_speed = m_speed1 - sp1;
	}


	if( m_speed <=0 )
		return 0;
	

	return m_speed/(1024);
}

short CMDFtpOcxCtrl::ftpGetDownloadFilePercent() 
{
	short s1 = (short)m_ftpclient.GetDownloadFilePercent();
	if(s1 >= 100)
		KillTimer(m_uploadTimer);
	
	return s1;
}


short CMDFtpOcxCtrl::ftpDownloadFile(LPCTSTR strRemoteFileName, LPCTSTR strLocalNewFileName) 
{
	//KillTimer(m_uploadTimer);
	m_speed = 0;
	m_speed1 = 0;
	//m_uploadTimer = SetTimer( GET_SPEED_TIMER, 1000, NULL );
	return m_ftpclient.DownloadFileThread( strRemoteFileName, strLocalNewFileName);
}

BSTR CMDFtpOcxCtrl::ftpGetErrorMsg() 
{
	CString strResult;
	strResult = m_ftpclient.GetErrorMsg();
	return strResult.AllocSysString();
}

short CMDFtpOcxCtrl::ftpGetUploadFilePercent() 
{
	short s1 = (short)m_ftpclient.GetUploadFilePercent();
	if(s1 >= 100)
		KillTimer(m_uploadTimer);
	
	return s1;

}

short CMDFtpOcxCtrl::DelLocalFile(LPCTSTR strFileName) 
{
	return DeleteFile( strFileName );
}

BSTR CMDFtpOcxCtrl::getLocalDirFiles(LPCTSTR strDir, BOOL bAllSubDir) 
{
	CString strResult;
	
	CStringArray fileArray;
	
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.avi");
	
	
	for ( int i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".AVI")) != -1 ||
			fileArray.GetAt(i).Find(_T(".avi")) != -1
			)
			strResult += fileArray.GetAt(i) + "*";
	}

	fileArray.RemoveAll();
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.jpg");
	
	
	for ( i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".JPG")) != -1 ||
			fileArray.GetAt(i).Find(_T(".jpg")) != -1 )
			strResult += fileArray.GetAt(i) + "*";
	}
	
	strResult.TrimRight(_T("*"));
	
	return strResult.AllocSysString();
}


// K/S
long CMDFtpOcxCtrl::ftpGetUploadSpeed() 
{
	//return m_ftpclient.GetUploadSpeed();
	
	int fix = 1;//解决在有些网页调用时不能启动timer的问题
	if(fix)
	{
		DWORD sp1 = m_speed1;
		m_speed1 = m_ftpclient.GetUploadSpeed();

		if(m_speed1 - sp1 > 0)
			m_speed = m_speed1 - sp1;
	}


	if( m_speed <=0 )
		return 0;
	

	return m_speed/(1024);

}




//得到USB盘符名称
BSTR CMDFtpOcxCtrl::getUsbDriver() 
{
	CString strResult;
	ShowDiskInfo(strResult);
	
	return strResult.AllocSysString();
}

int CMDFtpOcxCtrl::ShowDiskInfo(CString &diskDeviceName/*盘符,用#分隔*/)
{
	
	int deviceNum = 0;
	TCHAR szMoveDiskName[100];
	TCHAR	szDrvName[33];
	
	int k = 0;
	DWORD			MaxDriveSet, CurDriveSet;
	DWORD			drive, drivetype;
	TCHAR			szBuf[300];
	HANDLE			hDevice;
	PSTORAGE_DEVICE_DESCRIPTOR pDevDesc;
	
	char* p;
	
	CString str;
	for(k=0; k<26; k++)
		szMoveDiskName[k] = '\0';	
	k = 1;		
	MaxDriveSet = CurDriveSet = 0;
	
	MaxDriveSet = GetLogicalDrives();
	CurDriveSet = MaxDriveSet;
	for ( drive = 0; drive < 32; ++drive )  
	{
		if ( MaxDriveSet & (1 << drive) )  
		{
			DWORD temp = 1<<drive;
			_stprintf( szDrvName, _T("%c:\\"), 'A'+drive );
			if(GetDriveType( szDrvName )== DRIVE_REMOVABLE)
			{
				drivetype = DRVREMOVE;
				
				sprintf(szBuf, "\\\\?\\%c:", 'A'+drive);
				hDevice = CreateFile(szBuf, GENERIC_READ,
					FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
				
				if (hDevice != INVALID_HANDLE_VALUE)
				{
					
					pDevDesc = (PSTORAGE_DEVICE_DESCRIPTOR)new BYTE[sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1];
					
					pDevDesc->Size = sizeof(STORAGE_DEVICE_DESCRIPTOR) + 512 - 1;
					
					if(GetDisksProperty(hDevice, pDevDesc))
					{
						szMoveDiskName[k] = chFirstDriveFromMask(temp);
						diskDeviceName = diskDeviceName + szMoveDiskName[k] + "*";
						szMoveDiskName[0]=k;
						k++;
						//ShowMessage("\r\n找到U盘，名称:\r\n");
						p= (char*)pDevDesc;
						str = (pDevDesc->VendorIdOffset ? &p[pDevDesc->VendorIdOffset]:"(NULL)");
						//ShowMessage(str);
						
						//ShowMessage("\r\n产品ID:\r\n");
						str=(pDevDesc->ProductIdOffset ? &p[pDevDesc->ProductIdOffset]:"(NULL)");
						//ShowMessage(str);
						//ShowMessage("\r\n产品版本:\r\n");
						str = (pDevDesc->ProductRevisionOffset ? &p[pDevDesc->ProductRevisionOffset] : "(NULL)");
						//ShowMessage(str);
						//ShowMessage("\r\n序列号:\r\n");
						str = (pDevDesc->SerialNumberOffset ? &p[pDevDesc->SerialNumberOffset] : "(NULL)");
						//ShowMessage(str);
					}
					
					delete pDevDesc;
					CloseHandle(hDevice);
				}
			}
		}
		
	}
	str.Format("\r\n U盘符:\r\n%s",&szMoveDiskName[1]);
	
	if(szMoveDiskName[0]==0)
	{
		str="\r\n没有U盘\r\n";
		//m_showMessage.Empty();
	}
	
	deviceNum =  szMoveDiskName[0];
	diskDeviceName.TrimRight(_T("*"));
	return deviceNum;
	//ShowMessage(str);
}


// 判断路径是否存在
BOOL CMDFtpOcxCtrl::IsPathExist(LPCTSTR lpszPathName)
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

short CMDFtpOcxCtrl::getLocalDirFilesNum(LPCTSTR strDir, BOOL bAllSubDir) 
{
	CString strResult;
	
	CStringArray fileArray;

	m_totalFileNum = 0;
	
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.avi");
	
	
	for ( int i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".AVI")) != -1 ||
			fileArray.GetAt(i).Find(_T(".avi")) != -1 )
			m_totalFileNum ++;
	}

	fileArray.RemoveAll();
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.jpg");	
	for ( i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".JPG")) != -1 ||
			fileArray.GetAt(i).Find(_T(".jpg")) != -1 )
			m_totalFileNum ++;
	}

	//add by paul 20120901
	fileArray.RemoveAll();
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.mp4");	
	for ( i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".MP4")) != -1 ||
			fileArray.GetAt(i).Find(_T(".mp4")) != -1 )
			m_totalFileNum ++;
	}

	//add by paul 20120901
	fileArray.RemoveAll();
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.wav");	
	for ( i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".WAV")) != -1 ||
			fileArray.GetAt(i).Find(_T(".wav")) != -1 )
			m_totalFileNum ++;
	}
	
	return (short)m_totalFileNum;
}

BSTR CMDFtpOcxCtrl::getLocalFileCreateTime(LPCTSTR fileName1)
{
	CString strResult;
	CFileStatus   Status;
	
	
	if(CFile::GetStatus(fileName1,Status)) 
	{ 
		strResult = Status.m_ctime.Format( "%Y-%m-%d %H:%M:%S"); 
	}
	else
		strResult = "";	
	
	
	return strResult.AllocSysString();
}


BSTR CMDFtpOcxCtrl::getLocalFileModifyTime(LPCTSTR filename1) 
{
	CString strResult;
	CFileStatus   Status;
	
	
	if(CFile::GetStatus(filename1,Status)) 
	{ 
		strResult = Status.m_mtime.Format( "%Y-%m-%d %H:%M:%S"); 
	}
	else
		strResult = "";	
	
	
	return strResult.AllocSysString();
}


BSTR CMDFtpOcxCtrl::getLocalFirstFile(LPCTSTR strDir, BOOL bAllSubDir) 
{
	CString strResult;
	
	CStringArray fileArray;

	
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.avi");
	
	
	for ( int i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".AVI")) != -1 ||
			fileArray.GetAt(i).Find(_T(".avi")) != -1 )
		{
			strResult = fileArray.GetAt(i);
			return strResult.AllocSysString();
		}
	}

	
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.jpg");	
	for ( i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".JPG")) != -1 ||
			fileArray.GetAt(i).Find(_T(".jpg")) != -1 )
		{
			strResult = fileArray.GetAt(i);
			return strResult.AllocSysString();
		}
	}

	//add by paul 20120901
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.mp4");	
	for ( i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".MP4")) != -1 ||
			fileArray.GetAt(i).Find(_T(".mp4")) != -1 )
		{
			strResult = fileArray.GetAt(i);
			return strResult.AllocSysString();
		}
	}

	//add by paul 20120901
	m_ftpclient.GetFileInPath( strDir, fileArray, bAllSubDir, "\\*.wav");	
	for ( i = 0; i < fileArray.GetSize(); i++)
	{
		
		if( fileArray.GetAt(i).Find(_T(".WAV")) != -1 ||
			fileArray.GetAt(i).Find(_T(".wav")) != -1 )
		{
			strResult = fileArray.GetAt(i);
			return strResult.AllocSysString();
		}
	}
	
	return strResult.AllocSysString();
}

short CMDFtpOcxCtrl::setLocalSaveDir(LPCTSTR strLocalDir) 
{
	
	if(  !IsPathExist(strLocalDir) )
		return 0;

	return 1;
}


	

/*****************************************************************
** 函数名:GetPath
** 输 入: 无
** 输 出: CString strPath
**        strPath非空, 表示用户选择的文件夹路径
**        strPath为空, 表示用户点击了“取消”键，取消选择
** 功能描述:显示“选择文件夹”对话框，让用户选择文件夹
****************************************************************/
CString GetSelectPath()
{
	CString strPath = "";
	BROWSEINFO bInfo;
	HWND m_hWnd;
	ZeroMemory(&bInfo, sizeof(bInfo));
	bInfo.hwndOwner = m_hWnd;
	bInfo.lpszTitle = _T("请选择路径: ");
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS;    
	
	LPITEMIDLIST lpDlist; //用来保存返回信息的IDList
	lpDlist = SHBrowseForFolder(&bInfo) ; //显示选择对话框
	if(lpDlist != NULL)  //用户按了确定按钮
	{
		TCHAR chPath[255]; //用来存储路径的字符串
		SHGetPathFromIDList(lpDlist, chPath);//把项目标识列表转化成字符串
		strPath = chPath; //将TCHAR类型的字符串转换为CString类型的字符串
	}
	return strPath;
}


BSTR CMDFtpOcxCtrl::selectLocalSaveDir() 
{
	CString strResult;	

	strResult = GetSelectPath();
	
	return strResult.AllocSysString();
}

short CMDFtpOcxCtrl::copyLocalFile(LPCTSTR strUsbFileName, LPCTSTR strLocalDir) 
{

	SHFILEOPSTRUCT FileOp; 
    ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));
    
    FileOp.fFlags = FOF_NOCONFIRMATION ;
    FileOp.hNameMappings = NULL;
    FileOp.hwnd = NULL;
    FileOp.lpszProgressTitle = NULL;
    FileOp.pFrom = strUsbFileName;
    FileOp.pTo = strLocalDir;
    FileOp.wFunc = FO_COPY;
    
    return SHFileOperation(&FileOp) == 0;
	
}

void CMDFtpOcxCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default


	if(m_uploadTimer == nIDEvent)
	{
		DWORD sp1 = m_speed1;
		m_speed1 = m_ftpclient.GetUploadSpeed();


		if(m_speed1 - sp1 > 0)
			m_speed = m_speed1 - sp1;
	}
	
	COleControl::OnTimer(nIDEvent);
}

long CMDFtpOcxCtrl::getFileSize(LPCTSTR strFileName) 
{
	CFileStatus status;
	CFile::GetStatus(strFileName,status);
	return status.m_size;
}


