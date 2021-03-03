// Copyright 2006 WaveBreak Software

// main.h -- system core header

// flags //

// omit from release version
//#define DEBUG_MODE

// shareware mode flag
//#define SHAREWARE_MODE

// check processes flag
//#define CHECK_PROCESSES

// check exit flag
//#define CHECK_EXIT

// non-essential errors flag
//#define SHOW_NE_ERRORS

// defines //

// use strict compiling
#define STRICT
// exclude unnecessary code
#define VC_EXTRALEAN

// includes //

// mfc includes
#include<afxwin.h>
#include<afxext.h>
#include<afxdisp.h>
#include<afxdtctl.h>
#include<afxcmn.h>
#include<afxpriv.h>

// system includes
#include<atlbase.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<tlhelp32.h>
#include<commdlg.h>
#include<cderr.h>
#include<vfw.h>
#include<imagehlp.h>
#include<direct.h>
#include<math.h>

// directx includes 
#include<dxerr8.h>
#include<dmusici.h>

// application includes
#include"errlog.h"
#include"htmlhelp\\htmlhelp.h"

// constants //

#define NO_OBJECT 0xFFFFFFFFL

// null string value
#define NULL_STRING ""

// size of long msg strings
#define LONG_MSG_SIZE (1024*4)

// message box checkbox id
#define IDC_XMSGBOXCHK 0xBFFF

// min/max integer values
#define MIN_INT 0x80000000L
#define MAX_INT 0x7FFFFFFFL

// browse-for-folder updates
#define BIF_NEWDIALOGSTYLE    0x0040
#define BIF_NONEWFOLDERBUTTON 0x0200

// 100-nanosecond intervals per day
#define CNSEC_PER_DAY 0xC92A69C000I64

// structures //

typedef struct tag_PROCWND
{
	// window handle
	HWND hWnd;
	// process info
	LPPROCESS_INFORMATION lpPI;
} _PROCWND,*_LPPROCWND;

#ifdef SHAREWARE_MODE
typedef struct tagTIMESTAMP
{
	// persistent id
	DWORD dwID;
	// install time
	DWORD dwInstTimeLow;
	DWORD dwInstTimeHigh;
	// days left
	DWORD dwDaysLeft;
} TIMESTAMP,*LPTIMESTAMP;
#endif

typedef struct tag_SAVEREXECINFO
{
	// flag
	char cFlag;
	// id/handle
	int nID;
	// user data
	DWORD dwUserData;
} SAVEREXECINFO,*LPSAVEREXECINFO;

// data types //

typedef unsigned __int64 QWORD;

// classes //

class CMainApp:public CWinApp
{
public:
	// system overrides
	virtual BOOL InitInstance(void);

	// execution info methods
	BOOL GetSaverExecInfo(void);

	// init/shutdown methods
	BOOL PrimaryInit(void);
	void PrimaryShutdown(void);

