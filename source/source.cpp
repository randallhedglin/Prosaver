// Copyright 2006 WaveBreak Software

// source.cpp -- application core

// includes //

#include"main.h"

// message maps //

BEGIN_MESSAGE_MAP(CMainPropSheet,CPropertySheet)
	ON_MESSAGE(MCIWNDM_NOTIFYMODE,OnMCINotifyMode)
	ON_MESSAGE(MCIWNDM_NOTIFYPOS, OnMCINotifyPos)
	ON_BN_CLICKED(IDC_GHELPBTN,OnGHelpBtn)
	ON_BN_CLICKED(IDC_ABOUTBTN,OnAboutBtn)
	ON_BN_CLICKED(IDC_PREFSBTN,OnPrefsBtn)
	ON_BN_CLICKED(IDC_PURCHBTN,OnPurchBtn)
	ON_MESSAGE(WM_HELP,  OnWmHelp)
	ON_MESSAGE(WM_HOTKEY,OnWmHotkey)
	ON_WM_SYSCOLORCHANGE()
	ON_WM_DEVMODECHANGE()
	ON_WM_WININICHANGE()
	ON_WM_SHOWWINDOW()
	ON_WM_CONTEXTMENU()
	ON_WM_SYSCOMMAND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDefButton,CExtButton)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CExtDialog,CDialog)
	ON_BN_CLICKED(IDC_APPLY,OnApply)
	ON_WM_CONTEXTMENU()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CPlaylistCtrl,CListCtrl)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA,0,0xFFFF,OnTTNeedText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW,0,0xFFFF,OnTTNeedText)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,  OnCustomDraw)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED,OnItemChanged)
	ON_NOTIFY_REFLECT(NM_RCLICK,      OnRtClick)
	ON_NOTIFY_REFLECT(NM_CLICK,       OnClick)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CHistoryComboBox,CExtComboBox)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA,0,0xFFFF,OnTTNeedText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW,0,0xFFFF,OnTTNeedText)
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CFileListCtrl,CListCtrl)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA,0,0xFFFF,OnTTNeedText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW,0,0xFFFF,OnTTNeedText)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,  OnCustomDraw)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED,OnItemChanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK,      OnDblClick)
	ON_NOTIFY_REFLECT(NM_RCLICK,      OnRtClick)
	ON_NOTIFY_REFLECT(NM_CLICK,       OnClick)
	ON_WM_CONTEXTMENU()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CFolderCtrlButton,CExtButton)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CPreferencesDlg,CExtDialog)
	ON_BN_CLICKED(IDC_SAVERLISTDETCHK,OnSaverListDetChkClk)
	ON_BN_CLICKED(IDC_PREFSHELPBTN,   OnHelpBtnClk)
	ON_MESSAGE(WM_HELP,OnWmHelp)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSplashWnd,CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAboutDlg,CExtDialog)
	ON_BN_CLICKED(IDC_VIEWLICBTN,   OnLicenseBtnClk)
	ON_BN_CLICKED(IDC_VIEWREADMEBTN,OnReadMeBtnClk)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CPurchDlg,CExtDialog)
	ON_BN_CLICKED(IDC_ORDERBTN,   OnOrderBtnClk)
	ON_BN_CLICKED(IDC_MAILFORMBTN,OnMailFormBtnClk)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CContextHelpWnd,CWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CWelcomeScrnDlg,CExtDialog)
	ON_BN_CLICKED(IDC_SHOWTUTORIALBTN,OnOK)
	ON_BN_CLICKED(IDC_CLOSEWNDBTN,    OnCancel)
END_MESSAGE_MAP()

// globals //

// main property sheet
CMainPropSheet* g_lpMainSheet=NULL;
// sort images
CBitmap* g_lpSortUp=NULL;
CBitmap* g_lpSortDn=NULL;
CBitmap* g_lpSortNa=NULL;
// null-icon image
CBitmap* g_lpNullIcon=NULL;
// first-run flag
BOOL g_bFirstRun=TRUE;
// options
BOOL g_bPlaySFX=TRUE;
BOOL g_bShowToolTips=TRUE;
// default buttons
CDefButton* g_lpDefOKBtn=NULL;
CDefButton* g_lpDefCancelBtn=NULL;
CDefButton* g_lpDefApplyBtn=NULL;
// global apply buttons
CExtButton* g_lpApplyBtn=NULL;
CExtButton* g_lpSubApplyBtn=NULL;
// misc. buttons
CExtButton* g_lpGHelpBtn=NULL;
CExtButton* g_lpAboutBtn=NULL;
CExtButton* g_lpPrefsBtn=NULL;
CExtButton* g_lpPurchBtn=NULL;
// file dialog boxes
CExtFileDialog* g_lpFileOpenDlg=NULL;
CExtFileDialog* g_lpFileSaveDlg=NULL;
// playlist sort images
CBitmap* g_lpPListUpBmp=NULL;
CBitmap* g_lpPListDownBmp=NULL;
CBitmap* g_lpPListTopBmp=NULL;
CBitmap* g_lpPListBottomBmp=NULL;
CBitmap* g_lpPListUpBmpGr=NULL;
CBitmap* g_lpPListDownBmpGr=NULL;
CBitmap* g_lpPListTopBmpGr=NULL;
CBitmap* g_lpPListBottomBmpGr=NULL;
// last file list selection flag
BOOL g_bLastFileSelFlag=FALSE;
// overlay icons
CImageList* g_lpOverlayIcons=NULL;
// navigation images
CBitmap* g_lpNavBackBmp=NULL;
CBitmap* g_lpNavBackBmpGr=NULL;
CBitmap* g_lpNavUpBmp=NULL;
CBitmap* g_lpNavUpBmpGr=NULL;
// tooltip controls
CToolTipCtrl* g_lpMainToolTip=NULL;
// playback control images
CBitmap* g_lpPlayBmp=NULL;
CBitmap* g_lpPauseBmp=NULL;
CBitmap* g_lpStopBmp=NULL;
CBitmap* g_lpFullRewBmp=NULL;
CBitmap* g_lpRewBmp=NULL;
CBitmap* g_lpFwdBmp=NULL;
// playback control images (grayed)
CBitmap* g_lpPlayBmpGr=NULL;
CBitmap* g_lpPauseBmpGr=NULL;
CBitmap* g_lpStopBmpGr=NULL;
CBitmap* g_lpFullRewBmpGr=NULL;
CBitmap* g_lpRewBmpGr=NULL;
CBitmap* g_lpFwdBmpGr=NULL;
// splash screen flag
BOOL g_bSplashScreen=FALSE;
// preferences dialog
CPreferencesDlg* g_lpPrefsDlg=NULL;
// preference checkboxes
CExtButton* g_lpSplashScreenChk=NULL;
CExtButton* g_lpPlaySFXChk=NULL;
CExtButton* g_lpTooltipsChk=NULL;
CExtButton* g_lpSaverListDetChk=NULL;
CExtButton* g_lpRatingImagesChk=NULL;
CExtButton* g_lpSaverListPopupChk=NULL;
CExtButton* g_lpPlaylistPopupChk=NULL;
// preferences help button
CExtButton* g_lpPrefsHelpBtn=NULL;
// splash screen data
CSplashWnd* g_lpSplashWnd=NULL;
CBitmap* g_lpSplashBmp=NULL;
DWORD g_dwSplashTime=0;
// about dialog
CAboutDlg* g_lpAboutDlg=NULL;
// about box bitmaps
CBitmap* g_lpAboutBmp=NULL;
CBitmap* g_lpWBSLogoBmp=NULL;
CBitmap* g_lpASPLogoBmp=NULL;
// about box controls
CExtStatic* g_lpPSIconBox=NULL;
CExtStatic* g_lpPSTitleTxt=NULL;
CExtStatic* g_lpWBSLinkBox=NULL;
CExtStatic* g_lpASPLinkBox=NULL;
CExtButton* g_lpLicenseBtn=NULL;
CExtButton* g_lpReadMeBtn=NULL;
// purchase dialog
CPurchDlg* g_lpPurchDlg=NULL;
// purchase bitmaps
CBitmap* g_lpCCards1Bmp=NULL;
CBitmap* g_lpCCards2Bmp=NULL;
CBitmap* g_lpPSBuyBmp=NULL;
// purchase controls
CExtStatic* g_lpTrialDaysTxt=NULL;
CExtStatic* g_lpCCards1Box=NULL;
CExtStatic* g_lpCCards2Box=NULL;
CExtStatic* g_lpPSBuyBox=NULL;
CExtButton* g_lpOrderBtn=NULL;
CExtButton* g_lpMailFormBtn=NULL;
// default cursors
HCURSOR g_hArrowCur=(HCURSOR)INVALID_HANDLE_VALUE;
HCURSOR g_hHandCur=(HCURSOR)INVALID_HANDLE_VALUE;
// install path
LPSTR g_lpInstPath=NULL;
#ifdef SHAREWARE_MODE
// trial period data
DWORD g_dwTrialDays=0;
UINT g_nTrialDaysTimerID=0;
BOOL g_bTrialTextOn=FALSE;
#endif
// allow-screensaver flag
BOOL g_bAllowWinSaver=FALSE;
// saver-app init flag
BOOL g_bSaverAppInit=FALSE;
// closing flag
BOOL g_bClosing=FALSE;
// context help window
CContextHelpWnd* g_lpContextHelpWnd=NULL;

// functions //

// ApplicationName()

LPCSTR ApplicationName(void)
{
ANTIHACK_5

	// return name
	return("ProSaver");
}

// ApplicationLongName()

LPCSTR ApplicationLongName(void)
{
	// return name
	return("ProSaver Screensaver Manager");
}

// ApplicationID()

LPCSTR ApplicationID(int nAlt)
{
	// check alternate index
	switch(nAlt)
	{
	// check index & return id
	case(APID_NORMAL):   return("35C85175-7E86-43FF-B3B8-08A2539F102B");
	case(APID_VERSION):  return("08A2539F-102B-B3B8-43FF-7E8635C85175-10");
	case(APID_MINIPREV): return("35C85175-7E86-43FF-B3B8-08A2539F102B-PRV");
	case(APID_DEFSVR):   return("35C85175-7E86-43FF-B3B8-08A2539F102B-DEF");
	case(APID_RUNPS):    return("35C85175-7E86-43FF-B3B8-08A2539F102B-RUN");
	case(APID_TSRMODE):  return("35C85175-7E86-43FF-B3B8-08A2539F102B-TSR");
	
	// not found
	default:
#ifdef DEBUG_MODE
		DisplayInfoMessage("Invalid alternate ID index!");
#endif
ANTIHACK_7
		return("35C85175-7E86-43FF-B3B8-08A2539F102B-INV");
	}
}

// ApplicationIcon()

LPCSTR ApplicationIcon(void)
{
	// return icon resource
	return(MAKEINTRESOURCE(IDI_MAINICON));
}

// ApplicationRegistryPath()

LPCSTR ApplicationRegistryPath(void)
{
	// return path
	return("Software\\ProSaver\\");
}

// InitMainSheet()

BOOL InitMainSheet(BOOL bPurchOnly)
{
////////////////////////////////////////
// MISCELLANEOUS ///////////////////////
////////////////////////////////////////

	// check purchase flag
	if(!bPurchOnly)
	{
		LockGlobalMsg()

		// copy application name
		strcpy(g_lpMsg,
			   ApplicationLongName());

#ifdef SHAREWARE_MODE
		// add trial version
		strcat(g_lpMsg,
			   " (Trial Version)");
#endif

		// lock application
		if(!LockApplication(ApplicationID(APID_NORMAL),
							g_lpMsg,
							"#32770",
							FALSE))
		{
			UnlockGlobalMsg()
			return(FALSE);
		}

		UnlockGlobalMsg()

#ifdef DEBUG_MODE
		// check process list
		CheckProcessList();
#endif

		// check for first-run
		if(LoadOptionInt("Misc_InitFlag",
						 0,
						 -1,
						 (int)0x12345678L)!=0x12345678L)
		{
			// reset flag
			g_bFirstRun=FALSE;
		}
	}

	// load preferences
	if(!LoadPreferences())
		return(FALSE);

	// keep tsr running
	if(!IsTSRActive())
		RestartTSR();

ANTIHACK_1

	// check purchase flag
	if(!bPurchOnly)
	{
		// init splash screen
		if(!InitSplashScreen())
			return(FALSE);
	}

#ifdef SHAREWARE_MODE
	// get days left
	g_dwTrialDays=GetTrialDaysRemaining();
#else
	// reset leftover timestamps
	ResetTimeStamps();
#endif

	// check purchase flag
	if(!bPurchOnly)
	{
		// init saver hook
		if(!InitSaverHookProc())
			return(FALSE);
	}

ANTIHACK_12

	// load default cursors
	if(!InitDefCursors())
		return(FALSE);

	// check purchase flag
	if(!bPurchOnly)
	{
		// create audio temp file
		if(!CreateAudioTempFile())
		{
			DisplayErrorMessage("Unable to create temporary audio data file.");
			return(FALSE);
		}
	}

////////////////////////////////////////
// COMMON DIALOGS //////////////////////
////////////////////////////////////////

	// check purchase flag
	if(!bPurchOnly)
	{
		// create open file dialog
		AllocClassObject(g_lpFileOpenDlg,
						 CExtFileDialog(TRUE));

		// check new object
		if(!g_lpFileOpenDlg)
			return(FALSE);

		// create save file dialog
		AllocClassObject(g_lpFileSaveDlg,
						 CExtFileDialog(FALSE));

		// check new object
		if(!g_lpFileSaveDlg)
			return(FALSE);
	}

////////////////////////////////////////
// DEFAULT BUTTONS /////////////////////
////////////////////////////////////////

ANTIHACK_2

	// check purchase flag
	if(!bPurchOnly)
	{
		// create default button
		AllocClassObject(g_lpDefOKBtn,
						 CDefButton(IDC_DEFOKBTN));

		// check new object
		if(!g_lpDefOKBtn)
			return(FALSE);

		// create default button
		AllocClassObject(g_lpDefCancelBtn,
						 CDefButton(IDC_DEFCANCELBTN));

		// check new object
		if(!g_lpDefCancelBtn)
			return(FALSE);

		// create default button
		AllocClassObject(g_lpDefApplyBtn,
						 CDefButton(IDC_DEFAPPLYBTN));

		// check new object
		if(!g_lpDefApplyBtn)
			return(FALSE);

		// create general help button
		if(!CreateExtButton(&g_lpGHelpBtn,
							IDC_GHELPBTN))
			return(FALSE);

		// create about button
		if(!CreateExtButton(&g_lpAboutBtn,
							IDC_ABOUTBTN))
			return(FALSE);

		// create preferences button
		if(!CreateExtButton(&g_lpPrefsBtn,
							IDC_PREFSBTN))
			return(FALSE);

		// create purchase button
		if(!CreateExtButton(&g_lpPurchBtn,
							IDC_PURCHBTN))
			return(FALSE);
	}

////////////////////////////////////////
// PROPERTY PAGES //////////////////////
////////////////////////////////////////

ANTIHACK_3

	// check purchase flag
	if(!bPurchOnly)
	{
		// create property page
		AllocClassObject(g_lpSaverPage,
						 CSaverPage(IDD_MAINDLG_SAVERS));

		// check new object
		if(!g_lpSaverPage)
			return(FALSE);

		// create property page
		AllocClassObject(g_lpPlaybackPage,
						 CPlaybackPage(IDD_MAINDLG_PLAYBACK));

		// check new object
		if(!g_lpPlaybackPage)
			return(FALSE);

		// create property sheet
		AllocClassObject(g_lpMainSheet,
						 CMainPropSheet(ApplicationLongName(),
										GetParentCWnd()));

		// check new object
		if(!g_lpMainSheet)
			return(FALSE);

#ifdef SHAREWARE_MODE
		LockGlobalMsg()

		// copy application name
		strcpy(g_lpMsg,
			   ApplicationLongName());

		// add trial version
		strcat(g_lpMsg,
			   " (Trial Version)");

		// set prop sheet title
		g_lpMainSheet->SetTitle(g_lpMsg);

		UnlockGlobalMsg()
#endif

		// enable stacked tabs
		g_lpMainSheet->EnableStackedTabs(TRUE);

		// add pages to sheet
		g_lpMainSheet->AddPage(g_lpSaverPage);
		g_lpMainSheet->AddPage(g_lpPlaybackPage);

		// set allow-screensaver flag
		g_bAllowWinSaver=TRUE;
	}

////////////////////////////////////////
// SCREENSAVER PAGE ////////////////////
////////////////////////////////////////

ANTIHACK_4

	// check purchase flag
	if(!bPurchOnly)
	{
		// create sort images
		if(!CreateSortImages())
			return(FALSE);

		// create playlist button images
		if(!CreatePlaylistBtnImages())
			return(FALSE);

		// create null-icon image
		if(!CreateNullIconImage())
			return(FALSE);

		// load themes
		if(!LoadThemes())
			return(FALSE);

		// load saver info
		if(!LoadScreensaverInfo())
			return(FALSE);

		// create clear selection button
		if(!CreateExtButton(&g_lpClearSelBtn,
							IDC_CLEARSELBTN))
			return(FALSE);

		// create add saver button
		if(!CreateExtButton(&g_lpAddSaverBtn,
							IDC_ADDSAVERBTN))
			return(FALSE);

		// load rating bitmap
		if(!LoadBitmap(&g_lpRatingBmp,
					   IDB_RATINGS))
			return(FALSE);

		// load dim rating bitmap
		if(!LoadBitmap(&g_lpDimRatingBmp,
					   IDB_DIMRATINGS))
			return(FALSE);

		// create saver info box
		AllocClassObject(g_lpSaverInfoBox,
						 CSaverInfoBox(IDC_SAVERINFO));

		// check new object
		if(!g_lpSaverInfoBox)
			return(FALSE);

		// create saver settings button
		if(!CreateExtButton(&g_lpSaverSettingsBtn,
							IDC_SETTINGSBTN))
			return(FALSE);

		// create preview saver button
		if(!CreateExtButton(&g_lpPreviewSaverBtn,
							IDC_PREVIEWBTN))
			return(FALSE);

		// create edit saver button
		if(!CreateExtButton(&g_lpEditSaverInfoBtn,
							IDC_EDITINFOBTN))
			return(FALSE);

		// init saver preview window
		if(!InitSaverPreviewWnd())
			return(FALSE);

		// create mini-preview button
		if(!CreateExtButton(&g_lpMiniPreviewChk,
							IDC_SHOWPREVIEWCHK))
			return(FALSE);

		// create saver playlist
		AllocClassObject(g_lpSaverPlaylist,
						 CSaverPlaylist);

		// check new object
		if(!g_lpSaverPlaylist)
			return(FALSE);

		// set id value
		g_lpSaverPlaylist->SetCtrlIds(IDC_CURRPLIST,
									  IDC_CURRPLISTHEAD);

		// create saver playlist header
		AllocClassObject(g_lpSaverPlaylistHdr,
						 CExtHeaderCtrl);

		// check new object
		if(!g_lpSaverPlaylistHdr)
			return(FALSE);

		// create playlist sort box
		AllocClassObject(g_lpSaverSortBox,
						 CSaverSortBox(IDC_PLISTSORTCBX));

		// check new object
		if(!g_lpSaverSortBox)
			return(FALSE);

		// create playlist up button
		if(!CreateExtButton(&g_lpPListUpBtn,
							IDC_PLISTUPBTN))
			return(FALSE);

		// create playlist down button
		if(!CreateExtButton(&g_lpPListDownBtn,
							IDC_PLISTDOWNBTN))
			return(FALSE);

		// create playlist top button
		if(!CreateExtButton(&g_lpPListTopBtn,
							IDC_PLISTTOPBTN))
			return(FALSE);

		// create playlist bottom button
		if(!CreateExtButton(&g_lpPListBottomBtn,
							IDC_PLISTBOTTOMBTN))
			return(FALSE);

		// create playlist delete button
		if(!CreateExtButton(&g_lpPListDeleteBtn,
							IDC_PLISTDELBTN))
			return(FALSE);

		// create playlist clear button
		if(!CreateExtButton(&g_lpPListClearBtn,
							IDC_PLISTCLRBTN))
			return(FALSE);

		// create playlist save button
		if(!CreateExtButton(&g_lpPListSaveBtn,
							IDC_PLISTSAVEBTN))
			return(FALSE);

		// create playlist load button
		if(!CreateExtButton(&g_lpPListLoadBtn,
							IDC_PLISTLOADBTN))
			return(FALSE);
	}

////////////////////////////////////////
// PLAYBACK PAGE ///////////////////////
////////////////////////////////////////

ANTIHACK_5

	// check purchase flag
	if(!bPurchOnly)
	{
		// create one-saver radio button
		if(!CreateExtButton(&g_lpOneSaverRad,
							IDC_ONESVRRAD))
			return(FALSE);

		// create multi-saver radio button
		if(!CreateExtButton(&g_lpMultiSaverRad,
							IDC_MULTISVRRAD))
			return(FALSE);

		// create show-saver static
		AllocClassObject(g_lpShowSaverTxt,
						 CExtStatic(IDC_SHOWSVRTXT));

		// check new object
		if(!g_lpShowSaverTxt)
			return(FALSE);

		// create show-saver edit box
		AllocClassObject(g_lpShowSaverEdit,
						 CExtEdit(IDC_SHOWSVREDT));

		// check new object
		if(!g_lpShowSaverEdit)
			return(FALSE);

		// create show-saver-minutes static
		AllocClassObject(g_lpShowSaverMinTxt,
						 CExtStatic(IDC_SHOWSVRMINTXT));

		// check new object
		if(!g_lpShowSaverMinTxt)
			return(FALSE);

		// create saver-cycle radio button
		if(!CreateExtButton(&g_lpSaverCycleRad,
							IDC_SVRCYCLERAD))
			return(FALSE);

		// create saver-shuffle radio button
		if(!CreateExtButton(&g_lpSaverShuffleRad,
							IDC_SVRSHUFFLERAD))
			return(FALSE);

		// create enable-hotkeys checkbox
		if(!CreateExtButton(&g_lpEnableHotkeysChk,
							IDC_ENABLEHKEYSCBX))
			return(FALSE);

		// create start-saver text
		AllocClassObject(g_lpStartSaverTxt,
						 CExtStatic(IDC_STARTSVRTXT));

		// check new object
		if(!g_lpStartSaverTxt)
			return(FALSE);

		// create start-saver hotkey
		AllocClassObject(g_lpStartSaverHky,
						 CExtHotKeyCtrl(IDC_STARTSVRHKY));

		// check new object
		if(!g_lpStartSaverHky)
			return(FALSE);

		// create skip-saver text
		AllocClassObject(g_lpSkipSaverTxt,
						 CExtStatic(IDC_SKIPSVRTXT));

		// check new object
		if(!g_lpSkipSaverTxt)
			return(FALSE);

		// create skip-saver hotkey
		AllocClassObject(g_lpSkipSaverHky,
						 CExtHotKeyCtrl(IDC_SKIPSVRHKY));

		// check new object
		if(!g_lpSkipSaverHky)
			return(FALSE);

		// create open-prosaver text
		AllocClassObject(g_lpOpenPSTxt,
						 CExtStatic(IDC_OPENPSTXT));

		// check new object
		if(!g_lpOpenPSTxt)
			return(FALSE);

		// create open-prosaver hotkey
		AllocClassObject(g_lpOpenPSHky,
						 CExtHotKeyCtrl(IDC_OPENPSHKY));

		// check new object
		if(!g_lpOpenPSHky)
			return(FALSE);

		// create clear-screen checkbox
		if(!CreateExtButton(&g_lpClearScreenChk,
							IDC_CLRSCREENCBX))
			return(FALSE);

		// create no-music checkbox
		if(!CreateExtButton(&g_lpNoMusicChk,
							IDC_NOMUSICCBX))
			return(FALSE);

		// create open-themes pushbutton
		if(!CreateExtButton(&g_lpOpenThemesBtn,
							IDC_OPENTHEMESBTN))
			return(FALSE);

		// create open-music pushbutton
		if(!CreateExtButton(&g_lpOpenMusicBtn,
							IDC_OPENAUDIOBTN))
			return(FALSE);

		// create advanced-warning static
		AllocClassObject(g_lpAdvWarningTxt,
						 CExtEdit(IDC_ADVWARNTXT));

		// check new object
		if(!g_lpAdvWarningTxt)
			return(FALSE);

		// create show-advanced pushbutton
		if(!CreateExtButton(&g_lpShowAdvancedBtn,
							IDC_SHOWADVBTN))
			return(FALSE);

		// create search-path box
		AllocClassObject(g_lpSearchPathBox,
						 CStatic);

		// check new object
		if(!g_lpSearchPathBox)
			return(FALSE);

		// create search-path list
		AllocClassObject(g_lpSearchPathList,
						 CPathListCtrl(IDC_SEARCHLIST));

		// check new object
		if(!g_lpSearchPathList)
			return(FALSE);

		// create search-path image list
		AllocClassObject(g_lpSPathImageList,
						 CImageList);

		// check new object
		if(!g_lpSPathImageList)
			return(FALSE);

		// create add-path button
		if(!CreateExtButton(&g_lpAddPathBtn,
							IDC_ADDPATHBTN))
			return(FALSE);

		// create change-path button
		if(!CreateExtButton(&g_lpChangePathBtn,
							IDC_CHANGEPATHBTN))
			return(FALSE);

		// create delete-path button
		if(!CreateExtButton(&g_lpDeletePathBtn,
							IDC_DELETEPATHBTN))
			return(FALSE);

		// create sys-tray checkbox
		if(!CreateExtButton(&g_lpSystemTrayChk,
							IDC_SYSTRAYCHK))
			return(FALSE);

		// create keep-current checkbox
		if(!CreateExtButton(&g_lpKeepCurrentChk,
							IDC_KEEPCURCHK))
			return(FALSE);

		// create hide-advanced checkbox
		if(!CreateExtButton(&g_lpHideAdvancedChk,
							IDC_HIDEADVCHK))
			return(FALSE);

		// create error-log box
		AllocClassObject(g_lpErrorLogBox,
						 CStatic);

		// check new object
		if(!g_lpErrorLogBox)
			return(FALSE);

		// create error-log checkbox
		if(!CreateExtButton(&g_lpErrorLogChk,
							IDC_ERRORLOGCHK))
			return(FALSE);

		// create max-lines static
		AllocClassObject(g_lpMaxLinesTxt,
						 CExtStatic(IDC_MAXLINESTXT));

		// check new object
		if(!g_lpMaxLinesTxt)
			return(FALSE);

		// create max-lines edit box
		AllocClassObject(g_lpMaxLinesEdit,
						 CExtEdit(IDC_MAXLINESEDT));

		// check new object
		if(!g_lpMaxLinesEdit)
			return(FALSE);

		// create error-log button
		if(!CreateExtButton(&g_lpErrorLogBtn,
							IDC_ERRORLOGBTN))
			return(FALSE);

		// create reset-messages button
		if(!CreateExtButton(&g_lpResetMessagesBtn,
							IDC_RESETMSGBTN))
			return(FALSE);

		// create hide-advanced button
		if(!CreateExtButton(&g_lpHideAdvancedBtn,
							IDC_HIDEADVBTN))
			return(FALSE);

		// create music manager dialog
		g_lpMusicManagerDlgA=CreateMusicManagerDlg(g_lpPlaybackPage);

		// check new object
		if(!g_lpMusicManagerDlgA)
			return(FALSE);
	}

////////////////////////////////////////
// MUSIC MANAGER ///////////////////////
////////////////////////////////////////

ANTIHACK_6

	// check purchase flag
	if(!bPurchOnly)
	{
		// load overlay icons
		if(!LoadOverlayIcons())
			return(FALSE);

		// load playback control images
		if(!CreatePlaybackCtrlImages())
			return(FALSE);

		// load extension groups
		if(!InitExtensionGroups())
			return(FALSE);

		// create music dialog history box
		AllocClassObject(g_lpAudioHistoryCbx,
						 CHistoryComboBox(IDC_HISTORYCBX));

		// check new object
		if(!g_lpAudioHistoryCbx)
			return(FALSE);

		// create navigation buttons
		if(!CreateNavigationImages())
			return(FALSE);

		// create file back button
		AllocClassObject(g_lpFileBackBtn,
						 CFolderCtrlButton(IDC_FILEBACKBTN));

		// check new object
		if(!g_lpFileBackBtn)
			return(FALSE);

		// create file up button
		AllocClassObject(g_lpFileUpBtn,
						 CFolderCtrlButton(IDC_FILEUPBTN));

		// check new object
		if(!g_lpFileUpBtn)
			return(FALSE);

		// create clear audio sel button
		if(!CreateExtButton(&g_lpClearAudioSelBtn,
							IDC_CLEARAUDIOSELBTN))
			return(FALSE);

		// create add audio file button
		if(!CreateExtButton(&g_lpAddAudioFileBtn,
							IDC_ADDAUDIOFILEBTN))
			return(FALSE);

		// create audio playlist up button
		if(!CreateExtButton(&g_lpAudioPListUpBtn,
							IDC_AUDIOPLISTUPBTN))
			return(FALSE);

		// create audio playlist top button
		if(!CreateExtButton(&g_lpAudioPListTopBtn,
							IDC_AUDIOPLISTTOPBTN))
			return(FALSE);

		// create audio playlist down button
		if(!CreateExtButton(&g_lpAudioPListDownBtn,
							IDC_AUDIOPLISTDOWNBTN))
			return(FALSE);

		// create audio playlist bottom button
		if(!CreateExtButton(&g_lpAudioPListBottomBtn,
							IDC_AUDIOPLISTBOTTOMBTN))
			return(FALSE);

		// create audio playlist delete button
		if(!CreateExtButton(&g_lpAudioPListDelBtn,
							IDC_AUDIOPLISTDELBTN))
			return(FALSE);

		// create audio playlist clear button
		if(!CreateExtButton(&g_lpAudioPListClearBtn,
							IDC_AUDIOPLISTCLRBTN))
			return(FALSE);

		// create audio playlist save button
		if(!CreateExtButton(&g_lpAudioPListSaveBtn,
							IDC_AUDIOPLISTSAVEBTN))
			return(FALSE);

		// create audio playlist load button
		if(!CreateExtButton(&g_lpAudioPListLoadBtn,
							IDC_AUDIOPLISTLOADBTN))
			return(FALSE);

		// create play button
		if(!CreateExtButton(&g_lpPlayBtn,
							IDC_PLAYBTN))
			return(FALSE);

		// create pause button
		if(!CreateExtButton(&g_lpPauseBtn,
							IDC_PAUSEBTN))
			return(FALSE);

		// create stop button
		if(!CreateExtButton(&g_lpStopBtn,
							IDC_STOPBTN))
			return(FALSE);

		// create full rewind button
		if(!CreateExtButton(&g_lpFullRewBtn,
							IDC_FULLREWBTN))
			return(FALSE);

		// create rewind button
		if(!CreateExtButton(&g_lpRewBtn,
							IDC_REWBTN))
			return(FALSE);

		// create forward button
		if(!CreateExtButton(&g_lpFwdBtn,
							IDC_FWDBTN))
			return(FALSE);

		// create music manager help button
		if(!CreateExtButton(&g_lpMusicMgrHelpBtn,
							IDC_MUSMANHELPBTN))
			return(FALSE);

		// create install directx button
		if(!CreateExtButton(&g_lpInstallDXBtn,
							IDC_INSTALLDXBTN))
			return(FALSE);

		// create music dialog file list
		AllocClassObject(g_lpAudioFileList,
						 CFileListCtrl(IDC_FILELIST));

		// check new object
		if(!g_lpAudioFileList)
			return(FALSE);

		// create file type box
		AllocClassObject(g_lpFileTypeCbx,
						 CAudioExtComboBox(IDC_FILETYPECBX));

		// check new object
		if(!g_lpFileTypeCbx)
			return(FALSE);

		// create audio playlist sort box
		AllocClassObject(g_lpAudioPListSortCbx,
						 CAudioSortBox(IDC_AUDIOPLISTSORTCBX));

		// check new object
		if(!g_lpFileTypeCbx)
			return(FALSE);

		// create audio playlist
		AllocClassObject(g_lpAudioPList,
						 CAudioPlaylist);

		// check new object
		if(!g_lpAudioPList)
			return(FALSE);

		// set id value
		g_lpAudioPList->SetCtrlIds(IDC_AUDIOPLIST,
								   IDC_AUDIOPLISTHEAD);

		// create audio file info
		AllocClassObject(g_lpAudioInfoBox,
						 CAudioInfoBox(IDC_AUDIOINFO));

		// check new object
		if(!g_lpAudioInfoBox)
			return(FALSE);

		// create audio position text
		AllocClassObject(g_lpAudioPosTxt,
						 CExtStatic(IDC_AUDIOPOSTXT));

		// check new object
		if(!g_lpAudioPosTxt)
			return(FALSE);

		// create next hotkey text
		AllocClassObject(g_lpNextHkyTxt,
						 CExtStatic(IDC_NEXTHKYTXT));

		// check new object
		if(!g_lpNextHkyTxt)
			return(FALSE);

		// create volume up hotkey text
		AllocClassObject(g_lpVolUpHkyTxt,
						 CExtStatic(IDC_VOLUPHKYTXT));

		// check new object
		if(!g_lpVolUpHkyTxt)
			return(FALSE);

		// create volume down hotkey text
		AllocClassObject(g_lpVolDownHkyTxt,
						 CExtStatic(IDC_VOLDNHKYTXT));

		// check new object
		if(!g_lpVolDownHkyTxt)
			return(FALSE);

		// create mute hotkey text
		AllocClassObject(g_lpMuteHkyTxt,
						 CExtStatic(IDC_MUTEHKYTXT));

		// check new object
		if(!g_lpMuteHkyTxt)
			return(FALSE);

		// create directx effects text
		AllocClassObject(g_lpDXFXTxt,
						 CExtStatic(IDC_DXFXTXT));

		// check new object
		if(!g_lpDXFXTxt)
			return(FALSE);

		// crate position slider
		AllocClassObject(g_lpAudioPosSld,
						 CAudioPosSlider(IDC_AUDIOPOSSLD));

		// check new object
		if(!g_lpAudioPosSld)
			return(FALSE);

		// create playback controls checkbox
		if(!CreateExtButton(&g_lpEnablePBCChk,
							IDC_ENABLEPBCCHK))
			return(FALSE);

		// create reverb checkbox
		if(!CreateExtButton(&g_lpReverbChk,
							IDC_REVERBCHK))
			return(FALSE);

		// create chorus checkbox
		if(!CreateExtButton(&g_lpChorusChk,
							IDC_CHORUSCHK))
			return(FALSE);

		// create next hotkey
		AllocClassObject(g_lpNextHky,
						 CExtHotKeyCtrl(IDC_NEXTHKY));

		// check new object
		if(!g_lpNextHky)
			return(FALSE);

		// create volume up hotkey
		AllocClassObject(g_lpVolUpHky,
						 CExtHotKeyCtrl(IDC_VOLUPHKY));

		// check new object
		if(!g_lpVolUpHky)
			return(FALSE);

		// create volume down hotkey
		AllocClassObject(g_lpVolDownHky,
						 CExtHotKeyCtrl(IDC_VOLDNHKY));

		// check new object
		if(!g_lpVolDownHky)
			return(FALSE);

		// create mute hotkey
		AllocClassObject(g_lpMuteHky,
						 CExtHotKeyCtrl(IDC_MUTEHKY));

		// check new object
		if(!g_lpMuteHky)
			return(FALSE);

		// create windows synth radio
		if(!CreateExtButton(&g_lpWinSynthRad,
							IDC_WINSYNTHRAD))
			return(FALSE);

		// create directx synth radio
		if(!CreateExtButton(&g_lpDXSynthRad,
							IDC_DXSYNTHRAD))
			return(FALSE);
	}

////////////////////////////////////////
// EDIT INFO DIALOG ////////////////////
////////////////////////////////////////
	
ANTIHACK_7

	// check purchase flag
	if(!bPurchOnly)
	{
		// create saver info icon
		AllocClassObject(g_lpSaverInfoIcon,
						 CExtStatic(IDC_SAVERINFOICON));

		// check new object
		if(!g_lpSaverInfoIcon)
			return(FALSE);

		// create theme selection box
		AllocClassObject(g_lpThemeSelBox,
						 CExtComboBox(IDC_THEMESELBOX));

		// check new object
		if(!g_lpThemeSelBox)
			return(FALSE);

		// create edit themes button
		if(!CreateExtButton(&g_lpEditThemesBtn,
							IDC_EDITTHEMESBTN))
			return(FALSE);

		// create rating selection box
		AllocClassObject(g_lpRatingSelBox,
						 CExtComboBox(IDC_RATINGSELBOX));

		// check new object
		if(!g_lpRatingSelBox)
			return(FALSE);

		// create edit saver help button
		if(!CreateExtButton(&g_lpEditHelpBtn,
							IDC_EDITHELPBTN))
			return(FALSE);

		// create rating selection box
		AllocClassObject(g_lpMusicSelBox,
						 CExtEdit(IDC_MUSICSELBOX));

		// check new object
		if(!g_lpMusicSelBox)
			return(FALSE);

		// create music browse button
		if(!CreateExtButton(&g_lpMusicBrowseBtn,
							IDC_MUSICBROWSEBTN))
			return(FALSE);

		// create music cycle button
		if(!CreateExtButton(&g_lpMusicCycleRad,
							IDC_MUSICCYCLERAD))
			return(FALSE);

		// create music shuffle button
		if(!CreateExtButton(&g_lpMusicShuffleRad,
							IDC_MUSICSHUFFLERAD))
			return(FALSE);

		// create saver description label
		AllocClassObject(g_lpSaverDescLabel,
						 CExtStatic(IDC_SAVERDESC));

		// check new object
		if(!g_lpSaverDescLabel)
			return(FALSE);

		// create saver description edit box
		AllocClassObject(g_lpSaverDescEdit,
						 CExtEdit(IDC_SAVERDESCEDT));

		// check new object
		if(!g_lpSaverDescEdit)
			return(FALSE);

		// create no-mini-preview button
		if(!CreateExtButton(&g_lpNoMiniPrevChk,
							IDC_DISABLEPREVCHK))
			return(FALSE);
	}

////////////////////////////////////////
// EDIT THEMES DIALOG //////////////////
////////////////////////////////////////

ANTIHACK_8

	// check purchase flag
	if(!bPurchOnly)
	{
		// create themes list
		AllocClassObject(g_lpThemesList,
						 CThemesList);

		// check new object
		if(!g_lpThemesList)
			return(FALSE);

		// create new theme button
		if(!CreateExtButton(&g_lpNewThemeBtn,
							IDC_NEWTHEMEBTN))
			return(FALSE);

		// create delete theme button
		if(!CreateExtButton(&g_lpDelThemeBtn,
							IDC_DELTHEMEBTN))
			return(FALSE);

		// create rename theme button
		if(!CreateExtButton(&g_lpRenThemeBtn,
							IDC_RENAMETHEMEBTN))
			return(FALSE);

		// create default themes button
		if(!CreateExtButton(&g_lpDefThemesBtn,
							IDC_DEFTHEMESBTN))
			return(FALSE);

		// create themes help button
		if(!CreateExtButton(&g_lpThemesHelpBtn,
							IDC_THEMESHELPBTN))
			return(FALSE);
	}

////////////////////////////////////////
// NEW THEME DIALOG ////////////////////
////////////////////////////////////////

ANTIHACK_9

	// check purchase flag
	if(!bPurchOnly)
	{
		// create new theme edit control
		AllocClassObject(g_lpNewThemeEdit,
						 CExtEdit(IDC_NEWTHEMEEDT));

		// check new object
		if(!g_lpNewThemeEdit)
			return(FALSE);
	}

////////////////////////////////////////
// RENAME THEME DIALOG /////////////////
////////////////////////////////////////

ANTIHACK_10

	// check purchase flag
	if(!bPurchOnly)
	{
		// create rename theme edit control
		AllocClassObject(g_lpRenThemeEdit,
						 CExtEdit(IDC_RENAMETHEMEEDT));

		// check new object
		if(!g_lpRenThemeEdit)
			return(FALSE);
	}

////////////////////////////////////////
// CHANGE AUDIO DIALOG /////////////////
////////////////////////////////////////

ANTIHACK_11

	// check purchase flag
	if(!bPurchOnly)
	{
		// create load single file button
		if(!CreateExtButton(&g_lpLoadAudioFileBtn,
							IDC_LOADAUDFILEBTN))
			return(FALSE);

		// create load playlist button
		if(!CreateExtButton(&g_lpLoadAudioPlaylistBtn,
							IDC_LOADPLISTBTN))
			return(FALSE);

		// create clear music button
		if(!CreateExtButton(&g_lpClearAudioFileBtn,
							IDC_CLEARMUSBTN))
			return(FALSE);

		// create open manager button
		if(!CreateExtButton(&g_lpOpenMusicManagerBtn,
							IDC_EDITAUDIOBTN))
			return(FALSE);

		// create change music help button
		if(!CreateExtButton(&g_lpChangeAudioHelpBtn,
							IDC_CHGMUSHELPBTN))
			return(FALSE);
	}

////////////////////////////////////////
// PREFERENCES DIALOG //////////////////
////////////////////////////////////////

ANTIHACK_12

	// check purchase flag
	if(!bPurchOnly)
	{
		// create preferences dialog
		AllocClassObject(g_lpPrefsDlg,
						 CPreferencesDlg(IDD_PREFS,
										 g_lpMainSheet));

		// check new object
		if(!g_lpPrefsDlg)
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpSplashScreenChk,
							IDC_SPLASHSCRNCHK))
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpPlaySFXChk,
							IDC_PLAYSFXCHK))
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpTooltipsChk,
							IDC_SHOWTOOLTIPSCHK))
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpSaverListDetChk,
							IDC_SAVERLISTDETCHK))
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpRatingImagesChk,
							IDC_RATINGIMGSCHK))
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpSaverListPopupChk,
							IDC_SLISTPOPUPCHK))
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpPlaylistPopupChk,
							IDC_PLISTPOPUPCHK))
			return(FALSE);

		// create button
		if(!CreateExtButton(&g_lpPrefsHelpBtn,
							IDC_PREFSHELPBTN))
			return(FALSE);
	}

////////////////////////////////////////
// ABOUT DIALOG ////////////////////////
////////////////////////////////////////

ANTIHACK_8

	// check purchase flag
	if(!bPurchOnly)
	{
		// create about dialog
		AllocClassObject(g_lpAboutDlg,
						 CAboutDlg(IDD_ABOUT,
								   g_lpMainSheet));

		// check new object
		if(!g_lpAboutDlg)
			return(FALSE);

		// load about bitmap
		if(!LoadBitmap(&g_lpAboutBmp,
					   IDB_ABOUTBMP))
			return(FALSE);

		// load WaveBreak bitmap
		if(!LoadBitmap(&g_lpWBSLogoBmp,
					   IDB_WBSLOGO))
			return(FALSE);

		/* -- removed ASP
		// load ASP bitmap
		if(!LoadBitmap(&g_lpASPLogoBmp,
					   IDB_ASPLOGO))
			return(FALSE);
		*/

		// create icon box
		AllocClassObject(g_lpPSIconBox,
						 CExtStatic(IDC_ABOUTBMP));

		// check new object
		if(!g_lpPSIconBox)
			return(FALSE);

		// create title text
		AllocClassObject(g_lpPSTitleTxt,
						 CExtStatic(IDC_PSMGRTXT));

		// check new object
		if(!g_lpPSTitleTxt)
			return(FALSE);

		// create WBS link box
		AllocClassObject(g_lpWBSLinkBox,
						 CExtStatic(IDC_WBSOFTBMP));

		// check new object
		if(!g_lpWBSLinkBox)
			return(FALSE);

		// create ASP link box
		AllocClassObject(g_lpASPLinkBox,
						 CExtStatic(IDC_ASPLOGOBMP));

		// check new object
		if(!g_lpASPLinkBox)
			return(FALSE);

		// create license button
		if(!CreateExtButton(&g_lpLicenseBtn,
							IDC_VIEWLICBTN))
			return(FALSE);

		// create read-me button
		if(!CreateExtButton(&g_lpReadMeBtn,
							IDC_VIEWREADMEBTN))
			return(FALSE);
	}

////////////////////////////////////////
// PURCHASE DIALOG /////////////////////
////////////////////////////////////////

#ifdef SHAREWARE_MODE
ANTIHACK_4

	// create purchase dialog
	AllocClassObject(g_lpPurchDlg,
					 CPurchDlg(IDD_PURCHASE,
							   g_lpMainSheet));

	// check new object
	if(!g_lpPurchDlg)
		return(FALSE);

	// load cards-1 bitmap
	if(!LoadBitmap(&g_lpCCards1Bmp,
				  IDB_CCARDS1))
		return(FALSE);

	// load cards-2 bitmap
	if(!LoadBitmap(&g_lpCCards2Bmp,
				  IDB_CCARDS2))
		return(FALSE);

	// load purchase bitmap
	if(!LoadBitmap(&g_lpPSBuyBmp,
				  IDB_PSBUY))
		return(FALSE);

	// create trial text
	AllocClassObject(g_lpTrialDaysTxt,
					 CExtStatic(IDC_TRIALDAYSTXT));

	// check new object
	if(!g_lpTrialDaysTxt)
		return(FALSE);

	// create cards-1 box
	AllocClassObject(g_lpCCards1Box,
					 CExtStatic(IDC_CCARDS1BMP));

	// check new object
	if(!g_lpCCards1Box)
		return(FALSE);

	// create cards-2 box
	AllocClassObject(g_lpCCards2Box,
					 CExtStatic(IDC_CCARDS2BMP));

	// check new object
	if(!g_lpCCards2Box)
		return(FALSE);

	// create purchase box
	AllocClassObject(g_lpPSBuyBox,
					 CExtStatic(IDC_PSBUYBMP));

	// check new object
	if(!g_lpPSBuyBox)
		return(FALSE);

	// create order button
	if(!CreateExtButton(&g_lpOrderBtn,
						IDC_ORDERBTN))
		return(FALSE);

	// create mail-form button
	if(!CreateExtButton(&g_lpMailFormBtn,
						IDC_MAILFORMBTN))
		return(FALSE);
#endif

////////////////////////////////////////
// MISCELLANEOUS ///////////////////////
////////////////////////////////////////

ANTIHACK_9

	// check purchase flag
	if(!bPurchOnly)
	{
		// set starting page
		g_lpMainSheet->SetActivePage(g_lpSaverPage);

		// wait for splash
		WaitForSplashScreen();
	}

	// ok
	return(TRUE);
}

// ReleaseMainSheet()

void ReleaseMainSheet()
{
ANTIHACK_3

	// release leftover context help
	ReleaseContextHelpWnd();

	// macro to close dialogs
	#define CloseDlg(dlg,cmd) if(dlg) if(IsWindow(dlg->m_hWnd)) { dlg->cmd; dlg->DestroyWindow(); }

	// cancel all dialogs
	CloseDlg(g_lpNewThemeDlg,     OnCancel());
	CloseDlg(g_lpRenThemeDlg,     OnCancel());
	CloseDlg(g_lpEditThemesDlgA,  OnCancel());
	CloseDlg(g_lpEditThemesDlgB,  OnCancel());
	CloseDlg(g_lpMusicManagerDlgA,OnCancel());
	CloseDlg(g_lpMusicManagerDlgB,OnCancel());
	CloseDlg(g_lpChangeMusicDlg,  OnCancel());
	CloseDlg(g_lpSaverInfoDlg,    OnCancel());
	CloseDlg(g_lpPrefsDlg,        OnCancel());
	CloseDlg(g_lpAboutDlg,        OnCancel());
	CloseDlg(g_lpPurchDlg,        OnCancel());
	CloseDlg(g_lpMainSheet,       PressButton(IDCANCEL));

	// release pushbuttons
	FreeClassObject(g_lpClearSelBtn);
	FreeClassObject(g_lpAddSaverBtn);
	FreeClassObject(g_lpSaverSettingsBtn);
	FreeClassObject(g_lpPreviewSaverBtn);
	FreeClassObject(g_lpEditSaverInfoBtn);
	FreeClassObject(g_lpEditThemesBtn);
	FreeClassObject(g_lpEditHelpBtn);
	FreeClassObject(g_lpMusicBrowseBtn);
	FreeClassObject(g_lpNewThemeBtn);
	FreeClassObject(g_lpDelThemeBtn);
	FreeClassObject(g_lpRenThemeBtn);
	FreeClassObject(g_lpDefThemesBtn);
	FreeClassObject(g_lpThemesHelpBtn);
	FreeClassObject(g_lpLoadAudioFileBtn);
	FreeClassObject(g_lpLoadAudioPlaylistBtn);
	FreeClassObject(g_lpClearAudioFileBtn);
	FreeClassObject(g_lpOpenMusicManagerBtn);
	FreeClassObject(g_lpChangeAudioHelpBtn);
	FreeClassObject(g_lpPListUpBtn);
	FreeClassObject(g_lpPListDownBtn);
	FreeClassObject(g_lpPListTopBtn);
	FreeClassObject(g_lpPListBottomBtn);
	FreeClassObject(g_lpPListDeleteBtn);
	FreeClassObject(g_lpPListClearBtn);
	FreeClassObject(g_lpPListSaveBtn);
	FreeClassObject(g_lpPListLoadBtn);
	FreeClassObject(g_lpOpenThemesBtn);
	FreeClassObject(g_lpOpenMusicBtn);
	FreeClassObject(g_lpShowAdvancedBtn);
	FreeClassObject(g_lpAddPathBtn);
	FreeClassObject(g_lpChangePathBtn);
	FreeClassObject(g_lpDeletePathBtn);
	FreeClassObject(g_lpErrorLogBtn);
	FreeClassObject(g_lpResetMessagesBtn);
	FreeClassObject(g_lpHideAdvancedBtn);
	FreeClassObject(g_lpFileBackBtn);
	FreeClassObject(g_lpFileUpBtn);
	FreeClassObject(g_lpClearAudioSelBtn);
	FreeClassObject(g_lpAddAudioFileBtn);
	FreeClassObject(g_lpAudioPListUpBtn);
	FreeClassObject(g_lpAudioPListTopBtn);
	FreeClassObject(g_lpAudioPListDownBtn);
	FreeClassObject(g_lpAudioPListBottomBtn);
	FreeClassObject(g_lpAudioPListDelBtn);
	FreeClassObject(g_lpAudioPListClearBtn);
	FreeClassObject(g_lpAudioPListSaveBtn);
	FreeClassObject(g_lpAudioPListLoadBtn);
	FreeClassObject(g_lpPlayBtn);
	FreeClassObject(g_lpPauseBtn);
	FreeClassObject(g_lpStopBtn);
	FreeClassObject(g_lpFullRewBtn);
	FreeClassObject(g_lpRewBtn);
	FreeClassObject(g_lpFwdBtn);
	FreeClassObject(g_lpMusicMgrHelpBtn);
	FreeClassObject(g_lpInstallDXBtn);
	FreeClassObject(g_lpPrefsHelpBtn);
	FreeClassObject(g_lpLicenseBtn);
	FreeClassObject(g_lpReadMeBtn);
	FreeClassObject(g_lpOrderBtn);
	FreeClassObject(g_lpMailFormBtn);

	// release radio buttons
	FreeClassObject(g_lpMusicCycleRad);
	FreeClassObject(g_lpMusicShuffleRad);
	FreeClassObject(g_lpOneSaverRad);
	FreeClassObject(g_lpMultiSaverRad);
	FreeClassObject(g_lpSaverCycleRad);
	FreeClassObject(g_lpSaverShuffleRad);
	FreeClassObject(g_lpWinSynthRad);
	FreeClassObject(g_lpDXSynthRad);

	// release checkboxes
	FreeClassObject(g_lpMiniPreviewChk);
	FreeClassObject(g_lpNoMiniPrevChk);
	FreeClassObject(g_lpEnableHotkeysChk);
	FreeClassObject(g_lpClearScreenChk);
	FreeClassObject(g_lpNoMusicChk);
	FreeClassObject(g_lpSystemTrayChk);
	FreeClassObject(g_lpKeepCurrentChk);
	FreeClassObject(g_lpHideAdvancedChk);
	FreeClassObject(g_lpErrorLogChk);
	FreeClassObject(g_lpEnablePBCChk);
	FreeClassObject(g_lpReverbChk);
	FreeClassObject(g_lpChorusChk);
	FreeClassObject(g_lpSplashScreenChk);
	FreeClassObject(g_lpPlaySFXChk);
	FreeClassObject(g_lpTooltipsChk);
	FreeClassObject(g_lpSaverListDetChk);
	FreeClassObject(g_lpRatingImagesChk);
	FreeClassObject(g_lpSaverListPopupChk);
	FreeClassObject(g_lpPlaylistPopupChk);

	// release bitmaps
	FreeClassObject(g_lpRatingBmp);
	FreeClassObject(g_lpDimRatingBmp);
	FreeClassObject(g_lpSortUp);
	FreeClassObject(g_lpSortDn);
	FreeClassObject(g_lpSortNa);
	FreeClassObject(g_lpPListUpBmp);
	FreeClassObject(g_lpPListDownBmp);
	FreeClassObject(g_lpPListTopBmp);
	FreeClassObject(g_lpPListBottomBmp);
	FreeClassObject(g_lpPListUpBmpGr);
	FreeClassObject(g_lpPListDownBmpGr);
	FreeClassObject(g_lpPListTopBmpGr);
	FreeClassObject(g_lpPListBottomBmpGr);
	FreeClassObject(g_lpNullIcon);
	FreeClassObject(g_lpNavBackBmp);
	FreeClassObject(g_lpNavBackBmpGr);
	FreeClassObject(g_lpNavUpBmp);
	FreeClassObject(g_lpNavUpBmpGr);
	FreeClassObject(g_lpPlayBmp);
	FreeClassObject(g_lpPauseBmp);
	FreeClassObject(g_lpStopBmp);
	FreeClassObject(g_lpFullRewBmp);
	FreeClassObject(g_lpRewBmp);
	FreeClassObject(g_lpFwdBmp);
	FreeClassObject(g_lpPlayBmpGr);
	FreeClassObject(g_lpPauseBmpGr);
	FreeClassObject(g_lpStopBmpGr);
	FreeClassObject(g_lpFullRewBmpGr);
	FreeClassObject(g_lpRewBmpGr);
	FreeClassObject(g_lpFwdBmpGr);
	FreeClassObject(g_lpAboutBmp);
	FreeClassObject(g_lpWBSLogoBmp);
	//FreeClassObject(g_lpASPLogoBmp);
	FreeClassObject(g_lpCCards1Bmp);
	FreeClassObject(g_lpCCards2Bmp);
	FreeClassObject(g_lpPSBuyBmp);

	// release image lists
	FreeClassObject(g_lpSPathImageList);
	
	// release icons
	FreeClassObject(g_lpSaverInfoIcon);

	// release fonts
	FreeClassObject(g_lpLCFont);
	FreeClassObject(g_lpLCFontBold);
	
	// release static controls
	FreeClassObject(g_lpSaverDescLabel);
	FreeClassObject(g_lpShowSaverTxt);
	FreeClassObject(g_lpShowSaverMinTxt);
	FreeClassObject(g_lpStartSaverTxt);
	FreeClassObject(g_lpSkipSaverTxt);
	FreeClassObject(g_lpOpenPSTxt);
	FreeClassObject(g_lpMaxLinesTxt);
	FreeClassObject(g_lpSearchPathBox);
	FreeClassObject(g_lpErrorLogBox);
	FreeClassObject(g_lpAudioPosTxt);
	FreeClassObject(g_lpNextHkyTxt);
	FreeClassObject(g_lpVolUpHkyTxt);
	FreeClassObject(g_lpVolDownHkyTxt);
	FreeClassObject(g_lpMuteHkyTxt);
	FreeClassObject(g_lpDXFXTxt);
	FreeClassObject(g_lpPSIconBox);
	FreeClassObject(g_lpPSTitleTxt);
	FreeClassObject(g_lpWBSLinkBox);
	FreeClassObject(g_lpASPLinkBox);
	FreeClassObject(g_lpTrialDaysTxt);
	FreeClassObject(g_lpCCards1Box);
	FreeClassObject(g_lpCCards2Box);
	FreeClassObject(g_lpPSBuyBox);

	// release saver playlist
	if(g_lpSaverPlaylist)
		g_lpSaverPlaylist->Release();
	
	// release list controls
	FreeClassObject(g_lpSaverPlaylist);
	FreeClassObject(g_lpThemesList);
	FreeClassObject(g_lpSearchPathList);
	FreeClassObject(g_lpAudioFileList);
	FreeClassObject(g_lpAudioPList);

	// release header controls
	FreeClassObject(g_lpSaverPlaylistHdr);

	// release edit controls
	FreeClassObject(g_lpRenThemeEdit);
	FreeClassObject(g_lpNewThemeEdit);
	FreeClassObject(g_lpSaverDescEdit);
	FreeClassObject(g_lpShowSaverEdit);
	FreeClassObject(g_lpMaxLinesEdit);

	// release read-only edit controls
	FreeClassObject(g_lpAdvWarningTxt);

	// release combo boxes
	FreeClassObject(g_lpSaverSortBox);
	FreeClassObject(g_lpThemeSelBox);
	FreeClassObject(g_lpRatingSelBox);
	FreeClassObject(g_lpMusicSelBox);
	FreeClassObject(g_lpAudioHistoryCbx);
	FreeClassObject(g_lpFileTypeCbx);
	FreeClassObject(g_lpAudioPListSortCbx);
	
	// relase slider controls
	FreeClassObject(g_lpAudioPosSld);

	// release misc. windows
	ReleaseSaverPreviewWnd();
	FreeClassObject(g_lpSaverInfoBox);
	FreeClassObject(g_lpAudioInfoBox);

	// release dialog boxes
	FreeClassObject(g_lpSaverInfoDlg);
	FreeClassObject(g_lpEditThemesDlgB);
	FreeClassObject(g_lpMusicManagerDlgA);
	FreeClassObject(g_lpPrefsDlg);
	FreeClassObject(g_lpAboutDlg);
	FreeClassObject(g_lpPurchDlg);
	
ANTIHACK_2

	// release hotkey controls
	FreeClassObject(g_lpStartSaverHky);
	FreeClassObject(g_lpSkipSaverHky);
	FreeClassObject(g_lpOpenPSHky);
	FreeClassObject(g_lpNextHky);
	FreeClassObject(g_lpVolUpHky);
	FreeClassObject(g_lpVolDownHky);
	FreeClassObject(g_lpMuteHky);

	// relese miscellaneous objects
	ReleaseScreensaverInfo();
	ReleaseThemes();
	ReleaseToolTips(&g_lpMainToolTip);
	ReleaseOverlayIcons();
	ReleaseExtensionGroups();
	ReleaseSplashScreen();
	ReleaseDefCursors();
	ReleaseSaverHookProc();
	DeleteAudioTempFile();

	// release property pages
	FreeClassObject(g_lpSaverPage);
	FreeClassObject(g_lpPlaybackPage);

	// release main property sheet
	FreeClassObject(g_lpMainSheet);

	// release common dialog boxes
	FreeClassObject(g_lpFileOpenDlg);
	FreeClassObject(g_lpFileSaveDlg);

	// release extra buttons
	FreeClassObject(g_lpGHelpBtn);
	FreeClassObject(g_lpAboutBtn);
	FreeClassObject(g_lpPrefsBtn);
	FreeClassObject(g_lpPurchBtn);
	FreeClassObject(g_lpDefOKBtn);
	FreeClassObject(g_lpDefCancelBtn);
	FreeClassObject(g_lpDefApplyBtn);

	// release install path
	FreeMem((LPVOID*)&g_lpInstPath);

#ifdef DEBUG_MODE
	// check process list
	CheckProcessList();
#endif

	// unlock application
	UnlockApplication();
}

// CMainPropSheet::OnCreate()

int CMainPropSheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// save global window handle
	g_hWnd=m_hWnd;

	// set icon
	SetIcon(LoadIcon(AfxGetInstanceHandle(),
					 ApplicationIcon()),
					 TRUE);

	// modify window style
	ModifyStyle(NULL,
				WS_SYSMENU|
				DS_3DLOOK);

	// init main sheet tooltips
	if(!InitToolTips(&g_lpMainToolTip,
					 this))
		return(FALSE);

	// enable tooltips as needed
	if(g_bShowToolTips)
		::EnableToolTips(g_lpMainToolTip);
	else
		DisableToolTips(g_lpMainToolTip);

ANTIHACK_6

	// call base method
	return(CPropertySheet::OnCreate(lpCreateStruct));
}

// CMainPropSheet::OnDestroy()

void CMainPropSheet::OnDestroy(void)
{
	// release audio support
	ReleaseAudioSupport();
	DXAudioRelease();

	// destroy extra buttons
	DestroyExtraButtons();

ANTIHACK_12

	// clear global window handle
	g_hWnd=(HWND)INVALID_HANDLE_VALUE;

	// call base method
	CPropertySheet::OnDestroy();
}

// CMainPropSheet::OnNotify()

BOOL CMainPropSheet::OnNotify(WPARAM wParam,
							  LPARAM lParam,
							  LRESULT* pResult)
{
	// cast pointer to notification header
	LPNMHDR lpNM=(LPNMHDR)lParam;

	// check notification code
	switch(lpNM->code)
	{
	// right click
	case(NM_RCLICK):

		// show popup menu
		ShowPopupMenu(IDC_MAINSHEET);

		// stop here
		return(TRUE);

	// tab selection change
	case(TCN_SELCHANGE):

		// play sound
		PlaySound(IDR_NEWSELSND);

		// ok
		break;
	}

	// call base function
	return(CPropertySheet::OnNotify(wParam,
									lParam,
									pResult));
}

// LoadPreferences()

BOOL LoadPreferences(void)
{
	LockGlobalMsg()

	// load install path
	if(!LoadOptionString("Path_Install",
						 g_lpMsg,
						 TRUE))
	{
		DisplayErrorMessage("Unable to locate the working folder for this application.",
							"Please run the setup program again.",
							FALSE);
		UnlockGlobalMsg()
		return(FALSE);
	}

	// remove '\' if req'd
	if(strlen(g_lpMsg))
		if(g_lpMsg[strlen(g_lpMsg)-1]=='\\')
			g_lpMsg[strlen(g_lpMsg)-1]=0;

	// check path
	if(!DoesPathExist(g_lpMsg))
	{
		DisplayErrorMessage("The working folder for this application does not exist.",
							"Please run the setup program again.",
							FALSE);
		UnlockGlobalMsg()
		return(FALSE);
	}

	// allocate memory for path
	if(!AllocMem((LPVOID*)&g_lpInstPath,
				 strlen(g_lpMsg)+1))
		return(FALSE);

	// copy install path
	strcpy(g_lpInstPath,
		   g_lpMsg);

	UnlockGlobalMsg()

	// load misc preferences
	g_bPlaySFX=(BOOL)LoadOptionInt("Misc_PlaySFX",
								   0,
								   1,
								   1);
	g_bShowToolTips=(BOOL)LoadOptionInt("Misc_ToolTips",
									    0,
									    1,
									    1);
	g_bSplashScreen=(BOOL)LoadOptionInt("Misc_SplashScreen",
										0,
										1,
										1);
	
ANTIHACK_11

	// load saver page preferences
	g_bShowSaverInfo=(BOOL)LoadOptionInt("Savers_SListInfo",
										 0,
										 1,
										 1);
	g_bShowRatingImgs=(BOOL)LoadOptionInt("Savers_RatingImgs",
										  0,
										  1,
										  1);
	g_bShowPopupInfo=(BOOL)LoadOptionInt("Savers_PopupInfo",
										 0,
										 1,
										 1);
	g_bShowPListPopup=(BOOL)LoadOptionInt("Savers_PListPopup",
										  0,
										  1,
										  1);

#ifndef SHAREWARE_MODE
	// set id for future updates
	SaveOptionString("Misc_AppId",
					 (LPSTR)ApplicationID(APID_VERSION),
					 TRUE);
#endif

	// load playback options
	if(!LoadPlaybackOptions())
		return(FALSE);

	// ok
	return(TRUE);
}

// SavePreferences()

BOOL SavePreferences(void)
{
	// save misc preferences
	SaveOptionInt("Misc_PlaySFX",
				  (int)g_bPlaySFX);
	SaveOptionInt("Misc_ToolTips",
				  (int)g_bShowToolTips);
	SaveOptionInt("Misc_SplashScreen",
				  (int)g_bSplashScreen);

	// save saver page preferences
	SaveOptionInt("Savers_SListInfo",
				  (int)g_bShowSaverInfo);
	SaveOptionInt("Savers_RatingImgs",
				  (int)g_bShowRatingImgs);
	SaveOptionInt("Savers_PopupInfo",
				  (int)g_bShowPopupInfo);
	SaveOptionInt("Savers_PListPopup",
				  (int)g_bShowPListPopup);

ANTIHACK_10

	// ok
	return(TRUE);
}

// CreateSortImages()

BOOL CreateSortImages(void)
{
	// device contexts
	CDC* lpDesktopDC=NULL;
	CDC* lpImageDC=NULL;

	// bitmap colors
	COLORREF clrBnFace;
	COLORREF clrShadow;
	COLORREF clrHilite;
	COLORREF clrArrow;

	// allocate bitmap
	AllocClassObject(g_lpSortUp,
					 CBitmap);

	// check new object
	if(!g_lpSortUp)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpSortDn,
					 CBitmap);

	// check new object
	if(!g_lpSortDn)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpSortNa,
					 CBitmap);

	// check new object
	if(!g_lpSortNa)
		return(FALSE);

	// get desktop dc
	lpDesktopDC=CDC::FromHandle(::GetDC(GetDesktopWindow()));

	// check desktop dc
	if(!lpDesktopDC)
	{
		DisplayErrorMessage("Unable to find desktop device context.");
		return(FALSE);
	}

	// create up bitmap
	if(!g_lpSortUp->CreateCompatibleBitmap(lpDesktopDC,
										   7,10))
	{
		DisplayErrorMessage("Unable to create sort image.");
		return(FALSE);
	}

	// create down bitmap
	if(!g_lpSortDn->CreateCompatibleBitmap(lpDesktopDC,
										   7,10))
	{
		DisplayErrorMessage("Unable to create sort image.");
		return(FALSE);
	}

ANTIHACK_9

	// create n/a bitmap
	if(!g_lpSortNa->CreateCompatibleBitmap(lpDesktopDC,
										   7,10))
	{
		DisplayErrorMessage("Unable to create sort image.");
		return(FALSE);
	}

	// get bitmap colors
	clrBnFace=GetSysColor(COLOR_3DFACE);
	clrShadow=GetSysColor(COLOR_3DSHADOW);
	clrHilite=GetSysColor(COLOR_3DHILIGHT);
	clrArrow =GetSysColor(COLOR_3DDKSHADOW);

	// allocate device context
	AllocClassObject(lpImageDC,
					 CDC);

	// check new object
	if(!lpImageDC)
		return(FALSE);

	// create compatible dc
	if(!lpImageDC->CreateCompatibleDC(lpDesktopDC))
	{
		DisplayErrorMessage("Unable to create desktop-compatible device context.");
		return(FALSE);
	}
	else
		AddWinResource

	// select up bitmap
	lpImageDC->SelectObject(g_lpSortUp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(1,1,5,8,clrBnFace);

		// draw border
		lpImageDC->FillSolidRect(0,0,7,1,clrShadow);
		lpImageDC->FillSolidRect(0,1,1,8,clrShadow);
		lpImageDC->FillSolidRect(0,9,7,1,clrHilite);
		lpImageDC->FillSolidRect(6,0,1,9,clrHilite);

		// draw up arrow
		lpImageDC->FillSolidRect(3,2,1,2,clrArrow);
		lpImageDC->FillSolidRect(2,4,3,2,clrArrow);
		lpImageDC->FillSolidRect(1,6,5,1,clrArrow);
	}

	// select down bitmap
	lpImageDC->SelectObject(g_lpSortDn);
	
	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(1,1,5,8,clrBnFace);

		// draw border
		lpImageDC->FillSolidRect(0,0,7,1,clrShadow);
		lpImageDC->FillSolidRect(0,1,1,8,clrShadow);
		lpImageDC->FillSolidRect(0,9,7,1,clrHilite);
		lpImageDC->FillSolidRect(6,0,1,9,clrHilite);

		// draw down arrow
		lpImageDC->FillSolidRect(3,6,1,2,clrArrow);
		lpImageDC->FillSolidRect(2,4,3,2,clrArrow);
		lpImageDC->FillSolidRect(1,3,5,1,clrArrow);
	}

	// select n/a bitmap
	lpImageDC->SelectObject(g_lpSortNa);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(1,1,5,8,clrBnFace);

		// draw border
		lpImageDC->FillSolidRect(0,0,7,1,clrShadow);
		lpImageDC->FillSolidRect(0,1,1,8,clrShadow);
		lpImageDC->FillSolidRect(0,9,7,1,clrHilite);
		lpImageDC->FillSolidRect(6,0,1,9,clrHilite);
	}

	// select null object
	lpImageDC->SelectObject((CGdiObject*)NULL);

	// delete device context
	if(lpImageDC->DeleteDC())
		RemoveWinResource

	// free device context
	FreeClassObject(lpImageDC);

	// ok
	return(TRUE);
}

// CMainPropSheet::OnSysColorChange()

void CMainPropSheet::OnSysColorChange(void)
{
	// free sort images
	FreeClassObject(g_lpSortUp);
	FreeClassObject(g_lpSortDn);
	FreeClassObject(g_lpSortNa);

	// create with new colors
	if(!CreateSortImages())
		ForceImmediateExit();

	// update sort images
	UpdateSaverListSortImages();

	// free playlist button images
	FreeClassObject(g_lpPListUpBmp);
	FreeClassObject(g_lpPListDownBmp);
	FreeClassObject(g_lpPListTopBmp);
	FreeClassObject(g_lpPListBottomBmp);
	FreeClassObject(g_lpPListUpBmpGr);
	FreeClassObject(g_lpPListDownBmpGr);
	FreeClassObject(g_lpPListTopBmpGr);
	FreeClassObject(g_lpPListBottomBmpGr);
	
	// create with new colors
	if(!CreatePlaylistBtnImages())
		ForceImmediateExit();

	// free playback control images
	FreeClassObject(g_lpPlayBmp);
	FreeClassObject(g_lpPauseBmp);
	FreeClassObject(g_lpStopBmp);
	FreeClassObject(g_lpFullRewBmp);
	FreeClassObject(g_lpRewBmp);
	FreeClassObject(g_lpFwdBmp);
	FreeClassObject(g_lpPlayBmpGr);
	FreeClassObject(g_lpPauseBmpGr);
	FreeClassObject(g_lpStopBmpGr);
	FreeClassObject(g_lpFullRewBmpGr);
	FreeClassObject(g_lpRewBmpGr);
	FreeClassObject(g_lpFwdBmpGr);

	// create with new colors
	if(!CreatePlaybackCtrlImages())
		ForceImmediateExit();

	// free navigation images
	FreeClassObject(g_lpNavBackBmp);
	FreeClassObject(g_lpNavBackBmpGr);
	FreeClassObject(g_lpNavUpBmp);
	FreeClassObject(g_lpNavUpBmpGr);

	// create with new colors
	if(!CreateNavigationImages())
		ForceImmediateExit();

ANTIHACK_8

	// free null-icon image
	FreeClassObject(g_lpNullIcon);

	// create with new colors
	if(!CreateNullIconImage())
		ForceImmediateExit();

	// redraw saver info box
	UpdateSaverInfoBox(g_lpCurSaver);

	// check saver list
	if(g_lpSaverList)
		if(IsWindow(g_lpSaverList->m_hWnd))
		{
			// update background
			g_lpSaverList->SetBkColor(GetSysColor(COLOR_WINDOW));
		}

	// call base method
	CPropertySheet::OnSysColorChange();

	// redraw window
	RedrawWindow();

	// post change command
	PostCommand(g_lpMainSheet,
				IDM_MSHEET_CLRCHG);
}

// CMainPropSheet::OnDevModeChange()

void CMainPropSheet::OnDevModeChange(LPTSTR lpDeviceName)
{
	// call base method
	CPropertySheet::OnDevModeChange(lpDeviceName);

	// redraw window
	RedrawWindow();
}

// CMainPropSheet::OnWinIniChange()

void CMainPropSheet::OnWinIniChange(LPCTSTR lpszSection)

{
	// call base method
	CPropertySheet::OnWinIniChange(lpszSection);

	// redraw window
	RedrawWindow();
}

// CreateListControlFonts()

BOOL CreateListControlFonts(HDC hDC,
							CFont* lpFont)
{
#ifdef DEBUG_MODE
	// check dc
	if(hDC==NULL||
	   hDC==(HDC)INVALID_HANDLE_VALUE)
	{
		// no dc, so font must exist
		if(!lpFont)
		{
			DisplayErrorMessage("Invalid handle value.",
								"CreateListControlFonts()",
								FALSE);
			return(FALSE);
		}
	}
#endif

	// device context
	CDC* lpDC=NULL;

	// text metrics
	TEXTMETRIC tm;

	// font attributes
	LOGFONT lf;

	// check for existing fonts
	if(g_lpLCFont&&
	   g_lpLCFontBold)
		return(TRUE);

ANTIHACK_7

	// release fonts (just in case)
	FreeClassObject(g_lpLCFont);
	FreeClassObject(g_lpLCFontBold);

	// create normal font
	AllocClassObject(g_lpLCFont,
					 CFont);

	// check new object
	if(!g_lpLCFont)
		goto CreateListControlFonts1;
	
	// create bold font
	AllocClassObject(g_lpLCFontBold,
					 CFont);

	// check new object
	if(!g_lpLCFontBold)
		goto CreateListControlFonts1;

	// check font
	if(!lpFont)
	{
		// copy device context
		lpDC=CDC::FromHandle(hDC);

		// check device context
		if(!lpDC)
			goto CreateListControlFonts1;

		// get text metrics
		if(!lpDC->GetTextMetrics(&tm))
			goto CreateListControlFonts1;

		// set font attributes
		lf.lfHeight        =tm.tmHeight;
		lf.lfWidth         =0;
		lf.lfEscapement    =0;
		lf.lfOrientation   =0;
		lf.lfWeight        =FW_NORMAL;
		lf.lfItalic        =tm.tmItalic;
		lf.lfUnderline     =tm.tmUnderlined;
		lf.lfStrikeOut     =tm.tmStruckOut;
		lf.lfCharSet       =tm.tmCharSet;
		lf.lfOutPrecision  =OUT_DEFAULT_PRECIS;
		lf.lfClipPrecision =CLIP_DEFAULT_PRECIS;
		lf.lfQuality       =DEFAULT_QUALITY;
		lf.lfPitchAndFamily=tm.tmPitchAndFamily;
		
		LockGlobalMsg()
		
		// get face name
		if(!lpDC->GetTextFace(_MAX_PATH,
							  g_lpMsg))
		{
			UnlockGlobalMsg()
			goto CreateListControlFonts1;
		}

		// force null terminator
		g_lpMsg[LF_FACESIZE-1]=0;

		// copy face name
		strcpy(lf.lfFaceName,
			   g_lpMsg);

		UnlockGlobalMsg()
	}
	else
	{
		// use supplied font
		if(!lpFont->GetLogFont(&lf))
			goto CreateListControlFonts1;
	}

	// create normal font
	if(!g_lpLCFont->CreateFontIndirect(&lf))
		goto CreateListControlFonts1;

	// set bold flag
	lf.lfWeight=FW_BOLD;
	
	// create bold font
	if(!g_lpLCFontBold->CreateFontIndirect(&lf))
		goto CreateListControlFonts1;

	// update locations
	UpdateLCFontLocations();

	// ok
	return(TRUE);

// error exit point
CreateListControlFonts1:;

	// release fonts
	FreeClassObject(g_lpLCFont);
	FreeClassObject(g_lpLCFontBold);

	// no good
	return(FALSE);
}

// CMainPropSheet::OnShowWindow()

void CMainPropSheet::OnShowWindow(BOOL bShow,
								  UINT nStatus)
{
	// initialized flag
	static BOOL bInit=FALSE;

	// window objects
	CWnd* lpTopWnd   =NULL;
	CWnd* lpParentWnd=NULL;

	// button windows
	CWnd* lpOKBtn=NULL;
	CWnd* lpCancelBtn=NULL;
	CWnd* lpApplyBtn=NULL;

	// window rects
	CRect rWnd1;
	CRect rWnd2;

	// check initialized flag
	if(!bInit)
	{
		// check show flag
		if(bShow)
		{
			// set init flag
			bInit=TRUE;

			// get top window
			lpTopWnd=GetTopWindow();

			// check window
			if(!lpTopWnd)
			{
				DisplayErrorMessage("Cannot find property sheet window.");
				ForceImmediateExit();
			}

			// find ok button
			lpOKBtn=lpTopWnd->GetNextWindow();

			// check button
			if(!lpOKBtn)
			{
				DisplayErrorMessage("Cannot find default 'OK' button.");
				ForceImmediateExit();
			}

			// find cancel button
			lpCancelBtn=lpOKBtn->GetNextWindow();

			// check button
			if(!lpCancelBtn)
			{
				DisplayErrorMessage("Cannot find default 'Cancel' button.");
				ForceImmediateExit();
			}

			// find apply button
			lpApplyBtn=lpCancelBtn->GetNextWindow();

			// check button
			if(!lpApplyBtn)
			{
				DisplayErrorMessage("Cannot find default 'Apply' button.");
				ForceImmediateExit();
			}

			// capture ok button
			if(!g_lpDefOKBtn->SubclassWindow(lpOKBtn->m_hWnd))
			{
				DisplayErrorMessage("Unable to capture default 'OK' button.");
				ForceImmediateExit();
			}

			// capture cancel button
			if(!g_lpDefCancelBtn->SubclassWindow(lpCancelBtn->m_hWnd))
			{
				DisplayErrorMessage("Unable to capture default 'Cancel' button.");
				ForceImmediateExit();
			}

			// capture apply button
			if(!g_lpDefApplyBtn->SubclassWindow(lpApplyBtn->m_hWnd))
			{
				DisplayErrorMessage("Unable to capture default 'Apply' button.");
				ForceImmediateExit();
			}

			// add extra buttons
			if(!CreateExtraButtons())
				ForceImmediateExit();

			// get parent
			lpParentWnd=GetParentCWnd();

			// check parent
			if(lpParentWnd)
			{
				// get window rects
				GetWindowRect(&rWnd1);
				lpParentWnd->GetWindowRect(&rWnd2);

				// move this window to parent
				rWnd1.OffsetRect(rWnd2.left-rWnd1.left,
								 rWnd2.top -rWnd1.top);

				// keep rect on screen
				KeepRectsOnScreen(&rWnd1);

				// move window
				MoveWindow(&rWnd1,
						   FALSE);
			}

			// post init command
			PostCommand(g_lpMainSheet,
						IDM_MSHEET_INIT);
		}
	}
	else
		ANTIHACK_6
}

// MainSheetIsInit()

void MainSheetIsInit(void)
{
	// items to process immediately
	// after main window is displayed

	// get main sheet font
	CFont* lpFont=g_lpMainSheet->GetFont();

	// create list control fonts
	if(lpFont)
		CreateListControlFonts(NULL,
							   lpFont);

#ifdef SHAREWARE_MODE
	// check trial days
	CheckTrialDays();
#endif

	// init audio support
	if(!InitAudioSupport(TRUE,
						 TRUE))
	{
		// alert user
		DisplayOptMessageBox("Failed to initialize audio support.\n\nAudio playback will not be available.",
							 "ProSaver",
							 MB_OK|MB_ICONEXCLAMATION,
							 "MsgBox_AudioError");
	}

	// alert new savers
	g_lpSaverInfo->AlertNewSavers();
	
	// check invalid playlist flag
	if(g_bInvPListItems)
	{
		// alert user
		AlertInvSaverPlaylistItems();
	}
	else
		ANTIHACK_5

	// keep ProSaver current
	KeepProSaverCurrent();

	// display welcome screen
	RunWelcomeScreen();

	// set focus to ok button
	g_lpDefOKBtn->SetFocus();
}

// CreateNullIconImage()

BOOL CreateNullIconImage(void)
{
	// device contexts
	CDC* lpDesktopDC=NULL;
	CDC* lpImageDC  =NULL;

	// bitmap colors
	COLORREF clrHilite;
	COLORREF clrLight;
	COLORREF clrShadow;
	COLORREF clrDkShadow;

	// allocate bitmap
	AllocClassObject(g_lpNullIcon,
					 CBitmap);

	// check new object
	if(!g_lpNullIcon)
		return(FALSE);
	
	// get desktop dc
	lpDesktopDC=CDC::FromHandle(::GetDC(GetDesktopWindow()));

	// check desktop dc
	if(!lpDesktopDC)
	{
		DisplayErrorMessage("Unable to find desktop device context.");
		return(FALSE);
	}

	// create bitmap
	if(!g_lpNullIcon->CreateCompatibleBitmap(lpDesktopDC,
											 32,32))
	{
		DisplayErrorMessage("Unable to create sort image.");
		return(FALSE);
	}

	// set bitmap colors
	clrLight   =GetSysColor(COLOR_BTNFACE);
	clrHilite  =LightenColor(clrLight,4);
	clrShadow  =DarkenColor(clrLight,4);
	clrDkShadow=DarkenColor(clrLight,3);

	// allocate device context
	AllocClassObject(lpImageDC,
					 CDC);

	// check new object
	if(!lpImageDC)
	{
		ANTIHACK_4
		return(FALSE);
	}

	// create compatible dc
	if(!lpImageDC->CreateCompatibleDC(lpDesktopDC))
	{
		DisplayErrorMessage("Unable to create desktop-compatible device context.");
		return(FALSE);
	}
	else
		AddWinResource

	// select bitmap
	lpImageDC->SelectObject(g_lpNullIcon);

	// erase background
	lpImageDC->FillSolidRect(0,0, 32,32, clrLight);

	// draw border
	lpImageDC->FillSolidRect(0,0,  22,1, clrShadow);
	lpImageDC->FillSolidRect(0,0,  1,30, clrShadow);
	lpImageDC->FillSolidRect(21,0, 1,9,  clrShadow);
	lpImageDC->FillSolidRect(21,9, 9,1,  clrShadow);
	lpImageDC->FillSolidRect(0,30, 30,1, clrDkShadow);
	lpImageDC->FillSolidRect(30,9, 1,22, clrDkShadow);

	// draw page corner
	lpImageDC->SetPixelV(22,1, clrDkShadow);
	lpImageDC->SetPixelV(23,2, clrDkShadow);
	lpImageDC->SetPixelV(24,3, clrDkShadow);
	lpImageDC->SetPixelV(25,4, clrDkShadow);
	lpImageDC->SetPixelV(26,5, clrDkShadow);
	lpImageDC->SetPixelV(27,6, clrDkShadow);
	lpImageDC->SetPixelV(28,7, clrDkShadow);
	lpImageDC->SetPixelV(29,8, clrDkShadow);
	lpImageDC->SetPixelV(22,2, clrShadow);
	lpImageDC->SetPixelV(23,3, clrShadow);
	lpImageDC->SetPixelV(24,4, clrShadow);
	lpImageDC->SetPixelV(25,5, clrShadow);
	lpImageDC->SetPixelV(26,6, clrShadow);
	lpImageDC->SetPixelV(27,7, clrShadow);
	lpImageDC->SetPixelV(28,8, clrShadow);
	lpImageDC->SetPixelV(22,4, clrHilite);
	lpImageDC->SetPixelV(23,5, clrHilite);
	lpImageDC->SetPixelV(24,6, clrHilite);
	lpImageDC->SetPixelV(25,7, clrHilite);
	lpImageDC->SetPixelV(26,8, clrHilite);
	lpImageDC->SetPixelV(22,6, clrHilite);
	lpImageDC->SetPixelV(23,7, clrHilite);
	lpImageDC->SetPixelV(24,8, clrHilite);
	lpImageDC->SetPixelV(22,8, clrHilite);

	// draw square outlines
	lpImageDC->FillSolidRect(5,1,  1,29, clrHilite);
	lpImageDC->FillSolidRect(10,1, 1,5,  clrHilite);
	lpImageDC->FillSolidRect(15,1, 1,5,  clrHilite);
	lpImageDC->FillSolidRect(20,1, 1,5,  clrHilite);
	lpImageDC->FillSolidRect(1,5,  5,1,  clrHilite);
	lpImageDC->FillSolidRect(1,10, 5,1,  clrHilite);
	lpImageDC->FillSolidRect(1,15, 5,1,  clrHilite);
	lpImageDC->FillSolidRect(1,20, 5,1,  clrHilite);
	lpImageDC->FillSolidRect(1,25, 5,1,  clrHilite);

	// draw squares
	lpImageDC->FillSolidRect(6,6,   4,4, clrHilite);
	lpImageDC->FillSolidRect(11,6,  4,4, clrHilite);
	lpImageDC->FillSolidRect(16,6,  4,4, clrHilite);
	lpImageDC->FillSolidRect(6,11,  4,4, clrHilite);
	lpImageDC->FillSolidRect(11,11, 4,4, clrHilite);
	lpImageDC->FillSolidRect(16,11, 4,4, clrHilite);
	lpImageDC->FillSolidRect(21,11, 4,4, clrHilite);
	lpImageDC->FillSolidRect(6,16,  4,4, clrHilite);
	lpImageDC->FillSolidRect(11,16, 4,4, clrHilite);
	lpImageDC->FillSolidRect(16,16, 4,4, clrHilite);
	lpImageDC->FillSolidRect(21,16, 4,4, clrHilite);
	lpImageDC->FillSolidRect(6,21,  4,4, clrHilite);
	lpImageDC->FillSolidRect(11,21, 4,4, clrHilite);
	lpImageDC->FillSolidRect(16,21, 4,4, clrHilite);
	lpImageDC->FillSolidRect(21,21, 4,4, clrHilite);
	lpImageDC->FillSolidRect(6,26,  4,4, clrShadow);
	lpImageDC->FillSolidRect(11,26, 4,4, clrShadow);
	lpImageDC->FillSolidRect(16,26, 4,4, clrShadow);
	lpImageDC->FillSolidRect(21,26, 4,4, clrShadow);
	lpImageDC->FillSolidRect(26,26, 4,4, clrShadow);
	lpImageDC->FillSolidRect(26,21, 4,4, clrShadow);
	lpImageDC->FillSolidRect(26,16, 4,4, clrShadow);
	lpImageDC->FillSolidRect(26,11, 4,4, clrShadow);

	// release device context
	if(lpImageDC->DeleteDC())
		RemoveWinResource

	// free device context
	FreeClassObject(lpImageDC);

	// ok
	return(TRUE);
}

// CMainPropSheet::PreTranslateMessage()

BOOL CMainPropSheet::PreTranslateMessage(MSG* pMsg)
{
	// relay message to tooltip control
	if(g_lpMainToolTip)
		g_lpMainToolTip->RelayEvent(pMsg);

	// check for key-down message
	if(pMsg->message==WM_KEYDOWN)
	{
		// check for enter & esc
		if(pMsg->wParam==VK_ESCAPE||
		   pMsg->wParam==VK_RETURN)
		{
			// eat message
			return(FALSE);
		}
	}

	// call base method
	return(CPropertySheet::PreTranslateMessage(pMsg));
}

// PlaySound()

void PlaySound(UINT nSndID,
			   BOOL bOverrideFlag)
{
	// check flag
	if(g_bPlaySFX||
	   bOverrideFlag)
	{
		// check id
		if(nSndID==ID_DEFSND)
		{
			// default message beep
			MessageBeep(MB_OK);
		}
		else
		{
			// play sound (asynchronously)
			PlaySound((LPCSTR)nSndID,
					  AfxGetInstanceHandle(),
					  SND_RESOURCE|SND_ASYNC);
		}
	}
}

// CDefButton::CDefButton()

CDefButton::CDefButton(UINT nID)
{
	// reset sound id
	nSndId=NULL;

	// reset async flag
	bAsync=TRUE;

	// call base constructor
	this->CExtButton::CExtButton(nID);
}

// CMainPropSheet::OnContextMenu()

void CMainPropSheet::OnContextMenu(CWnd* pWnd,
								   CPoint pos)
{
	// check for ok button
	if(IsPointInWindow(&pos,
					   g_lpDefOKBtn))
		g_lpDefOKBtn->OnContextMenu(pWnd,
									pos);

	// check for cancel button
	if(IsPointInWindow(&pos,
					   g_lpDefCancelBtn))
		g_lpDefCancelBtn->OnContextMenu(pWnd,
									    pos);

	// check for apply button
	if(IsPointInWindow(&pos,
					   g_lpDefApplyBtn))
		g_lpDefApplyBtn->OnContextMenu(pWnd,
									   pos);
}

// CDefButton::OnLButtonUp()

void CDefButton::OnLButtonUp(UINT nFlags,
							 CPoint point)
{
	// check state
	if(GetState()&0x0004)
	{
		// check sound
		if(nSndId)
		{
			// check flag
			if(bAsync)
			{
				// play sound
				PlaySound(nSndId);
			}
			else
			{
				// play sync sound
				PlaySyncSound(nSndId);
			}
		}
	}

	// call base method
	CExtButton::OnLButtonUp(nFlags,
							point);
}

// CDefButton::SetDefSoundId()

void CDefButton::SetDefSoundId(UINT nID,
							   BOOL bAsyncFlag)
{
	// save id
	nSndId=nID;

	// save flag
	bAsync=bAsyncFlag;
}

// PlaySyncSound()

void PlaySyncSound(UINT nSndID,
				   BOOL bOverrideFlag)
{
	// check flag
	if(g_bPlaySFX||
	   bOverrideFlag)
	{
		// check id
		if(nSndID==ID_DEFSND)
		{
			// default message beep
			MessageBeep(MB_OK);
		}
		else
		{
			// play sound (synchronously)
			PlaySound((LPCSTR)nSndID,
					  AfxGetInstanceHandle(),
					  SND_RESOURCE);
		}
	}
}

// CExtDialog::OnOK()

void CExtDialog::OnOK(void)
{
	// reset close-ok flag
	bCloseOK=TRUE;

	// apply changes
	ApplyChanges();
	
	// check close-ok flag
	if(!bCloseOK)
		return;

	// release dialog
	ReleaseDialog();

	// check close-ok flag
	if(!bCloseOK)
		return;

	// release buttons
	FreeClassObject(lpOKBtn);
	FreeClassObject(lpCancelBtn);

	// call base method
	CDialog::OnOK();
}

// CExtDialog::OnCancel()

void CExtDialog::OnCancel(void)
{
	// reset close-ok flag
	bCloseOK=TRUE;

	// release dialog
	ReleaseDialog();

	// check close-ok flag
	if(!bCloseOK)
		return;

	// release buttons
	FreeClassObject(lpOKBtn);
	FreeClassObject(lpCancelBtn);

	// call base method
	CDialog::OnCancel();
}

// CExtDialog::ApplyChanges()

void CExtDialog::ApplyChanges(void)
{
	// NOTE: Derived classes must call
	//       this version of ApplyChanges()
	//       for proper functioning.

ANTIHACK_3

	// reset modified state
	SetModified(FALSE);
}

// CMainPropSheet::OnSysCommand()

void CMainPropSheet::OnSysCommand(UINT nID,
								  LPARAM lParam)
{
	// check for screensaver command
	if((nID&0xFFF0)==SC_SCREENSAVE)
	{
		// check screensaver flag
		if(!g_bAllowWinSaver)
		{
			// do not process
			return;
		}
	}

	// call base method
	CPropertySheet::OnSysCommand(nID,
								 lParam);
}

// CExtDialog::OnInitDialog()

BOOL CExtDialog::OnInitDialog(void)
{
	// call base method
	CDialog::OnInitDialog();

	// create ok button
	if(CreateExtButton(&lpOKBtn,
					   IDC_DLGOKBTN))
	{
		// capture ok button
		if(!CaptureDlgControl(this,
							  lpOKBtn,
							  IDOK,
							  TRUE))
		{
			// button does not exist
			FreeClassObject(lpOKBtn);
		}
	}

	// create cancel button
	if(CreateExtButton(&lpCancelBtn,
					   IDC_DLGCANCELBTN))
	{
		// capture cancel button
		if(!CaptureDlgControl(this,
							  lpCancelBtn,
							  IDCANCEL,
							  TRUE))
		{
			// button does not exist
			FreeClassObject(lpCancelBtn);
		}
	}

	// reset apply button
	lpApplyBtn=NULL;

	// reset must-close flag
	bMustClose=FALSE;

	// perform initialization
	if(!InitDialog())
		ForceImmediateExit();

	// ok
	return(TRUE);
}

// CExtDialog::InitDialog()

BOOL CExtDialog::InitDialog(void)
{
	// reserved for future use

	// ok
	return(TRUE);
}

// CExtDialog::ReleaseDialog()

void CExtDialog::ReleaseDialog(void)
{
	// reserved for future use
}

// CExtDialog::CaptureApplyBtn()

BOOL CExtDialog::CaptureApplyBtn(CExtButton* lpBtn)
{
	// capture control
	if(!CaptureDlgControl(this,
						  lpBtn,
						  IDC_APPLY))
		return(FALSE);

	// store button interface
	lpApplyBtn=lpBtn;

	// set proper id
	lpApplyBtn->nCtrlId=IDC_DLGAPPLYBTN;

	// set unmodified state
	SetModified(FALSE);

	// ok
	return(TRUE);
}

// CExtDialog::SetModified()

void CExtDialog::SetModified(BOOL bState)
{
	// check apply button
	if(!lpApplyBtn)
		return;

	// check flag & set button
	if(bState)
		lpApplyBtn->Enable();
	else
		lpApplyBtn->Disable();
}

// CExtDialog::OnApply()

void CExtDialog::OnApply(void)
{
	// apply changes
	ApplyChanges();

	// check must-close flag
	if(bMustClose)
	{
		// close now
		OnCancel();
	}
}

// CExtDialog::CloseNotOK()

void CExtDialog::CloseNotOK(void)
{
	// set flag
	bCloseOK=FALSE;
}

// CMainPropSheet::OnGHelpBtn()

void CMainPropSheet::OnGHelpBtn(void)
{
	// show general help
	ShowHelp(NULL,
			 NULL);
}

// CMainPropSheet::CreateExtraButtons()

BOOL CMainPropSheet::CreateExtraButtons(void)
{
	// tab control window
	CTabCtrl* lpTabCtrl=NULL;

	// tab control position
	CRect rTabCtrl;

	// default button positions
	CRect rDefOK;
	CRect rDefCancel;
	CRect rDefApply;
	
	// new button positions
	CRect rGHelp;
	CRect rAbout;
	CRect rPrefs;
	CRect rPurch;

	// default font
	CFont* lpDefFont=NULL;

	// button spacing
	int nBtnSpcA;
	int nBtnSpcB;
	int nBtnSpc;
	
	// center position
	int nXCen;

	// leftmost position
	int nLeftMost;

	// get tab control
	lpTabCtrl=GetTabControl();

	// check tab control
	if(!lpTabCtrl)
	{
		DisplayErrorMessage("Unable to find main tab control window.");
		return(FALSE);
	}

	// get position of tab control
	lpTabCtrl->GetWindowRect(&rTabCtrl);

	// get positions of default buttons
	g_lpDefOKBtn->GetWindowRect(&rDefOK);
	g_lpDefCancelBtn->GetWindowRect(&rDefCancel);
	g_lpDefApplyBtn->GetWindowRect(&rDefApply);

	// convert to client positions
	ScreenToClient(&rTabCtrl);
	ScreenToClient(&rDefOK);
	ScreenToClient(&rDefCancel);
	ScreenToClient(&rDefApply);

	// set button spacing
	nBtnSpcA=abs(rDefCancel.left-rDefOK.left);
	nBtnSpcB=abs(rDefCancel.left-rDefApply.left);
	nBtnSpc =(nBtnSpcA<nBtnSpcB) ? nBtnSpcA : nBtnSpcB;

	// set help button position
	rGHelp.left  =rTabCtrl.left;
	rGHelp.right =rGHelp.left+rDefOK.Width();
	rGHelp.top   =rDefOK.top,
	rGHelp.bottom=rGHelp.top+rDefOK.Height();

	// set about button position
	rAbout.left  =rGHelp.left+nBtnSpc;
	rAbout.right =rAbout.left+rDefOK.Width();
	rAbout.top   =rDefOK.top;
	rAbout.bottom=rAbout.top+rDefOK.Height();

	// set prefs button position
	rPrefs.left  =rAbout.left+nBtnSpc;
	rPrefs.right =rPrefs.left+rDefOK.Width();
	rPrefs.top   =rDefOK.top,
	rPrefs.bottom=rPrefs.top+rDefOK.Height();

	// calculate leftmost button
	nLeftMost=rDefOK.left;
	if(rDefCancel.left<nLeftMost)
		nLeftMost=rDefCancel.left;
	if(rDefApply.left<nLeftMost)
		nLeftMost=rDefApply.left;

	// get center of remaining area
	nXCen=(rPrefs.right+nLeftMost)>>1;

	// set purchase button position
	rPurch.left  =nXCen-(rDefOK.Width()>>1);
	rPurch.right =rPurch.left+rDefOK.Width();
	rPurch.top   =rDefOK.top,
	rPurch.bottom=rPurch.top+rDefOK.Height();

	// create help button
	if(!g_lpGHelpBtn->Create("Help",
							 WS_CHILD|
							 WS_VISIBLE|
							 WS_TABSTOP|
							 BS_PUSHBUTTON,
							 rGHelp,
							 this,
							 IDC_GHELPBTN))
	{
		DisplayErrorMessage("Unable to create help button.");
		return(FALSE);
	}
	else
		AddWinResource

	// create about button
	if(!g_lpAboutBtn->Create("About...",
							 WS_CHILD|
							 WS_VISIBLE|
							 WS_TABSTOP|
							 BS_PUSHBUTTON,
							 rAbout,
							 this,
							 IDC_ABOUTBTN))
	{
		DisplayErrorMessage("Unable to create about button.");
		return(FALSE);
	}
	else
		AddWinResource

	// create prefs button
	if(!g_lpPrefsBtn->Create("Preferences",
							 WS_CHILD|
							 WS_VISIBLE|
							 WS_TABSTOP|
							 BS_PUSHBUTTON,
							 rPrefs,
							 this,
							 IDC_PREFSBTN))
	{
		DisplayErrorMessage("Unable to create preferences button.");
		return(FALSE);
	}
	else
		AddWinResource

	// create purchase button
	if(!g_lpPurchBtn->Create("Buy Now!",
							 WS_CHILD|
							 WS_VISIBLE|
							 WS_TABSTOP|
							 BS_PUSHBUTTON,
							 rPurch,
							 this,
							 IDC_PURCHBTN))
	{
		DisplayErrorMessage("Unable to create purchase button.");
		return(FALSE);
	}
	else
		AddWinResource

	// get default font
	lpDefFont=g_lpDefOKBtn->GetFont();

	// check font
	if(!lpDefFont)
	{
		DisplayErrorMessage("Unable to read default button font.");
		return(FALSE);
	}

	// set button fonts
	g_lpGHelpBtn->SetFont(lpDefFont);
	g_lpAboutBtn->SetFont(lpDefFont);
	g_lpPrefsBtn->SetFont(lpDefFont);
	g_lpPurchBtn->SetFont(lpDefFont);

#ifndef SHAREWARE_MODE
	// hide purchase button
	g_lpPurchBtn->ShowWindow(SW_HIDE);
#endif

	// ok
	return(TRUE);
}

// CMainPropSheet::DestroyExtraButtons()

void CMainPropSheet::DestroyExtraButtons(void)
{
	// destroy button
	if(g_lpGHelpBtn)
		if(IsWindow(g_lpGHelpBtn->m_hWnd))
			if(g_lpGHelpBtn->DestroyWindow())
				RemoveWinResource

	// destroy button
	if(g_lpAboutBtn)
		if(IsWindow(g_lpAboutBtn->m_hWnd))
			if(g_lpAboutBtn->DestroyWindow())
				RemoveWinResource

	// destroy button
	if(g_lpPrefsBtn)
		if(IsWindow(g_lpPrefsBtn->m_hWnd))
			if(g_lpPrefsBtn->DestroyWindow())
				RemoveWinResource

	// destroy button
	if(g_lpPurchBtn)
		if(IsWindow(g_lpPurchBtn->m_hWnd))
			if(g_lpPurchBtn->DestroyWindow())
				RemoveWinResource
}

// CExtDialog::OnShowWindow()

void CExtDialog::OnShowWindow(BOOL bShow,
							  UINT nStatus)
{
	// call base method
	CDialog::OnShowWindow(bShow,
						  nStatus);

	// check show flag
	if(bShow)
	{
		// set focus to ok button
		if(lpOKBtn)
			lpOKBtn->SetFocus();
	}
}

// CExtDialog::OnContextMenu()

void CExtDialog::OnContextMenu(CWnd* pWnd,
							   CPoint pos)
{
	// check for ok button
	if(lpOKBtn)
		if(IsPointInWindow(&pos,
						   lpOKBtn))
			lpOKBtn->OnContextMenu(pWnd,
								   pos);

	// check for cancel button
	if(lpCancelBtn)
		if(IsPointInWindow(&pos,
						   lpCancelBtn))
			lpCancelBtn->OnContextMenu(pWnd,
									   pos);

	// check for apply button
	if(lpApplyBtn)
		if(IsPointInWindow(&pos,
						   lpApplyBtn))
			lpApplyBtn->OnContextMenu(pWnd,
									  pos);
}

// SortIntList()

void SortIntList(int* lpnVal,
				 int nNumVal)
{
#ifdef DEBUG_MODE
	// verify list
	if(!lpnVal)
	{
		DisplayErrorMessage("Inavalid pointer value.",
							"SortIntList()",
							FALSE);
		return;
	}
#endif

	// changes flag
	BOOL bChanges=TRUE;

	// counter
	int nCount;

	// perform sort
	while(bChanges)
	{
		// reset flag
		bChanges=FALSE;

		// sort list
		for(nCount=0;nCount<nNumVal-1;nCount++)
		{
			// compare value with next
			if(lpnVal[nCount]>lpnVal[nCount+1])
			{
				// swap values
				int nTemp=lpnVal[nCount];
				lpnVal[nCount+1]=lpnVal[nCount];
				lpnVal[nCount]=nTemp;

				// set flag
				bChanges=TRUE;
			}
		}
	}
}

#ifdef DEBUG_MODE
// CheckProcessList()

void CheckProcessList(void)
{
#ifdef CHECK_PROCESSES
	// process entry
	PROCESSENTRY32 pe;

	// new process list
	LPSTR lpNewProcs=NULL;

	LockGlobalLongMsg()

	// load previous process list
	if(!LoadOptionString("Debug_ProcList",
						 g_lpLongMsg))
	{
		// reset string
		strcpy(g_lpLongMsg,
			   "**");
	}

	// allocate new process list
	if(!AllocMem((LPVOID*)&lpNewProcs,
				 LONG_MSG_SIZE))
	{
		UnlockGlobalLongMsg()
		return;
	}

	// get handle to process list
	HANDLE hProcList=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,
											  NULL);

	// check handle
	if(hProcList==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("CreateToolhelp32Snapshot() failed");
		UnlockGlobalLongMsg()
		return;
	}
	else
		AddWinResource

	// get first process entry
	if(!Process32First(hProcList,
					   &pe))
	{
		DisplayErrorMessage("Process32First() failed");
		UnlockGlobalLongMsg()
		return;
	}

	LockGlobalMsg()
	
	// isolate filename
	GetFilenameFromPath(g_lpMsg,
						_MAX_PATH,
						pe.szExeFile);

	// convert to lowercase
	strlwr(g_lpMsg);

	// begin new process list
	strcpy(lpNewProcs,
		   g_lpMsg);

	// append terminator
	strcat(lpNewProcs,
		   "*");

	// check for process
	if(!IsProcessInList(g_lpMsg,
						g_lpLongMsg))
		DisplayMessageBox(g_hWnd,
						  g_lpMsg,
						  "New Process",
						  MB_OK);

	UnlockGlobalMsg()

	// get remaining entries
	while(Process32Next(hProcList,
						&pe))
	{
		LockGlobalMsg()
		
		// isolate filename
		GetFilenameFromPath(g_lpMsg,
							_MAX_PATH,
							pe.szExeFile);

		// convert to lowercase
		strlwr(g_lpMsg);

		// add process to list
		strcat(lpNewProcs,
			   g_lpMsg);

		// append terminator
		strcat(lpNewProcs,
			   "*");

		// check for process
		if(!IsProcessInList(g_lpMsg,
							g_lpLongMsg))
			DisplayMessageBox(g_hWnd,
							  g_lpMsg,
							  "New Process",
							  MB_OK);

		UnlockGlobalMsg()
	}

	// append final terminator
	strcat(lpNewProcs,
		   "*");

	UnlockGlobalLongMsg()

	// save process list
	SaveOptionString("Debug_ProcList",
					 lpNewProcs);

	// release handle to process list
	if(CloseHandle(hProcList))
		RemoveWinResource

	// release new process list
	FreeMem((LPVOID*)&lpNewProcs);
#endif
}

// IsProcessInList()

BOOL IsProcessInList(LPSTR lpProc,
					 LPSTR lpList)
{
#ifdef CHECK_PROCESSES
	// string to check
	char lpStr[128];

	// string pointers
	int nListPtr;
	int nStrPtr;

	// reset list pointer
	nListPtr=0;

	// search string
	while(TRUE)
	{
		// reset string pointer
		nStrPtr=0;

		// extract next string
		while(lpList[nListPtr++]!='*')
		{
			// copy byte
			lpStr[nStrPtr++]=lpList[nListPtr-1];
		}

		// set null terminator
		lpStr[nStrPtr]=0;

		// check length
		if(strlen(lpStr)==0)
		{
			// stop here
			return(FALSE);
		}

		// compare strings
		if(strcmp(lpStr,
				  lpProc)==0)
		{
			// ok
			return(TRUE);
		}
	}
#endif

	// default reply
	return(FALSE);
}
#endif

// CExtDialog::ApplyToClose()

void CExtDialog::ApplyToClose(void)
{
	// check apply button
	if(!lpApplyBtn)
		return;

	// disable close button
	if(!DisableSysMenuClose(this))
		ForceImmediateExit();

	// destroy ok button
	FreeClassObject(lpOKBtn);
	
	// destroy cancel button
	FreeClassObject(lpCancelBtn);

	// change 'apply' to 'close'
	lpApplyBtn->SetWindowText("Close");

	// change button id
	lpApplyBtn->nCtrlId=IDC_DLGOKBTN;

	// enable apply button
	lpApplyBtn->Enable();
	
	// set must-close flag
	bMustClose=TRUE;
}

// CMainPropSheet::ApplyChanges()

void CMainPropSheet::ApplyChanges(void)
{
	// set initialized flag
	SaveOptionInt("Misc_InitFlag",
				  1);

	// save preferences
	SavePreferences();
	
	// restart tsr
	RestartTSR();
}

// CPlaylistCtrl::AddToList()

BOOL CPlaylistCtrl::AddToList(LPVOID lpItemData,
							  LPSTR lpTitle,
							  LPSTR lpSave,
							  BOOL bLoading)
{
	// item info
	LVITEM lvi;

	// item number
	int nItem;

	// pointer to playlist data
	LPPLAYLISTDATA lpData;

	// check data counter
	if(nNumDataItems==0)
	{
		// allocate list
		if(!AllocMem((LPVOID*)&lpPListData,
					 sizeof(PLAYLISTDATA)*PLIST_DATA_INC))
			return(FALSE);

		// set max items
		nMaxDataItems=PLIST_DATA_INC;
	}
	else if(nNumDataItems>=nMaxDataItems)
	{
		// expand list
		if(!ExpandMem((LPVOID*)&lpPListData,
					  sizeof(PLAYLISTDATA)*nMaxDataItems,
					  sizeof(PLAYLISTDATA)*PLIST_DATA_INC))
			return(FALSE);

		// increment max items
		nMaxDataItems+=PLIST_DATA_INC;
	}

	// save pointer to data
	lpData=&lpPListData[nNumDataItems];

	// increment counter (indexing system is 1-based)
	nNumDataItems++;

	// copy user data
	lpData->lpUserData=lpItemData;

	// reset strings
	lpData->lpTitle=NULL;
	lpData->lpSave =NULL;

	LockGlobalLongMsg()

	// check for title
	if(lpTitle)
	{
		// copy title
		strcpy(g_lpLongMsg,
			   lpTitle);
	}
	else
	{
		// get string
		if(!GetItemStringCallback(g_lpLongMsg,
								  lpItemData))
		{
			// copy empty string
			strcpy(g_lpLongMsg,
				   NO_SEL_TEXT);
		}
	}

	// allocate memory for title
	if(!AllocMem((LPVOID*)&lpData->lpTitle,
				 strlen(g_lpLongMsg)+1))
	{
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	// copy string
	strcpy(lpData->lpTitle,
		   g_lpLongMsg);

	// check for save string
	if(lpSave)
	{
		// copy string
		strcpy(g_lpLongMsg,
			   lpSave);
	}
	else
	{
		// get string
		if(!GetItemSaveCallback(g_lpLongMsg,
								lpItemData))
		{
			// copy empty string
			strcpy(g_lpLongMsg,
				   NO_SEL_TEXT);
		}
	}

	// allocate memory for save string
	if(!AllocMem((LPVOID*)&lpData->lpSave,
				 strlen(g_lpLongMsg)+1))
	{
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	// copy string
	strcpy(lpData->lpSave,
		   g_lpLongMsg);

	// get item number
	nItem=GetItemCount();

	// copy title
	strcpy(g_lpLongMsg,
		   lpData->lpTitle);

	// get item string
	GetItemString(nItem,
				  g_lpLongMsg);

	// prepare item info
	lvi.mask      =LVIF_TEXT|
			       LVIF_PARAM;
	lvi.iItem     =nItem;
	lvi.iSubItem  =0;
	lvi.pszText   =g_lpLongMsg;
	lvi.cchTextMax=_MAX_PATH;
	lvi.lParam    =(LPARAM)nNumDataItems;

	// add item
	if(InsertItem(&lvi)==-1)
	{
		DisplayNEErrorMessage("Unable to add item to playlist.");
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	UnlockGlobalLongMsg()

	// check loading flag
	if(!bLoading)
	{
		// make item visible
		EnsureVisible(nItem,
					  FALSE);

		// highlight item
		SetItemState(nItem,
					 LVIS_FOCUSED|
					 LVIS_SELECTED,
					 0xFF);

		// set parent modified
		SetParentModified();

		// enable global buttons
		EnableGlobalButtons();
	}

	// ok
	return(TRUE);
}

// CPlaylistCtrl::MoveSelUp()

void CPlaylistCtrl::MoveSelUp(void)
{
	// set flag
	bMoving=TRUE;

	// get current selection
	int nSelItem=GetSelection();

	// check for valid selection
	if(nSelItem!=-1&&
	   nSelItem!=0)
	{
		// swap items
		SwapItems(nSelItem,
				  nSelItem-1);
	}

	// reset flag
	bMoving=FALSE;
}

// CPlaylistCtrl::MoveSelDown()

void CPlaylistCtrl::MoveSelDown(void)
{
	// set flag
	bMoving=TRUE;

	// get current selection
	int nSelItem=GetSelection();

	// get max item
	int nMaxItem=GetItemCount()-1;

	// check for valid selection
	if(nSelItem!=-1&&
	   nSelItem!=nMaxItem)
	{
		// swap items
		SwapItems(nSelItem,
				  nSelItem+1);
	}

	// reset flag
	bMoving=FALSE;
}

// CPlaylistCtrl::GetPlaylistItemData()

BOOL CPlaylistCtrl::GetPlaylistItemData(int nItem,
										LPPLAYLISTDATA* lplpData)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lplpData)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CPlaylistCtrl::GetPlaylistItemData()",
							FALSE);
		return(FALSE);
	}
#endif

	// clear pointer
	(*lplpData)=NULL;

	// get data index
	int nIndex=((int)GetItemData(nItem))-1;

	// check for error
	if(nIndex<0||
	   nIndex>=nNumDataItems)
		return(FALSE);

	// copy data pointer
	(*lplpData)=&lpPListData[nIndex];

	// ok
	return(TRUE);
}

// CPlaylistCtrl::DeleteSel()

void CPlaylistCtrl::DeleteSel(void)
{
	// counter
	int nCount;

	// pointer to playlist data
	LPPLAYLISTDATA lpData;

	// item indices
	int nSelItem;
	int nNumItems;
	
	// get current selection
	nSelItem=GetSelection();

	// check for valid selection
	if(nSelItem==-1)
		return;

	// remove selection
	DeleteItem(nSelItem);

	// get number of items
	nNumItems=GetItemCount();

	// check for items
	if(nNumItems)
	{
		// move remaining items up
		for(nCount=nSelItem;nCount<nNumItems;nCount++)
		{
			// get playlist data
			if(GetPlaylistItemData(nCount,
								   &lpData))
			{
				LockGlobalLongMsg()

				// copy title
				strcpy(g_lpLongMsg,
					   lpData->lpTitle);

				// get new string
				GetItemString(nCount,
							  g_lpLongMsg);

				// set new string
				SetItemText(nCount,
							0,
							g_lpLongMsg);

				UnlockGlobalLongMsg()
			}
		}

		// validate item
		if(nSelItem>=nNumItems)
			nSelItem=nNumItems-1;

		// highlight item
		SetItemState(nSelItem,
					 LVIS_FOCUSED|
					 LVIS_SELECTED,
					 0xFF);

		// make sure item is visible
		EnsureVisible(nSelItem,
					  FALSE);

		// give focus to playlist
		SetFocus();
	}
	else
	{
		// disable global buttons
		DisableGlobalButtons();
	}

	// play sound
	PlaySound(IDR_CLEARSELSND);

	// set parent modified
	SetParentModified();
}

// CPlaylistCtrl::ClearList()

void CPlaylistCtrl::ClearList(BOOL bSilent)
{
	// parent window
	HWND hParentWnd;

	// counter
	int nCount;

	// check flag
	if(!bSilent)
	{
		// set parent window
		hParentWnd=(lpParentDlg ? lpParentDlg->m_hWnd : (lpParentPropPage ? lpParentPropPage->m_hWnd : this->m_hWnd));

		// query user
		if(DisplayMessageBox(hParentWnd,
							 "This will remove all selections from the current\nplaylist, and any unsaved changes will be lost.\n\nAre you sure?",
							 (LPSTR)ApplicationName(),
							 MB_YESNO|MB_ICONWARNING)==IDNO)
			return;

		// play sound
		PlaySound(IDR_DELALLSND);
	}
	
	// check selection
	if(QuerySelection())
	{
		// clear selection
		SetItemState(GetSelection(),
					 NULL,
					 LVIS_SELECTED);
	}

	// delete all items
	DeleteAllItems();

	// relase playlist data items
	for(nCount=0;nCount<nNumDataItems;nCount++)
	{
		// release strings
		FreeMem((LPVOID*)&lpPListData[nCount].lpTitle);
		FreeMem((LPVOID*)&lpPListData[nCount].lpSave);
	}

	// release playlist data
	FreeMem((LPVOID*)&lpPListData);

	// reset counters
	nNumDataItems=0;
	nMaxDataItems=0;

	// disable nacigation buttons
	DisableNavButtons();

	// disable global buttons
	DisableGlobalButtons();

	// check flag
	if(!bSilent)
	{
		// set parent modified
		SetParentModified();

		// set saved flag
		bIsSaved=TRUE;
	}
}

// CPlaylistCtrl::SaveListReg()

BOOL CPlaylistCtrl::SaveListReg(LPCSTR lpAppKey,
							    LPCSTR lpSubKey)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpAppKey||
	   !lpSubKey)
	{
		DisplayErrorMessage("Invalid string value.",
							"CPlaylistCtrl::SaveListReg()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// return value
	BOOL bRet;

	// counter
	int nCount;

	// number of items
	int nNumItems;

	// playlist data
	LPPLAYLISTDATA lpData;

	// reset return value
	bRet=TRUE;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	// get number of items
	nNumItems=GetItemCount();

	// reset counter
	nCount=0;

	LockGlobalLongMsg()
	
	// create registry key
	strcpy(g_lpLongMsg,
		   lpAppKey);
	strcat(g_lpLongMsg,
		   lpSubKey);

	// create registry key
	if(lpRegKey->Create(HKEY_CURRENT_USER,
						g_lpLongMsg,
						REG_NONE,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS,
						NULL,
						NULL)==ERROR_SUCCESS)
	{
		AddWinResource

		UnlockGlobalLongMsg()

		// output values
		while(TRUE)
		{
			// check counter
			if(nCount<nNumItems)
			{
				// get playlist data
				if(!GetPlaylistItemData(nCount,
										&lpData))
				{
					// clear data
					lpData=NULL;
				}
			}
			else
			{
				// clear data
				lpData=NULL;
			}

			LockGlobalLongMsg()

			// copy title string
			strcpy(g_lpLongMsg,
				   (lpData ? lpData->lpTitle : NULL_STRING));

			LockGlobalMsg()

			// create key name
			sprintf(g_lpMsg,
					"DefStr%u",
					nCount);

			// set value
			if(lpRegKey->SetValue(g_lpLongMsg,
								  g_lpMsg)!=ERROR_SUCCESS)
			{
				// alert user
				DisplayNEErrorMessage("Unable to write value to system registry.");

				// set return value
				bRet=FALSE;
			}

			UnlockGlobalMsg()
			
			// copy save string
			strcpy(g_lpLongMsg,
				   (lpData ? lpData->lpSave : NULL_STRING));

			LockGlobalMsg()

			// create key name
			sprintf(g_lpMsg,
					"ItemData%u",
					nCount);

			// set value
			if(lpRegKey->SetValue(g_lpLongMsg,
								  g_lpMsg)!=ERROR_SUCCESS)
			{
				// alert user
				DisplayNEErrorMessage("Unable to write value to system registry.");

				// set return value
				bRet=FALSE;
			}

			UnlockGlobalMsg()
			UnlockGlobalLongMsg()

			// increment counter
			nCount++;

			// check for overflow
			if(nCount>nNumItems)
				break;
		}

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}
	else
		UnlockGlobalLongMsg()

	// relese key interface
	FreeClassObject(lpRegKey);

	// copy saved flag
	bIsSaved=bRet;

	// return result
	return(bRet);
}

// CPlaylistCtrl::LoadListReg()

BOOL CPlaylistCtrl::LoadListReg(LPCSTR lpAppKey,
							    LPCSTR lpSubKey)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpAppKey||
	   !lpSubKey)
	{
		DisplayErrorMessage("Invalid string value.",
							"CPlaylistCtrl::LoadListReg()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// length of buffer
	DWORD dwLen;

	// string pointers
	LPSTR lpTitle=NULL;
	LPSTR lpSave =NULL;

	// reset continue flag
	BOOL bCont=TRUE;

	// reset counter
	int nCount=0;

	// pointer to item data
	LPVOID lpItemData;

	// reset invalid items flag
	BOOL bInvItems=FALSE;

	// clear list
	ClearList(TRUE);

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	LockGlobalMsg()

	// create registry key
	strcpy(g_lpMsg,
		   lpAppKey);
	strcat(g_lpMsg,
		   lpSubKey);

	// open registry key
	if(lpRegKey->Open(HKEY_CURRENT_USER,
					  g_lpMsg)==ERROR_SUCCESS)
	{
		AddWinResource

		UnlockGlobalMsg()

		// input values
		while(bCont)
		{
			LockGlobalMsg()

			// create key name
			sprintf(g_lpMsg,
					"DefStr%u",
					nCount);

			LockGlobalLongMsg()

			// set buffer size
			dwLen=_MAX_PATH;

			// get value
			if(lpRegKey->QueryValue(g_lpLongMsg,
									g_lpMsg,
									&dwLen)!=ERROR_SUCCESS)
			{
				UnlockGlobalMsg()
				UnlockGlobalLongMsg()

				// stop here
				bCont=FALSE;
			}
			else
			{
				UnlockGlobalMsg()

				// check length of string
				if(strlen(g_lpLongMsg)==0)
				{
					UnlockGlobalLongMsg()

					// stop here
					bCont=FALSE;
				}
				else
				{
					// allocate memory for title
					if(!AllocMem((LPVOID*)&lpTitle,
								 strlen(g_lpLongMsg)+1))
					{
						UnlockGlobalLongMsg()

						// stop here
						bCont=FALSE;
					}
					else
					{
						// copy string
						strcpy(lpTitle,
							   g_lpLongMsg);

						UnlockGlobalLongMsg()

						LockGlobalMsg()

						// create key name
						sprintf(g_lpMsg,
								"ItemData%u",
								nCount);

						LockGlobalLongMsg()

						// set buffer size
						dwLen=_MAX_PATH;

						// get value
						if(lpRegKey->QueryValue(g_lpLongMsg,
												g_lpMsg,
												&dwLen)!=ERROR_SUCCESS)
						{
							UnlockGlobalMsg()
							UnlockGlobalLongMsg()

							// stop here
							bCont=FALSE;
						}
						else
						{
							UnlockGlobalMsg()

							// check length of string
							if(strlen(g_lpLongMsg)==0)
							{
								UnlockGlobalLongMsg()

								// stop here
								bCont=FALSE;
							}
							else
							{
								// allocate memory for save string
								if(!AllocMem((LPVOID*)&lpSave,
											 strlen(g_lpLongMsg)+1))
								{
									UnlockGlobalLongMsg()

									// stop here
									bCont=FALSE;
								}
								else
								{
									// copy string
									strcpy(lpSave,
										   g_lpLongMsg);

									UnlockGlobalLongMsg()

									// get item data from save string
									lpItemData=GetItemDataCallback(lpSave);

									// check item data
									if(lpItemData!=NULL&&
									   lpItemData!=IGNORE_ITEM_DATA)
									{
										// add item with validated info
										AddToList(lpItemData,
												  NULL,
												  NULL,
												  TRUE);
									}
									else
									{
										// add item with stored info
										AddToList(NULL,
												  lpTitle,
												  lpSave,
												  TRUE);

										// check for ignore flag
										if(lpItemData!=IGNORE_ITEM_DATA)
										{
											// set invalid-items flag
											bInvItems=TRUE;
										}
									}
								}
							}
						}
					}
				}
			}

			// release strings
			FreeMem((LPVOID*)&lpTitle);
			FreeMem((LPVOID*)&lpSave);

			// increment counter
			nCount++;
		}

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}
	else
		UnlockGlobalMsg()
	
	// relese key interface
	FreeClassObject(lpRegKey);

	// check for invalid items
	if(bInvItems)
	{
		// inform user
		DisplayOptMessageBox(INV_ITEMS_MSG,
							 (LPSTR)ApplicationName(),
							 MB_OK|MB_ICONEXCLAMATION,
							 "MsgBox_PLInvItems");
	}

	// init navigation buttons
	DisableNavButtons();

	// init global buttons
	if(GetItemCount())
		EnableGlobalButtons();
	else
		DisableGlobalButtons();

	// set saved flag
	bIsSaved=TRUE;

	// ok
	return(TRUE);
}

// CPlaylistCtrl::QuerySelection()

BOOL CPlaylistCtrl::QuerySelection(void)
{
	// check for selection
	return(GetFirstSelectedItemPosition() ? TRUE : FALSE);
}

// CPlaylistCtrl::GetSelection()

int CPlaylistCtrl::GetSelection(void)
{
	// position value
	POSITION pos;

	// get first position
	pos=GetFirstSelectedItemPosition();

	// check position
	return(pos ? GetNextSelectedItem(pos) : -1);
}

// CPlaylistCtrl::OnRtClick()

void CPlaylistCtrl::OnRtClick(NMHDR* pNMHDR,
							  LRESULT* pResult)
{
	// show popup menu
	if(nCtrlId)
		ShowPopupMenu(nCtrlId);
}

// CPlaylistCtrl::OnClick()

void CPlaylistCtrl::OnClick(NMHDR* pNMHDR,
							LRESULT* pResult)
{
	// nothing special
}

// CPlaylistCtrl::OnNotify()

BOOL CPlaylistCtrl::OnNotify(WPARAM wParam,
							 LPARAM lParam,
							 LRESULT* pResult)
{
	// cast pointer to notification header
	LPNMHDR lpNM=(LPNMHDR)lParam;

	// check notification code
	switch(lpNM->code)
	{
	// right click
	case(NM_RCLICK):

		// show popup menu
		ShowPopupMenu(nHdrId);

		// ok
		return(TRUE);

	// header resize
	case(HDN_BEGINTRACKA):
	case(HDN_BEGINTRACKW):

		// do not allow tracking
		(*pResult)=TRUE;

		// ok
		return(TRUE);

	// divider double-click
	case(HDN_DIVIDERDBLCLICKA):
	case(HDN_DIVIDERDBLCLICKW):

		// do nothing

		// ok
		return(TRUE);

	// all other messages
	default:

		// call base function
		return(CListCtrl::OnNotify(wParam,
								   lParam,
								   pResult));
	}
}

// CPlaylistCtrl::PreTranslateMessage()

BOOL CPlaylistCtrl::PreTranslateMessage(MSG* pMsg)
{
	// call base method
	return(CListCtrl::PreTranslateMessage(pMsg));
}

// CPlaylistCtrl::OnItemChanged()

void CPlaylistCtrl::OnItemChanged(NMHDR* pNMHDR,
								  LRESULT* pResult)
{
	// get pointer to item change header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// new selection
	if(lpLV->uNewState&LVIS_SELECTED&&
	   !(lpLV->uOldState&LVIS_SELECTED))
	{
		// enable buttons
		EnableNavButtons(lpLV->iItem);
		
		// play sound
		PlaySound(IDR_NEWSELSND);
	}
	
	// cleared selection
	if(!(lpLV->uNewState&LVIS_SELECTED)&&
	   lpLV->uOldState&LVIS_SELECTED)
	{
		// check for selection
		if(!QuerySelection())
		{
			// disable buttons
			DisableNavButtons();
		}
	}

	// set return value
	(*pResult)=NULL;
}

// CPlaylistCtrl::CPlaylistCtrl()

CPlaylistCtrl::CPlaylistCtrl()
{
	// reset callbacks
	SetCallbacks(NULL,
				 NULL,
				 NULL,
				 NULL);

	// reset values
	nCtrlId=NULL;
	nHdrId=NULL;
	lpHdrCtrl=NULL;
	lpUpBtn=NULL;
	lpDownBtn=NULL;
	lpTopBtn=NULL;
	lpBottomBtn=NULL;
	lpDeleteBtn=NULL;
	lpClearBtn=NULL;
	lpSaveBtn=NULL;
	lpLoadBtn=NULL;
	lpParentDlg=NULL;
	lpParentPropPage=NULL;
	lpPListData=NULL;
	nNumDataItems=0;
	nMaxDataItems=0;
	lpAuxCtrl1=NULL;
	lpAuxCtrl2=NULL;
	lpAuxCtrl3=NULL;
	lpAuxCtrl4=NULL;
	bMoving=FALSE;
	bIsSaved=FALSE;

	// call base method
	CListCtrl::CListCtrl();
}

// CPlaylistCtrl::Release()

void CPlaylistCtrl::Release(void)
{
	// counter
	int nCount;

	// reset flags
	bMoving=FALSE;

	// relase playlist data items
	for(nCount=0;nCount<nNumDataItems;nCount++)
	{
		// release strings
		FreeMem((LPVOID*)&lpPListData[nCount].lpTitle);
		FreeMem((LPVOID*)&lpPListData[nCount].lpSave);
	}

	// release playlist data
	FreeMem((LPVOID*)&lpPListData);

	// reset counters
	nNumDataItems=0;
	nMaxDataItems=0;

	// release header control
	FreeClassObject(lpHdrCtrl);
}

// CPlaylistCtrl::GetItemString()

BOOL CPlaylistCtrl::GetItemString(int nItem,
								  LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"CPlaylistCtrl::GetItemString()",
							FALSE);
		return(FALSE);
	}
#endif

	LockGlobalMsg()

	// prepare string
	sprintf(g_lpMsg,
		    "%d. ",
			nItem+1);

	// add string
	strcat(g_lpMsg,
		   lpStr);

	// copy new string to destination
	strcpy(lpStr,
		   g_lpMsg);

	UnlockGlobalMsg()

	// ok
	return(TRUE);
}

// CPlaylistCtrl::SetCallbacks()

void CPlaylistCtrl::SetCallbacks(BOOL (*lpfnGetItemStringCallback)(LPSTR,LPVOID),
								 BOOL (*lpfnGetItemSaveCallback)(LPSTR,LPVOID),
								 LPVOID (*lpfnGetItemDataCallback)(LPSTR),
								 BOOL (*lpfnGetItemTooltipCallback)(LPSTR,LPVOID))
{
	// copy pointers
	GetItemStringCallback =lpfnGetItemStringCallback;
	GetItemSaveCallback   =lpfnGetItemSaveCallback;
	GetItemDataCallback   =lpfnGetItemDataCallback;
	GetItemTooltipCallback=lpfnGetItemTooltipCallback;
}

// CPlaylistCtrl::Init()

BOOL CPlaylistCtrl::Init(LPSTR lpColHead)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpColHead)
	{
		DisplayErrorMessage("Invalid string value.",
							"CPlaylistCtrl::Init()",
							FALSE);
		return(FALSE);
	}
#endif

	// header control
	CHeaderCtrl* lpHdr;

	// position rectangle
	CRect rPos;

	// playlist width
	int nListWidth;

	// get playlist size
	GetClientRect(&rPos);

	// set playlist width
	nListWidth=(rPos.right-rPos.left)-GetSystemMetrics(SM_CXVSCROLL);

	// add main column
	if(InsertColumn(0,
					lpColHead,
					LVCFMT_LEFT,
					nListWidth,
					0)==-1)
	{
		DisplayErrorMessage("Unable to add column header to playlist.");
		return(FALSE);
	}

	// get header control
	lpHdr=GetHeaderCtrl();

	// check header control
	if(!lpHdr)
	{
		DisplayErrorMessage("Unable to find playlist control header.");
		return(FALSE);
	}

	// create extended header
	AllocClassObject(lpHdrCtrl,
					 CExtHeaderCtrl);

	// check new object
	if(!lpHdrCtrl)
		return(FALSE);

	// subclass header control
	if(!lpHdrCtrl->SubclassWindow(lpHdr->m_hWnd))
	{
		DisplayErrorMessage("Unable to attach playlist control header.");
		return(FALSE);
	}

	// set no-resize cursor
	lpHdrCtrl->SetNoResizeCursor();

	// init navigation buttons
	DisableNavButtons();

	// init global buttons
	DisableGlobalButtons();

	// set saved flag
	bIsSaved=TRUE;

	// ok
	return(TRUE);
}

// CPlaylistCtrl::SetButtonPtrs()

void CPlaylistCtrl::SetButtonPtrs(CExtButton* lpUp,
								  CExtButton* lpDown,
								  CExtButton* lpTop,
								  CExtButton* lpBottom,
								  CExtButton* lpDelete,
								  CExtButton* lpClear,
								  CExtButton* lpSave,
								  CExtButton* lpLoad)
{
	// copy pointers
	lpUpBtn    =lpUp;
	lpDownBtn  =lpDown;
	lpTopBtn   =lpTop;
	lpBottomBtn=lpBottom;
	lpDeleteBtn=lpDelete;
	lpClearBtn =lpClear;
	lpSaveBtn  =lpSave;
	lpLoadBtn  =lpLoad;
}

// CPlaylistCtrl::SetParentDlg()

void CPlaylistCtrl::SetParentDlg(CExtDialog* lpDlg)
{
	// copy pointer
	lpParentDlg=lpDlg;
}

// CPlaylistCtrl::SetParentPropPage()

void CPlaylistCtrl::SetParentPropPage(CPropertyPage* lpPropPage)
{
	// copy pointer
	lpParentPropPage=lpPropPage;
}

// CPlaylistCtrl::SetParentModified()

void CPlaylistCtrl::SetParentModified(BOOL bState)
{
	// check for dialog
	if(lpParentDlg)
		lpParentDlg->SetModified(bState);

	// check for property page
	if(lpParentPropPage)
		lpParentPropPage->SetModified(bState);

	// set saved flag
	bIsSaved=(bState ? FALSE : TRUE);
}

// CPlaylistCtrl::EnableNavButtons()

void CPlaylistCtrl::EnableNavButtons(int nSelItem)
{
	// get number of items
	int nNumItems=GetItemCount();

	// check for no items
	if(nNumItems==0)
	{
		// disable instead
		DisableNavButtons();

		// stop here
		return;
	}

	// check for only one item
	if(nNumItems!=1)
	{
		// check for uppermost position
		if(nSelItem!=0)
		{
			// enable upward movement
			lpUpBtn->Enable();
			lpTopBtn->Enable();
		}

		// check for lowermost position
		if(nSelItem!=(nNumItems-1))
		{
			// enable downward movement
			lpDownBtn->Enable();
			lpBottomBtn->Enable();
		}
	}

	// enable delete button
	lpDeleteBtn->Enable();
}

// CPlaylistCtrl::DisableNavButtons()

void CPlaylistCtrl::DisableNavButtons(void)
{
	// disable all buttons
	lpUpBtn->Disable();
	lpDownBtn->Disable();
	lpTopBtn->Disable();
	lpBottomBtn->Disable();
	lpDeleteBtn->Disable();
}

// CPlaylistCtrl::EnableGlobalButtons()

void CPlaylistCtrl::EnableGlobalButtons(void)
{
	// enable buttons
	lpClearBtn->Enable();

	// enable auxilliary controls
	if(lpAuxCtrl1) lpAuxCtrl1->EnableWindow();
	if(lpAuxCtrl2) lpAuxCtrl2->EnableWindow();
	if(lpAuxCtrl3) lpAuxCtrl3->EnableWindow();
	if(lpAuxCtrl4) lpAuxCtrl4->EnableWindow();
}

// CPlaylistCtrl::DisableGlobalButtons()

void CPlaylistCtrl::DisableGlobalButtons(void)
{
	// disable buttons
	lpClearBtn->Disable();

	// disable auxilliary controls
	if(lpAuxCtrl1) lpAuxCtrl1->EnableWindow(FALSE);
	if(lpAuxCtrl2) lpAuxCtrl2->EnableWindow(FALSE);
	if(lpAuxCtrl3) lpAuxCtrl3->EnableWindow(FALSE);
	if(lpAuxCtrl4) lpAuxCtrl4->EnableWindow(FALSE);
}

// CPlaylistCtrl::SwapItems()

void CPlaylistCtrl::SwapItems(int nItem1,
							  int nItem2,
							  BOOL bNoUpdate)
{
	// item data
	DWORD dwItemData1;
	DWORD dwItemData2;

	// playlist data
	LPPLAYLISTDATA lpData1;
	LPPLAYLISTDATA lpData2;

	// check for last-item flag
	if(nItem1==-1)
		nItem1=GetItemCount()-1;
	if(nItem2==-1)
		nItem2=GetItemCount()-1;

	// check for same item
	if(nItem1==nItem2)
		return;

	// save item data
	dwItemData1=GetItemData(nItem1);
	dwItemData2=GetItemData(nItem2);

	// swap item data
	SetItemData(nItem1,
				dwItemData2);
	SetItemData(nItem2,
				dwItemData1);

	// check flag
	if(!bNoUpdate)
	{
		// get playlist data #1
		if(!GetPlaylistItemData(nItem1,
								&lpData1))
		{
			DisplayNEErrorMessage("Unable to retrieve item data for move.");
			return;
		}

		// get playlist data #2
		if(!GetPlaylistItemData(nItem2,
								&lpData2))
		{
			DisplayNEErrorMessage("Unable to retrieve item data for move.");
			return;
		}

		LockGlobalLongMsg()

		// copy title of item #1
		strcpy(g_lpLongMsg,
			   lpData1->lpTitle);

		// get new string for item #1
		GetItemString(nItem1,
					  g_lpLongMsg);

		// set new string to item #1
		SetItemText(nItem1,
					0,
					g_lpLongMsg);

		// copy title of item #2
		strcpy(g_lpLongMsg,
			   lpData2->lpTitle);

		// get new string for item #2
		GetItemString(nItem2,
					  g_lpLongMsg);

		// set new string to item #2
		SetItemText(nItem2,
					0,
					g_lpLongMsg);

		UnlockGlobalLongMsg()

		// highlight item #2
		SetItemState(nItem2,
					 LVIS_FOCUSED|
					 LVIS_SELECTED,
					 0xFF);

		// make sure item #2 is visible
		EnsureVisible(nItem2,
					  FALSE);

		// give focus to playlist
		SetFocus();

		// set parent modified
		SetParentModified();
	}
}

// CPlaylistCtrl::OnCustomDraw()

void CPlaylistCtrl::OnCustomDraw(NMHDR* pNMHDR,
								 LRESULT* pResult)
{
	// get pointer to custom draw header
	LPNMLVCUSTOMDRAW lpLVCD=(LPNMLVCUSTOMDRAW)pNMHDR;

	// text colors
	COLORREF clrTxt;
	COLORREF clrBkg;

	// pointer to device context
	CDC* lpDC=NULL;

	// device context state
	int nState;

	// drawing areas
	CRect rcMain;
	CRect rcHead;
	CRect rcSrc;
	CRect rcDest;

	// pointer to header control
	CHeaderCtrl* lpHC=NULL;

	// item nubmer
	int nItem;

	// pointer to playlist data
	LPPLAYLISTDATA lpData=NULL;
	
	// device context
	HDC hDC=(HDC)INVALID_HANDLE_VALUE;

	// gdi object
	CGdiObject* lpGdiObj=NULL;
	
	// assume default processing
	(*pResult)=CDRF_DODEFAULT;

	// check draw stage
	switch(lpLVCD->nmcd.dwDrawStage)
	{
	// general pre-paint stage
	case(CDDS_PREPAINT):

		// check number of items
		if(GetItemCount()<=0)
		{
			// get text colors
			clrTxt=GetSysColor(COLOR_GRAYTEXT);
			clrBkg=GetSysColor(COLOR_WINDOW);

			// get device context
			lpDC=CDC::FromHandle(lpLVCD->nmcd.hdc);

			// check device context
			if(!lpDC)
				return;

			// save device context state
			nState=lpDC->SaveDC();

			// get window area
			GetWindowRect(&rcMain);
			
			// convert to client
			ScreenToClient(&rcMain);

			// get header control		
			lpHC=GetHeaderCtrl();

			// check for control
			if(lpHC)
			{
				// get header rect
				if(lpHC->GetItemRect(0,
									 &rcHead))
				{
					// update drawing area
					rcMain.top+=rcHead.bottom;
				}
			}	

			// add white space
			rcMain.top+=5;

			// set text parameters
			lpDC->SetTextColor(clrTxt);
			lpDC->SetBkColor(clrBkg);

			// clear rect
			lpDC->FillRect(rcMain,
						   &CBrush(clrBkg));

			// select current font
			lpGdiObj=lpDC->SelectObject(GetFont());

			// draw text
			lpDC->DrawText("Playlist is empty ",
						   -1,
						   rcMain,
						   DT_CENTER|
						   DT_WORDBREAK|
						   DT_NOPREFIX);

			// restore object
			lpDC->SelectObject(lpGdiObj);

			// restore device context
			lpDC->RestoreDC(nState);

			// stop here
			(*pResult)=CDRF_SKIPDEFAULT;
		}
		else
		{
			// get notification of each item
			(*pResult)=CDRF_NOTIFYITEMDRAW;
		}

		// ok
		break;

	// item pre-paint stage
	case(CDDS_ITEMPREPAINT):

		// get item number
		nItem=(int)lpLVCD->nmcd.dwItemSpec;

		// get playlist data
		if(GetPlaylistItemData(nItem,
							   &lpData))
		{
			// check for user data
			if(lpData->lpUserData)
			{
				// set normal text
				lpLVCD->clrText=GetSysColor(COLOR_WINDOWTEXT);
			}
			else
			{
				// set gray text
				lpLVCD->clrText=GetSysColor(COLOR_GRAYTEXT);
			}
		}
		else
		{
			// set gray text
			lpLVCD->clrText=GetSysColor(COLOR_GRAYTEXT);
		}

		// ok
		break;
	}
}

// CPlaylistCtrl::PreSubclassWindow()

void CPlaylistCtrl::PreSubclassWindow(void)
{
	// call base function
	CListCtrl::PreSubclassWindow();

	// enable tooltips
	EnableToolTips(TRUE);
}

// CPlaylistCtrl::CellRectFromPoint()

int CPlaylistCtrl::CellRectFromPoint(CPoint point,
									 LPRECT lprCell) const
{
	// item counters
	int nNumItems;
	int nItem;

	// bounding rect
	CRect rRect;

	// client rect
	CRect rClient;

	// string width
	int nStringWidth;

	// rect width
	int nRectWidth;

	// get item count
	nNumItems=GetItemCount();

	// check for items
	if(nNumItems)
	{
		// check each item
		for(nItem=0;nItem<nNumItems;nItem++)
		{
			// get bounding rect
			if(!GetItemRect(nItem,
							&rRect,
							LVIR_BOUNDS))
				return(-1);

			// get string width
			nStringWidth=GetStringWidth(GetItemText(nItem,0));

			// check string width
			if(nStringWidth)
			{
				// set rect witdht
				nRectWidth=nStringWidth+0;

				// compare widths
				if(nRectWidth<rRect.Width())
					rRect.right=rRect.left+nRectWidth;
			}

			// check point
			if(rRect.PtInRect(point))
			{
				// get client rect
				GetClientRect(&rClient);

				// clip rect to client
				if(rRect.right>rClient.right) 
					rRect.right=rClient.right;

				// copy rect
				(*lprCell)=rRect;

				// ok
				return(nItem);
			}
		}
	}

	// not found
	return(-1);
}

// CPlaylistCtrl::OnToolHitTest()

int CPlaylistCtrl::OnToolHitTest(CPoint point,
								 TOOLINFO *pTI) const
{
	// item number
	int nItem;

	// bounding rect
	CRect rRect;

	// check for item intersect
	nItem=CellRectFromPoint(point,
							&rRect);

	// check item number	
	if(nItem==-1) 
		return(-1);

	// just to verify
	LockGlobalTTMsg()
	UnlockGlobalTTMsg()
	LockGlobalLongTTMsg()
	UnlockGlobalLongTTMsg()

	// set tooltip info
	pTI->hwnd=m_hWnd;
	pTI->uId=(UINT)(nItem+1);
	pTI->lpszText=LPSTR_TEXTCALLBACK;
	pTI->rect=rRect;

	// return id
	return(pTI->uId);
}

// CPlaylistCtrl::OnTTNeedText()

BOOL CPlaylistCtrl::OnTTNeedText(UINT nID,
								 NMHDR* pNMHDR,
								 LRESULT* pResult)
{
	// cast pointers to tooltip info
	LPTOOLTIPTEXTA lpTTTa=(LPTOOLTIPTEXTA)pNMHDR;
	LPTOOLTIPTEXTW lpTTTw=(LPTOOLTIPTEXTW)pNMHDR;

	// playlist data
	LPPLAYLISTDATA lpData;

	// get actual id
	nID=pNMHDR->idFrom;

	// check for winnt auto tooltip
	if(nID==0)
		return(FALSE);

	// get playlist data
	if(!GetPlaylistItemData(nID-1,
						    &lpData))
		return(FALSE);

	// check playlist data
	if(!lpData)
		return(FALSE);

	// check item data
	if(lpData->lpUserData)
	{
		// get text
		if(!GetItemTooltipCallback(g_lpTTMsg,
								   lpData->lpUserData))
		{
			UnlockGlobalTTMsg()
			return(FALSE);
		}
	}
	else
	{
		// check flag
		if(!g_bShowPListPopup)
		{
			UnlockGlobalTTMsg()
			return(FALSE);
		}

		// set default text
		strcpy(g_lpTTMsg,
			   NO_ITEM_TEXT);
	}

#ifndef _UNICODE
	// check notification code
	if(pNMHDR->code==TTN_NEEDTEXTA)
	{
		// copy text
		lstrcpyn(g_lpLongTTMsg,g_lpTTMsg,LONG_MSG_SIZE-1);

		// set text
		lpTTTa->lpszText=g_lpLongTTMsg;

		// clear instance
		lpTTTa->hinst=NULL;
	}
	else
	{
		// convert text
		_mbstowcsz((LPWSTR)g_lpLongTTMsg,g_lpTTMsg,_MAX_PATH-1);

		// set text
		lpTTTw->lpszText=(LPWSTR)g_lpLongTTMsg;

		// clear instance
		lpTTTw->hinst=NULL;
	}
#else
	// check notification code
	if(pNMHDR->code==TTN_NEEDTEXTA)
	{
		// convert text
		_wcstombsz(g_lpLongTTMsg,(LPWSTR)g_lpTTMsg,_MAX_PATH-1);

		// set text
		lpTTTa->lpszText=g_lpLongTTMsg;

		// clear instance
		lpTTTa->hinst=NULL;
	}
	else
	{
		// copy text
		lstrcpyn(g_lpLongTTMsg,g_lpTTMsg,LONG_MSG_SIZE-1);

		// set text
		lpTTTw->lpszText=(LPWSTR)g_lpLongTTMsg;

		// clear instance
		lpTTTw->hinst=NULL;
	}
#endif

	// ok
	return(TRUE);
}

// CPlaylistCtrl::PurgeInvalid()

void CPlaylistCtrl::PurgeInvalid(BOOL bSilent)
{
	// counter
	int nCount;

	// num items
	int nNumItems;

	// playlist data
	LPPLAYLISTDATA lpPD;

	// get number of items
	nNumItems=GetItemCount();

	// check item count
	if(!nNumItems)
		return;

	// play sound
	if(!bSilent)
		PlaySound(IDR_DELALLSND);

	// loop through items (backwards)
	for(nCount=nNumItems-1;nCount>=0;nCount--)
	{
		// get item data
		if(GetPlaylistItemData(nCount,
							   &lpPD))
		{
			// check user data
			if(!lpPD->lpUserData)
			{
				// delete item
				DeleteItem(nCount);
			}
		}
		else
		{
			// delete item
			DeleteItem(nCount);
		}
	}

	// renumber items
	RenumberItems();

	// set parent modified
	SetParentModified();
}

// CPlaylistCtrl::HasInvalid()

BOOL CPlaylistCtrl::HasInvalid(void)
{
	// counter
	int nCount;

	// num items
	int nNumItems;

	// playlist data
	LPPLAYLISTDATA lpPD;

	// get number of items
	nNumItems=GetItemCount();

	// check item count
	if(!nNumItems)
		return(FALSE);

	// loop through items
	for(nCount=0;nCount<nNumItems;nCount++)
	{
		// get item data
		if(GetPlaylistItemData(nCount,
							   &lpPD))
		{
			// check user data
			if(!lpPD->lpUserData)
			{
				// found invalid
				return(TRUE);
			}
		}
		else
		{
			// found invalid
			return(TRUE);
		}
	}

	// none found
	return(FALSE);
}

// CPlaylistCtrl::RenumberItems()

void CPlaylistCtrl::RenumberItems(void)
{
	// counter
	int nCount;

	// num items
	int nNumItems;

	// playlist data
	LPPLAYLISTDATA lpPD;

	// get item count
	nNumItems=GetItemCount();

	// check item count
	if(!nNumItems)
		return;

	// renumber list
	for(nCount=0;nCount<nNumItems;nCount++)
	{
		// get item data
		if(GetPlaylistItemData(nCount,
							   &lpPD))
		{
			LockGlobalLongMsg()
			
			// copy string
			strcpy(g_lpLongMsg,
				   lpPD->lpTitle);
			
			// get item string
			GetItemString(nCount,
						  g_lpLongMsg);

			// set new text
			SetItemText(nCount,
						0,
						g_lpLongMsg);

			UnlockGlobalLongMsg()
		}
	}
}

// CPlaylistCtrl::MoveSelTop()

void CPlaylistCtrl::MoveSelTop(void)
{
	// get current selection
	int nSelItem=GetSelection();

	// check for valid selection
	if(nSelItem==-1||
	   nSelItem==0)
		return;

	// set flag
	bMoving=TRUE;

	// swap to top
	while(nSelItem!=0)
	{
		// swap items (no update)
		SwapItems(nSelItem,
				  nSelItem-1,
				  TRUE);

		// decrement item
		nSelItem--;
	}

	// renumber items
	RenumberItems();

	// highlight item
	SetItemState(nSelItem,
				 LVIS_FOCUSED|
				 LVIS_SELECTED,
				 0xFF);

	// make sure item is visible
	EnsureVisible(nSelItem,
				  FALSE);

	// give focus to playlist
	SetFocus();

	// set parent modified
	SetParentModified();
	
	// reset flag
	bMoving=FALSE;
}

// CPlaylistCtrl::MoveSelBottom()

void CPlaylistCtrl::MoveSelBottom(void)
{
	// get current selection
	int nSelItem=GetSelection();

	// get max item
	int nMaxItem=GetItemCount()-1;

	// check for valid selection
	if(nSelItem==-1||
	   nSelItem==nMaxItem)
		return;

	// set flag
	bMoving=TRUE;

	// swap to bottom
	while(nSelItem!=nMaxItem)
	{
		// swap items (no update)
		SwapItems(nSelItem,
				  nSelItem+1,
				  TRUE);

		// increment item
		nSelItem++;
	}

	// renumber items
	RenumberItems();

	// highlight item
	SetItemState(nSelItem,
				 LVIS_FOCUSED|
				 LVIS_SELECTED,
				 0xFF);

	// make sure item is visible
	EnsureVisible(nSelItem,
				  FALSE);

	// give focus to playlist
	SetFocus();

	// set parent modified
	SetParentModified();

	// reset flag
	bMoving=FALSE;
}

// CPlaylistCtrl::OnKeyDown()

void CPlaylistCtrl::OnKeyDown(UINT nChar,
							  UINT nRepCnt,
							  UINT nFlags)
{
	// check for up arrow
	if(nChar==VK_UP)
	{
		// check shift key
		if(GetKeyState(VK_SHIFT)&0x8000)
		{
			// check ctrl key
			if(GetKeyState(VK_CONTROL)&0x8000)
			{
				// move to top
				MoveSelTop();

				// stop here
				return;
			}
			else
			{
				// move up
				MoveSelUp();

				// stop here
				return;
			}
		}
	}

	// check for down arrow
	if(nChar==VK_DOWN)
	{
		// check shift key
		if(GetKeyState(VK_SHIFT)&0x8000)
		{
			// check ctrl key
			if(GetKeyState(VK_CONTROL)&0x8000)
			{
				// move to bottom
				MoveSelBottom();

				// stop here
				return;
			}
			else
			{
				// move down
				MoveSelDown();

				// stop here
				return;
			}
		}
	}

	// check for delete key
	if(nChar==VK_DELETE)
		DeleteSel();

	// call base method
	CListCtrl::OnKeyDown(nChar,
						 nRepCnt,
						 nFlags);
}

// CPlaylistCtrl::SetAuxCtrlPtrs()

void CPlaylistCtrl::SetAuxCtrlPtrs(CWnd* lpAux1,
								   CWnd* lpAux2,
								   CWnd* lpAux3,
								   CWnd* lpAux4)
{
	// copy pointers
	lpAuxCtrl1=lpAux1;
	lpAuxCtrl2=lpAux2;
	lpAuxCtrl3=lpAux3;
	lpAuxCtrl4=lpAux4;
}

// CreatePlaylistBtnImages()

BOOL CreatePlaylistBtnImages(void)
{
	// device contexts
	CDC* lpDesktopDC=NULL;
	CDC* lpImageDC=NULL;

	// bitmap colors
	COLORREF clrBnFace;
	COLORREF clrShadow;
	COLORREF clrHilite;
	COLORREF clrArrow;
	COLORREF clrCurrent;

	// allocate bitmap
	AllocClassObject(g_lpPListUpBmp,
					 CBitmap);

	// check new object
	if(!g_lpPListUpBmp)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpPListDownBmp,
					 CBitmap);

	// check new object
	if(!g_lpPListDownBmp)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpPListTopBmp,
					 CBitmap);

	// check new object
	if(!g_lpPListTopBmp)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpPListBottomBmp,
					 CBitmap);

	// check new object
	if(!g_lpPListBottomBmp)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpPListUpBmpGr,
					 CBitmap);

	// check new object
	if(!g_lpPListUpBmpGr)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpPListDownBmpGr,
					 CBitmap);

	// check new object
	if(!g_lpPListDownBmpGr)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpPListTopBmpGr,
					 CBitmap);

	// check new object
	if(!g_lpPListTopBmpGr)
		return(FALSE);
	
	// allocate bitmap
	AllocClassObject(g_lpPListBottomBmpGr,
					 CBitmap);

	// check new object
	if(!g_lpPListBottomBmpGr)
		return(FALSE);
	
	// get desktop dc
	lpDesktopDC=CDC::FromHandle(::GetDC(GetDesktopWindow()));

	// check desktop dc
	if(!lpDesktopDC)
	{
		DisplayErrorMessage("Unable to find desktop device context.");
		return(FALSE);
	}

	// create up bitmap
	if(!g_lpPListUpBmp->CreateCompatibleBitmap(lpDesktopDC,
											   24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// create down bitmap
	if(!g_lpPListDownBmp->CreateCompatibleBitmap(lpDesktopDC,
												 24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// create top bitmap
	if(!g_lpPListTopBmp->CreateCompatibleBitmap(lpDesktopDC,
												24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// create bottom bitmap
	if(!g_lpPListBottomBmp->CreateCompatibleBitmap(lpDesktopDC,
												   24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// create up bitmap (grayed)
	if(!g_lpPListUpBmpGr->CreateCompatibleBitmap(lpDesktopDC,
											     24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// create down bitmap (grayed)
	if(!g_lpPListDownBmpGr->CreateCompatibleBitmap(lpDesktopDC,
												   24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// create top bitmap (grayed)
	if(!g_lpPListTopBmpGr->CreateCompatibleBitmap(lpDesktopDC,
												  24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// create bottom bitmap (grayed)
	if(!g_lpPListBottomBmpGr->CreateCompatibleBitmap(lpDesktopDC,
												     24,16))
	{
		DisplayErrorMessage("Unable to create playlist control image.");
		return(FALSE);
	}

	// get bitmap colors
	clrBnFace=GetSysColor(COLOR_3DFACE);
	clrShadow=LightenColor(GetSysColor(COLOR_3DSHADOW),2);
	clrHilite=GetSysColor(COLOR_3DHILIGHT);
	clrArrow =GetSysColor(COLOR_BTNTEXT);

	// allocate device context
	AllocClassObject(lpImageDC,
					 CDC);

	// check new object
	if(!lpImageDC)
		return(FALSE);

	// create compatible dc
	if(!lpImageDC->CreateCompatibleDC(lpDesktopDC))
	{
		DisplayErrorMessage("Unable to create desktop-compatible device context.");
		return(FALSE);
	}
	else
		AddWinResource

	// select up bitmap
	lpImageDC->SelectObject(g_lpPListUpBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 12,18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 11,16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 10,14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 9, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 7, 8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 6, 6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,5, 4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,4, 2, 1,clrCurrent);
	}

	// select up bitmap (grayed)
	lpImageDC->SelectObject(g_lpPListUpBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 12,18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 11,16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 10,14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 9, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 7, 8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 6, 6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,5, 4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,4, 2, 1,clrCurrent);
	}

	// select down bitmap
	lpImageDC->SelectObject(g_lpPListDownBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 4, 18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 5, 16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 6, 14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 7, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 9,8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 10,6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,11,4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,12,2, 1,clrCurrent);
	}

	// select down bitmap (grayed)
	lpImageDC->SelectObject(g_lpPListDownBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 4, 18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 5, 16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 6, 14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 7, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 9,8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 10,6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,11,4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,12,2, 1,clrCurrent);
	}

	// select top bitmap
	lpImageDC->SelectObject(g_lpPListTopBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 12,18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 11,16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 10, 14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 9, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 7, 8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 6, 6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,5, 4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,4, 2, 1,clrCurrent);

		// draw stop
		lpImageDC->FillSolidRect(3,2,18,2,clrCurrent);
	}

	// select top bitmap (grayed)
	lpImageDC->SelectObject(g_lpPListTopBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 12,18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 11,16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 10, 14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 9, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 7, 8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 6, 6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,5, 4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,4, 2, 1,clrCurrent);

		// draw stop
		lpImageDC->FillSolidRect(3,2,18,2,clrCurrent);
	}

	// select bottom bitmap
	lpImageDC->SelectObject(g_lpPListBottomBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 4, 18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 5, 16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 6, 14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 7, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 9,8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 10,6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,11,4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,12,2, 1,clrCurrent);

		// draw stop
		lpImageDC->FillSolidRect(3,13,18,2,clrCurrent);
	}

	// select bottom bitmap (grayed)
	lpImageDC->SelectObject(g_lpPListBottomBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,24,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow
		lpImageDC->FillSolidRect(3, 4, 18,1,clrCurrent);
		lpImageDC->FillSolidRect(4, 5, 16,1,clrCurrent);
		lpImageDC->FillSolidRect(5, 6, 14,1,clrCurrent);
		lpImageDC->FillSolidRect(6, 7, 12,1,clrCurrent);
		lpImageDC->FillSolidRect(7, 8, 10,1,clrCurrent);
		lpImageDC->FillSolidRect(8, 9,8, 1,clrCurrent);
		lpImageDC->FillSolidRect(9, 10,6, 1,clrCurrent);
		lpImageDC->FillSolidRect(10,11,4, 1,clrCurrent);
		lpImageDC->FillSolidRect(11,12,2, 1,clrCurrent);

		// draw stop
		lpImageDC->FillSolidRect(3,13,18,2,clrCurrent);
	}

	// select null object
	lpImageDC->SelectObject((CGdiObject*)NULL);

	// delete device context
	if(lpImageDC->DeleteDC())
		RemoveWinResource

	// free device context
	FreeClassObject(lpImageDC);

	// ok
	return(TRUE);
}

// GetSaverPListFilterList();

LPSTR GetSaverPListFilterList(void)
{
	// byte counters
	int nNumBytes;
	int nCurByte;

	LockGlobalLongTTMsg()
	
	// start list
	strcpy(g_lpLongTTMsg,
		   "");

	// add filters
	strcat(g_lpLongTTMsg,"Screensaver Playlist Files (*.spl)#*.spl#");
	strcat(g_lpLongTTMsg,"All Files (*.*)#*.*#");

	// add terminator
	strcat(g_lpLongTTMsg,"\0");

	// get number of bytes
	nNumBytes=strlen(g_lpLongTTMsg);

	// replace '#' with terminator
	for(nCurByte=0;nCurByte<nNumBytes;nCurByte++)
		if(g_lpLongTTMsg[nCurByte]=='#')
			g_lpLongTTMsg[nCurByte]=0;

	UnlockGlobalLongTTMsg()

	// return string
	return(g_lpLongTTMsg);
}

// GetAudioPListFilterList()

LPSTR GetAudioPListFilterList(void)
{
	// byte counters
	int nNumBytes;
	int nCurByte;
	
	LockGlobalLongTTMsg()

	// start list
	strcpy(g_lpLongTTMsg,
		   "");

	// add filters
	strcat(g_lpLongTTMsg,"Audio Playlist Files (*.apl)#*.apl#");
	strcat(g_lpLongTTMsg,"All Files (*.*)#*.*#");

	// add terminator
	strcat(g_lpLongTTMsg,"#");

	// get number of bytes
	nNumBytes=strlen(g_lpLongTTMsg);

	// replace '#' with terminator
	for(nCurByte=0;nCurByte<nNumBytes;nCurByte++)
		if(g_lpLongTTMsg[nCurByte]=='#')
			g_lpLongTTMsg[nCurByte]=0;

	UnlockGlobalLongTTMsg()

	// return string
	return(g_lpLongTTMsg);
}

// CheckSaverPListFileCallback()

BOOL CheckSaverPListFileCallback(void)
{
	// check audio file
	if(!IsValidSaverPList(g_lpMsg))
	{
		// alert user
		DisplayInfoMessage("The file you have selected is not a valid screensaver playlist.\n\nPlease select another file.");

		// try again
		return(TRUE);
	}

	// file is ok
	return(FALSE);
}

// CheckAudioPListFileCallback()

BOOL CheckAudioPListFileCallback(void)
{
	// check audio file
	if(!IsValidAudioPList(g_lpMsg))
	{
		// alert user
		DisplayInfoMessage("The file you have selected is not a valid ProSaver audio playlist.\n\nPlease select another file.");

		// try again
		return(TRUE);
	}

	// file is ok
	return(FALSE);
}

// CPlaylistCtrl::SaveListFile()

BOOL CPlaylistCtrl::SaveListFile(LPSTR lpFilterList,
								 LPCSTR lpCaption,
								 LPCSTR lpStartDirReg,
								 LPCSTR lpFourCC,
								 LPCSTR lpDefExt,
								 LPSTR lpFileRet)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpFilterList||
	   !lpCaption||
	   !lpFourCC||
	   !lpDefExt)
	{
		DisplayErrorMessage("Invalid string value.",
							"CPlaylistCtrl::SaveListFile()",
							FALSE);
		return(FALSE);
	}
#endif

	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// item count
	int nItemCount;

	// counter
	int nCount;

	// index value
	BYTE cIdx;

	// playlist data
	LPPLAYLISTDATA lpData=NULL;

	// string length
	WORD wStrLen;

	// reset return value
	BOOL bRet=FALSE;

	LockGlobalLongMsg()

	// check for registry path
	if(lpStartDirReg)
	{
		// attempt to load string
		if(!LoadOptionString(lpStartDirReg,
							 g_lpLongMsg))
		{
			// reset text
			strcpy(g_lpLongMsg,
				   NULL_STRING);
		}
	}
	else
	{
		// reset text
		strcpy(g_lpLongMsg,
			   NULL_STRING);
	}

	LockGlobalMsg()

	// clear filename
	strcpy(g_lpMsg,
		   NULL_STRING);

	// just to verify
	LockGlobalTTMsg()
	UnlockGlobalTTMsg()

	// copy starting path
	strcpy(g_lpTTMsg,
		   g_lpLongMsg);

	UnlockGlobalLongMsg()

	// no callback needed
	g_lpFileSaveDlg->SetCheckFileCallback(NULL);

	// configure dialog box
	g_lpFileSaveDlg->m_ofn.lStructSize    =sizeof(OPENFILENAME);
	g_lpFileSaveDlg->m_ofn.hwndOwner      =m_hWnd;
	g_lpFileSaveDlg->m_ofn.lpstrFilter    =lpFilterList;
	g_lpFileSaveDlg->m_ofn.nFilterIndex   =1;
	g_lpFileSaveDlg->m_ofn.lpstrFile      =g_lpMsg;
	g_lpFileSaveDlg->m_ofn.nMaxFile       =_MAX_PATH-1;
	g_lpFileSaveDlg->m_ofn.lpstrTitle     =lpCaption;
	g_lpFileSaveDlg->m_ofn.Flags          |=OFN_OVERWRITEPROMPT;
	g_lpFileSaveDlg->m_ofn.lpstrInitialDir=g_lpTTMsg;
	g_lpFileSaveDlg->m_ofn.lpstrDefExt    =lpDefExt;

	// clear remaining items
	g_lpFileSaveDlg->m_ofn.hInstance        =NULL;
	g_lpFileSaveDlg->m_ofn.lpstrCustomFilter=NULL;
	g_lpFileSaveDlg->m_ofn.nMaxCustFilter   =0;
	g_lpFileSaveDlg->m_ofn.lpstrFileTitle   =NULL;
	g_lpFileSaveDlg->m_ofn.nMaxFileTitle    =0;
	g_lpFileSaveDlg->m_ofn.nFileOffset      =0;
	g_lpFileSaveDlg->m_ofn.nFileExtension   =0;
	g_lpFileSaveDlg->m_ofn.lCustData        =NULL;
	g_lpFileSaveDlg->m_ofn.lpTemplateName   =NULL;

	// run dialog box
	if(g_lpFileSaveDlg->DoModal()==IDOK)
	{
		// check registry path
		if(lpStartDirReg)
		{
			// save offset byte
			char cOfs=g_lpMsg[g_lpFileSaveDlg->m_ofn.nFileOffset];

			// set offset byte to 0
			g_lpMsg[g_lpFileSaveDlg->m_ofn.nFileOffset]=0;

			// save string
			SaveOptionString(lpStartDirReg,
							 g_lpMsg);

			// restore offset byte
			g_lpMsg[g_lpFileSaveDlg->m_ofn.nFileOffset]=cOfs;
		}

		// open file for output
		hFile=CreateFile(g_lpMsg,
						 GENERIC_WRITE,
						 NULL,
						 NULL,
						 CREATE_ALWAYS,
						 NULL,
						 NULL);

		// check handle
		if(hFile==INVALID_HANDLE_VALUE)
		{
			// alert user
			DisplayErrorMessage("Unable to open file for output:",
								g_lpMsg);
		}
		else
		{
			AddWinResource

			LockGlobalLongMsg()

			// copy byte code
			strcpy(g_lpLongMsg,
				   lpFourCC);

			// output byte code
			if(!WriteFileEnc(hFile,
						     g_lpLongMsg,
						     4))
				goto CPlaylistCtrl_SaveListFile1;

			// get item count
			nItemCount=GetItemCount();

			// output item count
			if(!WriteFileEnc(hFile,
						     &nItemCount,
						     sizeof(int)))
				goto CPlaylistCtrl_SaveListFile1;

			// check item count
			if(nItemCount)
			{
				// reset index
				cIdx=0;

				// loop through items
				for(nCount=0;nCount<nItemCount;nCount++)
				{
					// get item data
					if(!GetPlaylistItemData(nCount,
											&lpData))
						goto CPlaylistCtrl_SaveListFile1;

					// output index
					if(!WriteFileEnc(hFile,
								     &cIdx,
								     sizeof(BYTE)))
						goto CPlaylistCtrl_SaveListFile1;

					// increment index
					cIdx++;

					// get length of default string
					wStrLen=(WORD)strlen(lpData->lpTitle);

					// output length
					if(!WriteFileEnc(hFile,
								     &wStrLen,
								     sizeof(WORD)))
						goto CPlaylistCtrl_SaveListFile1;

					// output string
					if(!WriteFileEnc(hFile,
								     lpData->lpTitle,
								     wStrLen))
						goto CPlaylistCtrl_SaveListFile1;

					// output index
					if(!WriteFileEnc(hFile,
								     &cIdx,
								     sizeof(BYTE)))
						goto CPlaylistCtrl_SaveListFile1;

					// increment index
					cIdx++;

					// get length of save string
					wStrLen=(WORD)strlen(lpData->lpSave);

					// output length
					if(!WriteFileEnc(hFile,
								     &wStrLen,
								     sizeof(WORD)))
						goto CPlaylistCtrl_SaveListFile1;

					// output string
					if(!WriteFileEnc(hFile,
								     lpData->lpSave,
								     wStrLen))
						goto CPlaylistCtrl_SaveListFile1;
				}
			}

			// output final index
			if(!WriteFileEnc(hFile,
							 &cIdx,
							 sizeof(BYTE)))
				goto CPlaylistCtrl_SaveListFile1;

			// copy filename
			if(lpFileRet)
				strcpy(lpFileRet,
					   g_lpMsg);

			// set return value
			bRet=TRUE;

// error exit point
CPlaylistCtrl_SaveListFile1:;
							 
			UnlockGlobalLongMsg()

			// close file
			if(CloseHandle(hFile))
				RemoveWinResource
		}
	}

	UnlockGlobalMsg()

	// copy saved flag
	bIsSaved=bRet;

	// ok
	return(bRet);
}

// IsValidSaverPList()

BOOL IsValidSaverPList(LPSTR lpFile)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"IsValidSaverPList()",
							FALSE);
		return(FALSE);
	}
#endif

	// check list
	return(IsValidPList(lpFile,
						"PSSL"));
}

// IsValidAudioPList()

BOOL IsValidAudioPList(LPSTR lpFile)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"IsValidAudioPList()",
							FALSE);
		return(FALSE);
	}
#endif

	// check list
	return(IsValidPList(lpFile,
						"PSAL"));
}

// IsValidPList()

BOOL IsValidPList(LPSTR lpFile,
				  LPCSTR lpFourCC)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpFile||
	   !lpFourCC)
	{
		DisplayErrorMessage("Invalid string value.",
							"IsValidPList()",
							FALSE);
		return(FALSE);
	}
#endif

	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// item count
	int nItemCount;

	// counter
	int nCount;

	// index values
	BYTE cIdx;
	BYTE cIdx2;

	// string length
	WORD wStrLen;

	// reset return value
	BOOL bRet=FALSE;

	// open file for input
	hFile=CreateFile(lpFile,
					 GENERIC_READ,
					 NULL,
					 NULL,
					 OPEN_EXISTING,
					 NULL,
					 NULL);

	// check handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		// alert user
		DisplayErrorMessage("Unable to open the selected file:",
							lpFile);
	}
	else
	{
		AddWinResource

		LockGlobalLongMsg()
		
		// read byte code
		if(!ReadFileEnc(hFile,
					    g_lpLongMsg,
					    4,
					    TRUE))
			goto IsValidPList1;

		// set null terminator
		g_lpLongMsg[4]=0;

		// check for proper code
		if(strcmp(g_lpLongMsg,
				  lpFourCC))
			goto IsValidPList1;

		// get item count
		if(!ReadFileEnc(hFile,
					    &nItemCount,
					    sizeof(int),
					    TRUE))
			goto IsValidPList1;

		// check item count
		if(nItemCount)
		{
			// reset index
			cIdx=0;

			// loop through items
			for(nCount=0;nCount<nItemCount;nCount++)
			{
				// read index value
				if(!ReadFileEnc(hFile,
								&cIdx2,
								sizeof(BYTE),
								TRUE))
					goto IsValidPList1;

				// compare indices
				if(cIdx2!=cIdx)
					goto IsValidPList1;

				// increment index
				cIdx++;

				// read string length
				if(!ReadFileEnc(hFile,
								&wStrLen,
								sizeof(WORD),
								TRUE))
					goto IsValidPList1;

				// skip string
				if(!MoveFilePointer(hFile,
									wStrLen,
									TRUE))
					goto IsValidPList1;

				// read index value
				if(!ReadFileEnc(hFile,
								&cIdx2,
								sizeof(BYTE),
								TRUE))
					goto IsValidPList1;

				// compare indices
				if(cIdx2!=cIdx)
					goto IsValidPList1;

				// increment index
				cIdx++;

				// read string length
				if(!ReadFileEnc(hFile,
								&wStrLen,
								sizeof(WORD),
								TRUE))
					goto IsValidPList1;

				// skip string
				if(!MoveFilePointer(hFile,
									wStrLen,
									TRUE))
					goto IsValidPList1;
			}

			// read final index value
			if(!ReadFileEnc(hFile,
							&cIdx2,
							sizeof(BYTE),
							TRUE))
				goto IsValidPList1;

			// compare indices
			if(cIdx2!=cIdx)
				goto IsValidPList1;
		}

		// set return value
		bRet=TRUE;

// error exit point
IsValidPList1:;

		UnlockGlobalLongMsg()

		// close file
		if(CloseHandle(hFile))
			RemoveWinResource
	}

	// ok
	return(bRet);
}

// CPlaylistCtrl::LoadListFile()

BOOL CPlaylistCtrl::LoadListFile(LPSTR lpFilterList,
								 LPCSTR lpCaption,
								 LPCSTR lpStartDirReg,
								 BOOL (*lpfnCheckFileCallback)(void),
								 LPSTR lpFileRet)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpFilterList||
	   !lpCaption)
	{
		DisplayErrorMessage("Invalid string value.",
							"CPlaylistCtrl::LoadListFile()",
							FALSE);
		return(FALSE);
	}
#endif

	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// item count
	int nItemCount;

	// counter
	int nCount;

	// string length
	WORD wStrLen;

	// item data
	LPVOID lpItemData=NULL;

	// reset invalid items flag
	BOOL bInvItems=FALSE;

	// reset return value
	BOOL bRet=FALSE;

	LockGlobalLongMsg()

	// check for registry path
	if(lpStartDirReg)
	{
		// attempt to load string
		if(!LoadOptionString(lpStartDirReg,
							 g_lpLongMsg))
		{
			// reset text
			strcpy(g_lpLongMsg,
				   NULL_STRING);
		}
	}
	else
	{
		// reset text
		strcpy(g_lpLongMsg,
			   NULL_STRING);
	}

	LockGlobalMsg()

	// clear filename
	strcpy(g_lpMsg,
		   NULL_STRING);

	// just to verify
	LockGlobalTTMsg()
	UnlockGlobalTTMsg()

	// copy starting path
	strcpy(g_lpTTMsg,
		   g_lpLongMsg);

	UnlockGlobalLongMsg()

	// set callback
	g_lpFileOpenDlg->SetCheckFileCallback(lpfnCheckFileCallback);

	// configure dialog box
	g_lpFileOpenDlg->m_ofn.lStructSize    =sizeof(OPENFILENAME);
	g_lpFileOpenDlg->m_ofn.hwndOwner      =m_hWnd;
	g_lpFileOpenDlg->m_ofn.lpstrFilter    =lpFilterList;
	g_lpFileOpenDlg->m_ofn.nFilterIndex   =1;
	g_lpFileOpenDlg->m_ofn.lpstrFile      =g_lpMsg;
	g_lpFileOpenDlg->m_ofn.nMaxFile       =_MAX_PATH-1;
	g_lpFileOpenDlg->m_ofn.lpstrTitle     =lpCaption;
	g_lpFileOpenDlg->m_ofn.Flags          |=OFN_OVERWRITEPROMPT;
	g_lpFileOpenDlg->m_ofn.lpstrInitialDir=g_lpTTMsg;
	g_lpFileOpenDlg->m_ofn.lpstrDefExt    =NULL;

	// clear remaining items
	g_lpFileOpenDlg->m_ofn.hInstance        =NULL;
	g_lpFileOpenDlg->m_ofn.lpstrCustomFilter=NULL;
	g_lpFileOpenDlg->m_ofn.nMaxCustFilter   =0;
	g_lpFileOpenDlg->m_ofn.lpstrFileTitle   =NULL;
	g_lpFileOpenDlg->m_ofn.nMaxFileTitle    =0;
	g_lpFileOpenDlg->m_ofn.nFileOffset      =0;
	g_lpFileOpenDlg->m_ofn.nFileExtension   =0;
	g_lpFileOpenDlg->m_ofn.lCustData        =NULL;
	g_lpFileOpenDlg->m_ofn.lpTemplateName   =NULL;

	// run dialog box
	if(g_lpFileOpenDlg->DoModal()==IDOK)
	{
		// check registry path
		if(lpStartDirReg)
		{
			// save offset byte
			char cOfs=g_lpMsg[g_lpFileOpenDlg->m_ofn.nFileOffset];

			// set offset byte to 0
			g_lpMsg[g_lpFileOpenDlg->m_ofn.nFileOffset]=0;

			// save string
			SaveOptionString(lpStartDirReg,
							 g_lpMsg);

			// restore offset byte
			g_lpMsg[g_lpFileOpenDlg->m_ofn.nFileOffset]=cOfs;
		}

		// copy path
		if(lpFileRet)
			strcpy(lpFileRet,
				   g_lpMsg);

		// open file for input
		hFile=CreateFile(g_lpMsg,
						 GENERIC_READ,
						 NULL,
						 NULL,
						 OPEN_EXISTING,
						 NULL,
						 NULL);

		// check handle
		if(hFile==INVALID_HANDLE_VALUE)
		{
			// alert user
			DisplayErrorMessage("Unable to open the selected file:",
								g_lpMsg);
		}
		else
		{
			AddWinResource

			UnlockGlobalMsg()

			// clear list
			ClearList(TRUE);
			
			// init navigation buttons
			DisableNavButtons();

			// init global buttons
			if(GetItemCount())
				EnableGlobalButtons();
			else
				DisableGlobalButtons();

			// set parent modified
			SetParentModified();

			// move pointer to item count
			if(!MoveFilePointer(hFile,
							    4))
				goto CPlaylistCtrl_LoadListFile1;

			// get item count
			if(!ReadFileEnc(hFile,
						    &nItemCount,
						    sizeof(int)))
				goto CPlaylistCtrl_LoadListFile1;

			// check item count
			if(nItemCount)
			{
				// loop through items
				for(nCount=0;nCount<nItemCount;nCount++)
				{
					LockGlobalMsg()
					LockGlobalLongMsg()
					
					// skip index value
					if(!MoveFilePointer(hFile,
										1))
						goto CPlaylistCtrl_LoadListFile1;

					// read default string length
					if(!ReadFileEnc(hFile,
									&wStrLen,
									sizeof(WORD),
									TRUE))
						goto CPlaylistCtrl_LoadListFile1;

					// read string
					if(!ReadFileEnc(hFile,
									g_lpMsg,
									wStrLen,
									TRUE))
						goto CPlaylistCtrl_LoadListFile1;
					
					// set null terminator
					g_lpMsg[wStrLen]=0;

					// skip index value
					if(!MoveFilePointer(hFile,
										1))
						goto CPlaylistCtrl_LoadListFile1;

					// read save string length
					if(!ReadFileEnc(hFile,
									&wStrLen,
									sizeof(WORD),
									TRUE))
						goto CPlaylistCtrl_LoadListFile1;

					// read string
					if(!ReadFileEnc(hFile,
									g_lpLongMsg,
									wStrLen,
									TRUE))
						goto CPlaylistCtrl_LoadListFile1;
					
					// set null terminator
					g_lpLongMsg[wStrLen]=0;

					// just to verify
					LockGlobalTTMsg()
					LockGlobalLongTTMsg()
					UnlockGlobalTTMsg()
					UnlockGlobalLongTTMsg()

					// copy strings
					strcpy(g_lpTTMsg,
						   g_lpMsg);
					strcpy(g_lpLongTTMsg,
						   g_lpLongMsg);

					UnlockGlobalMsg()
					UnlockGlobalLongMsg()

					LockGlobalErrorMsg()

					// copy string
					strcpy(g_lpErrorMsg,
						   g_lpLongTTMsg);

					// get item data from save string
					lpItemData=GetItemDataCallback(g_lpErrorMsg);

					// restore string
					strcpy(g_lpLongTTMsg,
						   g_lpErrorMsg);

					UnlockGlobalErrorMsg()

					// check item data
					if(lpItemData!=NULL&&
					   lpItemData!=IGNORE_ITEM_DATA)
					{
						// add item with validated info
						AddToList(lpItemData,
								  NULL,
								  NULL,
								  TRUE);
					}
					else
					{
						// add item with stored info
						AddToList(NULL,
								  g_lpTTMsg,
								  g_lpLongTTMsg,
								  TRUE);

						// check for ignore flag
						if(lpItemData!=IGNORE_ITEM_DATA)
						{
							// set invalid-items flag
							bInvItems=TRUE;
						}
					}

					UnlockGlobalTTMsg()
					UnlockGlobalLongTTMsg()
				}
			}

			// check for invalid items
			if(bInvItems)
			{
				// inform user
				DisplayOptMessageBox(INV_ITEMS_MSG,
									 (LPSTR)ApplicationName(),
									 MB_OK|MB_ICONEXCLAMATION,
									 "MsgBox_PLInvItems");
			}

			// clear navigation buttons
			DisableNavButtons();

			// set global buttons
			if(GetItemCount())
				EnableGlobalButtons();
			else
				DisableGlobalButtons();

			// set return value
			bRet=TRUE;

// error exit point
CPlaylistCtrl_LoadListFile1:;

			UnlockGlobalLongMsg()

			// close file
			if(CloseHandle(hFile))
				RemoveWinResource
		}
	}

	UnlockGlobalMsg()

	// copy saved flag
	if(bRet)
		bIsSaved=TRUE;

	// ok
	return(bRet);
}

// CMainPropSheet::OnAboutBtn()

void CMainPropSheet::OnAboutBtn(void)
{
	// display about box
	ShowAboutDlg();
}

// CMainPropSheet::OnPrefsBtn()

void CMainPropSheet::OnPrefsBtn(void)
{
	// display preferences
	ShowPreferencesDlg();
}

// CMainPropSheet::OnPurchBtn()

void CMainPropSheet::OnPurchBtn(void)
{
#ifdef SHAREWARE_MODE
	// display purchase info
	ShowPurchaseDlg();
#endif
}

// CFileListCtrl::CFileListCtrl()

CFileListCtrl::CFileListCtrl(UINT nID)
{
	// copy id
	nCtrlId=nID;

	// reset values
	lpHistoryCbx  =NULL;
	lpSysImageList=NULL;
	bIsFilling    =FALSE;

	// call base method
	CListCtrl::CListCtrl();
}

// CPlaylistCtrl::SetCtrlIds()

void CPlaylistCtrl::SetCtrlIds(UINT nID,
							   UINT nHDR)
{
	// copy ids
	nCtrlId=nID;
	nHdrId =nHDR;
}

// CMainPropSheet::OnCommand()

BOOL CMainPropSheet::OnCommand(WPARAM wParam,
							   LPARAM lParam)
{
	// window rect
	CRect rWnd;

	// process message
	switch(HIWORD(wParam))
	{
	// menu selection
	case(0):

		// check message id
		switch(LOWORD(wParam))
		{
		case(IDM_SLIST_ADD):        AddCurSaverToPlaylist();    return(0);
		case(IDM_SLIST_EDIT):       EditCurSaverInfo();         return(0);
		case(IDM_SLIST_DETAILS):    ToggleSaverListDetails();   return(0);
		case(IDM_SLIST_RATINGS):    ToggleSaverListRatings();   return(0);
		case(IDM_SLIST_TITLESORT):  SortSaverListColumn(0);     return(0);
		case(IDM_SLIST_THEMESORT):  SortSaverListColumn(1);     return(0);
		case(IDM_SLIST_RATINGSORT): SortSaverListColumn(2);     return(0);
		case(IDM_SLIST_SETRATING0): SetCurSaverRating(0);       return(0);
		case(IDM_SLIST_SETRATING1): SetCurSaverRating(1);       return(0);
		case(IDM_SLIST_SETRATING2): SetCurSaverRating(2);       return(0);
		case(IDM_SLIST_SETRATING3): SetCurSaverRating(3);       return(0);
		case(IDM_SLIST_SETRATING4): SetCurSaverRating(4);       return(0);
		case(IDM_SLIST_SETRATING5): SetCurSaverRating(5);       return(0);
		case(IDM_SLIST_POPUPINFO):  ToggleSaverListPopupInfo(); return(0);

		case(IDM_SIBOX_SETTINGS): RunCurSaverSettings(); return(0);
		case(IDM_SIBOX_PREVIEW):  RunCurSaverPreview();  return(0);
		case(IDM_SIBOX_SHOWPREV): ToggleSaverPreview();  return(0);

		case(IDM_SDESC_UNDO):   g_lpSaverDescEdit->Undo();      return(0);
		case(IDM_SDESC_CUT):    g_lpSaverDescEdit->Cut();       return(0);
		case(IDM_SDESC_COPY):   g_lpSaverDescEdit->Copy();      return(0);
		case(IDM_SDESC_PASTE):  g_lpSaverDescEdit->Paste();     return(0);
		case(IDM_SDESC_DEL):    g_lpSaverDescEdit->Clear();     return(0);
		case(IDM_SDESC_SELALL): g_lpSaverDescEdit->SelectAll(); return(0);

		case(IDM_THEME_NEW):   g_lpThemesList->AddNewTheme();     return(0);
		case(IDM_THEME_DEL):   g_lpThemesList->DeleteSelection(); return(0);
		case(IDM_THEME_REN):   g_lpThemesList->RenameSelection(); return(0);
		case(IDM_THEME_CLEAR): g_lpThemesList->ClearSelection();  return(0);

		case(IDM_NWTHM_UNDO):   g_lpNewThemeEdit->Undo();      return(0);
		case(IDM_NWTHM_CUT):    g_lpNewThemeEdit->Cut();       return(0);
		case(IDM_NWTHM_COPY):   g_lpNewThemeEdit->Copy();      return(0);
		case(IDM_NWTHM_PASTE):  g_lpNewThemeEdit->Paste();     return(0);
		case(IDM_NWTHM_DEL):    g_lpNewThemeEdit->Clear();     return(0);
		case(IDM_NWTHM_SELALL): g_lpNewThemeEdit->SelectAll(); return(0);

		case(IDM_RNTHM_UNDO):   g_lpRenThemeEdit->Undo();      return(0);
		case(IDM_RNTHM_CUT):    g_lpRenThemeEdit->Cut();       return(0);
		case(IDM_RNTHM_COPY):   g_lpRenThemeEdit->Copy();      return(0);
		case(IDM_RNTHM_PASTE):  g_lpRenThemeEdit->Paste();     return(0);
		case(IDM_RNTHM_DEL):    g_lpRenThemeEdit->Clear();     return(0);
		case(IDM_RNTHM_SELALL): g_lpRenThemeEdit->SelectAll(); return(0);

		case(IDM_MUSIC_LOADFILE):  g_lpChangeMusicDlg->OnLoadAudioFileBtnClk();     return(0);
		case(IDM_MUSIC_LOADPLIST): g_lpChangeMusicDlg->OnLoadAudioPlaylistBtnClk(); return(0);
		case(IDM_MUSIC_CLEARSEL):  g_lpChangeMusicDlg->OnClearAudioFileBtnClk();    return(0);
		case(IDM_MUSIC_OPENMGR):   g_lpChangeMusicDlg->OnOpenMusicManagerBtnClk();  return(0);

		case(IDM_PLIST_SORTNAMEAZ):   SortSaverPlaylist(1);               return(0);
		case(IDM_PLIST_SORTNAMEZA):   SortSaverPlaylist(2);               return(0);
		case(IDM_PLIST_SORTTHEMEAZ):  SortSaverPlaylist(3);               return(0);
		case(IDM_PLIST_SORTTHEMEZA):  SortSaverPlaylist(4);               return(0);
		case(IDM_PLIST_SORTRATING51): SortSaverPlaylist(5);               return(0);
		case(IDM_PLIST_SORTRATING15): SortSaverPlaylist(6);               return(0);
		case(IDM_PLIST_CLEARLIST):    g_lpSaverPage->OnClearBtnClk();     return(0);
		case(IDM_PLIST_SAVELIST):     g_lpSaverPage->OnSaveBtnClk();      return(0);
		case(IDM_PLIST_LOADLIST):     g_lpSaverPage->OnLoadBtnClk();      return(0);
		case(IDM_PLIST_PURGEINV):     g_lpSaverPlaylist->QueryPurgeInv(); return(0);
		case(IDM_PLIST_MOVEUP):       g_lpSaverPlaylist->MoveSelUp();     return(0);
		case(IDM_PLIST_MOVEDOWN):     g_lpSaverPlaylist->MoveSelDown();   return(0);
		case(IDM_PLIST_MOVETOP):      g_lpSaverPlaylist->MoveSelTop();    return(0);
		case(IDM_PLIST_MOVEBOTTOM):   g_lpSaverPlaylist->MoveSelBottom(); return(0);
		case(IDM_PLIST_DELETESEL):    g_lpSaverPlaylist->DeleteSel();     return(0);
		case(IDM_PLIST_TOGGLEPOPUP):  TogglePListPopupInfo();             return(0);

		case(IDM_SPATH_ADDPATH): g_lpSearchPathList->AddPath();         return(0);
		case(IDM_SPATH_CHGPATH): g_lpSearchPathList->ChangeSelection(); return(0);
		case(IDM_SPATH_DELPATH): g_lpSearchPathList->DeleteSelection(); return(0);

		case(IDM_FLIST_OPENFOLDER): g_lpAudioFileList->ShowSelFolder(); return(0);
		case(IDM_FLIST_ADDFILE):    g_lpAudioFileList->AddToPlaylist(); return(0);
		case(IDM_FLIST_PLAYFILE):   g_lpCurMusicMgrDlg->OnStopBtnClk();
									g_lpCurMusicMgrDlg->OnPlayBtnClk(); return(0);

		case(IDM_APLST_SORTNAMEAZ):  SortAudioPlaylist(1);                     return(0);
		case(IDM_APLST_SORTNAMEZA):  SortAudioPlaylist(2);                     return(0);
		case(IDM_APLST_SORTTYPEAZ):  SortAudioPlaylist(3);                     return(0);
		case(IDM_APLST_SORTTYPEZA):  SortAudioPlaylist(4);                     return(0);
		case(IDM_APLST_CLEARLIST):   g_lpCurMusicMgrDlg->OnPListClearBtnClk(); return(0);
		case(IDM_APLST_SAVELIST):    g_lpCurMusicMgrDlg->OnPListSaveBtnClk();  return(0);
		case(IDM_APLST_LOADLIST):    g_lpCurMusicMgrDlg->OnPListLoadBtnClk();  return(0);
		case(IDM_APLST_PURGEINV):    g_lpAudioPList->QueryPurgeInv();          return(0);
		case(IDM_APLST_MOVEUP):      g_lpAudioPList->MoveSelUp();              return(0);
		case(IDM_APLST_MOVEDOWN):    g_lpAudioPList->MoveSelDown();            return(0);
		case(IDM_APLST_MOVETOP):     g_lpAudioPList->MoveSelTop();             return(0);
		case(IDM_APLST_MOVEBOTTOM):  g_lpAudioPList->MoveSelBottom();          return(0);
		case(IDM_APLST_DELETESEL):   g_lpAudioPList->DeleteSel();              return(0);
		case(IDM_APLST_TOGGLEPOPUP): ToggleAudioPListPopupInfo();              return(0);

		case(IDM_SPREV_SETTINGS): g_lpSaverPage->OnSettingsBtnClk(); return(0);
		case(IDM_SPREV_FULLPREV): g_lpSaverPage->OnPreviewBtnClk();  return(0);

		case(IDM_MSHEET_HELP):           ShowHelp(IDC_MAINSHEET,          NULL);                     return(0);
		case(IDM_DLGOK_HELP):            ShowHelp(IDC_DLGOKBTN,           NULL);                     return(0);
		case(IDM_DLGCANCEL_HELP):        ShowHelp(IDC_DLGCANCELBTN,       NULL);                     return(0);
		case(IDM_DLGAPPLY_HELP):         ShowHelp(IDC_DLGAPPLYBTN,        NULL);                     return(0);
		case(IDM_DEFOK_HELP):            ShowHelp(IDC_DEFOKBTN,           g_lpDefOKBtn);             return(0);
		case(IDM_DEFCANCEL_HELP):        ShowHelp(IDC_DEFCANCELBTN,       g_lpDefCancelBtn);         return(0);
		case(IDM_DEFAPPLY_HELP):         ShowHelp(IDC_DEFAPPLYBTN,        g_lpDefApplyBtn);          return(0);
		case(IDM_GHELPBTN_HELP):         ShowHelp(IDC_GHELPBTN,           g_lpGHelpBtn);             return(0);
		case(IDM_ABOUTBTN_HELP):         ShowHelp(IDC_ABOUTBTN,           g_lpAboutBtn);             return(0);
		case(IDM_PREFSBTN_HELP):         ShowHelp(IDC_PREFSBTN,           g_lpPrefsBtn);             return(0);
		case(IDM_PURCHBTN_HELP):         ShowHelp(IDC_PURCHBTN,           g_lpPurchBtn);             return(0);
		case(IDM_SLIST_HELP):            ShowHelp(IDC_SAVERLIST,          g_lpSaverList);            return(0);
		case(IDM_CLEARSEL_HELP):         ShowHelp(IDC_CLEARSELBTN,        g_lpClearSelBtn);          return(0);
		case(IDM_ADDSAVER_HELP):         ShowHelp(IDC_ADDSAVERBTN,        g_lpAddSaverBtn);          return(0);
		case(IDM_SAVERINFO_HELP):        ShowHelp(IDC_SAVERINFO,          g_lpSaverInfoBox);         return(0);
		case(IDM_SETTINGS_HELP):         ShowHelp(IDC_SETTINGSBTN,        g_lpSaverSettingsBtn);     return(0);
		case(IDM_PREVIEW_HELP):          ShowHelp(IDC_PREVIEWBTN,         g_lpPreviewSaverBtn);      return(0);
		case(IDM_EDITINFO_HELP):         ShowHelp(IDC_EDITINFOBTN,        g_lpEditSaverInfoBtn);     return(0);
		case(IDM_PREVIEWWND_HELP):       ShowHelp(IDC_PREVIEWWND,         g_lpSaverPrevBox);         return(0);
		case(IDM_SHOWPREV_HELP):         ShowHelp(IDC_SHOWPREVIEWCHK,     g_lpMiniPreviewChk);       return(0);
		case(IDM_THEMESEL_HELP):         ShowHelp(IDC_THEMESELBOX,        g_lpThemeSelBox);          return(0);
		case(IDM_EDITTHEMES_HELP):       ShowHelp(IDC_EDITTHEMESBTN,      g_lpEditThemesBtn);        return(0);
		case(IDM_RATINGSEL_HELP):        ShowHelp(IDC_RATINGSELBOX,       g_lpRatingSelBox);         return(0);
		case(IDM_EDITHELP_HELP):         ShowHelp(IDC_EDITHELPBTN,        g_lpEditHelpBtn);          return(0);
		case(IDM_MUSICSEL_HELP):         ShowHelp(IDC_MUSICSELBOX,        g_lpMusicSelBox);          return(0);
		case(IDM_MUSICBROWSE_HELP):      ShowHelp(IDC_MUSICBROWSEBTN,     g_lpMusicBrowseBtn);       return(0);
		case(IDM_MUSICCYCLE_HELP):       ShowHelp(IDC_MUSICCYCLERAD,      g_lpMusicCycleRad);        return(0);
		case(IDM_MUSICSHUFFLE_HELP):     ShowHelp(IDC_MUSICSHUFFLERAD,    g_lpMusicShuffleRad);      return(0);
		case(IDM_SAVERDESC_HELP):        ShowHelp(IDC_SAVERDESC,          g_lpSaverDescLabel);       return(0);
		case(IDM_NOMINIPREV_HELP):       ShowHelp(IDC_DISABLEPREVCHK,     g_lpNoMiniPrevChk);        return(0);
		case(IDM_THEMESLIST_HELP):       ShowHelp(IDC_THEMESLIST,         g_lpThemesList);           return(0);
		case(IDM_NEWTHEME_HELP):         ShowHelp(IDC_NEWTHEMEBTN,        g_lpNewThemeBtn);          return(0);
		case(IDM_DELTHEME_HELP):         ShowHelp(IDC_DELTHEMEBTN,        g_lpDelThemeBtn);          return(0);
		case(IDM_RENTHEME_HELP):         ShowHelp(IDC_RENAMETHEMEBTN,     g_lpRenThemeBtn);          return(0);
		case(IDM_DEFTHEMES_HELP):        ShowHelp(IDC_DEFTHEMESBTN,       g_lpDefThemesBtn);         return(0);
		case(IDM_THEMESHELP_HELP):       ShowHelp(IDC_THEMESHELPBTN,      g_lpThemesHelpBtn);        return(0);
		case(IDM_NEWTHEMEEDIT_HELP):     ShowHelp(IDC_NEWTHEMEEDT,        g_lpNewThemeEdit);         return(0);
		case(IDM_RENTHEMEEDIT_HELP):     ShowHelp(IDC_RENAMETHEMEEDT,     g_lpRenThemeEdit);         return(0);
		case(IDM_LOADMUSFILE_HELP):      ShowHelp(IDC_LOADAUDFILEBTN,     g_lpLoadAudioFileBtn);     return(0);
		case(IDM_LOADMUSPLIST_HELP):     ShowHelp(IDC_LOADPLISTBTN,       g_lpLoadAudioPlaylistBtn); return(0);
		case(IDM_CLEARMUSFILE_HELP):     ShowHelp(IDC_CLEARMUSBTN,        g_lpClearAudioFileBtn);    return(0);
		case(IDM_EDITAUDIO_HELP):        ShowHelp(IDC_EDITAUDIOBTN,       g_lpOpenMusicManagerBtn);  return(0);
		case(IDM_CHANGEMUS_HELP):        ShowHelp(IDC_CHGMUSHELPBTN,      g_lpChangeAudioHelpBtn);   return(0);
		case(IDM_CURRPLIST_HELP):        ShowHelp(IDC_CURRPLIST,          g_lpSaverPlaylist);        return(0);
		case(IDM_PLISTSORT_HELP):        ShowHelp(IDC_PLISTSORTCBX,       g_lpSaverSortBox);         return(0);
		case(IDM_PLISTUP_HELP):          ShowHelp(IDC_PLISTUPBTN,         g_lpPListUpBtn);           return(0);
		case(IDM_PLISTDOWN_HELP):        ShowHelp(IDC_PLISTDOWNBTN,       g_lpPListDownBtn);         return(0);
		case(IDM_PLISTTOP_HELP):         ShowHelp(IDC_PLISTTOPBTN,        g_lpPListTopBtn);          return(0);
		case(IDM_PLISTBOTTOM_HELP):      ShowHelp(IDC_PLISTBOTTOMBTN,     g_lpPListBottomBtn);       return(0);
		case(IDM_PLISTDELETE_HELP):      ShowHelp(IDC_PLISTDELBTN,        g_lpPListDeleteBtn);       return(0);
		case(IDM_PLISTCLEAR_HELP):       ShowHelp(IDC_PLISTCLRBTN,        g_lpPListClearBtn);        return(0);
		case(IDM_PLISTSAVE_HELP):        ShowHelp(IDC_PLISTSAVEBTN,       g_lpPListSaveBtn);         return(0);
		case(IDM_PLISTLOAD_HELP):        ShowHelp(IDC_PLISTLOADBTN,       g_lpPListLoadBtn);         return(0);
		case(IDM_ONESAVER_HELP):         ShowHelp(IDC_ONESVRRAD,          g_lpOneSaverRad);          return(0);
		case(IDM_MULTISAVER_HELP):       ShowHelp(IDC_MULTISVRRAD,        g_lpMultiSaverRad);        return(0);
		case(IDM_SHOWSAVEREDT_HELP):     ShowHelp(IDC_SHOWSVREDT,         g_lpShowSaverEdit);        return(0);
		case(IDM_SHOWSAVERSPIN_HELP):    ShowHelp(IDC_SHOWSVRSPIN,        g_lpShowSaverEdit);        return(0);
		case(IDM_SAVERCYCLE_HELP):       ShowHelp(IDC_SVRCYCLERAD,        g_lpSaverCycleRad);        return(0);
		case(IDM_SAVERSHUFFLE_HELP):     ShowHelp(IDC_SVRSHUFFLERAD,      g_lpSaverShuffleRad);      return(0);
		case(IDM_ENABLEHKEYS_HELP):      ShowHelp(IDC_ENABLEHKEYSCBX,     g_lpEnableHotkeysChk);     return(0);
		case(IDM_STARTSAVERHKY_HELP):    ShowHelp(IDC_STARTSVRHKY,        g_lpStartSaverHky);        return(0);
		case(IDM_SKIPSAVERHKY_HELP):     ShowHelp(IDC_SKIPSVRHKY,         g_lpSkipSaverHky);         return(0);
		case(IDM_OPENPSHKY_HELP):        ShowHelp(IDC_OPENPSHKY,          g_lpOpenPSHky);            return(0);
		case(IDM_CLEARSCREEN_HELP):      ShowHelp(IDC_CLRSCREENCBX,       g_lpClearScreenChk);       return(0);
		case(IDM_NOMUSIC_HELP):          ShowHelp(IDC_NOMUSICCBX,         g_lpNoMusicChk);           return(0);
		case(IDM_OPENTHEMES_HELP):       ShowHelp(IDC_OPENTHEMESBTN,      g_lpOpenThemesBtn);        return(0);
		case(IDM_OPENMUSICMGR_HELP):     ShowHelp(IDC_OPENAUDIOBTN,       g_lpOpenMusicBtn);         return(0);
		case(IDM_ADVWARNING_HELP):       ShowHelp(IDC_ADVWARNTXT,         g_lpAdvWarningTxt);        return(0);
		case(IDM_SHOWADVANCED_HELP):     ShowHelp(IDC_SHOWADVBTN,         g_lpShowAdvancedBtn);      return(0);
		case(IDM_SEARCHPATHLIST_HELP):   ShowHelp(IDC_SEARCHLIST,         g_lpSearchPathList);       return(0);
		case(IDM_ADDPATH_HELP):          ShowHelp(IDC_ADDPATHBTN,         g_lpAddPathBtn);           return(0);
		case(IDM_CHANGEPATH_HELP):       ShowHelp(IDC_CHANGEPATHBTN,      g_lpChangePathBtn);        return(0);
		case(IDM_DELETEPATH_HELP):       ShowHelp(IDC_DELETEPATHBTN,      g_lpDeletePathBtn);        return(0);
		case(IDM_SYSTEMTRAY_HELP):       ShowHelp(IDC_SYSTRAYCHK,         g_lpSystemTrayChk);        return(0);
		case(IDM_KEEPCURRENT_HELP):      ShowHelp(IDC_KEEPCURCHK,         g_lpKeepCurrentChk);       return(0);
		case(IDM_HIDEADVANCED_HELP):     ShowHelp(IDC_HIDEADVCHK,         g_lpHideAdvancedChk);      return(0);
		case(IDM_ERRORLOGCHK_HELP):      ShowHelp(IDC_ERRORLOGCHK,        g_lpErrorLogChk);          return(0);
		case(IDM_MAXLINESEDT_HELP):      ShowHelp(IDC_MAXLINESEDT,        g_lpMaxLinesEdit);         return(0);
		case(IDM_MAXLINESSPIN_HELP):     ShowHelp(IDC_MAXLINESSPIN,       g_lpMaxLinesEdit);         return(0);
		case(IDM_ERRORLOGBTN_HELP):      ShowHelp(IDC_ERRORLOGBTN,        g_lpErrorLogBtn);          return(0);
		case(IDM_RESETMSGBTN_HELP):      ShowHelp(IDC_RESETMSGBTN,        g_lpResetMessagesBtn);     return(0);
		case(IDM_HIDEADVBTN_HELP):       ShowHelp(IDC_HIDEADVBTN,         g_lpHideAdvancedBtn);      return(0);
		case(IDM_AUDIOHISTORY_HELP):     ShowHelp(IDC_HISTORYCBX,         g_lpAudioHistoryCbx);      return(0);
		case(IDM_FILEBACKBTN_HELP):      ShowHelp(IDC_FILEBACKBTN,        g_lpFileBackBtn);          return(0);
		case(IDM_FILEUPBTN_HELP):        ShowHelp(IDC_FILEUPBTN,          g_lpFileUpBtn);            return(0);
		case(IDM_AUDIOFILELIST_HELP):    ShowHelp(IDC_FILELIST,           g_lpAudioFileList);        return(0);
		case(IDM_FILETYPE_HELP):         ShowHelp(IDC_FILETYPECBX,        g_lpFileTypeCbx);          return(0);
		case(IDM_CLEARAUDIOSEL_HELP):    ShowHelp(IDC_CLEARAUDIOSELBTN,   g_lpClearAudioSelBtn);     return(0);
		case(IDM_ADDAUDIOFILE_HELP):     ShowHelp(IDC_ADDAUDIOFILEBTN,    g_lpAddAudioFileBtn);      return(0);
		case(IDM_AUDIOPLIST_HELP):       ShowHelp(IDC_AUDIOPLIST,         g_lpAudioPList);           return(0);
		case(IDM_AUDIOPLISTSORT_HELP):   ShowHelp(IDC_AUDIOPLISTSORTCBX,  g_lpAudioPListSortCbx);    return(0);
		case(IDM_AUDIOPLISTUP_HELP):     ShowHelp(IDC_AUDIOPLISTUPBTN,    g_lpAudioPListUpBtn);      return(0);
		case(IDM_AUDIOPLISTTOP_HELP):    ShowHelp(IDC_AUDIOPLISTTOPBTN,   g_lpAudioPListTopBtn);     return(0);
		case(IDM_AUDIOPLISTDOWN_HELP):   ShowHelp(IDC_AUDIOPLISTDOWNBTN,  g_lpAudioPListDownBtn);    return(0);
		case(IDM_AUDIOPLISTBOTTOM_HELP): ShowHelp(IDC_AUDIOPLISTBOTTOMBTN,g_lpAudioPListBottomBtn);  return(0);
		case(IDM_AUDIOPLISTDEL_HELP):    ShowHelp(IDC_AUDIOPLISTDELBTN,   g_lpAudioPListDelBtn);     return(0);
		case(IDM_AUDIOPLISTCLR_HELP):    ShowHelp(IDC_AUDIOPLISTCLRBTN,   g_lpAudioPListClearBtn);   return(0);
		case(IDM_AUDIOPLISTSAVE_HELP):   ShowHelp(IDC_AUDIOPLISTSAVEBTN,  g_lpAudioPListSaveBtn);    return(0);
		case(IDM_AUDIOPLISTLOAD_HELP):   ShowHelp(IDC_AUDIOPLISTLOADBTN,  g_lpAudioPListLoadBtn);    return(0);
		case(IDM_AUDIOINFO_HELP):        ShowHelp(IDC_AUDIOINFO,          g_lpAudioInfoBox);         return(0);
		case(IDM_PLAYBTN_HELP):          ShowHelp(IDC_PLAYBTN,            g_lpPlayBtn);              return(0);
		case(IDM_PAUSEBTN_HELP):         ShowHelp(IDC_PAUSEBTN,           g_lpPauseBtn);             return(0);
		case(IDM_STOPBTN_HELP):          ShowHelp(IDC_STOPBTN,            g_lpStopBtn);              return(0);
		case(IDM_FULLREWBTN_HELP):       ShowHelp(IDC_FULLREWBTN,         g_lpFullRewBtn);           return(0);
		case(IDM_REWBTN_HELP):           ShowHelp(IDC_REWBTN,             g_lpRewBtn);               return(0);
		case(IDM_FWDBTN_HELP):           ShowHelp(IDC_FWDBTN,             g_lpFwdBtn);               return(0);
		case(IDM_AUDIOPOS_HELP):         ShowHelp(IDC_AUDIOPOSSLD,        g_lpAudioPosSld);          return(0);
		case(IDM_ENABLEPBC_HELP):        ShowHelp(IDC_ENABLEPBCCHK,       g_lpEnablePBCChk);         return(0);
		case(IDM_NEXTHKY_HELP):          ShowHelp(IDC_NEXTHKY,            g_lpNextHky);              return(0);
		case(IDM_VOLUPHKY_HELP):         ShowHelp(IDC_VOLUPHKY,           g_lpVolUpHky);             return(0);
		case(IDM_VOLDNHKY_HELP):         ShowHelp(IDC_VOLDNHKY,           g_lpVolDownHky);           return(0);
		case(IDM_MUTEHKY_HELP):          ShowHelp(IDC_MUTEHKY,            g_lpMuteHky);              return(0);
		case(IDM_WINSYNTH_HELP):         ShowHelp(IDC_WINSYNTHRAD,        g_lpWinSynthRad);          return(0);
		case(IDM_DXSYNTH_HELP):          ShowHelp(IDC_DXSYNTHRAD,         g_lpDXSynthRad);           return(0);
		case(IDM_REVERB_HELP):           ShowHelp(IDC_REVERBCHK,          g_lpReverbChk);            return(0);
		case(IDM_CHORUS_HELP):           ShowHelp(IDC_CHORUSCHK,          g_lpChorusChk);            return(0);
		case(IDM_MUSICMGRHELP_HELP):     ShowHelp(IDC_MUSMANHELPBTN,      g_lpMusicMgrHelpBtn);      return(0);
		case(IDM_INSTALLDX_HELP):        ShowHelp(IDC_INSTALLDXBTN,       g_lpInstallDXBtn);         return(0);
		case(IDM_PLAYSFX_HELP):          ShowHelp(IDC_PLAYSFXCHK,         g_lpPlaySFXChk);           return(0);
		case(IDM_TOOLTIPS_HELP):         ShowHelp(IDC_SHOWTOOLTIPSCHK,    g_lpTooltipsChk);          return(0);
		case(IDM_SPLASHSCRN_HELP):       ShowHelp(IDC_SPLASHSCRNCHK,      g_lpSplashScreenChk);      return(0);
		case(IDM_SAVERLISTDET_HELP):     ShowHelp(IDC_SAVERLISTDETCHK,    g_lpSaverListDetChk);      return(0);
		case(IDM_RATINGIMGS_HELP):       ShowHelp(IDC_RATINGIMGSCHK,      g_lpRatingImagesChk);      return(0);
		case(IDM_SLISTPOPUP_HELP):       ShowHelp(IDC_SLISTPOPUPCHK,      g_lpSaverListPopupChk);    return(0);
		case(IDM_PLISTPOPUP_HELP):       ShowHelp(IDC_PLISTPOPUPCHK,      g_lpPlaylistPopupChk);     return(0);
		case(IDM_PREFERENCES_HELP):      ShowHelp(IDC_PREFSHELPBTN,       g_lpPrefsHelpBtn);         return(0);
		case(IDM_WBSLINK_HELP):          ShowHelp(IDC_WBSOFTBMP,          g_lpWBSLinkBox);           return(0);
		case(IDM_ASPLINK_HELP):          ShowHelp(IDC_ASPLOGOBMP,         g_lpASPLinkBox);           return(0);
		case(IDM_VIEWLICBTN_HELP):       ShowHelp(IDC_VIEWLICBTN,         g_lpLicenseBtn);           return(0);
		case(IDM_VIEWREADMEBTN_HELP):    ShowHelp(IDC_VIEWREADMEBTN,      g_lpReadMeBtn);            return(0);
		case(IDM_PSBUYLINK_HELP):        ShowHelp(IDC_PSBUYBMP,           g_lpPSBuyBox);             return(0);
		case(IDM_ORDERBTN_HELP):         ShowHelp(IDC_ORDERBTN,           g_lpOrderBtn);             return(0);
		case(IDM_MAILFORMBTN_HELP):      ShowHelp(IDC_MAILFORMBTN,        g_lpMailFormBtn);          return(0);
		}

		// not found
		break;

	// main sheet init
	case(IDM_MSHEET_INIT):
		
		// call function
		MainSheetIsInit();
		
		// ok
		return(0);

	// main sheet color change
	case(IDM_MSHEET_CLRCHG):
		
		// update advanced options
		//ShowAdvancedOptions(g_bHideAdvanced ? FALSE : TRUE);

		if(g_lpMaxLinesEdit)
			if(g_lpMaxLinesEdit->lpSpinCtrl)
				if(IsWindow(g_lpMaxLinesEdit->lpSpinCtrl->m_hWnd))
					g_lpMaxLinesEdit->lpSpinCtrl->ShowWindow(SW_HIDE);
		
		// ok
		return(0);

	// new theme dialog init
	case(IDM_NWTHM_INIT):
		
		// set focus to edit box
		if(g_lpNewThemeEdit)
			if(IsWindow(g_lpNewThemeEdit->m_hWnd))
				g_lpNewThemeEdit->SetFocus();
		
		// ok
		return(0);

	// rename theme dialog init
	case(IDM_RNTHM_INIT):
		
		// check for edit box
		if(g_lpRenThemeEdit)
		{
			// check for window
			if(IsWindow(g_lpRenThemeEdit->m_hWnd))
			{
				// selected item
				int nItem;

				// get selected item
				if(g_lpThemesList->GetSelItems(1,
											   &nItem)==1)
				{
					LockGlobalMsg()
					
					// get text
					if(g_lpThemesList->GetText(nItem,
											   g_lpMsg)!=LB_ERR)
					{
						// place text in edit box
						g_lpRenThemeEdit->SetWindowText(g_lpMsg);

						// select new text
						g_lpRenThemeEdit->SetSel(0,-1);
					}

					UnlockGlobalMsg()
				}
				
				// set focus to edit box
				g_lpRenThemeEdit->SetFocus();
			}
		}
		
		// ok
		return(0);

	// saver info dialog init
	case(IDM_SINFO_INIT):

		// dialog box
		if(g_lpSaverInfoDlg)
		{
			// validate music file
			if(g_lpSaverInfoDlg->lpMusicPath)
				if(strlen(g_lpSaverInfoDlg->lpMusicPath))
					if(!DoesFileExist(g_lpSaverInfoDlg->lpMusicPath))
					{
						// query user
						if(DisplayMessageBox(g_lpSaverInfoDlg->m_hWnd,
											 "The audio file selected for this screensaver cannot be found.\n\nWould you like to choose another file?",
											 (LPSTR)ApplicationName(),
											 MB_YESNO|MB_ICONWARNING)==IDYES)
						{
							// call dialog box
							BrowseMusicFiles();
						}
					}
					else
					{
						// test mp3 output
						if(TestMP3Output(TRUE))
						{
							// check audio file
							if(!IsValidMusicFile(g_lpSaverInfoDlg->lpMusicPath))
							{
								// query user
								if(DisplayMessageBox(g_lpSaverInfoDlg->m_hWnd,
													 "The audio file selected for this screensaver is not valid.\n\nWould you like to choose another file?",
													 (LPSTR)ApplicationName(),
													 MB_YESNO|
													 MB_ICONWARNING)==IDYES)
								{
									// call dialog box
									BrowseMusicFiles();
								}
							}
						}
					}
		}

		// ok
		return(0);

	// music manager dialog init
	case(IDM_MUSMAN_INIT):

		// finish initialization
		if(!g_lpCurMusicMgrDlg->PostInitDialog())
			ForceImmediateExit();

		// ok
		return(0);

	// browse music
	case(IDM_BROWSEMUSIC):
		
		// call function
		BrowseMusicFiles();
		
		// ok
		return(0);

		// tutorial commands
		case(IDM_DISPLAYTUT1): ShowHelpTopic((DWORD)"Tutorial1.htm"); return(0);
		case(IDM_DISPLAYTUT2): ShowHelpTopic((DWORD)"Tutorial2.htm"); return(0);
		case(IDM_DISPLAYTUT3): ShowHelpTopic((DWORD)"Tutorial3.htm"); return(0);
		case(IDM_DISPLAYTUT4): ShowHelpTopic((DWORD)"Tutorial4.htm"); return(0);
		case(IDM_DISPLAYTUT5): ShowHelpTopic((DWORD)"Tutorial5.htm"); return(0);
		case(IDM_DISPLAYTUT6): ShowHelpTopic((DWORD)"Tutorial6.htm"); return(0);
		case(IDM_DISPLAYTUT7): ShowHelpTopic((DWORD)"Tutorial7.htm"); return(0);
	}
	
	// call base method
	return(CPropertySheet::OnCommand(wParam,lParam));
}

// ShowPopupMenu()

void ShowPopupMenu(UINT nIDCtrl,
				   DWORD dwData,
				   DWORD dwData2,
				   DWORD dwData3,
				   DWORD dwData4)
{
	// pointer to saver info
	CSaverInfo* lpSaverInfo;

	// edit box selection positions
	int nSelStart;
	int nSelEnd;

	// cursor position
	POINT pCur;

	// get cursor position
	if(!GetCursorPos(&pCur))
	{
		// set default values
		pCur.x=0;
		pCur.y=0;
	}

	// init popup menu
	if(!InitPopupMenu())
		return;

	// check control id
	switch(nIDCtrl)
	{
	// one-liners
	case(IDC_MAINSHEET):           AddPopupMenuHelpItem(IDM_MSHEET_HELP);           break;
	case(IDC_DLGOKBTN):            AddPopupMenuHelpItem(IDM_DLGOK_HELP);            break;
	case(IDC_DLGCANCELBTN):        AddPopupMenuHelpItem(IDM_DLGCANCEL_HELP);        break;
	case(IDC_DLGAPPLYBTN):         AddPopupMenuHelpItem(IDM_DLGAPPLY_HELP);         break;
	case(IDC_DEFOKBTN):            AddPopupMenuHelpItem(IDM_DEFOK_HELP);            break;
	case(IDC_DEFCANCELBTN):        AddPopupMenuHelpItem(IDM_DEFCANCEL_HELP);        break;
	case(IDC_DEFAPPLYBTN):         AddPopupMenuHelpItem(IDM_DEFAPPLY_HELP);         break;
	case(IDC_GHELPBTN):            AddPopupMenuHelpItem(IDM_GHELPBTN_HELP);         break;
	case(IDC_ABOUTBTN):            AddPopupMenuHelpItem(IDM_ABOUTBTN_HELP);         break;
	case(IDC_PREFSBTN):            AddPopupMenuHelpItem(IDM_PREFSBTN_HELP);         break;
	case(IDC_PURCHBTN):            AddPopupMenuHelpItem(IDM_PURCHBTN_HELP);         break;
	case(IDC_CLEARSELBTN):         AddPopupMenuHelpItem(IDM_CLEARSEL_HELP);         break;
	case(IDC_ADDSAVERBTN):         AddPopupMenuHelpItem(IDM_ADDSAVER_HELP);         break;
	case(IDC_SETTINGSBTN):         AddPopupMenuHelpItem(IDM_SETTINGS_HELP);         break;
	case(IDC_PREVIEWBTN):          AddPopupMenuHelpItem(IDM_PREVIEW_HELP);          break;
	case(IDC_EDITINFOBTN):         AddPopupMenuHelpItem(IDM_EDITINFO_HELP);         break;
	case(IDC_SHOWPREVIEWCHK):      AddPopupMenuHelpItem(IDM_SHOWPREV_HELP);         break;
	case(IDC_THEMESELBOX):         AddPopupMenuHelpItem(IDM_THEMESEL_HELP);         break;
	case(IDC_EDITTHEMESBTN):       AddPopupMenuHelpItem(IDM_EDITTHEMES_HELP);       break;
	case(IDC_RATINGSELBOX):        AddPopupMenuHelpItem(IDM_RATINGSEL_HELP);        break;
	case(IDC_EDITHELPBTN):         AddPopupMenuHelpItem(IDM_EDITHELP_HELP);         break;
	case(IDC_MUSICBROWSEBTN):      AddPopupMenuHelpItem(IDM_MUSICBROWSE_HELP);      break;
	case(IDC_MUSICCYCLERAD):       AddPopupMenuHelpItem(IDM_MUSICCYCLE_HELP);       break;
	case(IDC_MUSICSHUFFLERAD):     AddPopupMenuHelpItem(IDM_MUSICSHUFFLE_HELP);     break;
	case(IDC_DISABLEPREVCHK):      AddPopupMenuHelpItem(IDM_NOMINIPREV_HELP);       break;
	case(IDC_NEWTHEMEBTN):         AddPopupMenuHelpItem(IDM_NEWTHEME_HELP);         break;
	case(IDC_DELTHEMEBTN):         AddPopupMenuHelpItem(IDM_DELTHEME_HELP);         break;
	case(IDC_RENAMETHEMEBTN):      AddPopupMenuHelpItem(IDM_RENTHEME_HELP);         break;
	case(IDC_DEFTHEMESBTN):        AddPopupMenuHelpItem(IDM_DEFTHEMES_HELP);        break;
	case(IDC_THEMESHELPBTN):       AddPopupMenuHelpItem(IDM_THEMESHELP_HELP);       break;
	case(IDC_LOADAUDFILEBTN):      AddPopupMenuHelpItem(IDM_LOADMUSFILE_HELP);      break;
	case(IDC_LOADPLISTBTN):        AddPopupMenuHelpItem(IDM_LOADMUSPLIST_HELP);     break;
	case(IDC_CLEARMUSBTN):         AddPopupMenuHelpItem(IDM_CLEARMUSFILE_HELP);     break;
	case(IDC_EDITAUDIOBTN):        AddPopupMenuHelpItem(IDM_EDITAUDIO_HELP);        break;
	case(IDC_CHGMUSHELPBTN):       AddPopupMenuHelpItem(IDM_CHANGEMUS_HELP);        break;
	case(IDC_PLISTSORTCBX):        AddPopupMenuHelpItem(IDM_PLISTSORT_HELP);        break;
	case(IDC_PLISTUPBTN):          AddPopupMenuHelpItem(IDM_PLISTUP_HELP);          break;
	case(IDC_PLISTDOWNBTN):        AddPopupMenuHelpItem(IDM_PLISTDOWN_HELP);        break;
	case(IDC_PLISTTOPBTN):         AddPopupMenuHelpItem(IDM_PLISTTOP_HELP);         break;
	case(IDC_PLISTBOTTOMBTN):      AddPopupMenuHelpItem(IDM_PLISTBOTTOM_HELP);      break;
	case(IDC_PLISTDELBTN):         AddPopupMenuHelpItem(IDM_PLISTDELETE_HELP);      break;
	case(IDC_PLISTCLRBTN):         AddPopupMenuHelpItem(IDM_PLISTCLEAR_HELP);       break;
	case(IDC_PLISTSAVEBTN):        AddPopupMenuHelpItem(IDM_PLISTSAVE_HELP);        break;
	case(IDC_PLISTLOADBTN):        AddPopupMenuHelpItem(IDM_PLISTLOAD_HELP);        break;
	case(IDC_ONESVRRAD):           AddPopupMenuHelpItem(IDM_ONESAVER_HELP);         break;
	case(IDC_MULTISVRRAD):         AddPopupMenuHelpItem(IDM_MULTISAVER_HELP);       break;
	case(IDC_SHOWSVREDT):          AddPopupMenuHelpItem(IDM_SHOWSAVEREDT_HELP);     break;
	case(IDC_SHOWSVRSPIN):         AddPopupMenuHelpItem(IDM_SHOWSAVERSPIN_HELP);    break;
	case(IDC_SVRCYCLERAD):         AddPopupMenuHelpItem(IDM_SAVERCYCLE_HELP);       break;
	case(IDC_SVRSHUFFLERAD):       AddPopupMenuHelpItem(IDM_SAVERSHUFFLE_HELP);     break;
	case(IDC_ENABLEHKEYSCBX):      AddPopupMenuHelpItem(IDM_ENABLEHKEYS_HELP);      break;
	case(IDC_STARTSVRHKY):         AddPopupMenuHelpItem(IDM_STARTSAVERHKY_HELP);    break;
	case(IDC_SKIPSVRHKY):          AddPopupMenuHelpItem(IDM_SKIPSAVERHKY_HELP);     break;
	case(IDC_OPENPSHKY):           AddPopupMenuHelpItem(IDM_OPENPSHKY_HELP);        break;
	case(IDC_CLRSCREENCBX):        AddPopupMenuHelpItem(IDM_CLEARSCREEN_HELP);      break;
	case(IDC_NOMUSICCBX):          AddPopupMenuHelpItem(IDM_NOMUSIC_HELP);          break;
	case(IDC_OPENTHEMESBTN):       AddPopupMenuHelpItem(IDM_OPENTHEMES_HELP);       break;
	case(IDC_OPENAUDIOBTN):        AddPopupMenuHelpItem(IDM_OPENMUSICMGR_HELP);     break;
	case(IDC_ADVWARNTXT):          AddPopupMenuHelpItem(IDM_ADVWARNING_HELP);       break;
	case(IDC_SHOWADVBTN):          AddPopupMenuHelpItem(IDM_SHOWADVANCED_HELP);     break;
	case(IDC_ADDPATHBTN):          AddPopupMenuHelpItem(IDM_ADDPATH_HELP);          break;
	case(IDC_CHANGEPATHBTN):       AddPopupMenuHelpItem(IDM_CHANGEPATH_HELP);       break;
	case(IDC_DELETEPATHBTN):       AddPopupMenuHelpItem(IDM_DELETEPATH_HELP);       break;
	case(IDC_SYSTRAYCHK):          AddPopupMenuHelpItem(IDM_SYSTEMTRAY_HELP);       break;
	case(IDC_KEEPCURCHK):          AddPopupMenuHelpItem(IDM_KEEPCURRENT_HELP);      break;
	case(IDC_HIDEADVCHK):          AddPopupMenuHelpItem(IDM_HIDEADVANCED_HELP);     break;
	case(IDC_ERRORLOGCHK):         AddPopupMenuHelpItem(IDM_ERRORLOGCHK_HELP);      break;
	case(IDC_MAXLINESEDT):         AddPopupMenuHelpItem(IDM_MAXLINESEDT_HELP);      break;
	case(IDC_MAXLINESSPIN):        AddPopupMenuHelpItem(IDM_MAXLINESSPIN_HELP);     break;
	case(IDC_ERRORLOGBTN):         AddPopupMenuHelpItem(IDM_ERRORLOGBTN_HELP);      break;
	case(IDC_RESETMSGBTN):         AddPopupMenuHelpItem(IDM_RESETMSGBTN_HELP);      break;
	case(IDC_HIDEADVBTN):          AddPopupMenuHelpItem(IDM_HIDEADVBTN_HELP);       break;
	case(IDC_HISTORYCBX):          AddPopupMenuHelpItem(IDM_AUDIOHISTORY_HELP);     break;
	case(IDC_FILEBACKBTN):         AddPopupMenuHelpItem(IDM_FILEBACKBTN_HELP);      break;
	case(IDC_FILEUPBTN):           AddPopupMenuHelpItem(IDM_FILEUPBTN_HELP);        break;
	case(IDC_FILETYPECBX):         AddPopupMenuHelpItem(IDM_FILETYPE_HELP);         break;
	case(IDC_CLEARAUDIOSELBTN):    AddPopupMenuHelpItem(IDM_CLEARAUDIOSEL_HELP);    break;
	case(IDC_ADDAUDIOFILEBTN):     AddPopupMenuHelpItem(IDM_ADDAUDIOFILE_HELP);     break;
	case(IDC_AUDIOPLISTSORTCBX):   AddPopupMenuHelpItem(IDM_AUDIOPLISTSORT_HELP);   break;
	case(IDC_AUDIOPLISTUPBTN):     AddPopupMenuHelpItem(IDM_AUDIOPLISTUP_HELP);     break;
	case(IDC_AUDIOPLISTTOPBTN):    AddPopupMenuHelpItem(IDM_AUDIOPLISTTOP_HELP);    break;
	case(IDC_AUDIOPLISTDOWNBTN):   AddPopupMenuHelpItem(IDM_AUDIOPLISTDOWN_HELP);   break;
	case(IDC_AUDIOPLISTBOTTOMBTN): AddPopupMenuHelpItem(IDM_AUDIOPLISTBOTTOM_HELP); break;
	case(IDC_AUDIOPLISTDELBTN):    AddPopupMenuHelpItem(IDM_AUDIOPLISTDEL_HELP);    break;
	case(IDC_AUDIOPLISTCLRBTN):    AddPopupMenuHelpItem(IDM_AUDIOPLISTCLR_HELP);    break;
	case(IDC_AUDIOPLISTSAVEBTN):   AddPopupMenuHelpItem(IDM_AUDIOPLISTSAVE_HELP);   break;
	case(IDC_AUDIOPLISTLOADBTN):   AddPopupMenuHelpItem(IDM_AUDIOPLISTLOAD_HELP);   break;
	case(IDC_AUDIOINFO):           AddPopupMenuHelpItem(IDM_AUDIOINFO_HELP);        break;
	case(IDC_PLAYBTN):             AddPopupMenuHelpItem(IDM_PLAYBTN_HELP);          break;
	case(IDC_PAUSEBTN):            AddPopupMenuHelpItem(IDM_PAUSEBTN_HELP);         break;
	case(IDC_STOPBTN):             AddPopupMenuHelpItem(IDM_STOPBTN_HELP);          break;
	case(IDC_FULLREWBTN):          AddPopupMenuHelpItem(IDM_FULLREWBTN_HELP);       break;
	case(IDC_REWBTN):              AddPopupMenuHelpItem(IDM_REWBTN_HELP);           break;
	case(IDC_FWDBTN):              AddPopupMenuHelpItem(IDM_FWDBTN_HELP);           break;
	case(IDC_AUDIOPOSSLD):         AddPopupMenuHelpItem(IDM_AUDIOPOS_HELP);         break;
	case(IDC_ENABLEPBCCHK):        AddPopupMenuHelpItem(IDM_ENABLEPBC_HELP);        break;
	case(IDC_NEXTHKY):             AddPopupMenuHelpItem(IDM_NEXTHKY_HELP);          break;
	case(IDC_VOLUPHKY):            AddPopupMenuHelpItem(IDM_VOLUPHKY_HELP);         break;
	case(IDC_VOLDNHKY):            AddPopupMenuHelpItem(IDM_VOLDNHKY_HELP);         break;
	case(IDC_MUTEHKY):             AddPopupMenuHelpItem(IDM_MUTEHKY_HELP);          break;
	case(IDC_WINSYNTHRAD):         AddPopupMenuHelpItem(IDM_WINSYNTH_HELP);         break;
	case(IDC_DXSYNTHRAD):          AddPopupMenuHelpItem(IDM_DXSYNTH_HELP);          break;
	case(IDC_REVERBCHK):           AddPopupMenuHelpItem(IDM_REVERB_HELP);           break;
	case(IDC_CHORUSCHK):           AddPopupMenuHelpItem(IDM_CHORUS_HELP);           break;
	case(IDC_MUSMANHELPBTN):       AddPopupMenuHelpItem(IDM_MUSICMGRHELP_HELP);     break;
	case(IDC_INSTALLDXBTN):        AddPopupMenuHelpItem(IDM_INSTALLDX_HELP);        break;
	case(IDC_PLAYSFXCHK):          AddPopupMenuHelpItem(IDM_PLAYSFX_HELP);          break;
	case(IDC_SHOWTOOLTIPSCHK):     AddPopupMenuHelpItem(IDM_TOOLTIPS_HELP);         break;
	case(IDC_SPLASHSCRNCHK):       AddPopupMenuHelpItem(IDM_SPLASHSCRN_HELP);       break;
	case(IDC_SAVERLISTDETCHK):     AddPopupMenuHelpItem(IDM_SAVERLISTDET_HELP);     break;
	case(IDC_RATINGIMGSCHK):       AddPopupMenuHelpItem(IDM_RATINGIMGS_HELP);       break;
	case(IDC_SLISTPOPUPCHK):       AddPopupMenuHelpItem(IDM_SLISTPOPUP_HELP);       break;
	case(IDC_PLISTPOPUPCHK):       AddPopupMenuHelpItem(IDM_PLISTPOPUP_HELP);       break;
	case(IDC_PREFSHELPBTN):        AddPopupMenuHelpItem(IDM_PREFERENCES_HELP);      break;
	case(IDC_WBSOFTBMP):           AddPopupMenuHelpItem(IDM_WBSLINK_HELP);          break;
	case(IDC_ASPLOGOBMP):          AddPopupMenuHelpItem(IDM_ASPLINK_HELP);          break;
	case(IDC_VIEWLICBTN):          AddPopupMenuHelpItem(IDM_VIEWLICBTN_HELP);       break;
	case(IDC_VIEWREADMEBTN):       AddPopupMenuHelpItem(IDM_VIEWREADMEBTN_HELP);    break;
	case(IDC_PSBUYBMP):            AddPopupMenuHelpItem(IDM_PSBUYLINK_HELP);        break;
	case(IDC_ORDERBTN):            AddPopupMenuHelpItem(IDM_ORDERBTN_HELP);         break;
	case(IDC_MAILFORMBTN):         AddPopupMenuHelpItem(IDM_MAILFORMBTN_HELP);      break;

	// saver list
	case(IDC_SAVERLIST):

		// cast pointer to saver info
		lpSaverInfo=(CSaverInfo*)dwData2;

		// check info flag
		if(g_bShowSaverInfo)
		{
			// add menu items
			AddPopupMenuItem("Add to Playlist",IDM_SLIST_ADD);
			AddPopupMenuItem("Edit Info...",   IDM_SLIST_EDIT);
			InsertPopupSubmenu("Change Rating");
				AddPopupSubmenuItem("Not rated",IDM_SLIST_SETRATING0);
				AddPopupSubmenuSeparator();
				AddPopupSubmenuItem("1 Star", IDM_SLIST_SETRATING1);
				AddPopupSubmenuItem("2 Stars",IDM_SLIST_SETRATING2);
				AddPopupSubmenuItem("3 Stars",IDM_SLIST_SETRATING3);
				AddPopupSubmenuItem("4 Stars",IDM_SLIST_SETRATING4);
				AddPopupSubmenuItem("5 Stars",IDM_SLIST_SETRATING5);
			AddPopupMenuSeparator();
			AddPopupMenuItem("Show Details",      IDM_SLIST_DETAILS);
			AddPopupMenuItem("Show Rating Images",IDM_SLIST_RATINGS);
			AddPopupMenuSeparator();
			AddPopupMenuHelpItem(IDM_SLIST_HELP);
			
			// set checks
			CheckPopupMenuItem(IDM_SLIST_DETAILS,g_bShowSaverInfo);
			CheckPopupMenuItem(IDM_SLIST_RATINGS,g_bShowRatingImgs);
			if(lpSaverInfo)
			{
				switch(lpSaverInfo->dwRating)
				{
				case(0): CheckPopupSubmenuItem(IDM_SLIST_SETRATING0); break;
				case(1): CheckPopupSubmenuItem(IDM_SLIST_SETRATING1); break;
				case(2): CheckPopupSubmenuItem(IDM_SLIST_SETRATING2); break;
				case(3): CheckPopupSubmenuItem(IDM_SLIST_SETRATING3); break;
				case(4): CheckPopupSubmenuItem(IDM_SLIST_SETRATING4); break;
				case(5): CheckPopupSubmenuItem(IDM_SLIST_SETRATING5); break;
				}
			}

			// disable as needed
			if(!lpSaverInfo)
			{
				EnablePopupMenuItem(IDM_SLIST_ADD, FALSE);
				EnablePopupMenuItem(IDM_SLIST_EDIT,FALSE);
				EnablePopupMenuItem((UINT)g_lpPopupSubmenu->m_hMenu,FALSE);
			}
		}
		else
		{
			// add menu items
			AddPopupMenuItem("Sort by Name",IDM_SLIST_TITLESORT);
			AddPopupMenuSeparator();
			AddPopupMenuItem("Add to Playlist",IDM_SLIST_ADD);
			AddPopupMenuItem("Edit Info...",   IDM_SLIST_EDIT);
			AddPopupMenuSeparator();
			AddPopupMenuItem("Show Details",   IDM_SLIST_DETAILS);
			AddPopupMenuItem("Show Popup Info",IDM_SLIST_POPUPINFO);
			AddPopupMenuSeparator();
			AddPopupMenuHelpItem(IDM_SLIST_HELP);
			
			// set checks
			CheckPopupMenuItem(IDM_SLIST_DETAILS,  g_bShowSaverInfo);
			CheckPopupMenuItem(IDM_SLIST_POPUPINFO,g_bShowPopupInfo);

			// disable as needed
			if(!lpSaverInfo)
			{
				EnablePopupMenuItem(IDM_SLIST_ADD, FALSE);
				EnablePopupMenuItem(IDM_SLIST_EDIT,FALSE);
			}
		}

		// ok
		break;

	// saver list header
	case(IDC_SLISTHEAD):

		// check info flag
		if(g_bShowSaverInfo)
		{
			// add menu items
			AddPopupMenuItem("Sort by Name",  IDM_SLIST_TITLESORT);
			AddPopupMenuItem("Sort by Theme", IDM_SLIST_THEMESORT);
			AddPopupMenuItem("Sort by Rating",IDM_SLIST_RATINGSORT);
			AddPopupMenuSeparator();
			AddPopupMenuItem("Show Details",      IDM_SLIST_DETAILS);
			AddPopupMenuItem("Show Rating Images",IDM_SLIST_RATINGS);
			AddPopupMenuSeparator();
			AddPopupMenuHelpItem(IDM_SLIST_HELP);
			
			// set checks
			CheckPopupMenuItem(IDM_SLIST_DETAILS,g_bShowSaverInfo);
			CheckPopupMenuItem(IDM_SLIST_RATINGS,g_bShowRatingImgs);
		}
		else
		{
			// add menu items
			AddPopupMenuItem("Sort by Name",IDM_SLIST_TITLESORT);
			AddPopupMenuSeparator();
			AddPopupMenuItem("Show Details",   IDM_SLIST_DETAILS);
			AddPopupMenuItem("Show Popup Info",IDM_SLIST_POPUPINFO);
			AddPopupMenuSeparator();
			AddPopupMenuHelpItem(IDM_SLIST_HELP);
			
			// set checks
			CheckPopupMenuItem(IDM_SLIST_DETAILS,  g_bShowSaverInfo);
			CheckPopupMenuItem(IDM_SLIST_POPUPINFO,g_bShowPopupInfo);
		}

		// ok
		break;

	// saver info box
	case(IDC_SAVERINFO):

		// add menu items
		AddPopupMenuItem("Edit Info...",IDM_SLIST_EDIT);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_SAVERINFO_HELP);

		// disable invalid items
		if(!g_lpCurSaver)
			EnablePopupMenuItem(IDM_SLIST_EDIT,FALSE);
		
		// ok
		break;

	// saver description box
	case(IDC_SAVERDESCEDT):
		
		// add menu items
		AddPopupMenuItem("Undo",IDM_SDESC_UNDO);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Cut",   IDM_SDESC_CUT);
		AddPopupMenuItem("Copy",  IDM_SDESC_COPY);
		AddPopupMenuItem("Paste", IDM_SDESC_PASTE);
		AddPopupMenuItem("Delete",IDM_SDESC_DEL);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Select All",IDM_SDESC_SELALL);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_SAVERDESC_HELP);

		// get current selection
		g_lpSaverDescEdit->GetSel(nSelStart,
								  nSelEnd);

		// disable invalid items
		if(!g_lpSaverDescEdit->CanUndo())
			EnablePopupMenuItem(IDM_SDESC_UNDO,FALSE);
		if(nSelStart==nSelEnd)
		{
			EnablePopupMenuItem(IDM_SDESC_CUT, FALSE);
			EnablePopupMenuItem(IDM_SDESC_COPY,FALSE);
			EnablePopupMenuItem(IDM_SDESC_DEL, FALSE);
		}
		if(g_lpSaverDescEdit->GetWindowTextLength()==0)
			EnablePopupMenuItem(IDM_SDESC_SELALL,FALSE);
		if(!ClipboardHasData())
			EnablePopupMenuItem(IDM_SDESC_PASTE,FALSE);

		// ok
		break;
	
	// new theme box
	case(IDC_NEWTHEMEEDT):
		
		// add menu items
		AddPopupMenuItem("Undo",IDM_NWTHM_UNDO);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Cut",   IDM_NWTHM_CUT);
		AddPopupMenuItem("Copy",  IDM_NWTHM_COPY);
		AddPopupMenuItem("Paste", IDM_NWTHM_PASTE);
		AddPopupMenuItem("Delete",IDM_NWTHM_DEL);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Select All",IDM_NWTHM_SELALL);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_NEWTHEMEEDIT_HELP);

		// get current selection
		g_lpNewThemeEdit->GetSel(nSelStart,
								 nSelEnd);

		// disable invalid items
		if(!g_lpNewThemeEdit->CanUndo())
			EnablePopupMenuItem(IDM_NWTHM_UNDO,FALSE);
		if(nSelStart==nSelEnd)
		{
			EnablePopupMenuItem(IDM_NWTHM_CUT, FALSE);
			EnablePopupMenuItem(IDM_NWTHM_COPY,FALSE);
			EnablePopupMenuItem(IDM_NWTHM_DEL, FALSE);
		}
		if(g_lpNewThemeEdit->GetWindowTextLength()==0)
			EnablePopupMenuItem(IDM_NWTHM_SELALL,FALSE);
		if(!ClipboardHasData())
			EnablePopupMenuItem(IDM_NWTHM_PASTE,FALSE);

		// ok
		break;
	
	// rename theme box
	case(IDC_RENAMETHEMEEDT):
		
		// add menu items
		AddPopupMenuItem("Undo",IDM_RNTHM_UNDO);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Cut",   IDM_RNTHM_CUT);
		AddPopupMenuItem("Copy",  IDM_RNTHM_COPY);
		AddPopupMenuItem("Paste", IDM_RNTHM_PASTE);
		AddPopupMenuItem("Delete",IDM_RNTHM_DEL);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Select All",IDM_RNTHM_SELALL);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_RENTHEMEEDIT_HELP);

		// get current selection
		g_lpRenThemeEdit->GetSel(nSelStart,
								 nSelEnd);

		// disable invalid items
		if(!g_lpRenThemeEdit->CanUndo())
			EnablePopupMenuItem(IDM_RNTHM_UNDO,FALSE);
		if(nSelStart==nSelEnd)
		{
			EnablePopupMenuItem(IDM_RNTHM_CUT, FALSE);
			EnablePopupMenuItem(IDM_RNTHM_COPY,FALSE);
			EnablePopupMenuItem(IDM_RNTHM_DEL, FALSE);
		}
		if(g_lpRenThemeEdit->GetWindowTextLength()==0)
			EnablePopupMenuItem(IDM_RNTHM_SELALL,FALSE);
		if(!ClipboardHasData())
			EnablePopupMenuItem(IDM_RNTHM_PASTE,FALSE);

		// ok
		break;
	
	// music selection box
	case(IDC_MUSICSELBOX):
		
		// add menu items
		AddPopupMenuItem("Load Audio File",    IDM_MUSIC_LOADFILE);
		AddPopupMenuItem("Load Audio Playlist",IDM_MUSIC_LOADPLIST);
		AddPopupMenuItem("Set to None",        IDM_MUSIC_CLEARSEL);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Open Music Manager",IDM_MUSIC_OPENMGR);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_MUSICSEL_HELP);
		
		// disable invalid items
		if(!g_lpSaverInfoDlg->lpMusicPath)
			EnablePopupMenuItem(IDM_MUSIC_CLEARSEL,FALSE);

		// ok
		break;
	
	// themes list
	case(IDC_THEMESLIST):

		// add menu items
		AddPopupMenuItem("Rename",IDM_THEME_REN);
		AddPopupMenuItem("Delete",IDM_THEME_DEL);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_THEMESLIST_HELP);
		
		// disable invalid items
		if(!g_lpThemesList->QuerySelection())
			EnablePopupMenuItem(IDM_THEME_DEL,FALSE);
		if(g_lpThemesList->GetSelCount()!=1)
			EnablePopupMenuItem(IDM_THEME_REN,FALSE);

		// ok
		break;
	
	// saver playlist & header
	case(IDC_CURRPLIST):
	case(IDC_CURRPLISTHEAD):

		// add menu items
		if(g_lpSaverPlaylist->HasInvalid())
		{
			AddPopupMenuItem("Remove Invalid Items",IDM_PLIST_PURGEINV);
		}
		InsertPopupSubmenu("Sort Items by");
			AddPopupSubmenuItem("Name (A-Z)",IDM_PLIST_SORTNAMEAZ);
			AddPopupSubmenuItem("Name (Z-A)",IDM_PLIST_SORTNAMEZA);
			AddPopupSubmenuSeparator();
			AddPopupSubmenuItem("Theme (A-Z)",IDM_PLIST_SORTTHEMEAZ);
			AddPopupSubmenuItem("Theme (Z-A)",IDM_PLIST_SORTTHEMEZA);
			AddPopupSubmenuSeparator();
			AddPopupSubmenuItem("Rating (5-1)",IDM_PLIST_SORTRATING51);
			AddPopupSubmenuItem("Rating (1-5)",IDM_PLIST_SORTRATING15);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Clear Playlist",IDM_PLIST_CLEARLIST);
		AddPopupMenuItem("Save to File",  IDM_PLIST_SAVELIST);
		AddPopupMenuItem("Load from File",IDM_PLIST_LOADLIST);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Show Popup Info",IDM_PLIST_TOGGLEPOPUP);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_CURRPLIST_HELP);

		// disable invalid items
		if(g_lpSaverPlaylist->GetItemCount()<=0)
		{
			EnablePopupMenuItem((UINT)g_lpPopupSubmenu->m_hMenu,FALSE);
			EnablePopupMenuItem(IDM_PLIST_CLEARLIST,FALSE);
			EnablePopupMenuItem(IDM_PLIST_SAVELIST, FALSE);
		}

		// check items as needed
		if(g_bShowPListPopup)
		{
			CheckPopupMenuItem(IDM_PLIST_TOGGLEPOPUP,TRUE);
		}

		// ok
		break;
	
	// search-path list
	case(IDC_SEARCHLIST):

		// add menu items
		AddPopupMenuItem("Add Path",   IDM_SPATH_ADDPATH);
		AddPopupMenuItem("Change Path",IDM_SPATH_CHGPATH);
		AddPopupMenuItem("Remove Path",IDM_SPATH_DELPATH);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_SEARCHPATHLIST_HELP);

		// disable items
		EnablePopupMenuItem(IDM_SPATH_CHGPATH,FALSE);
		EnablePopupMenuItem(IDM_SPATH_DELPATH,FALSE);

		// check for selection
		if(g_lpSearchPathList->QuerySelection())
		{
			// check for default item
			if(!g_lpSearchPathList->GetItemData(g_lpSearchPathList->GetSelection())==1)
			{
				// enable valid items
				EnablePopupMenuItem(IDM_SPATH_CHGPATH,TRUE);
				EnablePopupMenuItem(IDM_SPATH_DELPATH,TRUE);
			}
		}
		
		// ok
		break;
	
	// audio file list
	case(IDC_FILELIST):

		// check for current file
		if(g_lpCurAudioFLD)
		{
			// check for folder or link
			if(g_lpCurAudioFLD->bIsFolder||
			   g_lpCurAudioFLD->bIsLinkToFolder)
			{
				// add menu items
				AddPopupMenuItem("Open Folder",IDM_FLIST_OPENFOLDER);
			}
			else
			{
				// check for active timeout
				if(g_nCurAudioTimerID)
				{
					// begin wait
					::BeginWaitCursor();
					
					// wait for it
					Sleep(AUDIO_TIMEOUT_WAIT);

					// process now
					CurAudioTimerProc(NULL,
									  NULL,
									  NULL,
									  NULL);

					// end wait
					::EndWaitCursor();
				}

				// add menu items
				AddPopupMenuItem("Add to Playlist",IDM_FLIST_ADDFILE);
				AddPopupMenuItem("Play Audio File",IDM_FLIST_PLAYFILE);
				
				// wait for timeout
				WaitForAudioTimeout();

				// check for valid file
				if(!g_nCurAudioDevID)
				{
					// disable invalid items
					EnablePopupMenuItem(IDM_FLIST_ADDFILE, FALSE);
					EnablePopupMenuItem(IDM_FLIST_PLAYFILE,FALSE);
				}
			}

			// add separator
			AddPopupMenuSeparator();
		}

		// add help item
		AddPopupMenuHelpItem(IDM_AUDIOFILELIST_HELP);
		
		// ok
		break;

	// audio playlist & header
	case(IDC_AUDIOPLIST):
	case(IDC_AUDIOPLISTHEAD):

		// add menu items
		if(g_lpAudioPList->HasInvalid())
		{
			AddPopupMenuItem("Remove Invalid Items",IDM_APLST_PURGEINV);
		}
		InsertPopupSubmenu("Sort Items by");
			AddPopupSubmenuItem("Name (A-Z)",IDM_APLST_SORTNAMEAZ);
			AddPopupSubmenuItem("Name (Z-A)",IDM_APLST_SORTNAMEZA);
			AddPopupSubmenuSeparator();
			AddPopupSubmenuItem("Type (A-Z)",IDM_APLST_SORTTYPEAZ);
			AddPopupSubmenuItem("Type (Z-A)",IDM_APLST_SORTTYPEZA);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Clear Playlist",IDM_APLST_CLEARLIST);
		AddPopupMenuItem("Save to File",  IDM_APLST_SAVELIST);
		AddPopupMenuItem("Load from File",IDM_APLST_LOADLIST);
		AddPopupMenuSeparator();
		AddPopupMenuItem("Show Popup Info",IDM_APLST_TOGGLEPOPUP);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_AUDIOPLIST_HELP);

		// disable invalid items
		if(g_lpAudioPList->GetItemCount()<=0)
		{
			EnablePopupMenuItem((UINT)g_lpPopupSubmenu->m_hMenu,FALSE);
			EnablePopupMenuItem(IDM_APLST_CLEARLIST,FALSE);
			EnablePopupMenuItem(IDM_APLST_SAVELIST, FALSE);
		}

		// check items as needed
		if(g_bShowPListPopup)
		{
			CheckPopupMenuItem(IDM_APLST_TOGGLEPOPUP,TRUE);
		}
		
		// ok
		break;

	// preview window
	case(IDC_PREVIEWWND):
		
		// add menu items
		AddPopupMenuItem("Settings",    IDM_SPREV_SETTINGS);
		AddPopupMenuItem("Full Preview",IDM_SPREV_FULLPREV);
		AddPopupMenuSeparator();
		AddPopupMenuHelpItem(IDM_PREVIEWWND_HELP);

		// disable invalid items
		if(!g_lpCurSaver)
		{
			EnablePopupMenuItem(IDM_SPREV_SETTINGS,FALSE);
			EnablePopupMenuItem(IDM_SPREV_FULLPREV,FALSE);
		}
		
		// ok
		break;

	// system tray icon
	case(IDC_SYSTRAYICON):

		// add menu items
#ifdef SHAREWARE_MODE
		if(g_dwTrialDays>0)
#endif
		{
			AddPopupMenuItem("Run Screensaver Now",    IDM_SYSTRY_RUNPS);
			AddPopupMenuItem("Open ProSaver Options",  IDM_SYSTRY_OPENPS);
			AddPopupMenuItem("Show Display Properties",IDM_SYSTRY_OPENCPL);
			AddPopupMenuSeparator();
		}
		AddPopupMenuItem("Hide ProSaver Icon",IDM_SYSTRY_HIDEME);
#ifdef SHAREWARE_MODE
		AddPopupMenuSeparator();
		AddPopupMenuItem("How to Order...",IDM_SYSTRY_PURCH);
#endif
#ifdef DEBUG_MODE
		AddPopupMenuSeparator();
		AddPopupMenuItem("Debug Exit",IDM_SYSTRY_DBGEXIT);
#endif

		// ok
		break;

	// invalid id
	default:

#ifdef DEBUG_MODE
		DisplayErrorMessage("Invalid control ID.",
							"ShowPopupMenu()",
							FALSE);
#endif

		// ok
		break;
	}

	// execute popup menu
	ExecPopupMenu(pCur);
}

// CHistoryComboBox::CHistoryComboBox()

CHistoryComboBox::CHistoryComboBox(UINT nID)
{
	// save id
	nCtrlId=nID;

	// reset values
	lpDirTree   =NULL;
	bNoDraw     =FALSE;
	lpFileList  =NULL;
	nOpenSel    =-1;
	lpHistRoot  =NULL;
	lpHistCur   =NULL;
	lpMyComputer=NULL;
	bTextFit    =FALSE;
	lpParentDlg =NULL;

	// reset bounds
	rCurBounds.SetRect(0,0,0,0);

	// call base method
	CExtComboBox::CExtComboBox();
}

// CHistoryComboBox::Release()

void CHistoryComboBox::Release(void)
{
	// set no-draw
	bNoDraw=TRUE;

	// clear items
	if(IsWindow(m_hWnd))
		ResetContent();

	// check directory tree
	if(lpDirTree)
	{
		// delete root node
		lpDirTree->DeleteNode();

		// free root node
		FreeClassObject(lpDirTree);
	}

	// reset values
	lpFileList  =NULL;
	nOpenSel    =-1;
	lpMyComputer=NULL;
	bTextFit    =FALSE;

	// reset bounds
	rCurBounds.SetRect(0,0,0,0);
}

// CDirTree::CDirTree()

CDirTree::CDirTree(HWND hParentWnd)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hParentWnd==NULL||
	   hParentWnd==(HWND)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid window handle.",
							"CDirTree::CDirTree()",
							FALSE);
		return;
	}

	// verify window
	if(!IsWindow(hParentWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CDirTree::CDirTree()",
							FALSE);
		return;
	}
#endif

	// copy parent
	hParent=hParentWnd;

	// reset values
	lpParent       =NULL;
	lpChild        =NULL;
	lpSibling      =NULL;
	lpShellFolder  =NULL;
	lpItemIDList   =NULL;
	lpDisplayName  =NULL;
	nIndentLevel   =0;
	hIconImgs      =(HIMAGELIST)INVALID_HANDLE_VALUE;
	nIconIdx       =-1;
	nOpenIconIdx   =-1;
	bExpanded      =FALSE;
	bExtracted     =FALSE;
	bIsNSRoot      =FALSE;
	nSpclFolderId  =NULL;
	bDisplay       =FALSE;
	bAlwaysDisplay =FALSE;
	lpFileInfo     =NULL;
	bIsShared      =FALSE;
	bIsLink        =FALSE;
	bNoSortChildren=FALSE;
}

// CDirTree::DeleteNode()

void CDirTree::DeleteNode(void)
{
	// set parent to null
	lpParent=NULL;

	// check child node
	if(lpChild)
	{
		// delete child node
		lpChild->DeleteNode();

		// free child node
		FreeClassObject(lpChild);
	}

	// check sibling node
	if(lpSibling)
	{
		// delete sibling node
		lpSibling->DeleteNode();

		// free sibling node
		FreeClassObject(lpSibling);
	}

	// check id list
	if(lpItemIDList)
	{
		// free memory
		g_lpCoMalloc->Free(lpItemIDList);

		RemoveMemResource

		// reset pointer
		lpItemIDList=NULL;
	}

	// release shell folder
	ReleaseCOMPtr(lpShellFolder);

	// reset folder id
	nSpclFolderId=NULL;

	// release display name
	FreeMem((LPVOID*)&lpDisplayName);

	// reset indentation level
	nIndentLevel=0;

	// reset icon info
	hIconImgs   =(HIMAGELIST)INVALID_HANDLE_VALUE;
	nIconIdx    =-1;
	nOpenIconIdx=-1;

	// reset flags
	bExpanded      =FALSE;
	bExtracted     =FALSE;
	bIsNSRoot      =FALSE;
	bDisplay       =FALSE;
	bAlwaysDisplay =FALSE;
	bIsShared      =FALSE;
	bIsLink        =FALSE;
	bNoSortChildren=FALSE;

	// check file info
	if(lpFileInfo)
	{
		// delete file info
		lpFileInfo->Delete();

		// free file info
		FreeClassObject(lpFileInfo);
	}
}

// CDirTree::CreateNamespaceRoot()

BOOL CDirTree::CreateNamespaceRoot(CDirTree** lplpMyComputer)
{
	// redraw history box (to prevent flicker)
	if(g_lpAudioHistoryCbx)
		g_lpAudioHistoryCbx->RedrawWindow();

	// begin wait cursor
	::BeginWaitCursor();

	// delete any existing data
	DeleteNode();

	// get desktop folder
	if(FAILED(SHGetDesktopFolder(&lpShellFolder)))
	{
		DisplayErrorMessage("Unable to find namespace root.");
		::EndWaitCursor();
		return(FALSE);
	}
	else
		AddCOMResource

	// set root flag
	bIsNSRoot=TRUE;

	// set indentation level
	nIndentLevel=0;

	// extract info
	if(!ExtractFolderInfo())
	{
		::EndWaitCursor();
		return(FALSE);
	}

	// add 'My Documents'
	if(!AddChildSpclFolder(this,
						   CSIDL_PERSONAL,
						   nIndentLevel+1))
	{
		::EndWaitCursor();
		return(FALSE);
	}

	// add 'My Computer'
	if(!AddChildSpclFolder(this,
						   CSIDL_DRIVES,
						   nIndentLevel+1))
	{
		::EndWaitCursor();
		return(FALSE);
	}

	// set pointer to 'My Computer'
	(*lplpMyComputer)=lpChild->lpSibling;

	// expand 'My Computer'
	if(!(*lplpMyComputer)->ExpandNode(TRUE))
	{
		::EndWaitCursor();
		return(FALSE);
	}

	// add 'My Network Places'
	if(!AddChildSpclFolder(this,
						   CSIDL_NETWORK,
						   nIndentLevel+1))
	{
		::EndWaitCursor();
		return(FALSE);
	}

	// extract files
	if(!ExtractFiles())
	{
		::EndWaitCursor();
		return(FALSE);
	}

	// set expanded flag
	bExpanded=TRUE;

	// set to always display (in combo box)
	AlwaysDisplayBranch();
	
	// end wait cursor
	::EndWaitCursor();

	// ok
	return(TRUE);
}

// CDirTree::ExtractFolderInfo()

BOOL CDirTree::ExtractFolderInfo(void)
{
#ifdef DEBUG_MODE
	// check shell folder
	if(!lpShellFolder)
	{
		DisplayErrorMessage("Shell folder does not exist.",
							"CDirTree::ExtractFolderInfo()",
							FALSE);
		return(FALSE);
	}
#endif

	// persist-folder interface
	IPersistFolder2* lpPersistFolder=NULL;

	// bytes used
	ULONG uUsed;

	// file info
	SHFILEINFO sfi;

	// check flag
	if(bExtracted)
		return(TRUE);

	// get persist-folder inferface
	if(FAILED(lpShellFolder->QueryInterface(IID_IPersistFolder2,
											(LPVOID*)&lpPersistFolder)))
	{
		// check for existing id list
		if(!lpItemIDList)
		{
			// just to verify
			LockGlobalMsg()
			LockGlobalLongMsg()
			UnlockGlobalMsg()
			UnlockGlobalLongMsg()

			// set current path id
			strcpy(g_lpMsg,
				   ".");

			// convert to wide
			MakeWideString((LPWSTR)g_lpLongMsg,
						   g_lpMsg);

			// attempt to create id list
			if(FAILED(lpShellFolder->ParseDisplayName(NULL,
													  NULL,
													  (LPWSTR)g_lpLongMsg,
													  &uUsed,
													  &lpItemIDList,
													  NULL)))
			{
				DisplayNEErrorMessage("Unable to get folder interface.");
				return(FALSE);
			}
		}
	}
	else
	{
		AddCOMResource
		
		// check for existing id list
		if(lpItemIDList)
		{
			// free list
			g_lpCoMalloc->Free(lpItemIDList);

			RemoveMemResource

			// reset pointer
			lpItemIDList=NULL;
		}

		// get folder id list
		if(FAILED(lpPersistFolder->GetCurFolder(&lpItemIDList)))
		{
			DisplayNEErrorMessage("Unable to read current folder.");
			ReleaseCOMPtr(lpPersistFolder);
			return(FALSE);
		}
		
		AddMemResource

		// release persist-folder
		ReleaseCOMPtr(lpPersistFolder);
	}

	// set required flags
	sfi.dwAttributes=SFGAO_LINK|
					 SFGAO_SHARE;

	// get display name
	if(!SHGetFileInfo((LPCTSTR)lpItemIDList,
					  NULL,
					  &sfi,
					  sizeof(sfi),
					  SHGFI_PIDL|
					  SHGFI_DISPLAYNAME|
					  SHGFI_ATTRIBUTES|
					  SHGFI_ATTR_SPECIFIED))
	{
		DisplayNEErrorMessage("Unable to read folder display name.");
		return(FALSE);
	}

	// allocate memory for name
	if(!AllocMem((LPVOID*)&lpDisplayName,
				 strlen(sfi.szDisplayName)+1))
		return(FALSE);

	// copy name
	strcpy(lpDisplayName,
		   sfi.szDisplayName);

	// set flags
	bIsShared=(sfi.dwAttributes&SFGAO_SHARE) ? TRUE : FALSE;
	bIsLink  =(sfi.dwAttributes&SFGAO_LINK)  ? TRUE : FALSE;

	// get normal icon
	hIconImgs=(HIMAGELIST)SHGetFileInfo((LPCTSTR)lpItemIDList,
										NULL,
										&sfi,
										sizeof(sfi),
										SHGFI_PIDL|
										SHGFI_SYSICONINDEX|
										SHGFI_SMALLICON);

	// check handle
	if(hIconImgs==NULL||
	   hIconImgs==INVALID_HANDLE_VALUE)
	{
		DisplayNEErrorMessage("Unable to read folder icon.");
		return(FALSE);
	}

	// copy icon index
	nIconIdx=sfi.iIcon;
	
	// get open icon
	if(!SHGetFileInfo((LPCTSTR)lpItemIDList,
					  NULL,
					  &sfi,
					  sizeof(sfi),
					  SHGFI_PIDL|
					  SHGFI_SYSICONINDEX|
					  SHGFI_SMALLICON|
					  SHGFI_OPENICON))
	{
		// copy normal icon
		nOpenIconIdx=nIconIdx;
	}
	else
	{
		// copy icon index
		nOpenIconIdx=sfi.iIcon;
	}

	// set file list data
	fld.bIsFolder      =TRUE;
	fld.bIsLinkToFolder=FALSE;
	fld.lpData         =(LPVOID)this;

	// set flag
	bExtracted=TRUE;

	// maintain message queue
	MaintainMessageQueue(g_lpCurMusicMgrDlg,
						 TRUE);

	// ok
	return(TRUE);
}

// CDirTree::AddChild()

BOOL CDirTree::AddChild(CDirTree* lpParentNode,
						IShellFolder* lpNewFolder,
						int nLevel,
						LPITEMIDLIST lpTempIDList,
						int nID)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpParentNode||
	   !lpNewFolder)
	{
		DisplayErrorMessage("Invalid pointer value.",
						    "CDirTree::AddChild()",
							FALSE);
		return(FALSE);
	}
#endif

	// check for child
	if(lpChild)
	{
		// add to sibling of child
		return(lpChild->AddSibling(lpParentNode,
								   lpNewFolder,
								   nLevel,
								   lpTempIDList,
								   nID));
	}

	// create child
	AllocClassObject(lpChild,
					 CDirTree(hParent));

	// check new object
	if(!lpChild)
		return(FALSE);

	// copy parent node
	lpChild->lpParent=lpParentNode;

	// copy folder interface
	lpChild->lpShellFolder=lpNewFolder;

	// copy item id list
	lpChild->lpItemIDList=lpTempIDList;

	// copy folder id
	lpChild->nSpclFolderId=nID;

	// copy indentation level
	lpChild->nIndentLevel=nLevel;

	// extract folder info
	if(!lpChild->ExtractFolderInfo())
		return(FALSE);

	// ok
	return(TRUE);
}

// CDirTree::AddSibling()

BOOL CDirTree::AddSibling(CDirTree* lpParentNode,
						  IShellFolder* lpNewFolder,
						  int nLevel,
						  LPITEMIDLIST lpTempIDList,
						  int nID)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpParentNode||
	   !lpNewFolder)
	{
		DisplayErrorMessage("Invalid pointer value.",
						    "CDirTree::AddSibling()",
							FALSE);
		return(FALSE);
	}
#endif

	// check for sibling
	if(lpSibling)
	{
		// add to sibling of sibling
		return(lpSibling->AddSibling(lpParentNode,
									 lpNewFolder,
									 nLevel,
									 lpTempIDList,
									 nID));
	}

	// create sibling
	AllocClassObject(lpSibling,
					 CDirTree(hParent));

	// check new object
	if(!lpSibling)
		return(FALSE);

	// copy parent node
	lpSibling->lpParent=lpParentNode;

	// copy folder interface
	lpSibling->lpShellFolder=lpNewFolder;

	// copy item id list
	lpSibling->lpItemIDList=lpTempIDList;

	// copy folder id
	lpSibling->nSpclFolderId=nID;

	// copy indentation level
	lpSibling->nIndentLevel=nLevel;

	// extract folder info
	if(!lpSibling->ExtractFolderInfo())
		return(FALSE);

	// ok
	return(TRUE);
}

// CDirTree::AddChildSpclFolder()

BOOL CDirTree::AddChildSpclFolder(CDirTree* lpParentNode,
								  int nID,
								  int nLevel)
{
#ifdef DEBUG_MODE
	// check pointer
	if(!lpParentNode)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CDirTree::AddChildSpclFolder()",
							FALSE);
		return(FALSE);
	}

	// check shell folder
	if(!lpShellFolder)
	{
		DisplayErrorMessage("Shell folder does not exist.",
							"CDirTree::AddChildSpclFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// item id list (temporary)
	LPITEMIDLIST lpTempIDList=NULL;

	// subfolder interface
	IShellFolder* lpNewFolder=NULL;

	// get folder location
	if(FAILED(SHGetSpecialFolderLocation(hParent,
										 nID,
										 &lpTempIDList)))
	{
		DisplayErrorMessage("Unable to find special folder location.");
		return(FALSE);
	}
	else
		AddMemResource

	// get subfolder interface
	if(FAILED(lpShellFolder->BindToObject(lpTempIDList,
										  NULL,
										  IID_IShellFolder,
										  (LPVOID*)&lpNewFolder)))
	{
		DisplayErrorMessage("Unable to get special folder interface.");
		g_lpCoMalloc->Free(lpTempIDList);
		RemoveMemResource
		return(FALSE);
	}
	else
		AddCOMResource

	// free temporary list
	g_lpCoMalloc->Free(lpTempIDList);

	RemoveMemResource

	// add child
	return(AddChild(lpParentNode,
					lpNewFolder,
					nLevel,
					NULL,
					nID));
}

// CHistoryComboBox::DrawItem()

void CHistoryComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// rectangles
	CRect rItem;
	CRect rText;
	CRect rFocus;
	CRect rIcon;

	// text color
	COLORREF clrText;

	// highlight color
	COLORREF clrHilite;

	// counters
	int nX;
	int nY;

	// background mode
	int nBkgMode;

	// check no-draw flag
	if(bNoDraw)
		return;

	// check for no items
	if(GetCount()==0)
		return;

	// check item id
	if((int)(lpDrawItemStruct->itemID)<0)
		return;

	// cast pointer to item
	CDirTree* lpItem=(CDirTree*)lpDrawItemStruct->itemData;

	// copy item state
	int nState=lpDrawItemStruct->itemState;

	// get device context
	CDC* lpDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	// copy pointer to text
	LPSTR lpText=lpItem->lpDisplayName;

	// copy indentation level
	int nLevel=lpItem->nIndentLevel;

	// get image list
	CImageList* lpIcons=CImageList::FromHandle(lpItem->hIconImgs);

	// check for error
	if(!lpIcons)
	{
		DisplayNEErrorMessage("Unable to find system icon images.");
		return;
	}

	// copy icon index
	int nIcon=((nOpenSel==(int)lpDrawItemStruct->itemID) ? lpItem->nOpenIconIdx : lpItem->nIconIdx);

	// copy flags
	BOOL bIsShared=lpItem->bIsShared;
	BOOL bIsLink  =lpItem->bIsLink;

	// set text-drawing flags
	UINT nFlags=DT_SINGLELINE|
				DT_LEFT|
				DT_VCENTER|
				DT_END_ELLIPSIS;

	// set item rect (with 2-px gap on right)
	rItem.SetRect(lpDrawItemStruct->rcItem.left,
				  lpDrawItemStruct->rcItem.top,
				  lpDrawItemStruct->rcItem.right-2,
				  lpDrawItemStruct->rcItem.bottom);

	// copy icon rect
	rIcon.CopyRect(&rItem);

	// clip to size
	rIcon.right =rIcon.left+16;
	rIcon.bottom=rIcon.top +16;

	// copy text rect
	rText.CopyRect(&rItem);

	// compute text rect
	if(!lpDC->DrawText(lpText,
					   -1,
					   &rText,
					   nFlags|DT_CALCRECT))
	{
		DisplayNEErrorMessage("Unable to compute combo box rectangle.");
		return;
	}

	// copy focus rect
	rFocus.CopyRect(&rText);

	// adjust focus rect
	rFocus.InflateRect(1,0,4,1);

	// place rects
	rIcon.OffsetRect(1,0);
	rText.OffsetRect(21,0);
	rFocus.OffsetRect(20,0);
	
	// check for selection area
	if(!(nState&ODS_COMBOBOXEDIT))
	{
		// indent rects
		rIcon.OffsetRect((nLevel*11),0);
		rText.OffsetRect((nLevel*11),0);
		rFocus.OffsetRect((nLevel*11),0);
	}
	else
	{
		// move rects down
		rIcon.OffsetRect(0,1);
		rText.OffsetRect(0,1);
		rFocus.OffsetRect(0,1);
	}

	// clip right sides
	if(rIcon.right>rItem.right)
		rIcon.right=rItem.right;
	if(rText.right>rItem.right)
		rText.right=rItem.right;
	if(rFocus.right>rItem.right)
	{
		// clip side
		rFocus.right=rItem.right;

		// clear fit flag
		bTextFit=FALSE;
	}
	else
	{
		// set fit flag
		bTextFit=TRUE;
	}

	// check for overflow
	if((rIcon.left >=rIcon.right)||
	   (rText.left >=rText.right)||
	   (rFocus.left>=rFocus.right))
		return;

	// check for selection field
	if(nState&ODS_COMBOBOXEDIT)
	{
		// save bounds
		rCurBounds=rFocus;
	}

	// draw icon
	if(!lpIcons->Draw(lpDC,
					  nIcon,
					  CPoint(rIcon.left,
							 rIcon.top),
					  ILD_NORMAL))
	{
		DisplayNEErrorMessage("Unable to draw icon in combo box.");
		return;
	}

	// add 'shared' icon
	if(bIsShared)
		if(!g_lpOverlayIcons->Draw(lpDC,
								   0,
								   CPoint(rIcon.left,
									    rIcon.top),
								   ILD_TRANSPARENT|
								   ILD_NORMAL))
		{
			DisplayNEErrorMessage("Unable to draw 'shared' icon overlay in combo box.");
			return;
		}

	// add 'link' icon
	if(bIsLink)
		if(!g_lpOverlayIcons->Draw(lpDC,
								   1,
								   CPoint(rIcon.left,
									      rIcon.top),
								   ILD_TRANSPARENT|
								   ILD_NORMAL))
		{
			DisplayNEErrorMessage("Unable to draw 'link' icon overlay in combo box.");
			return;
		}

	// set background mode
	nBkgMode=lpDC->SetBkMode(TRANSPARENT);

	// check state flag
	if(nState&ODS_SELECTED)
	{
		// fill background
		lpDC->FillSolidRect(&rFocus,
							GetSysColor(COLOR_HIGHLIGHT));

		// set text color
		clrText=lpDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

		// draw focus rect
		lpDC->DrawFocusRect(&rFocus);

		// copy highlight color
		clrHilite=GetSysColor(COLOR_HIGHLIGHT);

		// highlight icon
		for(nX=0;nX<16;nX++)
			for(nY=0;nY<16;nY++)
				{
					// draw every other pixel	
					if(!((nX+nY)&1))
						lpDC->SetPixelV(rIcon.left+nX,
									    rIcon.top +nY,
									    clrHilite);
				}
	}
	else
	{
		// fill background
		lpDC->FillSolidRect(&rFocus,
							GetSysColor(COLOR_WINDOW));

		// set text color
		clrText=lpDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	}

	// draw text
	if(!lpDC->DrawText(lpText,
					   -1,
					   &rText,
					   nFlags))
		DisplayNEErrorMessage("Unable to draw text in combo box.");

	// restore text color
	lpDC->SetTextColor(clrText);

	// restore background mode
	lpDC->SetBkMode(nBkgMode);
}

// CDirTree::AlwaysDisplayBranch()

void CDirTree::AlwaysDisplayBranch(BOOL bFlag)
{
	// copy flag
	bAlwaysDisplay=bFlag;

	// pass it on
	if(lpChild)   lpChild->AlwaysDisplayBranch(bFlag);
	if(lpSibling) lpSibling->AlwaysDisplayBranch(bFlag);
}

// CDirTree::AddToComboBox()

BOOL CDirTree::AddToComboBox(CComboBox* lpCbx)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpCbx)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CDirTree::AddToComboBox()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpCbx->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CDirTree::AddToComboBox()",
							FALSE);
		return(FALSE);
	}
#endif

	// index
	int nIndex;

	// set return value
	BOOL bRet=TRUE;

	// check display flags
	if(bDisplay||
	   bAlwaysDisplay)
	{
		// add empty string
		nIndex=lpCbx->AddString(NULL_STRING);

		// check for error
		if(nIndex<0)
		{
			DisplayNEErrorMessage("Unable to add item to history box.");
			return(FALSE);
		}

		// set pointer to item
		if(lpCbx->SetItemData(nIndex,
							  (DWORD)this)==CB_ERR)
		{
			DisplayNEErrorMessage("Unable to add item to history box item data.");
			return(FALSE);
		}

		// check child
		if(lpChild)
		{
			// add child
			if(!lpChild->AddToComboBox(lpCbx))
				bRet=FALSE;
		}
	}

	// check sibling
	if(lpSibling)
	{
		// add sibling
		if(!lpSibling->AddToComboBox(lpCbx))
			bRet=FALSE;
	}

	// ok
	return(bRet);
}

// CHistoryComboBox::Init()

BOOL CHistoryComboBox::Init(CExtDialog* lpParent)
{
	// parent window
	CWnd* lpParentWnd=NULL;

	// set height of items & edit box
	if(SetItemHeight(-1,17)==CB_ERR||
	   SetItemHeight( 0,17)==CB_ERR)
	{
		DisplayErrorMessage("Unable to set combo box item height.");
		return(FALSE);
	}

	// get parent
	if(!GetSafeParentWnd(&lpParentWnd,
						 this))
		return(FALSE);

	// allocate directory tree
	AllocClassObject(lpDirTree,
					 CDirTree(lpParentWnd->m_hWnd));

	// check for error
	if(!lpDirTree)
		return(FALSE);

	// set no-draw
	bNoDraw=TRUE;

	// create root
	if(!lpDirTree->CreateNamespaceRoot(&lpMyComputer))
		return(FALSE);

	// add tree to combo box
	lpDirTree->AddToComboBox(this);

	// create history list
	AllocClassObject(lpHistRoot,
					 CFolderHistory);

	// check new object
	if(!lpHistRoot)
		return(FALSE);

	// set current to root
	lpHistCur=lpHistRoot;

	// clear no-draw
	bNoDraw=FALSE;

	// redraw window
	RedrawWindow();

	// clear current audio
	SetCurrentAudio(NULL);

	// copy parent dialog
	lpParentDlg=lpParent;

	// ok
	return(TRUE);
}

// CFileInfo::CFileInfo()

CFileInfo::CFileInfo()
{
	// reset values
	lpParent       =NULL;
	lpItemIDList   =NULL;
	lpNext         =NULL;
	lpDisplayName  =NULL;
	lpTitle        =NULL;
	hIconImgs      =(HIMAGELIST)INVALID_HANDLE_VALUE;
	nIconIdx       =-1;
	bExtracted     =FALSE;
	bIsShared      =FALSE;
	bIsLink        =FALSE;
	bIsLinkToFolder=FALSE;
	lpExtension    =NULL;
	lpFileData     =NULL;
	dwUserData     =NULL;
}

// CFileInfo::Add()

BOOL CFileInfo::Add(CDirTree* lpParentNode,
					LPITEMIDLIST lpTempIDList)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpParentNode||
	   !lpTempIDList)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CFileInfo::Add()",
							FALSE);
		return(FALSE);
	}
#endif

	// check for next item
	if(lpNext)
		return(lpNext->Add(lpParentNode,
						   lpTempIDList));

	// create next item
	AllocClassObject(lpNext,
					 CFileInfo);

	// check new object
	if(!lpNext)
		return(FALSE);

	// copy parent node
	lpParent=lpParentNode;

	// copy id list
	lpItemIDList=lpTempIDList;

	// extract info
	return(Extract());
}

// CFileInfo::Delete()

void CFileInfo::Delete(void)
{
	// delete next item
	if(lpNext)
		lpNext->Delete();

	// set parent to null
	lpParent=NULL;

	// free next item
	FreeClassObject(lpNext);

	// check id list
	if(lpItemIDList)
	{
		// free id list
		g_lpCoMalloc->Free(lpItemIDList);

		RemoveMemResource
	}

	// free strings
	FreeMem((LPVOID*)&lpDisplayName);
	FreeMem((LPVOID*)&lpExtension);
	FreeMem((LPVOID*)&lpTitle);
	FreeMem((LPVOID*)&lpFileData);

	// reset icon info
	hIconImgs=(HIMAGELIST)INVALID_HANDLE_VALUE;
	nIconIdx =-1;

	// reset flags
	bIsShared      =FALSE;
	bIsLink        =FALSE;
	bIsLinkToFolder=FALSE;
}

// CFileInfo::GetPath()

BOOL CFileInfo::GetPath(LPSTR lpPathRet)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPathRet)
	{
		DisplayErrorMessage("Invalid string value.",
							"CFileInfo::GetPath()",
							FALSE);
		return(FALSE);
	}
#endif

	// returned string
	STRRET sr;

	// get path
	if(FAILED(lpParent->lpShellFolder->GetDisplayNameOf(lpItemIDList,
														SHGDN_NORMAL|
														SHGDN_FORPARSING,
														&sr)))
	{
		DisplayNEErrorMessage("Unable to get path of file.");
		return(FALSE);
	}

	// check type
	if(sr.uType==STRRET_WSTR)
	{
		// convert to multi-byte
		if(!WideCharToMultiByte(CP_ACP,
								NULL,
								sr.pOleStr,
								-1,
								lpPathRet,
								LONG_MSG_SIZE,
								NULL,
								NULL))
		{
			DisplayNEErrorMessage("Unable to convert file path.");
			return(FALSE);
		}
	}
	else if(sr.uType==STRRET_CSTR)
	{
		// copy string
		strcpy(lpPathRet,
			   sr.cStr);
	}
	else
	{
		DisplayNEErrorMessage("Unrecognized path type.");
		return(FALSE);
	}

	// check for empty string
	if(!strlen(lpPathRet))
		return(FALSE);

	// ok
	return(TRUE);
}

// CFileInfo::Extract()

BOOL CFileInfo::Extract(void)
{
	// file info
	SHFILEINFO sfi;

	// check for id list
	if(!lpItemIDList)
	{
#ifdef DEBUG_MODE
		DisplayErrorMessage("Invalid item ID list.",
							"CFileInfo::Extract()",
							FALSE);
#endif
		return(FALSE);

	}

	// check flag
	if(bExtracted)
		return(TRUE);

	LockGlobalMsg()

	// get full path
	if(!GetPath(g_lpMsg))
	{
		UnlockGlobalMsg()
		return(FALSE);
	}

	// get extension
	if(!GetExtensionFromPath(g_lpMsg,
							 &lpExtension))
	{
		// allocate memory
		if(!AllocMem((LPVOID*)&lpExtension,
					 1))
			return(FALSE);

		// set null extension
		lpExtension[0]=0;
	}

	// set required flags
	sfi.dwAttributes=SFGAO_LINK|
					 SFGAO_SHARE;

	// get display name
	if(!SHGetFileInfo((LPCTSTR)g_lpMsg,
					  NULL,
					  &sfi,
					  sizeof(sfi),
					  SHGFI_DISPLAYNAME|
					  SHGFI_ATTRIBUTES|
					  SHGFI_ATTR_SPECIFIED))
	{
		DisplayNEErrorMessage("Unable to read file display name.");
		UnlockGlobalMsg()
		return(FALSE);
	}

	// check display name
	if(strlen(sfi.szDisplayName))
	{
		// allocate memory for name
		if(!AllocMem((LPVOID*)&lpDisplayName,
					 strlen(sfi.szDisplayName)+1))
		{
			UnlockGlobalMsg()
			return(FALSE);
		}

		// copy name
		strcpy(lpDisplayName,
			   sfi.szDisplayName);
	}

	// get title
	if(!ClipExtensionFromPath(lpDisplayName,
							  &lpTitle))
	{
		// allocate memory
		if(!AllocMem((LPVOID*)&lpTitle,
					 strlen(lpDisplayName)+1))
			return(FALSE);

		// copy display name
		strcpy(lpTitle,
			   lpDisplayName);
	}

	// set flags
	bIsShared=(sfi.dwAttributes&SFGAO_SHARE) ? TRUE : FALSE;
	bIsLink  =(sfi.dwAttributes&SFGAO_LINK)  ? TRUE : FALSE;

	// get normal icon
	hIconImgs=(HIMAGELIST)SHGetFileInfo((LPCTSTR)g_lpMsg,
										NULL,
										&sfi,
										sizeof(sfi),
										SHGFI_SYSICONINDEX|
										SHGFI_SMALLICON);

	// check handle
	if(hIconImgs==NULL||
	   hIconImgs==INVALID_HANDLE_VALUE)
	{
		DisplayNEErrorMessage("Unable to read folder icon.");
		UnlockGlobalMsg()
		return(FALSE);
	}

	// copy icon index
	nIconIdx=sfi.iIcon;

	// check for link
	if(bIsLink)
	{
		// check for folder
		if(IsLinkToFolder(g_lpMsg))
			bIsLinkToFolder=TRUE;
	}

	UnlockGlobalMsg()
	
	// set file list data
	fld.bIsFolder      =FALSE;
	fld.bIsLinkToFolder=bIsLinkToFolder;
	fld.lpData         =(LPVOID)this;

	// set extracted flag
	bExtracted=TRUE;

	// maintain message queue
	MaintainMessageQueue(g_lpCurMusicMgrDlg,
						 TRUE);

	// ok
	return(TRUE);
}

// CFileListCtrl::ShowFolder()

BOOL CFileListCtrl::ShowFolder(int nIndex,
							   BOOL bSaveInHist)
{
	// check index
	if(nIndex==-1)
	{
		// get selection
		nIndex=lpHistoryCbx->GetCurSel();

		// check for error
		if(nIndex==CB_ERR)
		{
			DisplayErrorMessage("No item is selected.");
			return(FALSE);
		}
	}

	// get item data
	CDirTree* lpDirTree=(CDirTree*)lpHistoryCbx->GetItemData(nIndex);

	// check item data
	if(!lpDirTree)
	{
		DisplayErrorMessage("Unable to find folder data.");
		return(FALSE);
	}

	// ok
	return(ShowFolder(lpDirTree,
					  bSaveInHist));
}

// CFileListCtrl::OnCustomDraw()

void CFileListCtrl::OnCustomDraw(NMHDR* pNMHDR,
								 LRESULT* pResult)
{
	// get pointer to custom draw header
	LPNMLVCUSTOMDRAW lpLVCD=(LPNMLVCUSTOMDRAW)pNMHDR;

	// text colors
	COLORREF clrTxt;
	COLORREF clrBkg;

	// pointer to device context
	CDC* lpDC=NULL;

	// device context state
	int nState;

	// drawing areas
	CRect rcMain;
	CRect rcHead;
	CRect rcItem;
	CRect rcIcon;
	CRect rcText;
	CRect rcFocus;

	// pointer to header control
	CHeaderCtrl* lpHC=NULL;

	// pointer to icon list
	CImageList* lpIcons=NULL;

	// file list data
	LPFILELISTDATA lpFLD=NULL;

	// pointers to file data
	CDirTree*  lpDirTree =NULL;
	CFileInfo* lpFileInfo=NULL;

	// icon index
	int nIconIdx;

	// pointer to display name
	LPSTR lpDisplayName=NULL;

	// overlay flags
	BOOL bIsShared;
	BOOL bIsLink;

	// text-drawing flags
	UINT nFlags;

	// item state
	UINT nItemState;

	// counters
	int nX;
	int nY;

	// highlight color
	COLORREF clrHilite;

	// saved gdi object
	CGdiObject* lpGdiObj=NULL;

	// assume default processing
	(*pResult)=CDRF_DODEFAULT;

	// check draw stage
	switch(lpLVCD->nmcd.dwDrawStage)
	{
	// general pre-paint stage
	case(CDDS_PREPAINT):

		// check number of items
		if(GetItemCount()<=0)
		{
			// get text colors
			clrTxt=GetSysColor(COLOR_GRAYTEXT);
			clrBkg=GetSysColor(COLOR_WINDOW);

			// get device context
			lpDC=CDC::FromHandle(lpLVCD->nmcd.hdc);

			// check device context
			if(!lpDC)
				return;

			// save device context state
			nState=lpDC->SaveDC();

			// get window area
			GetWindowRect(&rcMain);
			
			// convert to client
			ScreenToClient(&rcMain);

			// get header control		
			lpHC=GetHeaderCtrl();

			// check for control
			if(lpHC)
			{
				// get header rect
				if(lpHC->GetItemRect(0,
									 &rcHead))
				{
					// update drawing area
					rcMain.top+=rcHead.bottom;
				}
			}	

			// add white space
			rcMain.top+=4;

			// set text parameters
			lpDC->SetTextColor(clrTxt);
			lpDC->SetBkColor(clrBkg);

			// clear rect
			lpDC->FillRect(rcMain,
						   &CBrush(clrBkg));

			// select current font
			lpGdiObj=lpDC->SelectObject(GetFont());

			// draw text
			lpDC->DrawText(bIsFilling ? "Searching for files..." : "No files to display",
						   -1,
						   rcMain,
						   DT_CENTER|
						   DT_WORDBREAK|
						   DT_NOPREFIX);

			// restore gdi object
			lpDC->SelectObject(lpGdiObj);

			// restore device context
			lpDC->RestoreDC(nState);

			// stop here
			(*pResult)=CDRF_SKIPDEFAULT;
		}
		else
		{
			// check filling flag
			if(bIsFilling)
				break;

			// get notification of each item
			(*pResult)=CDRF_NOTIFYITEMDRAW;
		}

		// ok
		break;

	// item pre-paint stage
	case(CDDS_ITEMPREPAINT):

		// check filling flag
		if(bIsFilling)
			break;

		// get file list data
		lpFLD=(LPFILELISTDATA)GetItemData((int)lpLVCD->nmcd.dwItemSpec);

		// check item data
		if(!lpFLD)
			return;

		// check data pointer
		if(!lpFLD->lpData)
			return;

		// check file type
		if(lpFLD->bIsFolder)
		{
			// cast pointer to folder tree
			lpDirTree=(CDirTree*)lpFLD->lpData;

			// get pointer to icon list
			lpIcons=CImageList::FromHandle(lpDirTree->hIconImgs);

			// check icon list
			if(!lpIcons)
				return;

			// get icon index
			nIconIdx=lpDirTree->nIconIdx;

			// get display name
			lpDisplayName=lpDirTree->lpDisplayName;

			// get overlay flags
			bIsShared=lpDirTree->bIsShared;
			bIsLink  =lpDirTree->bIsLink;
		}
		else
		{
			// cast pointer to file info
			lpFileInfo=(CFileInfo*)lpFLD->lpData;

			// get pointer to icon list
			lpIcons=CImageList::FromHandle(lpFileInfo->hIconImgs);

			// check icon list
			if(!lpIcons)
				return;

			// get icon index
			nIconIdx=lpFileInfo->nIconIdx;

			// get display name
			lpDisplayName=lpFileInfo->lpDisplayName;

			// get overlay flags
			bIsShared=lpFileInfo->bIsShared;
			bIsLink  =lpFileInfo->bIsLink;
		}

		// get device context
		lpDC=CDC::FromHandle(lpLVCD->nmcd.hdc);

		// check device context
		if(!lpDC)
			return;

		// save state
		nState=lpDC->SaveDC();

		// get bounding rectangle
		if(!GetItemRect(lpLVCD->nmcd.dwItemSpec,
						rcItem,
						LVIR_BOUNDS))
			return;

		// place 2-px gap on right side
		rcItem.right-=2;

		// copy icon rect
		rcIcon.CopyRect(&rcItem);

		// clip to size
		rcIcon.right =rcIcon.left+16;
		rcIcon.bottom=rcIcon.top +16;

		// copy text rect
		rcText.CopyRect(&rcItem);

		// set text-drawing flags
		nFlags=DT_SINGLELINE|
			   DT_LEFT|
			   DT_VCENTER|
			   DT_END_ELLIPSIS;

		// compute text rect
		if(!lpDC->DrawText(lpDisplayName,
						   -1,
						   &rcText,
						   nFlags|DT_CALCRECT))
		{
			DisplayNEErrorMessage("Unable to compute list control rectangle.");
			return;
		}

		// copy focus rect
		rcFocus.CopyRect(&rcText);

		// adjust focus rect
		rcFocus.InflateRect(2,0,6,1);
		
		// place rects
		rcIcon.OffsetRect(1,0);
		rcText.OffsetRect(20,0);
		rcFocus.OffsetRect(19,0);
	
		// clip right sides
		if(rcIcon.right>rcItem.right)
			rcIcon.right=rcItem.right;
		if(rcText.right>rcItem.right)
			rcText.right=rcItem.right;
		if(rcFocus.right>rcItem.right)
			rcFocus.right=rcItem.right;

		// get item state
		nItemState=GetItemState((int)lpLVCD->nmcd.dwItemSpec,
								LVIS_FOCUSED|
								LVIS_SELECTED);

		// draw icon
		lpIcons->Draw(lpDC,
					  nIconIdx,
					  CPoint(rcIcon.left,
							 rcIcon.top),
					  ILD_NORMAL);

		// draw 'shared' overlay
		if(bIsShared)
			g_lpOverlayIcons->Draw(lpDC,
								   0,
								   CPoint(rcIcon.left,
										  rcIcon.top),
								   ILD_TRANSPARENT|
								   ILD_NORMAL);

		// draw 'link' overlay
		if(bIsLink)
			g_lpOverlayIcons->Draw(lpDC,
								   1,
								   CPoint(rcIcon.left,
										  rcIcon.top),
								   ILD_TRANSPARENT|
								   ILD_NORMAL);

		// set background mode
		lpDC->SetBkMode(TRANSPARENT);
		
		// check selected state
		if(nItemState&LVIS_SELECTED)
		{
			// check window focus
			if(GetFocus()==this)
			{
				// draw highlighted background
				lpDC->FillSolidRect(&rcFocus,
									GetSysColor(COLOR_HIGHLIGHT));

				// set text color
				lpDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));

				// copy highlight color
				clrHilite=GetSysColor(COLOR_HIGHLIGHT);

				// highlight icon
				for(nX=0;nX<16;nX++)
					for(nY=0;nY<16;nY++)
						{
							// draw every other pixel	
							if(!((nX+nY)&1))
								lpDC->SetPixelV(rcIcon.left+nX,
											    rcIcon.top +nY,
											    clrHilite);
						}
			}
			else
			{
				// draw grayed background
				lpDC->FillSolidRect(&rcFocus,
									GetSysColor(COLOR_BTNFACE));
				
				// set text color
				lpDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));
			}
		}
		else
		{
			// draw window background
			lpDC->FillSolidRect(&rcFocus,
								GetSysColor(COLOR_WINDOW));

			// set text color
			lpDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
		}

		// draw text
		lpDC->DrawText(lpDisplayName,
					   -1,
					   &rcText,
					   nFlags);

		// check focus state
		if(nItemState&LVIS_FOCUSED)
		{
			// check window focus
			if(GetFocus()==this)
			{
				// draw focus
				lpDC->DrawFocusRect(&rcFocus);
			}
		}

		// restore state
		lpDC->RestoreDC(nState);
		
		// skip default processing
		(*pResult)=CDRF_SKIPDEFAULT;

		// ok
		break;
	}
}

// CHistoryComboBox::Link()

BOOL CHistoryComboBox::Link(CFileListCtrl* lpList)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpList)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CHistoryComboBox::Link()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpList->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CHistoryComboBox::Link()",
							FALSE);
		return(FALSE);
	}
#endif

	// exchange pointers
	lpFileList=lpList;
	lpFileList->lpHistoryCbx=this;

	// ok
	return(TRUE);
}

// CFileListCtrl::OnDestroy()

void CFileListCtrl::OnDestroy(void)
{
	// clear current audio
	SetCurrentAudio(NULL);

	// check image list
	if(lpSysImageList)
	{
		// detach image list
		if(lpSysImageList->Detach())
			RemoveWinResource

		// free image list
		FreeClassObject(lpSysImageList);
	}

	// call base method
	CListCtrl::OnDestroy();
}

// CDirTree::AddFoldersToFileList()

BOOL CDirTree::AddFoldersToFileList(CFileListCtrl* lpFileList)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpFileList)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CDirTree::AddFoldersToFileList()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpFileList->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CDirTree::AddFoldersToFileList()",
							FALSE);
		return(FALSE);
	}

	// compare image lists
	if(hIconImgs!=lpFileList->lpSysImageList->m_hImageList)
	{
		DisplayErrorMessage("Image list inconsistency!",
							"CDirTree::AddFoldersToFileList()",
							FALSE);
		return(FALSE);
	}
#endif

	// get index
	int nIndex=lpFileList->GetItemCount();

	// add folder
	if(lpFileList->InsertItem(nIndex,
							  lpDisplayName,
							  nIconIdx)==-1)
	{
		DisplayNEErrorMessage("Unable to add folder to file list.");
		return(FALSE);
	}

	// set item data
	if(!lpFileList->SetItemData(nIndex,
								(DWORD)&fld))
	{
		DisplayNEErrorMessage("Unable to set folder data.");
		return(FALSE);
	}

	// add siblings (if any)
	if(lpSibling)
		return(lpSibling->AddFoldersToFileList(lpFileList));
	else
		return(TRUE);
}

// CDirTree::AddFilesToFileList()

BOOL CDirTree::AddFilesToFileList(CFileListCtrl* lpFileList)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpFileList)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CDirTree::AddFilesToFileList()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpFileList->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CDirTree::AddFilesToFileList()",
							FALSE);
		return(FALSE);
	}

	// compare image lists
	if(hIconImgs!=lpFileList->lpSysImageList->m_hImageList)
	{
		DisplayErrorMessage("Image list inconsistency!",
							"CDirTree::AddFilesToFileList()",
							FALSE);
		return(FALSE);
	}
#endif
	
	// check for files
	if(lpFileInfo)
	{
		// add to list
		return(lpFileInfo->AddToFileList(lpFileList));
	}

	// ok
	return(TRUE);
}

// CFileInfo::AddToFileList()

BOOL CFileInfo::AddToFileList(CFileListCtrl* lpFileList)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpFileList)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CFileInfo::AddToFileList()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpFileList->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CFileInfo::AddToFileList()",
							FALSE);
		return(FALSE);
	}

	// compare image lists
	if(lpDisplayName)
		if(hIconImgs!=lpFileList->lpSysImageList->m_hImageList)
		{
			DisplayErrorMessage("Image list inconsistency!",
								"CFileInfo::AddToFileList()",
								FALSE);
			return(FALSE);
		}
#endif

	// get index
	int nIndex=lpFileList->GetItemCount();

	// set continue flag
	BOOL bCont=TRUE;

	// check name
	if(lpDisplayName)
	{
		// compare extension
		if(g_lpCurAudExtList)
			if(g_lpCurAudExtList->GetMatch(lpExtension)==-1)
				bCont=FALSE;

		// check for link-to-folder
		if(bIsLinkToFolder)
			bCont=TRUE;

		// check continue flag
		if(bCont)
		{
			// add item
			if(lpFileList->InsertItem(nIndex,
									  lpDisplayName,
									  nIconIdx)==-1)
			{
				DisplayNEErrorMessage("Unable to add file to file list.");
				return(FALSE);
			}

			// set file data
			if(!lpFileList->SetItemData(nIndex,
										(DWORD)&fld))
			{
				DisplayNEErrorMessage("Unable to set file data.");
				return(FALSE);
			}
		}
	}	
		
	// add next (if any)
	if(lpNext)
		return(lpNext->AddToFileList(lpFileList));
	else
		return(TRUE);
}

// CFileListCtrl::OnRtClick()

void CFileListCtrl::OnRtClick(NMHDR* pNMHDR,
						      LRESULT* pResult)
{
	// get pointer to notification header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// show popup menu (if visible)
	if(IsWindowVisible())
		ShowPopupMenu(nCtrlId);

	// check for selection
	g_bLastFileSelFlag=(QuerySelection() ? TRUE : FALSE);
}

// CFileListCtrl::OnClick()

void CFileListCtrl::OnClick(NMHDR* pNMHDR,
						    LRESULT* pResult)
{
	// get pointer to notification header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// check for selection
	if(QuerySelection())
	{
		// set flag
		g_bLastFileSelFlag=TRUE;
	}
	else
	{
		// check last selection
		if(g_bLastFileSelFlag)
		{
			// play sound (annoying!)
			//PlaySound(IDR_CLEARSELSND);

			// reset flag
			g_bLastFileSelFlag=FALSE;
		}
	}
}

// CFileListCtrl::QuerySelection()

BOOL CFileListCtrl::QuerySelection(void)
{
	// check for selection
	return(GetFirstSelectedItemPosition() ? TRUE : FALSE);
}

// CFileListCtrl::GetSelection()

int CFileListCtrl::GetSelection(void)
{
	// position value
	POSITION pos;

	// get first position
	pos=GetFirstSelectedItemPosition();

	// check position
	return(pos ? GetNextSelectedItem(pos) : -1);
}

// CFileListCtrl::SortFolder()

BOOL CFileListCtrl::SortFolder(BOOL bAsc)
{
	// sort list
	if(!SortItems(SortFileList,
				  (DWORD)bAsc))
	{
		DisplayErrorMessage("Unable to sort items in list.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// LoadOverlayIcons()

BOOL LoadOverlayIcons(void)
{
	// library instance
	HINSTANCE hInst=(HINSTANCE)INVALID_HANDLE_VALUE;

	// icons
	HICON hShareIcon=(HICON)INVALID_HANDLE_VALUE;
	HICON hLinkIcon =(HICON)INVALID_HANDLE_VALUE;

	// allocate image list
	AllocClassObject(g_lpOverlayIcons,
					 CImageList);
	
	// check new object
	if(!g_lpOverlayIcons)
		return(FALSE);

	// create image list
	if(!g_lpOverlayIcons->Create(16,16,
							     ILC_COLOR32|
							     ILC_MASK,
							     2,2))
	{
		DisplayErrorMessage("Unable to create overlay image list.");
		return(FALSE);
	}

	// load 'shell32.dll'
	hInst=LoadLibrary("shell32.dll");

	// check handle
	if(hInst==NULL||
	   hInst==(HINSTANCE)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Unable to open 'shell32.dll'.");
		return(FALSE);
	}
	else
		AddWinResource

	// load 'share' icon
	hShareIcon=(HICON)LoadImage(hInst,
								"#29",
								IMAGE_ICON,
								16,16,
								LR_SHARED);

	// check icon
	if(hShareIcon==NULL||
	   hShareIcon==(HICON)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Unable to load 'shared' icon overlay.");
		if(FreeLibrary(hInst))
			RemoveWinResource
		return(FALSE);
	}

	// load 'link' icon
	hLinkIcon=(HICON)LoadImage(hInst,
							   "#30",
							   IMAGE_ICON,
							   16,16,
							   LR_SHARED);

	// check icon
	if(hLinkIcon==NULL||
	   hLinkIcon==(HICON)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Unable to load 'link' icon overlay.");
		if(FreeLibrary(hInst))
			RemoveWinResource
		return(FALSE);
	}

	// close 'shell32.dll'
	if(FreeLibrary(hInst))
		RemoveWinResource

	// add icons
	if(g_lpOverlayIcons->Add(hShareIcon)==-1||
	   g_lpOverlayIcons->Add(hLinkIcon)==-1)
	{
		DisplayErrorMessage("Unable to add overlay icons to image list.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// ReleaseOverlayIcons()

void ReleaseOverlayIcons(void)
{
	// release image list
	FreeClassObject(g_lpOverlayIcons);
}

// SortFileList()

int CALLBACK SortFileList(LPARAM lParam1,
						  LPARAM lParam2,
						  LPARAM lParamSort)
{
	// pointers to file list data
	LPFILELISTDATA lpFLD1=NULL;
	LPFILELISTDATA lpFLD2=NULL;

	// pointers to file/folder info
	CDirTree*  lpDirTree =NULL;
	CFileInfo* lpFileInfo=NULL;

	// pointers to display names
	LPSTR lpDisplayName1=NULL;
	LPSTR lpDisplayName2=NULL;

	// cast sort parameter
	BOOL bSortAsc=(BOOL)lParamSort;

	// check sort parameter
	if(bSortAsc)
	{
		// cast pointers
		lpFLD1=(LPFILELISTDATA)lParam1;
		lpFLD2=(LPFILELISTDATA)lParam2;
	}
	else
	{
		// cast pointers (reversed)
		lpFLD1=(LPFILELISTDATA)lParam2;
		lpFLD2=(LPFILELISTDATA)lParam1;
	}

	// check file list data #1
	if(lpFLD1->bIsFolder)
	{
		// cast pointer to folder info
		lpDirTree=(CDirTree*)lpFLD1->lpData;

		// check for parent
		if(lpDirTree->lpParent)
		{
			// check no-sort children flag
			if(lpDirTree->lpParent->bNoSortChildren)
			{
				// no change
				return(0);
			}
		}

		// copy pointer to display name
		lpDisplayName1=lpDirTree->lpDisplayName;
	}
	else
	{
		// cast pointer to file info
		lpFileInfo=(CFileInfo*)lpFLD1->lpData;

		// check for parent
		if(lpFileInfo->lpParent)
		{
			// check no-sort children flag
			if(lpFileInfo->lpParent->bNoSortChildren)
			{
				// no change
				return(0);
			}
		}

		// copy pointer to display name
		lpDisplayName1=lpFileInfo->lpDisplayName;
	}

	// check file list data #2
	if(lpFLD2->bIsFolder)
	{
		// cast pointer to folder info
		lpDirTree=(CDirTree*)lpFLD2->lpData;

		// check for parent
		if(lpDirTree->lpParent)
		{
			// check no-sort children flag
			if(lpDirTree->lpParent->bNoSortChildren)
			{
				// no change
				return(0);
			}
		}

		// copy pointer to display name
		lpDisplayName2=lpDirTree->lpDisplayName;
	}
	else
	{
		// cast pointer to file info
		lpFileInfo=(CFileInfo*)lpFLD2->lpData;

		// check for parent
		if(lpFileInfo->lpParent)
		{
			// check no-sort children flag
			if(lpFileInfo->lpParent->bNoSortChildren)
			{
				// no change
				return(0);
			}
		}		

		// copy pointer to display name
		lpDisplayName2=lpFileInfo->lpDisplayName;
	}

	// check folder flag #1
	if(lpFLD1->bIsFolder||
	   lpFLD1->bIsLinkToFolder)
	{
		// check folder flag #2
		if(lpFLD2->bIsFolder||
		   lpFLD2->bIsLinkToFolder)
		{
			// compare folders
			return(stricmp(lpDisplayName1,
						   lpDisplayName2));
		}
		else
		{
			// #1 takes precedence
			return(-1);
		}
	}
	else
	{
		// check folder flag #2
		if(lpFLD2->bIsFolder||
		   lpFLD2->bIsLinkToFolder)
		{
			// #2 takes precedence
			return(1);
		}
		else
		{
			// compare files
			return(stricmp(lpDisplayName1,
						   lpDisplayName2));
		}
	}
}

// CDirTree::SetNoSortChildren()

void CDirTree::SetNoSortChildren(BOOL bFlag)
{
	// copy flag
	bNoSortChildren=bFlag;
}

// CFileListCtrl::ShowFolder()

BOOL CFileListCtrl::ShowFolder(CDirTree* lpDirTree,
							   BOOL bSaveInHist)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpDirTree)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CFileListCtrl::ShowFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// client rect
	CRect rClient;

	// begin wait cursor
	::BeginWaitCursor();

	// check for image list
	if(!lpSysImageList)
	{
		// create image list
		AllocClassObject(lpSysImageList,
						 CImageList);

		// check new object
		if(!lpSysImageList)
		{
			::EndWaitCursor();
			return(FALSE);
		}

		// attach image list
		if(!lpSysImageList->Attach(lpDirTree->hIconImgs))
		{
			DisplayNEErrorMessage("Unable to attach system image list to file list.");
			::EndWaitCursor();
			return(FALSE);
		}
		else
			AddWinResource

		// set image list
		SetImageList(lpSysImageList,
					 LVSIL_SMALL);
	}

	// set filling flag
	bIsFilling=TRUE;

	// clear list
	DeleteAllItems();

	// clear current audio
	SetCurrentAudio(NULL);

	// clear selection in playlist
	if(g_lpAudioPList->QuerySelection())
	{
		// clear selection
		g_lpAudioPList->SetItemState(g_lpAudioPList->GetSelection(),
									 NULL,
									 LVIS_SELECTED);
	}

	// redraw window
	RedrawWindow();

	// relay to history box
	lpHistoryCbx->ShowFolder(lpDirTree,
							 bSaveInHist);

	// check for child
	if(lpDirTree->lpChild)
	{
		// add subfolders
		lpDirTree->lpChild->AddFoldersToFileList(this);
	}

	// add files
	lpDirTree->AddFilesToFileList(this);

	// sort folder
	SortFolder();

	// get list rect
	GetClientRect(&rClient);

	// set list width
	SetColumnWidth(0,
				   (rClient.Width()/2));

	// reset filling flag
	bIsFilling=FALSE;

	// redraw window
	RedrawWindow();

	// end wait cursor
	::EndWaitCursor();

	// ok
	return(TRUE);
}

// CDirTree::ClearDisplayFlags()

void CDirTree::ClearDisplayFlags(void)
{
	// clear flag
	bDisplay=FALSE;

	// pass it on
	if(lpChild)   lpChild->ClearDisplayFlags();
	if(lpSibling) lpSibling->ClearDisplayFlags();
}

// CDirTree::SetDisplayFlags()

void CDirTree::SetDisplayFlags(void)
{
	// set flag
	bDisplay=TRUE;

	// pass it back
	if(lpParent)
		lpParent->SetDisplayFlags();
}

// CHistoryComboBox::ShowFolder()

BOOL CHistoryComboBox::ShowFolder(CDirTree* lpDirNode,
								  BOOL bSaveInHist)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpDirNode)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CHistoryComboBox::ShowFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// clear display flags (entire tree)
	lpDirTree->ClearDisplayFlags();

	// set display flags (selected node)
	lpDirNode->SetDisplayFlags();

	// expand node
	lpDirNode->ExpandNode();

	// set no-draw flag
	bNoDraw=TRUE;

	// reset combo box
	ResetContent();

	// clear current audio
	SetCurrentAudio(NULL);

	// add items to list
	lpDirTree->AddToComboBox(this);

	// select folder
	SelectFolder(lpDirNode);

	// clear no-draw flag
	bNoDraw=FALSE;

	// redraw window
	RedrawWindow();

	// check history flag
	if(bSaveInHist)
	{
		// add to history
		if(lpHistCur->AddNode(lpDirNode))
		{
			// set new current
			lpHistCur=lpHistCur->lpNext;
		}

		// set parent modified
		if(lpParentDlg)
			lpParentDlg->SetModified();
	}

	// disable back button
	g_lpFileBackBtn->Disable();

	// check for previous
	if(lpHistCur)
		if(lpHistCur->lpPrev)
			if(lpHistCur->lpPrev->lpSavedTree)
			{
				// enable back button
				g_lpFileBackBtn->Enable();
			}
	
	// check for root
	if(!lpDirNode->bIsNSRoot)
		g_lpFileUpBtn->Enable();
	else
		g_lpFileUpBtn->Disable();

	// ok
	return(TRUE);
}

// CHistoryComboBox::OnCommand()

BOOL CHistoryComboBox::OnCommand(WPARAM wParam,
								 LPARAM lParam)
{
	// check message
	switch(HIWORD(wParam))
	{
	// combo box selection
	case(CBN_SELCHANGE):

		// hide list
		ShowDropDown(FALSE);

		// display folder
		lpFileList->ShowFolder();

		// play sound
		PlaySound(IDR_NEWSELSND);

		// ok
		break;
	}

	// call base method
	return(CExtComboBox::OnCommand(wParam,
								   lParam));
}

// CHistoryComboBox::SelectFolder()

BOOL CHistoryComboBox::SelectFolder(CDirTree* lpDirNode)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpDirNode)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CHistoryComboBox::SelectFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// counter
	int nCount;

	// get item count
	int nNumItems=GetCount();

	// check item count
	if(nNumItems)
	{
		// check each item
		for(nCount=0;nCount<nNumItems;nCount++)
		{
			// compare pointers
			if((CDirTree*)GetItemData(nCount)==lpDirNode)
			{
				// set current selection
				SetCurSel(nCount);

				// ok
				return(TRUE);
			}
		}
	}

	// not found
	return(FALSE);
}

// CreateNavigationImages()

BOOL CreateNavigationImages(void)
{
	// load back bitmap
	if(!LoadBitmap(&g_lpNavBackBmp,
				   IDB_BACKBTN))
		return(FALSE);

	// replace transparent color
	if(!ReplaceBmpColor(g_lpNavBackBmp,
						GetSysColor(COLOR_BTNFACE),
						RGB(255,0,255)))
		return(FALSE);

	// load back bitmap (grayed)
	if(!LoadBitmap(&g_lpNavBackBmpGr,
				   IDB_DIMBACKBTN))
		return(FALSE);

	// replace transparent color
	if(!ReplaceBmpColor(g_lpNavBackBmpGr,
						GetSysColor(COLOR_BTNFACE),
						RGB(255,0,255)))
		return(FALSE);

	// load up bitmap
	if(!LoadBitmap(&g_lpNavUpBmp,
				   IDB_UPBTN))
		return(FALSE);

	// replace transparent color
	if(!ReplaceBmpColor(g_lpNavUpBmp,
						GetSysColor(COLOR_BTNFACE),
						RGB(255,0,255)))
		return(FALSE);

	// load up bitmap (grayed)
	if(!LoadBitmap(&g_lpNavUpBmpGr,
				   IDB_DIMUPBTN))
		return(FALSE);

	// replace transparent color
	if(!ReplaceBmpColor(g_lpNavUpBmpGr,
						GetSysColor(COLOR_BTNFACE),
						RGB(255,0,255)))
		return(FALSE);

	// ok
	return(TRUE);
}

// CFolderHistory::CFolderHistory()

CFolderHistory::CFolderHistory()
{
	// reset pointers
	lpPrev     =NULL;
	lpNext     =NULL;
	lpSavedTree=NULL;
}

// CFolderHistory::AddNode()

BOOL CFolderHistory::AddNode(CDirTree* lpDirTree)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpDirTree)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CFolderHistory::AddNode()",
							FALSE);
		return(FALSE);
	}
#endif

	// delete any descendants
	if(lpNext)
		lpNext->DeleteNode();
	else
	{
		// allocate next object
		AllocClassObject(lpNext,
						 CFolderHistory);

		// check new object
		if(!lpNext)
			return(FALSE);
	}

	// copy dir tree
	lpNext->lpSavedTree=lpDirTree;

	// set parent
	lpNext->lpPrev=this;

	// ok
	return(TRUE);
}

// CFolderHistory::DeleteNode()

void CFolderHistory::DeleteNode(void)
{
	// delete any descendants
	if(lpNext)
		lpNext->DeleteNode();

	// release next item
	FreeClassObject(lpNext);

	// reset folder
	lpSavedTree=NULL;
}

// CHistoryComboBox::OnDestroy()

void CHistoryComboBox::OnDestroy(void)
{
	// clear current audio
	SetCurrentAudio(NULL);

	// check folder history
	if(lpHistRoot)
	{
		// delete folder history
		lpHistRoot->DeleteNode();

		// release folder history
		FreeClassObject(lpHistRoot);
	}

	// call base method
	CExtComboBox::OnDestroy();
}

// CHistoryComboBox::FolderBack()

BOOL CHistoryComboBox::FolderBack(void)
{
	// previous folder
	CDirTree* lpPrevTree;

	// check for previous node
	if(!lpHistCur->lpPrev->lpSavedTree)
		return(FALSE);

	// move pointer back
	lpHistCur=lpHistCur->lpPrev;

	// copy previous folder
	lpPrevTree=lpHistCur->lpSavedTree;

	// show previous folder
	if(!lpFileList->ShowFolder(lpPrevTree,
							   FALSE))
		return(FALSE);

	// play sound
	PlaySound(IDR_NEWSELSND);

	// set parent modified
	if(lpParentDlg)
		lpParentDlg->SetModified();

	// ok
	return(TRUE);
}

// CHistoryComboBox::FolderUp()

BOOL CHistoryComboBox::FolderUp(void)
{
	// check current folder
	if(lpHistCur->lpSavedTree)
	{
		// check for parent
		if(lpHistCur->lpSavedTree->lpParent)
		{
			// play sound
			PlaySound(IDR_NEWSELSND);

			// show folder
			return(lpFileList->ShowFolder(lpHistCur->lpSavedTree->lpParent));
		}
	}

	// no good
	return(FALSE);
}

// CDirTree::ExpandNode()

BOOL CDirTree::ExpandNode(BOOL bIsMyComputer,
						  BOOL bUseDriveFlag,
						  BOOL bDriveFlag)
{
#ifdef DEBUG_MODE
	// check shell folder
	if(!lpShellFolder)
	{
		DisplayErrorMessage("Shell folder does not exist.",
							"CDirTree::ExpandNode()",
							FALSE);
		return(FALSE);
	}
#endif

	// enumeration list interface
	IEnumIDList* lpEnumIDList=NULL;

	// item id list (temporary)
	LPITEMIDLIST lpTempIDList=NULL;

	// function result
	HRESULT hr;

	// new folder interface
	IShellFolder* lpNewFolder=NULL;

	// file attributes
	ULONG lAttr;
	ULONG lAttrReq;
	ULONG lAttrExc;

	// file description
	SHDESCRIPTIONID shdid;

	// continue flag
	BOOL bCont;

	// drive flag
	BOOL bIsDrive;

	// check flag
	if(bExpanded)
		return(TRUE);

	// check 'My Computer' flag
	if(bIsMyComputer)
	{
		// check flag
		if(!bUseDriveFlag)
		{
			// expand drives
			if(!ExpandNode(TRUE,
						   TRUE,
						   TRUE))
				return(FALSE);

			// expand non-drives
			if(!ExpandNode(TRUE,
						   TRUE,
						   FALSE))
				return(FALSE);

			// set expanded flag
			bExpanded=TRUE;

			// ok
			return(TRUE);
		}
	}

	// get enumeration list
	if(FAILED(lpShellFolder->EnumObjects(hParent,
										 SHCONTF_FOLDERS,
										 &lpEnumIDList)))
	{
		// windows will provide suitable message
		return(FALSE);
	}
	else
		AddCOMResource

	// set required attributes
	lAttrReq=SFGAO_FILESYSTEM;

	// set excluded attributes
	lAttrExc=SFGAO_REMOVABLE;

	// add subfolders
	while(TRUE)
	{
		// get next item
		hr=lpEnumIDList->Next(1,
							  &lpTempIDList,
							  NULL);

		// check for last item
		if(hr==S_FALSE)
			break;

		// check for error
		if(FAILED(hr))
		{
			// alert user
			DisplayNEErrorMessage("Unable to read subfolder.");

			// stop here
			break;
		}
		else
			AddMemResource

		// reset continue flag
		bCont=TRUE;

		// check use-drive flag
		if(bUseDriveFlag)
		{
			// get description
			if(FAILED(SHGetDataFromIDList(lpShellFolder,
										  lpTempIDList,
										  SHGDFIL_DESCRIPTIONID,
										  &shdid,
										  sizeof(shdid))))
			{
				// sorting purposes only; not essential to operation
				// therefore, continue on drive flag & skip otherwise
				if(!bDriveFlag)
				{
					// free id list
					g_lpCoMalloc->Free(lpTempIDList);
						RemoveMemResource
					
					// clear continue flag
					bCont=FALSE;
				}
			}
			else
			{
				// check for drive
				if(shdid.dwDescriptionId==SHDID_COMPUTER_DRIVE35||
				   shdid.dwDescriptionId==SHDID_COMPUTER_DRIVE525||
				   shdid.dwDescriptionId==SHDID_COMPUTER_REMOVABLE||
				   shdid.dwDescriptionId==SHDID_COMPUTER_FIXED||
				   shdid.dwDescriptionId==SHDID_COMPUTER_NETDRIVE||
				   shdid.dwDescriptionId==SHDID_COMPUTER_CDROM||
				   shdid.dwDescriptionId==SHDID_COMPUTER_RAMDISK||
				   shdid.dwDescriptionId==SHDID_COMPUTER_OTHER)
					bIsDrive=TRUE;
				else
					bIsDrive=FALSE;

				// check flags
				if((bDriveFlag&&!bIsDrive)||
				   (!bDriveFlag&&bIsDrive))
				{
					// free id list
					g_lpCoMalloc->Free(lpTempIDList);
					RemoveMemResource
					
					// clear continue flag
					bCont=FALSE;
				}
			}
		}

		// check continue flag
		if(bCont)
		{
			// reset file attributes
			lAttr=lAttrReq|
				  lAttrExc;

			// get file attributes
			if(FAILED(lpShellFolder->GetAttributesOf(1,
													 (LPCITEMIDLIST*)&lpTempIDList,
													 &lAttr)))
			{
				DisplayNEErrorMessage("Unable to read subfolder attributes.");
				g_lpCoMalloc->Free(lpTempIDList);
				RemoveMemResource
			}
			else
			{
				// check file attributes
				if(!(lAttr&lAttrReq)||
					(lAttr&lAttrExc))
				{
					// free id list
					g_lpCoMalloc->Free(lpTempIDList);

					RemoveMemResource
				}
				else
				{
					// get folder interface
					if(FAILED(lpShellFolder->BindToObject(lpTempIDList,
														  NULL,
														  IID_IShellFolder,
														  (LPVOID*)&lpNewFolder)))
					{
						DisplayNEErrorMessage("Unable to get subfolder interface.");
						g_lpCoMalloc->Free(lpTempIDList);
						RemoveMemResource
					}
					else
					{
						AddCOMResource

						// check 'My Computer' flag
						if(bIsMyComputer)
						{
							// release list (not useful)
							g_lpCoMalloc->Free(lpTempIDList);

							RemoveMemResource

							// reset pointer
							lpTempIDList=NULL;
						}

						// add child
						if(!AddChild(this,
									 lpNewFolder,
									 nIndentLevel+1,
									 lpTempIDList))
						{
							// free id list
							g_lpCoMalloc->Free(lpTempIDList);

							RemoveMemResource
						}
					}
				}
			}
		}
	}

	// release enumeration list
	ReleaseCOMPtr(lpEnumIDList);

	// check for 'My Computer'
	if(bIsMyComputer)
	{
		// set no-sort children
		SetNoSortChildren();
	}
	else
	{
		// get files
		if(!ExtractFiles())
			return(FALSE);

		// set flag
		bExpanded=TRUE;
	}

	// ok
	return(TRUE);
}

// CDirTree::ExtractFiles()

BOOL CDirTree::ExtractFiles(void)
{
#ifdef DEBUG_MODE
	// check shell folder
	if(!lpShellFolder)
	{
		DisplayErrorMessage("Shell folder does not exist.",
							"CDirTree::ExtractFiles()",
							FALSE);
		return(FALSE);
	}
#endif

	// enumeration list interface
	IEnumIDList* lpEnumIDList=NULL;

	// item id list (temporary)
	LPITEMIDLIST lpTempIDList=NULL;

	// function result
	HRESULT hr;

	// new folder interface
	IShellFolder* lpNewFolder=NULL;

	// file attributes
	ULONG lAttr;
	ULONG lAttrReq;
	ULONG lAttrExc;

	// current file info (optimization)
	CFileInfo* lpCurFileInfo=NULL;

	// release file info (just in case)
	FreeClassObject(lpFileInfo);

	// allocate file info
	AllocClassObject(lpFileInfo,
					 CFileInfo);

	// check new object
	if(!lpFileInfo)
		return(FALSE);

	// copy pointer
	lpCurFileInfo=lpFileInfo;

	// get enumeration list
	if(FAILED(lpShellFolder->EnumObjects(hParent,
										 SHCONTF_NONFOLDERS,
										 &lpEnumIDList)))
	{
		DisplayNEErrorMessage("Unable to extract files from folder.");
		return(FALSE);
	}
	else
		AddCOMResource

	// set required attributes
	lAttrReq=SFGAO_FILESYSTEM;

	// set excluded attributes
	lAttrExc=SFGAO_REMOVABLE;

	// add all files
	while(TRUE)
	{
		// get next item
		hr=lpEnumIDList->Next(1,
							  &lpTempIDList,
							  NULL);

		// check for last item
		if(hr==S_FALSE)
			break;

		// check for error
		if(FAILED(hr))
		{
			// alert user
			DisplayNEErrorMessage("Unable to read files from folder.");

			// stop here
			break;
		}
		else
			AddMemResource

		// reset file attributes
		lAttr=lAttrReq|
			  lAttrExc;

		// get file attributes
		if(FAILED(lpShellFolder->GetAttributesOf(1,
												 (LPCITEMIDLIST*)&lpTempIDList,
												 &lAttr)))
		{
			DisplayNEErrorMessage("Unable to read file attributes.");
			g_lpCoMalloc->Free(lpTempIDList);
			RemoveMemResource
		}
		else
		{
			// check file attributes
			if(!(lAttr&lAttrReq)||
				(lAttr&lAttrExc))
			{
				// release id list
				g_lpCoMalloc->Free(lpTempIDList);

				RemoveMemResource
			}
			else
			{
				// add file
				if(!lpCurFileInfo->Add(this,
									   lpTempIDList))
				{
					// release id list
					g_lpCoMalloc->Free(lpTempIDList);

					RemoveMemResource
				}
				else
				{
					// set to next item
					lpCurFileInfo=lpCurFileInfo->lpNext;
				}
			}
		}
	}

	// release enumeration list
	ReleaseCOMPtr(lpEnumIDList);

	// ok
	return(TRUE);
}

// CHistoryComboBox::OnKeyDown()

void CHistoryComboBox::OnKeyDown(UINT nChar,
								 UINT nRepCnt,
								 UINT nFlags)
{
	// check key
	switch(nChar)
	{
	// backspace
	case(VK_BACK):

		// move back
		FolderBack();

		// ok
		return;
	}	

	// call base method
	CExtComboBox::OnKeyDown(nChar,
							nRepCnt,
							nFlags);
}

// CFileListCtrl::OnKeyDown()

void CFileListCtrl::OnKeyDown(UINT nChar,
							  UINT nRepCnt,
							  UINT nFlags)
{
	// check key
	switch(nChar)
	{
	// backspace
	case(VK_BACK):

		// move back
		lpHistoryCbx->FolderBack();

		// ok
		return;
	}	

	// call base method
	CListCtrl::OnKeyDown(nChar,
						 nRepCnt,
						 nFlags);
}

// CFileListCtrl::PreTranslateMessage()

BOOL CFileListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// check for key-down
	if(pMsg->message==WM_KEYDOWN)
	{
		// check key
		switch((int)pMsg->wParam)
		{
		// return
		case(VK_RETURN):

			// relay double-click
			OnDblClick(NULL,
					   NULL);

			// stop here
			return(TRUE);

		// escape
		case(VK_ESCAPE):

			// clear selection
			ClearSelection();

			// stop here
			return(TRUE);
		}
	}

	// call base method
	return(CListCtrl::PreTranslateMessage(pMsg));
}

// CFileListCtrl::OnItemChanged()

void CFileListCtrl::OnItemChanged(NMHDR* pNMHDR,
							      LRESULT* pResult)
{
	// get pointer to item change header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// playlist item data
	LPPLAYLISTDATA lpPD;

	// selection
	int nSel;

	// equal items flag
	BOOL bItemsAreEqual=FALSE;

	// check audio playlist
	if(g_lpAudioPList)
	{
		// check window
		if(IsWindow(g_lpAudioPList->m_hWnd))
		{
			// check selection
			if(g_lpAudioPList->QuerySelection())
			{
				// get selection
				nSel=g_lpAudioPList->GetSelection();

				// get playlist data
				if(g_lpAudioPList->GetPlaylistItemData(nSel,
													   &lpPD))
				{
					// compare item data
					if(PlaylistDataMatchesAudioItemData(lpPD->lpUserData,
														(LPVOID)GetItemData(lpLV->iItem)))
						bItemsAreEqual=TRUE;
					else
						bItemsAreEqual=FALSE;
				}
			}
		}
	}

	// new selection
	if(lpLV->uNewState&LVIS_SELECTED&&
	   !(lpLV->uOldState&LVIS_SELECTED))
	{
		// check equal flag
		if(!bItemsAreEqual)
		{
			// clear playlist selection
			g_lpAudioPList->SetItemState(nSel,
										 NULL,
										 LVIS_SELECTED);
		}
		else
		{
			// enable buttons
			g_lpClearAudioSelBtn->Enable();
			g_lpAddAudioFileBtn->Enable();
		}

		// play sound
		PlaySound(IDR_NEWSELSND);

		// save as current
		SetCurrentAudio((LPFILELISTDATA)GetItemData(lpLV->iItem));
	}
	
	// cleared selection
	if(!(lpLV->uNewState&LVIS_SELECTED)&&
	   lpLV->uOldState&LVIS_SELECTED)
	{
		// check equal flag
		if(bItemsAreEqual)
		{
			// clear playlist selection
			g_lpAudioPList->SetItemState(nSel,
										 NULL,
										 LVIS_SELECTED);
		}

		// clear current audio
		SetCurrentAudio(NULL);
	}

	// set return value
	(*pResult)=NULL;
}

// CFileListCtrl::OnDblClick()

void CFileListCtrl::OnDblClick(NMHDR* pNMHDR,
							   LRESULT* pResult)
{
	// get pointer to notification header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// folder info
	CDirTree* lpDirTree;

	// check for current item
	if(!g_lpCurAudioFLD)
		return;

	// begin wait
	::BeginWaitCursor(g_lpCurMusicMgrDlg);

	// check for active timeout
	if(g_nCurAudioTimerID)
	{
		// wait for it
		Sleep(AUDIO_TIMEOUT_WAIT);

		// process now
		CurAudioTimerProc(NULL,
						  NULL,
						  NULL,
						  NULL);
	}

	// check folder flag
	if(g_lpCurAudioFLD->bIsFolder)
	{
		// cast pointer to folder info
		lpDirTree=(CDirTree*)g_lpCurAudioFLD->lpData;

		// show folder
		ShowFolder(lpDirTree);
	}
	else
	{
		// check for link to folder
		if(g_lpCurAudioFLD->bIsLinkToFolder)
		{
			// show folder
			ShowLinkedFolder((CFileInfo*)g_lpCurAudioFLD->lpData);
		}
		else
		{
			// check for loaded file
			if(g_nCurAudioDevID==0)
			{
				// reload audio
				SetCurrentAudio(CURAUDIO_RELOAD);
			}

			// click stop button
			g_lpCurMusicMgrDlg->OnStopBtnClk();

			// click play button
			g_lpCurMusicMgrDlg->OnPlayBtnClk();
		}
	}

	// end wait
	::EndWaitCursor(g_lpCurMusicMgrDlg);
}

// CFileListCtrl::ClearSelection()

void CFileListCtrl::ClearSelection(void)
{
	// check selection
	if(QuerySelection())
	{
		// clear selection
		if(!SetItemState(GetSelection(),
						 NULL,
						 LVIS_SELECTED))
			DisplayErrorMessage("Unable to clear selection.");

		// clear audio file
		SetCurrentAudio(NULL);

		// play sound
		PlaySound(IDR_CLEARSELSND);
	}
}

// CFileListCtrl::ShowSelFolder()

BOOL CFileListCtrl::ShowSelFolder(BOOL bSaveInHist)
{
	// pointer to file data
	LPFILELISTDATA lpFLD=NULL;

	// check for seleciton
	if(!QuerySelection())
		return(FALSE);

	// cast pointer to file data
	lpFLD=(LPFILELISTDATA)GetItemData(GetSelection());

	// check pointer
	if(!lpFLD)
		return(FALSE);

	// check for folder
	if(lpFLD->bIsFolder)
	{
		// show folder
		return(ShowFolder((CDirTree*)lpFLD->lpData,
						  bSaveInHist));
	}
	else
	{
		// check for link
		if(lpFLD->bIsLinkToFolder)
		{
			// show linked folder
			return(ShowLinkedFolder((CFileInfo*)lpFLD->lpData,
									bSaveInHist));
		}
	}

	// no good
	return(FALSE);
}

// CFileListCtrl::ShowLinkedFolder()

BOOL CFileListCtrl::ShowLinkedFolder(CFileInfo* lpFileInfo,
									 BOOL bSaveInHist)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpFileInfo)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CFileListCtrl::ShowLinkedFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// set return value
	BOOL bRet=FALSE;

	LockGlobalMsg()

	// get path to link
	if(lpFileInfo->GetPath(g_lpMsg))
	{
		LockGlobalLongMsg()

		// resolve link
		if(FAILED(ResolveShortcut(g_lpMsg,g_lpLongMsg)))
		{
			UnlockGlobalMsg()
			UnlockGlobalLongMsg()

			// alert user
			DisplayErrorMessage("Unable to resolve shortcut.");
		}
		else
		{
			UnlockGlobalMsg()
			LockGlobalErrorMsg()

			// copy to error message
			strcpy(g_lpErrorMsg,
				   g_lpLongMsg);

			UnlockGlobalLongMsg()

			// show folder
			ShowFolder(g_lpErrorMsg,
					   bSaveInHist);

			UnlockGlobalErrorMsg()

			// set return value
			bRet=TRUE;
		}
	}
	else
		UnlockGlobalMsg()

	// ok
	return(bRet);
}

// CFileListCtrl::ShowFolder()

BOOL CFileListCtrl::ShowFolder(LPSTR lpPath,
							   BOOL bSaveInHist)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"CFileListCtrl::ShowFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// begin wait cursor
	::BeginWaitCursor();

	// locate folder
	CDirTree* lpDirTree=lpHistoryCbx->lpMyComputer->LocateFolder(lpPath);

	// end wait cursor
	::EndWaitCursor();

	// check result
	if(!lpDirTree)
	{
		DisplayErrorMessage("Unable to open shortcut.",
							"The folder may have been moved or deleted, or it may be\n located on a removable device (floppy drive, CD-ROM, etc.).",
							FALSE);
		return(FALSE);
	}

	// show folder
	if(!ShowFolder(lpDirTree,
				   bSaveInHist))
		return(FALSE);

	// ok
	return(TRUE);
}

// CDirTree::LocateFolder()

CDirTree* CDirTree::LocateFolder(LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"CDirTree::LocateFolder()",
							FALSE);
		return(NULL);
	}
#endif

	// flag
	BOOL bPass;
	
	// return value
	CDirTree* lpDirTree=NULL;

	LockGlobalLongTTMsg()

	// clear message
	g_lpLongTTMsg[0]=0;
	
	// get folder path (cheat)
	SHGetPathFromIDList(lpItemIDList,
						g_lpLongTTMsg);

	// set flag
	bPass=TRUE;

	// check for string
	if(strlen(g_lpLongTTMsg)>0)
	{
		// compare strings
		if(stricmp(g_lpLongTTMsg,
				   lpPath)==0)
		{
			UnlockGlobalLongTTMsg()

			// success!
			return(this);
		}

		LockGlobalTTMsg()
		
		// copy path (cheat)
		strcpy(g_lpTTMsg,
			   lpPath);

		// clip to length of test path
		g_lpTTMsg[strlen(g_lpLongTTMsg)]=0;

		// compare new strings
		if(stricmp(g_lpLongTTMsg,
				   g_lpTTMsg)!=0)
		{
			// clear flag
			bPass=FALSE;
		}

		UnlockGlobalTTMsg()
	}

	UnlockGlobalLongTTMsg()

	// check flag
	if(bPass)
	{
		// expand folder
		ExpandNode();

		// check children
		if(lpChild)
		{
			// search children
			lpDirTree=lpChild->LocateFolder(lpPath);

			// check result
			if(lpDirTree)
				return(lpDirTree);
		}
	}

	// check siblings
	if(lpSibling)
	{
		// search siblings
		lpDirTree=lpSibling->LocateFolder(lpPath);

		// check result
		if(lpDirTree)
			return(lpDirTree);
	}

	// not found
	return(NULL);
}

// CHistoryComboBox::PreSubclassWindow()

void CHistoryComboBox::PreSubclassWindow(void)
{
	// call base function
	CComboBox::PreSubclassWindow();

	// enable tooltips
	EnableToolTips(TRUE);
}

// CHistoryComboBox::OnToolHitTest()

int CHistoryComboBox::OnToolHitTest(CPoint point,
									TOOLINFO* pTI) const
{
	// check fit flag
	if(bTextFit)
	{
		// no tooltip
		return(-1);
	}

	// just to verify
	LockGlobalTTMsg()
	UnlockGlobalTTMsg()
	LockGlobalLongTTMsg()
	UnlockGlobalLongTTMsg()

	// set tooltip info
	pTI->hwnd=m_hWnd;
	pTI->uId=(UINT)GetCurSel()+1;
	pTI->lpszText=LPSTR_TEXTCALLBACK;
	pTI->rect=rCurBounds;

	// return id
	return(pTI->uId);
}

// CHistoryComboBox::OnTTNeedText()

BOOL CHistoryComboBox::OnTTNeedText(UINT nID,
									NMHDR* pNMHDR,
									LRESULT* pResult)
{
	// cast pointers to tooltip info
	LPTOOLTIPTEXTA lpTTTa=(LPTOOLTIPTEXTA)pNMHDR;
	LPTOOLTIPTEXTW lpTTTw=(LPTOOLTIPTEXTW)pNMHDR;
	
	// folder info
	CDirTree* lpFolder=NULL;

	// get actual id
	nID=pNMHDR->idFrom;

	// check for winnt auto tooltip
	if(nID==0)
		return(FALSE);

	// get folder info
	lpFolder=(CDirTree*)GetItemData(nID-1);

	// check folder info
	if(!lpFolder)
		return(FALSE);

	// copy display name
	strcpy(g_lpTTMsg,
		   lpFolder->lpDisplayName);

#ifndef _UNICODE
	// check notification code
	if(pNMHDR->code==TTN_NEEDTEXTA)
	{
		// copy text
		lstrcpyn(g_lpLongTTMsg,g_lpTTMsg,LONG_MSG_SIZE-1);

		// set text
		lpTTTa->lpszText=g_lpLongTTMsg;

		// clear instance
		lpTTTa->hinst=NULL;
	}
	else
	{
		// convert text
		_mbstowcsz((LPWSTR)g_lpLongTTMsg,g_lpTTMsg,_MAX_PATH-1);

		// set text
		lpTTTw->lpszText=(LPWSTR)g_lpLongTTMsg;

		// clear instance
		lpTTTw->hinst=NULL;
	}
#else
	// check notification code
	if(pNMHDR->code==TTN_NEEDTEXTA)
	{
		// convert text
		_wcstombsz(g_lpLongTTMsg,(LPWSTR)g_lpTTMsg,_MAX_PATH-1);

		// set text
		lpTTTa->lpszText=g_lpLongTTMsg;

		// clear instance
		lpTTTa->hinst=NULL;
	}
	else
	{
		// copy text
		lstrcpyn(g_lpLongTTMsg,g_lpTTMsg,LONG_MSG_SIZE-1);

		// set text
		lpTTTw->lpszText=(LPWSTR)g_lpLongTTMsg;

		// clear instance
		lpTTTw->hinst=NULL;
	}
#endif

	// ok
	return(TRUE);
}

// CFileListCtrl::PreSubclassWindow()

void CFileListCtrl::PreSubclassWindow(void)
{
	// call base function
	CListCtrl::PreSubclassWindow();

	// enable tooltips
	EnableToolTips(TRUE);
}

// CFileListCtrl::OnToolHitTest()

int CFileListCtrl::OnToolHitTest(CPoint point,
								 TOOLINFO* pTI) const
{
	// item number
	int nItem;

	// bounding rect
	CRect rRect;

	// check for item intersect
	nItem=CellRectFromPoint(point,
							&rRect);

	// check item number	
	if(nItem==-1) 
		return(-1);

	// just to verify
	LockGlobalTTMsg()
	UnlockGlobalTTMsg()
	LockGlobalLongTTMsg()
	UnlockGlobalLongTTMsg()

	// set tooltip info
	pTI->hwnd=m_hWnd;
	pTI->uId=(UINT)(nItem+1);
	pTI->lpszText=LPSTR_TEXTCALLBACK;
	pTI->rect=rRect;

	// return id
	return(pTI->uId);
}

// CFileListCtrl::CellRectFromPoint()

int CFileListCtrl::CellRectFromPoint(CPoint point,
									 LPRECT lprCell) const
{
	// item counters
	int nNumItems;
	int nItem;

	// bounding rect
	CRect rRect;

	// client rect
	CRect rClient;

	// string width
	int nStringWidth;

	// rect width
	int nRectWidth;

	// fit flag
	BOOL bFit;

	// get item count
	nNumItems=GetItemCount();

	// check for items
	if(nNumItems)
	{
		// check each item
		for(nItem=0;nItem<nNumItems;nItem++)
		{
			// reset fit flag
			bFit=FALSE;

			// get bounding rect
			if(!GetItemRect(nItem,
							&rRect,
							LVIR_BOUNDS))
				return(-1);

			// get string width
			nStringWidth=GetStringWidth(GetItemText(nItem,0));

			// check string width
			if(nStringWidth)
			{
				// set rect width
				nRectWidth=nStringWidth+20;

				// compare widths
				if(nRectWidth<rRect.Width())
				{
					// adjust rect
					rRect.right=rRect.left+nRectWidth;

					// set fit flag
					bFit=TRUE;
				}
			}

			// check point
			if(rRect.PtInRect(point))
			{
				// check fit flag
				if(bFit)
				{
					// text fits, no tooltip
					return(-1);
				}
				else
				{
					// copy rect
					(*lprCell)=rRect;

					// ok
					return(nItem);
				}
			}
		}
	}

	// not found
	return(-1);
}

// CFileListCtrl::OnTTNeedText()

BOOL CFileListCtrl::OnTTNeedText(UINT nID,
								 NMHDR* pNMHDR,
								 LRESULT* pResult)
{
	// cast pointers to tooltip info
	LPTOOLTIPTEXTA lpTTTa=(LPTOOLTIPTEXTA)pNMHDR;
	LPTOOLTIPTEXTW lpTTTw=(LPTOOLTIPTEXTW)pNMHDR;

	// get actual id
	nID=pNMHDR->idFrom;

	// check for winnt auto tooltip
	if(nID==0)
		return(FALSE);

	// get text
	if(!GetItemText(nID-1,
					0,
					g_lpTTMsg,
					_MAX_PATH))
	{
		UnlockGlobalTTMsg()
		return(FALSE);
	}

#ifndef _UNICODE
	// check notification code
	if(pNMHDR->code==TTN_NEEDTEXTA)
	{
		// copy text
		lstrcpyn(g_lpLongTTMsg,g_lpTTMsg,LONG_MSG_SIZE-1);

		// set text
		lpTTTa->lpszText=g_lpLongTTMsg;

		// clear instance
		lpTTTa->hinst=NULL;
	}
	else
	{
		// convert text
		_mbstowcsz((LPWSTR)g_lpLongTTMsg,g_lpTTMsg,_MAX_PATH-1);

		// set text
		lpTTTw->lpszText=(LPWSTR)g_lpLongTTMsg;

		// clear instance
		lpTTTw->hinst=NULL;
	}
#else
	// check notification code
	if(pNMHDR->code==TTN_NEEDTEXTA)
	{
		// convert text
		_wcstombsz(g_lpLongTTMsg,(LPWSTR)g_lpTTMsg,_MAX_PATH-1);

		// set text
		lpTTTa->lpszText=g_lpLongTTMsg;

		// clear instance
		lpTTTa->hinst=NULL;
	}
	else
	{
		// copy text
		lstrcpyn(g_lpLongTTMsg,g_lpTTMsg,LONG_MSG_SIZE-1);

		// set text
		lpTTTw->lpszText=(LPWSTR)g_lpLongTTMsg;

		// clear instance
		lpTTTw->hinst=NULL;
	}
#endif

	// ok
	return(TRUE);
}

// CExtensionList::CExtensionList()

CExtensionList::CExtensionList()
{
	// reset values
	lpDesc =NULL;
	nNumExt=NULL;
	lplpExt=NULL;
}

// CExtensionList::Init()

BOOL CExtensionList::Init(LPSTR lpDescription)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpDescription)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtensionList::Init()",
							FALSE);
		return(FALSE);
	}
#endif

	// allocate memory
	if(!AllocMem((LPVOID*)&lpDesc,
				 strlen(lpDescription)+1))
		return(FALSE);

	// copy description
	strcpy(lpDesc,
		   lpDescription);

	// ok
	return(TRUE);
}

// CExtensionList::Add()

int CExtensionList::Add(LPSTR lpExt)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpExt)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtensionList::Add()",
							FALSE);
		return(-1);
	}
#endif

	// check counter
	if(nNumExt==0)
	{
		// allocate extension list
		if(!AllocMem((LPVOID*)&lplpExt,
					 sizeof(LPSTR)))
			return(FALSE);
	}
	else
	{
		// expand extension list
		if(!ExpandMem((LPVOID*)&lplpExt,
					  sizeof(LPSTR)*nNumExt,
					  sizeof(LPSTR)))
			return(FALSE);
	}

	// allocate memory
	if(!AllocMem((LPVOID*)&lplpExt[nNumExt],
				 strlen(lpExt)+1))
		return(-1);

	// copy extension
	strcpy(lplpExt[nNumExt],
		   lpExt);

	// convert to lowercase
	strlwr(lplpExt[nNumExt]);

	// increment counter
	nNumExt++;

	// ok
	return(nNumExt-1);
}

// CExtensionList::GetString()

BOOL CExtensionList::GetString(LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtensionList::GetString()",
							FALSE);
		return(FALSE);
	}

	// check count
	if(!lpDesc||
	   nNumExt==0)
	{
		DisplayErrorMessage("No extensions in list!",
							"CExtensionList::GetString()",
							FALSE);
		return(FALSE);
	}
#endif

	// counter
	int nCount;

	// copy description
	strcpy(lpStr,lpDesc);

	// add ' ('
	strcat(lpStr," (");

	// add extensions
	for(nCount=0;nCount<nNumExt;nCount++)
	{
		// add '*.'
		strcat(lpStr,"*.");

		// add extension
		strcat(lpStr,lplpExt[nCount]);

		// add ';'
		strcat(lpStr,";");
	}

	// change last ';' to ')'
	lpStr[strlen(lpStr)-1]=')';

	// add terminator
	strcat(lpStr,"#");

	// add extensions
	for(nCount=0;nCount<nNumExt;nCount++)
	{
		// add '*.'
		strcat(lpStr,"*.");

		// add extension
		strcat(lpStr,lplpExt[nCount]);

		// add ';'
		strcat(lpStr,";");
	}

	// change last ';' to '#'
	lpStr[strlen(lpStr)-1]='#';

	// ok
	return(TRUE);
}

// CExtensionList::GetMatch()

int CExtensionList::GetMatch(LPSTR lpExt)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpExt)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtensionList::GetMatch()",
							FALSE);
		return(-1);
	}
#endif

	// counter
	int nCount;

	// check for extensions
	if(nNumExt==0)
		return(-1);

	// check each extension
	for(nCount=0;nCount<nNumExt;nCount++)
	{
		// check for wildcard
		if(lplpExt[nCount][0]=='*')
			return(nCount);

		// compare strings
		if(strcmp(lpExt,
				  lplpExt[nCount])==0)
			return(nCount);
	}

	// not found
	return(-1);
}

// CExtensionList::Release()

void CExtensionList::Release(void)
{
	// counter
	int nCount;

	// free description
	FreeMem((LPVOID*)&lpDesc);

	// release extensions
	if(nNumExt)
		for(nCount=0;nCount<nNumExt;nCount++)
			FreeMem((LPVOID*)&lplpExt[nCount]);

	// free extension list
	FreeMem((LPVOID*)&lplpExt);
	
	// reset counter
	nNumExt=0;
}

// CExtensionGroup::CExtensionGroup()

CExtensionGroup::CExtensionGroup()
{
	// reset values
	nNumList   =0;
	lplpExtList=NULL;
}

// CExtensionGroup::AddList()

int CExtensionGroup::AddList(LPSTR lpDesc)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpDesc)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtensionGroup::AddList()",
							FALSE);
		return(-1);
	}
#endif

	// check counter
	if(nNumList==0)
	{
		// allocate extension list
		if(!AllocMem((LPVOID*)&lplpExtList,
					 sizeof(CExtensionList*)))
			return(FALSE);
	}
	else
	{
		// expand extension list
		if(!ExpandMem((LPVOID*)&lplpExtList,
					  sizeof(CExtensionList*)*nNumList,
					  sizeof(CExtensionList*)))
			return(FALSE);
	}

	// create extension list
	AllocClassObject(lplpExtList[nNumList],
					 CExtensionList);

	// check new object
	if(!lplpExtList[nNumList])
		return(-1);

	// init list
	if(!lplpExtList[nNumList]->Init(lpDesc))
		return(-1);

	// increment counter
	nNumList++;

	// ok
	return(nNumList-1);
}

// CExtensionGroup::AddExt()

int CExtensionGroup::AddExt(int nIndex,
							LPSTR lpExt)
{
#ifdef DEBUG_MODE
	// verify index
	if(nIndex>=nNumList)
	{
		DisplayErrorMessage("Invalid index.",
							"CExtensionGroup::AddExt()",
							FALSE);
		return(-1);
	}

	// verify string
	if(!lpExt)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtensionGroup::AddExt()",
							FALSE);
		return(-1);
	}
#endif

	// add to list
	return(lplpExtList[nIndex]->Add(lpExt));
}

// CExtensionGroup::GetString()

BOOL CExtensionGroup::GetString(LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"CExtensionGroup::GetString()",
							FALSE);
		return(-1);
	}

	// verify group
	if(nNumList==0)
	{
		DisplayErrorMessage("Empty extension group!",
							"CExtensionGroup::GetString()",
							FALSE);
		return(-1);
	}
#endif

	// counter
	int nCount;

	// string length
	int nStrLen;

	// character to copy
	char cChar;

	LockGlobalMsg()
	LockGlobalLongMsg()

	// reset string
	g_lpLongMsg[0]=0;

	// add all lists
	for(nCount=0;nCount<nNumList;nCount++)
	{
		// get string
		if(!lplpExtList[nCount]->GetString(g_lpMsg))
		{
			UnlockGlobalMsg()
			UnlockGlobalMsg()
			return(FALSE);
		}

		// add string
		strcat(g_lpLongMsg,
			   g_lpMsg);
	}

	// add terminator
	strcat(g_lpLongMsg,
		   "#");

	// get string length
	nStrLen=strlen(g_lpLongMsg);
	
	// translate string
	for(nCount=0;nCount<nStrLen;nCount++)
	{
		// get character
		cChar=g_lpLongMsg[nCount];

		// check character
		if(cChar=='#')
			lpStr[nCount]=0;
		else
			lpStr[nCount]=cChar;
	}

	UnlockGlobalMsg()
	UnlockGlobalLongMsg()

	// ok
	return(TRUE);
}

// CExtensionGroup::GetExtList()

CExtensionList* CExtensionGroup::GetExtList(int nIndex)
{
#ifdef DEBUG_MODE
	// verify index
	if(nIndex>=nNumList)
	{
		DisplayErrorMessage("Invalid index.",
							"CExtensionGroup::GetExtList()",
							FALSE);
		return(NULL);
	}
#endif

	// return list
	return(lplpExtList[nIndex]);
}

// CExtensionGroup::Release()

void CExtensionGroup::Release(void)
{
	// counter
	int nCount;

	// release extension lists
	if(nNumList)
		for(nCount=0;nCount<nNumList;nCount++)
		{
			// release list
			if(lplpExtList[nCount])
				lplpExtList[nCount]->Release();

			// free list
			FreeClassObject(lplpExtList[nCount]);
		}

	// release list
	FreeMem((LPVOID*)&lplpExtList);
	
	// reset counter
	nNumList=0;
}

// ReleaseExtensionGroups()

void ReleaseExtensionGroups(void)
{
	// release groups
	if(g_lpAudioExtGrp) g_lpAudioExtGrp->Release();
	if(g_lpPListExtGrp) g_lpPListExtGrp->Release();

	// free groups
	FreeClassObject(g_lpAudioExtGrp);
	FreeClassObject(g_lpPListExtGrp);
}

// InitExtensionGroups()

BOOL InitExtensionGroups(void)
{
	// allocate audio extensions
	AllocClassObject(g_lpAudioExtGrp,
					 CExtensionGroup);

	// check new object
	if(!g_lpAudioExtGrp)
		return(FALSE);

	// add audio extensions
	if(g_lpAudioExtGrp->AddList("All Audio Files")==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"mp3")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"mid")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"midi")      ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"rmi")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"wav")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"wm")        ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"wma")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"au")        ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"aif")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"aifc")      ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"aiff")      ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"asf")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(0,"voc")       ==-1) return(FALSE);

	if(g_lpAudioExtGrp->AddList("MP3 Files")==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(1,"mp3") ==-1) return(FALSE);

	if(g_lpAudioExtGrp->AddList("MIDI Files")==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(2,"mid")  ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(2,"midi") ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(2,"rmi")  ==-1) return(FALSE);

	if(g_lpAudioExtGrp->AddList("Windows Audio Files")==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(3,"wav")           ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(3,"wm")            ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(3,"wma")           ==-1) return(FALSE);

	if(g_lpAudioExtGrp->AddList("Other File Types")==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(4,"au")         ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(4,"aif")        ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(4,"aifc")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(4,"aiff")       ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(4,"asf")        ==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(4,"voc")        ==-1) return(FALSE);

	if(g_lpAudioExtGrp->AddList("All Files")==-1) return(FALSE);
		if(g_lpAudioExtGrp->AddExt(5,"*")   ==-1) return(FALSE);

	// allocate playlist extensions
	AllocClassObject(g_lpPListExtGrp,
					 CExtensionGroup);

	// check new object
	if(!g_lpPListExtGrp)
		return(FALSE);

	// add playlist extensions
	if(g_lpPListExtGrp->AddList("Audio Playlist Files")==-1) return(FALSE);
		if(g_lpPListExtGrp->AddExt(0,"apl")            ==-1) return(FALSE);

	if(g_lpPListExtGrp->AddList("All Files")==-1) return(FALSE);
		if(g_lpPListExtGrp->AddExt(1,"*")   ==-1) return(FALSE);

	// ok
	return(TRUE);
}

// CExtensionGroup::AddToComboBox()

BOOL CExtensionGroup::AddToComboBox(CComboBox* lpCbx)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpCbx)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CExtensionGroup::AddToComboBox()",
							FALSE);
		return(FALSE);
	}

	// verify window
	if(!IsWindow(lpCbx->m_hWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"CExtensionGroup::AddToComboBox()",
							FALSE);
		return(FALSE);
	}

	// check for extensions
	if(nNumList==0)
	{
		DisplayErrorMessage("No lists to add!",
							"CExtensionGroup::AddToComboBox()",
							FALSE);
		return(FALSE);
	}
#endif

	// counter
	int nCount;

	// string pointer
	LPSTR lpStr=NULL;

	// index
	int nIdx;

	LockGlobalMsg()

	// add extensions
	for(nCount=0;nCount<nNumList;nCount++)
	{
		// get string
		if(!lplpExtList[nCount]->GetString(g_lpMsg))
		{
			UnlockGlobalMsg()
			return(FALSE);
		}

		// get first '#'
		lpStr=strchr(g_lpMsg,
					 '#');

		// check pointer
		if(lpStr)
		{
			// clip string
			lpStr[0]=0;
		}

		// add to combo box
		nIdx=lpCbx->AddString(g_lpMsg);

		// check result
		if(nIdx<0)
		{
			DisplayNEErrorMessage("Unable to add extension list to combo box.");
			UnlockGlobalMsg()
			return(FALSE);
		}

		// set pointer to list
		if(lpCbx->SetItemData(nIdx,
							  (DWORD)lplpExtList[nCount])==CB_ERR)
		{
			DisplayNEErrorMessage("Unable to set extension list pointer.");
			UnlockGlobalMsg()
			return(FALSE);
		}
	}

	UnlockGlobalMsg()

	// select first item
	lpCbx->SetCurSel(0);

	// ok
	return(TRUE);
}

// CFolderCtrlButton::CFolderCtrlButton()

CFolderCtrlButton::CFolderCtrlButton(UINT nID)
{
	// copy id
	nCtrlId=nID;

	// call base method
	CExtButton::CExtButton();
}

// CFolderCtrlButton::PreTranslateMessage()

BOOL CFolderCtrlButton::PreTranslateMessage(MSG *pMsg)
{
	// check for keydown
	if(pMsg->message==WM_KEYDOWN)
	{
		// check for backspace
		if((int)pMsg->wParam==VK_BACK)
		{
			// go back
			if(g_lpAudioHistoryCbx)
				g_lpAudioHistoryCbx->FolderBack();

			// do not process
			return(TRUE);
		}
	}

	// call base method
	return(CExtButton::PreTranslateMessage(pMsg));
}

// CreatePlaybackCtrlImages()

BOOL CreatePlaybackCtrlImages(void)
{
	// device contexts
	CDC* lpDesktopDC=NULL;
	CDC* lpImageDC=NULL;

	// bitmap colors
	COLORREF clrBnFace;
	COLORREF clrShadow;
	COLORREF clrHilite;
	COLORREF clrArrow;
	COLORREF clrCurrent;

	// allocate bitmaps
	AllocBitmap(g_lpPlayBmp);
	AllocBitmap(g_lpPauseBmp);
	AllocBitmap(g_lpStopBmp);
	AllocBitmap(g_lpFullRewBmp);
	AllocBitmap(g_lpRewBmp);
	AllocBitmap(g_lpFwdBmp);
	AllocBitmap(g_lpPlayBmpGr);
	AllocBitmap(g_lpPauseBmpGr);
	AllocBitmap(g_lpStopBmpGr);
	AllocBitmap(g_lpFullRewBmpGr);
	AllocBitmap(g_lpRewBmpGr);
	AllocBitmap(g_lpFwdBmpGr);

	// get desktop dc
	lpDesktopDC=CDC::FromHandle(::GetDC(GetDesktopWindow()));

	// check desktop dc
	if(!lpDesktopDC)
	{
		DisplayErrorMessage("Unable to find desktop device context.");
		return(FALSE);
	}

	// macro to create bitmaps
	#define CreateBmp(b,x,y) { if(!b->CreateCompatibleBitmap(lpDesktopDC,x,y)) { DisplayErrorMessage("Unable to create playback control image."); return(FALSE); } }

	// create bitmaps
	CreateBmp(g_lpPlayBmp,     16,16);
	CreateBmp(g_lpPauseBmp,    16,16);
	CreateBmp(g_lpStopBmp,     16,16);
	CreateBmp(g_lpFullRewBmp,  16,16);
	CreateBmp(g_lpRewBmp,      16,16);
	CreateBmp(g_lpFwdBmp,      16,16);
	CreateBmp(g_lpPlayBmpGr,   16,16);
	CreateBmp(g_lpPauseBmpGr,  16,16);
	CreateBmp(g_lpStopBmpGr,   16,16);
	CreateBmp(g_lpFullRewBmpGr,16,16);
	CreateBmp(g_lpRewBmpGr,    16,16);
	CreateBmp(g_lpFwdBmpGr,    16,16);

	// get bitmap colors
	clrBnFace=GetSysColor(COLOR_3DFACE);
	clrShadow=LightenColor(GetSysColor(COLOR_3DSHADOW),2);
	clrHilite=GetSysColor(COLOR_3DHILIGHT);
	clrArrow =GetSysColor(COLOR_BTNTEXT);

	// allocate device context
	AllocClassObject(lpImageDC,
					 CDC);

	// check new object
	if(!lpImageDC)
		return(FALSE);

	// create compatible dc
	if(!lpImageDC->CreateCompatibleDC(lpDesktopDC))
	{
		DisplayErrorMessage("Unable to create desktop-compatible device context.");
		return(FALSE);
	}
	else
		AddWinResource

	// select play bitmap
	lpImageDC->SelectObject(g_lpPlayBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow
		lpImageDC->FillSolidRect(4, 1,2,14,clrCurrent);
		lpImageDC->FillSolidRect(6, 2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(7, 3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(8, 4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(9, 5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(10,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(11,7,1,2, clrCurrent);
	}

	// select play bitmap (grayed)
	lpImageDC->SelectObject(g_lpPlayBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow
		lpImageDC->FillSolidRect(4, 1,2,14,clrCurrent);
		lpImageDC->FillSolidRect(6, 2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(7, 3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(8, 4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(9, 5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(10,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(11,7,1,2, clrCurrent);
	}

	// select pause bitmap
	lpImageDC->SelectObject(g_lpPauseBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw bars
		lpImageDC->FillSolidRect(3, 1,3,13,clrCurrent);
		lpImageDC->FillSolidRect(10,1,3,13,clrCurrent);
	}

	// select pause bitmap (grayed)
	lpImageDC->SelectObject(g_lpPauseBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw bars
		lpImageDC->FillSolidRect(3, 1,3,13,clrCurrent);
		lpImageDC->FillSolidRect(10,1,3,13,clrCurrent);
	}

	// select stop bitmap
	lpImageDC->SelectObject(g_lpStopBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw block
		lpImageDC->FillSolidRect(2,1,12,13,clrCurrent);
	}

	// select stop bitmap (grayed)
	lpImageDC->SelectObject(g_lpStopBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw block
		lpImageDC->FillSolidRect(2,1,12,13,clrCurrent);
	}

	// select full-rewind bitmap
	lpImageDC->SelectObject(g_lpFullRewBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow
		lpImageDC->FillSolidRect(5, 7,1,2, clrCurrent);
		lpImageDC->FillSolidRect(6, 6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(7, 5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(8, 4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(9, 3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(10,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(11,1,2,14,clrCurrent);

		// draw stop
		lpImageDC->FillSolidRect(3,1,2,14,clrCurrent);
	}

	// select full-rewind bitmap (grayed)
	lpImageDC->SelectObject(g_lpFullRewBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow
		lpImageDC->FillSolidRect(5, 7,1,2, clrCurrent);
		lpImageDC->FillSolidRect(6, 6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(7, 5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(8, 4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(9, 3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(10,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(11,1,2,14,clrCurrent);

		// draw stop
		lpImageDC->FillSolidRect(3,1,2,14,clrCurrent);
	}

	// select rewind bitmap
	lpImageDC->SelectObject(g_lpRewBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow #1
		lpImageDC->FillSolidRect(1,7,1,2, clrCurrent);
		lpImageDC->FillSolidRect(2,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(3,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(4,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(5,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(6,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(7,1,1,14,clrCurrent);

		// draw arrow #2
		lpImageDC->FillSolidRect(8, 7,1,2, clrCurrent);
		lpImageDC->FillSolidRect(9, 6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(10,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(11,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(12,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(13,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(14,1,1,14,clrCurrent);
	}

	// select rewind bitmap (grayed)
	lpImageDC->SelectObject(g_lpRewBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow #1
		lpImageDC->FillSolidRect(1,7,1,2, clrCurrent);
		lpImageDC->FillSolidRect(2,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(3,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(4,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(5,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(6,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(7,1,1,14,clrCurrent);

		// draw arrow #2
		lpImageDC->FillSolidRect(8, 7,1,2, clrCurrent);
		lpImageDC->FillSolidRect(9, 6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(10,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(11,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(12,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(13,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(14,1,1,14,clrCurrent);
	}

	// select forward bitmap
	lpImageDC->SelectObject(g_lpFwdBmp);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrArrow;

		// draw arrow #1
		lpImageDC->FillSolidRect(1,1,1,14,clrCurrent);
		lpImageDC->FillSolidRect(2,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(3,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(4,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(5,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(6,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(7,7,1,2, clrCurrent);

		// draw arrow #2
		lpImageDC->FillSolidRect(8, 1,1,14,clrCurrent);
		lpImageDC->FillSolidRect(9, 2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(10,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(11,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(12,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(13,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(14,7,1,2, clrCurrent);
	}

	// select forward bitmap (grayed)
	lpImageDC->SelectObject(g_lpFwdBmpGr);

	// draw image
	{
		// draw background
		lpImageDC->FillSolidRect(0,0,16,16,clrBnFace);

		// set current color
		clrCurrent=clrShadow;

		// draw arrow #1
		lpImageDC->FillSolidRect(1,1,1,14,clrCurrent);
		lpImageDC->FillSolidRect(2,2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(3,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(4,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(5,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(6,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(7,7,1,2, clrCurrent);

		// draw arrow #2
		lpImageDC->FillSolidRect(8, 1,1,14,clrCurrent);
		lpImageDC->FillSolidRect(9, 2,1,12,clrCurrent);
		lpImageDC->FillSolidRect(10,3,1,10,clrCurrent);
		lpImageDC->FillSolidRect(11,4,1,8, clrCurrent);
		lpImageDC->FillSolidRect(12,5,1,6, clrCurrent);
		lpImageDC->FillSolidRect(13,6,1,4, clrCurrent);
		lpImageDC->FillSolidRect(14,7,1,2, clrCurrent);
	}

	// select null object
	lpImageDC->SelectObject((CGdiObject*)NULL);

	// delete device context
	if(lpImageDC->DeleteDC())
		RemoveWinResource

	// free device context
	FreeClassObject(lpImageDC);

	// ok
	return(TRUE);
}

// CMainPropSheet::OnMCINotifyPos()

LRESULT CMainPropSheet::OnMCINotifyPos(WPARAM wParam,
									   LPARAM lParam)
{
	// check for music manager
	if(g_lpCurMusicMgrDlg)
	{
		// update timer
		UpdateAudioTimer();
	}

	// ok
	return(NULL);
}

// CMainPropSheet::OnMCINotifyMode()

LRESULT CMainPropSheet::OnMCINotifyMode(WPARAM wParam,
										LPARAM lParam)
{
	// check for playback mode
	if(g_bSongPlaying)
	{
		// check for stop
		if(lParam==MCI_MODE_STOP)
		{
			// check music flag
			if(!g_bNoMusic)
			{
				// play next song
				PlayNextSong();
			}
		}
	}

	// check for music manager
	if(g_lpCurMusicMgrDlg)
	{
		// check for stop
		if(lParam==MCI_MODE_STOP)
		{
			// ignore when paused
			if(!g_bAudioPause)
			{
				// click stop button
				g_lpCurMusicMgrDlg->OnStopBtnClk();
			}
		}
	}

	// ok
	return(NULL);
}

// CFileListCtrl::AddToPlaylist()

BOOL CFileListCtrl::AddToPlaylist(void)
{
	// pointer to file info
	CFileInfo* lpFileInfo;

	// check for current audio
	if(!g_lpCurAudioFLD)
		return(FALSE);

	// must not be folder or link
	if(g_lpCurAudioFLD->bIsFolder||
	   g_lpCurAudioFLD->bIsLinkToFolder)
		return(FALSE);

	// must be valid audio
	if(!g_nCurAudioDevID)
		return(FALSE);

	// cast pointer to file info
	lpFileInfo=(CFileInfo*)g_lpCurAudioFLD->lpData;

	LockGlobalTTMsg()

	// get full path
	lpFileInfo->GetPath(g_lpTTMsg);

	// switch focus back and forth to playlist to indicate action
	PerformFocusSwap(g_lpAudioPList,
					 g_lpAudioFileList,
					 75,2);

	// add to playlist
	if(!g_lpAudioPList->AddToList(g_lpCurAudioFLD,
								  lpFileInfo->lpTitle,
								  g_lpTTMsg))
		return(FALSE);

	UnlockGlobalTTMsg()

	// make sure selection is visible
	g_lpAudioFileList->EnsureVisible(g_lpAudioFileList->GetSelection(),
									 FALSE);

	// play sound
	PlaySound(IDR_ADDSAVERSND);

	// ok
	return(TRUE);
}

// ShowPreferencesDlg()

void ShowPreferencesDlg(void)
{
	// run dialog box
	g_lpPrefsDlg->DoModal();
}

// CPreferencesDlg::InitDialog()

BOOL CPreferencesDlg::InitDialog(void)
{
	// capture splash-screen checkbox
	if(!CaptureDlgControl(this,
						  g_lpSplashScreenChk,
						  IDC_SPLASHSCRNCHK))
		return(FALSE);

	// capture play-sfx checkbox
	if(!CaptureDlgControl(this,
						  g_lpPlaySFXChk,
						  IDC_PLAYSFXCHK))
		return(FALSE);

	// capture button-tooltips checkbox
	if(!CaptureDlgControl(this,
						  g_lpTooltipsChk,
						  IDC_SHOWTOOLTIPSCHK))
		return(FALSE);

	// capture saver-list-details checkbox
	if(!CaptureDlgControl(this,
						  g_lpSaverListDetChk,
						  IDC_SAVERLISTDETCHK))
		return(FALSE);

	// capture rating-images checkbox
	if(!CaptureDlgControl(this,
						  g_lpRatingImagesChk,
						  IDC_RATINGIMGSCHK))
		return(FALSE);

	// capture saver-list-popup checkbox
	if(!CaptureDlgControl(this,
						  g_lpSaverListPopupChk,
						  IDC_SLISTPOPUPCHK))
		return(FALSE);

	// capture playlist-popup checkbox
	if(!CaptureDlgControl(this,
						  g_lpPlaylistPopupChk,
						  IDC_PLISTPOPUPCHK))
		return(FALSE);
	
	// fill in preferences
	g_lpPlaySFXChk->SetCheck(g_bPlaySFX              ? 1 : 0);
	g_lpTooltipsChk->SetCheck(g_bShowToolTips        ? 1 : 0);
	g_lpSplashScreenChk->SetCheck(g_bSplashScreen    ? 1 : 0);
	g_lpSaverListDetChk->SetCheck(g_bShowSaverInfo   ? 1 : 0);
	g_lpRatingImagesChk->SetCheck(g_bShowRatingImgs  ? 1 : 0);
	g_lpSaverListPopupChk->SetCheck(g_bShowPopupInfo ? 1 : 0);
	g_lpPlaylistPopupChk->SetCheck(g_bShowPListPopup ? 1 : 0);

	// check details flag
	if(g_bShowSaverInfo)
	{
		// update controls
		g_lpRatingImagesChk->Enable();
		g_lpSaverListPopupChk->Disable();
	}
	else
	{
		// update controls
		g_lpRatingImagesChk->Disable();
		g_lpSaverListPopupChk->Enable();
	}

	// capture help button
	if(!CaptureDlgControl(this,
						  g_lpPrefsHelpBtn,
						  IDC_PREFSHELPBTN))
		return(FALSE);

	// ok
	return(TRUE);
}

// CPreferencesDlg::ApplyChanges()

void CPreferencesDlg::ApplyChanges(void)
{
	// update flags
	g_bPlaySFX       =g_lpPlaySFXChk->GetCheck()        ? TRUE : FALSE;
	g_bShowToolTips  =g_lpTooltipsChk->GetCheck()       ? TRUE : FALSE;
	g_bSplashScreen  =g_lpSplashScreenChk->GetCheck()   ? TRUE : FALSE;
	g_bShowSaverInfo =g_lpSaverListDetChk->GetCheck()   ? TRUE : FALSE;
	g_bShowRatingImgs=g_lpRatingImagesChk->GetCheck()   ? TRUE : FALSE;
	g_bShowPopupInfo =g_lpSaverListPopupChk->GetCheck() ? TRUE : FALSE;
	g_bShowPListPopup=g_lpPlaylistPopupChk->GetCheck()  ? TRUE : FALSE;

	// save preferences
	SavePreferences();

	// enable tooltips as needed
	if(g_bShowToolTips)
		::EnableToolTips(g_lpMainToolTip);
	else
		DisableToolTips(g_lpMainToolTip);

	// update required settings
	ToggleSaverListDetails(FALSE);
	ToggleSaverListRatings(FALSE);

	// call base method
	CExtDialog::ApplyChanges();
}

// CPurchDlg::ReleaseDialog()

void CPurchDlg::ReleaseDialog(void)
{
#ifdef SHAREWARE_MODE
	// check timer
	if(g_nTrialDaysTimerID)
	{
		// stop timer
		if(::KillTimer(NULL,
					   g_nTrialDaysTimerID))
			RemoveWinResource

		// clear id
		g_nTrialDaysTimerID=NULL;
	}
#endif
}

// CPreferencesDlg::OnSaverListDetChkClk()

void CPreferencesDlg::OnSaverListDetChkClk(void)
{
	// check details flag
	if(g_lpSaverListDetChk->GetCheck())
	{
		// update controls
		g_lpRatingImagesChk->Enable();
		g_lpSaverListPopupChk->Disable();
	}
	else
	{
		// update controls
		g_lpRatingImagesChk->Disable();
		g_lpSaverListPopupChk->Enable();
	}
}

// CPreferencesDlg::OnContextMenu()

void CPreferencesDlg::OnContextMenu(CWnd* pWnd,
								    CPoint pos)
{
	// check for rating images check
	if(IsPointInWindow(&pos,
					   g_lpRatingImagesChk))
		g_lpRatingImagesChk->OnContextMenu(pWnd,
										   pos);

	// check for popup info check
	if(IsPointInWindow(&pos,
					   g_lpSaverListPopupChk))
		g_lpSaverListPopupChk->OnContextMenu(pWnd,
											 pos);
}

// CPreferencesDlg::OnHelpBtnClk()

void CPreferencesDlg::OnHelpBtnClk(void)
{
	// show help
	ShowHelp(IDC_PREFERENCESDLG,
			 NULL);
}

// InitSplashScreen()

BOOL InitSplashScreen(void)
{
	// image info
	BITMAP bmp;

	// parent window
	CWnd* lpParentWnd=NULL;

	// screen size
	int nXScr;
	int nYScr;

	// window rects
	CRect rWnd1;
	CRect rWnd2;

	// load splash image
	if(!LoadBitmap(&g_lpSplashBmp,
				   IDB_SPLASH))
		return(FALSE);

	// check splash screen flag
	if(!g_bSplashScreen)
		return(TRUE);

	// get image info
	if(!g_lpSplashBmp->GetBitmap(&bmp))
	{
		DisplayErrorMessage("Unable to read bitmap info.");
		return(FALSE);
	}

	// create window object
	AllocClassObject(g_lpSplashWnd,
					 CSplashWnd);

	// check new object
	if(!g_lpSplashWnd)
		return(FALSE);

	// best to keep splash centered, so leave parent null
	/* // get parent
	lpParentWnd=GetParentCWnd();*/

	// check parent
	if(lpParentWnd)
	{
		// get parent rect
		lpParentWnd->GetWindowRect(&rWnd2);

		// set window rect
		rWnd1.SetRect(((rWnd2.left+rWnd2.right )/2)-(bmp.bmWidth/2),
					  ((rWnd2.top +rWnd2.bottom)/2)-(bmp.bmHeight/2),
					  bmp.bmWidth,
					  bmp.bmHeight);
	}
	else
	{
		// get screen size
		nXScr=GetSystemMetrics(SM_CXSCREEN);
		nYScr=GetSystemMetrics(SM_CYSCREEN);

		// adjust for task bar
		nYScr-=30;

		// set window rect
		rWnd1.SetRect((nXScr/2)-(bmp.bmWidth/2),
					  (nYScr/2)-(bmp.bmHeight/2),
					  bmp.bmWidth,
					  bmp.bmHeight);
	}

	// create splash window
	if(!g_lpSplashWnd->CreateEx(WS_EX_TOPMOST,
								AfxRegisterWndClass(CS_NOCLOSE|
													CS_OWNDC|
													CS_SAVEBITS),
							    ApplicationLongName(),
							    WS_POPUP|
								WS_VISIBLE|
								WS_CLIPCHILDREN|
								WS_CLIPSIBLINGS,
								rWnd1.left,
								rWnd1.top,
								rWnd1.right,
								rWnd1.bottom,
								NULL,
								NULL))
		return(FALSE);
	else
		AddWinResource

	// play sound (bad idea)
	//PlaySound(IDR_OPENWNDSND);

	// redraw window
	g_lpSplashWnd->RedrawWindow();

	// record time
	g_dwSplashTime=GetTickCount();

	// ok
	return(TRUE);
}

// ReleaseSplashScreen()

void ReleaseSplashScreen(void)
{
	// destroy splash window
	if(g_lpSplashWnd)
		if(IsWindow(g_lpSplashWnd->m_hWnd))
			if(g_lpSplashWnd->DestroyWindow())
				RemoveWinResource

	// release image
	FreeClassObject(g_lpSplashBmp);

	// release window
	FreeClassObject(g_lpSplashWnd);
}

// CSplashWnd::CSplashWnd()

CSplashWnd::CSplashWnd()
{
	// call base method
	CWnd::CWnd();
}

// CSplashWnd::OnPaint()

void CSplashWnd::OnPaint(void)
{
	// paint struct
	PAINTSTRUCT ps;
	
	// begin paint
	BeginPaint(&ps);

	// draw bitmap
	DrawBitmap(&ps);

	// end paint
	EndPaint(&ps);
}

// CSplashWnd::DrawBitmap()

void CSplashWnd::DrawBitmap(LPPAINTSTRUCT lpPS)
{
	// working rect
	CRect rBmp;

	// device contexts
	CDC* lpSrcDC=NULL;
	CDC* lpDestDC=NULL;

	// device context state
	int nDestState;

	// previous object
	CGdiObject* lpGdiObj=NULL;

	// check bitmap
	if(!g_lpSplashBmp)
		return;

	// check for paint struct
	if(lpPS)
	{
		// copy rect
		rBmp.SetRect(lpPS->rcPaint.left,
					 lpPS->rcPaint.top,
					 lpPS->rcPaint.right,
					 lpPS->rcPaint.bottom);

		// copy dest dc
		lpDestDC=CDC::FromHandle(lpPS->hdc);
	}
	else
	{
		// use client
		GetClientRect(&rBmp);

		// get dest dc
		lpDestDC=GetDC();
	}

	// check dc
	if(!lpDestDC)
		goto CSplashWnd_DrawBitmap1;

	// save state
	nDestState=lpDestDC->SaveDC();

	// create source dc
	AllocClassObject(lpSrcDC,
					 CDC);
	
	// check for error
	if(!lpSrcDC)
		goto CSplashWnd_DrawBitmap1;

	// create compatible dc
	if(!lpSrcDC->CreateCompatibleDC(lpDestDC))
		goto CSplashWnd_DrawBitmap1;
	else
		AddWinResource

	// select bitmap
	lpGdiObj=lpSrcDC->SelectObject(g_lpSplashBmp);

	// copy bitmap
	BitBlt(lpDestDC->m_hDC,
		   rBmp.left,
		   rBmp.top,
		   rBmp.Width(),
		   rBmp.Height(),
		   lpSrcDC->m_hDC,
		   rBmp.left,
		   rBmp.top,
		   SRCCOPY);

	// restore object
	lpSrcDC->SelectObject(lpGdiObj);

// error exit point
CSplashWnd_DrawBitmap1:;

	// check destination dc
	if(lpDestDC)
	{
		// restore state
		lpDestDC->RestoreDC(nDestState);

		// check paint struct
		if(!lpPS)
		{
			// release dc
			ReleaseDC(lpDestDC);
		}
	}

	// check source dc
	if(lpSrcDC)
	{
		// delete dc
		if(lpSrcDC->DeleteDC())
			RemoveWinResource

		// free object
		FreeClassObject(lpSrcDC);
	}
}

// CAboutDlg::InitDialog()

BOOL CAboutDlg::InitDialog(void)
{
	// attach icon box
	if(!CaptureDlgControl(this,
						  g_lpPSIconBox,
						  IDC_ABOUTBMP))
		return(FALSE);

	// set icon bitmap
	g_lpPSIconBox->SetBitmap((HBITMAP)g_lpAboutBmp->m_hObject);

	// attach title text
	if(!CaptureDlgControl(this,
						  g_lpPSTitleTxt,
						  IDC_PSMGRTXT))
		return(FALSE);

	// set bold font
	if(g_lpLCFontBold)
		g_lpPSTitleTxt->SetFont(g_lpLCFontBold);

	// attach WBS link box
	if(!CaptureDlgControl(this,
						  g_lpWBSLinkBox,
						  IDC_WBSOFTBMP))
		return(FALSE);

	// set WBS bitmap
	g_lpWBSLinkBox->SetBitmap((HBITMAP)g_lpWBSLogoBmp->m_hObject);

	/* -- removed ASP
	// attach ASP link box
	if(!CaptureDlgControl(this,
						  g_lpASPLinkBox,
						  IDC_ASPLOGOBMP))
		return(FALSE);

	// set ASP bitmap
	g_lpASPLinkBox->SetBitmap((HBITMAP)g_lpASPLogoBmp->m_hObject);
	*/

	// attach license button
	if(!CaptureDlgControl(this,
						  g_lpLicenseBtn,
						  IDC_VIEWLICBTN))
		return(FALSE);

	// attach read-me button
	if(!CaptureDlgControl(this,
						  g_lpReadMeBtn,
						  IDC_VIEWREADMEBTN))
		return(FALSE);

	// ok
	return(TRUE);
}

// CAboutDlg::OnLButtonDown()

void CAboutDlg::OnLButtonDown(UINT nFlags,
							  CPoint point)
{
	// call base method
	CExtDialog::OnLButtonDown(nFlags,
							  point);
	
	// convert point to screen coordinates
	ClientToScreen(&point);

	// check for WBS logo
	if(IsPointInWindow(&point,
					   g_lpWBSLinkBox))
	{
		// begin wait
		::BeginWaitCursor();

		// open link
		OpenExternalDoc("http://www.wb-software.com/");

		// end wait
		::EndWaitCursor();
	}

	/* -- removed ASP
	// check for ASP logo
	if(IsPointInWindow(&point,
					   g_lpASPLinkBox))
	{
		// begin wait
		::BeginWaitCursor();

		// open link
		OpenExternalDoc("http://www.asp-shareware.org/");

		// end wait
		::EndWaitCursor();
	}
	*/
}

// CAboutDlg::OnMouseMove()

void CAboutDlg::OnMouseMove(UINT nFlags,
							CPoint point)
{
	// call base method
	CExtDialog::OnMouseMove(nFlags,
							point);
	
	// convert point to screen coordinates
	ClientToScreen(&point);

	// check point
	if(IsPointInWindow(&point,g_lpWBSLinkBox)/* removed ASP ||
	   IsPointInWindow(&point,g_lpASPLinkBox)*/)
	{
		// set hand cursor
		SetCursor(g_hHandCur);
	}
	else
	{
		// set default cursor
		SetCursor(g_hArrowCur);
	}
}

// CAboutDlg::OnLicenseBtnClk()

void CAboutDlg::OnLicenseBtnClk(void)
{
	// begin wait
	::BeginWaitCursor();

	LockGlobalLongMsg()

	// copy install path
	strcpy(g_lpLongMsg,
		   g_lpInstPath);

	// add '\' if req'd
	if(g_lpLongMsg[strlen(g_lpLongMsg)-1]!='\\')
		strcat(g_lpLongMsg,
			   "\\");

	// add filename
	strcat(g_lpLongMsg,
		   "license.txt");

	// open file
	OpenExternalDoc(g_lpLongMsg);

	UnlockGlobalLongMsg()

	// end wait
	::EndWaitCursor();
}

// CAboutDlg::OnReadMeBtnClk()

void CAboutDlg::OnReadMeBtnClk(void)
{
	// begin wait
	::BeginWaitCursor();

	LockGlobalLongMsg()

	// copy install path
	strcpy(g_lpLongMsg,
		   g_lpInstPath);

	// add '\' if req'd
	if(g_lpLongMsg[strlen(g_lpLongMsg)-1]!='\\')
		strcat(g_lpLongMsg,
			   "\\");

	// add filename
	strcat(g_lpLongMsg,
		   "readme.txt");

	// open file
	OpenExternalDoc(g_lpLongMsg);

	UnlockGlobalLongMsg()

	// end wait
	::EndWaitCursor();
}

// CPurchDlg::InitDialog()

BOOL CPurchDlg::InitDialog(void)
{
	// capture trial text
	if(!CaptureDlgControl(this,
						  g_lpTrialDaysTxt,
						  IDC_TRIALDAYSTXT))
		return(FALSE);

	// set bold font
	if(g_lpLCFontBold)
		g_lpTrialDaysTxt->SetFont(g_lpLCFontBold);

	LockGlobalMsg()

#ifdef SHAREWARE_MODE
	// set flag
	g_bTrialTextOn=TRUE;

	// prepare trial text
	if(g_dwTrialDays>1)
		sprintf(g_lpMsg,
				"You have %d days remaining in your free trial!",
				g_dwTrialDays);
	else if(g_dwTrialDays==1)
		strcpy(g_lpMsg,
			   "You have 1 day remaining in your free trial!");
	else
		strcpy(g_lpMsg,
			   "Your free trial period has expired! Order today!");
#endif

	// set trial text
	g_lpTrialDaysTxt->SetWindowText(g_lpMsg);

	UnlockGlobalMsg()

	// capture cards-1 box
	if(!CaptureDlgControl(this,
						  g_lpCCards1Box,
						  IDC_CCARDS1BMP))
		return(FALSE);

	// capture cards-2 box
	if(!CaptureDlgControl(this,
						  g_lpCCards2Box,
						  IDC_CCARDS2BMP))
		return(FALSE);

	// capture purchase box
	if(!CaptureDlgControl(this,
						  g_lpPSBuyBox,
						  IDC_PSBUYBMP))
		return(FALSE);

	// set bitmaps
	g_lpCCards1Box->SetBitmap((HBITMAP)g_lpCCards1Bmp->m_hObject);
	g_lpCCards2Box->SetBitmap((HBITMAP)g_lpCCards2Bmp->m_hObject);
	g_lpPSBuyBox->SetBitmap((HBITMAP)g_lpPSBuyBmp->m_hObject);

	// attach order button
	if(!CaptureDlgControl(this,
						  g_lpOrderBtn,
						  IDC_ORDERBTN))
		return(FALSE);

	// attach mail-form button
	if(!CaptureDlgControl(this,
						  g_lpMailFormBtn,
						  IDC_MAILFORMBTN))
		return(FALSE);

#ifdef SHAREWARE_MODE
	// start timer
	g_nTrialDaysTimerID=::SetTimer(NULL,
								   DUMMY_TIMER_ID,
								   500,
								   TrialDaysTimerProc);
	// check value
	if(g_nTrialDaysTimerID)
		AddWinResource
#endif

	// ok
	return(TRUE);
}

// CPurchDlg::OnCtlColor()

HBRUSH CPurchDlg::OnCtlColor(CDC* pDC,
							 CWnd* pWnd,
							 UINT nCtlColor)
{
	// init brush object
	static CBrush br;

	// text colors
	COLORREF clrTxt;
	COLORREF clrBkg;

#ifdef SHAREWARE_MODE
	// check flag
	if(g_bTrialTextOn)
	{
		// set text color
		if(g_dwTrialDays>7)
			clrTxt=RGB(0,128,0);
		else
			clrTxt=RGB(128,0,0);
	}
	else
	{
		// clear text color
		clrTxt=RGB(255,255,255);
	}
#else
	// set text color
	clrTxt=RGB(0,0,0);
#endif

	// set text bkg color
	clrBkg=RGB(255,255,255);
	
	// call base method
	HBRUSH hbr=CExtDialog::OnCtlColor(pDC,
									  pWnd,
									  nCtlColor);

	// check window pointer
	if(pWnd->m_hWnd==g_lpTrialDaysTxt->m_hWnd)
	{
		// set text colors
		pDC->SetTextColor(clrTxt);
		pDC->SetBkColor(clrBkg);

		// delete existing object
		br.DeleteObject();

		// create bkg brush
		br.CreateSolidBrush(clrBkg);
		
		// set brush handle
		hbr=(HBRUSH)br.m_hObject;
	}

	// ok
	return(hbr);
}

// CPurchDlg::OnLButtonDown()

void CPurchDlg::OnLButtonDown(UINT nFlags,
							  CPoint point)
{
	// call base method
	CExtDialog::OnLButtonDown(nFlags,
							  point);
	
	// convert point to screen coordinates
	ClientToScreen(&point);

	// check point
	if(IsPointInWindow(&point,g_lpCCards1Box)||
	   IsPointInWindow(&point,g_lpCCards2Box)||
	   IsPointInWindow(&point,g_lpPSBuyBox))
	{
		// click button
		OnOrderBtnClk();
	}
}

// CPurchDlg::OnMouseMove()

void CPurchDlg::OnMouseMove(UINT nFlags,
							CPoint point)
{
	// call base method
	CExtDialog::OnMouseMove(nFlags,
							point);
	
	// convert point to screen coordinates
	ClientToScreen(&point);

	// check point
	if(IsPointInWindow(&point,g_lpCCards1Box)||
	   IsPointInWindow(&point,g_lpCCards2Box)||
	   IsPointInWindow(&point,g_lpPSBuyBox))
	{
		// set hand cursor
		SetCursor(g_hHandCur);
	}
	else
	{
		// set default cursor
		SetCursor(g_hArrowCur);
	}
}

// CPurchDlg::OnOrderBtnClk()

void CPurchDlg::OnOrderBtnClk(void)
{
	// begin wait
	::BeginWaitCursor();

	LockGlobalLongMsg()

	// open link
	OpenExternalDoc("http://www.wb-software.com/prosaver.htm");

	UnlockGlobalLongMsg()

	// end wait
	::EndWaitCursor();
}

// CPurchDlg::OnMailFormBtnClk()

void CPurchDlg::OnMailFormBtnClk(void)
{
	// begin wait
	::BeginWaitCursor();

	LockGlobalLongMsg()

	// copy install path
	strcpy(g_lpLongMsg,
		   g_lpInstPath);

	// add '\' if req'd
	if(g_lpLongMsg[strlen(g_lpLongMsg)-1]!='\\')
		strcat(g_lpLongMsg,
			   "\\");

	// add filename
	strcat(g_lpLongMsg,
		   "order.txt");

	// open file
	OpenExternalDoc(g_lpLongMsg);

	UnlockGlobalLongMsg()

	// end wait
	::EndWaitCursor();
}

// CPurchDlg::OnContextMenu()

void CPurchDlg::OnContextMenu(CWnd* pWnd,
							  CPoint pos)
{
	// check for image boxes
	if(IsPointInWindow(&pos,g_lpCCards1Box)||
	   IsPointInWindow(&pos,g_lpCCards2Box)||
	   IsPointInWindow(&pos,g_lpPSBuyBox))
		ShowPopupMenu(IDC_PSBUYBMP);
}

// CAboutDlg::OnContextMenu()

void CAboutDlg::OnContextMenu(CWnd* pWnd,
							  CPoint pos)
{
	// check for WBS box
	if(IsPointInWindow(&pos,g_lpWBSLinkBox))
		ShowPopupMenu(IDC_WBSOFTBMP);

	/* -- removed ASP
	// check for ASP box
	if(IsPointInWindow(&pos,g_lpASPLinkBox))
		ShowPopupMenu(IDC_ASPLOGOBMP);
	*/
}

// ShowAboutDlg(void)

void ShowAboutDlg(void)
{
	// run dialog
	if(g_lpAboutDlg)
		g_lpAboutDlg->DoModal();
}

#ifdef SHAREWARE_MODE
// ShowPurchaseDlg()

void ShowPurchaseDlg(void)
{
	// run dialog
	if(g_lpPurchDlg)
		g_lpPurchDlg->DoModal();
}
#endif

// InitDefCursors()

BOOL InitDefCursors(void)
{
	// load standard cursor
	g_hArrowCur=LoadCursor(NULL,
						   IDC_ARROW);

	// check cursor
	if(g_hArrowCur==NULL||
	   g_hArrowCur==(HCURSOR)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Unable to load standard cursor resource.");
		return(FALSE);
	}
	
	// load hand cursor
	g_hHandCur=LoadCursor(NULL,
						  IDC_HAND);

	// check cursor
	if(g_hHandCur==NULL||
	   g_hHandCur==(HCURSOR)INVALID_HANDLE_VALUE)
	{
		// default to arrow
		g_hHandCur=g_hArrowCur;
	}

	// ok
	return(TRUE);
}

// ReleaseDefCursors()

void ReleaseDefCursors(void)
{
	// system will delete on exit
}

// UpdateLCFontLocations()

void UpdateLCFontLocations(void)
{
	// window object
	CWnd* lpWnd=NULL;

	// update saver info box
	if(g_lpSaverInfoDlg)
		if(IsWindow(g_lpSaverInfoDlg->m_hWnd))
		{
			// get title window
			lpWnd=g_lpSaverInfoDlg->GetDlgItem(IDC_SAVERNAME);

			// set font
			if(lpWnd)
				lpWnd->SetFont(g_lpLCFontBold);
		}

	// update about box
	if(g_lpPSTitleTxt)
		if(IsWindow(g_lpPSTitleTxt->m_hWnd))
			g_lpPSTitleTxt->SetFont(g_lpLCFontBold);

#ifdef SHAREWARE_MODE
	// update purchase box
	if(g_lpTrialDaysTxt)
		if(IsWindow(g_lpTrialDaysTxt->m_hWnd))
			g_lpTrialDaysTxt->SetFont(g_lpLCFontBold);
#endif
}

// PlaylistDataMatchesAudioItemData()

BOOL PlaylistDataMatchesAudioItemData(LPVOID lpPD,
									  LPVOID lpID)
{
	// the hard way
	/*// cast pointers to file data
	LPFILELISTDATA lpFileData1=(LPFILELISTDATA)lpPD;
	LPFILELISTDATA lpFileData2=(LPFILELISTDATA)lpID;

	// check pointers
	if(lpFileData1==NULL||
	   lpFileData2==NULL)
		return(FALSE);

	// check for folders
	if(lpFileData1->bIsFolder||
	   lpFileData2->bIsFolder||
	   lpFileData1->bIsLinkToFolder||
	   lpFileData2->bIsLinkToFolder)
		return(FALSE);

	// cast pointers to file info
	CFileInfo* lpFileInfo1=(CFileInfo*)lpFileData1->lpData;
	CFileInfo* lpFileInfo2=(CFileInfo*)lpFileData2->lpData;

	// check pointers
	if(lpFileInfo1==NULL||
	   lpFileInfo2==NULL)
		return(FALSE);

	// compare display names
	if(stricmp(lpFileInfo1->lpDisplayName,
			   lpFileInfo1->lpDisplayName)==0)
	{
		// match found
		return(TRUE);
	}*/

	// the easy way
	if(lpPD==lpID)
		return(TRUE);
	
	// no match
	return(FALSE);
}

#ifdef SHAREWARE_MODE
// GetTrialDaysRemaining()

DWORD GetTrialDaysRemaining(void)
{
	// timestamp locations
	LPSTR lpTSLoc=NULL;

	// individual timestamps
	TIMESTAMP lpTS[5];

	// final timestamp
	TIMESTAMP ts;

	// unique id
	DWORD dwID=NO_OBJECT;

	// allocate memory for locations
	if(!AllocMem((LPVOID*)&lpTSLoc,
				 119))
		return(0);
	else
		ANTIHACK_6

	// get timestamp locations
	GetTimeStampLocations(lpTSLoc);

	// get unique id
	dwID=GetHDDSerialNumber();

	// get timestamps
	GetTimeStamp(&lpTS[0],0,dwID,lpTSLoc);
	GetTimeStamp(&lpTS[1],1,dwID,lpTSLoc);
	GetTimeStamp(&lpTS[2],2,dwID,lpTSLoc);
ANTIHACK_7
	GetTimeStamp(&lpTS[3],3,dwID,lpTSLoc);
	GetTimeStamp(&lpTS[4],4,dwID,lpTSLoc);

	// reset output timestamp
	ts.dwDaysLeft    =TRIALDAYS_MAX;
	ts.dwID          =dwID;
	ts.dwInstTimeHigh=NULL;
	ts.dwInstTimeLow =NULL;

	// sort timestamps
	SortTimeStamps(&ts,lpTS,5);

	// save timestamps
	SetTimeStamp(&ts,0,lpTSLoc);
	SetTimeStamp(&ts,1,lpTSLoc);
	SetTimeStamp(&ts,2,lpTSLoc);
ANTIHACK_9
	SetTimeStamp(&ts,3,lpTSLoc);
	SetTimeStamp(&ts,4,lpTSLoc);

	// clear timestamp locations
	ClearTimeStampLocations(lpTSLoc,
							119);

	// free memory for locations
	FreeMem((LPVOID*)&lpTSLoc);

ANTIHACK_3

	// ok
	return(ts.dwDaysLeft);
}
#endif

// GetTimeStampLocations()

void GetTimeStampLocations(LPSTR lpStr)
{
	// timestamps are located as follows:
	// (1): (win.ini)  [scr32_msp] sysid=~
	// (2): bwapps.ini [appcommon] dat32=~
	// (3): HK_LM/Software/ MSP/PrivateData
	// (4): HK_LM/Software/ Microsoft/35C85175-7E86-43FF-B3B8-08A2539F102B
	// (5): C:/Windows/     msrcs32.sbw (every other byte starting at #22)

	// copy values into string
	lpStr[43] ='M';
	lpStr[60] ='i';
	lpStr[95] ='A';
	lpStr[64] ='s';
	lpStr[54] ='D';
	lpStr[16] ='b';
ANTIHACK_3
	lpStr[59] ='M';
	lpStr[114]='s';
	lpStr[25] ='i';
	lpStr[70] ='5';
	lpStr[105]=NULL;
	lpStr[93] ='0';
	lpStr[45] ='P';
	lpStr[77] ='-';
	lpStr[32] ='m';
ANTIHACK_6
	lpStr[44] ='S';
	lpStr[46] ='\\';
	lpStr[57] ='a';
	lpStr[26] =NULL;
	lpStr[50] ='v';
	lpStr[79] ='E';
	lpStr[29] ='p';
	lpStr[99] ='9';
	lpStr[34] ='o';
	lpStr[84] ='3';
	lpStr[2]  ='r';
	lpStr[11] ='y';
	lpStr[31] ='o';
	lpStr[1]  ='c';
	lpStr[86] ='F';
	lpStr[66] ='f';
	lpStr[117]=NULL;
	lpStr[13] ='i';
ANTIHACK_9
	lpStr[36] =NULL;
ANTIHACK_12
ANTIHACK_4
	lpStr[96] ='2';
	lpStr[39] ='t';
	lpStr[103]='2';
	lpStr[28] ='p';
	lpStr[56] ='t';
	lpStr[63] ='o';
	lpStr[15] =NULL;
	lpStr[18] ='a';
	lpStr[108]='r';
	lpStr[8]  ='p';
	lpStr[82] ='-';
	lpStr[51] ='a';
	lpStr[52] ='t';
	lpStr[37] ='d';
ANTIHACK_7
	lpStr[53] ='e';
	lpStr[81] ='6';
	lpStr[22] ='.';
	lpStr[10] ='s';
	lpStr[101]='1';
	lpStr[115]='b';
	lpStr[35] ='n';
	lpStr[9]  =NULL;
	lpStr[111]='3';
	lpStr[49] ='i';
	lpStr[87] ='-';
	lpStr[80] ='8';
	lpStr[42] =NULL;
	lpStr[19] ='p';
	lpStr[85] ='F';
	lpStr[100]='F';
	lpStr[65] ='o';
	lpStr[97] ='5';
ANTIHACK_10
	lpStr[104]='B';
	lpStr[17] ='w';
	lpStr[38] ='a';
ANTIHACK_5
	lpStr[0]  ='s';
	lpStr[83] ='4';
	lpStr[62] ='r';
	lpStr[106]='m';
	lpStr[109]='c';
	lpStr[4]  ='2';
	lpStr[48] ='r';
	lpStr[47] ='P';
	lpStr[6]  ='m';
	lpStr[5]  ='_';
	lpStr[116]='w';
	lpStr[112]='2';
	lpStr[33] ='m';
	lpStr[71] ='C';
	lpStr[27] ='a';
	lpStr[102]='0';
	lpStr[7]  ='s';
	lpStr[61] ='c';
	lpStr[107]='s';
	lpStr[40] ='3';
	lpStr[72] ='8';
	lpStr[23] ='i';
ANTIHACK_8
	lpStr[67] ='t';
	lpStr[76] ='5';
	lpStr[3]  ='3';
	lpStr[89] ='3';
	lpStr[30] ='c';
	lpStr[74] ='1';
	lpStr[20] ='p';
	lpStr[68] ='\\';
	lpStr[91] ='8';
	lpStr[21] ='s';
	lpStr[75] ='7';
	lpStr[92] ='-';
	lpStr[78] ='7';
	lpStr[90] ='B';
	lpStr[94] ='8';
	lpStr[73] ='5';
	lpStr[12] ='s';
ANTIHACK_11
	lpStr[41] ='2';
	lpStr[69] ='3';
	lpStr[55] ='a';
	lpStr[113]='.';
	lpStr[58] =NULL;
	lpStr[110]='s';
	lpStr[24] ='n';
	lpStr[98] ='3';
	lpStr[88] ='B';
	lpStr[14] ='d';
ANTIHACK_6
	lpStr[118]=NULL;
}

// ClearTimeStampLocations()

void ClearTimeStampLocations(LPSTR lpStr,
							 DWORD dwBytes)
{
	// counter
	DWORD dwCount;

	// randomize bytes
	for(dwCount=0;dwCount<dwBytes;dwCount++)
		lpStr[dwCount]=rand()&0xFF;

ANTIHACK_8
}

#ifdef SHAREWARE_MODE
// SetTimeStamp()

void SetTimeStamp(LPTIMESTAMP lpTS,
				  DWORD dwLocID,
				  LPSTR lpTSLoc)
{
	// timestamps are located as follows:
	// (1): (win.ini)  [scr32_msp] sysid=~
	// (2): bwapps.ini [appcommon] dat32=~
	// (3): HK_LM/Software/ MSP/PrivateData
	// (4): HK_LM/Software/ Microsoft/35C85175-7E86-43FF-B3B8-08A2539F102B
	// (5): C:/Windows/     msrcs32.sbw (every other byte starting at #22)

	// encoded timestamp
	char lpEnc[33];

	// encode timestamp
	EncodeTimeStamp((*lpTS),
					lpEnc);

	// check location
	switch(dwLocID)
	{
	case(0):

		// save profile string
		WriteProfileString(GetStringDivision(lpTSLoc,0),
						   GetStringDivision(lpTSLoc,1),
						   lpEnc);

		// ok
		break;

	case(1):

		// save private profile string
		WritePrivateProfileString(GetStringDivision(lpTSLoc,3),
								  GetStringDivision(lpTSLoc,4),
								  lpEnc,
								  GetStringDivision(lpTSLoc,2));

		// ok
		break;

	case(2):

		// prepare key string
		sprintf(g_lpMsg,
				"%s\\%s",
				"Software",
				GetStringDivision(lpTSLoc,5));

		// set registry value
		RegSetValue(HKEY_LOCAL_MACHINE,
					g_lpMsg,
					REG_SZ,
					lpEnc,
					32);

		// ok
		break;

	case(3):
		
		// prepare key string
		sprintf(g_lpMsg,
				"%s\\%s",
				"Software",
				GetStringDivision(lpTSLoc,6));

		// set registry value
		RegSetValue(HKEY_LOCAL_MACHINE,
					g_lpMsg,
					REG_SZ,
					lpEnc,
					32);

		// ok
		break;

	case(4):

		// set string to file
		SetTimeStampStringToFile(lpEnc,
								 GetStringDivision(lpTSLoc,7));

		// ok
		break;
	}
}

// GetTimeStamp()

void GetTimeStamp(LPTIMESTAMP lpTS,
				  DWORD dwLocID,
				  DWORD dwUniID,
				  LPSTR lpTSLoc)
{
	// timestamps are located as follows:
	// (1): (win.ini)  [scr32_msp] sysid=~
	// (2): bwapps.ini [appcommon] dat32=~
	// (3): HK_LM/Software/ MSP/PrivateData
	// (4): HK_LM/Software/ Microsoft/35C85175-7E86-43FF-B3B8-08A2539F102B
	// (5): C:/Windows/     msrcs32.sbw (every 3rd byte starting at #22)

	// encoded timestamp
	char lpEnc[33];

	// set null in case of error
	lpEnc[0]=NULL;

	// data buffer size
	LONG cbSize;

	// check location
	switch(dwLocID)
	{
	case(0):

		// read profile string
		GetProfileString(GetStringDivision(lpTSLoc,0),
						 GetStringDivision(lpTSLoc,1),
						 "q",
						 lpEnc,
						 33);

		// ok
		break;

	case(1):

		// read private profile string
		GetPrivateProfileString(GetStringDivision(lpTSLoc,3),
								GetStringDivision(lpTSLoc,4),
								"w",
								lpEnc,
								33,
								GetStringDivision(lpTSLoc,2));

		// ok
		break;

	case(2):

		// prepare key string
		sprintf(g_lpMsg,
				"%s\\%s",
				"Software",
				GetStringDivision(lpTSLoc,5));

		// get size of registry value
		RegQueryValue(HKEY_LOCAL_MACHINE,
					  g_lpMsg,
					  NULL,
					  &cbSize);

		// check size
		if(cbSize>33)
		{
			// set default string
			strcpy(lpEnc,"e");
		}
		else
		{
			// get registry data
			RegQueryValue(HKEY_LOCAL_MACHINE,
						  g_lpMsg,
						  lpEnc,
						  &cbSize);
		}

		// ok
		break;

	case(3):

		// prepare key string
		sprintf(g_lpMsg,
				"%s\\%s",
				"Software",
				GetStringDivision(lpTSLoc,6));

		// get size of registry value
		RegQueryValue(HKEY_LOCAL_MACHINE,
					  g_lpMsg,
					  NULL,
					  &cbSize);

		// check size
		if(cbSize>33)
		{
			// set default string
			strcpy(lpEnc,"r");
		}
		else
		{
			// get registry data
			RegQueryValue(HKEY_LOCAL_MACHINE,
						  g_lpMsg,
						  lpEnc,
						  &cbSize);
		}

		// ok
		break;

	case(4):

		// get string from file
		GetTimeStampStringFromFile(lpEnc,
								   GetStringDivision(lpTSLoc,7));

		// ok
		break;
	}

	// decode timestamp
	(*lpTS)=DecodeTimeStamp(lpEnc);

	// check id
	if(lpTS->dwID!=dwUniID)
	{
		// set default values
		lpTS->dwDaysLeft    =TRIALDAYS_MAX;
		lpTS->dwID          =dwUniID;
		lpTS->dwInstTimeHigh=NULL;
		lpTS->dwInstTimeLow =NULL;
	}
}

// SortTimeStamps()

void SortTimeStamps(LPTIMESTAMP lpOut,
					LPTIMESTAMP lpTS,
					DWORD dwNumTS)
{
	// counter
	DWORD dwCount;

	// current time
	FILETIME ft;

	// 64-bit time values
	QWORD qwInstTime;
	QWORD qwCurTime;

	// copy first timestamp
	(*lpOut)=lpTS[0];

	// sort through timestamps
	for(dwCount=1;dwCount<dwNumTS;dwCount++)
	{
		// set lowest days
		if(lpTS[dwCount].dwDaysLeft<lpOut->dwDaysLeft)
			lpOut->dwDaysLeft=lpTS[dwCount].dwDaysLeft;

		// set 64-bit date values
		QWORD qwDateLow=(((QWORD)lpOut->dwInstTimeHigh)       <<32)+((QWORD)lpOut->dwInstTimeLow);
		QWORD qwDateCur=(((QWORD)lpTS[dwCount].dwInstTimeHigh)<<32)+((QWORD)lpTS[dwCount].dwInstTimeLow);

		// check for null date
		if(qwDateCur!=NULL)
		{
			// compare values
			if(qwDateCur<qwDateLow)
			{
				// set new value
				lpOut->dwInstTimeHigh=(DWORD)((qwDateCur&0xFFFFFFFF00000000I64)>>32);
				lpOut->dwInstTimeLow =(DWORD)((qwDateCur&0x00000000FFFFFFFFI64));
			}
		}
	}

	// get current time
	GetSystemTimeAsFileTime(&ft);
	
	// check for null date
	if(lpOut->dwInstTimeHigh==NULL&&
	   lpOut->dwInstTimeLow ==NULL)
	{
		// set current date
		lpOut->dwInstTimeHigh=ft.dwHighDateTime;
		lpOut->dwInstTimeLow =ft.dwLowDateTime;
	}

	// set current time
	qwCurTime=(((QWORD)ft.dwHighDateTime)<<32)+((QWORD)ft.dwLowDateTime);

	// get install time
	qwInstTime=(((QWORD)lpOut->dwInstTimeHigh)<<32)+((QWORD)lpOut->dwInstTimeLow);

	// compare current & install times
	if(qwCurTime<qwInstTime)
	{
		// cheater!!
		lpOut->dwDaysLeft=0;

		// ok
		return;
	}

	// compute days left based on install time
	DWORD dwDaysLeft=TRIALDAYS_MAX-((DWORD)((qwCurTime-qwInstTime)/CNSEC_PER_DAY));

	// check for overflow
	if(dwDaysLeft>TRIALDAYS_MAX)
	{
		// trial expired
		lpOut->dwDaysLeft=0;

		// ok
		return;
	}

	// set lowest days left
	if(dwDaysLeft<lpOut->dwDaysLeft)
		lpOut->dwDaysLeft=dwDaysLeft;
}

// ShowTrialDays()

void ShowTrialDays(LPCSTR lpReg)
{
	// check reg flag
	if(!lpReg)
	{
		// check main sheet
		if(g_lpMainSheet)
			if(IsWindow(g_lpMainSheet->m_hWnd))
			{
				// show dialog (always)
				g_lpMainSheet->OnPurchBtn();

				// warn about default saver
				DisplayOptMessageBox("Since your free trial period has expired, only the default\nProSaver screensaver will be shown during playback.\n\nClick the 'Buy Now!' button to order the full version today!",
									 (LPCSTR)ApplicationName(),
									 MB_OK|MB_ICONINFORMATION,
									 "MsgBox_TrialExp");

				// stop here
				return;
			}

		// run stand-alone
		RunStandAlonePurchDlg();

		// stop here
		return;
	}

	// check for flag
	if(LoadOptionInt(lpReg,
					 0,
					 1,
					 0)==0)
	{
		// save flag
		SaveOptionInt(lpReg,
					  1);

		// check main sheet
		if(g_lpMainSheet)
			if(IsWindow(g_lpMainSheet->m_hWnd))
			{
				// play sound
				PlaySound(FORCE_DEFSND);

				// show dialog
				g_lpMainSheet->OnPurchBtn();

				// stop here
				return;
			}

		// run stand-alone
		RunStandAlonePurchDlg();

		// stop here
		return;
	}
}

// TrialDaysTimerProc()

void CALLBACK TrialDaysTimerProc(HWND hWnd,
								 UINT uMsg,
								 UINT idEvent,
								 DWORD dwTime)
{
	// counter
	static int nCount=0;
	
	// increment counter
	nCount++;

	// check counter
	if(nCount==2)
	{
		// clear text flag
		g_bTrialTextOn=FALSE;

		// redraw window
		g_lpTrialDaysTxt->RedrawWindow();
	}
	else if(nCount==3)
	{
		// set text flag
		g_bTrialTextOn=TRUE;

		// redraw window
		g_lpTrialDaysTxt->RedrawWindow();

		// reset counter
		nCount=0;
	}
}
#else
// ResetTimeStamps()

void ResetTimeStamps(void)
{
	// timestamps are located as follows:
	// (1): (win.ini)  [scr32_msp] sysid=~
	// (2): bwapps.ini [appcommon] dat32=~
	// (3): HK_LM/Software/ MSP/PrivateData
	// (4): HK_LM/Software/ Microsoft/35C85175-7E86-43FF-B3B8-08A2539F102B
	// (5): C:/Windows/     msrcs32.sbw (every other byte starting at #22)

	// timestamp locations
	LPSTR lpTSLoc=NULL;

	// allocate memory for locations
	if(!AllocMem((LPVOID*)&lpTSLoc,
				 119))
		return;

	// get timestamp locations
	GetTimeStampLocations(lpTSLoc);

	// reset location #1
	WriteProfileString(GetStringDivision(lpTSLoc,0),
					   GetStringDivision(lpTSLoc,1),
					   "q");

	// reset location #2
	WritePrivateProfileString(GetStringDivision(lpTSLoc,3),
							  GetStringDivision(lpTSLoc,4),
							  "w",
							  GetStringDivision(lpTSLoc,2));

	// prepare key string
	sprintf(g_lpMsg,
			"%s\\%s",
			"Software",
			GetStringDivision(lpTSLoc,5));

	// reset location #3
	RegSetValue(HKEY_LOCAL_MACHINE,
				g_lpMsg,
				REG_SZ,
				"e",
				1);

	// prepare key string
	sprintf(g_lpMsg,
			"%s\\%s",
			"Software",
			GetStringDivision(lpTSLoc,6));

	// reset location #4
	RegSetValue(HKEY_LOCAL_MACHINE,
				g_lpMsg,
				REG_SZ,
				"r",
				1);

	// reset location #5
	SetTimeStampStringToFile("t",
							 GetStringDivision(lpTSLoc,7));

	// clear timestamp locations
	ClearTimeStampLocations(lpTSLoc,
							119);

	// free memory for locations
	FreeMem((LPVOID*)&lpTSLoc);

	// clear trial flags
	SaveOptionInt("Misc_TFlag1",0);
	SaveOptionInt("Misc_TFlag2",0);
	SaveOptionInt("Misc_TFlag3",0);
	SaveOptionInt("Misc_TFlag4",0);
	SaveOptionInt("Misc_TFlag5",0);
	SaveOptionInt("MsgBox_TrialExpFlag",0);
	SaveOptionInt("MsgBox_TrialExpReply",0);
}
#endif

// KeepProSaverCurrent()

BOOL KeepProSaverCurrent(void)
{
	// check flag
	if(g_bKeepCurrent)
	{
		LockGlobalErrorMsg()

		// reset string
		g_lpErrorMsg[0]=0;
		
		// get current saver
		GetCurrentScreensaver(g_lpErrorMsg,
							  _MAX_PATH);

		// check for ProSaver
		if(stricmp(g_lpErrorMsg,
				   EXE_NAME)!=0)
		{
			// query user
			if(DisplayOptMessageBox("ProSaver Screensaver Manager is not your current screensaver.\n\nWould you like to make ProSaver your current screensaver?",
									"ProSaver",
									MB_YESNO|MB_ICONWARNING,
									"MsgBox_KeepCurrent")==IDYES)
			{
				// update screensaver
				if(!SetCurrentScreensaver(EXE_NAME))
				{
					UnlockGlobalErrorMsg()
					return(FALSE);
				}
			}

			// check for flag
			if(LoadOptionInt("MsgBox_KeepCurrentFlag",
							 0,
							 1,
							 0)==1)
			{
				// clear flag & reply
				SaveOptionInt("MsgBox_KeepCurrentFlag", 0);
				SaveOptionInt("MsgBox_KeepCurrentReply",0);

				// clear warning flag
				g_bKeepCurrent=FALSE;

				// save registry flag
				SaveOptionInt("Adv_KeepCurrent",0);

				// update options if necessary
				if(g_bPlaybackPageInitOK)
					if(g_bAdvOptViewed)
						g_lpKeepCurrentChk->SetCheck(0);
			}
		}

		UnlockGlobalErrorMsg()
	}

	// ok
	return(TRUE);
}

// CMainPropSheet::OnWmHelp()

LRESULT CMainPropSheet::OnWmHelp(WPARAM wParam,
								 LPARAM lParam)
{
	// show help
	ShowHelp(NULL,
			 NULL);

	// ok
	return(TRUE);
}

// CPreferencesDlg::OnWmHelp()

LRESULT CPreferencesDlg::OnWmHelp(WPARAM wParam,
								  LPARAM lParam)
{
	// show help
	ShowHelp(IDC_PREFERENCESDLG,
			 NULL);

	// ok
	return(TRUE);
}

// ApplicationInit()

BOOL ApplicationInit(LPSAVEREXECINFO lpSEI)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpSEI)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ApplicationInit()",
							FALSE);
		return(FALSE);
	}
#endif

	// check mode
	switch(lpSEI->cFlag)
	{
	// run screensaver
	case('s'):

		// init screensaver mode
		if(!InitScreensaverMode())
			return(FALSE);

		// ok
		break;

	// change password
	case('a'):

		// change passoword
		ChangeScreensaverPassword((HWND)lpSEI->nID);

		// ok
		break;

	// WaveBreak Software commands
	case('w'):

		// check command
		switch(lpSEI->nID)
		{
#ifdef SHAREWARE_MODE
		// purchase
		case(1000):

			// run purchase dialog
			RunStandAlonePurchDlg();

			// ok
			break;
#endif
		
		// set as current screensaver
		case(2000):

			// set as current screensaver
			SetCurrentScreensaver("ProSaver.scr");

			// copy application name
			strcpy(g_lpMsg,ApplicationName());

#ifdef SHAREWARE_MODE
			// append "trial version" to name
			strcat(g_lpMsg," (Trial Version)");
#endif

			// query for options
			if(MessageBox(NULL,
						  "Your current screensaver has been changed.\n\nWould you like to open Windows Display Properties?",
						  g_lpMsg,
						  MB_YESNO|MB_ICONQUESTION|MB_APPLMODAL)==IDYES)
			{
				// open screensaver settings
				OpenScreensaverControlPanel();
			}

			// ok
			break;
		
		// open settings
		case(3000):

			// open screensaver settings
			OpenScreensaverControlPanel();

			// ok
			break;

		// run default saver
		case(4000):

#ifdef SHAREWARE_MODE
			// get days left
			g_dwTrialDays=GetTrialDaysRemaining();
#else
			// reset leftover timestamps
			ResetTimeStamps();
#endif

			// init default saver
			if(!InitDefSaverWindow())
				return(FALSE);

			// ok
			break;

		// tsr mode
		case(5000):

			// init tsr mode
			if(!InitTSRMode())
				return(FALSE);

			// ok
			break;
		}

		// ok
		break;

	// mini-preview
	case('p'):

		// initialize preview window
		if(!InitPreviewImageWindow((HWND)lpSEI->nID))
			return(FALSE);

		// ok
		break;

	// configure/default
	case('c'):
	default:

		// set parent window
		SetParentHWnd((HWND)lpSEI->nID);

		// init main sheet
		if(!InitMainSheet())
			return(FALSE);

		// ok
		break;
	}

	// ok
	return(TRUE);
}

// ApplicationExec()

void ApplicationExec(LPSAVEREXECINFO lpSEI)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpSEI)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ApplicationExec()",
							FALSE);
		return;
	}
#endif

	// check mode
	switch(lpSEI->cFlag)
	{
	// run screensaver
	case('s'):

		// exec screensaver mode
		ExecScreensaverMode();

		// ok
		break;

	// change password
	case('a'):

		// no exec req'd

		// ok
		break;

	// WaveBreak Software commands
	case('w'):

		// check command
		switch(lpSEI->nID)
		{
#ifdef SHAREWARE_MODE
		// purchase
		case(1000):

			// no exec req'd

			// ok
			break;
#endif
		
		// set as current screensaver
		case(2000):

			// no exec req;d

			// ok
			break;
		
		// load options
		case(3000):

			// no exec req'd

			// ok
			break;

		// run default saver
		case(4000):

			// run default saver
			ProcessScreensaverMessages();

			// ok
			break;

		// tsr mode
		case(5000):

			// exec tsr mode
			ExecTSRMode();

			// ok
			break;
		}

		// ok
		break;

	// mini-preview
	case('p'):

		// run preview
		ProcessScreensaverMessages();

		// ok
		break;

	// configure/default
	case('c'):
	default:

ANTIHACK_4

		// execute property sheet
		if(g_lpMainSheet)
			g_lpMainSheet->DoModal();

		// ok
		break;
	}
}

// ApplicationRelease()

void ApplicationRelease(LPSAVEREXECINFO lpSEI)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpSEI)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ApplicationRelease()",
							FALSE);
		return;
	}
#endif

	// kill all timers
	KillAllTimers();

	// check mode
	switch(lpSEI->cFlag)
	{
	// run screensaver
	case('s'):

		// release screensaver mode
		ReleaseScreensaverMode();

		// ok
		break;

	// change password
	case('a'):

		// no release req'd

		// ok
		break;

	// WaveBreak Software commands
	case('w'):

		// check command
		switch(lpSEI->nID)
		{
#ifdef SHAREWARE_MODE
		// purchase
		case(1000):

			// no release req'd

			// ok
			break;
#endif
		
		// set as current screensaver
		case(2000):

			// no release req'd

			// ok
			break;
		
		// load options
		case(3000):

			// no release req'd

			// ok
			break;

		// run default saver
		case(4000):

			// release default saver
			ReleaseDefSaverWindow();

#ifdef SHAREWARE_MODE
			// too annoying!! (& causes problem after run)
			/*// check trial days
			if(g_dwTrialDays==0)
			{
				// run purchase dialog
				RunStandAlonePurchDlg();
			}*/
#endif

			// ok
			break;

		// tsr mode
		case(5000):

			// release tsr mode
			ReleaseTSRMode();

			// ok
			break;
		}

		// ok
		break;

	// mini-preview
	case('p'):

		// release preview window
		ReleasePreviewImageWindow();

		// ok
		break;

	// configure/default
	case('c'):
	default:

		// release main sheet
		ReleaseMainSheet();

		// ok
		break;
	}
}

// InitPreviewImageWindow()

BOOL InitPreviewImageWindow(HWND hParentWnd)
{
	// parent's client area
	RECT rClient;
	
	// validate window handle
	if(hParentWnd==NULL||
	   hParentWnd==INVALID_HANDLE_VALUE)
	{
		DisplayNEErrorMessage("Invalid preview image window handle.");
		return(FALSE);
	}

	// check window
	if(!IsWindow(hParentWnd))
	{
		DisplayNEErrorMessage("Invalid preview image window.");
		return(FALSE);
	}

	// add window class
	if(!AddPreviewImageWindowClass())
		return(FALSE);

	// get parent's client area
	if(!GetClientRect(hParentWnd,
					  &rClient))
		return(FALSE);
	
	// create application window
	g_hWnd=CreateWindowEx(NULL,
						  ApplicationID(APID_MINIPREV),
						  NULL,
						  WS_CHILD|
						  WS_VISIBLE|
						  WS_CLIPCHILDREN,
						  0,0,
						  rClient.right,
						  rClient.bottom,
						  hParentWnd,
						  NULL,
						  g_MainApp.m_hInstance,
						  NULL);

	// check window handle
	if(g_hWnd==(HWND)INVALID_HANDLE_VALUE||
	   g_hWnd==NULL)
		return(FALSE);
	else
		AddWinResource;

	// ok
	return(TRUE);
}

// ReleasePreviewImageWindow()

void ReleasePreviewImageWindow(void)
{
	// check handle & destroy window
	if(g_hWnd!=(HWND)INVALID_HANDLE_VALUE&&
	   g_hWnd!=NULL)
		if(DestroyWindow(g_hWnd))
		{
			// reset handle
			g_hWnd=(HWND)INVALID_HANDLE_VALUE;
			
			// remove resource
			RemoveWinResource;
		}

	// remove window class
	RemovePreviewImageWindowClass();
}

// AddPreviewImageWindowClass()

BOOL AddPreviewImageWindowClass(void)
{
ANTIHACK_5

	// create class for this window
	WNDCLASSEX wcx;
	wcx.cbSize       =sizeof(WNDCLASSEX);
	wcx.style        =CS_OWNDC;
	wcx.lpfnWndProc  =PreviewImageWindowProc;
	wcx.cbClsExtra   =NULL;
	wcx.cbWndExtra   =NULL;
	wcx.hInstance    =g_MainApp.m_hInstance;
	wcx.hIcon        =NULL;
	wcx.hIconSm      =NULL;
	wcx.hCursor      =LoadCursor(NULL,IDC_ARROW);
	wcx.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName =NULL;
	wcx.lpszClassName=ApplicationID(APID_MINIPREV);

	// register window class
	if(!RegisterClassEx(&wcx))
		return(FALSE);
	else
		AddWinResource;

	// ok
	return(TRUE);
}

// RemovePreviewImageWindowClass()

void RemovePreviewImageWindowClass(void)
{
	// un-register class
	if(UnregisterClass(ApplicationID(APID_MINIPREV),
					   g_MainApp.m_hInstance))
		RemoveWinResource;
}

// PreviewImageWindowProc()

LRESULT CALLBACK PreviewImageWindowProc(HWND hWnd,
										UINT Msg,
										WPARAM wParam,
										LPARAM lParam)
{
	// bitmap handle
	static HBITMAP hBmp=(HBITMAP)INVALID_HANDLE_VALUE;
	
	// device context
	HDC hDC;

	// pointer to create structure
	LPCREATESTRUCT lpCS;

	// paint structure
	PAINTSTRUCT ps;

	// dc state
	int nState=NULL;

	// gdi object
	HGDIOBJ hGdiObj=(HGDIOBJ)INVALID_HANDLE_VALUE;

	// check for messages that we are interested in
	switch(Msg)
	{
	// create window message
	case(WM_CREATE):

		// get pointer to create struct
		lpCS=(LPCREATESTRUCT)lParam;

		// load preview image
		hBmp=(HBITMAP)LoadImage(g_MainApp.m_hInstance,
								MAKEINTRESOURCE(IDB_SCREEN),
								IMAGE_BITMAP,
								lpCS->cx,
								lpCS->cy,
								LR_DEFAULTCOLOR);

		// verify handle
		if(hBmp)
			AddWinResource;

		// ok
		return(NULL);

	// close message
	case(WM_CLOSE):

		// release preview image
		if(hBmp!=(HBITMAP)INVALID_HANDLE_VALUE&&
		   hBmp!=NULL)
			if(DeleteObject(hBmp))
			{
				RemoveWinResource;

				// reset handle
				hBmp=(HBITMAP)INVALID_HANDLE_VALUE;
			}

		// quit application
		PostMessage(g_hWnd,
					WM_QUIT,
					NULL,
					NULL);
		
		// ok
		return(NULL);

	// paint message
	case(WM_PAINT):

		// begin paint
		hDC=BeginPaint(g_hWnd,
					   &ps);

		// add resource
		AddWinResource;

		// check value
		if(hDC)
		{
			// display bitmap if available
			if(hBmp!=(HBITMAP)INVALID_HANDLE_VALUE&&
			   hBmp!=NULL)
			{
				// create compatible device context
				HDC hSrcDC=CreateCompatibleDC(hDC);

				// verify handle
				if(hSrcDC)
				{
					AddWinResource;

					// save state
					nState=SaveDC(hSrcDC);
					
					// select bitmap as source
					hGdiObj=SelectObject(hSrcDC,
										 hBmp);

					// copy image
					BitBlt(hDC,
						   ps.rcPaint.left,
						   ps.rcPaint.top,
						   ps.rcPaint.right,
						   ps.rcPaint.bottom,
						   hSrcDC,
						   0,0,
						   SRCCOPY);

					// restore object
					SelectObject(hSrcDC,
								 hGdiObj);

					// restore state
					RestoreDC(hSrcDC,
							  nState);

					// delete device context
					if(DeleteDC(hSrcDC))
						RemoveWinResource;
				}
				else
				{
					// save state
					nState=SaveDC(hDC);
					
					// select bitmap as source
					hGdiObj=SelectObject(hDC,
										 GetStockObject(BLACK_BRUSH));

					// paint window
					PatBlt(hDC,
						   ps.rcPaint.left,
						   ps.rcPaint.top,
						   ps.rcPaint.right,
						   ps.rcPaint.bottom,
						   PATCOPY);

					// restore object
					SelectObject(hDC,
								 hGdiObj);

					// restore state
					RestoreDC(hDC,
							  nState);
				}
			}
		}

		// end paint
		EndPaint(g_hWnd,
				 &ps); 
		
		// remove resource
		RemoveWinResource;

		// ok
		return(NULL);
	}

	// let windows process all other messages
	return(DefWindowProc(hWnd,Msg,wParam,lParam));
}

// ProcessScreensaverMessages()

void ProcessScreensaverMessages(void)
{
	// message storage
	MSG Msg;

	// retrieve message
	while(TRUE)
	{
		// process message
		if(PeekMessage(&Msg,
					   NULL,
					   NULL,
					   NULL,
					   PM_REMOVE))
		{
			// check for quit message
			if(Msg.message==WM_QUIT)
				return;

			// process message
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			// wait for message
			WaitMessage();
		}			
	}
}

// InitDefSaverWindow()

BOOL InitDefSaverWindow(void)
{
	// add window class
	if(!AddDefSaverWindowClass())
		return(FALSE);

	// create application window
	g_hWnd=CreateWindowEx(WS_EX_TOPMOST,
						  ApplicationID(APID_DEFSVR),
						  "ProSaver Default Window",
						  WS_POPUP|
						  WS_VISIBLE|
						  WS_CLIPCHILDREN|
						  WS_CLIPSIBLINGS,
						  0,0,
						  GetSystemMetrics(SM_CXSCREEN),
						  GetSystemMetrics(SM_CYSCREEN),
						  NULL,
						  NULL,
						  g_MainApp.m_hInstance,
						  NULL);

	// check window handle
	if(g_hWnd==(HWND)INVALID_HANDLE_VALUE||
	   g_hWnd==NULL)
	{
		DisplayErrorMessage("Unable to create default screensaver window.");
		return(FALSE);
	}
	else
		AddWinResource;

	// ok
	return(TRUE);
}

// ReleaseDefSaverWindow()

void ReleaseDefSaverWindow(void)
{
	// check handle & destroy window
	if(g_hWnd!=(HWND)INVALID_HANDLE_VALUE&&
	   g_hWnd!=NULL)
		if(DestroyWindow(g_hWnd))
		{
			// reset handle
			g_hWnd=(HWND)INVALID_HANDLE_VALUE;
			
			// remove resource
			RemoveWinResource;
		}

	// remove window class
	RemoveDefSaverWindowClass();
}

// AddDefSaverWindowClass()

BOOL AddDefSaverWindowClass(void)
{
	// create class for this window
	WNDCLASSEX wcx;
	wcx.cbSize       =sizeof(WNDCLASSEX);
	wcx.style        =CS_OWNDC;
	wcx.lpfnWndProc  =DefSaverWindowProc;
	wcx.cbClsExtra   =NULL;
	wcx.cbWndExtra   =NULL;
	wcx.hInstance    =g_MainApp.m_hInstance;
	wcx.hIcon        =NULL;
	wcx.hIconSm      =NULL;
	wcx.hCursor      =LoadCursor(NULL,IDC_ARROW);
	wcx.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName =NULL;
	wcx.lpszClassName=ApplicationID(APID_DEFSVR);

	// register window class
	if(!RegisterClassEx(&wcx))
		return(FALSE);
	else
		AddWinResource;

	// ok
	return(TRUE);
}

// RemoveDefSaverWindowClass()

void RemoveDefSaverWindowClass(void)
{
	// un-register class
	if(UnregisterClass(ApplicationID(APID_DEFSVR),
					   g_MainApp.m_hInstance))
		RemoveWinResource;
}

// DefSaverWindowProc()

LRESULT CALLBACK DefSaverWindowProc(HWND hWnd,
									UINT Msg,
									WPARAM wParam,
									LPARAM lParam)
{
	// bitmap handles
	static HBITMAP hBmp   =(HBITMAP)INVALID_HANDLE_VALUE;
	static HBITMAP hMemBmp=(HBITMAP)INVALID_HANDLE_VALUE;

	// timer
	static int nTimer=-1;

	// timer id
	static DWORD dwTimerId=0;
	
	// screen size
	static int nScrX=0;
	static int nScrY=0;

	// bitmap data
	static int nBmpWd=0;
	static int nBmpHt=0;
	static int nBmpX1=0;
	static int nBmpY1=0;
	static int nBmpX2=0;
	static int nBmpY2=0;

	// device contexts
	static HDC hSrcDC =(HDC)INVALID_HANDLE_VALUE;
	static HDC hDestDC=(HDC)INVALID_HANDLE_VALUE;
	static HDC hMemDC =(HDC)INVALID_HANDLE_VALUE;

	// blend info
	static BLENDFUNCTION bf;

	// pointer to create structure
	LPCREATESTRUCT lpCS;

	// paint structure
	PAINTSTRUCT ps;

	// resource id
	int nResId;

	// bitmap object (temp)
	CBitmap* lpBmp=NULL;

	// device context object (temp)
	CDC* lpDC=NULL;

	// bitmap info
	BITMAP bmp;

	// counters
	int nX;
	int nY;

	// overlap flags
	BOOL bXOverlap;
	BOOL bYOverlap;

	// dummy flag
	BOOL bDummy;

	// check for messages that we are interested in
	switch(Msg)
	{
	// create window message
	case(WM_CREATE):

		// set screen-saver-running flag
		SystemParametersInfo(SPI_SCREENSAVERRUNNING,
							 TRUE,
							 &bDummy,
							 0);

#ifdef SHAREWARE_MODE
		// set resource id
		if(g_dwTrialDays>0)
			nResId=IDB_SAVERIMG1;
		else
			nResId=IDB_SAVERIMG2;
#else
		// set resource id
		nResId=IDB_SAVERIMG1;
#endif

		// get pointer to create struct
		lpCS=(LPCREATESTRUCT)lParam;

		// compute image sizes
		nX=(int)(((float)GetSystemMetrics(SM_CXSCREEN))*(256.0/800.0));
		nY=(int)(((float)GetSystemMetrics(SM_CYSCREEN))*(180.0/600.0));

		// load saver image
		hBmp=(HBITMAP)LoadImage(g_MainApp.m_hInstance,
								MAKEINTRESOURCE(nResId),
								IMAGE_BITMAP,
								nX,
								nY,
								LR_DEFAULTCOLOR);

		// verify handle
		if(hBmp)
		{
			AddWinResource

			// get dest dc
			hDestDC=GetDC(hWnd);

			// check handle
			if(hDestDC)
			{
				AddWinResource

				// get source dc
				hSrcDC=CreateCompatibleDC(hDestDC);

				// check handle
				if(hSrcDC)
				{
					AddWinResource

					// select bitmap into source
					SelectObject(hSrcDC,
								 hBmp);

					// get memory dc
					hMemDC=CreateCompatibleDC(hDestDC);

					// check handle
					if(hMemDC)
					{
						AddWinResource

						// copy bitmap object
						lpBmp=CBitmap::FromHandle(hBmp);

						// check object
						if(lpBmp)
						{
							// get bitmap info
							if(lpBmp->GetBitmap(&bmp))
							{
								// create memory bitmap
								hMemBmp=CreateBitmap(bmp.bmWidth,
													 bmp.bmHeight,
													 bmp.bmPlanes,
													 bmp.bmBitsPixel,
													 NULL);

								// check handle
								if(hMemBmp)
								{
									AddWinResource

									// select bitmap into mem
									SelectObject(hMemDC,
												 hMemBmp);

									// set screen size
									nScrX=GetSystemMetrics(SM_CXSCREEN);
									nScrY=GetSystemMetrics(SM_CYSCREEN);

									// set bitmap data
									nBmpWd=bmp.bmWidth;
									nBmpHt=bmp.bmHeight;

									// position 1 must be off-screen
									nBmpX1=nScrX;
									nBmpY1=nScrY;

									// adjust screen for bitmap size
									nScrX-=nBmpWd;
									nScrY-=nBmpHt;

									// set position of bitmap #2
									nBmpX2=rand()%nScrX;
									nBmpY2=rand()%nScrY;

									// set blend info
									bf.BlendOp    =AC_SRC_OVER;
									bf.BlendFlags =0;
									bf.AlphaFormat=NULL;

									// begin timer
									dwTimerId=::SetTimer(hWnd,
														 DUMMY_TIMER_ID,
														 50,
														 NULL);

									// check id
									if(dwTimerId)
										AddWinResource
								}
							}
						}
					}
				}
			}
		}

		// hide cursor
		while(ShowCursor(FALSE)>=0)
		{}

		// set init flag
		g_bSaverAppInit=TRUE;
		
		// ok
		return(NULL);

	// close message
	case(WM_CLOSE):

		// set closing flag
		g_bClosing=TRUE;

		// clear init flag
		g_bSaverAppInit=FALSE;

		// restore cursor
		while(ShowCursor(TRUE)<0)
		{}

		// kill timer
		if(::KillTimer(g_hWnd,
					   dwTimerId))
			RemoveWinResource

		// reset id
		dwTimerId=NULL;

		// de-select memory bitmap
		SelectObject(hSrcDC,
					 NULL);

		// de-select source bitmap
		SelectObject(hSrcDC,
					 NULL);

		// release saver image
		if(hBmp!=(HBITMAP)INVALID_HANDLE_VALUE&&
		   hBmp!=NULL)
			if(DeleteObject(hBmp))
				RemoveWinResource;

		// release memory bitmap
		if(hMemBmp!=(HBITMAP)INVALID_HANDLE_VALUE&&
		   hMemBmp!=NULL)
			if(DeleteObject(hMemBmp))
				RemoveWinResource;

		// release memory dc
		if(DeleteDC(hMemDC))
			RemoveWinResource

		// release source dc
		if(DeleteDC(hSrcDC))
			RemoveWinResource

		// release dest dc
		if(ReleaseDC(g_hWnd,
					 hDestDC))
			RemoveWinResource

		// clear screen-saver-running flag
		SystemParametersInfo(SPI_SCREENSAVERRUNNING,
							 FALSE,
							 &bDummy,
							 0);

		// quit application
		PostMessage(g_hWnd,
					WM_QUIT,
					NULL,
					NULL);
		
		// ok
		return(NULL);

	// paint message
	case(WM_PAINT):

		// begin paint
		BeginPaint(g_hWnd,
				   &ps);

		// select black brush
		SelectObject(ps.hdc,
					 GetStockObject(BLACK_BRUSH));

		// paint window
		PatBlt(ps.hdc,
			   0,0,
			   GetSystemMetrics(SM_CXSCREEN),
			   GetSystemMetrics(SM_CYSCREEN),
			   PATCOPY);

		// de-select object
		SelectObject(ps.hdc,
					 NULL);

		// end paint
		EndPaint(g_hWnd,
				 &ps); 

		// ok
		return(NULL);

	// update saver
	case(WM_TIMER):

		// animation values
		#define ANIM_TOTAL  16
		#define ANIM_OFFSET 20
		#define ANIM_DELAY  120

		// check screen size
		if(nScrX>0&&
		   nScrY>0)
		{
			// check timer
			if(nTimer>=0)
			{
				// check timer position
				if(nTimer<=(ANIM_TOTAL+ANIM_OFFSET))
				{
					// get dc object
					lpDC=CDC::FromHandle(hMemDC);
					
					// check object
					if(lpDC)
					{
						// check timer for pos-1
						if(nTimer<=ANIM_TOTAL)
						{
							// clear mem bitmap
							lpDC->FillSolidRect(0,0,
												nBmpWd,
												nBmpHt,
												NULL);

							// set blend factor
							bf.SourceConstantAlpha=255-((nTimer*255)/ANIM_TOTAL);

							// blend to mem bitmap
							AlphaBlend(hMemDC,
									   0,0,
									   nBmpWd,
									   nBmpHt,
									   hSrcDC,
									   0,0,
									   nBmpWd,
									   nBmpHt,
									   bf);

							// copy to display
							BitBlt(hDestDC,
								   nBmpX1,
								   nBmpY1,
								   nBmpWd,
								   nBmpHt,
								   hMemDC,
								   0,0,
								   SRCCOPY);
						}

						// check timer for pos-2
						if(nTimer>=ANIM_OFFSET)
						{
							// clear mem bitmap
							lpDC->FillSolidRect(0,0,
												nBmpWd,
												nBmpHt,
												NULL);

							// set blend factor
							bf.SourceConstantAlpha=((nTimer-ANIM_OFFSET)*255)/ANIM_TOTAL;

							// blend to mem bitmap
							AlphaBlend(hMemDC,
									   0,0,
									   nBmpWd,
									   nBmpHt,
									   hSrcDC,
									   0,0,
									   nBmpWd,
									   nBmpHt,
									   bf);

							// copy to display
							BitBlt(hDestDC,
								   nBmpX2,
								   nBmpY2,
								   nBmpWd,
								   nBmpHt,
								   hMemDC,
								   0,0,
								   SRCCOPY);
						}
					}
				}
				else if(nTimer==ANIM_DELAY)
				{
					// move pos-2 to pos-1
					nBmpX1=nBmpX2;
					nBmpY1=nBmpY2;

					// set new pos-2
					while(TRUE)
					{
						// set position
						nBmpX2=rand()%nScrX;
						nBmpY2=rand()%nScrY;

						// reset overlap flags
						bXOverlap=FALSE;
						bYOverlap=FALSE;

						// check for x-overlap
						if(nBmpX2<=nBmpX1)
						{
							if((nBmpX2+nBmpWd)>=nBmpX1)
								bXOverlap=TRUE;
						}
						else
						{
							if(nBmpX2<=(nBmpX1+nBmpWd))
								bXOverlap=TRUE;
						}

						// check for y-overlap
						if(nBmpY2<=nBmpY1)
						{
							if((nBmpY2+nBmpHt)>=nBmpY1)
								bYOverlap=TRUE;
						}
						else
						{
							if(nBmpY2<=(nBmpY1+nBmpHt))
								bYOverlap=TRUE;
						}

						// check flags
						if(bXOverlap&&bYOverlap)
						{
							// try again
						}
						else
							break;
					}

					// reset timer
					nTimer=-1;
				}
			}

			// increment timer
			nTimer++;
		}

		// ok
		return(NULL);

	// process activate message
	case(WM_ACTIVATE):

		// ignore until initialized
		if(!g_bSaverAppInit)
			return(NULL);

		// check new state
		if(LOWORD(wParam)==WA_INACTIVE)
			SendCloseMessage(&dwTimerId,
							 &nTimer);
		
		// ok
		return(NULL);
		
	// process enable message
	case(WM_ENABLE):

		// ignore until initialized
		if(!g_bSaverAppInit)
			return(NULL);

		// check flag
		if(!wParam)
			SendCloseMessage(&dwTimerId,
							 &nTimer);
		
		// ok
		return(NULL);
		
	// user has ended session
	case(WM_ENDSESSION):

		// check flags
		if((BOOL)wParam==TRUE||
		   (BOOL)lParam==TRUE)
			ForceImmediateExit();
		
		// ok
		return(NULL);

	// focus is lost
	case(WM_ENTERMENULOOP):
	case(WM_ENTERSIZEMOVE):
	case(WM_KILLFOCUS):

		// ignore until initialized
		if(!g_bSaverAppInit)
			return(NULL);

		// close screensaver
		SendCloseMessage(&dwTimerId,
						 &nTimer);

		// ok
		return(NULL);

	// system entering standby
	case(WM_POWERBROADCAST):

		// check flag
		if((DWORD)wParam==PBT_APMSUSPEND)
		{
			// close screensaver
			ForceImmediateExit();
			
			// ok
			return(TRUE);
		}
		else if((DWORD)wParam==PBT_APMQUERYSUSPEND)
		{
			// ok
			return(TRUE);
		}

		// ok
		break;
		
	// key presses
	case(WM_KEYDOWN):
	case(WM_SYSKEYDOWN):
		
		// ignore until initialized
		if(!g_bSaverAppInit)
			return(NULL);

		// close screensaver
		SendCloseMessage(&dwTimerId,
						 &nTimer);

		// ok
		return(NULL);

	// mouse movement
	case(WM_MOUSEMOVE):

		// ignore until initialized
		if(!g_bSaverAppInit)
			return(NULL);

		// scope for static variables
		{
			// init flag
			static BOOL bInit=FALSE;

			// cursor position
			static int nX=0;
			static int nY=0;

			// check timer
			if(nTimer<0)
			{
				// clear init
				bInit=FALSE;
			}

			// check init
			if(!bInit)
			{
				// save positions
				nX=(int)LOWORD(lParam);
				nY=(int)HIWORD(lParam);

				// set flag
				bInit=TRUE;
			}
			else
			{
				// check for excessive movement
				if((abs(nX-(int)LOWORD(lParam))>5)||
				   (abs(nY-(int)HIWORD(lParam))>5))
				{
					// close screensaver
					SendCloseMessage(&dwTimerId,
									 &nTimer);
				}
				else
				{
					// save new positions
					nX=(int)LOWORD(lParam);
					nY=(int)HIWORD(lParam);
				}
			}

			// ok
			return(NULL);
		}

		// ok
		break;

	// mouse buttons
	case(WM_LBUTTONDOWN):
	case(WM_MBUTTONDOWN):
	case(WM_RBUTTONDOWN):

		// ignore until initialized
		if(!g_bSaverAppInit)
			return(NULL);

		// close screensaver
		SendCloseMessage(&dwTimerId,
						 &nTimer);

		// ok
		return(NULL);

	// system command
	case(WM_SYSCOMMAND):

		// check command
		switch(wParam&0xFFF0)
		{
		// block commands
		case(SC_SCREENSAVE):
		case(SC_NEXTWINDOW):
		case(SC_PREVWINDOW):
		case(SC_CLOSE):

			// ok
			return(NULL);
		}

		// ok
		break;
	}

	// let windows process all other messages
	return(DefWindowProc(hWnd,Msg,wParam,lParam));
}

// SendCloseMessage()

void SendCloseMessage(LPDWORD lpdwTimerId,
					  int* lpnTimer)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpdwTimerId)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"SendCloseMessage()",
							FALSE);
		return;
	}
#endif

	// local closing flag
	static BOOL bClosing=FALSE;
	
	// check global closing flag
	if(g_bClosing)
		return;

	// check local closing flag
	if(bClosing)
		return;

	// set local closing flag
	bClosing=TRUE;

	// kill animation timer
	if(::KillTimer(g_hWnd,
				   (*lpdwTimerId)))
		RemoveWinResource

	// reset id
	(*lpdwTimerId)=NULL;

	// show cursor
	while(ShowCursor(TRUE)<0)
	{}

	// clear initialized flag
	g_bSaverAppInit=FALSE;

	// reset timer
	(*lpnTimer)=-1;

	/* calling app will handle passwords!!
	// confirm screensaver password
	if(!ConfirmScreensaverPassword())
	{
		// redraw window
		RedrawWindow(g_hWnd,
					 NULL,
					 NULL,
					 RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE);

		// set initialized flag
		g_bSaverAppInit=TRUE;

		// hide cursor
		while(ShowCursor(FALSE)>=0)
		{}

		// begin timer
		(*lpdwTimerId)=::SetTimer(g_hWnd,
								  DUMMY_TIMER_ID,
								  50,
								  NULL);

		// check id
		if(*lpdwTimerId)
			AddWinResource

		// return focus to saver
		SetFocus(g_hWnd);

		// clear local closing flag
		bClosing=FALSE;

		// ok
		return;
	}*/
	
	// send close message
	SendMessage(g_hWnd,
				WM_CLOSE,
				NULL,
				NULL);

	// reset local closing flag
	bClosing=FALSE;
}

// ConfirmScreensaverPassword()

BOOL ConfirmScreensaverPassword(void)
{
	// version info
	OSVERSIONINFO osvi;

	// set version info size
	osvi.dwOSVersionInfoSize=sizeof(osvi);

	// get version info
	if(!GetVersionEx(&osvi))
	{
		DisplayErrorMessage("Unable to read Windows version information.");
		return(TRUE);
	}

	// do not continue if winnt
	if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
		return(TRUE);

	// registry key handle
	HKEY hKey;

	// key value data
	DWORD dwValType;
	DWORD dwValSize=sizeof(DWORD);

	// password flag
	DWORD dwUsePwd=NULL;

	// return value
	BOOL bResult=TRUE;

	// open password flag key
	if(RegOpenKeyEx(HKEY_CURRENT_USER,
					"Control Panel\\Desktop",
					0,
					KEY_READ,
					&hKey)==ERROR_SUCCESS)
	{
		// read value
		RegQueryValueEx(hKey,
						"ScreenSaveUsePassword",
						NULL,
						&dwValType,
						(LPBYTE)&dwUsePwd,
						&dwValSize);

		// close key
		RegCloseKey(hKey);
	}

	// check flag
	if(!dwUsePwd)
		return(TRUE);
	
	// load password.cpl
	HINSTANCE hPwdCpl=LoadLibrary("password.cpl");

	// check handle
	if(!hPwdCpl)
		return(TRUE);
	else
		AddWinResource

	// define prototype
	typedef BOOL (WINAPI *VERIFYSCREENSAVEPWD) (HWND);

	// cast pointer to funtion
	VERIFYSCREENSAVEPWD VerifyScreenSavePwd=(VERIFYSCREENSAVEPWD)GetProcAddress(hPwdCpl,
																			    "VerifyScreenSavePwd");

	// execute dialog box
	if(VerifyScreenSavePwd)
		bResult=VerifyScreenSavePwd(g_hWnd);

	// free password.cpl
	if(FreeLibrary(hPwdCpl))
		RemoveWinResource

	// return result
	return(bResult);
}

// ChangeScreensaverPassword()

void ChangeScreensaverPassword(HWND hParentWnd)
{
ANTIHACK_4
	
	// version info
	OSVERSIONINFO osvi;

	// set version info size
	osvi.dwOSVersionInfoSize=sizeof(osvi);

	// get version info
	if(!GetVersionEx(&osvi))
	{
		DisplayErrorMessage("Unable to read Windows version information.");
		return;
	}

	// do not continue if winnt
	if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
		return;

	// validate window handle
	if(hParentWnd==INVALID_HANDLE_VALUE)
		hParentWnd=GetDesktopWindow();

	// load mpr.dll
	HINSTANCE hMprDll=LoadLibrary("mpr.dll");

	// check handle
	if(!hMprDll)
		return;
	else
		AddWinResource;

	// define prototype
	typedef void (WINAPI *PWDCHANGEPASSWORDA) (LPSTR,HWND,UINT,UINT);

	// cast pointer to funtion
	PWDCHANGEPASSWORDA PwdChangePasswordA=(PWDCHANGEPASSWORDA)GetProcAddress(hMprDll,
																			 "PwdChangePasswordA");

	// execute dialog box
	if(PwdChangePasswordA)
		PwdChangePasswordA("SCRSAVE",
						   hParentWnd,
						   NULL,
						   NULL);

	// free mpr.dll
	if(FreeLibrary(hMprDll))
		RemoveWinResource;
}

#ifdef SHAREWARE_MODE
// RunStandAlonePurchDlg()

void RunStandAlonePurchDlg(void)
{
	// font
	CFont* lpFont=NULL;

	// perform req'd init
	if(InitMainSheet(TRUE))
	{
		// create font object
		AllocClassObject(lpFont,
						 CFont);

		// check new object
		if(lpFont)
		{
			// create font
			if(lpFont->CreatePointFont(80,
									   "MS Shell Dlg"))
			{
				// create lc fonts
				CreateListControlFonts(NULL,
									   lpFont);
			}
			else if(lpFont->CreatePointFont(80,
										    "MS Sans Serif"))
			{
				// create lc fonts
				CreateListControlFonts(NULL,
									   lpFont);
			}
		}

		// run dialog
		ShowPurchaseDlg();

		// release font
		FreeClassObject(lpFont);
	}

	// perform release
	ReleaseMainSheet();
}
#endif

// InitScreensaverMode()

BOOL InitScreensaverMode(void)
{
	// lock application
	if(!LockApplication(ApplicationID(APID_RUNPS),
						WND_PBTITLE,
						(LPSTR)ApplicationID(APID_RUNPS),
						TRUE))
		return(FALSE);

	// load preferences
	if(!LoadPreferences())
		return(FALSE);

	LockGlobalMsg()

	// copy install path
	strcpy(g_lpMsg,
		   g_lpInstPath);

	// add error log filename
	strcat(g_lpMsg,
		   "\\errorlog.txt");

	UnlockGlobalMsg()

	// initialize error log
	g_lpErrorLog->Init(g_lpMsg,
					   g_nErrorLogLines);

	// set record mode
	g_lpErrorLog->SetLogMode(g_bKeepErrorLog);

	// output error log header
	g_lpErrorLog->AddDivider(104);
	g_lpErrorLog->AddString("INIT","ProSaver Screensaver Manager copyright © 2006 WaveBreak Software.");
	g_lpErrorLog->AddString("INIT","Starting initialization ...");
	g_lpErrorLog->Dump();

	// changed my mind
	/*// check for defrag
	if(IsDefragRunning())
	{
		DisplayInfoMessage("Windows Disk Defragmenter has been detected.\nScreensaver execution has been blocked.");
		return(FALSE);
	}*/

	// init splash screen
	if(!InitSplashScreen())
		return(FALSE);

#ifdef SHAREWARE_MODE
	// get trial days
	g_dwTrialDays=GetTrialDaysRemaining();
#else
	// reset leftover timestamps
	ResetTimeStamps();
#endif

	// init run window
	if(!InitRunPSWindow())
		return(FALSE);

	// init saver hook
	if(!InitSaverHookProc())
		return(FALSE);

	// init audio support
	if(!InitAudioSupport(FALSE,
						 TRUE))
	{
		// alert user
		DisplayErrorMessage("Failed to initialize audio support.\n\nAudio playback will not be available.",
							NULL,
							FALSE);
	}

	// save & half master volume
	MasterVolume(MV_SAVE);
	MasterVolume(MV_HALF);

	// output log lines
	g_lpErrorLog->AddString("INIT","Initialization completed successfully.");
	g_lpErrorLog->Dump();

	// wait for splash screen
	WaitForSplashScreen();

	// ok
	return(TRUE);
}

// ExecScreensaverMode()

void ExecScreensaverMode(void)
{
	// output log lines
	g_lpErrorLog->AddString("EXEC","Beginning program execution ...");
	g_lpErrorLog->Dump();

	// process messages
	ProcessScreensaverMessages();

	// output log lines
	g_lpErrorLog->AddString("EXEC","Program execution complete.");
	g_lpErrorLog->Dump();
}

// ReleaseScreensaverMode()

void ReleaseScreensaverMode(void)
{
	// output log lines
	g_lpErrorLog->AddString("CLOSE","Beginning application shutdown ...");
	g_lpErrorLog->Dump();

	// restore master volume
	MasterVolume(MV_RESTORE);

	// release audio support
	ReleaseAudioSupport();
	DXAudioRelease();
	
	// release saver hook
	ReleaseSaverHookProc();

	// release main window
	ReleaseRunPSWindow();

	// release splash screen
	ReleaseSplashScreen();

	// keep tsr running
	if(!IsTSRActive())
		RestartTSR();

	// release install path
	FreeMem((LPVOID*)&g_lpInstPath);

	// complete error log
	g_lpErrorLog->AddString("CLOSE","Application shutdown complete.");
	g_lpErrorLog->AddString("CLOSE","Thank you for using ProSaver Screensaver Manager.");
	g_lpErrorLog->AddDivider(104);
	g_lpErrorLog->Dump();

	// unlock application
	UnlockApplication();
}

#ifdef SHAREWARE_MODE
// CPurchDlg::OnShowWindow()

void CPurchDlg::OnShowWindow(BOOL bShow,
							 UINT nStatus)
{
	// check flag
	if(bShow)
	{
		// play sound
		PlaySound(FORCE_DEFSND);

		// highlight window
		HighlightWindow(m_hWnd);
	}
}
#endif

// WaitForSplashScreen()

void WaitForSplashScreen(void)
{
	// check window object
	if(g_lpSplashWnd)
	{
		// check window
		if(IsWindow(g_lpSplashWnd->m_hWnd))
		{
			// check recorded time
			if(g_dwSplashTime!=0)
			{
				// check current time
				while(GetTickCount()<(g_dwSplashTime+SPLASH_DELAY))
				{
					// wait for it...
					Sleep(100);
				}
			}

			// destroy splash window
			if(g_lpSplashWnd->DestroyWindow())
				RemoveWinResource

			// clear recorded time
			g_dwSplashTime=0;
		}
	}
}

// CMainPropSheet::OnWmHotkey()

LRESULT CMainPropSheet::OnWmHotkey(WPARAM wParam,
								   LPARAM lParam)
{
	// check hotkey
	switch(wParam)
	{
	case(ID_NEXTSVRHKY):  OnNextSaverHky(); break;
	case(ID_NEXTSONGHKY): OnNextSongHky();  break;
	case(ID_VOLUPHKY):    OnVolUpHky();     break;
	case(ID_VOLDOWNHKY):  OnVolDownHky();   break;
	case(ID_VOLMUTEHKY):  OnVolMuteHky();   break;
	}

	// ok
	return(NULL);
}

// IsDefragRunning()

BOOL IsDefragRunning(void)
{
	// check for window
	if(FindWindow("MMCMainFrame",
				  "Disk Defragmenter"))
		return(TRUE);
	else
		return(FALSE);
}

// OpenProSaverConfig()

BOOL OpenProSaverConfig(void)
{
	LockGlobalErrorMsg()

	// check for install path
	if(!g_lpInstPath)
	{
		// load prefs
		if(!LoadPreferences())
		{
			UnlockGlobalErrorMsg()
			return(FALSE);
		}

		// copy path
		strcpy(g_lpErrorMsg,
			   g_lpInstPath);

		// release install path
		FreeMem((LPVOID*)&g_lpInstPath);
	}
	else
	{
		// copy path
		strcpy(g_lpErrorMsg,
			   g_lpInstPath);
	}

	LockGlobalMsg()

	// create command line
	strcpy(g_lpMsg,"\"");
	strcat(g_lpMsg,g_lpErrorMsg);
	strcat(g_lpMsg,"\\ProSaver.exe\" /c");

	UnlockGlobalErrorMsg()

	// open config box
	BOOL bRet=ExecuteExternalApp(g_lpMsg,
								 (LPCSTR)NULL);

	UnlockGlobalMsg()

	// ok
	return(bRet);
}

#ifdef SHAREWARE_MODE
// RunExternalPurchDlg()

BOOL RunExternalPurchDlg(void)
{
	LockGlobalErrorMsg()

	// check for install path
	if(!g_lpInstPath)
	{
		// load prefs
		if(!LoadPreferences())
		{
			UnlockGlobalErrorMsg()
			return(FALSE);
		}

		// copy path
		strcpy(g_lpErrorMsg,
			   g_lpInstPath);

		// release install path
		FreeMem((LPVOID*)&g_lpInstPath);
	}
	else
	{
		// copy path
		strcpy(g_lpErrorMsg,
			   g_lpInstPath);
	}

	LockGlobalMsg()

	// create command line
	strcpy(g_lpMsg,"\"");
	strcat(g_lpMsg,g_lpErrorMsg);
	strcat(g_lpMsg,"\\ProSaver.exe\" w~1000");

	UnlockGlobalErrorMsg()

	// open config box
	BOOL bRet=ExecuteExternalApp(g_lpMsg,
								 (LPCSTR)NULL);

	UnlockGlobalMsg()

	// ok
	return(bRet);
}

// CheckTrialDays()

void CheckTrialDays(void)
{
	// check days remaining
	if(g_dwTrialDays<=15)
	{
		if(g_dwTrialDays<=7)
		{
			if(g_dwTrialDays<=3)
			{
				if(g_dwTrialDays<=2)
				{
					if(g_dwTrialDays<=1)
					{
						if(g_dwTrialDays==0)
						{
							// show dialog
							ShowTrialDays(NULL);
						}
						else
						{
							// show dialog
							ShowTrialDays("Misc_TFlag1");
						}
					}
					else
					{
						// show dialog
						ShowTrialDays("Misc_TFlag2");
					}
				}
				else
				{
					// show dialog
					ShowTrialDays("Misc_TFlag3");
				}
			}
			else
			{
				// show dialog
				ShowTrialDays("Misc_TFlag4");
			}
		}
		else
		{
			// show dialog
			ShowTrialDays("Misc_TFlag5");
		}
	}
}
#endif

// ShowHelp()

BOOL ShowHelp(UINT nIDCtrl,
			  CWnd* lpCtrlWnd)
{
	// position
	CPoint pt;

	// window rect
	CRect rWnd;

	// set default text
	LPSTR lpText=NULL;
	
	// reset link data
	DWORD dwLinkData=NULL;

	// macro for help ids
	#define HelpCase(id,text,link) case(id): lpText=(text); dwLinkData=(DWORD)(link); break;

	// check id
	switch(nIDCtrl)
	{
	HelpCase(IDC_MAINSHEET,"\\b\\ul ProSaver Main Window\\ul0\\b0\\par\\par Click on one of the tabs at the top of the window to display its contents.\\par\\par\\b Screensavers Tab:\\b0  View your available screensavers and create/edit the current playlist.\\par\\par\\b Playback Options Tab:\\b0  Select options for displaying screensavers in the current playlist.","ProSaverMainWindow.htm");

	HelpCase(IDC_DLGOKBTN,"Click this button to close the dialog box and save any changes you have made.",NULL);
	HelpCase(IDC_DLGCANCELBTN,"Click this button to close the dialog box without saving any changes you have made.",NULL);
	HelpCase(IDC_DLGAPPLYBTN,"Click this button to save all the changes you have made without closing the dialog box.",NULL);
	HelpCase(IDC_DEFOKBTN,"Click this button to close the \\b ProSaver Main Window\\b0  and save any changes you have made.",NULL);
	HelpCase(IDC_DEFCANCELBTN,"Click this button to close the \\b ProSaver Main Window\\b0  without saving any changes you have made.",NULL);
	HelpCase(IDC_DEFAPPLYBTN,"Click this button to save all the changes you have made without closing the \\b ProSaver Main Window\\b0 .",NULL);

	HelpCase(IDC_GHELPBTN,"Click this button to display the \\b ProSaver Screensaver Manager\\b0  Help file.",NULL);
	HelpCase(IDC_ABOUTBTN,"Click this button to display information about this version of \\b ProSaver Screensaver Manager\\b0 .",NULL);
	HelpCase(IDC_PREFSBTN,"Click this button to open the \\b Preferences Window\\b0 .",NULL);
	HelpCase(IDC_PURCHBTN,"Click this button to open the \\b How to Order Window\\b0 .",NULL);

	HelpCase(IDC_SAVERLIST,"\\b\\ul Screensaver List\\ul0\\b0\\par\\par This list displays all of your available screensavers.","ScreensaverList.htm");
	HelpCase(IDC_CLEARSELBTN,"Click this button to clear the current selection from the \\b Screensaver List\\b0 .",NULL);
	HelpCase(IDC_ADDSAVERBTN,"Click this button to add the current selection to the \\b Screensaver Playlist\\b0 .",NULL);

	HelpCase(IDC_CURRPLIST,"\\b\\ul Screensaver Playlist\\ul0\\b0\\par\\par This list displays the screensavers that will be shown by the \\b ProSaver Playback Window\\b0  the next time your screensaver starts.","ScreensaverPlaylist.htm");
	HelpCase(IDC_PLISTSORTCBX,"Select an item from this list to sort the \\b Screensaver Playlist\\b0 .",NULL);
	HelpCase(IDC_PLISTUPBTN,"Click this button to move the current \\b Screensaver Playlist\\b0  selection up one position.",NULL);
	HelpCase(IDC_PLISTDOWNBTN,"Click this button to move the current \\b Screensaver Playlist\\b0  selection down one position.",NULL);
	HelpCase(IDC_PLISTTOPBTN,"Click this button to move the current \\b Screensaver Playlist\\b0  selection to the top of the list.",NULL);
	HelpCase(IDC_PLISTBOTTOMBTN,"Click this button to move the current \\b Screensaver Playlist\\b0  selection to the bottom of the list.",NULL);
	HelpCase(IDC_PLISTDELBTN,"Click this button to delete the current selection from the \\b Screensaver Playlist\\b0 .",NULL);
	HelpCase(IDC_PLISTCLRBTN,"Click this button to delete all items from the \\b Screensaver Playlist\\b0 .",NULL);
	HelpCase(IDC_PLISTSAVEBTN,"Click this button to save the current \\b Screensaver Playlist\\b0  to disk.",NULL);
	HelpCase(IDC_PLISTLOADBTN,"Click this button to load a previously saved \\b Screensaver Playlist\\b0  from disk.",NULL);

	HelpCase(IDC_SAVERINFO,"\\b\\ul Screensaver Info Box\\ul0\\b0\\par\\par This box displays information about the currently selected screensaver, including name, theme, rating, background music, and description.","ScreensaverInfoBox.htm");
	HelpCase(IDC_SETTINGSBTN,"Click this button to open the Settings dialog box for the selected screensaver.",NULL);
	HelpCase(IDC_PREVIEWBTN,"Click this button to run a full preview of the selected screensaver.",NULL);
	HelpCase(IDC_EDITINFOBTN,"Click this button to open the \\b Screensaver Info Editor\\b0  for the selected screensaver.",NULL);
	HelpCase(IDC_SHOWPREVIEWCHK,"Check this box to turn on the \\b Mini-Preview Window\\b0 . Clear the box to turn it off.",NULL);
	HelpCase(IDC_PREVIEWWND,"\\b\\ul Mini-Preview Window\\ul0\\b0\\par\\par This window displays a mini-preview for the selected screensaver.","MiniPreviewWindow.htm");

	HelpCase(IDC_THEMESELBOX,"Use this list to select a theme for the current screensaver.","ThemesAndRatings.htm");
	HelpCase(IDC_EDITTHEMESBTN,"Click this button to open the \\b Themes Manager\\b .",NULL);
	HelpCase(IDC_RATINGSELBOX,"Use this list to select a rating for the current screensaver.","ThemesAndRatings.htm");
	HelpCase(IDC_EDITHELPBTN,"Click this button to display the \\b Screensaver Info Editor\\b0  Help topic.",NULL);
	HelpCase(IDC_MUSICSELBOX,"This box displays the selected background music (single file or playlist) for the current screensaver.","MusicOptions.htm");
	HelpCase(IDC_MUSICBROWSEBTN,"Click this button to open the \\b Change Music Dialog\\b0 , which allows you to change the background music for this screensaver.",NULL);
	HelpCase(IDC_MUSICCYCLERAD,"Select this option to play songs from the playlist in order during screensaver playback.",NULL);
	HelpCase(IDC_MUSICSHUFFLERAD,"Select this option to play songs randomly from the playlist during screensaver playback.",NULL);
	HelpCase(IDC_SAVERDESC,"Use this box to enter a description for the current screensaver, up to 1000 characters.","ScreensaverDescription.htm");
	HelpCase(IDC_DISABLEPREVCHK,"Check this box to turn off the \\b Mini-Preview Window\\b0  for this screensaver only.\\par\\par See the Help topic for more information.","TurnOffPreviewBox.htm");

	HelpCase(IDC_THEMESLIST,"\\b\\ul Themes List \\ul0\\b0\\par\\par This list displays all of the themes that are available to be assigned to screensavers.\\par\\par Click the \\b New\\b0  button to add a new theme to the list.","ThemesList.htm");
	HelpCase(IDC_NEWTHEMEBTN,"Click this button to add a new theme to the \\b Themes List\\b0 .",NULL);
	HelpCase(IDC_DELTHEMEBTN,"Click this button to delete the currently selected theme(s) from the \\b Themes List\\b0 .",NULL);
	HelpCase(IDC_RENAMETHEMEBTN,"Click this button to rename the currently selected theme in the \\b Themes List\\b0 .",NULL);
	HelpCase(IDC_DEFTHEMESBTN,"Click this button to reset the \\b Themes List\\b0  to the ProSaver default themes.",NULL);
	HelpCase(IDC_THEMESHELPBTN,"Click this button to display the \\b Themes Manager\\b0  Help topic.",NULL);

	HelpCase(IDC_NEWTHEMEEDT,"Type a new theme to be added to the \\b Themes List\\b0  and click the \\b OK\\b0  button.","NewThemeDialog.htm");
	HelpCase(IDC_RENAMETHEMEEDT,"Type a new name to replace the selected theme in the \\b Themes List\\b0  and click the \\b OK\\b0  button.","RenameThemeDialog.htm");

	HelpCase(IDC_LOADAUDFILEBTN,"Click this button to select an audio file to be used as background music for the current screensaver.",NULL);
	HelpCase(IDC_LOADPLISTBTN,"Click this button to select a \\b ProSaver Audio Playlist\\b0  to be used as background music for the current screensaver.",NULL);
	HelpCase(IDC_CLEARMUSBTN,"Click this button to select no background music for the current screensaver.",NULL);
	HelpCase(IDC_EDITAUDIOBTN,"Click this button to open the \\b Music Manager\\b0 . From here, you can create and edit audio playlists for use as background music in your screensavers.",NULL);
	HelpCase(IDC_CHGMUSHELPBTN,"Click this button to open the \\b Change Music Dialog\\b0  Help topic.",NULL);

	HelpCase(IDC_ONESVRRAD,"Select this option to show only one screensaver each time the \\b ProSaver Playback Window\\b0  is displayed.",NULL);
	HelpCase(IDC_MULTISVRRAD,"Select this option to display screensavers from your \\b Screensaver Playlist\\b0  as a slideshow (one after another) during screensaver playback.",NULL);
	HelpCase(IDC_SHOWSVREDT,"Use this box to enter the number of mintues (1-120) to display each screensaver during slideshow playback.",NULL);
	HelpCase(IDC_SHOWSVRSPIN,"Use this box to enter the number of mintues (1-120) to display each screensaver during slideshow playback.",NULL);

	HelpCase(IDC_SVRCYCLERAD,"Select this option to show screensavers from your \\b Screensaver Playlist\\b0  in the exact order that they appear in the list during playback.",NULL);
	HelpCase(IDC_SVRSHUFFLERAD,"Select this option to show random screensavers from your \\b Screensaver Playlist\\b0  during playback.",NULL);

	HelpCase(IDC_ENABLEHKEYSCBX,"Check this box to turn on \\b Screensaver Hotkeys\\b0 , which are used for quick and easy access to the most important features of \\b ProSaver Screensaver Manager\\b0 .","ScreensaverHotkeys.htm");
	HelpCase(IDC_STARTSVRHKY,"Use this box to enter a key combination that can be used to immediately start the \\b ProSaver Playback Window\\b0 .",NULL);
	HelpCase(IDC_SKIPSVRHKY,"Use this box to enter a key combination that can be used to skip ahead to the next screensaver in your \\b Screensaver Playlist\\b0  during playback.",NULL);
	HelpCase(IDC_OPENPSHKY,"Use this box to enter a key combination that can be used to immediately open the \\b ProSaver Main Window\\b0 .",NULL);

	HelpCase(IDC_CLRSCREENCBX,"Check this box to cause the screen to be cleared before running screensavers during playback.",NULL);
	HelpCase(IDC_NOMUSICCBX,"Check this box to temporarily disable all background music for your screensavers.\\par\\par This option is useful because it allows you to turn off ProSaver music output without disturbing any of your playlists or settings, so that you can easily turn music back on at a later time.",NULL);
	HelpCase(IDC_OPENTHEMESBTN,"Click this button to open the \\b Themes Manager\\b0 .",NULL);
	HelpCase(IDC_OPENAUDIOBTN,"Click this button to open the \\b Music Manager\\b0 .",NULL);

	HelpCase(IDC_ADVWARNTXT,"This is the \\b Advanced Settings\\b0  area.\\par\\par Click the \\b Show Advanced Options\\b0  button to display these settings.","AdvancedSettings.htm");
	HelpCase(IDC_SHOWADVBTN,"Click this button to display the \\b Advanced Settings\\b0 .",NULL);

	HelpCase(IDC_SEARCHLIST,"\\b\\ul Search Paths List\\ul0\\b0\\par\\par This list displays locations that will be scanned for available screensavers.","ScreensaverSearchPaths.htm");
	HelpCase(IDC_ADDPATHBTN,"Click this button to select a path to add to the \\b Search Paths List\\b0 .",NULL);
	HelpCase(IDC_CHANGEPATHBTN,"Click this button to change the selected path in the \\b Search Paths List\\b0 .",NULL);
	HelpCase(IDC_DELETEPATHBTN,"Click this button to delete the selected path from the \\b Search Paths List\\b0 .",NULL);

	HelpCase(IDC_SYSTRAYCHK,"Select this option to display a small \\b ProSaver Screensaver Manager\\b0  icon in your system tray.",NULL);
	HelpCase(IDC_KEEPCURCHK,"Select this option to be notified when ProSaver is not set as your current screensaver.\\par\\par\\b ProSaver Screensaver Manager\\b0  must be set as your current Windows screensaver in order to function properly. See the Help topic for more information.","ProSaverAndWindowsControlPanel.htm");
	HelpCase(IDC_HIDEADVCHK,"Select this option to automatically hide the \\b Advanced Settings\\b0  when ProSaver first opens.",NULL);

	HelpCase(IDC_ERRORLOGCHK,"Select this option to record an error log during screensaver playback.\\par\\par This is the only way to be notified of error messages during playback. See the Help topic for more information.","ErrorLogging.htm");
	HelpCase(IDC_MAXLINESEDT,"Use this box to enter the number of lines (50-400) to be kept in the \\b Error Log\\b0 .",NULL);
	HelpCase(IDC_MAXLINESSPIN,"Use this box to enter the number of lines (50-400) to be kept in the \\b Error Log\\b0 .",NULL);
	HelpCase(IDC_ERRORLOGBTN,"Click this button to view the current contents of the \\b Error Log\\b0 .",NULL);

	HelpCase(IDC_RESETMSGBTN,"Click this button to restore all messages that you have previously chosen not to display.\\par\\par See the Help topic for more information.","OtherOptionsAdv.htm");
	HelpCase(IDC_HIDEADVBTN,"Click this button to hide the \\b Advanced Settings\\b0 .",NULL);

	HelpCase(IDC_HISTORYCBX,"This list displays a tree-like view of the current folder in the \\b Audio File List\\b0 .\\par\\par Use this list to easily change disk drives or folders.",NULL);
	HelpCase(IDC_FILEBACKBTN,"Click this button to display the previous folder in the \\b Audio File List\\b0 .",NULL);
	HelpCase(IDC_FILEUPBTN,"Click this button to display the parent of the current folder in the \\b Audio File List\\b0 .",NULL);
	HelpCase(IDC_FILELIST,"\\b\\ul Audio File List\\ul0\\b0\\par\\par This list is used for navigating your computer's folders for the purpose of adding music files to the \\b Audio Playlist\\b0 .","AudioFileList.htm");
	HelpCase(IDC_FILETYPECBX,"Use this list to choose what types of audio files to display in the \\b Audio File List\\b0 .",NULL);
	HelpCase(IDC_CLEARAUDIOSELBTN,"Click this button to clear the current selection from the \\b Audio File List\\b0 .",NULL);
	HelpCase(IDC_ADDAUDIOFILEBTN,"Click this button to add the current selection to the \\b Audio Playlist\\b0 .",NULL);

	HelpCase(IDC_AUDIOPLIST,"\\b\\ul Audio Playlist\\ul0\\b0\\par\\par This list displays a collection of audio files that can be saved to disk and then used as background music for any of your screensavers.","AudioPlaylist.htm");
	HelpCase(IDC_AUDIOPLISTSORTCBX,"Select an item from this list to sort the \\b Audio Playlist\\b0 .",NULL);
	HelpCase(IDC_AUDIOPLISTUPBTN,"Click this button to move the current \\b Audio Playlist\\b0  selection up one position.",NULL);
	HelpCase(IDC_AUDIOPLISTDOWNBTN,"Click this button to move the current \\b Audio Playlist\\b0  selection down one position.",NULL);
	HelpCase(IDC_AUDIOPLISTTOPBTN,"Click this button to move the current \\b Audio Playlist\\b0  selection to the top of the list.",NULL);
	HelpCase(IDC_AUDIOPLISTBOTTOMBTN,"Click this button to move the current \\b Audio Playlist\\b0  selection to the bottom of the list.",NULL);
	HelpCase(IDC_AUDIOPLISTDELBTN,"Click this button to delete the current selection from the \\b Audio Playlist\\b0 .",NULL);
	HelpCase(IDC_AUDIOPLISTCLRBTN,"Click this button to delete all items from the \\b Audio Playlist\\b0 .",NULL);
	HelpCase(IDC_AUDIOPLISTSAVEBTN,"Click this button to save the current \\b Audio Playlist\\b0  to disk.",NULL);
	HelpCase(IDC_AUDIOPLISTLOADBTN,"Click this button to load a previously saved \\b Audio Playlist\\b0  from disk.",NULL);

	HelpCase(IDC_AUDIOINFO,"\\b\\ul Audio File Info\\ul0\\b0\\par\\par This box displays information about the audio file that is currently selected in either the \\b Audio File List\\b0  or the \\b Audio Playlist\\b0 .","AudioFileInfo.htm");
	HelpCase(IDC_PLAYBTN,"Click this button to play the selected audio file from its current position.",NULL);
	HelpCase(IDC_PAUSEBTN,"Click this button to pause the currently playing audio file.",NULL);
	HelpCase(IDC_STOPBTN,"Click this button to stop the currently playing audio file and set the file position to the beginning.",NULL);
	HelpCase(IDC_FULLREWBTN,"Click this button to set the selected audio file's position to the beginning.",NULL);
	HelpCase(IDC_REWBTN,"Click this button to move the selected audio file's positon back a small increment.",NULL);
	HelpCase(IDC_FWDBTN,"Click this button to move the selected audio file's positon forward a small increment.",NULL);
	HelpCase(IDC_AUDIOPOSSLD,"Use this slider to change the selected audio file's current position.",NULL);

	HelpCase(IDC_ENABLEPBCCHK,"Select this option to enable \\b Playback Controls\\b0  during screensaver playback.\\par\\par Please note that these controls only work during screensaver playback, and not in the \\b Music Manager\\b0 .","PlaybackControlsBox.htm");
	HelpCase(IDC_NEXTHKY,"Use this box to enter a key combination to be used during screensaver playback that will skip to the next audio file in the playlist.",NULL);
	HelpCase(IDC_VOLUPHKY,"Use this box to enter a key combination to be used during screensaver playback that will increase the playback volume.",NULL);
	HelpCase(IDC_VOLDNHKY,"Use this box to enter a key combination to be used during screensaver playback that will decrease the playback volume.",NULL);
	HelpCase(IDC_MUTEHKY,"Use this box to enter a key combination to be used during screensaver playback that will mute the playback volume.",NULL);

	HelpCase(IDC_WINSYNTHRAD,"Select this option to use the default Windows synthesizer for MIDI file playback.\\par\\par While this is sufficient for hearing the music, it is recommended that you use the \\b DirectX Audio\\b0  synthesizer for improved sound quality.",NULL);
	HelpCase(IDC_DXSYNTHRAD,"Select this option to use the \\b DirectX Audio\\b0  synthesizer for MIDI file playback.\\par\\par This is the recommended option for the best sound quality.",NULL);
	HelpCase(IDC_REVERBCHK,"Select this option to add an echo-like quality to synthesized music (MIDI files) during screensaver playback.\\par\\par This option is only available with the \\b DirectX Audio\\b0  synthesizer.",NULL);
	HelpCase(IDC_CHORUSCHK,"Select this option to add a richer, fuller sound to synthesized music (MIDI files) during screensaver playback.\\par\\par This option is only available with the \\b DirectX Audio\\b0  synthesizer.",NULL);

	HelpCase(IDC_MUSMANHELPBTN,"Click this button to display the \\b Music Manager\\b0  Help topic.",NULL);
	HelpCase(IDC_INSTALLDXBTN,"Click this button to download and install DirectX 8.1, which is required in order to use the \\b DirectX Audio\\b0  synthesizer for music playback.",NULL);

	HelpCase(IDC_PLAYSFXCHK,"Select this option to play small sound effects during your interaction with \\b ProSaver Screensaver Manager\\b0 .",NULL);
	HelpCase(IDC_SHOWTOOLTIPSCHK,"Select this option to display a small popup over icon buttons to remind you of the button's function.",NULL);
	HelpCase(IDC_SPLASHSCRNCHK,"Select this option to briefly display a small window when the \\b ProSaver Main Window \\b0  is opened and before screensaver playback begins.",NULL);
	HelpCase(IDC_SAVERLISTDETCHK,"Select this option to display the \\b Screensaver List\\b0  in \\ul Details Mode\\ul0 . Otherwise, the list will be displayed in \\ul List Mode\\ul0 .",NULL);
	HelpCase(IDC_RATINGIMGSCHK,"Select this option to display ratings in the \\b Screensaver List\\b0  as star images. Otherwise, ratings will be displayed as text.",NULL);
	HelpCase(IDC_SLISTPOPUPCHK,"Select this option to display a small popup containing additional information about a screensasver in the \\b Screensaver List\\b0 .\\par\\par This option is only used when the list is in \\ul List Mode\\ul0 .",NULL);
	HelpCase(IDC_PLISTPOPUPCHK,"Select this option to display a small popup containing additional information about items in a playlist.",NULL);
	HelpCase(IDC_PREFSHELPBTN,"Click this button to display the \\b Preferences Window\\b0  Help topic.",NULL);

	HelpCase(IDC_WBSOFTBMP,"Click here to visit the \\b WaveBreak Software\\b0  web site.",NULL);
	HelpCase(IDC_ASPLOGOBMP,"Click here to visit the \\b Association of Shareware Professionals\\b0  website.",NULL);
	HelpCase(IDC_VIEWLICBTN,"Click this button to view the \\b End-User License Agreement\\b0  for this program.",NULL);
	HelpCase(IDC_VIEWREADMEBTN,"Click this button to view the \\b ProSaver Screensaver Manager\\b0  readme file, which contains additional information about the software.",NULL);

	HelpCase(IDC_PSBUYBMP,"Click here to be taken to our \\b SECURE\\b0  online order form.",NULL);
	HelpCase(IDC_ORDERBTN,"Click here to be taken to our \\b SECURE\\b0  online order form.",NULL);
	HelpCase(IDC_MAILFORMBTN,"Click here to view and print a mail-order form for this software.",NULL);
	}

	// check for text
	if(lpText)
	{
		// get cursor position
		GetCursorPos(&pt);

		// move point up
		pt.y-=16;

		// get nearest point
		GetNearestPointInWnd(&pt,
							 lpCtrlWnd,
							 8);

		// release existing window
		ReleaseContextHelpWnd();

		// create new window (with foreground as parent)
		if(InitContextHelpWnd())
		{
			// update window text
			UpdateContextHelpWnd(lpText,
								 dwLinkData);

			// show help window
			ShowContextHelpWnd(pt.x,
							   pt.y);

			// ok
			return(TRUE);
		}
		else
		{
			// reset id (to show default help)
			nIDCtrl=NULL;
		}
	}

	// check id and show topic
	switch(nIDCtrl)
	{
	// dialog boxes
	case(IDC_EDITSAVERDLG):   ShowHelpTopic((DWORD)"ScreensaverInfoEditor.htm"); break;
	case(IDC_EDITTHEMESDLG):  ShowHelpTopic((DWORD)"ThemesManager.htm");         break;
	case(IDC_CHGMUSICDLG):    ShowHelpTopic((DWORD)"ChangeMusicDialog.htm");     break;
	case(IDC_MUSICMGRDLG):    ShowHelpTopic((DWORD)"MusicManager.htm");          break;
	case(IDC_PREFERENCESDLG): ShowHelpTopic((DWORD)"PreferencesWindow.htm");     break;

	// all others
	default: ShowHelpTopic((DWORD)"AboutThisSoftware.htm"); break;
	}

	// ok
	return(TRUE);
}

// InitContextHelpWnd()

BOOL InitContextHelpWnd(HWND hParentWnd)
{
	// create window object
	AllocClassObject(g_lpContextHelpWnd,
					 CContextHelpWnd);

	// check object
	if(!g_lpContextHelpWnd)
		return(FALSE);

	// validate parent
	if(hParentWnd==NULL||
	   hParentWnd==(HWND)INVALID_HANDLE_VALUE)
		hParentWnd=::GetForegroundWindow();

	// create window
	if(!g_lpContextHelpWnd->CreateEx(WS_EX_TOPMOST,
									 AfxRegisterWndClass(CS_BYTEALIGNWINDOW|
														 CS_CLASSDC|
														 CS_SAVEBITS),
									 NULL,
									 WS_POPUP|
									 WS_CHILD,
									 0,0,
									 CHW_INITXSIZE,
									 CHW_INITYSIZE,
									 hParentWnd,
									 NULL))
	{
		DisplayErrorMessage("Unable to create context help window.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// ShowContextHelpWnd()

void ShowContextHelpWnd(int nXPos,
						int nYPos)
{
	// window rect
	CRect rWnd;

	// offset values
	int nXOfs;
	int nYOfs;

	// hide window first
	HideContextHelpWnd();

	// get current position
	g_lpContextHelpWnd->GetWindowRect(&rWnd);

	// compute offset values
	nXOfs=nXPos-rWnd.left;
	nYOfs=nYPos-rWnd.top;

	// adjust x-axis 1/3 left
	nXOfs-=rWnd.Width()/3;

	// move rectangle
	rWnd.OffsetRect(nXOfs,
					nYOfs);

	// keep it visible
	KeepRectsOnScreen(&rWnd);

	// move window
	g_lpContextHelpWnd->MoveWindow(&rWnd);

	// show window
	g_lpContextHelpWnd->ShowWindow(SW_SHOW);
}

// HideContextHelpWnd()

void HideContextHelpWnd(void)
{
	// hide window
	g_lpContextHelpWnd->ShowWindow(SW_HIDE);
}

// ReleaseContextHelpWnd()

void ReleaseContextHelpWnd(void)
{
	// check window
	if(g_lpContextHelpWnd)
		if(IsWindow(g_lpContextHelpWnd->m_hWnd))
		{
			// destroy window
			g_lpContextHelpWnd->DestroyWindow();
		}

	// free window object
	FreeClassObject(g_lpContextHelpWnd);
}

// CContextHelpWnd::OnLButtonDown()

void CContextHelpWnd::OnLButtonDown(UINT nFlags,
									CPoint point)
{
	// check for link
	if(dwSavedLinkData)
	{
		// convert point
		ClientToScreen(&point);

		// check link window
		if(IsPointInWindow(&point,
						   lpLinkTxt))
		{
			// show help
			ShowHelpTopic(dwSavedLinkData);
		}
	}

	// call base method
	CWnd::OnLButtonDown(nFlags,
						point);

	// destroy window
	DestroyWindow();
}

// CContextHelpWnd::OnKeyDown()

void CContextHelpWnd::OnKeyDown(UINT nChar,
								UINT nRepCnt,
								UINT nFlags)
{
	// check for link
	if(dwSavedLinkData)
	{
		// check for F1 key
		if(nChar==VK_F1)
		{
			// show help
			ShowHelpTopic(dwSavedLinkData);
		}
	}

	// call base method
	CWnd::OnKeyDown(nChar,
					nRepCnt,
					nFlags);

	// destroy window
	DestroyWindow();
}

// CContextHelpWnd::OnSysKeyDown()

void CContextHelpWnd::OnSysKeyDown(UINT nChar,
								   UINT nRepCnt,
								   UINT nFlags)
{
	// call base method
	CWnd::OnSysKeyDown(nChar,
					   nRepCnt,
					   nFlags);

	// destroy window
	DestroyWindow();
}

// CContextHelpWnd::OnKillFocus()

void CContextHelpWnd::OnKillFocus(CWnd* pNewWnd)
{
	// call base method
	CWnd::OnKillFocus(pNewWnd);

	// destroy window
	DestroyWindow();
}

// CContextHelpWnd::CContextHelpWnd()

CContextHelpWnd::CContextHelpWnd()
{
	// init values
	lpHelpTxt      =NULL;
	lpLinkTxt      =NULL;
	dwSavedLinkData=NULL;

	// call base method
	CWnd::CWnd();
}

// CContextHelpWnd::OnDestroy()

void CContextHelpWnd::OnDestroy(void)
{
	// release text windows
	FreeClassObject(lpHelpTxt);
	FreeClassObject(lpLinkTxt);

	// clear link data
	dwSavedLinkData=NULL;

	RemoveWinResource

	// call base method
	CWnd::OnDestroy();
}

// CContextHelpWnd::OnPaint()

void CContextHelpWnd::OnPaint(void)
{
	// paint struct
	PAINTSTRUCT ps;

	// begin paint
	CDC* lpDC=BeginPaint(&ps);

	// paint objects
	PaintWindow(lpDC);
	PaintShadow(lpDC);

	// end paint
	EndPaint(&ps);

	// redraw controls
	lpHelpTxt->RedrawWindow();
	lpLinkTxt->RedrawWindow();
}

// CContextHelpWnd::PaintWindow()

void CContextHelpWnd::PaintWindow(CDC* lpDC)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpDC)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"PaintWindow()",
							FALSE);
		return;
	}
#endif

	// window rect
	CRect rWnd;

	// set colors
	COLORREF clrBdr1=RGB(0,  0,  0);
	COLORREF clrBdr2=RGB(192,192,192);
	COLORREF clrBkg =GetSysColor(COLOR_INFOBK);

	// get client rect
	GetClientRect(&rWnd);

	// adjust for shadow
	rWnd.right -=CHW_SHADOWSIZE+1;
	rWnd.bottom-=CHW_SHADOWSIZE+1;

	// draw outer border
	lpDC->FillSolidRect(rWnd.left ,rWnd.top,   rWnd.right+1,1,            clrBdr1);
	lpDC->FillSolidRect(rWnd.left ,rWnd.bottom,rWnd.right+1,1,            clrBdr1);
	lpDC->FillSolidRect(rWnd.left ,rWnd.top,   1,           rWnd.bottom+1,clrBdr1);
	lpDC->FillSolidRect(rWnd.right,rWnd.top,   1,           rWnd.bottom+1,clrBdr1);

	// adjust rect
	rWnd.DeflateRect(1,1);

	// draw inner border
	lpDC->FillSolidRect(rWnd.left ,rWnd.top,   rWnd.right,1,              clrBdr2);
	lpDC->FillSolidRect(rWnd.left ,rWnd.bottom,rWnd.right,1,              clrBdr2);
	lpDC->FillSolidRect(rWnd.left ,rWnd.top,   1,           rWnd.bottom,  clrBdr2);
	lpDC->FillSolidRect(rWnd.right,rWnd.top,   1,           rWnd.bottom,  clrBdr2);

	// adjust rect
	rWnd.DeflateRect(1,1);

	// draw background
	lpDC->FillSolidRect(rWnd.left, rWnd.top,   rWnd.right-1,rWnd.bottom-1,clrBkg);
}

// CContextHelpWnd::PaintShadow()

void CContextHelpWnd::PaintShadow(CDC* lpDC)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpDC)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"PaintShadow()",
							FALSE);
		return;
	}
#endif

	// window rect
	CRect rWnd;

	// counters
	int nX;
	int nY;

	// get client rect
	GetClientRect(&rWnd);

	// draw right-side shadow
	for(nX=rWnd.right-CHW_SHADOWSIZE;nX<rWnd.right;nX++)
		for(nY=CHW_SHADOWSIZE;nY<rWnd.bottom;nY++)
			if((nX+nY)%2) lpDC->SetPixelV(nX,nY,RGB(0,0,0));

	// draw bottom shadow
	for(nX=CHW_SHADOWSIZE;nX<rWnd.right;nX++)
		for(nY=rWnd.bottom-CHW_SHADOWSIZE;nY<rWnd.bottom;nY++)
			if((nX+nY)%2) lpDC->SetPixelV(nX,nY,RGB(0,0,0));
}

// CContextHelpWndWnd::OnNotify()

BOOL CContextHelpWnd::OnNotify(WPARAM wParam,
							   LPARAM lParam,
							   LRESULT* pResult)
{
	// resize data
	REQRESIZE* lpRR;

	// window rect
	CRect rWnd;

	// get notification data
	LPNMHDR lpNMHDR=(LPNMHDR)lParam;

	// check code
	if(lpNMHDR->code==EN_REQUESTRESIZE)
	{
		// get resize data
		lpRR=(REQRESIZE*)lpNMHDR;

		// resize control
		lpHelpTxt->MoveWindow(&lpRR->rc);

		// get parent window
		GetWindowRect(&rWnd);

		// compute parent size
		rWnd.bottom=(lpRR->rc.bottom-lpRR->rc.top)+CHW_SHADOWSIZE+(CHW_TMARGINSIZE+2)+(CHW_BMARGINSIZE+2)+1;

		// resize parent
		MoveWindow(&rWnd);
	}

	// call base method
	return(CWnd::OnNotify(wParam,
						  lParam,
						  pResult));
}

// UpdateContextHelpWnd()

BOOL UpdateContextHelpWnd(LPSTR lpText,
						  DWORD dwLinkData)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpText)
	{
		DisplayErrorMessage("Invalid string value.",
							"UpdateContextHelpWnd()",
							FALSE);
		return(FALSE);
	}
#endif

	// edit stream info
	EDITSTREAM es;

	// window rect
	CRect rWnd;

	LockGlobalLongMsg()
	
	// output rtf header
	strcpy(g_lpLongMsg,"{\\rtf1\\ansi\\deff0"
					   "{\\fonttbl{\\f0\\fnil\\fcharset0 MS Shell Dlg;}}"
					   "\\viewkind4\\uc1\\pard\\lang1033\\f0\\fs17");

	// add text
	strcat(g_lpLongMsg,lpText);

	// close rtf data
	strcat(g_lpLongMsg,"\\par }");

	UnlockGlobalLongMsg()

	// correct for newlines
	CorrectRTFNewLines(g_lpLongMsg);

	LockGlobalLongMsg()

	// prepare edit stream
	es.dwCookie   =(DWORD)g_lpLongMsg;
	es.dwError    =NULL;
	es.pfnCallback=StreamInCallback;

	// stream text to window
	g_lpContextHelpWnd->lpHelpTxt->StreamIn(SF_RTF,
											es);

	UnlockGlobalLongMsg()

	// enable resize messages
	g_lpContextHelpWnd->lpHelpTxt->SetEventMask(ENM_REQUESTRESIZE);

	// resize window
	g_lpContextHelpWnd->lpHelpTxt->RequestResize();

	// disable resize messages
	g_lpContextHelpWnd->lpHelpTxt->SetEventMask(NULL);

	// check link data
	if(dwLinkData)
	{
		// save link data
		g_lpContextHelpWnd->dwSavedLinkData=dwLinkData;

		// get window size
		g_lpContextHelpWnd->GetWindowRect(&rWnd);

		// add room for link
		rWnd.bottom+=CHW_LINKGUTTER+CHW_LINKYSIZE+CHW_BLINKMARGIN;

		// resize window
		g_lpContextHelpWnd->MoveWindow(&rWnd);

		// get text window position
		g_lpContextHelpWnd->lpHelpTxt->GetWindowRect(&rWnd);

		// adjust size & position
		rWnd.right -=CHW_RLINKMARGIN;
		rWnd.left  =rWnd.right-CHW_LINKXSIZE;
		rWnd.top   =rWnd.bottom+CHW_LINKGUTTER;
		rWnd.bottom=rWnd.top   +CHW_LINKYSIZE;

		// set link window position
		g_lpContextHelpWnd->lpLinkTxt->MoveWindow(&rWnd);

		// make window visible
		g_lpContextHelpWnd->lpLinkTxt->ShowWindow(SW_SHOW);

		LockGlobalLongMsg()
		
		// output rtf header
		strcpy(g_lpLongMsg,"{\\rtf1\\ansi\\deff0"
						   "{\\fonttbl{\\f0\\fnil\\fcharset0 MS Shell Dlg;}}"
						   "{\\colortbl ;\\red0\\green0\\blue255;}"
						   "\\viewkind4\\uc1\\pard\\lang1033\\f0\\fs17\\cf1");

		// add text
		strcat(g_lpLongMsg,"\\qr\\ul Click here to view Help topic\\ul0");

		// close rtf data
		strcat(g_lpLongMsg,"\\par }");

		UnlockGlobalLongMsg()

		// correct for newlines
		CorrectRTFNewLines(g_lpLongMsg);

		LockGlobalLongMsg()

		// prepare edit stream
		es.dwCookie   =(DWORD)g_lpLongMsg;
		es.dwError    =NULL;
		es.pfnCallback=StreamInCallback;

		// stream text to window
		g_lpContextHelpWnd->lpLinkTxt->StreamIn(SF_RTF,
												es);

		UnlockGlobalLongMsg()
	}

	// ok
	return(TRUE);
}

// CContextHelpWnd::OnCreate()

int CContextHelpWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// window rect
	CRect rWnd;

	// create help text
	AllocClassObject(lpHelpTxt,
					 CExtRichEditCtrl(NULL));

	// check new object
	if(!lpHelpTxt)
		return(-1);

	// prepare rect
	rWnd.SetRect(CHW_LMARGINSIZE+2,
				 CHW_TMARGINSIZE+2,
				 lpCreateStruct->cx-((CHW_RMARGINSIZE+2)+CHW_SHADOWSIZE),
				 lpCreateStruct->cy-((CHW_BMARGINSIZE+2)+CHW_SHADOWSIZE));

	// create help text window
	if(!lpHelpTxt->Create(ES_MULTILINE|
						  ES_READONLY|
						  WS_CHILD|
						  WS_VISIBLE|
						  WS_DISABLED,
						  rWnd,
						  this,
						  NULL))
	{
		DisplayErrorMessage("Unable to create help text window.");
		return(-1);
	}

	// create link text
	AllocClassObject(lpLinkTxt,
					 CExtRichEditCtrl(NULL));

	// check new object
	if(!lpLinkTxt)
		return(-1);

	// set null rect
	rWnd.SetRect(0,0,
				 0,0);

	// create link text window
	if(!lpLinkTxt->Create(ES_READONLY|
						  WS_CHILD|
						  WS_DISABLED,
						  rWnd,
						  this,
						  NULL))
	{
		DisplayErrorMessage("Unable to create link text window.");
		return(-1);
	}

	// set background colors
	lpHelpTxt->SetBackgroundColor(FALSE,GetSysColor(COLOR_INFOBK));
	lpLinkTxt->SetBackgroundColor(FALSE,GetSysColor(COLOR_INFOBK));

	// call base method
	if(CWnd::OnCreate(lpCreateStruct)==0)
	{
		AddWinResource

		// ok
		return(0);
	}

	// no good
	return(-1);
}

// CContextHelpWnd::OnMouseMove()

void CContextHelpWnd::OnMouseMove(UINT nFlags,
								  CPoint point)
{
	// check window
	if(lpHelpTxt)
		if(IsWindow(lpHelpTxt->m_hWnd))
		{
			// convert point
			ClientToScreen(&point);

			// check point
			if(IsPointInWindow(&point,
							   lpLinkTxt))
				SetCursor(g_hHandCur);
			else
				SetCursor(g_hArrowCur);
		}
}

// KillAllTimers()

void KillAllTimers(void)
{
	// macro to kill timers
	#define SafeKillTimer(id) { if(id) { ::KillTimer(NULL,id); id=NULL; } }

	// kill all timers
	SafeKillTimer(g_nCurAudioTimerID);
	SafeKillTimer(g_nFlashId);
	SafeKillTimer(g_nFSwapId);
	SafeKillTimer(g_nPrevTimerId);
	SafeKillTimer(g_nScrnUpTimerId);
	SafeKillTimer(g_nOnCloseTimerId);
	SafeKillTimer(g_nOnTimeoutTimerId);
	SafeKillTimer(g_nDXSongTimerId);
#ifdef SHAREWARE_MODE
	SafeKillTimer(g_nTrialDaysTimerID);
#endif
}

// ShowHelpTopic()

BOOL ShowHelpTopic(DWORD dwLinkData)
{
	// window handle
	HWND hWnd=(HWND)INVALID_HANDLE_VALUE;

	LockGlobalErrorMsg()

	// copy install path
	strcpy(g_lpErrorMsg,
		   g_lpInstPath);

	// add help file
	strcat(g_lpErrorMsg,
		   "\\prosaver.chm");

	// show help
	hWnd=HtmlHelp(NULL,
				  g_lpErrorMsg,
				  HH_DISPLAY_TOPIC,
				  dwLinkData);

	UnlockGlobalErrorMsg()

	// check window
	if(hWnd==NULL||
	   hWnd==(HWND)INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Unable to display Help topic.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// CWelcomeScrnDlg::InitDialog()

BOOL CWelcomeScrnDlg::InitDialog(void)
{
	// reset values
	lpTutorialList=NULL;
	lpShowWndChk  =NULL;
	bInitOK       =FALSE;

	// create tutorial list
	AllocClassObject(lpTutorialList,
					 CListBox);

	// check new object
	if(!lpTutorialList)
		return(FALSE);

	// capture list box
	if(!CaptureDlgControl(this,
						  lpTutorialList,
						  IDC_TUTORIALLBX))
		return(FALSE);

	// fill list
	if(lpTutorialList->AddString("Tutorial #1: Introduction to ProSaver")<0||
	   lpTutorialList->AddString("Tutorial #2: Creating a Screensaver Playlist")<0||
	   lpTutorialList->AddString("Tutorial #3: Setting Playback Options")<0||
	   lpTutorialList->AddString("Tutorial #4: Organizing Your Screensavers")<0||
	   lpTutorialList->AddString("Tutorial #5: Adding Music and Audio Playlists")<0||
	   lpTutorialList->AddString("Tutorial #6: Shortcuts and Time-Savers")<0||
	   lpTutorialList->AddString("Tutorial #7: Using Advanced Options")<0)
	{
		DisplayErrorMessage("Unable to add Tutorial item to list box.");
		return(FALSE);
	}

	// create show-window checkbox
	AllocClassObject(lpShowWndChk,
					 CButton);

	// check new object
	if(!lpShowWndChk)
		return(FALSE);

	// capture checkbox
	if(!CaptureDlgControl(this,
						  lpShowWndChk,
						  IDC_SHOWWELCOMECHK))
		return(FALSE);

	// set check
	lpShowWndChk->SetCheck(1);

	// set init flag
	bInitOK=TRUE;

	// ok
	return(TRUE);
}

// CWelcomeScrnDlg::ApplyChanges()

void CWelcomeScrnDlg::ApplyChanges(void)
{
	// selection index
	int nSel;

	// check init flag
	if(!bInitOK)
		return;

	// get selection
	nSel=lpTutorialList->GetCurSel();

	// check selection
	if(nSel<0)
	{
		DisplayInfoMessage("Please select a Tutorial from the list.");
		CloseNotOK();
		return;
	}

	// display selected tutorial
	switch(nSel)
	{
	case(0): PostCommand(g_lpMainSheet,IDM_DISPLAYTUT1); break;
	case(1): PostCommand(g_lpMainSheet,IDM_DISPLAYTUT2); break;
	case(2): PostCommand(g_lpMainSheet,IDM_DISPLAYTUT3); break;
	case(3): PostCommand(g_lpMainSheet,IDM_DISPLAYTUT4); break;
	case(4): PostCommand(g_lpMainSheet,IDM_DISPLAYTUT5); break;
	case(5): PostCommand(g_lpMainSheet,IDM_DISPLAYTUT6); break;
	case(6): PostCommand(g_lpMainSheet,IDM_DISPLAYTUT7); break;
	}
}
\
// CWelcomeScrnDlg::ReleaseDialog()

void CWelcomeScrnDlg::ReleaseDialog(void)
{
	// show-again flag
	BOOL bShowAgain=FALSE;

	// check init
	if(bInitOK)
	{
		// check checkbox
		if(lpShowWndChk->GetCheck()==1)
			bShowAgain=TRUE;
	}

	// check show-again flag
	if(!bShowAgain)
	{
		// clear flag
		SaveOptionInt("MsgBox_ShowWelcome",
					  0);
	}

	// release objects
	FreeClassObject(lpTutorialList);
	FreeClassObject(lpShowWndChk);
}

// RunWelcomeScreen()

BOOL RunWelcomeScreen(void)
{
	// welcome dialog
	CWelcomeScrnDlg* lpWelcomeScrn=NULL;

	// check flag
	if(LoadOptionInt("MsgBox_ShowWelcome",
					 0,
					 1,
					 1)==0)
		return(TRUE);

	// create welcome dialog
	AllocClassObject(lpWelcomeScrn,
					 CWelcomeScrnDlg(IDD_WELCOMEDLG,
									 g_lpMainSheet));

	// check new object
	if(!lpWelcomeScrn)
		return(FALSE);

	// display window
	lpWelcomeScrn->DoModal();

	// release window
	FreeClassObject(lpWelcomeScrn);
	
	// ok
	return(TRUE);
}

// CWelcomeScrnDlg::OnDblClick()

void CWelcomeScrnDlg::OnDblClick(void)
{
	// simulate ok
	OnOK();
}

// CWelcomeScrnDlg::OnSelChange()

void CWelcomeScrnDlg::OnSelChange(void)
{
	// play sound
	PlaySound(IDR_NEWSELSND);
}

// CWelcomeScrnDlg::OnCommand()

BOOL CWelcomeScrnDlg::OnCommand(WPARAM wParam,
							    LPARAM lParam)
{
	// call base method
	BOOL bRet=CExtDialog::OnCommand(wParam,
									lParam);

	// check code
	switch(HIWORD(wParam))
	{
	// list box messages
	case(LBN_DBLCLK):    OnDblClick();  break;
	case(LBN_SELCHANGE): OnSelChange(); break;
	}

	// ok
	return(bRet);
}

// RunProSaverExe()

BOOL RunProSaverExe()
{
	// run program
	return(ExecuteExternalApp("ProSaver.exe /s",
							  g_lpInstPath));
}

// eof //

// Copyright 2006 WaveBreak Software
