// Copyright 2006 WaveBreak Software

// playback.cpp -- playback settings functions

// includes //

#include"main.h"

// message maps

BEGIN_MESSAGE_MAP(CPlaybackPage,CPropertyPage)
	ON_BN_CLICKED(IDC_ONESVRRAD,     OnOneSaverRadClk)
	ON_BN_CLICKED(IDC_MULTISVRRAD,   OnMultiSaverRadClk)
	ON_BN_CLICKED(IDC_SVRCYCLERAD,   OnSaverCycleRadClk)
	ON_BN_CLICKED(IDC_SVRSHUFFLERAD, OnSaverShuffleRadClk)
	ON_BN_CLICKED(IDC_ENABLEHKEYSCBX,OnEnableHotkeysChkClk)
	ON_BN_CLICKED(IDC_CLRSCREENCBX,  OnClearScreenChkClk)
	ON_BN_CLICKED(IDC_NOMUSICCBX,    OnMusicPlaybackChkClk)
	ON_BN_CLICKED(IDC_OPENTHEMESBTN, OnOpenThemesBtnClk)
	ON_BN_CLICKED(IDC_OPENAUDIOBTN,  OnOpenMusicBtnClk)
	ON_BN_CLICKED(IDC_SHOWADVBTN,    OnShowAdvancedBtnClk)
	ON_BN_CLICKED(IDC_ADDPATHBTN,    OnAddPathBtnClk)
	ON_BN_CLICKED(IDC_CHANGEPATHBTN, OnChangePathBtnClk)
	ON_BN_CLICKED(IDC_DELETEPATHBTN, OnDeletePathBtnClk)
	ON_BN_CLICKED(IDC_SYSTRAYCHK,    OnSystemTrayChkClk)
	ON_BN_CLICKED(IDC_KEEPCURCHK,    OnKeepCurrentChkClk)
	ON_BN_CLICKED(IDC_HIDEADVCHK,    OnHideAdvancedChkClk)
	ON_BN_CLICKED(IDC_ERRORLOGCHK,   OnErrorLogChkClk)
	ON_BN_CLICKED(IDC_ERRORLOGBTN,   OnErrorLogBtnClk)
	ON_BN_CLICKED(IDC_RESETMSGBTN,   OnResetMessagesBtnClk)
	ON_BN_CLICKED(IDC_HIDEADVBTN,    OnHideAdvancedBtnClk)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CPathListCtrl,CListCtrl)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED,OnItemChanged)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,  OnCustomDraw)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA,0,0xFFFF,OnTTNeedText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW,0,0xFFFF,OnTTNeedText)
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// globals //

// main property page
CPlaybackPage* g_lpPlaybackPage=NULL;
// page init flag
BOOL g_bPlaybackPageInit=FALSE;
// page init-ok flag
BOOL g_bPlaybackPageInitOK=FALSE;
// radio buttons
CExtButton* g_lpOneSaverRad=NULL;
CExtButton* g_lpMultiSaverRad=NULL;
CExtButton* g_lpSaverCycleRad=NULL;
CExtButton* g_lpSaverShuffleRad=NULL;
// static controls
CExtStatic* g_lpShowSaverTxt=NULL;
CExtStatic* g_lpShowSaverMinTxt=NULL;
CExtStatic* g_lpStartSaverTxt=NULL;
CExtStatic* g_lpSkipSaverTxt=NULL;
CExtStatic* g_lpOpenPSTxt=NULL;
CExtStatic* g_lpMaxLinesTxt=NULL;
// read-only edit controls
CExtEdit* g_lpAdvWarningTxt=NULL;
// edit controls
CExtEdit* g_lpShowSaverEdit=NULL;
CExtEdit* g_lpMaxLinesEdit=NULL;
// checkboxes
CExtButton* g_lpEnableHotkeysChk=NULL;
CExtButton* g_lpClearScreenChk=NULL;
CExtButton* g_lpNoMusicChk=NULL;
CExtButton* g_lpSystemTrayChk=NULL;
CExtButton* g_lpKeepCurrentChk=NULL;
CExtButton* g_lpHideAdvancedChk=NULL;
CExtButton* g_lpErrorLogChk=NULL;
// hotkey controls
CExtHotKeyCtrl* g_lpStartSaverHky=NULL;
CExtHotKeyCtrl* g_lpSkipSaverHky=NULL;
CExtHotKeyCtrl* g_lpOpenPSHky=NULL;
// pushbutton controls
CExtButton* g_lpOpenThemesBtn=NULL;
CExtButton* g_lpOpenMusicBtn=NULL;
CExtButton* g_lpShowAdvancedBtn=NULL;
CExtButton* g_lpAddPathBtn=NULL;
CExtButton* g_lpChangePathBtn=NULL;
CExtButton* g_lpDeletePathBtn=NULL;
CExtButton* g_lpErrorLogBtn=NULL;
CExtButton* g_lpResetMessagesBtn=NULL;
CExtButton* g_lpHideAdvancedBtn=NULL;
// search path list
CPathListCtrl* g_lpSearchPathList=NULL;
// misc. flags
BOOL g_bMultiSavers=FALSE;
BOOL g_bCycleSavers=FALSE;
BOOL g_bEnableHotkeys=FALSE;
BOOL g_bClearScreen=FALSE;
BOOL g_bNoMusic=FALSE;
BOOL g_bSystemTray=FALSE;
BOOL g_bKeepCurrent=FALSE;
BOOL g_bHideAdvanced=FALSE;
BOOL g_bKeepErrorLog=FALSE;
// playback minutes
int g_nPlayMinutes=0;
// hotkey values
DWORD g_dwStartSaverHky=NULL;
DWORD g_dwSkipSaverHky=NULL;
DWORD g_dwOpenPSHky=NULL;
// search path image list
CImageList* g_lpSPathImageList=NULL;
// advanced-viewed flag
BOOL g_bAdvOptViewed=FALSE;
// static boxes
CStatic* g_lpSearchPathBox=NULL;
CStatic* g_lpErrorLogBox=NULL;
// error-log lines
int g_nErrorLogLines=0;
// music manager dialog
CMusicManagerDlg* g_lpMusicManagerDlgA=NULL;
// advanced-visible flag
BOOL g_bAdvOptVisible=FALSE;

// functions //

// CPlaybackPage::OnSetActive()

BOOL CPlaybackPage::OnSetActive(void)
{
	// call init
	if(!Initialize())
		ForceImmediateExit();

	// ok
	return(TRUE);
}

// CPlaybackPage::Initialize()