	// saver execution info
	SAVEREXECINFO sei;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtButton:public CButton
{
public:
	// constructor overrides
	CExtButton():CButton() {}
	CExtButton(UINT nID);

	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// system overrides
	virtual LRESULT WindowProc(UINT message,
							   WPARAM wParam,
							   LPARAM lParam);

	// enable/disable functions
	void Enable(void);
	void Disable(void);

	// spcl. bitmap button functions
	void SetSpclBitmapButton(BOOL bEnable,
							 CBitmap** lplpEnabled,
							 CBitmap** lplpDisabled);
	
	// control id
	UINT nCtrlId;
	// spcl. button flag
	BOOL bSpclBtn;
	// enabled flag
	BOOL bEnabled;
	// button bitmap pointers
	CBitmap** lplpEnBmp;
	CBitmap** lplpDisBmp;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtStatic:public CStatic
{
public:
	// constructor overrides
	CExtStatic():CStatic() {}
	CExtStatic(UINT nID);

	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// enable/disable functions
	void Enable(void);
	void Disable(void);
	
	// control id
	UINT nCtrlId;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtSpinCtrl:public CSpinButtonCtrl
{
public:
	// constructor override
	CExtSpinCtrl(UINT nID,
				 UINT nSndID=NULL);

	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnLButtonUp(UINT nFlags,
							 CPoint point);
	afx_msg void OnStyleChanging(int nStyleType,
								 LPSTYLESTRUCT lpStyleStruct);

	// enable/disable functions
	void Enable(void);
	void Disable(void);

	// misc. methods
	void SetVisibilityFlagPtr(LPBOOL lpbPtr);
	
	// control id
	UINT nCtrlId;
	// sound id
	UINT nSoundId;
	// pointer to visibility flag
	LPBOOL lpbVisFlag;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtEdit:public CEdit
{
public:
	// constructor/destructor override
	CExtEdit(UINT nID);
	~CExtEdit();

	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd,
							 UINT nHitTest,
							 UINT message);
	afx_msg void OnLButtonUp(UINT nFlags,
							 CPoint point);
	afx_msg void OnTextChange(void);
	afx_msg void OnFocusLost(void);

	// enable/disable functions
	void Enable(void);
	void Disable(void);

	// initialization methods
	void SetNoCursor(BOOL bFlag=TRUE);
	void SetNumLimits(int nMin=-1,
					  int nMax=-1,
					  int* lpnDef=NULL);
	void SetParentPropPage(CPropertyPage* lpPage);
	BOOL AddSpinControl(CWnd* lpParentWnd,
						UINT nID,
						UINT nSndID=NULL,
						BOOL bHorz=FALSE,
						BOOL bWrap=FALSE,
						BOOL bArrowKeys=TRUE,
						BOOL bAutoUpdate=TRUE,
						BOOL nNoThouSep=TRUE,
						BOOL bAlignRight=TRUE,
						LPBOOL lpbVisFlag=NULL);

	// misc. functions
	void SelectAll(void);

	// control id
	UINT nCtrlId;
	// no-cursor flag
	BOOL bNoCursor;
	// numerical limits
	int nMinVal;
	int nMaxVal;
	// pointer to default limit
	int* lpnDefVal;
	// parent windows
	CPropertyPage* lpParentPropPage;
	// spin control
	CExtSpinCtrl* lpSpinCtrl;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtComboBox:public CComboBox
{
public:
	// constructor overrides
	CExtComboBox():CComboBox() {}
	CExtComboBox(UINT nID);

	// system overrides
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// enable/disable functions
	void Enable(void);
	void Disable(void);

	// misc. functions
	int SelectStringExact(LPSTR lpFind);
	
	// control id
	UINT nCtrlId;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtRichEditCtrl:public CRichEditCtrl
{
public:
	// constructor/destructor overrides
	CExtRichEditCtrl(UINT nID);
	~CExtRichEditCtrl();

	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnHScroll(UINT nSBCode,
						   UINT nPos,
						   CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode,
						   UINT nPos,
						   CScrollBar* pScrollBar);
	afx_msg void OnPaint(void);

	// enable/disable functions
	void Enable(void);
	void Disable(void);

	// bitmap functions
	BOOL DrawBitmaps(int nXOfs=0,
					 int nYOfs=0);
	BOOL DrawBitmap(DWORD dwIndex,
					int nXOfs=0,
					int nYOfs=0);
	BOOL AddBitmap(int nX,
				   int nY,
				   CBitmap* lpBmp,
				   int nBdrOfs=0,
				   COLORREF clrBdr=NULL,
				   COLORREF clrBkg=NULL,
				   COLORREF clrShadow=NULL);
	void RemoveBitmaps(void);

	// misc. functions
	void ScrollToTop(void);
	
	// control id
	UINT nCtrlId;
	// bitmap counter
	DWORD dwNumBmp;
	// bitmap array
	CBitmap** lplpBmp;
	// position arrays
	int* lpnX;
	int* lpnY;
	// size arrays
	int* lpnSX;
	int* lpnSY;
	// border offset array
	int* lpnBdrOfs;
	// border color arrays
	COLORREF* lpclrBdr;
	COLORREF* lpclrBkg;
	COLORREF* lpclrShadow;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtFileDialog:public CFileDialog
{
public:
	// constructor
	CExtFileDialog(BOOL bOpenFileDialog,
				   LPCTSTR lpszDefExt=NULL,
				   LPCTSTR lpszFileName=NULL,
				   DWORD dwFlags=OFN_HIDEREADONLY|
								 OFN_OVERWRITEPROMPT,
				   LPCTSTR lpszFilter=NULL,
				   CWnd* pParentWnd=NULL):CFileDialog(bOpenFileDialog,
													  lpszDefExt,
													  lpszFileName,
													  dwFlags,
													  lpszFilter,
													  pParentWnd) {}

	// system overrides
	virtual BOOL OnFileNameOK(void);

	// file checking functions
	void SetCheckFileCallback(BOOL (*lpfnCallback)(void)=NULL);

	// check-file callback
	BOOL (*CheckFileCallback)(void);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtHeaderCtrl:public CHeaderCtrl
{
public:
	// constructor
	CExtHeaderCtrl();

	// message handlers
	afx_msg BOOL OnSetCursor(CWnd* pWnd,
							 UINT nHitTest,
							 UINT message);
	afx_msg void OnBeginTrack(NMHDR* pNMHDR,
							  LRESULT* pResult);

	// misc. functions
	void SetNoResizeCursor(BOOL bFlag=TRUE);

	// no-resize cursor flag
	BOOL bNoResizeCursor;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtMessageBox:public CWnd
{
public:
	// constructor
	CExtMessageBox();

	// message handlers
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnMsgBoxInit(WPARAM wParam,
								 LPARAM lParam);
	afx_msg LRESULT OnMsgBoxClose(WPARAM wParam,
								  LPARAM lParam);
	
	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);

    // message box override
	int MessageBox(LPCTSTR lpszText,
				   LPCTSTR lpszCaption=NULL,
				   UINT nType=MB_OK);

    // checkbox funtions
	void SetCheck(BOOL bFlag);
    BOOL GetCheck();

	// check state
	BOOL bBtnChecked;
	// extra controls
	CStatic* lpSeparator;
	CButton* lpNoShowCbx;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtHotKeyCtrl:public CHotKeyCtrl
{
public:
	// constructor overrides
	CExtHotKeyCtrl(UINT nID);

	// system overrides
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// enable/disable functions
	void Enable(void);
	void Disable(void);
	
	// control id
	UINT nCtrlId;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtSliderCtrl:public CSliderCtrl
{
public:
	// constructor overrides
	CExtSliderCtrl(UINT nID);
	CExtSliderCtrl():CSliderCtrl() {}

	// system overrides
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// enable/disable functions
	void Enable(void);
	void Disable(void);
	
	// control id
	UINT nCtrlId;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

// main application include //

#include"source.h"

// main application instance (defines program entry point) //

extern CMainApp g_MainApp;

// globals //

// handle to application window
extern HWND g_hWnd;
// message strings
extern char g_lpMsg[];
extern char* g_lpTTMsg;
extern char* g_lpErrorMsg;
extern char* g_lpLongMsg;
extern char* g_lpLongTTMsg;
// com memory allocator
extern IMalloc* g_lpCoMalloc;
// resource counters
extern DWORD g_dwNumCOMRes;
extern DWORD g_dwNumWinRes;
extern DWORD g_dwNumMemRes;
extern DWORD g_dwNumClassRes;
// popup menus
extern CMenu* g_lpPopupMenu;
extern CMenu* g_lpPopupSubmenu;
// highlight window data
extern HWND g_hFlashWnd;
extern DWORD g_dwFlashCnt;
extern UINT g_nFlashId;
#ifdef DEBUG_MODE
// message locking flags
extern BOOL _g_bMsgLocked;
extern BOOL _g_bLongMsgLocked;
extern BOOL _g_bTTMsgLocked;
extern BOOL _g_bLongTTMsgLocked;
extern BOOL _g_bErrorMsgLocked;
#endif
// focus swap data
extern HWND g_hFSwapWnd1;
extern HWND g_hFSwapWnd2;
extern DWORD g_dwFSwapCnt;
extern UINT g_nFSwapId;
// shell link interfaces
extern IShellLink* g_lpShellLink;
extern IPersistFile* g_lpShellLinkPF;
// wait-cursor counter
extern int g_nWaitCursorCnt;
// anti-hacking values
extern DWORD g_dwAHVal1;
extern DWORD g_dwAHVal2;
extern DWORD g_dwAHVal3;
extern DWORD g_dwAHVal4;
#ifdef SHAREWARE_MODE
// nybble codes
extern char g_lpNybCode[64];
#endif
// duplication mutex
extern HANDLE g_hMutex;
// error log
extern CErrorLog* g_lpErrorLog;
// parent window
extern HWND g_hParentWnd;

// prototypes //

// error handling functions

extern void DisplayErrorMessage(LPSTR lpError,
								LPSTR lpSolution=NULL,
								BOOL bExtInfo=TRUE,
								BOOL bFatal=FALSE);

extern void DisplayNEErrorMessage(LPSTR lpError,
								  LPSTR lpSolution=NULL,
								  BOOL bExtInfo=TRUE,
								  BOOL bFatal=FALSE);

extern void DisplayFatalErrorMessage(LPSTR lpError,
									 LPSTR lpSolution=NULL,
									 BOOL bExtInfo=TRUE);

extern void DisplayDXErrorMessage(LPSTR lpError,
								  LPSTR lpSolution=NULL,
								  HRESULT hError=NULL,
								  BOOL bFatal=FALSE);

extern void DisplayNEDXErrorMessage(LPSTR lpError,
								    LPSTR lpSolution=NULL,
								    HRESULT hError=NULL,
								    BOOL bFatal=FALSE);

extern void DisplayFatalDXErrorMessage(LPSTR lpError,
									   LPSTR lpSolution=NULL,
									   HRESULT hError=NULL);

extern void DisplayInfoMessage(LPSTR lpError);

extern int DisplayMessageBox(HWND hWnd,
							 LPSTR lpText,
							 LPSTR lpCaption,
							 UINT uType);

extern int DisplayOptMessageBox(LPCSTR lpText,
								LPCSTR lpCaption,
								UINT uType,
								LPCSTR lpRegKey);

// popup menu functions

extern BOOL InitPopupMenu(void);

extern BOOL AddPopupMenuItem(LPCTSTR lpszNewItem,
							 UINT nIDNewItem=NULL);

extern BOOL AddPopupMenuHelpItem(UINT nIDNewItem);

extern BOOL AddPopupMenuSeparator(void);

extern BOOL CheckPopupMenuItem(UINT nIDItem,
							   BOOL bChecked=TRUE);

extern BOOL EnablePopupMenuItem(UINT nIDItem,
							    BOOL bEnabled=TRUE);

extern void ExecPopupMenu(POINT pCur);

extern BOOL InsertPopupSubmenu(LPCTSTR lpszNewItem);

extern BOOL AddPopupSubmenuItem(LPCTSTR lpszNewItem,
							    UINT nIDNewItem=NULL);

extern BOOL AddPopupSubmenuHelpItem(UINT nIDNewItem);

extern BOOL AddPopupSubmenuSeparator(void);

extern BOOL CheckPopupSubmenuItem(UINT nIDItem,
								  BOOL bChecked=TRUE);

extern BOOL EnablePopupSubmenuItem(UINT nIDItem,
								   BOOL bEnabled=TRUE);

// bitmap functions

extern CBitmap* CreateBitmapFromIcon(HICON hIcon,
									 COLORREF hBackground=RGB(255,255,255));

extern BOOL ResizeBitmap(CBitmap** lplpDestBmp,
						 CBitmap* lpSrcBmp,
						 int nWidth,
						 int nHeight);

extern BOOL LoadBitmap(CBitmap** lplpBmp,
					   UINT nID);

/* does not work (retained for reference)
extern BOOL OutputRtfBitmap(LPSTR lpRtf,
							CBitmap* lpBmp);*/

// option handling functions

extern BOOL LoadOptionString(LPCSTR lpKey,
							 LPSTR lpVal,
							 BOOL bIsGlobal=FALSE);

extern int LoadOptionInt(LPCSTR lpKey,
						 int nMin,
						 int nMax,
						 int nDef,
						 BOOL bIsGlobal=FALSE);

extern BOOL SaveOptionString(LPCSTR lpKey,
							 LPSTR lpVal,
							 BOOL bIsGlobal=FALSE);

extern BOOL SaveOptionInt(LPCSTR lpKey,
						  int nVal,
						  BOOL bIsGlobal=FALSE);

// tooltip control functions

BOOL InitToolTips(CToolTipCtrl** lplpToolTipCtrl,
				  CWnd* lpParent);

BOOL AddToolTip(CToolTipCtrl* lpToolTipCtrl,
				CWnd* lpWnd,
				LPCSTR lpText);

void EnableToolTips(CToolTipCtrl* lpToolTipCtrl);

void DisableToolTips(CToolTipCtrl* lpToolTipCtrl);

void ReleaseToolTips(CToolTipCtrl** lplpToolTipCtrl);

// memory manipulation functions

extern void SwapPtrs(LPVOID* lplpPtr1,
					 LPVOID* lplpPtr2);

extern BOOL AllocMem(LPVOID* lplpPtr,
					 DWORD dwSize);

extern BOOL ExpandMem(LPVOID* lplpPtr,
	 			      DWORD dwSize,
 				      DWORD dwExpAmt);

extern BOOL CompressMem(LPVOID* lplpPtr,
	 			        DWORD dwSize);

extern void FreeMem(LPVOID* lplpPtr);

// object init/shutdown functions

extern BOOL VerifyClassObject(LPVOID lpPtr);

#ifdef DEBUG_MODE
extern void DisplayResourceUsage(void);
#endif

extern void ConfirmResourcesReleased(void);

extern void ForceImmediateExit(void);

extern void SetParentHWnd(HWND hWnd);

extern CWnd* GetParentCWnd(void);

extern BOOL CaptureDlgControl(CWnd* lpParentWnd,
							  CWnd* lpObjectWnd,
							  UINT nCtrlID,
							  BOOL bSilentFail=FALSE);

extern BOOL CreateExtButton(CExtButton** lplpBtn,
							UINT nID);

extern BOOL LockApplication(LPCSTR lpID,
							LPSTR lpWndTitle,
							LPSTR lpWndClass,
							BOOL bClose);

extern void UnlockApplication(void);

// window manipulation functions

extern BOOL PostCommand(CWnd* lpWnd,
						int nCmd);

extern BOOL SendCommand(CWnd* lpWnd,
						int nCmd);

extern BOOL PostCommand(HWND hWnd,
						int nCmd);

extern BOOL SendCommand(HWND hWnd,
						int nCmd);

extern BOOL IsPointInWindow(CPoint* lpPos,
							CWnd* lpWnd);

extern BOOL IsPointInRect(CPoint* lpPos,
						  LPRECT lpRect);

extern BOOL CenterWindow(HWND hWnd,
						 HWND hRefWnd=(HWND)INVALID_HANDLE_VALUE);

extern void HighlightWindow(HWND hWnd);

extern void CALLBACK FlashTimerProc(HWND hWnd,
									UINT uMsg,
									UINT idEvent,
									DWORD dwTime);

extern BOOL DisableSysMenuClose(CWnd* lpWnd);

extern void PerformFocusSwap(CWnd* lpWnd1,
							 CWnd* lpWnd2,
							 UINT nDelay,
							 DWORD dwNumSwaps);

extern void CALLBACK SwapTimerProc(HWND hWnd,
								   UINT uMsg,
								   UINT idEvent,
								   DWORD dwTime);

extern BOOL GetDlgCtrlWnd(CWnd** lplpWnd,
						  CWnd* lpParent,
						  UINT nCtrlId);

extern BOOL FindChildWindow(CWnd** lplpWnd,
							CWnd* lpParent,
							LPSTR lpClass,
							LPSTR lpTitle,
							UINT nID=NULL);

extern CWnd* FindSiblingWindow(CWnd* lpWnd,
							   LPSTR lpClass,
							   LPSTR lpTitle,
							   UINT nID=NULL);

extern BOOL GetSafeParentWnd(CWnd** lplpParent,
							 CWnd* lpWnd);

extern BOOL MoveCtrlToPH(CWnd* lpSrcWnd,
						 CWnd* lpParent,
						 UINT nDestCtrlId,
						 int nDX=0,
						 int nDY=0);

extern BOOL GetWindowOffset(CWnd* lpWnd1,
							CWnd* lpWnd2,
							int* lpnDX,
							int* lpnDY);

extern BOOL ResizeClient(CWnd* lpWnd,
						 int nWd,
						 int nHt);

extern void ProcessPendingMessages(CWnd* lpWnd);

extern int BeginWaitCursor(CWnd* lpWnd=NULL);

extern int EndWaitCursor(CWnd* lpWnd=NULL);

extern BOOL OffsetWindow(CWnd* lpWnd,
						 int nDX,
						 int nDY);

extern BOOL OffsetDlgCtrl(CWnd* lpParent,
						  UINT nCtrlId,
						  int nDX,
						  int nDY);

extern void MaintainMessageQueue(CWnd* lpWnd,
								 BOOL bPaint);

// outside process functions

extern BOOL ExecuteExternalApp(LPTSTR lpCmdLine,
							   LPPROCESS_INFORMATION lpPI=NULL,
							   BOOL bHideWnd=FALSE,
							   LPCTSTR lpWorkingDir=NULL);

extern HWND GetWndFromProcess(LPPROCESS_INFORMATION lpPI);

extern BOOL CALLBACK GetWndFromProcessCallback(HWND hWnd,
											   LPARAM lParam);

extern BOOL ExecuteExternalApp(LPTSTR lpCmdLine,
							   LPCTSTR lpWorkingDir=NULL);

extern BOOL OpenExternalDoc(LPCTSTR lpFileName,
							LPCTSTR lpWorkingDir=NULL,
							BOOL bSilent=FALSE);

extern BOOL PrintExternalDoc(LPCTSTR lpFileName,
							 LPCTSTR lpWorkingDir=NULL);

extern BOOL ExecuteCommandLine(LPCTSTR lpExeFile,
							   LPCTSTR lpCmdLine,
							   LPCTSTR lpWorkingDir=NULL);

// message string protection functions

#ifdef DEBUG_MODE
extern void LockGlobalMessageString(void);

extern void UnlockGlobalMessageString(void);

extern void LockGlobalLongMessageString(void);

extern void UnlockGlobalLongMessageString(void);

extern void LockGlobalTTMessageString(void);

extern void UnlockGlobalTTMessageString(void);

extern void LockGlobalLongTTMessageString(void);

extern void UnlockGlobalLongTTMessageString(void);

extern void LockGlobalErrorMessageString(void);

extern void UnlockGlobalErrorMessageString(void);
#endif

// file manipulation functions

extern BOOL GetFilenameFromPath(LPSTR lpFile,
								DWORD dwBufferLg,
								LPSTR lpPath);

extern BOOL DoesFileExist(LPSTR lpFile);

extern BOOL ReadFile(HANDLE hFile,
					 LPVOID lpBuffer,
					 DWORD dwBytes,
					 BOOL bSilent=FALSE);

extern BOOL WriteFile(HANDLE hFile,
					  LPVOID lpBuffer,
					  DWORD dwBytes,
					  BOOL bSilent=FALSE);

extern BOOL MoveFilePointer(HANDLE hFile,
							long lDistToMove,
							BOOL bSilent=FALSE,
							DWORD dwMoveMethod=FILE_CURRENT);

extern BOOL ReadFileEnc(HANDLE hFile,
					    LPVOID lpBuffer,
					    DWORD dwBytes,
					    BOOL bSilent=FALSE);

extern BOOL WriteFileEnc(HANDLE hFile,
					     LPVOID lpBuffer,
					     DWORD dwBytes,
					     BOOL bSilent=FALSE);

extern BOOL DoesPathExist(LPSTR lpPath);

extern BOOL SelectPathDlg(CWnd* lpParentWnd,
						  LPSTR lpPath,
						  LPSTR lpStartPath,
						  LPCSTR lpTitle=NULL);

extern BOOL IsPathFixed(LPSTR lpPath);

extern LPITEMIDLIST GetIDListFromPath(HWND hParentWnd,
									  LPSTR lpPath,
									  BOOL bSilent=FALSE);

extern int CALLBACK SelectPathCallback(HWND hWnd,
									   UINT uMsg,
									   LPARAM lParam,
									   LPARAM lData);

extern HRESULT ResolveShortcut(LPSTR lpShortcutPath,
							   LPSTR lpFilePath);

extern BOOL IsLinkToFolder(LPSTR lpShortcutPath);

extern BOOL GetExtensionFromPath(LPSTR lpPath,
								 LPSTR* lplpExt);

extern BOOL ClipExtensionFromPath(LPSTR lpPath,
								  LPSTR* lplpNewPath);

// bitmap manipulation functions

extern BOOL ReplaceBmpColor(CBitmap* lpBmp,
							COLORREF clrDest,
							COLORREF clrSrc);

extern COLORREF DarkenColor(COLORREF clrSrc,
							DWORD dwNumBits);

extern COLORREF LightenColor(COLORREF clrSrc,
							 DWORD dwNumBits);

// audio playback functions

extern MCIERROR MCIWaitForReady(MCIDEVICEID wDeviceID);

extern MCIERROR MCIWaitForNotReady(MCIDEVICEID wDeviceID);

extern BOOL GetHmsStringFromMsVal(LPSTR lpStr,
								  long lVal);

extern void AutoSetSliderTics(CSliderCtrl* lpSld,
							  int nMaxTics);

// screensaver manipulation functions

extern BOOL SetCurrentScreensaver(LPCSTR lpScr);

extern BOOL GetCurrentScreensaver(LPSTR lpScr,
								  int nBufferLg);

extern BOOL OpenScreensaverControlPanel(void);

// trial time limit functions

#ifdef SHAREWARE_MODE
extern DWORD GetHDDSerialNumber(void);

extern void EncodeTimeStamp(TIMESTAMP tsSrc,
							LPSTR lpStr);

extern TIMESTAMP DecodeTimeStamp(LPSTR lpStr);

extern void EncodeDWORD(LPDWORD lpDW);

extern void DecodeDWORD(LPDWORD lpDW);

extern BYTE EncodeNybble(BYTE cNybble);

extern BYTE DecodeNybble(BYTE cByte);

extern void InitNybbleCodes(void);

extern void EncodeBytesAsString(LPBYTE lpcBytes,
								DWORD dwNumBytes,
								LPSTR lpStr);

extern void DecodeBytesFromString(LPSTR lpStr,
								  LPBYTE lpcBytes,
								  DWORD dwNumBytes);

extern void GetTimeStampStringFromFile(LPSTR lpEnc,
									   LPSTR lpFile);
							 
extern void GetTimeStampStringFromDataFile(LPSTR lpEnc,
										   LPSTR lpFile);
#endif

extern void SetTimeStampStringToFile(LPSTR lpEnc,
									 LPSTR lpFile);
							 
// misc. functions

extern LPSTR GetStringDivision(LPSTR lpStr,
							   DWORD dwIndex);
extern BOOL MakeSafeRegString(LPSTR lpPath,
							  LPSTR* lplpRegPath);

extern void AddCharsToString(LPSTR lpStr,
							 char cChar,
							 int nNum);

extern LPSTR ByteToHexString(BYTE cByte);

extern BOOL ClipboardHasData(void);

extern void CorrectRTFNewLines(LPSTR lpStr);

extern BOOL VerifyDirectXVersion(void);

extern void KeepRectsOnScreen(CRect* lprParent,
							  CRect* lprChild=NULL);

extern void GetNearestPointInWnd(CPoint* lpPt,
								 CWnd* lpWnd,
								 int nBorder=0);

// macros //

#define AddCOMResource   { g_dwNumCOMRes++; }
#define AddWinResource   { g_dwNumWinRes++; }
#define AddMemResource   { g_dwNumMemRes++; }
#define AddClassResource { g_dwNumClassRes++; }

#define AddCOMResources(n) { g_dwNumCOMRes+=n; }

#define RemoveCOMResource   { g_dwNumCOMRes--; }
#define RemoveWinResource   { g_dwNumWinRes--; }
#define RemoveMemResource   { g_dwNumMemRes--; }
#define RemoveClassResource { g_dwNumClassRes--; }

#define ReleaseCOMPtr(a) { if(a) { a->Release(); a=NULL; RemoveCOMResource } }

#define AllocClassObject(a,b)   { a=new b; if(VerifyClassObject((LPVOID)(a))) AddClassResource }
#define FreeClassObject(a)      { if(a) { delete a; a=NULL; RemoveClassResource } }

#define InitStruct(a) { ZeroMemory(&a,sizeof(a)); }

#define MakeWideString(d,s) { MultiByteToWideChar(CP_ACP,MB_PRECOMPOSED,s,-1,d,_MAX_PATH); }

#ifdef DEBUG_MODE
	#define LockGlobalMsg()         LockGlobalMessageString();
	#define UnlockGlobalMsg()       UnlockGlobalMessageString();
	#define LockGlobalLongMsg()     LockGlobalLongMessageString();
	#define UnlockGlobalLongMsg()   UnlockGlobalLongMessageString();
	#define LockGlobalTTMsg()       LockGlobalTTMessageString();
	#define UnlockGlobalTTMsg()     UnlockGlobalTTMessageString();
	#define LockGlobalLongTTMsg()   LockGlobalLongTTMessageString();
	#define UnlockGlobalLongTTMsg() UnlockGlobalLongTTMessageString();
	#define LockGlobalErrorMsg()    LockGlobalErrorMessageString();
	#define UnlockGlobalErrorMsg()  UnlockGlobalErrorMessageString();
#else
	#define LockGlobalMsg()         {}
	#define UnlockGlobalMsg()       {}
	#define LockGlobalLongMsg()     {}
	#define UnlockGlobalLongMsg()   {}
	#define LockGlobalTTMsg()       {}
	#define UnlockGlobalTTMsg()     {}
	#define LockGlobalLongTTMsg()   {}
	#define UnlockGlobalLongTTMsg() {}
	#define LockGlobalErrorMsg()    {}
	#define UnlockGlobalErrorMsg()  {}
#endif

#define AllocBitmap(p) { AllocClassObject(p,CBitmap); if(!p) return(FALSE); }

#define IsKeyDown(a) (GetAsyncKeyState(a)&0x8000)

#define LoggingErrors (g_lpErrorLog ? g_lpErrorLog->IsInit() : FALSE)

// anti-hacking macros

typedef BOOL (WINAPI *ISDEBUGGERPRESENT) (void);

#define ANTIHACK_1  { HINSTANCE hKernel32Dll=LoadLibrary("kernel32.dll"); \
					if(!hKernel32Dll) return(FALSE); else AddWinResource; \
					ISDEBUGGERPRESENT IsDebuggerPresent=(ISDEBUGGERPRESENT)GetProcAddress(hKernel32Dll,"IsDebuggerPresent"); \
					g_dwAHVal3=NULL; \
					if(IsDebuggerPresent) if(IsDebuggerPresent()) g_dwAHVal3=NO_OBJECT; \
					if(FreeLibrary(hKernel32Dll)) RemoveWinResource; }
#define ANTIHACK_2  MapFileAndCheckSum("prosaver.scr",&g_dwAHVal4,&g_dwAHVal2);
#define ANTIHACK_3  g_dwAHVal1=(DWORD)(rand()%0xFFFF00FF)|((g_dwAHVal4&0xFF)<<8);
#define ANTIHACK_4  g_dwAHVal3&=g_dwAHVal1;
#define ANTIHACK_5  g_dwAHVal4++;
#define ANTIHACK_6  g_dwAHVal3=!g_dwAHVal1;;
#define ANTIHACK_7  g_dwAHVal2=0xFF00FF;;
#define ANTIHACK_8  g_dwAHVal3=g_dwAHVal2%17;
#define ANTIHACK_9  g_dwAHVal1=g_dwAHVal3;
#define ANTIHACK_10 g_dwAHVal2=g_dwAHVal1&0xFFFF0000;
#define ANTIHACK_11 g_dwAHVal3=g_dwAHVal4&0x0000FFFF;
#define ANTIHACK_12 g_dwAHVal4=g_dwAHVal2&g_dwAHVal3;

// eof //

// Copyright 2006 WaveBreak Software
