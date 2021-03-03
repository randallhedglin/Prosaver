// Copyright 2006 WaveBreak Software

// main.cpp -- system core

// includes //

#include"main.h"

// message maps //

BEGIN_MESSAGE_MAP(CMainApp,CWinApp)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtButton,CButton)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtStatic,CStatic)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtEdit,CEdit)
	ON_CONTROL_REFLECT(EN_CHANGE,   OnTextChange)
	ON_CONTROL_REFLECT(EN_KILLFOCUS,OnFocusLost)
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtComboBox,CComboBox)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtRichEditCtrl,CRichEditCtrl)
	ON_WM_CONTEXTMENU()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtFileDialog,CFileDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtHeaderCtrl,CHeaderCtrl)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtMessageBox,CWnd)
	ON_WM_CREATE()
    ON_MESSAGE(WM_INITDIALOG,OnMsgBoxInit)
    ON_MESSAGE(WM_DESTROY,   OnMsgBoxClose)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtHotKeyCtrl,CHotKeyCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtSpinCtrl,CSpinButtonCtrl)
	ON_WM_CONTEXTMENU()
	ON_WM_LBUTTONUP()
	ON_WM_STYLECHANGING()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtSliderCtrl,CSliderCtrl)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// main application instance //

// let's get this show on the road!
CMainApp g_MainApp;

// globals //

// handle to application window
HWND g_hWnd=(HWND)INVALID_HANDLE_VALUE;
// message string
char g_lpMsg[LONG_MSG_SIZE];
char* g_lpTTMsg=NULL;
char* g_lpErrorMsg=NULL;
char* g_lpLongMsg=NULL;
char* g_lpLongTTMsg=NULL;
// com memory allocator
IMalloc* g_lpCoMalloc=NULL;
// resource counters
DWORD g_dwNumCOMRes=0;
DWORD g_dwNumWinRes=0;
DWORD g_dwNumMemRes=0;
DWORD g_dwNumClassRes=0;
// popup menus
CMenu* g_lpPopupMenu=NULL;
CMenu* g_lpPopupSubmenu=NULL;
// highlight window handle
HWND g_hFlashWnd=(HWND)INVALID_HANDLE_VALUE;
DWORD g_dwFlashCnt=0;
UINT g_nFlashId=NULL;
#ifdef DEBUG_MODE
// message locking flags
BOOL _g_bMsgLocked=FALSE;
BOOL _g_bLongMsgLocked=FALSE;
BOOL _g_bTTMsgLocked=FALSE;
BOOL _g_bLongTTMsgLocked=FALSE;
BOOL _g_bErrorMsgLocked=FALSE;
#endif
// focus swap data
HWND g_hFSwapWnd1=(HWND)INVALID_HANDLE_VALUE;
HWND g_hFSwapWnd2=(HWND)INVALID_HANDLE_VALUE;
DWORD g_dwFSwapCnt=0;
UINT g_nFSwapId=0;
// shell link interfaces
IShellLink* g_lpShellLink=NULL;
IPersistFile* g_lpShellLinkPF=NULL;
// wait cursor counter
int g_nWaitCursorCnt=0;
// anti-hacking values
DWORD g_dwAHVal1=NULL;
DWORD g_dwAHVal2=NULL;
DWORD g_dwAHVal3=NULL;
DWORD g_dwAHVal4=NULL;
#ifdef SHAREWARE_MODE
// nybble codes
char g_lpNybCode[64];
#endif
// duplication mutex
HANDLE g_hMutex=INVALID_HANDLE_VALUE;
// error log
CErrorLog* g_lpErrorLog=NULL;
// parent window
HWND g_hParentWnd=(HWND)INVALID_HANDLE_VALUE;

// functions //

// DisplayErrorMessage()

void DisplayErrorMessage(LPSTR lpError,
						 LPSTR lpSolution,
						 BOOL bExtInfo,
						 BOOL bFatal)
{
	// recursion counter
	static int nRecur=0;

	// add error message
	strcpy(g_lpErrorMsg,
		   (lpError ? lpError : "Undefined error."));

	// check solution string
	if(lpSolution)
	{
		// add line break
		strcat(g_lpErrorMsg,"\n\n");

		// add possible solutions
		strcat(g_lpErrorMsg,lpSolution);
	}

	// check last error
	if(GetLastError()==ERROR_SUCCESS)
	{
		// reset extended info flag
		bExtInfo=FALSE;
	}
	
	// check extended info flag
	if(bExtInfo)
	{
		// add extended info
		strcat(g_lpErrorMsg,"\n\n");

		// add system message
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
					  NULL,
					  GetLastError(),
					  NULL,
					  g_lpErrorMsg+strlen(g_lpErrorMsg),
					  (_MAX_PATH-1)-strlen(g_lpErrorMsg),
					  NULL);
	}

	// check error log
	if(LoggingErrors)
	{
		// check recursion counter
		if(nRecur==0)
		{
			// increment counter
			nRecur++;

			// add string
			g_lpErrorLog->AddString((bFatal ? "FATAL ERROR" : "ERROR"),
									g_lpErrorMsg);

			// dump error log
			g_lpErrorLog->Dump();

			// decrement counter
			nRecur--;
		}
	}
	else
	{
		// display message box
		DisplayMessageBox(g_hWnd,
						  g_lpErrorMsg,
						  (LPSTR)ApplicationName(),
						  MB_OK|(bFatal ? MB_ICONSTOP : MB_ICONWARNING));
	}
}

// DisplayNEErrorMessage()

void DisplayNEErrorMessage(LPSTR lpError,
						   LPSTR lpSolution,
						   BOOL bExtInfo,
						   BOOL bFatal)
{
#ifdef SHOW_NE_ERRORS
	// display error
	DisplayErrorMessage(lpError,
						lpSolution,
						bExtInfo,
						bFatal);
#else
	// only output if logging
	if(g_lpErrorLog)
		if(g_lpErrorLog->IsInit())
			DisplayErrorMessage(lpError,
								lpSolution,
								bExtInfo,
								bFatal);
#endif
}

// DisplayFatalErrorMessage()

void DisplayFatalErrorMessage(LPSTR lpError,
							  LPSTR lpSolution,
							  BOOL bExtInfo)
{
	// display error message
	DisplayErrorMessage(lpError,lpSolution,bExtInfo,TRUE);

#ifdef DEBUG_MODE
	// uncomment to locate error
	//return;
#endif

	// end execution
	ForceImmediateExit();
}

// DisplayDXErrorMessage()

void DisplayDXErrorMessage(LPSTR lpError,
						   LPSTR lpSolution,
						   HRESULT hError,
						   BOOL bFatal)
{
	// recursion counter
	static int nRecur=0;

	// add error message
	strcpy(g_lpErrorMsg,
		   (lpError ? lpError : "Undefined error."));

	// check solution string
	if(lpSolution)
	{
		// add line break
		strcat(g_lpErrorMsg,"\n\n");

		// add possible solutions
		strcat(g_lpErrorMsg,lpSolution);
	}
	
	// check for extended info
	if(FAILED(hError))
	{
		// add extended info
		strcat(g_lpErrorMsg,"\n\n");

		// copy dx error description
		strncpy(g_lpErrorMsg+strlen(g_lpErrorMsg),
				DXGetErrorDescription8(hError),
				(_MAX_PATH-1)-strlen(g_lpErrorMsg));

		// set null terminator
		g_lpErrorMsg[_MAX_PATH-1]=0;
	}

	// check error log
	if(LoggingErrors)
	{
		// check recursion counter
		if(nRecur==0)
		{
			// increment counter
			nRecur++;

			// add string
			g_lpErrorLog->AddString((bFatal ? "FATAL DX ERROR" : "DX ERROR"),
									g_lpErrorMsg);

			// dump error log
			g_lpErrorLog->Dump();

			// decrement counter
			nRecur--;
		}
	}
	else
	{
		// display message box
		DisplayMessageBox(g_hWnd,
						  g_lpErrorMsg,
						  (LPSTR)ApplicationName(),
						  MB_OK|(bFatal ? MB_ICONSTOP : MB_ICONWARNING));
	}
}

// DisplayNEDXErrorMessage()

void DisplayNEDXErrorMessage(LPSTR lpError,
						     LPSTR lpSolution,
						     HRESULT hError,
						     BOOL bFatal)
{
#ifdef SHOW_NE_ERRORS
	// display error
	DisplayDXErrorMessage(lpError,
						  lpSolution,
						  hError,
						  bFatal);
#else
	// only output if logging
	if(g_lpErrorLog)
		if(g_lpErrorLog->IsInit())
			DisplayDXErrorMessage(lpError,
								  lpSolution,
								  hError,
								  bFatal);
#endif
}

// DisplayFatalDXErrorMessage()

void DisplayFatalDXErrorMessage(LPSTR lpError,
							    LPSTR lpSolution,
							    HRESULT hError)
{
	// display error message
	DisplayDXErrorMessage(lpError,lpSolution,hError,TRUE);

#ifdef DEBUG_MODE
	// uncomment to locate error
	//return;
#endif

	// end execution
	ForceImmediateExit();
}

// DisplayInfoMessage()

void DisplayInfoMessage(LPSTR lpError)
{
	// recursion counter
	static int nRecur=0;

	// copy error
	strcpy(g_lpErrorMsg,
		   (lpError ? lpError : "Unknown message."));

	// check error log
	if(LoggingErrors)
	{
		// check recursion counter
		if(nRecur==0)
		{
			// increment counter
			nRecur++;

			// add string
			g_lpErrorLog->AddString("INFO",
									g_lpErrorMsg);

			// dump error log
			g_lpErrorLog->Dump()
				;
			// decrement counter
			nRecur--;
		}
	}
	else
	{
		// display message
		DisplayMessageBox(g_hWnd,
						  g_lpErrorMsg,
						  (LPSTR)ApplicationName(),
						  MB_OK|MB_ICONINFORMATION);
	}
}

// SwapPtrs()

void SwapPtrs(LPVOID* lplpPtr1,
 			  LPVOID* lplpPtr2)
{
#ifdef DEBUG_MODE
	// check pointers
	if(!lplpPtr1||
	   !lplpPtr2)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"SwapPtrs()",
							FALSE);
		return;
	}
#endif

	// swap pointers
	LPVOID lpTemp=(*lplpPtr2);
	(*lplpPtr2)=(*lplpPtr1);
	(*lplpPtr1)=lpTemp;
}

// AllocMem()

BOOL AllocMem(LPVOID* lplpPtr,
 			  DWORD dwSize)
{
#ifdef DEBUG_MODE
	// check pointer
	if(!lplpPtr)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"AllocMem()",
							FALSE);
		return(FALSE);
	}
#endif

	// allocate memory
	(*lplpPtr)=malloc(dwSize);

	// check for error
	if(!(*lplpPtr))
	{
		DisplayErrorMessage("The system is out of memory.",
							"Close some open applications and try again.");
		return(FALSE);
	}
	else
		AddMemResource;

	// clear memory
	ZeroMemory((*lplpPtr),
			   dwSize);

	// ok
	return(TRUE);
}

// ExpandMem()

BOOL ExpandMem(LPVOID* lplpPtr,
 			   DWORD dwSize,
 			   DWORD dwExpAmt)
{
#ifdef DEBUG_MODE
	// check pointer
	if(!lplpPtr||
	   !(*lplpPtr))
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ExpandMem()",
							FALSE);
		return(FALSE);
	}
#endif

	// new block
	LPVOID lpVoid;
	
	// allocate new block
	if(!AllocMem(&lpVoid,
				 dwSize+dwExpAmt))
		return(FALSE);

	// copy memory
	CopyMemory(lpVoid,
			   (*lplpPtr),
			   dwSize);

	// swap pointers
	SwapPtrs(&lpVoid,
			 lplpPtr);

	// free old block
	FreeMem(&lpVoid);

	// ok
	return(TRUE);
}

// CompressMem()

BOOL CompressMem(LPVOID* lplpPtr,
 			     DWORD dwSize)
{
#ifdef DEBUG_MODE
	// check pointer
	if(!lplpPtr||
	   !(*lplpPtr))
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CompressMem()",
							FALSE);
		return(FALSE);
	}
#endif

	// new block
	LPVOID lpVoid;
	
	// allocate new block
	if(!AllocMem(&lpVoid,
				 dwSize))
		return(FALSE);

	// copy memory
	CopyMemory(lpVoid,
			   (*lplpPtr),
			   dwSize);

	// swap pointers
	SwapPtrs(&lpVoid,
			 lplpPtr);

	// free old block
	FreeMem(&lpVoid);

	// ok
	return(TRUE);
}

// FreeMem()

void FreeMem(LPVOID* lplpPtr)
{
	// check pointer
	if(*lplpPtr)
	{
		// free memory
		free(*lplpPtr);
		RemoveMemResource;

		// clear pointer
		(*lplpPtr)=NULL;
	}
}

// VerifyClassObject()

BOOL VerifyClassObject(LPVOID lpPtr)
{
	// check pointer
	if(!lpPtr)
	{
		DisplayErrorMessage("A required object could not be created.");
		return(FALSE);
	}
	
	// ok
	return(TRUE);
}

#ifdef DEBUG_MODE
// DisplayResourceUsage()

void DisplayResourceUsage(void)
{
	LockGlobalMsg()

	// display system resources
	sprintf(g_lpMsg,
			"System Resources\n\n"
			"System: %d\n"
			"Memory: %d\n"
			"Class: %d\n"
			"COM: %d\n",
			g_dwNumWinRes,
			g_dwNumMemRes,
			g_dwNumClassRes,
			g_dwNumCOMRes);
	DisplayInfoMessage(g_lpMsg);

	/*// display audio resources
	sprintf(g_lpMsg,
			"Audio Resources\n\n"
			"Segments: %d\n"
			"Audio Paths: %d\n",
			g_dwNumAudioSeg,
			g_dwNumAudioPath);
	DisplayInfoMessage(g_lpMsg);*/

	UnlockGlobalMsg()
}
#endif

// ConfirmResourcesReleased()

void ConfirmResourcesReleased(void)
{
	// compute total resources
	DWORD dwTotalRes=g_dwNumWinRes+
					 g_dwNumMemRes+
					 g_dwNumClassRes+
					 g_dwNumCOMRes/*+
					 g_dwNumAudioSeg+
					 g_dwNumAudioPath*/;

#ifdef DEBUG_MODE
	// if resources are left over, speak up!
	if(dwTotalRes!=0)
	{
		DisplayInfoMessage("Some resources were not able to be released.");
		DisplayResourceUsage();
	}
#endif
}

// DisplayMessageBox()

int DisplayMessageBox(HWND hWnd,
					  LPSTR lpText,
					  LPSTR lpCaption,
					  UINT uType)
{
#ifdef DEBUG_MODE
	// check strings
	if(!lpText||
	   !lpCaption)
	{
		DisplayErrorMessage("Invalid string value.",
							"DisplayMessageBox()",
							FALSE);
		return(NULL);
	}
#endif

	// return value
	int nVal;

	// extended caption string
	char lpXCaption[64];

	// reset new flags
	UINT uFlags=NULL;

	// copy caption string
	strcpy(lpXCaption,
		   lpCaption);

#ifdef SHAREWARE_MODE
	// append "trial version" to caption
	strcat(lpXCaption," (Trial Version)");
#endif

	// ignore given window & use current
	hWnd=::GetForegroundWindow();

	// validate window
	if(hWnd==(HWND)INVALID_HANDLE_VALUE)
		hWnd=NULL;

	// check windows
	if(hWnd!=NULL&&
	   g_hWnd!=NULL&&
	   g_hWnd!=(HWND)INVALID_HANDLE_VALUE)
	{
		// compare thread ids
		if(GetWindowThreadProcessId(hWnd,NULL)==GetWindowThreadProcessId(g_hWnd,NULL))
		{
			// set default flags
			uFlags=MB_SETFOREGROUND|
				   MB_APPLMODAL;
		}
	}

	// check flags
	if(!uFlags)
	{
		// set in-your-face flags
		uFlags=MB_SETFOREGROUND|
			   MB_TASKMODAL|
			   MB_TOPMOST;

		// clear window
		hWnd=NULL;
	}

	// combine flags
	uType=uType|uFlags;

	// display message box
	nVal=MessageBox(hWnd,
					lpText,
					lpXCaption,
					uType);

	// return value
	return(nVal);
}

// ForceImmediateExit()

void ForceImmediateExit(void)
{
	// perform shutdown
	g_MainApp.PrimaryShutdown();

	// return to os
	ExitProcess(0);
}

// CMainApp::PrimaryInit()

BOOL CMainApp::PrimaryInit(void)
{
	// use global message for errors
	g_lpErrorMsg=g_lpMsg;

	// create error log
	AllocClassObject(g_lpErrorLog,
					 CErrorLog);

	// check new object
	if(!g_lpErrorLog)
		return(FALSE);

	// seed random numbers
	srand((int)GetTickCount());

	// enable control container
	AfxEnableControlContainer();

	// enable 3d controls
	if(!g_MainApp.Enable3dControls())
	{
		DisplayErrorMessage("Unable to load system library file 'ctl3d32.dll'.");
		return(FALSE);
	}

	// init rich edit
	if(!AfxInitRichEdit())
	{
		DisplayErrorMessage("Unable to load rich edit control module.");
		return(FALSE);
	}

	// allocate tooltip message string
	if(!AllocMem((LPVOID*)&g_lpTTMsg,
				 LONG_MSG_SIZE))
		return(FALSE);

	// allocate error message string
	if(!AllocMem((LPVOID*)&g_lpErrorMsg,
				 LONG_MSG_SIZE))
		return(FALSE);

	// allocate long message string
	if(!AllocMem((LPVOID*)&g_lpLongMsg,
				 LONG_MSG_SIZE))
		return(FALSE);

	// allocate long tooltip message string
	if(!AllocMem((LPVOID*)&g_lpLongTTMsg,
				 LONG_MSG_SIZE))
		return(FALSE);

	// initialize com
	if(FAILED(CoInitialize(NULL)))
	{
		DisplayErrorMessage("Unable to initialize COM library.");
		return(FALSE);
	}
	else
		AddCOMResource

	// get memory allocator
	if(FAILED(CoGetMalloc(1,
						  &g_lpCoMalloc)))
	{
		DisplayErrorMessage("Unable to find memory allocator object.");
		return(FALSE);
	}
	else
		AddCOMResource

	// get shell link interface
	if(FAILED(CoCreateInstance(CLSID_ShellLink,
							   NULL,
							   CLSCTX_ALL,
							   IID_IShellLink,
							   (LPVOID*)&g_lpShellLink)))
	{
		DisplayErrorMessage("Unable to find shell link resolution interface.");
		return(FALSE);
	}
	else
		AddCOMResource

	// get shell link persist-file
	if(FAILED(g_lpShellLink->QueryInterface(IID_IPersistFile,
											(LPVOID*)&g_lpShellLinkPF)))
	{
		DisplayErrorMessage("Unable to find shell link file interface.");
		return(FALSE);
	}
	else
		AddCOMResource

	// initialize main app
	if(!ApplicationInit(&sei))
		return(FALSE);

	// ok
	return(TRUE);
}

// CMainApp::PrimaryShutdown()

void CMainApp::PrimaryShutdown(void)
{
	// release main app
	ApplicationRelease(&sei);

	// remove leftover wait cursors
	while(::EndWaitCursor())
	{}

	// free message strings
	FreeMem((LPVOID*)&g_lpLongMsg);
	FreeMem((LPVOID*)&g_lpTTMsg);
	FreeMem((LPVOID*)&g_lpLongTTMsg);
	FreeMem((LPVOID*)&g_lpErrorMsg);

	// use global message for any remaining errors
	g_lpErrorMsg=g_lpMsg;

	// release memory allocator
	ReleaseCOMPtr(g_lpCoMalloc);

	// release shell link interfaces
	ReleaseCOMPtr(g_lpShellLinkPF);
	ReleaseCOMPtr(g_lpShellLink);

	// release com
	CoUninitialize();
	RemoveCOMResource

	// release error log
	FreeClassObject(g_lpErrorLog);

	// confirm release of resources
	ConfirmResourcesReleased();

#ifdef DEBUG_MODE
#ifdef CHECK_EXIT
	// alert user
	DisplayInfoMessage("Exit OK");
#endif
#endif
}

// CMainApp::InitInstance()

BOOL CMainApp::InitInstance(void)
{
	// get saver execution info
	if(!GetSaverExecInfo())
		return(FALSE);

	// perform initialization
	if(PrimaryInit())
	{
		// execute main app
		ApplicationExec(&sei);
	}

	// perform shutdown
	PrimaryShutdown();
	
	// close application
	return(FALSE);
}

// CreateBitmapFromIcon()

CBitmap* CreateBitmapFromIcon(HICON hIcon,
							  COLORREF hBackground) 
{
	// check icon handle
	if(hIcon==NULL||
	   hIcon==(HICON)INVALID_HANDLE_VALUE)
		return(NULL);

	// device contexts
	CDC MemDC;
	CDC* lpDesktopDC=NULL;

	// bitmap object
	CBitmap* lpBmp=NULL;

	// get desktop device context
	lpDesktopDC=CDC::FromHandle(::GetDC(GetDesktopWindow()));

	// create compatible device context
	if(!MemDC.CreateCompatibleDC(lpDesktopDC))
		return(NULL);
	else
		AddWinResource

	// allocate new bitmap
	AllocClassObject(lpBmp,
					 CBitmap);

	// check new object
	if(lpBmp)
	{
		// create bitmap
		if(lpBmp->CreateCompatibleBitmap(lpDesktopDC,
										 32,32))
		{
			// get handle to bitmap
			HGDIOBJ hGdiObj=MemDC.SelectObject(lpBmp);

			// check object
			if(hGdiObj)
			{
				// draw background color
				MemDC.FillSolidRect(0,0,
									32,32,
									hBackground);

				// draw icon image
				MemDC.DrawState(CPoint(0,0),
								CSize(32,32),
								hIcon,
								DST_ICON|DSS_NORMAL,
								(HBRUSH)NULL);

				// select object
				MemDC.SelectObject(hGdiObj); 
			}
		}
	}
	
	// delete device contect
	if(MemDC.DeleteDC())
		RemoveWinResource

	// return pointer
	return(lpBmp);
} 