BOOL CPlaybackPage::Initialize(void)
{
	// column width
	int nColWd;

	// position rectangle
	RECT rPos;

	// call base function
	if(!CPropertyPage::OnSetActive())
		return(FALSE);

	// check initialized flag
	if(g_bPlaybackPageInit)
		return(g_bPlaybackPageInitOK);

	// set init flag
	g_bPlaybackPageInit=TRUE;

	// pre-set advanced-display flag
	g_bAdvOptVisible=(g_bHideAdvanced ? FALSE : TRUE);

	// capture one-saver radio button
	if(!CaptureDlgControl(this,
						  g_lpOneSaverRad,
						  IDC_ONESVRRAD))
		return(FALSE);

	// capture multi-saver radio button
	if(!CaptureDlgControl(this,
						  g_lpMultiSaverRad,
						  IDC_MULTISVRRAD))
		return(FALSE);

	// capture show-saver text
	if(!CaptureDlgControl(this,
						  g_lpShowSaverTxt,
						  IDC_SHOWSVRTXT))
		return(FALSE);

	// capture show-saver edit box
	if(!CaptureDlgControl(this,
						  g_lpShowSaverEdit,
						  IDC_SHOWSVREDT))
		return(FALSE);

	// capture show-saver-min text
	if(!CaptureDlgControl(this,
						  g_lpShowSaverMinTxt,
						  IDC_SHOWSVRMINTXT))
		return(FALSE);

	// update multi-savers option
	if(g_bMultiSavers)
		SetMultiSavers(FALSE);
	else
		SetOneSaver(FALSE);

	// just to verify
	LockGlobalMsg()
	UnlockGlobalMsg()

	// fill in minutes text
	g_lpShowSaverEdit->SetWindowText(itoa(g_nPlayMinutes,
										  g_lpMsg,
										  10));

	// set text limit
	g_lpShowSaverEdit->SetLimitText(3);

	// set numerical limits
	g_lpShowSaverEdit->SetNumLimits(1,
									120,
									&g_nPlayMinutes);

	// add spin control
	if(!g_lpShowSaverEdit->AddSpinControl(this,
										  IDC_SHOWSVRSPIN,
										  IDR_NEWSELSND))
		return(FALSE);

	// set edit box parent
	g_lpShowSaverEdit->SetParentPropPage(this);

	// capture cycle-savers radio button
	if(!CaptureDlgControl(this,
						  g_lpSaverCycleRad,
						  IDC_SVRCYCLERAD))
		return(FALSE);

	// capture shuffle-savers radio button
	if(!CaptureDlgControl(this,
						  g_lpSaverShuffleRad,
						  IDC_SVRSHUFFLERAD))
		return(FALSE);

	// update cycle-savers option
	if(g_bCycleSavers)
		SetCycleSavers(FALSE);
	else
		SetShuffleSavers(FALSE);

	// capture enable-hotkeys checkbox
	if(!CaptureDlgControl(this,
						  g_lpEnableHotkeysChk,
						  IDC_ENABLEHKEYSCBX))
		return(FALSE);

	// capture start-saver text
	if(!CaptureDlgControl(this,
						  g_lpStartSaverTxt,
						  IDC_STARTSVRTXT))
		return(FALSE);

	// capture start-saver hotkey
	if(!CaptureDlgControl(this,
						  g_lpStartSaverHky,
						  IDC_STARTSVRHKY))
		return(FALSE);

	// capture skip-saver text
	if(!CaptureDlgControl(this,
						  g_lpSkipSaverTxt,
						  IDC_SKIPSVRTXT))
		return(FALSE);

	// capture skip-saver hotkey
	if(!CaptureDlgControl(this,
						  g_lpSkipSaverHky,
						  IDC_SKIPSVRHKY))
		return(FALSE);

	// capture open-prosaver text
	if(!CaptureDlgControl(this,
						  g_lpOpenPSTxt,
						  IDC_OPENPSTXT))
		return(FALSE);

	// capture open-prosaver hotkey
	if(!CaptureDlgControl(this,
						  g_lpOpenPSHky,
						  IDC_OPENPSHKY))
		return(FALSE);

	// hotkey rules
	#define HKEY_RULES HKCOMB_NONE|HKCOMB_S,HOTKEYF_CONTROL|HOTKEYF_ALT

	// configure hotkey controls
	g_lpStartSaverHky->SetRules(HKEY_RULES);
	g_lpSkipSaverHky->SetRules(HKEY_RULES);
	g_lpOpenPSHky->SetRules(HKEY_RULES);

	// set hotkey values
	g_lpStartSaverHky->SetHotKey(LOWORD(g_dwStartSaverHky),
								 HIWORD(g_dwStartSaverHky));
	g_lpSkipSaverHky->SetHotKey(LOWORD(g_dwSkipSaverHky),
								HIWORD(g_dwSkipSaverHky));
	g_lpOpenPSHky->SetHotKey(LOWORD(g_dwOpenPSHky),
							 HIWORD(g_dwOpenPSHky));

	// update enable-hotkeys option
	ToggleHotkeys(FALSE);

	// capture clear-screen checkbox
	if(!CaptureDlgControl(this,
						  g_lpClearScreenChk,
						  IDC_CLRSCREENCBX))
		return(FALSE);

	// update clear-screen checkbox
	ToggleClearScreen(FALSE);

	// capture music-playback checkbox
	if(!CaptureDlgControl(this,
						  g_lpNoMusicChk,
						  IDC_NOMUSICCBX))
		return(FALSE);

	// update no-music checkbox
	ToggleMusicPlayback(FALSE);

	// capture edit-themes button
	if(!CaptureDlgControl(this,
						  g_lpOpenThemesBtn,
						  IDC_OPENTHEMESBTN))
		return(FALSE);

	// create edit themes dialog
	AllocClassObject(g_lpEditThemesDlgB,
					 CEditThemesDlg(IDD_EDITTHEMES,
								    this));

	// check new object
	if(!g_lpEditThemesDlgB)
		return(FALSE);

	// capture edit-music button
	if(!CaptureDlgControl(this,
						  g_lpOpenMusicBtn,
						  IDC_OPENAUDIOBTN))
		return(FALSE);

	// capture advanced-warning text
	if(!CaptureDlgControl(this,
						  g_lpAdvWarningTxt,
						  IDC_ADVWARNTXT))
		return(FALSE);

	// set advanced warning text
	g_lpAdvWarningTxt->SetWindowText("Warning! This section contains options\r\nthat are intended for advanced users.\r\n\r\nClick the 'Show Advanced Options'\r\nbutton to view or change these settings.");

	// set no-cursor
	g_lpAdvWarningTxt->SetNoCursor();

	// capture show-advanced button
	if(!CaptureDlgControl(this,
						  g_lpShowAdvancedBtn,
						  IDC_SHOWADVBTN))
		return(FALSE);

	// capture search-path box
	if(!CaptureDlgControl(this,
						  g_lpSearchPathBox,
						  IDC_SPATHSTATIC))
		return(FALSE);

	// capture search-path list
	if(!CaptureDlgControl(this,
						  g_lpSearchPathList,
						  IDC_SEARCHLIST))
		return(FALSE);

	// get search list window
	g_lpSearchPathList->GetClientRect(&rPos);

	// set search list width
	nColWd=(rPos.right-rPos.left)-GetSystemMetrics(SM_CXVSCROLL);

	// add default column
	if(g_lpSearchPathList->InsertColumn(0,
										NULL_STRING,
										LVCFMT_LEFT,
										nColWd,
										0)==-1)
	{
		DisplayErrorMessage("Unable to add search path list column.");
		return(FALSE);
	}

	// create search path image list
	if(!CreateSearchPathImageList())
		return(FALSE);

	// add paths to list
	if(!AddSearchPathsToList())
		return(FALSE);

	// capture add-path button
	if(!CaptureDlgControl(this,
						  g_lpAddPathBtn,
						  IDC_ADDPATHBTN))
		return(FALSE);

	// capture change-path button
	if(!CaptureDlgControl(this,
						  g_lpChangePathBtn,
						  IDC_CHANGEPATHBTN))
		return(FALSE);

	// capture delete-path button
	if(!CaptureDlgControl(this,
						  g_lpDeletePathBtn,
						  IDC_DELETEPATHBTN))
		return(FALSE);

	// capture system-tray check
	if(!CaptureDlgControl(this,
						  g_lpSystemTrayChk,
						  IDC_SYSTRAYCHK))
		return(FALSE);

	// capture keep-current check
	if(!CaptureDlgControl(this,
						  g_lpKeepCurrentChk,
						  IDC_KEEPCURCHK))
		return(FALSE);

	// capture hide-advanced check
	if(!CaptureDlgControl(this,
						  g_lpHideAdvancedChk,
						  IDC_HIDEADVCHK))
		return(FALSE);

	// update checkboxes
	ToggleSystemTray(FALSE);
	ToggleKeepCurrent(FALSE);
	ToggleHideAdvanced(FALSE);

	// capture error-log box
	if(!CaptureDlgControl(this,
						  g_lpErrorLogBox,
						  IDC_ERRLOGSTATIC))
		return(FALSE);

	// capture error-log check
	if(!CaptureDlgControl(this,
						  g_lpErrorLogChk,
						  IDC_ERRORLOGCHK))
		return(FALSE);

	// capture max-lines text
	if(!CaptureDlgControl(this,
						  g_lpMaxLinesTxt,
						  IDC_MAXLINESTXT))
		return(FALSE);

	// capture max-lines edit
	if(!CaptureDlgControl(this,
						  g_lpMaxLinesEdit,
						  IDC_MAXLINESEDT))
		return(FALSE);

	// capture error-log button
	if(!CaptureDlgControl(this,
						  g_lpErrorLogBtn,
						  IDC_ERRORLOGBTN))
		return(FALSE);

	// just to verify
	LockGlobalMsg()
	UnlockGlobalMsg()

	// fill in error-log lines
	g_lpMaxLinesEdit->SetWindowText(itoa(g_nErrorLogLines,
										 g_lpMsg,
										 10));

	// set text limit
	g_lpMaxLinesEdit->SetLimitText(3);

	// set numerical limits
	g_lpMaxLinesEdit->SetNumLimits(50,
								   400,
								   &g_nErrorLogLines);

	// add spin control
	if(!g_lpMaxLinesEdit->AddSpinControl(this,
										 IDC_MAXLINESSPIN,
										 IDR_NEWSELSND,
										 FALSE,
										 FALSE,
										 TRUE,
										 TRUE,
										 TRUE,
										 TRUE,
										 &g_bAdvOptVisible))
		return(FALSE);

	// set edit box parent
	g_lpMaxLinesEdit->SetParentPropPage(this);

	// update error log
	ToggleErrorLog(FALSE);

	// capture reset-messages button
	if(!CaptureDlgControl(this,
						  g_lpResetMessagesBtn,
						  IDC_RESETMSGBTN))
		return(FALSE);

	// capture hide-advanced button
	if(!CaptureDlgControl(this,
						  g_lpHideAdvancedBtn,
						  IDC_HIDEADVBTN))
		return(FALSE);

	// set init-ok flag
	g_bPlaybackPageInitOK=TRUE;

	// update advanced options
	ShowAdvancedOptions(g_bHideAdvanced ? FALSE : TRUE);

	// ok
	return(TRUE);
}

// CPlaybackPage::OnOK()