// MakeSafeRegString()

BOOL MakeSafeRegString(LPSTR lpPath,
					   LPSTR* lplpRegPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lplpRegPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"MakeSafeRegString()",
							FALSE);
		return(FALSE);
	}
#endif

	// counter
	DWORD dwCount;

	// check for string
	if(lpPath)
	{
		// allocate memory for new string
		if(!AllocMem((LPVOID*)lplpRegPath,
					 strlen(lpPath)+1))
			return(FALSE);

		// copy path
		strcpy((*lplpRegPath),
			   lpPath);	
	
		// convert to lowercase
		strlwr(*lplpRegPath);

		// reset counter
		dwCount=0;

		// remove non-alpha-num characters
		while((*lplpRegPath)[dwCount]!=0)
		{
			// remove character if necessary
			if(!isalnum((*lplpRegPath)[dwCount]))
				(*lplpRegPath)[dwCount]='_';
			
			// next byte
			dwCount++;
		}

		// ok
		return(TRUE);
	}

	// no good
	return(FALSE);
}
	
// ResizeBitmap()

BOOL ResizeBitmap(CBitmap** lplpDestBmp,
				  CBitmap* lpSrcBmp,
				  int nWidth,
				  int nHeight)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lplpDestBmp||
	   !lpSrcBmp)
	{
		DisplayErrorMessage("Invalid bitmap pointer.",
							"ResizeBitmap()",
							FALSE);
		return(FALSE);
	}

	// verify destination
	if(*lplpDestBmp)
	{
		DisplayErrorMessage("Destination bitmap must be empty!",
							"ResizeBitmap()",
							FALSE);
		return(FALSE);
	}
#endif

	// device contexts
	CDC* lpSrcDC=NULL;
	CDC* lpDestDC=NULL;
	CDC* lpDesktopDC=NULL;

	// return value
	BOOL bRetVal=FALSE;

	// bitmap info
	BITMAP bmp;

	// get bitmap info
	if(!lpSrcBmp->GetBitmap(&bmp))
	{
		DisplayNEErrorMessage("Cannot read bitmap information.");
		goto ResizeBitmap1;
	}

	// allocate bitmap object
	AllocClassObject((*lplpDestBmp),
					 CBitmap);

	// check new object
	if(!(*lplpDestBmp))
	{
		DisplayNEErrorMessage("Unable to allocate bitmap object.");
		goto ResizeBitmap1;
	}

	// allocate source device context
	AllocClassObject(lpSrcDC,
					 CDC);

	// check new object
	if(!lpSrcDC)
	{
		DisplayNEErrorMessage("Unable to allocate source device context.");
		goto ResizeBitmap1;
	}

	// allocate destination device context
	AllocClassObject(lpDestDC,
					 CDC);

	// check new object
	if(!lpDestDC)
	{
		DisplayNEErrorMessage("Unable to allocate destination device context.");
		goto ResizeBitmap1;
	}

	// get desktop device context
	lpDesktopDC=CDC::FromHandle(::GetDC(GetDesktopWindow()));

	// create compatible device context
	if(!lpSrcDC->CreateCompatibleDC(lpDesktopDC))
	{
		DisplayNEErrorMessage("Unable to create desktop source device context.");
		goto ResizeBitmap1;
	}
	else
		AddWinResource	
		
	// create compatible device context
	if(!lpDestDC->CreateCompatibleDC(lpDesktopDC))
	{
		DisplayNEErrorMessage("Unable to create desktop source device context.");
		goto ResizeBitmap1;
	}
	else
		AddWinResource	
		
	// create bitmap
	if(!(*lplpDestBmp)->CreateCompatibleBitmap(lpDesktopDC,
											   nWidth,
											   nHeight))
	{
		DisplayNEErrorMessage("Unable to create resized bitmap.");
		goto ResizeBitmap1;
	}

	// select source bitmap
	lpSrcDC->SelectObject(lpSrcBmp);

	// select destination bitmap
	lpDestDC->SelectObject(*lplpDestBmp);

	// set stretch mode
	lpDestDC->SetStretchBltMode(HALFTONE);
	
	// resize image
	lpDestDC->StretchBlt(0,0,
						 nWidth,
						 nHeight,
						 lpSrcDC,
						 0,0,
						 bmp.bmWidth,
						 bmp.bmHeight,
						 SRCCOPY);

	// set return value
	bRetVal=TRUE;

// error exit point
ResizeBitmap1:;
	
	// delete destination device context
	if(lpDestDC)
		if(lpDestDC->DeleteDC())
			RemoveWinResource
		
	// delete source device context
	if(lpSrcDC)
		if(lpSrcDC->DeleteDC())
			RemoveWinResource

	// release device contexts
	FreeClassObject(lpDestDC);
	FreeClassObject(lpSrcDC);

	// ok
	return(bRetVal);
}

// CaptureDlgControl()

BOOL CaptureDlgControl(CWnd* lpParentWnd,
					   CWnd* lpObjectWnd,
					   UINT nCtrlID,
					   BOOL bSilentFail)
{
#ifdef DEBUG_MODE
	// check pointers
	if(!lpParentWnd||
	   !lpObjectWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CaptureDlgControl()",
							FALSE);
		return(FALSE);
	}
#endif

	// subclass control
	if(!lpObjectWnd->SubclassDlgItem(nCtrlID,
									 lpParentWnd))
	{
		if(!bSilentFail)
			DisplayErrorMessage("Unable to attach control window to dialog box.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// LoadOptionString()

BOOL LoadOptionString(LPCSTR lpKey,
					  LPSTR lpVal,
					  BOOL bIsGlobal)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpKey||
	   !lpVal)
	{
		DisplayErrorMessage("Invalid string value.",
							"LoadOptionString()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// length of buffer
	DWORD dwLen;

	// reset return value
	BOOL bRet=FALSE;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	// matching strings ok
	if(lpVal!=g_lpMsg)
		LockGlobalMsg()
	
	// create registry key
	strcpy(g_lpMsg,
		   ApplicationRegistryPath());
	if(!bIsGlobal)
		strcat(g_lpMsg,
			   "Options");

	// open registry key
	if(lpRegKey->Open((bIsGlobal ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER),
					  g_lpMsg,
					  KEY_READ)==ERROR_SUCCESS)
	{
		AddWinResource

		// matching strings ok
		if(lpVal!=g_lpLongMsg)
			LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// check for theme
		if(lpRegKey->QueryValue(g_lpLongMsg,
								lpKey,
								&dwLen)==ERROR_SUCCESS)
		{
			// copy to buffer
			strcpy(lpVal,
				   g_lpLongMsg);

			// set return value
			bRet=TRUE;
		}

		// matching strings ok
		if(lpVal!=g_lpLongMsg)
			UnlockGlobalLongMsg()

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}

	// matching strings ok
	if(lpVal!=g_lpMsg)
		UnlockGlobalMsg()

	// relese key interface
	FreeClassObject(lpRegKey);

	// return result
	return(bRet);
}

// LoadOptionInt()

int LoadOptionInt(LPCSTR lpKey,
				  int nMin,
				  int nMax,
				  int nDef,
				  BOOL bIsGlobal)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpKey)
	{
		DisplayErrorMessage("Invalid string value.",
							"LoadOptionInt()",
							FALSE);
		return(FALSE);
	}
#endif

	// set default return value
	int nRet=nDef;
	
	LockGlobalMsg()

	// load string
	if(LoadOptionString(lpKey,
						g_lpMsg,
						bIsGlobal))
	{
		// convert to int
		nRet=atoi(g_lpMsg);

		// check for infinite limits
		if(!(nMin==0&&
		     nMax==-1))
		{
			// clip if necessary
			if(nRet<nMin)
				nRet=nMin;
			else if(nRet>nMax)
				nRet=nMax;
		}
	}

	UnlockGlobalMsg()

	// return value
	return(nRet);
}

// SaveOptionString()

BOOL SaveOptionString(LPCSTR lpKey,
					  LPSTR lpVal,
					  BOOL bIsGlobal)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpKey||
	   !lpVal)
	{
		DisplayErrorMessage("Invalid string value.",
							"SaveOptionString()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// reset return value
	BOOL bRet=FALSE;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	LockGlobalLongMsg()

	// create registry key
	strcpy(g_lpLongMsg,
		   ApplicationRegistryPath());
	if(!bIsGlobal)
		strcat(g_lpLongMsg,
			   "Options\\");

	// open registry key
	if(lpRegKey->Create((bIsGlobal ? HKEY_LOCAL_MACHINE : HKEY_CURRENT_USER),
						g_lpLongMsg,
						REG_NONE,
						REG_OPTION_NON_VOLATILE,
						KEY_WRITE,
						NULL,
						NULL)==ERROR_SUCCESS)
	{
		AddWinResource

		// set value
		if(lpRegKey->SetValue(lpVal,
							  lpKey)==ERROR_SUCCESS)
		{
			// set return value
			bRet=TRUE;
		}

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}

	UnlockGlobalLongMsg()

	// relese key interface
	FreeClassObject(lpRegKey);

	// return result
	return(bRet);
}

// SaveOptionInt()

BOOL SaveOptionInt(LPCSTR lpKey,
				   int nVal,
				   BOOL bIsGlobal)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpKey)
	{
		DisplayErrorMessage("Invalid string value.",
							"SaveOptionInt()",
							FALSE);
		return(FALSE);
	}
#endif

	LockGlobalMsg()
	
	// convert value to string
	itoa(nVal,
		 g_lpMsg,
		 10);

	UnlockGlobalMsg()
	
	// save as string
	return(SaveOptionString(lpKey,
							g_lpMsg,
							bIsGlobal));
}

// InitPopupMenu()

BOOL InitPopupMenu(void)
{
	// allocate menu object
	AllocClassObject(g_lpPopupMenu,
					 CMenu);

	// cehck new object
	if(!g_lpPopupMenu)
		return(FALSE);

	// create empty menu
	if(!g_lpPopupMenu->CreatePopupMenu())
	{
		DisplayNEErrorMessage("Unable to create popup menu.");
		return(FALSE);
	}
	else
		AddWinResource

	// ok
	return(TRUE);
}

// AddPopupMenuItem()

BOOL AddPopupMenuItem(LPCTSTR lpszNewItem,
					  UINT nIDNewItem)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpszNewItem)
	{
		DisplayErrorMessage("Invalid string value.",
							"AddPopupMenuItem()",
							FALSE);
		return(FALSE);
	}
#endif

	// check menu object
	if(!g_lpPopupMenu)
		return(FALSE);

	// add item
	if(!g_lpPopupMenu->AppendMenu(MF_STRING,
								  nIDNewItem,
								  lpszNewItem))
	{
		DisplayNEErrorMessage("Unable to add popup menu item.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// AddPopupMenuSeparator()

BOOL AddPopupMenuSeparator(void)
{
	// check menu object
	if(!g_lpPopupMenu)
		return(FALSE);

	// add item
	if(!g_lpPopupMenu->AppendMenu(MF_SEPARATOR))
		return(FALSE);

	// ok
	return(TRUE);
}

// CheckPopupMenuItem()

BOOL CheckPopupMenuItem(UINT nIDItem,
						BOOL bChecked)
{
	// check menu object
	if(!g_lpPopupMenu)
		return(FALSE);

	// flag
	UINT nCheck;

	// set flag
	nCheck=MF_BYCOMMAND|(bChecked ? MF_CHECKED : MF_UNCHECKED);
	
	// check item
	g_lpPopupMenu->CheckMenuItem(nIDItem,
								 nCheck);

	// ok
	return(TRUE);
}

// EnablePopupMenuItem()

BOOL EnablePopupMenuItem(UINT nIDItem,
						 BOOL bEnabled)
{
	// check menu object
	if(!g_lpPopupMenu)
		return(FALSE);

	// flag
	UINT nCheck;

	// set flag
	nCheck=MF_BYCOMMAND|(bEnabled ? MF_ENABLED : MF_GRAYED);
	
	// check item
	g_lpPopupMenu->EnableMenuItem(nIDItem,
								  nCheck);

	// ok
	return(TRUE);
}

// ExecPopupMenu()

void ExecPopupMenu(POINT pCur)
{
	// window object
	CWnd* lpWnd=NULL;

	// check main window handle
	if(g_hWnd!=NULL&&
	   g_hWnd!=(INVALID_HANDLE_VALUE))
	{
		// check menu object
		if(g_lpPopupMenu)
		{
			// get window object
			lpWnd=CWnd::FromHandle(g_hWnd);

			// set to foreground
			if(lpWnd)
				lpWnd->SetForegroundWindow();

			// display menu
			if(!g_lpPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|
											  TPM_LEFTBUTTON|
											  TPM_RIGHTBUTTON,
											  pCur.x,
											  pCur.y,
											  lpWnd,
											  NULL))
				DisplayNEErrorMessage("Unable to display popup menu.");
		}
	}
	
	// destroy menus
	if(g_lpPopupSubmenu)
		if(g_lpPopupSubmenu->DestroyMenu())
			RemoveWinResource
	if(g_lpPopupMenu)
		if(g_lpPopupMenu->DestroyMenu())
			RemoveWinResource

	// free menu objects
	FreeClassObject(g_lpPopupSubmenu);
	FreeClassObject(g_lpPopupMenu);
}

// CExtButton::CExtButton()

CExtButton::CExtButton(UINT nID)
{
	// save id
	nCtrlId=nID;

	// reset values
	bSpclBtn=FALSE;
	bEnabled=TRUE;
	lplpEnBmp=NULL;
	lplpDisBmp=NULL;

	// call base constructor
	CButton::CButton();
}

// CExtButton::OnContextMenu()

void CExtButton::OnContextMenu(CWnd* pWnd,
							   CPoint pos)
{
	// show popup menu (if visible)
	if(IsWindowVisible())
		ShowPopupMenu(nCtrlId);
}

// AddPopupMenuHelpItem()

BOOL AddPopupMenuHelpItem(UINT nIDNewItem)
{
	// add menu item
	return(AddPopupMenuItem("What's This?",
							nIDNewItem));
}

// CExtButton::Enable()

void CExtButton::Enable(void)
{
	// check spcl. button flag
	if(bSpclBtn)
	{
		// set flag
		bEnabled=TRUE;

		// set bitmap
		SetBitmap((HBITMAP)(*lplpEnBmp)->m_hObject);
	}
	else
	{
		// enable window
		EnableWindow(TRUE);
	}

	// add tabstop
	ModifyStyle(NULL,
				WS_TABSTOP);
}

// CExtButton::Disable()

void CExtButton::Disable(void)
{
	// check spcl. button flag
	if(bSpclBtn)
	{
		// set flag
		bEnabled=FALSE;

		// set bitmap
		SetBitmap((HBITMAP)(*lplpDisBmp)->m_hObject);
	}
	else
	{
		// disable window
		EnableWindow(FALSE);
	}
		
	// remove tabstop
	ModifyStyle(WS_TABSTOP,
				NULL);
}

// CExtButton::WindowProc()

LRESULT CExtButton::WindowProc(UINT message,
							   WPARAM wParam,
							   LPARAM lParam)
{
	// check for paint message
	if(message==WM_PAINT)
	{
		// check for spcl. button
		if(bSpclBtn)
		{
			// check enabled flag
			if(bEnabled)
			{
				// check bitmap
				if(lplpEnBmp)
					if(*lplpEnBmp)
					{
						// update bitmap if necessary
						if(GetBitmap()!=(HBITMAP)(*lplpEnBmp)->m_hObject)
							SetBitmap((HBITMAP)(*lplpEnBmp)->m_hObject);
					}
			}
			else
			{
				// check bitmap
				if(lplpDisBmp)
					if(*lplpDisBmp)
					{
						// update bitmap if necessary
						if(GetBitmap()!=(HBITMAP)(*lplpDisBmp)->m_hObject)
							SetBitmap((HBITMAP)(*lplpDisBmp)->m_hObject);
					}
			}
		}
	}
	
	// check spcl. button flags
	if(bSpclBtn&&
	   !bEnabled)
	{
		// check message
		switch(message)
		{
		// state change
		case(BM_SETSTATE):

			// remove highlight
			wParam=(WPARAM)FALSE;

			// ok
			break;

		// focus change
		case(WM_SETFOCUS):

			// eat message
			return(0);
		}
	}

	// call base method
	return(CButton::WindowProc(message,
							   wParam,
							   lParam));
}

// IsPointInWindow()

BOOL IsPointInWindow(CPoint* lpPos,
					 CWnd* lpWnd)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpPos||
	   !lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"IsPointInWindow()",
							FALSE);
		return(FALSE);
	}
#endif

	// window position
	RECT rPos;

	// get window position
	lpWnd->GetWindowRect(&rPos);

	// compare point
	return(IsPointInRect(lpPos,
						 &rPos));
}

// IsPointInRect()

BOOL IsPointInRect(CPoint* lpPos,
				   LPRECT lpRect)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpPos||
	   !lpRect)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"IsPointInRect()",
							FALSE);
		return(FALSE);
	}
#endif

	// compare point
	return(lpPos->x>=lpRect->left&&
		   lpPos->x<=lpRect->right&&
		   lpPos->y>=lpRect->top&&
		   lpPos->y<=lpRect->bottom);
}

// CreateExtButton()

BOOL CreateExtButton(CExtButton** lplpBtn,
					 UINT nID)
{
	// allocate button object
	AllocClassObject((*lplpBtn),
					 CExtButton(nID));

	// check new object
	if(!(*lplpBtn))
		return(FALSE);

	// ok
	return(TRUE);
}

// LoadBitmap()

BOOL LoadBitmap(CBitmap** lplpBmp,
				UINT nID)
{
	// allocate bitmap object
	AllocClassObject((*lplpBmp),
					 CBitmap);

	// check new object
	if(!(*lplpBmp))
		return(FALSE);

	// load bitmap
	if(!(*lplpBmp)->LoadBitmap(nID))
	{
		DisplayErrorMessage("Unable to load bitmap image.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// PostCommand()

BOOL PostCommand(CWnd* lpWnd,
				 int nCmd)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"PostCommand()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"PostCommand()",
							FALSE);
		return(FALSE);
	}
#endif

	// post command message (in hiword of wparam)
	return(lpWnd->PostMessage(WM_COMMAND,
							  (nCmd<<16)));
}

// SendCommand()

BOOL SendCommand(CWnd* lpWnd,
				 int nCmd)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"SendCommand()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"SendCommand()",
							FALSE);
		return(FALSE);
	}
#endif

	// send command message (in hiword of wparam)
	return(lpWnd->SendMessage(WM_COMMAND,
							  (nCmd<<16)));
}

// PostCommand()

BOOL PostCommand(HWND hWnd,
				 int nCmd)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hWnd==NULL||
	   hWnd==(HWND)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid handle value.",
							"PostCommand()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"PostCommand()",
							FALSE);
		return(FALSE);
	}
#endif

	// post command message (in hiword of wparam)
	return(PostMessage(hWnd,
					   WM_COMMAND,
					   (nCmd<<16),
					   NULL));
}

// SendCommand()

BOOL SendCommand(HWND hWnd,
				 int nCmd)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hWnd==NULL||
	   hWnd==(HWND)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid handle value.",
							"PostCommand()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"PostCommand()",
							FALSE);
		return(FALSE);
	}
#endif

	// send command message (in hiword of wparam)
	return(SendMessage(hWnd,
					   WM_COMMAND,
					   (nCmd<<16),
					   NULL));
}

// InsertPopupSubmenu()

BOOL InsertPopupSubmenu(LPCTSTR lpszNewItem)
{
#ifdef DEBUG_MODE
	// check current pointer
	if(g_lpPopupSubmenu)
	{
		DisplayErrorMessage("Submenu already exists.",
							"InsertPopupSubmenu()",
							FALSE);
		return(FALSE);
	}

	// verify string
	if(!lpszNewItem)
	{
		DisplayErrorMessage("Invalid string value.",
							"AddPopupMenuItem()",
							FALSE);
		return(FALSE);
	}
#endif

	// cehck menu object
	if(!g_lpPopupMenu)
		return(FALSE);

	// allocate submenu object
	AllocClassObject(g_lpPopupSubmenu,
					 CMenu);

	// cehck new object
	if(!g_lpPopupSubmenu)
		return(FALSE);

	// create empty menu
	if(!g_lpPopupSubmenu->CreatePopupMenu())
	{
		DisplayNEErrorMessage("Unable to create popup submenu.");
		return(FALSE);
	}
	else
		AddWinResource

	// add popup menu
	if(!g_lpPopupMenu->AppendMenu(MF_POPUP,
								  (UINT)g_lpPopupSubmenu->m_hMenu,
								  lpszNewItem))
	{
		DisplayNEErrorMessage("Unable to add popup submenu.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// AddPopupSubmenuItem()

BOOL AddPopupSubmenuItem(LPCTSTR lpszNewItem,
						 UINT nIDNewItem)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpszNewItem)
	{
		DisplayErrorMessage("Invalid string value.",
							"AddPopupSubmenuItem()",
							FALSE);
		return(FALSE);
	}
#endif

	// check submenu object
	if(!g_lpPopupSubmenu)
		return(FALSE);

	// add item
	if(!g_lpPopupSubmenu->AppendMenu(MF_STRING,
									 nIDNewItem,
									 lpszNewItem))
	{
		DisplayNEErrorMessage("Unable to add popup submenu item.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// AddPopupSubmenuHelpItem()

BOOL AddPopupSubmenuHelpItem(UINT nIDNewItem)
{
	// add submenu item
	return(AddPopupSubmenuItem("What's This?",
							   nIDNewItem));
}

// AddPopupSubmenuSeparator()

BOOL AddPopupSubmenuSeparator(void)
{
	// check submenu object
	if(!g_lpPopupSubmenu)
		return(FALSE);

	// add item
	if(!g_lpPopupSubmenu->AppendMenu(MF_SEPARATOR))
		return(FALSE);

	// ok
	return(TRUE);
}

// CheckPopupSubmenuItem()

BOOL CheckPopupSubmenuItem(UINT nIDItem,
						   BOOL bChecked)
{
	// check submenu object
	if(!g_lpPopupSubmenu)
		return(FALSE);

	// flag
	UINT nCheck;

	// set flag
	nCheck=MF_BYCOMMAND|(bChecked ? MF_CHECKED : MF_UNCHECKED);
	
	// check item
	g_lpPopupSubmenu->CheckMenuItem(nIDItem,
									nCheck);

	// ok
	return(TRUE);
}

// EnablePopupSubmenuItem()

BOOL EnablePopupSubmenuItem(UINT nIDItem,
						    BOOL bEnabled)
{
	// check submenu object
	if(!g_lpPopupSubmenu)
		return(FALSE);

	// flag
	UINT nCheck;

	// set flag
	nCheck=MF_BYCOMMAND|(bEnabled ? MF_ENABLED : MF_GRAYED);
	
	// check item
	g_lpPopupSubmenu->EnableMenuItem(nIDItem,
									 nCheck);

	// ok
	return(TRUE);
}

// DarkenColor()

COLORREF DarkenColor(COLORREF clrSrc,
					 DWORD dwNumBits)
{
	// extract color componennts
	int nR=GetRValue(clrSrc);
	int nG=GetGValue(clrSrc);
	int nB=GetBValue(clrSrc);

	// darken components
	nR-=(nR>>dwNumBits);
	nG-=(nG>>dwNumBits);
	nB-=(nB>>dwNumBits);

	// clip components
	if(nR<0) nR=0;
	if(nG<0) nG=0;
	if(nB<0) nB=0;

	// return new color
	return(RGB(nR,nG,nB));
}

// LightenColor()

COLORREF LightenColor(COLORREF clrSrc,
					  DWORD dwNumBits)
{
	// extract color componennts
	int nR=GetRValue(clrSrc);
	int nG=GetGValue(clrSrc);
	int nB=GetBValue(clrSrc);

	// lighten components
	nR+=(nR>>dwNumBits);
	nG+=(nG>>dwNumBits);
	nB+=(nB>>dwNumBits);

	// clip components
	if(nR>255) nR=255;
	if(nG>255) nG=255;
	if(nB>255) nB=255;

	// return new color
	return(RGB(nR,nG,nB));
}

// CExtStatic::CExtStatic()

CExtStatic::CExtStatic(UINT nID)
{
	// save id
	nCtrlId=nID;

	// call base constructor
	CStatic::CStatic();
}

// CExtStatic::OnContextMenu()

void CExtStatic::OnContextMenu(CWnd* pWnd,
							   CPoint pos)
{
	// show popup menu (if visible)
	if(IsWindowVisible())
		ShowPopupMenu(nCtrlId);
}

// CExtStatic::Enable()

void CExtStatic::Enable(void)
{
	// enable window
	EnableWindow(TRUE);
}

// CExtStatic::Disable()

void CExtStatic::Disable(void)
{
	// disable window
	EnableWindow(FALSE);
}

// CExtEdit::CExtEdit()

CExtEdit::CExtEdit(UINT nID)
{
	// save id
	nCtrlId=nID;

	// reset no-cursor flag
	bNoCursor=FALSE;

	// reset numerical limits
	nMinVal=-1;
	nMaxVal=-1;

	// reset pointer to default value
	lpnDefVal=NULL;

	// reset parent window
	lpParentPropPage=NULL;

	// reset spin control
	lpSpinCtrl=NULL;

	// call base constructor
	CEdit::CEdit();
}

// CExtEdit::OnContextMenu()

void CExtEdit::OnContextMenu(CWnd* pWnd,
							 CPoint pos)
{
	// check visibilty
	if(IsWindowVisible())
	{
		// window rect
		CRect rWnd;
		
		// get window rect
		GetWindowRect(&rWnd);

		// check for horizontal scrollbar
		if(GetStyle()&WS_HSCROLL)
		{
			// deduct from rect
			rWnd.bottom-=GetSystemMetrics(SM_CYHSCROLL);
		}

		// check for vertical scrollbar
		if(GetStyle()&WS_VSCROLL)
		{
			// deduct from rect
			rWnd.right-=GetSystemMetrics(SM_CXVSCROLL);
		}

		// check point
		if(IsPointInRect(&pos,
						 &rWnd))
		{
			// show popup menu
			ShowPopupMenu(nCtrlId);
		}
		else
		{
			// call base method
			CEdit::OnContextMenu(pWnd,
								 pos);
		}
	}
}

// CExtEdit::Enable()

void CExtEdit::Enable(void)
{
	// enable window
	EnableWindow(TRUE);

	// check spin control
	if(lpSpinCtrl)
	{
		// enable control
		lpSpinCtrl->Enable();
	}

	// add tabstop
	ModifyStyle(NULL,
				WS_TABSTOP);
}

// CExtEdit::Disable()

void CExtEdit::Disable(void)
{
	// disable window
	EnableWindow(FALSE);

	// check spin control
	if(lpSpinCtrl)
	{
		// disable control
		lpSpinCtrl->Disable();
	}

	// remove tabstop
	ModifyStyle(WS_TABSTOP,
				NULL);
}

// CExtRichEditCtrl::CExtRichEditCtrl()

CExtRichEditCtrl::CExtRichEditCtrl(UINT nID)
{
	// save id
	nCtrlId=nID;

	// init values
	dwNumBmp=0;
	lplpBmp=NULL;
	lpnX=NULL;
	lpnY=NULL;
	lpnSX=NULL;
	lpnSY=NULL;
	lpnBdrOfs=NULL;
	lpclrBdr=NULL;
	lpclrBkg=NULL;
	lpclrShadow=NULL;

	// call base constructor
	CRichEditCtrl::CRichEditCtrl();
}

// CExtRichEditCtrl::OnContextMenu()

void CExtRichEditCtrl::OnContextMenu(CWnd* pWnd,
									 CPoint pos)
{
	// check visilbilty
	if(IsWindowVisible())
	{
		// window rect
		RECT rRect;
		
		// get window rect
		GetWindowRect(&rRect);
		
		// adjust for border
		rRect.left  +=GetSystemMetrics(SM_CXEDGE);
		rRect.right -=GetSystemMetrics(SM_CXEDGE);
		rRect.top   +=GetSystemMetrics(SM_CYEDGE);
		rRect.bottom-=GetSystemMetrics(SM_CYEDGE);

		// adjust for scroll bars
		if(GetStyle()&WS_HSCROLL)
			rRect.bottom-=GetSystemMetrics(SM_CYHSCROLL);
		if(GetStyle()&WS_VSCROLL)
			rRect.right-=GetSystemMetrics(SM_CXVSCROLL);

		// check point
		if(IsPointInRect(&pos,
						 &rRect))
		{
			// show popup menu
			ShowPopupMenu(nCtrlId);
		}
		else
		{
			// hand off message
			CRichEditCtrl::OnContextMenu(pWnd,
										 pos);
		}
	}
}

// CExtRichEditCtrl::Enable()

void CExtRichEditCtrl::Enable(void)
{
	// enable window
	EnableWindow(TRUE);

	// add tabstop
	ModifyStyle(NULL,
				WS_TABSTOP);
}

// CExtRichEditCtrl::Disable()

void CExtRichEditCtrl::Disable(void)
{
	// disable window
	EnableWindow(FALSE);

	// remove tabstop
	ModifyStyle(WS_TABSTOP,
				NULL);
}

// AddCharsToString()

void AddCharsToString(LPSTR lpStr,
					  char cChar,
					  int nNum)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"AddCharsToString()",
							FALSE);
		return;
	}
#endif

	// counter
	int nCount;

	// set index
	int nIndex=strlen(lpStr);

	// add characters
	for(nCount=0;nCount<nNum;nCount++)
		lpStr[nIndex++]=cChar;

	// set null terminator
	lpStr[nIndex]=0;
}

/* does not work (retained for reference)
// OutputRtfBitmap()

BOOL OutputRtfBitmap(LPSTR lpRtf,
					 CBitmap* lpBmp)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpRtf)
	{
		DisplayErrorMessage("Invalid string value.",
							"OutputRtfBitmap()",
							FALSE);
		return(FALSE);
	}
#endif

	// bitmap info
	BITMAP bm;

	// bitmap bits
	LPBYTE lpBits=NULL;

	// number of bytes
	DWORD dwNumBytes;

	// counter
	DWORD dwCount;
	
	// check bitmap
	if(lpBmp)
	{
		// get bitmap info
		if(!lpBmp->GetBitmap(&bm))
		{
			DisplayNEErrorMessage("Unable to read bitmap info.");
			return(FALSE);
		}

		// get number of bytes
		dwNumBytes=(DWORD)(bm.bmHeight*bm.bmWidthBytes);

		// allocate bitmap bits
		if(!AllocMem((LPVOID*)&lpBits,
					 dwNumBytes))
			return(FALSE);	
		
		// begin picture data
		strcat(lpRtf,"{\\pict\\wbitmap0");
		
		LockGlobalMsg()

		// output bitmap info
		strcat(lpRtf,"\\wbmbitspixel");
		strcat(lpRtf,itoa(bm.bmBitsPixel,g_lpMsg,10));
		strcat(lpRtf,"\\wbmplanes");
		strcat(lpRtf,itoa(bm.bmPlanes,g_lpMsg,10));
		strcat(lpRtf,"\\wbmwidthbytes");
		strcat(lpRtf,itoa(bm.bmWidthBytes,g_lpMsg,10));
		strcat(lpRtf,"\\picw");
		strcat(lpRtf,itoa(bm.bmWidth,g_lpMsg,10));
		strcat(lpRtf,"\\pich");
		strcat(lpRtf,itoa(bm.bmHeight,g_lpMsg,10));
		strcat(lpRtf," ");

		UnlockGlobalMsg()

		// get bitmap bits
		if(!lpBmp->GetBitmapBits(dwNumBytes,
								 lpBits))
		{
			DisplayNEErrorMessage("Unable to read bitmap data.");
			FreeMem((LPVOID*)&lpBits);
			return(FALSE);
		}
		
		// output bits
		for(dwCount=0;dwCount<dwNumBytes;dwCount++)
			strcat(lpRtf,
				   ByteToHexString(lpBits[dwCount]));

		// end picture data
		strcat(lpRtf,"}");

		// free bitmap bits
		FreeMem((LPVOID*)&lpBits);
	}
	else
	{
		// invalid bitmap
		strcat(lpRtf,"<invalid bitmap data>");
	}

	// ok
	return(TRUE);
}*/

// ByteToHexString()

LPSTR ByteToHexString(BYTE cByte)
{
	// return value
	static char lpHex[3];

	// get digits
	BYTE cDigit1=(cByte&0xF0)>>4;
	BYTE cDigit2=cByte&0x0F;

	// output digit #1
	lpHex[0]=(cDigit1>9 ? 'a'+(cDigit1-10) : '0'+cDigit1);

	// output digit #2
	lpHex[1]=(cDigit2>9 ? 'a'+(cDigit2-10) : '0'+cDigit2);

	// output null terminator
	lpHex[2]=0;

	// return string
	return(lpHex);
}

// CExtRichEditCtrl::AddBitmap()

BOOL CExtRichEditCtrl::AddBitmap(int nX,
							     int nY,
							     CBitmap* lpBmp,
								 int nBdrOfs,
								 COLORREF clrBdr,
								 COLORREF clrBkg,
								 COLORREF clrShadow)
{
#ifdef DEBUG_MODE
	// verify bitmap
	if(!lpBmp)
	{
		DisplayErrorMessage("Invalid bitmap pointer.",
							"CExtRichEditCtrl::AddBitmap()",
							FALSE);
		return(FALSE);
	}
#endif

	// bitmap info
	BITMAP bm;
	
	// check counter
	if(!dwNumBmp)
	{
		// allocate data
		if(!AllocMem((LPVOID*)&lplpBmp,
					 sizeof(CBitmap*)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpnX,
					 sizeof(int)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpnY,
					 sizeof(int)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpnSX,
					 sizeof(int)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpnSY,
					 sizeof(int)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpnBdrOfs,
					 sizeof(int)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpclrBdr,
					 sizeof(COLORREF)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpclrBkg,
					 sizeof(COLORREF)))
			return(FALSE);
		if(!AllocMem((LPVOID*)&lpclrShadow,
					 sizeof(COLORREF)))
			return(FALSE);
	}
	else
	{
		// expand data
		if(!ExpandMem((LPVOID*)&lplpBmp,
					  sizeof(CBitmap*)*dwNumBmp,
					  sizeof(CBitmap*)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpnX,
					  sizeof(int)*dwNumBmp,
					  sizeof(int)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpnY,
					  sizeof(int)*dwNumBmp,
					  sizeof(int)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpnSX,
					  sizeof(int)*dwNumBmp,
					  sizeof(int)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpnSY,
					  sizeof(int)*dwNumBmp,
					  sizeof(int)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpnBdrOfs,
					  sizeof(int)*dwNumBmp,
					  sizeof(int)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpclrBdr,
					  sizeof(COLORREF)*dwNumBmp,
					  sizeof(COLORREF)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpclrBkg,
					  sizeof(COLORREF)*dwNumBmp,
					  sizeof(COLORREF)))
			return(FALSE);
		if(!ExpandMem((LPVOID*)&lpclrShadow,
					  sizeof(COLORREF)*dwNumBmp,
					  sizeof(COLORREF)))
			return(FALSE);
	}

	// save bitmap
	lplpBmp[dwNumBmp]=lpBmp;

	// save location
	lpnX[dwNumBmp]=nX;
	lpnY[dwNumBmp]=nY;

	// get bitmap info
	if(!lpBmp->GetBitmap(&bm))
	{
		DisplayNEErrorMessage("Unable to read bitmap info.");
		return(FALSE);
	}

	// save size
	lpnSX[dwNumBmp]=bm.bmWidth;
	lpnSY[dwNumBmp]=bm.bmHeight;

	// save border info
	lpnBdrOfs[dwNumBmp]  =nBdrOfs;
	lpclrBdr[dwNumBmp]   =clrBdr;
	lpclrBkg[dwNumBmp]   =clrBkg;
	lpclrShadow[dwNumBmp]=clrShadow;

	// increment counter
	dwNumBmp++;

	// ok
	return(TRUE);
}

// CExtRichEditCtrl::RemoveBitmaps()

void CExtRichEditCtrl::RemoveBitmaps(void)
{
	// free all data
	FreeMem((LPVOID*)&lplpBmp);
	FreeMem((LPVOID*)&lpnX);
	FreeMem((LPVOID*)&lpnY);
	FreeMem((LPVOID*)&lpnSX);
	FreeMem((LPVOID*)&lpnSY);
	FreeMem((LPVOID*)&lpnBdrOfs);
	FreeMem((LPVOID*)&lpclrBdr);
	FreeMem((LPVOID*)&lpclrBkg);
	FreeMem((LPVOID*)&lpclrShadow);

	// reset counter
	dwNumBmp=0;
}

// CExtRichEditCtrl::~CExtRichEditCtrl()

CExtRichEditCtrl::~CExtRichEditCtrl()
{
	// remove bitmaps
	RemoveBitmaps();

	// call base destructor
	CRichEditCtrl::~CRichEditCtrl();
}

// CExtRichEditCtrl::OnPaint()

void CExtRichEditCtrl::OnPaint(void)
{
	// update flag
	BOOL bUpdate;

	// scroll positions
	int nXPos;
	int nYPos;

	// get update flag
	bUpdate=GetUpdateRect(NULL);
	
	// get scroll positions
	nXPos=-GetScrollPos(SB_HORZ);
	nYPos=-GetScrollPos(SB_VERT);

	// call base function
	CRichEditCtrl::OnPaint();

	// draw bitmaps if necessary
	if(bUpdate)
		DrawBitmaps(nXPos,
					nYPos);
}

// CExtRichEditCtrl::OnHScroll()

void CExtRichEditCtrl::OnHScroll(UINT nSBCode,
								 UINT nPos,
								 CScrollBar* pScrollBar)
{
	// scroll info
	SCROLLINFO si;

	// check scrollbar code
	if(nSBCode==SB_THUMBPOSITION||
	   nSBCode==SB_THUMBTRACK)
	{
		// set size of structure
		si.cbSize=sizeof(si);

		// get horizontal bar info
		if(GetScrollInfo(SB_HORZ,
						 &si))
		{
			// keep position updated
			SetScrollPos(SB_HORZ,
						 si.nTrackPos,
						 FALSE);
		}
	}

	// call base function
	CRichEditCtrl::OnHScroll(nSBCode,
							 nPos,
							 pScrollBar);
}

// CExtRichEditCtrl::OnVScroll()

void CExtRichEditCtrl::OnVScroll(UINT nSBCode,
								 UINT nPos,
								 CScrollBar* pScrollBar)
{
	// scroll info
	SCROLLINFO si;

	// check scrollbar code
	if(nSBCode==SB_THUMBPOSITION||
	   nSBCode==SB_THUMBTRACK)
	{
		// set size of structure
		si.cbSize=sizeof(si);

		// get vertical bar info
		if(GetScrollInfo(SB_VERT,
						 &si))
		{
			// keep position updated
			SetScrollPos(SB_VERT,
						 si.nTrackPos,
						 FALSE);
		}
	}

	// call base function
	CRichEditCtrl::OnVScroll(nSBCode,
							 nPos,
							 pScrollBar);
}

// CExtRichEditCtrl::DrawBitmaps()

BOOL CExtRichEditCtrl::DrawBitmaps(int nXOfs,
								   int nYOfs)
{
	// counter
	DWORD dwCount;

	// draw bitmaps
	if(dwNumBmp)
		for(dwCount=0;dwCount<dwNumBmp;dwCount++)
			if(!DrawBitmap(dwCount,
						   nXOfs,
						   nYOfs))
				return(FALSE);

	// ok
	return(TRUE);
}

// CExtRichEditCtrl::ScrollToTop()

void CExtRichEditCtrl::ScrollToTop(void)
{
	// get first line
	int nFirstLine=GetFirstVisibleLine();

	// scroll to top
	LineScroll(-(nFirstLine+1));

	// set scroll position
	SetScrollPos(SB_VERT,
				 0,
				 FALSE);
}

// CExtRichEditCtrl::DrawBitmap()

BOOL CExtRichEditCtrl::DrawBitmap(DWORD dwIndex,
								  int nXOfs,
								  int nYOfs)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex>=dwNumBmp)
	{
		DisplayErrorMessage("Invalid bitmap index.",
							"CExtRichEditCtrl::DrawBitmap()",
							FALSE);
		return(FALSE);
	}