void CPlaybackPage::OnOK(void)
{
	// check initialized flag
	if(g_bPlaybackPageInitOK)
	{
		// save playback options
		SavePlaybackOptions();	
	}

	/* this causes double update
	// apply general changes
	g_lpMainSheet->ApplyChanges();*/

	// call base function
	CPropertyPage::OnOK();
}

// CPlaybackPage::OnOneSaverRadClk()

void CPlaybackPage::OnOneSaverRadClk(void)
{
	// set one saver
	SetOneSaver();
}

// CPlaybackPage::OnMultiSaverRadClk()

void CPlaybackPage::OnMultiSaverRadClk(void)
{
	// set multi savers
	SetMultiSavers();
}

// CPlaybackPage::OnSaverCycleRadClk()

void CPlaybackPage::OnSaverCycleRadClk(void)
{
	// set cycle savers
	SetCycleSavers();
}

// CPlaybackPage::OnSaverShuffleRadClk()

void CPlaybackPage::OnSaverShuffleRadClk(void)
{
	// set shuffle savers
	SetShuffleSavers();
}

// CPlaybackPage::OnEnableHotkeysChkClk()

void CPlaybackPage::OnEnableHotkeysChkClk(void)
{
	// toggle hotkeys
	ToggleHotkeys();
}

// CPlaybackPage::OnClearScreenChkClk()

void CPlaybackPage::OnClearScreenChkClk(void)
{
	// toggle clear-screen
	ToggleClearScreen();
}

// CPlaybackPage::OnMusicPlaybackChkClk(void)

void CPlaybackPage::OnMusicPlaybackChkClk(void)
{
	// toggle music-playback
	ToggleMusicPlayback();
}

// CPlaybackPage::OnOpenThemesBtnClk()

void CPlaybackPage::OnOpenThemesBtnClk(void)
{
	// edit themes
	EditThemes(g_lpEditThemesDlgB);
}

// CPlaybackPage::OnOpenMusicBtnClk()

void CPlaybackPage::OnOpenMusicBtnClk(void)
{
	// show music manager
	ShowMusicManager(g_lpMusicManagerDlgA,
					 g_lpMainSheet);
}

// CPlaybackPage::OnAddPathBtnClk()

void CPlaybackPage::OnAddPathBtnClk(void)
{
	// add path to list
	g_lpSearchPathList->AddPath();
}

// CPlaybackPage::OnChangePathBtnClk()

void CPlaybackPage::OnChangePathBtnClk(void)
{
	// change selection
	g_lpSearchPathList->ChangeSelection();
}

// CPlaybackPage::OnDeletePathBtnClk()

void CPlaybackPage::OnDeletePathBtnClk(void)
{
	// delete selection
	g_lpSearchPathList->DeleteSelection();
}

// CPlaybackPage::OnContextMenu()

void CPlaybackPage::OnContextMenu(CWnd* pWnd,
								  CPoint pos)
{
	// check for show-saver edit box
	if(IsPointInWindow(&pos,
					   g_lpShowSaverEdit))
		g_lpShowSaverEdit->OnContextMenu(pWnd,
										 pos);

	// check for show-saver spin control
	if(IsPointInWindow(&pos,
					   g_lpShowSaverEdit->lpSpinCtrl))
		g_lpShowSaverEdit->lpSpinCtrl->OnContextMenu(pWnd,
													 pos);

	// check for start-saver hotkey
	if(IsPointInWindow(&pos,
					   g_lpStartSaverHky))
		g_lpStartSaverHky->OnContextMenu(pWnd,
										 pos);

	// check for skip-saver hotkey
	if(IsPointInWindow(&pos,
					   g_lpSkipSaverHky))
		g_lpSkipSaverHky->OnContextMenu(pWnd,
										pos);

	// check for open-prosaver hotkey
	if(IsPointInWindow(&pos,
					   g_lpOpenPSHky))
		g_lpOpenPSHky->OnContextMenu(pWnd,
									 pos);

	// check for advanced-warning text
	if(IsPointInWindow(&pos,
					   g_lpAdvWarningTxt))
		g_lpAdvWarningTxt->OnContextMenu(pWnd,
										 pos);

	// check for change-path button
	if(IsPointInWindow(&pos,
					   g_lpChangePathBtn))
		g_lpChangePathBtn->OnContextMenu(pWnd,
										 pos);

	// check for delete-path button
	if(IsPointInWindow(&pos,
					   g_lpDeletePathBtn))
		g_lpDeletePathBtn->OnContextMenu(pWnd,
										 pos);

	// check for max-lines edit
	if(IsPointInWindow(&pos,
					   g_lpMaxLinesEdit))
		g_lpMaxLinesEdit->OnContextMenu(pWnd,
										pos);

	// check for error-log button
	if(IsPointInWindow(&pos,
					   g_lpErrorLogBtn))
		g_lpErrorLogBtn->OnContextMenu(pWnd,
									   pos);
}

// LoadPlaybackOptions()

BOOL LoadPlaybackOptions(void)
{
	// load misc. flags
	g_bMultiSavers=(BOOL)LoadOptionInt("Play_MultiSavers",
									   0,
									   1,
									   1);
	g_bCycleSavers=(BOOL)LoadOptionInt("Play_CycleSavers",
									   0,
									   1,
									   1);
	g_bEnableHotkeys=(BOOL)LoadOptionInt("Play_EnableHotkeys",
										 0,
										 1,
										 1);
	g_bClearScreen=(BOOL)LoadOptionInt("Play_ClearScreen",
									   0,
									   1,
									   1);
	g_bNoMusic=(BOOL)LoadOptionInt("Play_NoMusic",
								   0,
								   1,
								   0);

	// load playback minutes
	g_nPlayMinutes=LoadOptionInt("Play_Minutes",
								 1,
								 120,
								 4);

	// load hotkey values
	g_dwStartSaverHky=(DWORD)LoadOptionInt("Play_StartHky",
										   0,
										   -1,
										   (int)(((HOTKEYF_CONTROL|HOTKEYF_ALT)<<16)|'S'));
	g_dwSkipSaverHky=(DWORD)LoadOptionInt("Play_SkipHky",
										  0,
										  -1,
										  (int)(((HOTKEYF_CONTROL|HOTKEYF_ALT)<<16)|'N'));
	g_dwOpenPSHky=(DWORD)LoadOptionInt("Play_OpenPSHky",
									   0,
									   -1,
									   (int)(((HOTKEYF_CONTROL|HOTKEYF_ALT)<<16)|'P'));

	// validate hotkey values
	if(g_dwStartSaverHky==g_dwSkipSaverHky) g_dwSkipSaverHky=NULL;
	if(g_dwStartSaverHky==g_dwOpenPSHky)    g_dwOpenPSHky   =NULL;
	if(g_dwSkipSaverHky ==g_dwOpenPSHky)    g_dwOpenPSHky   =NULL;

	// load advanced options
	if(!LoadAdvancedOptions())
		return(FALSE);

	// ok
	return(TRUE);
}

// SavePlaybackOptions()

void SavePlaybackOptions(void)
{
	// hotkey values
	WORD wStartSaverHky1;
	WORD wStartSaverHky2;
	WORD wSkipSaverHky1;
	WORD wSkipSaverHky2;
	WORD wOpenPSHky1;
	WORD wOpenPSHky2;

	LockGlobalMsg()

	// get playback minutes
	if(g_lpShowSaverEdit->GetWindowText(g_lpMsg,
										_MAX_PATH)!=0)
	{
		// update playback minutes
		g_nPlayMinutes=atoi(g_lpMsg);

		UnlockGlobalMsg()

		// check value
		if(g_nPlayMinutes<1)
		{
			// set value
			g_nPlayMinutes=1;

			// update edit box
			g_lpShowSaverEdit->SetWindowText("1");

			// alert user
			DisplayInfoMessage("The minimum time to show each screensaver is 1 minute.\n\nThis value has been reset to 1 minute.");
		}
	}
	else
		UnlockGlobalMsg()

	// get hotkey values
	g_lpStartSaverHky->GetHotKey(wStartSaverHky1,
								 wStartSaverHky2);
	g_lpSkipSaverHky->GetHotKey(wSkipSaverHky1,
								wSkipSaverHky2);
	g_lpOpenPSHky->GetHotKey(wOpenPSHky1,
							 wOpenPSHky2);

	// save misc. flags
	SaveOptionInt("Play_MultiSavers",
				  (int)g_bMultiSavers);
	SaveOptionInt("Play_CycleSavers",
				  (int)g_bCycleSavers);
	SaveOptionInt("Play_EnableHotkeys",
				  (int)g_bEnableHotkeys);
	SaveOptionInt("Play_ClearScreen",
				  (int)g_bClearScreen);
	SaveOptionInt("Play_NoMusic",
				  (int)g_bNoMusic);

	// save playback minutes
	SaveOptionInt("Play_Minutes",
				  g_nPlayMinutes);

	// save hotkey values
	SaveOptionInt("Play_StartHky",
				  (int)(((DWORD)wStartSaverHky2)<<16)|((DWORD)wStartSaverHky1));
	SaveOptionInt("Play_SkipHky",
				  (int)(((DWORD)wSkipSaverHky2)<<16)|((DWORD)wSkipSaverHky1));
	SaveOptionInt("Play_OpenPSHky",
				  (int)(((DWORD)wOpenPSHky2)<<16)|((DWORD)wOpenPSHky1));

	// save advanced options
	SaveAdvancedOptions();
}