#endif

	// return value
	BOOL bRet=FALSE;

	// device contexts
	CDC* lpSrcDC=NULL;
	CDC* lpDestDC=NULL;

	// drawing rect
	CRect rDraw;
	
	// text-area rect
	CRect rText;

	// device context state
	int nState;

	// get bitmap data
	int nX            =lpnX[dwIndex]+nXOfs;
	int nY            =lpnY[dwIndex]+nYOfs;
	int nSX           =lpnSX[dwIndex];
	int nSY           =lpnSY[dwIndex];
	CBitmap* lpBmp    =lplpBmp[dwIndex];
	int nBdrOfs       =lpnBdrOfs[dwIndex];
	COLORREF clrBdr   =lpclrBdr[dwIndex];
	COLORREF clrBkg   =lpclrBkg[dwIndex];
	COLORREF clrShadow=lpclrShadow[dwIndex];

	// adjust position by border
	nX+=nBdrOfs;
	nY+=nBdrOfs;

	// get text-area rect
	GetRect(rText);

	// deflate text area
	rText.DeflateRect(1,1);	

	// get device context
	lpDestDC=GetDC();

	// check for error
	if(!lpDestDC)
	{
		DisplayNEErrorMessage("Cannot find rich edit control device context.");
		goto CExtRichEditCtrl_DrawBitmap1;
	}
	else
		AddWinResource

	// save device context
	nState=lpDestDC->SaveDC();

	// check for border
	if(nBdrOfs)
	{
		// set shadow rect
		rDraw.left  =(nX-nBdrOfs)+1;
		rDraw.right =rDraw.left+nSX+(nBdrOfs*2);
		rDraw.top   =(nY-nBdrOfs)+1;
		rDraw.bottom=rDraw.top+nSY+(nBdrOfs*2);

		// check intersect
		if(rDraw.IntersectRect(rText,
							   rDraw))
		{
			// draw shadow
			lpDestDC->FillSolidRect(rDraw,
									clrShadow);
		}

		// set border rect
		rDraw.left  =(nX-nBdrOfs);
		rDraw.right =rDraw.left+nSX+(nBdrOfs*2);
		rDraw.top   =(nY-nBdrOfs);
		rDraw.bottom=rDraw.top+nSY+(nBdrOfs*2);

		// check intersect
		if(rDraw.IntersectRect(rText,
							   rDraw))
		{
			// draw border
			lpDestDC->FillSolidRect(rDraw,
									clrBdr);
		}

		// set background rect
		rDraw.left  =(nX-nBdrOfs)+1;
		rDraw.right =(rDraw.left+nSX+(nBdrOfs*2))-2;
		rDraw.top   =(nY-nBdrOfs)+1;
		rDraw.bottom=(rDraw.top+nSY+(nBdrOfs*2))-2;

		// check intersect
		if(rDraw.IntersectRect(rText,
							   rDraw))
		{
			// draw background
			lpDestDC->FillSolidRect(rDraw,
									clrBkg);
		}
	}

	// set bitmap rect
	rDraw.left  =nX;
	rDraw.right =rDraw.left+nSX;
	rDraw.top   =nY;
	rDraw.bottom=rDraw.top+nSY;

	// check intersect
	if(rDraw.IntersectRect(rText,
						   rDraw))
	{
		// allocate source dc
		AllocClassObject(lpSrcDC,
						 CDC);

		// check object
		if(!lpSrcDC)
		{
			DisplayNEErrorMessage("Cannot find bitmap device context.");
			goto CExtRichEditCtrl_DrawBitmap1;
		}

		// create source dc
		if(!lpSrcDC->CreateCompatibleDC(lpDestDC))
		{
			DisplayNEErrorMessage("Cannot create bitmap device context.");
			goto CExtRichEditCtrl_DrawBitmap1;
		}
		else
			AddWinResource

		// select object
		if(!lpSrcDC->SelectObject(lpBmp))
		{
			DisplayNEErrorMessage("Cannot select source bitmap object.");
			goto CExtRichEditCtrl_DrawBitmap1;
		}

		// draw bitmap
		if(!lpDestDC->BitBlt(rDraw.left,
							 rDraw.top,
							 rDraw.Width(),
							 rDraw.Height(),
							 lpSrcDC,
							 nSX-rDraw.Width(),
							 nSY-rDraw.Height(),
							 SRCCOPY))
		{
			DisplayNEErrorMessage("Unable to draw bitmap in edit control.");
			goto CExtRichEditCtrl_DrawBitmap1;
		}
	}

	// ok
	bRet=TRUE;

// error exit point
CExtRichEditCtrl_DrawBitmap1:;

	// delete source dc
	if(lpSrcDC)
		if(lpSrcDC->DeleteDC())
			RemoveWinResource

	// free source dc
	FreeClassObject(lpSrcDC);

	// check destination dc
	if(lpDestDC)
	{
		// restore dc
		lpDestDC->RestoreDC(nState);

		// release dc
		if(ReleaseDC(lpDestDC))
			RemoveWinResource
	}

	// ok
	return(bRet);
}

// ExecuteExternalApp()

BOOL ExecuteExternalApp(LPTSTR lpCmdLine,
						LPPROCESS_INFORMATION lpPI,
						BOOL bHideWnd,
						LPCTSTR lpWorkingDir)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpCmdLine)
	{
		DisplayErrorMessage("Invalid string value.",
							"ExecuteExternalApp()",
							FALSE);
		return(FALSE);
	}
#endif

	// startup info
	STARTUPINFO si;

	// process info
	PROCESS_INFORMATION pi;

	// prepare startup info
	si.cb=sizeof(si);
	si.lpReserved=NULL;
	si.lpDesktop=NULL;
	si.lpTitle=NULL;
	si.dwFlags=NULL;
	si.cbReserved2=NULL;
	si.lpReserved2=NULL;

	// check for hide flag
	if(bHideWnd)
	{
		// add flag
		si.dwFlags|=STARTF_USESHOWWINDOW;

		// add hide flag
		si.wShowWindow=SW_HIDE;
	}

	// create new process
	if(!CreateProcess(NULL,
					  lpCmdLine,
					  NULL,
					  NULL,
					  FALSE,
					  NULL,
					  NULL,
					  lpWorkingDir,
					  &si,
					  &pi))
	{
		DisplayErrorMessage("Unable to start external application:",
							(LPSTR)lpCmdLine);
		return(FALSE);
	}

	// copy process info
	if(lpPI)
		(*lpPI)=pi;

	// ok
	return(TRUE);
}

// GetWndFromProcess()

HWND GetWndFromProcess(LPPROCESS_INFORMATION lpPI)
{
	// proc-wnd info
	_PROCWND pw;
	
	// prepare info
	pw.hWnd=NULL;
	pw.lpPI=lpPI;

	// enumerate windows
	EnumWindows(GetWndFromProcessCallback,
				(LPARAM)&pw);

	// return window handle
	return(pw.hWnd);
}

// GetWndFromProcessCallback()

BOOL CALLBACK GetWndFromProcessCallback(HWND hWnd,
										LPARAM lParam)
{
	// window process handle
	HANDLE hProc=INVALID_HANDLE_VALUE;
	
	// cast pointer to info
	_LPPROCWND lpPW=(_LPPROCWND)lParam;

	// compare thread id's
	if(lpPW->lpPI->dwThreadId==GetWindowThreadProcessId(hWnd,
														NULL))
	{
		// copy window handle
		lpPW->hWnd=hWnd;

		// stop here
		return(FALSE);
	}
	
	// ok
	return(TRUE);
}

// CenterWindow()

BOOL CenterWindow(HWND hWnd,
				  HWND hRefWnd)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hWnd==NULL||
	   hWnd==(HWND)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid handle value.",
							"CenterWindow()",
							FALSE);
		return(FALSE);
	}
#endif

	// window rects
	CRect rWnd;
	CRect rRefWnd;

	// center points
	CPoint pWnd;
	CPoint pRefWnd;

	// offset values
	int nXOfs;
	int nYOfs;
	
	// get window rect
	if(!GetWindowRect(hWnd,
					  &rWnd))
		return(FALSE);

	// check ref handle
	if(hRefWnd==NULL||
	   hRefWnd==(HWND)INVALID_HANDLE_VALUE)
	{
		// get window rect
		if(!GetWindowRect(hRefWnd,
						  &rRefWnd))
			return(FALSE);
	}
	else
	{
		// set to screen size
		rRefWnd.SetRect(0,0,
						GetSystemMetrics(SM_CXFULLSCREEN),
						GetSystemMetrics(SM_CYFULLSCREEN));
	}

	// get center points
	pWnd=rWnd.CenterPoint();
	pRefWnd=rRefWnd.CenterPoint();

	// compute offset
	nXOfs=pRefWnd.x-pWnd.x;
	nYOfs=pRefWnd.y-pWnd.y;

	// offset window
	rWnd.OffsetRect(nXOfs,
					nYOfs);

	// move window
	if(!MoveWindow(hWnd,
				   rWnd.left,
				   rWnd.top,
				   rWnd.Width(),
				   rWnd.Height(),
				   TRUE))
		return(FALSE);

	// ok
	return(TRUE);
}

// HighlightWindow()

void HighlightWindow(HWND hWnd)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hWnd==NULL||
	   hWnd==(HWND)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid handle value.",
							"HighlightWindow()",
							FALSE);
		return;
	}
#endif

	// check flash id
	if(g_nFlashId)
	{
		// kill timer
		KillTimer(NULL,
				  g_nFlashId);

		// reset id
		g_nFlashId=0;
	}

	// save window handle
	g_hFlashWnd=hWnd;

	// reset counter
	g_dwFlashCnt=0;

	// flash window
	FlashWindow(g_hFlashWnd,
				TRUE);

	// set timer
	g_nFlashId=SetTimer(NULL,
						NULL,
						33,
						FlashTimerProc);
}

// FlashTimerProc()

void CALLBACK FlashTimerProc(HWND hWnd,
							 UINT uMsg,
							 UINT idEvent,
							 DWORD dwTime)
{
	// check counter
	if(g_dwFlashCnt>8)
	{
		// un-flash window
		FlashWindow(g_hFlashWnd,
					FALSE);

		// kill timer
		KillTimer(NULL,
				  g_nFlashId);

		// reset id
		g_nFlashId=0;

		// ok
		return;
	}
	
	// flash window
	if((g_dwFlashCnt%2)!=0)
	FlashWindow(g_hFlashWnd,
				TRUE);

	// increment counter
	g_dwFlashCnt++;
}

// CExtComboBox::CExtComboBox()

CExtComboBox::CExtComboBox(UINT nID)
{
	// save id
	nCtrlId=nID;

	// call base constructor
	CComboBox::CComboBox();
}

// CExtComboBox::OnContextMenu()

void CExtComboBox::OnContextMenu(CWnd* pWnd,
								 CPoint pos)
{
	// show popup menu (if visible)
	if(IsWindowVisible())
		ShowPopupMenu(nCtrlId);
}

// CExtComboBox::Enable()

void CExtComboBox::Enable(void)
{
	// enable window
	EnableWindow(TRUE);

	// add tabstop
	ModifyStyle(NULL,
				WS_TABSTOP);
}

// CExtComboBox::Disable()

void CExtComboBox::Disable(void)
{
	// disable window
	EnableWindow(FALSE);

	// remove tabstop
	ModifyStyle(WS_TABSTOP,
				NULL);
}

// ClipboardHasData()

BOOL ClipboardHasData(void)
{
	// return value
	BOOL bRet=FALSE;

	// open clipboard
	if(OpenClipboard(NULL))
	{
		AddWinResource

		// check for data
		if(GetClipboardData(CF_TEXT))
			bRet=TRUE;

		// close clipboard
		if(CloseClipboard())
			RemoveWinResource
	}

	// no good
	return(bRet);
}

// GetFilenameFromPath()

BOOL GetFilenameFromPath(LPSTR lpFile,
						 DWORD dwBufferLg,
						 LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetFilenameFromPath()",
							FALSE);
		return(FALSE);
	}
#endif

	// error value
	DWORD dwVal;

	// filename pointer
	LPSTR lpName=NULL;

	// check for path
	if(!lpPath)
		return(FALSE);

	// get filename
	dwVal=GetFullPathName(lpPath,
						  dwBufferLg,
						  lpFile,
						  &lpName);

	// check for error
	if(dwVal==0||
	   dwVal>dwBufferLg)
		return(FALSE);

	// copy name
	strcpy(lpFile,
		   lpName);
		
	// ok
	return(TRUE);
}

// CExtEdit::OnSetFocus()

void CExtEdit::OnSetFocus(CWnd* pOldWnd)
{
	// check read-only flag
	if(bNoCursor)
	{
		// do nothing (refuse focus)
	}
	else
	{
		// call base method
		CEdit::OnSetFocus(pOldWnd);

		// select all text
		SetSel(0,-1);
	}
}

// CExtEdit::OnSetCursor()

BOOL CExtEdit::OnSetCursor(CWnd* pWnd,
						   UINT nHitTest,
						   UINT message)
{
	// check read-only flag
	if(bNoCursor)
	{
		// refuse to change cursor
		return(FALSE);
	}
	else
	{
		// call base method
		return(CEdit::OnSetCursor(pWnd,
								  nHitTest,
								  message));
	}
}

// CExtEdit::SetNoCursor()

void CExtEdit::SetNoCursor(BOOL bFlag)
{
	// save flag
	bNoCursor=bFlag;
}

// CExtFileDialog::OnFileNameOK()

BOOL CExtFileDialog::OnFileNameOK(void)
{
	// check for callback
	if(CheckFileCallback)
	{
		// check file
		if(CheckFileCallback())
		{
			// no good
			return(TRUE);
		}
	}

	// call base method
	return(CFileDialog::OnFileNameOK());
}

// CExtFileDialog::SetCheckFileCallback()

void CExtFileDialog::SetCheckFileCallback(BOOL (*lpfnCallback)(void))
{
	// copy value
	CheckFileCallback=lpfnCallback;
}

// CExtComboBox::SelectStringExact()

int CExtComboBox::SelectStringExact(LPSTR lpFind)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFind)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtComboBox::SelectStringExact()",
							FALSE);
		return(CB_ERR);
	}
#endif

	// matching index
	int nMatch;
	
	// set first & last match
	int nFirstMatch=-1;
	int nLastMatch=-1;

	// look for string
	while(TRUE)
	{
		// perform search
		nMatch=FindStringExact(nLastMatch,
							   lpFind);

		// check result
		if(nMatch==CB_ERR||
		   nMatch==nFirstMatch)
		{
			// not found
			return(-1);
		}

		// save first match
		if(nFirstMatch==-1)
			nFirstMatch=nMatch;

		// save last match
		nLastMatch=nMatch;

		LockGlobalLongMsg()

		// get text of matching item
		if(GetLBText(nMatch,
				     g_lpLongMsg)==CB_ERR)
		{
			UnlockGlobalLongMsg()

			// not found
			return(-1);
		}

		// check for exact match
		if(strcmp(g_lpLongMsg,
				  lpFind)==0)
		{
			// select string
			SetCurSel(nMatch);
			
			UnlockGlobalLongMsg()

			// ok
			return(nMatch);
		}

		UnlockGlobalLongMsg()
	}
}

// CorrectRTFNewLines()

void CorrectRTFNewLines(LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"CorrectRTFNewLines()",
							FALSE);
		return;
	}
#endif

	// counters
	int nCount;
	int nCount2;

	// string length
	int nStrLen;

	// get string length
	nStrLen=strlen(lpStr);

	// check length
	if(nStrLen<2)
		return;

	// append whitespace
	lpStr[nStrLen+0]=' ';
	lpStr[nStrLen+1]=0;

	// search string
	for(nCount=0;nCount<nStrLen;nCount++)
	{
		// check for CR/LF
		if(lpStr[nCount]==0x0D)
			if(lpStr[nCount+1]==0x0A)
			{
				// move remainder of string
				for(nCount2=nStrLen+4;nCount2>nCount;nCount2--)
					lpStr[nCount2]=lpStr[nCount2-3];

				// set rtf newline
				lpStr[nCount+0]='\\';
				lpStr[nCount+1]='p';
				lpStr[nCount+2]='a';
				lpStr[nCount+3]='r';
				lpStr[nCount+4]=' ';

				// update length
				nStrLen+=3;
			}
	}

	// remove appended whitespace
	lpStr[nStrLen]=0;
}

#ifdef DEBUG_MODE
// LockGlobalMessageString()

void LockGlobalMessageString(void)
{
	// check flag
	if(_g_bMsgLocked)
		DisplayErrorMessage("Global string collision! (g_lpMsg)",
							g_lpMsg,
							FALSE);

	// set flag
	_g_bMsgLocked=TRUE;
}

// UnlockGlobalMessageString()

void UnlockGlobalMessageString(void)
{
	// reset flag
	_g_bMsgLocked=FALSE;
}

// LockGlobalLongMessageString()

void LockGlobalLongMessageString(void)
{
	// check flag
	if(_g_bLongMsgLocked)
		DisplayErrorMessage("Global string collision! (g_lpLongMsg)",
						    g_lpLongMsg,
							FALSE);

	// set flag
	_g_bLongMsgLocked=TRUE;
}

// UnlockGlobalLongMessageString()

void UnlockGlobalLongMessageString(void)
{
	// reset flag
	_g_bLongMsgLocked=FALSE;
}

// LockGlobalTTMessageString()

void LockGlobalTTMessageString(void)
{
	// check flag
	if(_g_bTTMsgLocked)
		DisplayErrorMessage("Global string collision! (g_lpTTMsg)",
							g_lpTTMsg,
							FALSE);

	// set flag
	_g_bTTMsgLocked=TRUE;
}

// UnlockGlobalTTMessageString()

void UnlockGlobalTTMessageString(void)
{
	// reset flag
	_g_bTTMsgLocked=FALSE;
}

// LockGlobalLongTTMessageString()

void LockGlobalLongTTMessageString(void)
{
	// check flag
	if(_g_bLongTTMsgLocked)
		DisplayErrorMessage("Global string collision! (g_lpLongTTMsg)",
						    g_lpLongTTMsg,
							FALSE);

	// set flag
	_g_bLongTTMsgLocked=TRUE;
}

// UnlockGlobalLongTTMessageString()

void UnlockGlobalLongTTMessageString(void)
{
	// reset flag
	_g_bLongTTMsgLocked=FALSE;
}

// LockGlobalErrorMessageString()

void LockGlobalErrorMessageString(void)
{
	// check flag
	if(_g_bErrorMsgLocked)
		DisplayErrorMessage("Global string collision! (g_lpErrorMsg)",
						    NULL,
							FALSE);

	// set flag
	_g_bErrorMsgLocked=TRUE;
}

// UnlockGlobalErrorMessageString()

void UnlockGlobalErrorMessageString(void)
{
	// reset flag
	_g_bErrorMsgLocked=FALSE;
}
#endif

// DisableSysMenuClose()

BOOL DisableSysMenuClose(CWnd* lpWnd)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"DisableSysMenuClose()",
							FALSE);
		return(FALSE);
	}
#endif
	
	// system menu
	CMenu* lpSysMenu=NULL;
	
	// check window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayNEErrorMessage("Unable to modify system menu.",
							  "Target window does not exist.");
		return(FALSE);
	}

	// get system menu
	lpSysMenu=lpWnd->GetSystemMenu(FALSE);

	// check for menu
	if(!lpSysMenu)
	{
		DisplayNEErrorMessage("Unable to get system menu object.");
		return(FALSE);
	}

	// disable close command
	if(lpSysMenu->EnableMenuItem(SC_CLOSE,
								 MF_BYCOMMAND|
								 MF_GRAYED)==-1)
	{
		DisplayNEErrorMessage("Unable to modify system menu object.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// PerformFocusSwap()

void PerformFocusSwap(CWnd* lpWnd1,
					  CWnd* lpWnd2,
					  UINT nDelay,
					  DWORD dwNumSwaps)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpWnd1||
	   !lpWnd2)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"PerformFocusSwap()",
							FALSE);
		return;
	}
#endif

	// check swap id
	if(g_nFSwapId)
	{
		// kill timer
		KillTimer(NULL,
				  g_nFSwapId);

		// reset id
		g_nFSwapId=0;
	}

	// save window handles
	g_hFSwapWnd1=lpWnd1->m_hWnd;
	g_hFSwapWnd2=lpWnd2->m_hWnd;

	// reset counter
	g_dwFSwapCnt=(dwNumSwaps*2)-1;

	// set focus to window #2
	SetFocus(g_hFSwapWnd2);

	// set timer
	g_nFSwapId=SetTimer(NULL,
						NULL,
						nDelay,
						SwapTimerProc);
}

// SwapTimerProc()

void CALLBACK SwapTimerProc(HWND hWnd,
							UINT uMsg,
							UINT idEvent,
							DWORD dwTime)
{
	// check counter
	if(g_dwFSwapCnt==0)
	{
		// kill timer
		KillTimer(NULL,
				  g_nFSwapId);

		// reset id
		g_nFSwapId=0;

	}
	
	// set focus as req'd
	SetFocus((g_dwFSwapCnt&1) ? g_hFSwapWnd1 : g_hFSwapWnd2);

	// decrement counter
	g_dwFSwapCnt--;
}

// CExtHeaderCtrl::CExtHeaderCtrl()

CExtHeaderCtrl::CExtHeaderCtrl()
{
	// reset no-resize flag
	bNoResizeCursor=FALSE;

	// call base method
	CHeaderCtrl::CHeaderCtrl();
}

// CExtHeaderCtrl::SetNoResizeCursor()

void CExtHeaderCtrl::SetNoResizeCursor(BOOL bFlag)
{
	// copy flag
	bNoResizeCursor=bFlag;
}

// CExtHeaderCtrl::OnSetCursor()

BOOL CExtHeaderCtrl::OnSetCursor(CWnd* pWnd,
								 UINT nHitTest,
								 UINT message)
{
	// check no-resize flag
	if(bNoResizeCursor)
	{
		// keep cursor
		return(FALSE);
	}

	// call base method
	return(CHeaderCtrl::OnSetCursor(pWnd,
									nHitTest,
									message));
}
 
// CExtMessageBox::CExtMessageBox()

CExtMessageBox::CExtMessageBox()
{
	// reset check flag
	bBtnChecked=FALSE;

	// reset pointers
	lpSeparator=NULL;
	lpNoShowCbx=NULL;

	// call base method
	CWnd::CWnd();
}

// CExtMessageBox::MessageBox()

int CExtMessageBox::MessageBox(LPCTSTR lpszText,
							   LPCTSTR lpszCaption,
							   UINT nType)
{
	// add necessary flags
	nType=nType|
		  MB_SETFOREGROUND|
		  MB_APPLMODAL;

	LockGlobalMsg()

	// copy caption string
	strcpy(g_lpMsg,
		   lpszCaption);

#ifdef SHAREWARE_MODE
	// append "trial version" to caption
	strcat(g_lpMsg," (Trial Version)");
#endif

    // hook window creation
	AfxHookWindowCreate(this);

	// create message box
	return(AfxMessageBox(lpszText,
						 nType));
}

// CExtMessageBox::OnCreate()

int CExtMessageBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// unhook window
	AfxUnhookWindowCreate();

	// update caption
	SetWindowText(g_lpMsg);

	UnlockGlobalMsg()

	// call base method
	return(CWnd::OnCreate(lpCreateStruct));
}

// CExtMessageBox::OnMsgBoxClose()

LRESULT CExtMessageBox::OnMsgBoxClose(WPARAM wParam,
									  LPARAM lParam)
{
	// perform default processing
	LRESULT lRet=Default();

	UnlockGlobalMsg()

	// release extra windows
	FreeClassObject(lpSeparator);
	FreeClassObject(lpNoShowCbx);

	// ok
	return(lRet);
}

// CExtMessageBox::OnMsgBoxInit()

LRESULT CExtMessageBox::OnMsgBoxInit(WPARAM wParam,
									 LPARAM lParam)
{
	// window rects
	CRect rWnd;
	CRect rSep;
	CRect rCbx;
	
	// perform default processing
	LRESULT lRet=Default();

	// get window rect
	GetWindowRect(&rWnd);

	// message box sizes
	#define XMB_SEPXMARGIN 10
	#define XMB_CBXXMARGIN 12
	#define XMB_YMARGIN    8
	#define XMB_CBXHEIGHT  16
	#define XMB_SEPHEIGHT  2

	// add height for extra controls
	rWnd.bottom+=XMB_SEPHEIGHT+
				 XMB_YMARGIN+
				 XMB_CBXHEIGHT+
				 XMB_YMARGIN;

	// resize window
	MoveWindow(&rWnd);

	// create separator
	AllocClassObject(lpSeparator,
					 CStatic);

	// check for error
	if(!lpSeparator)
		ForceImmediateExit();

	// create checkbox
	AllocClassObject(lpNoShowCbx,
					 CButton);

	// check for error
	if(!lpNoShowCbx)
		ForceImmediateExit();

	// get client rect
	GetClientRect(&rWnd);

	// calculate separator window
	rSep.left  =XMB_SEPXMARGIN;
	rSep.right =rSep.left+(rWnd.Width()-(XMB_SEPXMARGIN*2));
	rSep.top   =rWnd.bottom-(XMB_SEPHEIGHT+XMB_YMARGIN+XMB_CBXHEIGHT+XMB_YMARGIN);
	rSep.bottom=rSep.top+XMB_SEPHEIGHT;

	// create separator window
	if(!lpSeparator->Create(NULL,
							WS_CHILD|
							WS_VISIBLE|
							SS_ETCHEDHORZ,
							rSep,
							this,
							IDC_STATIC))
	{
		DisplayFatalErrorMessage("Unable to create divider window.");
		ForceImmediateExit();
	}

	// calculate checkbox window
	rCbx.left  =XMB_CBXXMARGIN;
	rCbx.right =rCbx.left+(rWnd.Width()-(XMB_CBXXMARGIN*2));
	rCbx.top   =rWnd.bottom-(XMB_CBXHEIGHT+XMB_YMARGIN);
	rCbx.bottom=rCbx.top+XMB_CBXHEIGHT;

	// create checkbox window
	if(!lpNoShowCbx->Create(" Do not show this message again",
							WS_CHILD|
							WS_VISIBLE|
							WS_TABSTOP|
							BS_CHECKBOX,
							rCbx,
							this,
							IDC_XMSGBOXCHK))
	{
		DisplayFatalErrorMessage("Unable to create checkbox window.");
		ForceImmediateExit();
	}

	// update font
	lpNoShowCbx->SetFont(GetFont());

	// update checkbox
	SetCheck(bBtnChecked);

	// ok
	return(lRet);
}

// CExtMessageBox::SetCheck()

void CExtMessageBox::SetCheck(BOOL bFlag)
{
	// copy flag
	bBtnChecked=bFlag;

	// set button state
	lpNoShowCbx->SetCheck(bFlag ? 1 : 0);
}

// CExtMessageBox::GetCheck()

BOOL CExtMessageBox::GetCheck()
{
	// return flag
	return(bBtnChecked);
}

// CExtMessageBox::OnCommand()

BOOL CExtMessageBox::OnCommand(WPARAM wParam,
							   LPARAM lParam)
{
	// check message id
	if(HIWORD(wParam)==BN_CLICKED)
	{
		// check control id
		if(LOWORD(wParam)==IDC_XMSGBOXCHK)
		{
			// toggle checkbox
			SetCheck(GetCheck() ? FALSE : TRUE);
		}
	}

	// call base method
	return(CWnd::OnCommand(wParam,
						   lParam));
}

// DisplayOptMessageBox()

int DisplayOptMessageBox(LPCSTR lpText,
						 LPCSTR lpCaption,
						 UINT uType,
						 LPCSTR lpRegKey)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpText||
	   !lpCaption||
	   !lpRegKey)
	{
		DisplayErrorMessage("Invalid string value.",
							"DisplayOptMessageBox()",
							FALSE);
		return(0);
	}
#endif

	// message box object
	CExtMessageBox* lpMsgBox=NULL;

	// registry strings
	LPSTR lpRegFlag =NULL;
	LPSTR lpRegReply=NULL;

	// return value
	int nRet=0;

	// create message box
	AllocClassObject(lpMsgBox,
					 CExtMessageBox);

	// check for error
	if(!lpMsgBox)
		return(0);

	LockGlobalTTMsg()
	LockGlobalLongTTMsg()
	
	// copy key value
	strcpy(g_lpTTMsg,
		   lpRegKey);

	// append "flag"
	strcat(g_lpTTMsg,
		   "Flag");

	// copy key value
	strcpy(g_lpLongTTMsg,
		   lpRegKey);

	// append "reply"
	strcat(g_lpLongTTMsg,
		   "Reply");

	// allocate flag string
	if(!AllocMem((LPVOID*)&lpRegFlag,
				 strlen(g_lpTTMsg)+1))
	{
		FreeClassObject(lpMsgBox);
		return(0);
	}

	// copy flag string
	strcpy(lpRegFlag,
		   g_lpTTMsg);

	// allocate reply string
	if(!AllocMem((LPVOID*)&lpRegReply,
				 strlen(g_lpLongTTMsg)+1))
	{
		FreeClassObject(lpRegFlag);
		FreeClassObject(lpMsgBox);
		return(0);
	}

	// copy reply string
	strcpy(lpRegReply,
		   g_lpLongTTMsg);

	UnlockGlobalTTMsg()
	UnlockGlobalLongTTMsg()

	// check for flag
	if(LoadOptionInt(lpRegFlag,
					 0,
					 1,
					 0)==0)
	{
		// run message box
		nRet=lpMsgBox->MessageBox(lpText,
								  lpCaption,
								  uType);

		// check flag
		if(lpMsgBox->GetCheck())
		{
			// save option
			SaveOptionInt(lpRegFlag,
						  1);

			// save reply
			SaveOptionInt(lpRegReply,
						  nRet);
		}
	}
	else
	{
		// load reply
		nRet=LoadOptionInt(lpRegReply,
						   MIN_INT,
						   MAX_INT,
						   0);
	}

	UnlockGlobalTTMsg()
	UnlockGlobalLongTTMsg()

	// release message box
	FreeClassObject(lpMsgBox);

	// release strings
	FreeClassObject(lpRegFlag);
	FreeClassObject(lpRegReply);

	// return reply
	return(nRet);
}

// CExtButton::SetSpclBitmapButton()

void CExtButton::SetSpclBitmapButton(BOOL bEnable,
									 CBitmap** lplpEnabled,
									 CBitmap** lplpDisabled)
{
#ifdef DEBUG_MODE
	// verify bitmaps
	if(!lplpEnabled||
	   !lplpDisabled||
	   !(*lplpEnabled)||
	   !(*lplpDisabled))
	{
		DisplayErrorMessage("Invalid bitmap pointer.",
							"CExtButton::SetSpclBitmapButton()",
							FALSE);
		return;
	}
#endif

	// clear flag (for proper enabling)
	bSpclBtn=FALSE;

	// button must be enabled
	Enable();
	
	// set flag
	bSpclBtn=TRUE;

	// copy bitmaps
	lplpEnBmp=lplpEnabled;
	lplpDisBmp=lplpDisabled;

	// enable button as needed
	if(bEnable)
		Enable();
	else
		Disable();
}

// DoesFileExist()

BOOL DoesFileExist(LPSTR lpFile)
{
#ifdef DEBUG_MODE
	// verify filename
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string pointer.",
							"DoesFileExist()",
							FALSE);
		return(FALSE);
	}
#endif

	// open file info
	OFSTRUCT ofs;

	// prepare file info
	ofs.cBytes=sizeof(OFSTRUCT);

	// check existence
	if(OpenFile(lpFile,
				&ofs,
				OF_EXIST)==HFILE_ERROR)
		return(FALSE);

	// ok
	return(TRUE);
}

// ReadFile()

BOOL ReadFile(HANDLE hFile,
			  LPVOID lpBuffer,
			  DWORD dwBytes,
			  BOOL bSilent)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid file handle.",
							"ReadFile()",
							FALSE);
		return(FALSE);
	}
	
	// verify buffer
	if(!lpBuffer)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ReadFile()",
							FALSE);
		return(FALSE);
	}
#endif

	// bytes read
	DWORD dwBytesRead;

	// read file
	if(!ReadFile(hFile,
				 lpBuffer,
				 dwBytes,
				 &dwBytesRead,
				 NULL))
	{
		if(!bSilent)
			DisplayNEErrorMessage("Unable to read from file.");
		return(FALSE);
	}

	// check bytes read
	if(dwBytes!=dwBytesRead)
	{
		if(!bSilent)
			DisplayNEErrorMessage("Unexpected end of file during read operation.");
		return(FALSE);
	}
	
	// ok
	return(TRUE);
}

// WriteFile()

BOOL WriteFile(HANDLE hFile,
			   LPVOID lpBuffer,
			   DWORD dwBytes,
			   BOOL bSilent)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid file handle.",
							"WriteFile()",
							FALSE);
		return(FALSE);
	}
	
	// verify buffer
	if(!lpBuffer)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"WriteFile()",
							FALSE);
		return(FALSE);
	}
#endif
	
	// bytes written
	DWORD dwBytesWritten;

	// write file
	if(!WriteFile(hFile,
				  lpBuffer,
				  dwBytes,
				  &dwBytesWritten,
				  NULL))
	{
		if(!bSilent)
			DisplayNEErrorMessage("Unable to write to file.");
		return(FALSE);
	}

	// check bytes written
	if(dwBytes!=dwBytesWritten)
	{
		if(!bSilent)
			DisplayNEErrorMessage("Unexpected end of file during write operation.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// MoveFilePointer()

BOOL MoveFilePointer(HANDLE hFile,
					 long lDistToMove,
					 BOOL bSilent,
					 DWORD dwMoveMethod)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid file handle.",
							"ReadFile()",
							FALSE);
		return(FALSE);
	}
#endif

	// set file pointer
	if(SetFilePointer(hFile,
					  lDistToMove,
					  NULL,
					  dwMoveMethod)==0xFFFFFFFFL)
	{
		if(!bSilent)
			DisplayNEErrorMessage("Unable to set file pointer.");
		return(FALSE);
	}
	
	// ok
	return(TRUE);
}

// ReadFileEnc()

BOOL ReadFileEnc(HANDLE hFile,
			     LPVOID lpBuffer,
			     DWORD dwBytes,
			     BOOL bSilent)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid file handle.",
							"ReadFileEnc()",
							FALSE);
		return(FALSE);
	}
	
	// verify buffer
	if(!lpBuffer)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ReadFileEnc()",
							FALSE);
		return(FALSE);
	}
#endif

	// return value
	BOOL bRet;

	// counter
	DWORD dwCount;

	// cast byte pointer to buffer
	LPBYTE lpData=(LPBYTE)lpBuffer;

	// read encoded data
	bRet=ReadFile(hFile,
				  lpBuffer,
				  dwBytes,
				  bSilent);

	// decode bytes
	for(dwCount=0;dwCount<dwBytes;dwCount++)
		lpData[dwCount]=~lpData[dwCount];

	// ok
	return(bRet);
}

// WriteFileEnc()

BOOL WriteFileEnc(HANDLE hFile,
			      LPVOID lpBuffer,
			      DWORD dwBytes,
			      BOOL bSilent)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid file handle.",
							"WriteFileEnc()",
							FALSE);
		return(FALSE);
	}
	
	// verify buffer
	if(!lpBuffer)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"WriteFileEnc()",
							FALSE);
		return(FALSE);
	}
#endif
	
	// return value
	BOOL bRet;

	// counter
	DWORD dwCount;

	// cast byte pointer to buffer
	LPBYTE lpData=(LPBYTE)lpBuffer;

	// encode bytes
	for(dwCount=0;dwCount<dwBytes;dwCount++)
		lpData[dwCount]=~lpData[dwCount];

	// write encoded data
	bRet=WriteFile(hFile,
				   lpBuffer,
				   dwBytes,
				   bSilent);

	// decode bytes
	for(dwCount=0;dwCount<dwBytes;dwCount++)
		lpData[dwCount]=~lpData[dwCount];

	// ok
	return(bRet);
}

// CExtHotKeyCtrl::CExtHotKeyCtrl()

CExtHotKeyCtrl::CExtHotKeyCtrl(UINT nID)
{
	// save id
	nCtrlId=nID;

	// call base constructor
	CHotKeyCtrl::CHotKeyCtrl();
}

// CExtHotKeyCtrl::OnContextMenu()

void CExtHotKeyCtrl::OnContextMenu(CWnd* pWnd,
								   CPoint pos)
{
	// show popup menu (if visible)
	if(IsWindowVisible())
		ShowPopupMenu(nCtrlId);
}

// CExtHotKeyCtrl::Enable()

void CExtHotKeyCtrl::Enable(void)
{
	// enable window
	EnableWindow(TRUE);

	// add tabstop
	ModifyStyle(NULL,
				WS_TABSTOP);
}

// CExtHotKeyCtrl::Disable()

void CExtHotKeyCtrl::Disable(void)
{
	// disable window
	EnableWindow(FALSE);

	// remove tabstop
	ModifyStyle(WS_TABSTOP,
				NULL);
}

// CExtEdit::SetNumLimits()

void CExtEdit::SetNumLimits(int nMin,
						    int nMax,
							int* lpnDef)
{
	// current value
	int nCurVal;

	// save values
	nMinVal=nMin;
	nMaxVal=nMax;
	
	// save pointer to default
	lpnDefVal=lpnDef;

	LockGlobalMsg()

	// get current value
	if(GetWindowText(g_lpMsg,
					 _MAX_PATH))
	{
		// get current value
		nCurVal=atoi(g_lpMsg);

		// check current value
		if(nCurVal>nMaxVal)
		{
			// set max value
			SetWindowText(itoa(nMaxVal,
							   g_lpMsg,
							   10));
		}
		else if(nCurVal<nMinVal)
		{
			// set min value
			SetWindowText(itoa(nMinVal,
							   g_lpMsg,
							   10));
		}
	}

	UnlockGlobalMsg()
}

// CExtEdit::OnTextChange()

void CExtEdit::OnTextChange(void)
{
	// current value
	int nCurVal;

	// check limits
	if(nMinVal>=0&&
	   nMaxVal>=0)
	{
		// check for text
		if(GetWindowTextLength()!=0)
		{
			LockGlobalMsg()

			// get window text
			GetWindowText(g_lpMsg,
						  _MAX_PATH);

			// get current value
			nCurVal=atoi(g_lpMsg);

			UnlockGlobalMsg()
			
			// compare with upper limit
			if(nCurVal>nMaxVal)
			{
				// just to verify
				LockGlobalMsg()
				UnlockGlobalMsg()

				// set new value
				if(nCurVal<nMinVal)
					SetWindowText(itoa(nMinVal,
									   g_lpMsg,
									   10));
				else if(nCurVal>nMaxVal)
					SetWindowText(itoa(nMaxVal,
									   g_lpMsg,
									   10));

				LockGlobalMsg()

				// prepare message
				sprintf(g_lpMsg,
						"Please enter a value from %d to %d.",
						nMinVal,
						nMaxVal);

				// alert user
				DisplayInfoMessage(g_lpMsg);

				UnlockGlobalMsg()
			}
		}
	}

	// check for parent
	if(lpParentPropPage)
		lpParentPropPage->SetModified();
}

// CExtEdit::OnLButtonUp()

void CExtEdit::OnLButtonUp(UINT nFlags,
						   CPoint point)
{
	// call base method
	CEdit::OnLButtonUp(nFlags,
					   point);

	// check limits
	if(nMinVal>=0&&
	   nMaxVal>=0)
	{
		// select all text
		SetSel(0,-1);
	}
}

// CExtEdit::OnFocusLost()

void CExtEdit::OnFocusLost(void)
{
	// check limits
	if(nMinVal>=0&&
	   nMaxVal>=0)
	{
		// check for no text
		if(GetWindowTextLength()==0)
		{
			// just to verify
			LockGlobalMsg()
			UnlockGlobalMsg()

			// check for default
			if(lpnDefVal)
			{
				// set to default value
				SetWindowText(itoa((*lpnDefVal),
								   g_lpMsg,
								   10));
			}
			else
			{
				// set to minimum value
				SetWindowText(itoa(nMinVal,
								   g_lpMsg,
								   10));
			}
		}
	}
}

// CExtEdit::SetParentPropPage()

void CExtEdit::SetParentPropPage(CPropertyPage* lpPage)
{
	// copy value
	lpParentPropPage=lpPage;
}

// CExtEdit::AddSpinControl()

BOOL CExtEdit::AddSpinControl(CWnd* lpParentWnd,
							  UINT nID,
							  UINT nSndID,
							  BOOL bHorz,
							  BOOL bWrap,
							  BOOL bArrowKeys,
							  BOOL bAutoUpdate,
							  BOOL nNoThouSep,
							  BOOL bAlignRight,
							  LPBOOL lpbVisFlag)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpParentWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CExtEdit::AddSpinControl()",
							FALSE);
		return(FALSE);
	}

	// verify windows
	if(!IsWindow(this->m_hWnd)||
	   !IsWindow(lpParentWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CExtEdit::AddSpinControl()",
							FALSE);
		return(FALSE);
	}

	// check for existing spin control
	if(lpSpinCtrl)
	{
		DisplayErrorMessage("Spin control already added.",
							"CExtEdit::AddSpinControl()",
							FALSE);
		return(FALSE);
	}

	// check for limits
	if(nMinVal<0||
	   nMaxVal<0)
	{
		DisplayErrorMessage("Limits must be set before adding spin control.",
							"CExtEdit::AddSpinControl()",
							FALSE);
		return(FALSE);
	}
#endif

	// flags
	DWORD dwFlags;

	// null rect
	RECT rNull={0,0,0,0};

	// create spin control
	AllocClassObject(lpSpinCtrl,
					 CExtSpinCtrl(nID,
								  nSndID));

	// check new object
	if(!lpSpinCtrl)
		return(FALSE);

	// set visibility flag pointer
	lpSpinCtrl->SetVisibilityFlagPtr(lpbVisFlag);

	// set flags
	dwFlags=WS_CHILD|
			WS_VISIBLE;

	// update flags based on settings
	if(bHorz)       dwFlags|=UDS_HORZ;
	if(bWrap)       dwFlags|=UDS_WRAP;
	if(bArrowKeys)  dwFlags|=UDS_ARROWKEYS;
	if(bAutoUpdate) dwFlags|=UDS_SETBUDDYINT;
	if(nNoThouSep)  dwFlags|=UDS_NOTHOUSANDS;
	if(bAlignRight) dwFlags|=UDS_ALIGNRIGHT; else dwFlags|=UDS_ALIGNLEFT;

	// create spin control
	if(!lpSpinCtrl->Create(dwFlags,
						   rNull,
						   lpParentWnd,
						   nCtrlId))
	{
		DisplayErrorMessage("Unable to add arrow control to edit box.");
		return(FALSE);
	}

	// set buddy window
	lpSpinCtrl->SetBuddy(this);

	// set range
	lpSpinCtrl->SetRange(nMinVal,
						 nMaxVal);

	// ok
	return(TRUE);
}

// CExtEdit::~CExtEdit()

CExtEdit::~CExtEdit()
{
	// release spin control
	FreeClassObject(lpSpinCtrl);

	// call base destructor
	CEdit::~CEdit();
}

// CExtSpinCtrl::CExtSpinCtrl()

CExtSpinCtrl::CExtSpinCtrl(UINT nID,
						   UINT nSndID)
{
	// save id values
	nCtrlId =nID;
	nSoundId=nSndID;

	// reset visibility flag pointer
	lpbVisFlag=NULL;

	// call base constructor
	CSpinButtonCtrl::CSpinButtonCtrl();
}

// CExtSpinCtrl::OnContextMenu()

void CExtSpinCtrl::OnContextMenu(CWnd* pWnd,
							     CPoint pos)
{
	// show popup menu (if visible)
	if(IsWindowVisible())
		ShowPopupMenu(nCtrlId);
}

// CExtSpinCtrl::Enable()

void CExtSpinCtrl::Enable(void)
{
	// enable window
	EnableWindow(TRUE);

	// update window
	UpdateWindow();
}

// CExtSpinCtrl::Disable()

void CExtSpinCtrl::Disable(void)
{
	// disable window
	EnableWindow(FALSE);

	// update window
	UpdateWindow();
}

// DoesPathExist()

BOOL DoesPathExist(LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify path
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"DoesPathExist()",
							FALSE);
		return(FALSE);
	}