// SetMultiSavers()

void SetMultiSavers(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set value
		g_bMultiSavers=TRUE;

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set check states
	g_lpOneSaverRad->SetCheck(0);
	g_lpMultiSaverRad->SetCheck(1);

	// enable minutes controls
	g_lpShowSaverTxt->Enable();
	g_lpShowSaverEdit->Enable();
	g_lpShowSaverMinTxt->Enable();
}

// SetOneSaver()

void SetOneSaver(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// reset value
		g_bMultiSavers=FALSE;

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set check states
	g_lpOneSaverRad->SetCheck(1);
	g_lpMultiSaverRad->SetCheck(0);

	// disable minutes controls
	g_lpShowSaverTxt->Disable();
	g_lpShowSaverEdit->Disable();
	g_lpShowSaverMinTxt->Disable();
}

// SetCycleSavers()

void SetCycleSavers(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// reset value
		g_bCycleSavers=TRUE;

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set check states
	g_lpSaverCycleRad->SetCheck(1);
	g_lpSaverShuffleRad->SetCheck(0);
}

// SetShuffleSavers()

void SetShuffleSavers(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// reset value
		g_bCycleSavers=FALSE;

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set check states
	g_lpSaverCycleRad->SetCheck(0);
	g_lpSaverShuffleRad->SetCheck(1);
}

// ToggleHotkeys()

void ToggleHotkeys(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bEnableHotkeys=(g_bEnableHotkeys ? FALSE : TRUE);

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// check flag
	if(g_bEnableHotkeys)
	{
		// set check
		g_lpEnableHotkeysChk->SetCheck(1);

		// enable controls
		g_lpStartSaverTxt->Enable();
		g_lpStartSaverHky->Enable();
		g_lpSkipSaverTxt->Enable();
		g_lpSkipSaverHky->Enable();
		g_lpOpenPSTxt->Enable();
		g_lpOpenPSHky->Enable();
	}
	else
	{
		// clear check
		g_lpEnableHotkeysChk->SetCheck(0);

		// disable controls
		g_lpStartSaverTxt->Disable();
		g_lpStartSaverHky->Disable();
		g_lpSkipSaverTxt->Disable();
		g_lpSkipSaverHky->Disable();
		g_lpOpenPSTxt->Disable();
		g_lpOpenPSHky->Disable();
	}
}

// CPlaybackPage::OnCommand()

BOOL CPlaybackPage::OnCommand(WPARAM wParam,
							  LPARAM lParam)
{
	// duplicate flag
	BOOL bDup;

	// flash window
	CWnd* lpFlashWnd=NULL;

	// check message
	switch(HIWORD(wParam))
	{
	// edit control change
	case(EN_CHANGE):

		// check id
		switch(LOWORD(wParam))
		{
		// hotkey controls
		case(IDC_STARTSVRHKY):
		case(IDC_SKIPSVRHKY):
		case(IDC_OPENPSHKY):

			// reset duplicate flag
			bDup=FALSE;

			// get specific id
			switch(LOWORD(wParam))
			{
			// start-saver hotkey
			case(IDC_STARTSVRHKY):

				// check for hotkey
				if(LOWORD(g_lpStartSaverHky->GetHotKey()))
				{
					// compare with skip-saver
					if(g_lpStartSaverHky->GetHotKey()==g_lpSkipSaverHky->GetHotKey())
					{
						// set skip-saver to none
						g_lpSkipSaverHky->SetHotKey(NULL,
													NULL);

						// set flash window
						lpFlashWnd=g_lpSkipSaverHky;

						// set flag
						bDup=TRUE;
					}

					// compare with open-prosaver
					if(g_lpStartSaverHky->GetHotKey()==g_lpOpenPSHky->GetHotKey())
					{
						// set open-prosaver to none
						g_lpOpenPSHky->SetHotKey(NULL,
												 NULL);

						// set flash window
						lpFlashWnd=g_lpOpenPSHky;

						// set flag
						bDup=TRUE;
					}
				}

				// ok
				break;

			// skip-saver hotkey
			case(IDC_SKIPSVRHKY):

				// check for hotkey
				if(LOWORD(g_lpSkipSaverHky->GetHotKey()))
				{
					// compare with start-saver
					if(g_lpSkipSaverHky->GetHotKey()==g_lpStartSaverHky->GetHotKey())
					{
						// set start-saver to none
						g_lpStartSaverHky->SetHotKey(NULL,
													 NULL);

						// set flash window
						lpFlashWnd=g_lpStartSaverHky;

						// set flag
						bDup=TRUE;
					}

					// compare with open-prosaver
					if(g_lpSkipSaverHky->GetHotKey()==g_lpOpenPSHky->GetHotKey())
					{
						// set open-prosaver to none
						g_lpOpenPSHky->SetHotKey(NULL,
												 NULL);

						// set flash window
						lpFlashWnd=g_lpOpenPSHky;

						// set flag
						bDup=TRUE;
					}
				}

				// ok
				break;

			// open-prosaver hotkey
			case(IDC_OPENPSHKY):

				// check for hotkey
				if(LOWORD(g_lpOpenPSHky->GetHotKey()))
				{
					// compare with start-saver
					if(g_lpOpenPSHky->GetHotKey()==g_lpStartSaverHky->GetHotKey())
					{
						// set start-saver to none
						g_lpStartSaverHky->SetHotKey(NULL,
													 NULL);

						// set flash window
						lpFlashWnd=g_lpStartSaverHky;

						// set flag
						bDup=TRUE;
					}

					// compare with skip-saver
					if(g_lpOpenPSHky->GetHotKey()==g_lpSkipSaverHky->GetHotKey())
					{
						// set skip-saver to none
						g_lpSkipSaverHky->SetHotKey(NULL,
													NULL);

						// set flash window
						lpFlashWnd=g_lpSkipSaverHky;

						// set flag
						bDup=TRUE;
					}
				}

				// ok
				break;
			}

			// check for duplicate
			if(bDup)
			{
				// play sound
				PlaySound(FORCE_DEFSND);

				// alert user
				DisplayOptMessageBox("You have set a hotkey that is already taken.\n\nThe other hotkey has been reset to 'None'.",
									 (LPCSTR)ApplicationName(),
									 MB_OK|MB_ICONEXCLAMATION,
									 "MsgBox_DupHotkey");
			}

			// set modified state
			SetModified();
		}

		// ok
		break;
	}

	// call base method
	return(CPropertyPage::OnCommand(wParam,
									lParam));
}

// ToggleClearScreen()

void ToggleClearScreen(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bClearScreen=(g_bClearScreen ? FALSE : TRUE);

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set button state
	g_lpClearScreenChk->SetCheck(g_bClearScreen ? 1 : 0);
}

// ToggleMusicPlayback()

void ToggleMusicPlayback(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bNoMusic=(g_bNoMusic ? FALSE : TRUE);

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set button state
	g_lpNoMusicChk->SetCheck(g_bNoMusic ? 1 : 0);
}

// CPathListCtrl::CPathListCtrl()

CPathListCtrl::CPathListCtrl(UINT nID)
{
	// copy id
	nCtrlId=nID;

	// call base constructor
	CListCtrl::CListCtrl();
}

// CPathListCtrl::OnContextMenu()

void CPathListCtrl::OnContextMenu(CWnd* pWnd,
								  CPoint pos)
{
	// check visiblity
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
			ShowPopupMenu(IDC_SEARCHLIST);
		}
		else
		{
			// call base method
			CListCtrl::OnContextMenu(pWnd,
									 pos);
		}
	}
}

// CPathListCtrl::OnCustomDraw()

void CPathListCtrl::OnCustomDraw(NMHDR* pNMHDR,
								 LRESULT* pResult)
{
	// get pointer to custom draw header
	LPNMLVCUSTOMDRAW lpLVCD=(LPNMLVCUSTOMDRAW)pNMHDR;

	// item nubmer
	int nItem;

	// assume default processing
	(*pResult)=CDRF_DODEFAULT;

	// check draw stage
	switch(lpLVCD->nmcd.dwDrawStage)
	{
	// general pre-paint stage
	case(CDDS_PREPAINT):

		// get notification of each item
		(*pResult)=CDRF_NOTIFYITEMDRAW;

		// ok
		break;

	// item pre-paint stage
	case(CDDS_ITEMPREPAINT):

		// get item number
		nItem=(int)lpLVCD->nmcd.dwItemSpec;

		// check for default path
		if(GetItemData(nItem)==1)
		{
			// set gray text
			lpLVCD->clrText=GetSysColor(COLOR_GRAYTEXT);
		}
		else
		{
			// set normal text
			lpLVCD->clrText=GetSysColor(COLOR_WINDOWTEXT);
		}

		// ok
		break;
	}
}