#endif

	// find-file handle
	HANDLE hFind;
	
	// find-data structure	
	WIN32_FIND_DATA wfd;

	// search for path
	hFind=FindFirstFile(lpPath,
						&wfd);

	// check handle
	if(hFind==INVALID_HANDLE_VALUE)
	{
		// not found
		return(FALSE);
	}
	else
		AddWinResource

	// close handle
	if(FindClose(hFind))
		RemoveWinResource

	// ok
	return(TRUE);
}

// SelectPathDlg()

BOOL SelectPathDlg(CWnd* lpParentWnd,
				   LPSTR lpPath,
				   LPSTR lpStartPath,
				   LPCSTR lpTitle)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpParentWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"SelectPathDlg()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpParentWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window object.",
							"SelectPathDlg()",
							FALSE);
		return(FALSE);
	}

	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"SelectPathDlg()",
							FALSE);
		return(FALSE);
	}
#endif

	// reset return value
	BOOL bRet=FALSE;

	// browse info
	BROWSEINFO bi;

	// root item list pointer
	LPITEMIDLIST lpRootID=NULL;

	// start item list pointer
	LPITEMIDLIST lpStartID=NULL;

	// item list pointer
	LPITEMIDLIST lpID=NULL;

	// feign memory resource
	AddMemResource

	// check for start path
	if(lpStartPath)
	{
		// get id list
		lpStartID=GetIDListFromPath(lpParentWnd->m_hWnd,
								    lpStartPath);

		// check id list
		if(lpStartID)
		{
			// remove feigned resource
			RemoveMemResource
		}
	}

	// use namespace root
	if(FAILED(SHGetSpecialFolderLocation(NULL,
										 CSIDL_DESKTOP,
										 &lpRootID)))
	{
		// reset root
		lpRootID=NULL;
	}
	else
		AddMemResource

	// init browse info
	bi.hwndOwner     =lpParentWnd->m_hWnd;
	bi.pidlRoot      =lpRootID;
	bi.pszDisplayName=lpPath;
	bi.lpszTitle     =lpTitle;
	bi.ulFlags       =BIF_RETURNONLYFSDIRS|BIF_RETURNFSANCESTORS|BIF_NEWDIALOGSTYLE|BIF_NONEWFOLDERBUTTON;
	bi.lpfn          =SelectPathCallback;
	bi.lParam        =(LPARAM)lpStartID;
	bi.iImage        =NULL;

	// run dialog box
	lpID=SHBrowseForFolder(&bi);

	// check result
	if(lpID)
	{
		AddMemResource

		// convert to path
		if(!SHGetPathFromIDList(lpID,
							    lpPath))
		{
			// alert user
			DisplayErrorMessage("Unable to get a valid path from the selected folder.");
		}
		else
		{
			// set return value
			bRet=TRUE;
		}

		// free id block
		g_lpCoMalloc->Free(lpID);

		RemoveMemResource
	}

	// release id lists
	g_lpCoMalloc->Free(lpRootID);
	g_lpCoMalloc->Free(lpStartID);

	RemoveMemResource
	RemoveMemResource

	// ok
	return(bRet);
}

// CExtSpinCtrl::OnLButtonUp()

void CExtSpinCtrl::OnLButtonUp(UINT nFlags,
							   CPoint point)
{
	// check sound id
	if(nSoundId)
	{
		// play sound
		PlaySound(nSoundId);
	}

	// call base method
	CSpinButtonCtrl::OnLButtonUp(nFlags,
								 point);
}

// GetDlgCtrlWnd()

BOOL GetDlgCtrlWnd(CWnd** lplpWnd,
				   CWnd* lpParent,
				   UINT nCtrlId)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lplpWnd||
	   !lpParent)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"GetDlgCtrlWnd()",
							FALSE);
		return(FALSE);
	}
	
	// verify window
	if(!IsWindow(lpParent->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"GetDlgCtrlWnd()",
							FALSE);
		return(FALSE);
	}
#endif

	// window pointer
	CWnd* lpWnd=NULL;

	// reset return value
	(*lplpWnd)=NULL;

	// get control
	lpWnd=lpParent->GetDlgItem(nCtrlId);

	// check pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Unable to find dialolg box control window.");
		return(FALSE);
	}

	// check window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Dialog box control window does not exist.");
		return(FALSE);
	}

	// set return value
	(*lplpWnd)=lpWnd;

	// ok
	return(TRUE);
}

// FindChildWindow()

BOOL FindChildWindow(CWnd** lplpWnd,
					 CWnd* lpParent,
					 LPSTR lpClass,
					 LPSTR lpTitle,
					 UINT nID)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lplpWnd||
	   !lpParent)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"FindChildWindow()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpParent->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"FindChildWindow()",
							FALSE);
		return(FALSE);
	}
#endif

	// child window
	CWnd* lpChild=NULL;

	// reset return window
	(*lplpWnd)=NULL;
	
	// get child window
	lpChild=lpParent->GetWindow(GW_CHILD);

	// check pointer
	if(!lpChild)
	{
		DisplayNEErrorMessage("Unable to find descendant window.");
		return(FALSE);
	}

	// check window
	if(!IsWindow(lpChild->m_hWnd))
	{
		DisplayNEErrorMessage("Descendant window does not exist.");
		return(FALSE);
	}

	// search siblings
	(*lplpWnd)=FindSiblingWindow(lpChild,
								 lpClass,
								 lpTitle,
								 nID);

	// check window
	if(!(*lplpWnd))
	{
		DisplayNEErrorMessage("Descendant window cound not be found.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// FindSiblingWindow()

CWnd* FindSiblingWindow(CWnd* lpWnd,
						LPSTR lpClass,
						LPSTR lpTitle,
						UINT nID)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"FindSiblingWindow()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"FindChildWindow()",
							FALSE);
		return(FALSE);
	}
#endif

	// sibling window
	CWnd* lpSibWnd=NULL;

	// set match flags
	BOOL bClassMatch=TRUE;
	BOOL bTitleMatch=TRUE;
	BOOL bIDMatch   =TRUE;

	// check for class
	if(lpClass)
	{
		LockGlobalMsg()

		// clear message
		g_lpMsg[0]=0;

		// get class name
		GetClassName(lpWnd->m_hWnd,
					 g_lpMsg,
					 _MAX_PATH);

		// compare classes
		if(strcmp(lpClass,
				  g_lpMsg)!=0)
		{
			// reset flag
			bClassMatch=FALSE;
		}

		UnlockGlobalMsg()
	}

	// check for title
	if(lpTitle)
	{
		LockGlobalMsg()

		// clear message
		g_lpMsg[0]=0;

		// get window title
		lpWnd->GetWindowText(g_lpMsg,
							 _MAX_PATH);

		// compare titles
		if(strcmp(lpTitle,
				  g_lpMsg)!=0)
		{
			// reset flag
			bTitleMatch=FALSE;
		}

		UnlockGlobalMsg()
	}

	// check for id
	if(nID)
	{
		// compare ids
		if(nID!=(UINT)lpWnd->GetDlgCtrlID())
		{
			// reset flag
			bIDMatch=FALSE;
		}

	}

	// check flags
	if(bClassMatch&&
	   bTitleMatch&&
	   bIDMatch)
	{
		// return this window
		return(lpWnd);
	}

	// get next sibling
	lpSibWnd=lpWnd->GetWindow(GW_HWNDNEXT);

	// check pointer
	if(lpSibWnd)
	{
		// check window
		if(IsWindow(lpSibWnd->m_hWnd))
		{
			// search siblings
			return(FindSiblingWindow(lpSibWnd,
									 lpClass,
									 lpTitle,
									 nID));
		}
	}

	// not found
	return(NULL);
}

// GetSafeParentWnd()

BOOL GetSafeParentWnd(CWnd** lplpParent,
					  CWnd* lpWnd)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lplpParent||
	   !lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"GetSafeParentWnd()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"GetSafeParentWnd()",
							FALSE);
		return(FALSE);
	}
#endif

	// get parent window
	(*lplpParent)=lpWnd->GetParent();

	// check parent object
	if(!(*lplpParent))
	{
		DisplayNEErrorMessage("Cannot find parent window.");
		return(FALSE);
	}

	// check parent window
	if(!IsWindow((*lplpParent)->m_hWnd))
	{
		DisplayNEErrorMessage("Parent window does not exist.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// MoveCtrlToPH()

BOOL MoveCtrlToPH(CWnd* lpSrcWnd,
				  CWnd* lpParentWnd,
				  UINT nDestCtrlId,
				  int nDX,
				  int nDY)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpSrcWnd||
	   !lpParentWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"MoveCtrlToPH()",
							FALSE);
		return(FALSE);
	}

	// verify windows
	if(!IsWindow(lpSrcWnd->m_hWnd)||
	   !IsWindow(lpParentWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"MoveCtrlToPH()",
							FALSE);
		return(FALSE);
	}
#endif

	// destination window
	CWnd* lpDestWnd=NULL;

	// window rects
	CRect rWnd1;
	CRect rWnd2;

	// get destination window
	lpDestWnd=lpParentWnd->GetDlgItem(nDestCtrlId);

	// check window
	if(!lpDestWnd)
	{
		DisplayNEErrorMessage("Unable to find dialog box placeholder.");
		return(FALSE);
	}

	// get window rect
	lpDestWnd->GetWindowRect(&rWnd1);

	// compute window size
	rWnd2.right =rWnd1.right -rWnd1.left;
	rWnd2.bottom=rWnd1.bottom-rWnd1.top;

	// convert to client
	lpParentWnd->ScreenToClient(&rWnd1);

	// copy window size
	rWnd1.right =rWnd2.right;
	rWnd1.bottom=rWnd2.bottom;

	// hide destination window
	lpDestWnd->ShowWindow(SW_HIDE);

	// place source window
	if(!lpSrcWnd->SetWindowPos(NULL,
							   rWnd1.left+nDX,
							   rWnd1.top+nDY,
							   rWnd1.right,
							   rWnd1.bottom,
							   SWP_NOZORDER))
	{
		DisplayNEErrorMessage("Unable to set window placement position.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// GetWindowOffset()

BOOL GetWindowOffset(CWnd* lpWnd1,
					 CWnd* lpWnd2,
					 int* lpnDX,
					 int* lpnDY)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpWnd1||
	   !lpWnd2)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"GetWindowOffset()",
							FALSE);
		return(FALSE);
	}

	// verify windows
	if(!IsWindow(lpWnd1->m_hWnd)||
	   !IsWindow(lpWnd2->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"GetWindowOffset()",
							FALSE);
		return(FALSE);
	}
#endif

	// window rects
	CRect rWnd1;
	CRect rWnd2;

	// get window locations
	lpWnd1->GetWindowRect(&rWnd1);
	lpWnd2->GetWindowRect(&rWnd2);

	// compute offset values
	(*lpnDX)=rWnd2.left-rWnd1.left;
	(*lpnDY)=rWnd2.top -rWnd1.top;

	// ok
	return(TRUE);
}

// ResizeClient()

BOOL ResizeClient(CWnd* lpWnd,
				  int nWd,
				  int nHt)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ResizeClient()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"ResizeClient()",
							FALSE);
		return(FALSE);
	}
#endif

	// window rectangles
	CRect rWindow;
	CRect rClient;

	// border sizes
	int nBdrWd;
	int nBdrHt;

	// center point
	CPoint rCen;

	// get window rect
	lpWnd->GetWindowRect(&rWindow);

	// get client rect
	lpWnd->GetClientRect(&rClient);

	// compute border sizes
	nBdrWd=rWindow.Width() -rClient.Width();
	nBdrHt=rWindow.Height()-rClient.Height();

	// add border to new client size
	nWd+=nBdrWd;
	nHt+=nBdrHt;

	// get center of current window
	rCen=rWindow.CenterPoint();

	// compute new window
	rWindow.left  =rCen.x-(nWd/2);
	rWindow.right =rWindow.left+nWd;
	rWindow.top   =rCen.y-(nHt/2);
	rWindow.bottom=rWindow.top+nHt;

	// set window size
	if(!lpWnd->SetWindowPos(NULL,
							rWindow.left,
							rWindow.top,
							rWindow.Width(),
							rWindow.Height(),
							SWP_NOZORDER))
	{
		DisplayNEErrorMessage("Unable to resize window client area.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// CExtSliderCtrl::CExtSliderCtrl()

CExtSliderCtrl::CExtSliderCtrl(UINT nID)
{
	// save id
	nCtrlId=nID;

	// call base constructor
	CSliderCtrl::CSliderCtrl();
}

// CExtSliderCtrl::OnContextMenu()

void CExtSliderCtrl::OnContextMenu(CWnd* pWnd,
								   CPoint pos)
{
	// show popup menu (if visible)
	if(IsWindowVisible())
		ShowPopupMenu(nCtrlId);
}

// CExtSliderCtrl::Enable()

void CExtSliderCtrl::Enable(void)
{
	// enable window
	EnableWindow(TRUE);
}

// CExtSliderCtrl::Disable()

void CExtSliderCtrl::Disable(void)
{
	// disable window
	EnableWindow(FALSE);
}

// ReplaceBmpColor()

BOOL ReplaceBmpColor(CBitmap* lpBmp,
					 COLORREF clrDest,
					 COLORREF clrSrc)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpBmp)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ReplaceBmpColor()",
							FALSE);
		return(FALSE);
	}
#endif

	// pointer to dc object
	CDC* lpDC=NULL;

	// previous gdi object
	CGdiObject* lpGdiObj=NULL;

	// bitmap info
	BITMAP bmp;

	// counters
	int nX;
	int nY;

	// comparison color
	COLORREF clrCmp;

	// get bitmap info
	if(!lpBmp->GetBitmap(&bmp))
	{
		DisplayNEErrorMessage("Cannot read bitmap information.");
		return(FALSE);
	}

	// create dc object
	AllocClassObject(lpDC,
					 CDC);

	// check new object
	if(!lpDC)
		return(FALSE);

	// init dc
	if(!lpDC->CreateCompatibleDC(NULL))
	{
		DisplayNEErrorMessage("Unable to get display device context.");
		return(FALSE);
	}

	// select bitmap
	lpGdiObj=lpDC->SelectObject(lpBmp);

	// check object
	if(lpGdiObj==NULL)
	{
		DisplayNEErrorMessage("Unable to select bitmap for color replacement");
		FreeClassObject(lpDC);
		return(FALSE);
	}
	else
		AddWinResource

	// replace colors
	for(nX=0;nX<bmp.bmWidth;nX++)
		for(nY=0;nY<bmp.bmHeight;nY++)
		{
			// get color
			clrCmp=lpDC->GetPixel(nX,nY);

			// compare colors
			if(clrCmp==clrSrc)
			{
				// replace color
				lpDC->SetPixelV(nX,nY,
								clrDest);
			}
		}


	// select previous object
	if(lpDC->SelectObject(lpGdiObj))
		RemoveWinResource

	// release dc object
	FreeClassObject(lpDC);

	// ok
	return(TRUE);
}

// IsPathFixed()

BOOL IsPathFixed(LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"IsPathFixed()",
							FALSE);
		return(FALSE);
	}
#endif

	// file info
	SHFILEINFO sfi;

	// set requested attributes
	sfi.dwAttributes=SFGAO_REMOVABLE;

	// get file info
	if(!SHGetFileInfo((LPCTSTR)lpPath,
					  NULL,
					  &sfi,
					  sizeof(sfi),
					  SHGFI_ATTRIBUTES|
					  SHGFI_ATTR_SPECIFIED))
		return(FALSE);

	// check flag
	if(sfi.dwAttributes&SFGAO_REMOVABLE)
		return(FALSE);
	else
		return(TRUE);
}

// GetIDListFromPath()

LPITEMIDLIST GetIDListFromPath(HWND hParentWnd,
							   LPSTR lpPath,
							   BOOL bSilent)
{
#ifdef DEBUG_MODE
	// verify path
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetIDListFromPath()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(hParentWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"GetIDListFromPath()",
							FALSE);
		return(FALSE);
	}
#endif

	// shell folder interface
	IShellFolder* lpShellFolder=NULL;

	// list to return
	LPITEMIDLIST lpID=NULL;

	// bytes eaten
	ULONG nBytesEaten;

	// get shell folder
	if(FAILED(SHGetDesktopFolder(&lpShellFolder)))
	{
		if(!bSilent)
			DisplayNEErrorMessage("Unable to get desktop folder interface.");
		return(FALSE);
	}
	else
		AddCOMResource

	LockGlobalLongTTMsg()

	// convert to wide path
	MakeWideString((LPWSTR)g_lpLongTTMsg,
				   lpPath);

	// get id list
	if(FAILED(lpShellFolder->ParseDisplayName(hParentWnd,
											  NULL,
											  (LPOLESTR)g_lpLongTTMsg,
											  &nBytesEaten,
											  &lpID,
											  NULL)))
	{
		// display error
		if(!bSilent)
		{
			strcpy(g_lpLongTTMsg,lpPath);
			DisplayNEErrorMessage("Unable to get identifier list from path.",
								g_lpLongTTMsg);
		}
	}
	else
		AddMemResource

	UnlockGlobalLongTTMsg()

	// release shell folder
	ReleaseCOMPtr(lpShellFolder);

	// ok
	return(lpID);
}

// SelectPathCallback()

int CALLBACK SelectPathCallback(HWND hWnd,
								UINT uMsg,
								LPARAM lParam,
								LPARAM lData)
{
	// check message
	if(uMsg==BFFM_INITIALIZED)
	{
		// check for id list
		if(lData)
		{
			// set selection
			SendMessage(hWnd,
						BFFM_SETSELECTION,
						FALSE,
						lData);						
		}
	}

	// ok
	return(0);
}

// ResolveShortcut()

HRESULT ResolveShortcut(LPSTR lpShortcutPath,
						LPSTR lpFilePath)
{
	// return value
	HRESULT hRes=E_FAIL;

	// file data
	WIN32_FIND_DATA wfd;

	// clear output string
	lpFilePath[0]=0;

	LockGlobalLongTTMsg()
	
	// convert to wide path
	MakeWideString((LPWSTR)g_lpLongTTMsg,
				   lpShortcutPath);

	// open shortcut file
	hRes=g_lpShellLinkPF->Load((LPCOLESTR)g_lpLongTTMsg,
							   STGM_READ);

	UnlockGlobalLongTTMsg()

	// check return value
	if(SUCCEEDED(hRes))
	{
		// resolve link
		hRes=g_lpShellLink->Resolve(NULL,
									0x04000000L|
									SLR_NO_UI|
									SLR_UPDATE);

		// check return value
		if(SUCCEEDED(hRes))
		{
			// get path
			hRes=g_lpShellLink->GetPath(lpFilePath,
										_MAX_PATH,
										&wfd,
										SLGP_RAWPATH);

			// check return value
			if(SUCCEEDED(hRes))
			{
				// check for path
				if(!strlen(lpFilePath))
				{
					// no good
					hRes=E_FAIL;
				}
			}
		}
	}

	// ok
    return(hRes);
}

// IsLinkToFolder()

BOOL IsLinkToFolder(LPSTR lpShortcutPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpShortcutPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"IsLinkToFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// file info
	SHFILEINFO sfi;

	// reset return value
	BOOL bRet=FALSE;

	LockGlobalLongMsg()

	// resolve shortcut
	if(FAILED(ResolveShortcut(lpShortcutPath,
							  g_lpLongMsg)))
	{
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	// set requested attributes
	sfi.dwAttributes=SFGAO_FOLDER;

	// get file info
	if(SHGetFileInfo((LPCTSTR)g_lpLongMsg,
					 NULL,
					 &sfi,
					 sizeof(sfi),
					 SHGFI_ATTRIBUTES|
					 SHGFI_ATTR_SPECIFIED))
	{
		// check folder flag
		if(sfi.dwAttributes&SFGAO_FOLDER)
		{
			// set return value
			bRet=TRUE;
		}
	}

	UnlockGlobalLongMsg();

	// ok
	return(bRet);
}

// InitToolTips()

BOOL InitToolTips(CToolTipCtrl** lplpToolTipCtrl,
				  CWnd* lpParent)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lplpToolTipCtrl||
	   !lpParent)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"InitToolTips()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpParent->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"InitToolTips()",
							FALSE);
		return(FALSE);
	}
#endif
	
	// create tooltip control
	AllocClassObject((*lplpToolTipCtrl),
					 CToolTipCtrl);

	// verify object
	if(!(*lplpToolTipCtrl))
		return(FALSE);

	// init control
	if(!(*lplpToolTipCtrl)->Create(lpParent,
								   TTS_ALWAYSTIP))
	{
		DisplayErrorMessage("Unable to initialize tooltip control.");
		ReleaseToolTips(lplpToolTipCtrl);
		return(FALSE);
	}

	// enable tooltips
	EnableToolTips(*lplpToolTipCtrl);

	// ok
	return(TRUE);
}

// AddToolTip()

BOOL AddToolTip(CToolTipCtrl* lpToolTipCtrl,
				CWnd* lpWnd,
				LPCSTR lpText)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpToolTipCtrl||
	   !lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"AddToolTip()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"AddToolTip()",
							FALSE);
		return(FALSE);
	}
#endif

	// add tooltip
	if(!lpToolTipCtrl->AddTool(lpWnd,
							   lpText))
	{
		DisplayNEErrorMessage("Unable to add tooltip to control list.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// EnableToolTips()

void EnableToolTips(CToolTipCtrl* lpToolTipCtrl)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpToolTipCtrl)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"EnableToolTips()",
							FALSE);
		return;
	}
#endif

	// enable tooltips
	lpToolTipCtrl->Activate(TRUE);
}

// DisableToolTips()

void DisableToolTips(CToolTipCtrl* lpToolTipCtrl)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpToolTipCtrl)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"DisableToolTips()",
							FALSE);
		return;
	}
#endif

	// disable tooltips
	lpToolTipCtrl->Activate(FALSE);
}

// ReleaseToolTips()

void ReleaseToolTips(CToolTipCtrl** lplpToolTipCtrl)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lplpToolTipCtrl)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ReleaseToolTips()",
							FALSE);
		return;
	}
#endif

	// release interface
	FreeClassObject(*lplpToolTipCtrl);
}

// GetExtensionFromPath()

BOOL GetExtensionFromPath(LPSTR lpPath,
						  LPSTR* lplpExt)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetExtensionFromPath()",
							FALSE);
		return(FALSE);
	}

	// verify pointer
	if(!lplpExt)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"GetExtensionFromPath()",
							FALSE);
		return(FALSE);
	}
#endif

	// pointer to last '.'
	LPSTR lpLastDot=NULL;

	// release existing extension
	FreeMem((LPVOID*)lplpExt);
	
	// check for path
	if(!strlen(lpPath))
		return(FALSE);

	// find last '.'
	lpLastDot=strrchr(lpPath,
					  '.');

	// check string
	if(!lpLastDot)
		return(FALSE);

	// move pointer
	lpLastDot=&lpLastDot[1];

	// check string
	if(!strlen(lpLastDot))
		return(FALSE);

	// allocoate memory for extension
	if(!AllocMem((LPVOID*)lplpExt,
				 strlen(lpLastDot)+1))
		return(FALSE);

	// copy extension
	strcpy((*lplpExt),
		   lpLastDot);

	// convert to lowercase
	strlwr(*lplpExt);
	
	// ok
	return(TRUE);
}

// ClipExtensionFromPath()

BOOL ClipExtensionFromPath(LPSTR lpPath,
						   LPSTR* lplpNewPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"ClipExtensionFromPath()",
							FALSE);
		return(FALSE);
	}

	// verify pointer
	if(!lplpNewPath)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ClipExtensionFromPath()",
							FALSE);
		return(FALSE);
	}
#endif

	// saved byte
	BYTE cSave;

	// pointer to last '.'
	LPSTR lpLastDot=NULL;

	// release any existing string
	FreeMem((LPVOID*)lplpNewPath);
	
	// check for path
	if(!strlen(lpPath))
		return(FALSE);

	// find last '.'
	lpLastDot=strrchr(lpPath,
					  '.');

	// check string
	if(!lpLastDot)
		return(FALSE);

	// save byte
	cSave=lpLastDot[0];

	// clip string
	lpLastDot[0]=0;

	// check string
	if(!strlen(lpPath))
	{
		lpLastDot[0]=cSave;
		return(FALSE);
	}

	// allocoate memory for new path
	if(!AllocMem((LPVOID*)lplpNewPath,
				 strlen(lpPath)+1))
	{
		lpLastDot[0]=cSave;
		return(FALSE);
	}

	// copy clipped path
	strcpy((*lplpNewPath),
		   lpPath);

	// restore byte
	lpLastDot[0]=cSave;
	
	// ok
	return(TRUE);
}

// ProcessPendingMessages()

void ProcessPendingMessages(CWnd* lpWnd)
{
#ifdef DEBUG_MODE
	// verify poiner
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ProcessPendingMessages()",
							FALSE);
		return;
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"ProcessPendingMessages()",
							FALSE);
		return;
	}
#endif

	// message storage
	MSG Msg;

	// retrieve message
	while(PeekMessage(&Msg,
					  NULL,
					  NULL,
					  NULL,
					  PM_REMOVE))
	{
		// process message
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

// MCIWaitForReady()

MCIERROR MCIWaitForReady(MCIDEVICEID wDeviceID)
{
	// status parameters
	MCI_STATUS_PARMS msp;

	// error value
	MCIERROR nErr;
	
	// begin wait
	while(TRUE)
	{
		// set parameters
		msp.dwCallback=NULL;
		msp.dwReturn  =NULL;
		msp.dwItem    =MCI_STATUS_READY;
		msp.dwTrack   =NULL;

		// get status
		nErr=mciSendCommand(wDeviceID,
							MCI_STATUS,
							MCI_STATUS_ITEM|MCI_WAIT,
							(DWORD)&msp);

		// check for error
		if(nErr)
			return(nErr);

		// check ready flag
		if(msp.dwReturn)
			return(NULL);

		// wait a bit
		Sleep(AUDIO_TIMEOUT_BRIEF);
	}
}

// MCIWaitForNotReady()

MCIERROR MCIWaitForNotReady(MCIDEVICEID wDeviceID)
{
	// status parameters
	MCI_STATUS_PARMS msp;

	// error value
	MCIERROR nErr;
	
	// begin wait
	while(TRUE)
	{
		// set parameters
		msp.dwCallback=NULL;
		msp.dwReturn  =NULL;
		msp.dwItem    =MCI_STATUS_READY;
		msp.dwTrack   =NULL;

		// get status
		nErr=mciSendCommand(wDeviceID,
							MCI_STATUS,
							MCI_STATUS_ITEM|MCI_WAIT,
							(DWORD)&msp);

		// check for error
		if(nErr)
			return(nErr);

		// check ready flag
		if(!msp.dwReturn)
			return(NULL);

		// wait a bit
		Sleep(AUDIO_TIMEOUT_BRIEF);
	}
}

// GetHmsStringFromMsVal()

BOOL GetHmsStringFromMsVal(LPSTR lpStr,
						   long lVal)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetHmsStringFromMsInt()",
							FALSE);
		return(FALSE);
	}
#endif

	// hms values
	int nLen;
	int nHr;
	int nMin;
	int nSec;
	
	// digit values
	int nM1,nM2;
	int nS1,nS2;

	// set length
	nLen=(int)lVal;

	// remove milliseconds
	nLen/=1000;

	// get hours
	nHr=nLen/(60*60);

	// remove hours
	nLen-=nHr*(60*60);

	// get minutes
	nMin=nLen/60;

	// get seconds
	nSec=nLen-(nMin*60);

	// get minute digits
	nM1=nMin/10;
	nM2=nMin-(nM1*10);

	// get second digits
	nS1=nSec/10;
	nS2=nSec-(nS1*10);

	// clear string
	lpStr[0]=0;

	// create length string
	if(nHr)
	{
		// output hhh:mm:ss
		sprintf(lpStr,
				"%d:%d%d:%d%d",
				nHr,
				nM1,nM2,
				nS1,nS2);
	}
	else
	{
		// check first minute digit
		if(nM1)
		{
			// output mm:ss
			sprintf(lpStr,
					"%d%d:%d%d",
					nM1,nM2,
					nS1,nS2);
		}
		else
		{
			// output m:ss
			sprintf(lpStr,
					"%d:%d%d",
					nM2,
					nS1,nS2);
		}
	}

	// ok
	return(TRUE);
}

// AutoSetSliderTics()

void AutoSetSliderTics(CSliderCtrl* lpSld,
					   int nMaxTics)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpSld)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"AutoSetSliderTics()",
							FALSE);
		return;
	}

	// verify window
	if(!IsWindow(lpSld->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"AutoSetSliderTics()",
							FALSE);
		return;
	}
#endif

	// check max tics
	if(nMaxTics==0)
	{
		// clear all tics
		lpSld->ClearTics(TRUE);

		// stop here
		return;
	}

	// get min/max values
	int nMinVal=lpSld->GetRangeMin();
	int nMaxVal=lpSld->GetRangeMax();

	// set length
	int nLenVal=nMaxVal-nMinVal;
	
	// set default rate at 1.875 sec
	int nCurRate=1875;

	// current position
	int nCurPos;

	// find optimal rate
	while(TRUE)
	{
		// check rate
		if((nLenVal/nCurRate)<nMaxTics)
		{
			// found it!
			break;
		}
		else
		{
			// double rate
			nCurRate*=2;
		}
	}

	// add tics
	for(nCurPos=nMinVal;nCurPos<nMaxVal;nCurPos+=nCurRate)
		lpSld->SetTic(nCurPos);

	// check rate
	if(nCurRate<2000)
	{
		// set page size
		lpSld->SetPageSize(1000);

		// set line size
		lpSld->SetLineSize(100);
	}
	else
	{
		// set page size
		lpSld->SetPageSize(nCurRate/2);

		// set line size
		lpSld->SetLineSize(nCurRate/20);
	}
}

// BeginWaitCursor()

int BeginWaitCursor(CWnd* lpWnd)
{
	// check counter
	if(g_nWaitCursorCnt==0)
	{
		// begin wait cursor
		g_MainApp.BeginWaitCursor();
	}

	// increment counter
	g_nWaitCursorCnt++;

	// disable window input
	if(lpWnd)
		lpWnd->EnableWindow(FALSE);

	// return counter
	return(g_nWaitCursorCnt);
}

// EndWaitCursor()

int EndWaitCursor(CWnd* lpWnd)
{
	// decrement counter
	g_nWaitCursorCnt--;

	// check counter
	if(g_nWaitCursorCnt<=0)
	{
		// end wait cursor
		g_MainApp.EndWaitCursor();

		// clip value
		g_nWaitCursorCnt=0;
	}

	// enable window input
	if(lpWnd)
		lpWnd->EnableWindow(TRUE);

	// return counter
	return(g_nWaitCursorCnt);
}

// ExecuteExternalApp()

BOOL ExecuteExternalApp(LPTSTR lpCmdLine,
						LPCTSTR lpWorkingDir)
{
	// startup info
	STARTUPINFO si;

	// process information
	PROCESS_INFORMATION pi;
	
	// prepare startup info
	si.cb         =sizeof(STARTUPINFO);
	si.lpReserved =NULL;
	si.lpDesktop  =NULL;
	si.lpTitle    =NULL;
	si.dwFlags    =NULL;
	si.cbReserved2=NULL;
	si.lpReserved2=NULL;

	// create new process
	if(!CreateProcess(NULL,
					  lpCmdLine,
					  NULL,
					  NULL,
					  FALSE,
					  NULL,
					  NULL,
					  lpWorkingDir,
					  &si,
					  &pi))
	{
		DisplayErrorMessage("Unable to start external application:",
							(LPSTR)lpCmdLine,
							TRUE);
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// OpenExternalDoc()

BOOL OpenExternalDoc(LPCTSTR lpFileName,
					 LPCTSTR lpWorkingDir,
					 BOOL bSilent)
{
	// execute shell command
	if(ShellExecute(NULL,
					"open",
					lpFileName,
					NULL,
					lpWorkingDir,
					SW_SHOW)<=(HINSTANCE)32)
	{
		if(!bSilent)
			DisplayErrorMessage("Unable to open external document:",
								(LPSTR)lpFileName,
								FALSE);
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// PrintExternalDoc()

BOOL PrintExternalDoc(LPCTSTR lpFileName,
					  LPCTSTR lpWorkingDir)
{
	// execute shell command
	if(ShellExecute(NULL,
					"print",
					lpFileName,
					NULL,
					lpWorkingDir,
					SW_SHOW)<=(HINSTANCE)32)
	{
		DisplayErrorMessage("Unable to print external document:",
						    (LPSTR)lpFileName,
						    FALSE);
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// ExecuteCommandLine()

BOOL ExecuteCommandLine(LPCTSTR lpExeFile,
						LPCTSTR lpCmdLine,
						LPCTSTR lpWorkingDir)
{
	// command line storage
	LPSTR lpCmd;
		
	// execute shell command
	if(ShellExecute(NULL,
					"open",
					lpExeFile,
					lpCmdLine,
					lpWorkingDir,
					SW_SHOW)<=(HINSTANCE)32)
	{
		// allocate memory for command line
		if(AllocMem((LPVOID*)&lpCmd,
					strlen(lpExeFile)+1+strlen(lpCmdLine)+1))
		{
			// copy exe file
			strcpy(lpCmd,lpExeFile);

			// add ' '
			strcat(lpCmd," ");

			// add command line
			strcat(lpCmd,lpCmdLine);

			// display error message
			DisplayErrorMessage("Unable to execute command line:",
								lpCmd,
								FALSE);

			// free memory
			FreeMem((LPVOID*)&lpCmd);
		}

		// no good
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// SetCurrentScreensaver()

BOOL SetCurrentScreensaver(LPCSTR lpScr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpScr)
	{
		DisplayErrorMessage("Invalid string value.",
							"SetCurrentScreensaver()",
							FALSE);
		return(FALSE);
	}
#endif

	LockGlobalMsg()

	// copy windows path
	if(!GetWindowsDirectory(g_lpMsg,
							_MAX_PATH))
	{
		DisplayErrorMessage("Unable to read Windows directory.",
						    NULL,
						    TRUE);
		UnlockGlobalMsg()
		return(FALSE);
	}

	// append '\'
	strcat(g_lpMsg,
		   "\\");

	// append name
	strcat(g_lpMsg,
		   lpScr);

	// convert to short form
	GetShortPathName(g_lpMsg,
					 g_lpMsg,
					 _MAX_PATH);
	
	// save setting
	if(!WritePrivateProfileString("boot",
								  "SCRNSAVE.EXE",
								  g_lpMsg,
								  "system.ini"))
	{
		DisplayErrorMessage("Unable to set current screensaver.",
						    NULL,
						    TRUE);
		UnlockGlobalMsg()
		return(FALSE);
	}

	UnlockGlobalMsg()
	
	// ok
	return(TRUE);
}

// GetCurrentScreensaver()

BOOL GetCurrentScreensaver(LPSTR lpScr,
						   int nBufferLg)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpScr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetCurrentScreensaver()",
							FALSE);
		return(FALSE);
	}
#endif

	// reset string
	lpScr[0]=0;

	LockGlobalLongMsg()

	// read setting
	if(!GetPrivateProfileString("boot",
								"SCRNSAVE.EXE",
								NULL_STRING,
								g_lpLongMsg,
								_MAX_PATH,
								"system.ini"))
	{
		DisplayNEErrorMessage("Unable to read current screensaver.",
						      NULL,
						      TRUE);
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	// get filename
	if(!GetFilenameFromPath(lpScr,
							nBufferLg,
							g_lpLongMsg))
	{
		DisplayNEErrorMessage("Unable to read screensaver filename.",
						      NULL,
						      TRUE);
		UnlockGlobalLongMsg()
		return(FALSE);
	}
	
	UnlockGlobalLongMsg()

	// ok
	return(TRUE);
}

// OpenScreensaverControlPanel()

BOOL OpenScreensaverControlPanel(void)
{
	// execute control panel/display/screensaver
	if(WinExec("control.exe desk.cpl Display,@ScreenSaver",
			   SW_SHOW)<32)
	{
		DisplayErrorMessage("Unable to open Windows Control Panel.",
						    NULL,
						    FALSE);
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// VerifyDirectXVersion()

BOOL VerifyDirectXVersion(void)
{
	// The file 'dpnhpast.dll' was introducted in DirectX 8.1.
	// Presence of this file verifies that DirectX 8.1 or higher is present.
	
	// load dpnhpast.dll
	HINSTANCE hDpnhPastDll=LoadLibrary("dpnhpast.dll");

	// check handle
	if(!hDpnhPastDll)
	{
		// cannot continue
		return(FALSE);
	}
	else
		AddWinResource;

	// free dpnhpast.dll
	if(FreeLibrary(hDpnhPastDll))
		RemoveWinResource;

	// ok
	return(TRUE);
}

// CExtEdit::SelectAll()

void CExtEdit::SelectAll(void)
{
	// set focus
	SetFocus();

	// select all
	SetSel(0,-1);
}

// OffsetWindow()

BOOL OffsetWindow(CWnd* lpWnd,
				  int nDX,
				  int nDY)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"OffsetWindow()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"OffsetWindow()",
							FALSE);
		return(FALSE);
	}
#endif

	// window position
	CRect rWnd;

	// get client rect
	lpWnd->GetClientRect(&rWnd);

	// convert relative to parent
	lpWnd->MapWindowPoints(lpWnd->GetParent(),
						   &rWnd);

	// set new position
	if(!lpWnd->SetWindowPos(NULL,
							rWnd.left+nDX,
							rWnd.top +nDY,
							0,0,
							SWP_NOZORDER|
							SWP_NOSIZE))
	{
		DisplayNEErrorMessage("Unable to relocate window.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// OffsetDlgCtrl()

BOOL OffsetDlgCtrl(CWnd* lpParent,
				   UINT nCtrlId,
				   int nDX,
				   int nDY)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpParent)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"OffsetDlgCtrl()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpParent->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"OffsetDlgCtrl()",
							FALSE);
		return(FALSE);
	}
#endif

	// pointer to window
	CWnd* lpWnd=NULL;

	// get dialog item
	lpWnd=lpParent->GetDlgItem(nCtrlId);

	// check for object
	if(!lpWnd)
	{
		DisplayNEErrorMessage("Unable to relocate dialog item.");
		return(FALSE);
	}

	// offset window
	return(OffsetWindow(lpWnd,
						nDX,
						nDY));
}

// MaintainMessageQueue()

void MaintainMessageQueue(CWnd* lpWnd,
						  BOOL bPaint)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"MaintainMessageQueue()",
							FALSE);
		return;
	}

	// verify window
	if(!IsWindow(lpWnd->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"MaintainMessageQueue()",
							FALSE);
		return;
	}
#endif

	// message info
	MSG Msg;

	// read message
	if(PeekMessage(&Msg,
				   NULL,
				   (bPaint ? WM_PAINT : NULL),
				   (bPaint ? WM_PAINT : NULL),
				   PM_NOREMOVE))
	{
		// check paint flag
		if(bPaint)
		{
			// process message
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			// do nothing (just keep queue active)
		}
	}

	// check wait cursor
	if(g_nWaitCursorCnt)
		g_MainApp.BeginWaitCursor();
}

// CExtSpinCtrl::OnStyleChanging()

void CExtSpinCtrl::OnStyleChanging(int nStyleType,
								   LPSTYLESTRUCT lpStyleStruct)
{
	// check visibility flag
	if(lpbVisFlag)
	{
		// check visible state
		if(*lpbVisFlag)
		{
			// new state must be visible
			lpStyleStruct->styleNew|=WS_VISIBLE;
		}
		else
		{
			// new state must not be visible
			lpStyleStruct->styleNew&=~WS_VISIBLE;
		}
	}
}

// CExtSpinCtrl::SetVisibilityFlagPtr()

void CExtSpinCtrl::SetVisibilityFlagPtr(LPBOOL lpbPtr)
{
	// copy pointer
	lpbVisFlag=lpbPtr;
}

// SetParentHWnd()

void SetParentHWnd(HWND hWnd)
{
	// copy value
	g_hParentWnd=hWnd;
}

// GetParentCWnd()

CWnd* GetParentCWnd(void)
{
	// check handle
	if(g_hParentWnd==NULL||
	   g_hParentWnd==(HWND)INVALID_HANDLE_VALUE)
		return(NULL);

	// check window
	if(!IsWindow(g_hParentWnd))
		return(NULL);

	// return window
	return(CWnd::FromHandle(g_hParentWnd));
}

#ifdef SHAREWARE_MODE
// GetHDDSerialNumber()

DWORD GetHDDSerialNumber(void)
{
	// set default return value
	DWORD dwRet=NO_OBJECT;

	// counter
	DWORD dwCount;
	
ANTIHACK_7

	LockGlobalMsg()

	// get windows directory
	if(GetWindowsDirectory((LPTSTR)g_lpMsg,
						   _MAX_PATH))
	{
		// truncate directory after first '\'
		for(dwCount=0;dwCount<strlen(g_lpMsg);dwCount++)
			if(g_lpMsg[dwCount]=='\\')
				g_lpMsg[dwCount+1]=0;

		// get volume information
		if(!GetVolumeInformation((LPCSTR)g_lpMsg,
								 NULL,
								 0,
								 &dwRet,
								 NULL,
								 NULL,
								 NULL,
								 0))
		{
ANTIHACK_8
			
			// reset default return value
			DWORD dwRet=NO_OBJECT;
		}
	}

	UnlockGlobalMsg()

	// return value
	return(dwRet);
}

// EncodeTimeStamp()

void EncodeTimeStamp(TIMESTAMP tsSrc,
					 LPSTR lpStr)
{
	// destination timestamp
	TIMESTAMP tsDest;

	// randomize upper 3 bytes of days left
	tsSrc.dwDaysLeft=(tsSrc.dwDaysLeft&0x000000FFL)|(rand()&0xFFFFFF00L);

	// encode source elements
	EncodeDWORD(&tsSrc.dwID);
ANTIHACK_9
	EncodeDWORD(&tsSrc.dwInstTimeLow);
	EncodeDWORD(&tsSrc.dwInstTimeHigh);
ANTIHACK_10
	EncodeDWORD(&tsSrc.dwDaysLeft);

	// cast byte pointers
	LPBYTE lpcSrc=(LPBYTE)&tsSrc;
	LPBYTE lpcDest=(LPBYTE)&tsDest;

	// swap bytes
	lpcDest[0] =lpcSrc[4];
	lpcDest[1] =lpcSrc[0];
	lpcDest[2] =lpcSrc[5];
	lpcDest[3] =lpcSrc[7];
	lpcDest[4] =lpcSrc[11];
ANTIHACK_11
	lpcDest[5] =lpcSrc[6];
	lpcDest[6] =lpcSrc[9];
	lpcDest[7] =lpcSrc[2];
ANTIHACK_12
	lpcDest[8] =lpcSrc[8];
	lpcDest[9] =lpcSrc[1];
	lpcDest[10]=lpcSrc[14];
	lpcDest[11]=lpcSrc[13];
	lpcDest[12]=lpcSrc[3];
	lpcDest[13]=lpcSrc[12];
ANTIHACK_3
	lpcDest[14]=lpcSrc[15];
	lpcDest[15]=lpcSrc[10];

	// encode destination timestamp
	EncodeBytesAsString(lpcDest,
						16,
						lpStr);
}