// CPathListCtrl::QuerySelection()

BOOL CPathListCtrl::QuerySelection(void)
{
	// check for selection
	return(GetFirstSelectedItemPosition() ? TRUE : FALSE);
}

// CPathListCtrl::GetSelection()

int CPathListCtrl::GetSelection(void)
{
	// position value
	POSITION pos;

	// get first position
	pos=GetFirstSelectedItemPosition();

	// check position
	return(pos ? GetNextSelectedItem(pos) : -1);
}

// CPathListCtrl::AddPath()

BOOL CPathListCtrl::AddPath(LPSTR lpPath,
							BOOL bDefault,
							BOOL bSilent)
{
	// item info
	LVITEM lvi;

	// check for path
	if(!lpPath)
	{
		LockGlobalLongMsg()

		// get path from user
		if(!SelectPathDlg(g_lpPlaybackPage,
						  g_lpLongMsg,
						  NULL,
						  "Please select a folder to add to the screensaver search list."))
		{
			UnlockGlobalLongMsg()
			return(FALSE);
		}

		// set pointer
		lpPath=g_lpLongMsg;
	}

	// make sure path is valid
	if(!DoesPathExist(lpPath))
	{
		// check flag
		if(!bSilent)
		{
			LockGlobalLongTTMsg()

			// prepare message
			sprintf(g_lpLongTTMsg,
					"The path '%s' is not valid.",
					lpPath);

			// show message
			DisplayErrorMessage(g_lpLongTTMsg);

			UnlockGlobalLongTTMsg()
		}

		UnlockGlobalLongMsg()

		// do not add
		return(FALSE);
	}

	// check for duplicate path
	if(PathIsInList(lpPath))
	{
		// check flag
		if(!bSilent)
		{
			LockGlobalLongTTMsg()

			// prepare message
			sprintf(g_lpLongTTMsg,
					"The selected path:\n\n'%s'\n\nis already in the search list.",
					lpPath);

			// show message
			DisplayInfoMessage(g_lpLongTTMsg);

			UnlockGlobalLongTTMsg()
		}

		UnlockGlobalLongMsg()

		// do not add
		return(FALSE);
	}

	// no removable paths
	if(!IsPathFixed(g_lpLongMsg))
	{
		// check flag
		if(!bSilent)
		{
			LockGlobalLongTTMsg()

				// prepare message
			sprintf(g_lpLongTTMsg,
					"The path '%s' is on a removable device (floppy disk, CD-ROM, etc.).\n\nOnly folders on fixed devices can be used as screensaver search paths.",
					lpPath);

			// show message
			DisplayInfoMessage(g_lpLongTTMsg);

			UnlockGlobalLongTTMsg()
		}

		UnlockGlobalLongMsg()

		// do not add
		return(FALSE);
	}

	// prepare item info
	lvi.mask    =LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	lvi.iItem   =GetItemCount();
	lvi.iSubItem=0;
	lvi.pszText =lpPath;

	// set image index
	lvi.iImage=(bDefault ? 1 : 0);
	
	// set default flag
	lvi.lParam=(bDefault ? 1 : 0);

	// add item to list
	if(InsertItem(&lvi)==-1)
	{
		if(!bSilent)
			DisplayNEErrorMessage("Unable to add item to path list.");
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	UnlockGlobalLongMsg()

	// check silent flag
	if(!bSilent)
	{
		// select new item
		SetItemState(GetItemCount()-1,
					 LVIS_FOCUSED|
					 LVIS_SELECTED,
					 0xFF);

		// set visibile
		EnsureVisible(GetItemCount()-1,
					  FALSE);


		// set parent modified
		g_lpPlaybackPage->SetModified();

		// display message
		DisplayOptMessageBox(SPATH_CHGNOTIFY,
							 (LPCSTR)ApplicationName(),
							 MB_OK|MB_ICONINFORMATION,
							 "MsgBox_SearchList");
	}

	// ok
	return(TRUE);
}

// CreateSearchPathImageList()

BOOL CreateSearchPathImageList(void)
{
	// reset return value
	BOOL bRet=FALSE;

	// device contexts
	CDC SrcDC;
	CDC DestDC;
	CDC* lpDesktopDC=NULL;

	// bitmap objects
	CBitmap* lpBmp1 =NULL;
	CBitmap* lpBmp2 =NULL;
	CBitmap* lpBmp1A=NULL;
	CBitmap* lpBmp2A=NULL;

	// gdi objects
	CGdiObject* lpSrcObj =NULL;
	CGdiObject* lpDestObj=NULL;

	// reset bitmap-ok flags
	BOOL bBmp1OK=FALSE;
	BOOL bBmp2OK=FALSE;

	// create bitmap object #1
	AllocClassObject(lpBmp1,
					 CBitmap);

	// check new object
	if(!lpBmp1)
		goto CreateSearchPathImageList1;

	// create bitmap object #2
	AllocClassObject(lpBmp2,
					 CBitmap);

	// check new object
	if(!lpBmp2)
		goto CreateSearchPathImageList1;

	// create bitmap object #1A
	AllocClassObject(lpBmp1A,
					 CBitmap);

	// check new object
	if(!lpBmp1A)
		goto CreateSearchPathImageList1;

	// create bitmap object #2A
	AllocClassObject(lpBmp2A,
					 CBitmap);

	// check new object
	if(!lpBmp2A)
		goto CreateSearchPathImageList1;

	// load bitmap #1
	if(!lpBmp1->LoadBitmap(IDB_FOLDER))
	{
		DisplayErrorMessage("Unable to load search path bitmap.");
		goto CreateSearchPathImageList1;
	}

	// load bitmap #2
	if(!lpBmp2->LoadBitmap(IDB_FOLDERLT))
	{
		DisplayErrorMessage("Unable to load search path bitmap.");
		goto CreateSearchPathImageList1;
	}

	// get desktop device context
	lpDesktopDC=CDC::FromHandle(::GetDC(GetDesktopWindow()));

	// create source device context
	if(SrcDC.CreateCompatibleDC(lpDesktopDC))
	{
		AddWinResource

		// create destination device context
		if(DestDC.CreateCompatibleDC(lpDesktopDC))
		{
			AddWinResource

			// create bitmap #1A
			if(lpBmp1A->CreateCompatibleBitmap(lpDesktopDC,
											   16,16))
			{
				// select bitmaps
				lpSrcObj =SrcDC.SelectObject(lpBmp1);
				lpDestObj=DestDC.SelectObject(lpBmp1A);

				// draw background
				DestDC.FillSolidRect(0,0,
									 16,16,
									 GetSysColor(COLOR_WINDOW));

				// draw bitmap
				TransparentBlt(DestDC.m_hDC,
							   0,0,
							   16,16,
							   SrcDC.m_hDC,
							   0,0,
							   16,16,
							   RGB(255,0,255));

				// restore objects
				SrcDC.SelectObject(lpSrcObj);
				DestDC.SelectObject(lpDestObj);

				// set flag
				bBmp1OK=TRUE;
			}

			// create bitmap #2A
			if(lpBmp2A->CreateCompatibleBitmap(lpDesktopDC,
											   16,16))
			{
				// select bitmaps
				lpSrcObj =SrcDC.SelectObject(lpBmp2);
				lpDestObj=DestDC.SelectObject(lpBmp2A);

				// draw background
				DestDC.FillSolidRect(0,0,
									 16,16,
									 GetSysColor(COLOR_WINDOW));

				// draw bitmap
				TransparentBlt(DestDC.m_hDC,
							   0,0,
							   16,16,
							   SrcDC.m_hDC,
							   0,0,
							   16,16,
							   RGB(255,0,255));

				// restore objects
				SrcDC.SelectObject(lpSrcObj);
				DestDC.SelectObject(lpDestObj);

				// set flag
				bBmp2OK=TRUE;
			}

			// delete destination dc
			if(DestDC.DeleteDC())
				RemoveWinResource
		}
		
		// delete source dc
		if(SrcDC.DeleteDC())
			RemoveWinResource
	}

	// check flag #1
	if(!bBmp1OK)
	{
		// swap bitmaps
		SwapPtrs((LPVOID*)&lpBmp1,
				 (LPVOID*)&lpBmp1A);

		// release old bitmap
		FreeClassObject(lpBmp1);
	}

	// check flag #2
	if(!bBmp2OK)
	{
		// swap bitmaps
		SwapPtrs((LPVOID*)&lpBmp2,
				 (LPVOID*)&lpBmp2A);

		// release old bitmap
		FreeClassObject(lpBmp2);
	}

	// create list
	if(!g_lpSPathImageList->Create(16,16,
								   ILC_COLORDDB,
								   1,1))
	{
		DisplayErrorMessage("Unable to create search path image list.");
		goto CreateSearchPathImageList1;
	}

	// add image #1 to list
	if(g_lpSPathImageList->Add(lpBmp1A,
							   (COLORREF)NULL)==-1)
	{
		DisplayErrorMessage("Unable to add search path image to list.");
		goto CreateSearchPathImageList1;
	}
	
	// add image #2 to list
	if(g_lpSPathImageList->Add(lpBmp2A,
							   (COLORREF)NULL)==-1)
	{
		DisplayErrorMessage("Unable to add search path image to list.");
		goto CreateSearchPathImageList1;
	}
	
	// associate image list
	g_lpSearchPathList->SetImageList(g_lpSPathImageList,
									 LVSIL_SMALL);

	// set return value
	bRet=TRUE;

// error exit point
CreateSearchPathImageList1:;
						   
	// release bitmap objects
	FreeClassObject(lpBmp1);
	FreeClassObject(lpBmp2);
	FreeClassObject(lpBmp1A);
	FreeClassObject(lpBmp2A);

	// ok
	return(bRet);
}

// AddSearchPathsToList()

BOOL AddSearchPathsToList(void)
{
	LockGlobalLongMsg()

	// get windows folder
	if(!GetWindowsDirectory(g_lpLongMsg,
							_MAX_PATH))
	{
		DisplayErrorMessage("Unable to read Windows folder path.");
		return(FALSE);
	}

	// add to list
	if(!g_lpSearchPathList->AddPath(g_lpLongMsg,
									TRUE,
									TRUE))
		return(FALSE);

	// get system folder
	if(!GetSystemDirectory(g_lpLongMsg,
						   _MAX_PATH))
	{
		DisplayErrorMessage("Unable to read system folder path.");
		return(FALSE);
	}

	// add to list
	if(!g_lpSearchPathList->AddPath(g_lpLongMsg,
									TRUE,
									TRUE))
		return(FALSE);

	UnlockGlobalLongMsg()

	// add search paths from registry
	if(!LoadSearchPathsFromReg(ApplicationRegistryPath(),
							   "SearchPaths"))
		return(FALSE);

	// ok
	return(TRUE);
}

// SaveSearchPathsToReg()

BOOL SaveSearchPathsToReg(LPCSTR lpAppKey,
						  LPCSTR lpSubKey)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpAppKey||
	   !lpSubKey)
	{
		DisplayErrorMessage("Invalid string pointer.",
							"SaveSearchPathsToReg()",
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

	// item index
	int nItem;

	// default flag
	BOOL bDef;

	// reset return value
	bRet=TRUE;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	// get number of items
	nNumItems=g_lpSearchPathList->GetItemCount();

	LockGlobalLongMsg()
	
	// create registry path
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

		// reset counter
		nCount=0;

		// reset item index
		nItem=0;

		// output values
		while(TRUE)
		{
			LockGlobalLongMsg()

			// check counter
			if(nCount<nNumItems)
			{
				// copy path
				strcpy(g_lpLongMsg,
					   g_lpSearchPathList->GetItemText(nCount,
													   0).GetBuffer(_MAX_PATH));

				// clip string
				g_lpLongMsg[_MAX_PATH]=NULL;
				
				// set default flag
				bDef=(g_lpSearchPathList->GetItemData(nCount)==1) ? TRUE : FALSE;
			}
			else
			{
				// clear path
				strcpy(g_lpLongMsg,
					   NULL_STRING);

				// reset default flag
				bDef=FALSE;
			}

			// check default flag
			if(!bDef)
			{
				LockGlobalMsg()

				// create key name
				sprintf(g_lpMsg,
						"Path%u",
						nItem);

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
				
				// increment item index
				nItem++;
			}

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

	// return result
	return(bRet);
}

// LoadSearchPathsFromReg()

BOOL LoadSearchPathsFromReg(LPCSTR lpAppKey,
							LPCSTR lpSubKey,
							BOOL bScanAddOnly)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpAppKey||
	   !lpSubKey)
	{
		DisplayErrorMessage("Invalid string pointer.",
							"LoadSearchPathsFromReg()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// length of buffer
	DWORD dwLen;

	// reset continue flag
	BOOL bCont=TRUE;

	// reset counter
	int nCount=0;

	// path string
	LPSTR lpPath=NULL;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	LockGlobalMsg()

	// create registry path
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
					"Path%u",
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
					// check scan-&-add flag
					if(bScanAddOnly)
					{
						// allocate memory for path
						if(AllocMem((LPVOID*)&lpPath,
									strlen(g_lpLongMsg)+16))
						{
							// copy path
							strcpy(lpPath,
								   g_lpLongMsg);

							UnlockGlobalLongMsg()

							// get screensavers
							GetScreensaversFromFolder(lpPath);

							// free path string
							FreeMem((LPVOID*)&lpPath);
						}
						else
							UnlockGlobalLongMsg()
					}
					else
					{
						// add path to list
						g_lpSearchPathList->AddPath(g_lpLongMsg,
													FALSE,
													TRUE);

						UnlockGlobalLongMsg()
					}
				}
			}

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

	// ok
	return(TRUE);
}

// CPathListCtrl::PathIsInList()

BOOL CPathListCtrl::PathIsInList(LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string pointer.",
							"CPathListCtrl::PathIsInList()",
							FALSE);
		return(FALSE);
	}
#endif

	// number of items
	int nNumItems;

	// item counter
	int nItem;

	// get item count
	nNumItems=GetItemCount();

	// check item count
	if(nNumItems)
	{
		LockGlobalMsg()
		
		// get short path name
		if(GetShortPathName(lpPath,
						    g_lpMsg,
						    _MAX_PATH)!=0)
		{
			// convert to lowercase
			strlwr(g_lpMsg);

			// loop through items
			for(nItem=0;nItem<nNumItems;nItem++)
			{
				LockGlobalTTMsg()
				LockGlobalLongTTMsg()

				// get path
				GetItemText(nItem,
							0,
							g_lpLongTTMsg,
							_MAX_PATH);

				// get short path name
				if(GetShortPathName(g_lpLongTTMsg,
									g_lpTTMsg,
									_MAX_PATH)!=0)
				{
					// convert to lowercase
					strlwr(g_lpTTMsg);

					// compare paths
					if(strcmp(g_lpMsg,
							  g_lpTTMsg)==0)
					{
						UnlockGlobalMsg()
						UnlockGlobalTTMsg()
						UnlockGlobalLongTTMsg()

						// found
						return(TRUE);
					}
				}

				UnlockGlobalTTMsg()
				UnlockGlobalLongTTMsg()
			}
		}

		UnlockGlobalMsg()
	}

	// not found
	return(FALSE);
}

// CPathListCtrl::OnItemChanged()

void CPathListCtrl::OnItemChanged(NMHDR* pNMHDR,
							      LRESULT* pResult)
{
	// get pointer to item change header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// new selection
	if(lpLV->uNewState&LVIS_SELECTED&&
	   !(lpLV->uOldState&LVIS_SELECTED))
	{
		// check for default item
		if(GetItemData(lpLV->iItem)!=1)
		{
			// enable buttons
			g_lpChangePathBtn->Enable();
			g_lpDeletePathBtn->Enable();
		}

		// play sound
		PlaySound(IDR_NEWSELSND);
	}
	
	// cleared selection
	if(!(lpLV->uNewState&LVIS_SELECTED)&&
	   lpLV->uOldState&LVIS_SELECTED)
	{
		// disable buttons
		g_lpChangePathBtn->Disable();
		g_lpDeletePathBtn->Disable();
	}

	// set return value
	(*pResult)=NULL;
}

// CPathListCtrl::PreSubclassWindow()

void CPathListCtrl::PreSubclassWindow(void)
{
	// call base function
	CListCtrl::PreSubclassWindow();

	// enable tooltips
	EnableToolTips(TRUE);
}

// CPathListCtrl::CellRectFromPoint()

int CPathListCtrl::CellRectFromPoint(CPoint point,
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
			// add size of small icon & white space
			nRectWidth=nStringWidth+23;

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

	// not found
	return(-1);
}

// CPathListCtrl::OnToolHitTest()