// DecodeTimeStamp()

TIMESTAMP DecodeTimeStamp(LPSTR lpStr)
{
	// working timestamps
	TIMESTAMP tsSrc;
	TIMESTAMP tsDest;

	// check length of string
	if(strlen(lpStr)!=32)
	{
		// set default timestamp
		tsDest.dwDaysLeft=0;
		tsDest.dwID=NO_OBJECT;
ANTIHACK_4
		tsDest.dwInstTimeHigh=NULL;
		tsDest.dwInstTimeLow=NULL;

		// return timestamp
		return(tsDest);
	}

	// decode source timestamp
	DecodeBytesFromString(lpStr,
						  (LPBYTE)&tsSrc,
						  16);

	// cast byte pointers
	LPBYTE lpcSrc=(LPBYTE)&tsSrc;
	LPBYTE lpcDest=(LPBYTE)&tsDest;

	// swap bytes
	lpcDest[0] =lpcSrc[1];
	lpcDest[1] =lpcSrc[9];
	lpcDest[2] =lpcSrc[7];
	lpcDest[3] =lpcSrc[12];
	lpcDest[4] =lpcSrc[0];
ANTIHACK_5
	lpcDest[5] =lpcSrc[2];
	lpcDest[6] =lpcSrc[5];
	lpcDest[7] =lpcSrc[3];
	lpcDest[8] =lpcSrc[8];
	lpcDest[9] =lpcSrc[6];
_asm // anti-hack
{
	mov eax,1
	cpuid
	mov eax,ebx
}
	lpcDest[10]=lpcSrc[15];
	lpcDest[11]=lpcSrc[4];
	lpcDest[12]=lpcSrc[13];
	lpcDest[13]=lpcSrc[11];
ANTIHACK_6
	lpcDest[14]=lpcSrc[10];
	lpcDest[15]=lpcSrc[14];

	// decode timestamp elements
	DecodeDWORD(&tsDest.dwID);
	DecodeDWORD(&tsDest.dwInstTimeLow);
	DecodeDWORD(&tsDest.dwInstTimeHigh);
	DecodeDWORD(&tsDest.dwDaysLeft);

	// clear upper 3 bytes of days left
	tsDest.dwDaysLeft=(tsDest.dwDaysLeft&0x000000FFL);

	// return destination timestamp
	return(tsDest);
}

// EncodeDWORD()

void EncodeDWORD(LPDWORD lpDW)
{
	// get high/low words
	WORD wHigh=HIWORD(*lpDW);
	WORD wLow =LOWORD(*lpDW);

	// encode bits
	_asm
	{
		//  --> dummy instructions
	
		// copy high/low words
		mov ax,wHigh
		mov bx,wLow
				mov cx,ax
				mov dx,wLow

		// encode bits
		inc ah
				add cx,dx
		dec al
		dec bh
		inc bl
				inc dx
		neg ax
		not bx
				rol dx,7
				ror cl,4
		rol ah,3
		ror al,2
		ror bh,5
				and cx,dx
		rol bl,4
		xchg ah,bl
		xchg ax,bx
				mov dh,cl
		add ax,0x43A6
		sub bx,0xF430

		// store new words
				mov wLow,dx
		mov wHigh,ax
		mov wLow,bx
	}

	// set new dword value
	(*lpDW)=MAKELONG(wLow,wHigh);
}

// DecodeDWORD()

void DecodeDWORD(LPDWORD lpDW)
{
	// get high/low words
	WORD wHigh=HIWORD(*lpDW);
	WORD wLow =LOWORD(*lpDW);

	// decode bits
	_asm
	{
		//  --> dummy instructions

		// copy high/low words
		mov ax,wHigh
		mov bx,wLow
				mov cx,ax

		// decode bits
		add bx,0xF430
				mov dx,ax
		sub ax,0x43A6
		xchg ax,bx
		xchg ah,bl
		ror bl,4
				sub dx,bx
		rol bh,5
		rol al,2
				mov cl,dh
				mov ch,dl
		ror ah,3
		not bx
		neg ax
				inc cx
		dec bl
		inc bh
				dec dx
		inc al
		dec ah

		// store new words
				add cx,ax
		mov wHigh,ax
		mov wLow,bx
	}
	
	// set new dword value
	(*lpDW)=MAKELONG(wLow,wHigh);
}

// EncodeBytesAsString()

void EncodeBytesAsString(LPBYTE lpcBytes,
						 DWORD dwNumBytes,
						 LPSTR lpStr)
{
	// counter
	DWORD dwCount;

	// loop through bytes
	for(dwCount=0;dwCount<dwNumBytes;dwCount++)
	{
		// extract nybbles
		BYTE cNyb1=(lpcBytes[dwCount]   )&0x0F;
		BYTE cNyb2=(lpcBytes[dwCount]>>4)&0x0F;

ANTIHACK_12

		// convert nybbles to bytes
		BYTE cByte1=EncodeNybble(cNyb1);
		BYTE cByte2=EncodeNybble(cNyb2);

		// copy bytes
		lpStr[(dwCount<<1)  ]=cByte1;
		lpStr[(dwCount<<1)+1]=cByte2;
	}

	// place null terminator
	lpStr[dwNumBytes<<1]=0;
}

// DecodeBytesFromString()

void DecodeBytesFromString(LPSTR lpStr,
						   LPBYTE lpcBytes,
						   DWORD dwNumBytes)
{
	// counter
	DWORD dwCount;

	// loop through bytes
	for(dwCount=0;dwCount<dwNumBytes;dwCount++)
	{
		// copy bytes
		BYTE cByte1=lpStr[(dwCount<<1)  ];
		BYTE cByte2=lpStr[(dwCount<<1)+1];

		// extract nybbles
		BYTE cNyb1=DecodeNybble(cByte1);
		BYTE cNyb2=DecodeNybble(cByte2);

ANTIHACK_3
		
		// copy byte
		lpcBytes[dwCount]=cNyb1|(cNyb2<<4);
	}
}

// EncodeNybble()

BYTE EncodeNybble(BYTE cNybble)
{
	// init codes
	InitNybbleCodes();

	// return encoded byte
	return(g_lpNybCode[((cNybble&0x0F)<<2)+(abs(rand())%4)]);
}

// DecodeNybble()

BYTE DecodeNybble(BYTE cByte)
{
	// counter
	DWORD dwCount;

	// init codes
	InitNybbleCodes();

	// search for code
	for(dwCount=0;dwCount<64;dwCount++)
		if(g_lpNybCode[dwCount]==cByte)
			return((BYTE)((dwCount>>2)&0x0F));

ANTIHACK_4

	// problem
	return(NULL);
}

// InitNybbleCodes()

void InitNybbleCodes(void)
{
	// initialized flag
	static BOOL bInit=FALSE;

	// check initialized flag
	if(bInit)
		return;
	else
		ANTIHACK_5

	// set values
	g_lpNybCode[8] ='6';
	g_lpNybCode[9] ='b';
	g_lpNybCode[42]='f';
	g_lpNybCode[12]='q';
	g_lpNybCode[43]='D';
	g_lpNybCode[47]='U';
ANTIHACK_4
	g_lpNybCode[1] ='u';
	g_lpNybCode[20]='d';
	g_lpNybCode[21]='5';
	g_lpNybCode[62]='F';
	g_lpNybCode[44]='a';
	g_lpNybCode[11]='N';
	g_lpNybCode[51]='O';
	g_lpNybCode[26]='Q';
	g_lpNybCode[13]='g';
	g_lpNybCode[49]='0';
	g_lpNybCode[33]='-';
	g_lpNybCode[50]='8';
	g_lpNybCode[35]='Y';
	g_lpNybCode[61]='J';
	g_lpNybCode[40]='C';
	g_lpNybCode[14]='h';
	g_lpNybCode[3] ='M';
	g_lpNybCode[63]='G';
	g_lpNybCode[0] ='w';
	g_lpNybCode[58]='T';
	g_lpNybCode[23]='_';
	g_lpNybCode[30]='p';
	g_lpNybCode[16]='z';
	g_lpNybCode[17]='o';
ANTIHACK_6
ANTIHACK_10
	g_lpNybCode[22]='c';
	g_lpNybCode[55]='S';
	g_lpNybCode[38]='i';
	g_lpNybCode[2] ='v';
	g_lpNybCode[60]='7';
	g_lpNybCode[4] ='y';
	g_lpNybCode[34]='E';
	g_lpNybCode[27]='e';
	g_lpNybCode[41]='k';
	g_lpNybCode[39]='4';
	g_lpNybCode[46]='A';
	g_lpNybCode[32]='I';
	g_lpNybCode[25]='P';
_asm // anti-hack
{
	mov eax,2
	cpuid
	mov eax,edx
}
	g_lpNybCode[48]='r';
	g_lpNybCode[53]='s';
	g_lpNybCode[18]='X';
	g_lpNybCode[37]='x';
	g_lpNybCode[24]='j';
	g_lpNybCode[54]='l';
	g_lpNybCode[28]='H';
	g_lpNybCode[5] ='W';
ANTIHACK_7
	g_lpNybCode[36]='V';
	g_lpNybCode[15]='K';
	g_lpNybCode[45]='R';
	g_lpNybCode[7] ='n';
	g_lpNybCode[31]='3';
	g_lpNybCode[19]='m';
	g_lpNybCode[59]='t';
ANTIHACK_3
	g_lpNybCode[57]='9';
	g_lpNybCode[6] ='1';
	g_lpNybCode[56]='Z';
	g_lpNybCode[10]='L';
	g_lpNybCode[52]='B';
	g_lpNybCode[29]='2';

	// set initialized flag
	bInit=TRUE;

ANTIHACK_8
}
#endif

// SetTimeStampStringToFile()

void SetTimeStampStringToFile(LPSTR lpEnc,
							  LPSTR lpFile)
{
	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// counters
	DWORD dwCount;
	DWORD dwByteCount;

	// bytes written
	DWORD dwBytesWritten;

	// output byte
	BYTE cOut;

	LockGlobalMsg()

	// get windows directory
	if(!GetWindowsDirectory(g_lpMsg,
							_MAX_PATH))
		return;

	// append "\" and filename
	strcat(g_lpMsg,"\\");
	strcat(g_lpMsg,lpFile);

ANTIHACK_5

	// open file
	hFile=CreateFile(g_lpMsg,
					 GENERIC_WRITE,
					 NULL,
					 NULL,
					 CREATE_ALWAYS,
					 NULL,
					 NULL);

	// check handle
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		AddWinResource;

		// reset byte counter
		dwByteCount=0;

		// output 21 random bytes
		for(dwCount=0;dwCount<52;dwCount++)
		{
			// set random output byte
			cOut=(BYTE)(rand()%0xFF);

			// output byte
			WriteFile(hFile,
					  &cOut,
					  1,
					  &dwBytesWritten,
					  NULL);

			// increment byte counter
			dwByteCount++;
		}

		// output string (every 3rd byte)
		for(dwCount=0;dwCount<strlen(lpEnc);dwCount++)
		{
			// set output byte
			cOut=(BYTE)(lpEnc[dwCount]);

			// output byte
			WriteFile(hFile,
					  &cOut,
					  1,
					  &dwBytesWritten,
					  NULL);

			// set random output byte
			cOut=(BYTE)(rand()%0xFF);

			// output byte
			WriteFile(hFile,
					  &cOut,
					  1,
					  &dwBytesWritten,
					  NULL);

			// set random output byte
			cOut=(BYTE)(rand()%0xFF);

ANTIHACK_7

			// output byte
			WriteFile(hFile,
					  &cOut,
					  1,
					  &dwBytesWritten,
					  NULL);

			// increment byte counter
			dwByteCount+=3;
		}

		// output remaining bytes
		while(dwByteCount<256)
		{
			// set random output byte
			cOut=(BYTE)(rand()%0xFF);

			// output byte
			WriteFile(hFile,
					  &cOut,
					  1,
					  &dwBytesWritten,
					  NULL);

			// increment byte counter
			dwByteCount++;
		}

ANTIHACK_4

		// close file
		if(CloseHandle(hFile))
			RemoveWinResource;
	}

	UnlockGlobalMsg()
}
							 
#ifdef SHAREWARE_MODE
// GetTimeStampStringFromFile()

void GetTimeStampStringFromFile(LPSTR lpEnc,
								LPSTR lpFile)
{
	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// counters
	DWORD dwCount;

	// bytes read
	DWORD dwBytesRead;

	// set terminator in case of error
	lpEnc[0]=NULL;

	LockGlobalMsg()

	// get windows directory
	if(!GetWindowsDirectory(g_lpMsg,
							_MAX_PATH))
		return;

	// append "\" and filename
	strcat(g_lpMsg,"\\");
	strcat(g_lpMsg,lpFile);
	
	// open file
	hFile=CreateFile(g_lpMsg,
					 GENERIC_READ,
					 NULL,
					 NULL,
					 OPEN_EXISTING,
					 NULL,
					 NULL);

	// check handle
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		AddWinResource;

		// set file pointer
		if(SetFilePointer(hFile,
						  21,
						  NULL,
						  FILE_BEGIN)==NO_OBJECT)
		{
			if(CloseHandle(hFile))
				RemoveWinResource;
			return;
		}
		
		// read string (every 3rd byte)
		for(dwCount=0;dwCount<32;dwCount++)
		{
			// read 3 bytes
			ReadFile(hFile,
					 g_lpMsg,
					 3,
					 &dwBytesRead,
					 NULL);

			// check for error
			if(dwBytesRead!=3)
			{
				if(CloseHandle(hFile))
					RemoveWinResource;
				return;
			}

			// copy first byte
			lpEnc[dwCount]=g_lpMsg[0];

			// set null terminator
			lpEnc[dwCount+1]=NULL;
		}

		// close file
		if(CloseHandle(hFile))
			RemoveWinResource;
	}

	UnlockGlobalMsg()
}
#endif

// GetStringDivision()

LPSTR GetStringDivision(LPSTR lpStr,
					    DWORD dwIndex)
{
	ANTIHACK_8
		
	// position pointer
	DWORD dwPos=0;
	
	// loop until specified string
	while(dwIndex)
	{
		// find next string
		dwPos+=(DWORD)(strlen(&lpStr[dwPos])+1);
		
		// decrement index
		dwIndex--;
	}

	// return pointer
	return(&lpStr[dwPos]);
}

// LockApplication()

BOOL LockApplication(LPCSTR lpID,
					 LPSTR lpWndTitle,
					 LPSTR lpWndClass,
					 BOOL bClose)
{
	// note: this function has been re-written as follows:
	//       no mutex-object lock is used. the function only
	//       checks for the requested window. if the window
	//       is found, it is either closed or activiated,
	//       depending on the bClose flag.

#ifdef DEBUG_MODE
	// verify strings
	if(!lpWndTitle||
	   !lpWndClass)
	{
		DisplayErrorMessage("Invalid string value.",
							"LockApplication()",
							FALSE);
		return(FALSE);
	}
#endif

	// window object
	CWnd* lpWnd=NULL;

	// find window
	lpWnd=CWnd::FindWindow((LPCSTR)lpWndClass,
						   (LPCSTR)lpWndTitle);

	// check window
	if(lpWnd==NULL)
		return(TRUE);

	// check close flag
	if(bClose)
	{
		// close other window
		lpWnd->SendMessage(WM_CLOSE);

		// ok
		return(TRUE);
	}
	else
	{
		// set other to foreground
		lpWnd->SetForegroundWindow();

		// close this app
		return(FALSE);
	}
}

// UnlockApplication()

void UnlockApplication(void)
{
	// see comments under LockApplication()
}

// KeepRectsOnScreen()

void KeepRectsOnScreen(CRect* lprParent,
					   CRect* lprChild)
{
#ifdef DEBUG_MODE
	// verify parent
	if(lprParent==NULL)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"KeepRectOnScreen()",
							FALSE);
		return;
	}
#endif

	// offset values
	int nXOfs;
	int nYOfs;

	// get screen limits
	int nScrX=GetSystemMetrics(SM_CXFULLSCREEN)-1;
	int nScrY=GetSystemMetrics(SM_CYFULLSCREEN)-1;

	// check left side
	if(lprParent->left<0)
	{
		// compute offsets
		nXOfs=-lprParent->left;
		nYOfs=0;

		// offset parent
		lprParent->OffsetRect(nXOfs,nYOfs);

		// offset child
		if(lprChild)
			lprChild->OffsetRect(nXOfs,nYOfs);
	}

	// check top
	if(lprParent->top<0)
	{
		// compute offsets
		nXOfs=0;
		nYOfs=-lprParent->top;

		// offset parent
		lprParent->OffsetRect(nXOfs,nYOfs);

		// offset child
		if(lprChild)
			lprChild->OffsetRect(nXOfs,nYOfs);
	}

	// check right side
	if(lprParent->right>nScrX)
	{
		// compute offsets
		nXOfs=nScrX-lprParent->right;
		nYOfs=0;

		// offset parent
		lprParent->OffsetRect(nXOfs,nYOfs);

		// offset child
		if(lprChild)
			lprChild->OffsetRect(nXOfs,nYOfs);
	}

	// check bottom
	if(lprParent->bottom>nScrY)
	{
		// compute offsets
		nXOfs=0;
		nYOfs=nScrY-lprParent->bottom;

		// offset parent
		lprParent->OffsetRect(nXOfs,nYOfs);

		// offset child
		if(lprChild)
			lprChild->OffsetRect(nXOfs,nYOfs);
	}
}

// CMainApp::GetSaverExecInfo()

BOOL CMainApp::GetSaverExecInfo(void)
{
	// counter
	DWORD dwCount;

	// init values
	sei.cFlag     =NULL;
	sei.nID       =NULL;
	sei.dwUserData=NULL;

	LockGlobalMsg()

	// copy command line
	strcpy(g_lpMsg,
		   m_lpCmdLine);

	// cast pointer to cmd line
	LPSTR lpCmdLine=g_lpMsg;

	// check command line
	if(strlen(lpCmdLine)==0)
	{
		UnlockGlobalMsg()

		// ok, but no settings
		return(TRUE);
	}

	// check for WaveBreak special commands
	if(lpCmdLine[0]=='w'&&
	   lpCmdLine[1]=='~')
		sei.cFlag='w';

	// check for full-screen mode
	if(lpCmdLine[0]=='s'||
	   lpCmdLine[0]=='S'||
	   lpCmdLine[1]=='s'||
	   lpCmdLine[1]=='S')
		sei.cFlag='s';

	// check for configure mode
	if(lpCmdLine[0]=='c'||
	   lpCmdLine[0]=='C'||
	   lpCmdLine[1]=='c'||
	   lpCmdLine[1]=='C')
		sei.cFlag='c';
	
	// check for preview mode
	if(lpCmdLine[0]=='p'||
	   lpCmdLine[0]=='P'||
	   lpCmdLine[1]=='p'||
	   lpCmdLine[1]=='P')
		sei.cFlag='p';
	
	// check for password mode
	if(lpCmdLine[0]=='a'||
	   lpCmdLine[0]=='A'||
	   lpCmdLine[1]=='a'||
	   lpCmdLine[1]=='A')
		sei.cFlag='a';

	// check flag
	if(sei.cFlag)
	{
		// convert non-numerical characters to '0'
		for(dwCount=0;dwCount<strlen(lpCmdLine);dwCount++)
			if(lpCmdLine[dwCount]<'0'||
			   lpCmdLine[dwCount]>'9')
				lpCmdLine[dwCount]='0';

		// extract id/handle
		sei.nID=atoi(lpCmdLine);
	}

	UnlockGlobalMsg();	
	
	// ok
	return(TRUE);
}

// GetNearestPointInWnd()

void GetNearestPointInWnd(CPoint* lpPt,
						  CWnd* lpWnd,
						  int nBorder)
{
	// window rect
	CRect rWnd;

	// check window
	if(lpWnd)
		if(IsWindow(lpWnd->m_hWnd))
		{
			// get window rect
			lpWnd->GetWindowRect(&rWnd);

			// adjust for border
			rWnd.left  +=nBorder;
			rWnd.top   +=nBorder;
			rWnd.right -=nBorder;
			rWnd.bottom-=nBorder;

			// fix for small windows
			if(rWnd.right<rWnd.left)
				rWnd.left=rWnd.right=(rWnd.left+rWnd.right)>>1;
			if(rWnd.bottom<rWnd.top)
				rWnd.top=rWnd.bottom=(rWnd.top+rWnd.bottom)>>1;

			// clip point
			if(lpPt->x<rWnd.left)
				lpPt->x=rWnd.left;
			if(lpPt->x>rWnd.right)
				lpPt->x=rWnd.right;
			if(lpPt->y<rWnd.top)
				lpPt->y=rWnd.top;
			if(lpPt->y>rWnd.bottom)
				lpPt->y=rWnd.bottom;
		}
}

// eof //

// Copyright 2006 WaveBreak Software