int CPathListCtrl::OnToolHitTest(CPoint point,
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

// CPathListCtrl::OnTTNeedText()

BOOL CPathListCtrl::OnTTNeedText(UINT nID,
							     NMHDR* pNMHDR,
							     LRESULT* pResult)
{
	// cast pointers to tooltip info
	LPTOOLTIPTEXTA lpTTTa=(LPTOOLTIPTEXTA)pNMHDR;
	LPTOOLTIPTEXTW lpTTTw=(LPTOOLTIPTEXTW)pNMHDR;

	// client rect
	CRect rWnd;

	// get actual id
	nID=pNMHDR->idFrom;

	// check for winnt auto tooltip
	if(nID==0)
		return(FALSE);

	// copy text
	GetItemText(nID-1,
				0,
				g_lpTTMsg,
				_MAX_PATH);

	// get client rect
	GetClientRect(&rWnd);

	// check for string overflow
	if((GetStringWidth(g_lpTTMsg)+28)<rWnd.Width())
	{
		// text fits, so no tooltip
		strcpy(g_lpTTMsg,
			   NULL_STRING);
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

// CPlaybackPage::OnShowAdvancedBtnClk()

void CPlaybackPage::OnShowAdvancedBtnClk(void)
{
	// play sound
	PlaySound(IDR_SORTSND);
	
	// show options
	ShowAdvancedOptions(TRUE);
}

// CPlaybackPage::OnHideAdvancedBtnClk()

void CPlaybackPage::OnHideAdvancedBtnClk(void)
{
	// play sound
	PlaySound(IDR_SORTSND);
	
	// hide options
	ShowAdvancedOptions(FALSE);
}

// CPathListCtrl::ChangeSelection()

BOOL CPathListCtrl::ChangeSelection(void)
{
	// selected item
	int nSelItem;

	// pointer to current path
	LPSTR lpCurPath;

	// get selection
	nSelItem=GetSelection();

	// check selection
	if(nSelItem==-1)
		return(FALSE);
	
	// check for default item
	if(GetItemData(nSelItem)==1)
	{
		DisplayInfoMessage("You cannot change the default search paths.");
		return(FALSE);
	}

	LockGlobalMsg()

	// get selected path
	if(GetItemText(nSelItem,
				   0,
				   g_lpMsg,
				   _MAX_PATH))
	{
		// set current path
		lpCurPath=g_lpMsg;
	}
	else
	{
		// reset current path
		lpCurPath=NULL;
	}

	UnlockGlobalMsg()
	LockGlobalLongMsg()

	// get path from user
	if(!SelectPathDlg(g_lpPlaybackPage,
					  g_lpLongMsg,
					  lpCurPath,
					  "Please select a new folder to replace the current selection."))
	{
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	// make sure path is valid
	if(!DoesPathExist(g_lpLongMsg))
	{
		LockGlobalLongTTMsg()

		// prepare message
		sprintf(g_lpLongTTMsg,
				"The path '%s' is not valid.",
				g_lpLongMsg);

		// show message
		DisplayErrorMessage(g_lpLongTTMsg);

		UnlockGlobalLongTTMsg()
		UnlockGlobalLongMsg()

		// do not add
		return(FALSE);
	}

	// check for duplicate path
	if(PathIsInList(g_lpLongMsg))
	{
		LockGlobalMsg()

		// restore current path
		if(GetItemText(nSelItem,
					   0,
					   g_lpMsg,
					   _MAX_PATH))
		{
			// set current path
			lpCurPath=g_lpMsg;
		}
		else
		{
			// reset current path
			lpCurPath=NULL;
		}

		UnlockGlobalMsg()

		// check for same path
		if(stricmp(g_lpLongMsg,
				   lpCurPath)!=0)
		{
			LockGlobalLongTTMsg()

			// prepare message
			sprintf(g_lpLongTTMsg,
					"The selected path:\n\n'%s'\n\nis already in the search list.",
					g_lpLongMsg);

			// show message
			DisplayErrorMessage(g_lpLongTTMsg);

			UnlockGlobalLongTTMsg()
		}

		UnlockGlobalLongMsg()

		// do not add
		return(FALSE);
	}

	// update text
	SetItemText(nSelItem,
				0,
				g_lpLongMsg);

	UnlockGlobalLongMsg()

	// select new item
	SetItemState(nSelItem,
				 LVIS_FOCUSED|
				 LVIS_SELECTED,
				 0xFF);

	// set visibile
	EnsureVisible(nSelItem,
				  FALSE);

	// set parent modified
	g_lpPlaybackPage->SetModified();

	// display message
	DisplayOptMessageBox(SPATH_CHGNOTIFY,
						 (LPCSTR)ApplicationName(),
						 MB_OK|MB_ICONINFORMATION,
						 "MsgBox_SearchList");

	// ok
	return(TRUE);
}

// CPathListCtrl::DeleteSelection()

BOOL CPathListCtrl::DeleteSelection(void)
{
	// selected item
	int nSelItem;

	// number of items
	int nNumItems;

	// get selection
	nSelItem=GetSelection();

	// check selection
	if(nSelItem==-1)
		return(FALSE);
	
	// check for default item
	if(GetItemData(nSelItem)==1)
	{
		DisplayInfoMessage("You cannot remove the default search paths.");
		return(FALSE);
	}

	// query user
	if(DisplayMessageBox(g_lpPlaybackPage->m_hWnd,
						 "Are you sure you want to remove the selected path from the search list?",
						 (LPSTR)ApplicationName(),
						 MB_YESNO|MB_ICONQUESTION)==IDNO)
		return(FALSE);

	// remove selection
	DeleteItem(nSelItem);

	// get number of items
	nNumItems=GetItemCount();

	// validate next item
	if(nSelItem>=nNumItems)
		nSelItem=nNumItems-1;

	// highlight next item
	SetItemState(nSelItem,
				 LVIS_FOCUSED|
				 LVIS_SELECTED,
				 0xFF);

	// make sure item is visible
	EnsureVisible(nSelItem,
				  FALSE);

	// give focus to search list
	SetFocus();

	// play sound
	PlaySound(IDR_CLEARSELSND);

	// set parent modified
	g_lpPlaybackPage->SetModified();

	// display message
	DisplayOptMessageBox(SPATH_CHGNOTIFY,
						 (LPCSTR)ApplicationName(),
						 MB_OK|MB_ICONINFORMATION,
						 "MsgBox_SearchList");

	// ok
	return(TRUE);
}

// CPathListCtrl::OnKeyDown()

void CPathListCtrl::OnKeyDown(UINT nChar,
						      UINT nRepCnt,
						      UINT nFlags)
{
	// check for del key
	if(nChar==VK_DELETE)
		DeleteSelection();

	// call base method
	CListCtrl::OnKeyDown(nChar,
						 nRepCnt,
						 nFlags);
}

// CPlaybackPage::OnSystemTrayChkClk()

void CPlaybackPage::OnSystemTrayChkClk(void)
{
	// toggle system-tray
	ToggleSystemTray();
}

// CPlaybackPage::OnKeepCurrentChkClk()

void CPlaybackPage::OnKeepCurrentChkClk(void)
{
	// toggle keep-current
	ToggleKeepCurrent();
}

// CPlaybackPage::OnHideAdvancedChkClk()

void CPlaybackPage::OnHideAdvancedChkClk(void)
{
	// toggle hide-advanced
	ToggleHideAdvanced();
}

// ToggleSystemTray()

void ToggleSystemTray(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bSystemTray=(g_bSystemTray ? FALSE : TRUE);

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set check state
	g_lpSystemTrayChk->SetCheck(g_bSystemTray ? 1 : 0);
}

// ToggleKeepCurrent()

void ToggleKeepCurrent(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bKeepCurrent=(g_bKeepCurrent ? FALSE : TRUE);

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set check state
	g_lpKeepCurrentChk->SetCheck(g_bKeepCurrent ? 1 : 0);
}

// ToggleHideAdvanced()

void ToggleHideAdvanced(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bHideAdvanced=(g_bHideAdvanced ? FALSE : TRUE);

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// set check state
	g_lpHideAdvancedChk->SetCheck(g_bHideAdvanced ? 1 : 0);
}

// CPlaybackPage::OnErrorLogChkClk()

void CPlaybackPage::OnErrorLogChkClk(void)
{
	// toggle error log
	ToggleErrorLog();
}

// CPlaybackPage::OnErrorLogBtnClk()

void CPlaybackPage::OnErrorLogBtnClk(void)
{
	// view error log
	ViewErrorLog();
}

// ToggleErrorLog()

void ToggleErrorLog(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bKeepErrorLog=(g_bKeepErrorLog ? FALSE : TRUE);

		// set parent modified
		g_lpPlaybackPage->SetModified();
	}

	// check flag
	if(g_bKeepErrorLog)
	{
		// set check
		g_lpErrorLogChk->SetCheck(1);

		// enable controls
		g_lpMaxLinesTxt->Enable();
		g_lpMaxLinesEdit->Enable();
		g_lpErrorLogBtn->Enable();
	}
	else
	{
		// clear check
		g_lpErrorLogChk->SetCheck(0);

		// disable controls
		g_lpMaxLinesTxt->Disable();
		g_lpMaxLinesEdit->Disable();
		g_lpErrorLogBtn->Disable();
	}
}

// ShowAdvancedOptions()

void ShowAdvancedOptions(BOOL bShow)
{
	// check init flags
	if(g_bPlaybackPageInit&&
	   g_bPlaybackPageInitOK)
	{
		// check flag
		if(bShow)
		{
			// hide windows
			g_lpAdvWarningTxt->ShowWindow(SW_HIDE);
			g_lpShowAdvancedBtn->ShowWindow(SW_HIDE);

			// show windows
			g_lpSearchPathBox->ShowWindow(SW_SHOW);
			g_lpSearchPathList->ShowWindow(SW_SHOW);
			g_lpAddPathBtn->ShowWindow(SW_SHOW);
			g_lpChangePathBtn->ShowWindow(SW_SHOW);
			g_lpDeletePathBtn->ShowWindow(SW_SHOW);
			g_lpSystemTrayChk->ShowWindow(SW_SHOW);
			g_lpKeepCurrentChk->ShowWindow(SW_SHOW);
			g_lpHideAdvancedChk->ShowWindow(SW_SHOW);
			g_lpErrorLogBox->ShowWindow(SW_SHOW);
			g_lpErrorLogChk->ShowWindow(SW_SHOW);
			g_lpMaxLinesTxt->ShowWindow(SW_SHOW);
			g_lpMaxLinesEdit->ShowWindow(SW_SHOW);
			g_lpMaxLinesEdit->lpSpinCtrl->ShowWindow(SW_SHOW);
			g_lpErrorLogBtn->ShowWindow(SW_SHOW);
			g_lpResetMessagesBtn->ShowWindow(SW_SHOW);
			g_lpHideAdvancedBtn->ShowWindow(SW_SHOW);

			// set viewed flag
			g_bAdvOptViewed=TRUE;

			// set visible flag
			g_bAdvOptVisible=TRUE;
		}
		else
		{
			// hide windows
			g_lpSearchPathBox->ShowWindow(SW_HIDE);
			g_lpSearchPathList->ShowWindow(SW_HIDE);
			g_lpAddPathBtn->ShowWindow(SW_HIDE);
			g_lpChangePathBtn->ShowWindow(SW_HIDE);
			g_lpDeletePathBtn->ShowWindow(SW_HIDE);
			g_lpSystemTrayChk->ShowWindow(SW_HIDE);
			g_lpKeepCurrentChk->ShowWindow(SW_HIDE);
			g_lpHideAdvancedChk->ShowWindow(SW_HIDE);
			g_lpErrorLogBox->ShowWindow(SW_HIDE);
			g_lpErrorLogChk->ShowWindow(SW_HIDE);
			g_lpMaxLinesTxt->ShowWindow(SW_HIDE);
			g_lpMaxLinesEdit->ShowWindow(SW_HIDE);
			g_lpMaxLinesEdit->lpSpinCtrl->ShowWindow(SW_HIDE);
			g_lpErrorLogBtn->ShowWindow(SW_HIDE);
			g_lpResetMessagesBtn->ShowWindow(SW_HIDE);
			g_lpHideAdvancedBtn->ShowWindow(SW_HIDE);

			// show windows
			g_lpAdvWarningTxt->ShowWindow(SW_SHOW);
			g_lpShowAdvancedBtn->ShowWindow(SW_SHOW);

			// clear visible flag
			g_bAdvOptVisible=FALSE;
		}
	}
}

// LoadAdvancedOptions()

BOOL LoadAdvancedOptions(void)
{
	// load misc. flags
	g_bSystemTray=(BOOL)LoadOptionInt("Adv_SystemTray",
									  0,
									  1,
									  1);
	g_bKeepCurrent=(BOOL)LoadOptionInt("Adv_KeepCurrent",
									   0,
									   1,
									   1);
	g_bHideAdvanced=(BOOL)LoadOptionInt("Adv_HideAdvanced",
									    0,
									    1,
									    1);
	g_bKeepErrorLog=(BOOL)LoadOptionInt("Adv_KeepErrorLog",
									    0,
									    1,
									    1);

	// load error-log lines
	g_nErrorLogLines=LoadOptionInt("Adv_ErrLogLines",
								   50,
								   400,
								   100);

	// ok
	return(TRUE);
}

// SaveAdvancedOptions()

void SaveAdvancedOptions(void)
{
	// check viewed flag
	if(g_bAdvOptViewed)
	{
		LockGlobalMsg()

		// get error-log lines
		if(g_lpMaxLinesEdit->GetWindowText(g_lpMsg,
										   _MAX_PATH)!=0)
		{
			// update error-log lines
			g_nErrorLogLines=atoi(g_lpMsg);

			UnlockGlobalMsg()

			// check value
			if(g_nErrorLogLines<50)
			{
				// set value
				g_nErrorLogLines=50;

				// update edit box
				g_lpMaxLinesEdit->SetWindowText("50");

				// alert user
				DisplayInfoMessage("The minimum length for the error log is 50 lines.\n\nThis value has been reset to 50 lines.");
			}
		}
		else
			UnlockGlobalMsg()

		// save search paths
		SaveSearchPathsToReg(ApplicationRegistryPath(),
							 "SearchPaths");

		// save misc. flags
		SaveOptionInt("Adv_SystemTray",
					  (int)g_bSystemTray);
		SaveOptionInt("Adv_KeepCurrent",
					  (int)g_bKeepCurrent);
		SaveOptionInt("Adv_HideAdvanced",
					  (int)g_bHideAdvanced);
		SaveOptionInt("Adv_KeepErrorLog",
					  (int)g_bKeepErrorLog);

		// save error log lines
		SaveOptionInt("Adv_ErrLogLines",
					  g_nErrorLogLines);
	}
}

// CPlaybackPage::OnResetMessagesBtnClk()

void CPlaybackPage::OnResetMessagesBtnClk(void)
{
	// reset messages
	RestoreBlockedMessages();
}

// RestoreBlockedMessages()

BOOL RestoreBlockedMessages(void)
{
	// registry key interface
	CRegKey* lpRegKey=NULL;

	// return value
	BOOL bRet;

	// counter
	DWORD dwCount;

	// flag
	long lFlag;

	// buffer size
	DWORD dwBufSz;

	// displaced byte
	char cByte;

	// reset return value
	bRet=TRUE;

	// query user
	if(DisplayMessageBox(g_lpPlaybackPage->m_hWnd,
						 "This will restore all of the messages that you have previously chosen not to display.\n\nAre you sure?",
						 (LPSTR)ApplicationName(),
						 MB_YESNO|MB_ICONWARNING)==IDYES)
	{
		// get key interface
		AllocClassObject(lpRegKey,
						 CRegKey);

		// check new object
		if(!lpRegKey)
			return(FALSE);

		LockGlobalLongMsg()
		
		// create registry path
		strcpy(g_lpLongMsg,
			   ApplicationRegistryPath());
		strcat(g_lpLongMsg,
			   "Options");

		// open registry key
		if(lpRegKey->Open(HKEY_CURRENT_USER,
						  g_lpLongMsg)==ERROR_SUCCESS)
		{
			AddWinResource

			UnlockGlobalLongMsg()

			// reset counter
			dwCount=0;

			// reset flag
			lFlag=ERROR_SUCCESS;

			LockGlobalLongMsg()

			// enumerate values
			while(lFlag==ERROR_SUCCESS)
			{
				// set buffer size
				dwBufSz=_MAX_PATH;

				// get next value
				lFlag=RegEnumValue(lpRegKey->m_hKey,
								   dwCount++,
								   g_lpLongMsg,
								   &dwBufSz,
								   NULL,
								   NULL,
								   NULL,
								   NULL);

				// check flag
				if(lFlag!=ERROR_SUCCESS)
				{
					// check for no more items
					if(lFlag!=ERROR_NO_MORE_ITEMS)
					{
						DisplayErrorMessage("Unable to enumerate system registry values.");
						bRet=FALSE;
					}
				}
				else
				{
					// save byte
					cByte=g_lpLongMsg[6];

					// clip at 6 bytes
					g_lpLongMsg[6]=0;

					// compare with 'MsgBox'
					if(strcmp(g_lpLongMsg,
							  "MsgBox")==0)
					{
						// restore byte
						g_lpLongMsg[6]=cByte;

						// delete value
						if(lpRegKey->DeleteValue(g_lpLongMsg)!=ERROR_SUCCESS)
						{
							DisplayNEErrorMessage("Unable to delete registry key value.");
							bRet=FALSE;
						}

						// start over
						dwCount=0;
					}
				}
			}

			UnlockGlobalLongMsg()

			// close registry key
			if(lpRegKey->Close()==ERROR_SUCCESS)
				RemoveWinResource
		}
		else
			UnlockGlobalLongMsg()

		// relese key interface
		FreeClassObject(lpRegKey);

		// play sound
		PlaySound(IDR_DELALLSND);
	}

	// return result
	return(bRet);
}

// ViewErrorLog()

BOOL ViewErrorLog(void)
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
		   "errorlog.txt");

	// open file
	if(!OpenExternalDoc(g_lpLongMsg,
						NULL,
						TRUE))
	{
		// alert user
		DisplayInfoMessage("The error log has not yet been created.\n\nErrors are recorded only during screensaver playback.");
	}

	UnlockGlobalLongMsg()

	// end wait
	::EndWaitCursor();

	// ok
	return(TRUE);
}

// eof //

// Copyright 2006 WaveBreak Software
