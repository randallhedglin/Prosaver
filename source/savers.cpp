// Copyright 2006 WaveBreak Software

// savers.cpp -- screensaver settings functions

// includes //

#include"main.h"

// message maps //

BEGIN_MESSAGE_MAP(CSaverPage,CPropertyPage)
	ON_BN_CLICKED(IDC_ADDSAVERBTN,   OnAddSaverBtnClk)
	ON_BN_CLICKED(IDC_CLEARSELBTN,   OnClearSelBtnClk)
	ON_BN_CLICKED(IDC_SETTINGSBTN,   OnSettingsBtnClk)
	ON_BN_CLICKED(IDC_PREVIEWBTN,    OnPreviewBtnClk)
	ON_BN_CLICKED(IDC_EDITINFOBTN,   OnEditInfoBtnClk)
	ON_BN_CLICKED(IDC_SHOWPREVIEWCHK,OnShowPreviewChkClk)
	ON_BN_CLICKED(IDC_PLISTUPBTN,    OnUpBtnClk)
	ON_BN_CLICKED(IDC_PLISTDOWNBTN,  OnDownBtnClk)
	ON_BN_CLICKED(IDC_PLISTTOPBTN,   OnTopBtnClk)
	ON_BN_CLICKED(IDC_PLISTBOTTOMBTN,OnBottomBtnClk)
	ON_BN_CLICKED(IDC_PLISTDELBTN,   OnDeleteBtnClk)
	ON_BN_CLICKED(IDC_PLISTCLRBTN,   OnClearBtnClk)
	ON_BN_CLICKED(IDC_PLISTSAVEBTN,  OnSaveBtnClk)
	ON_BN_CLICKED(IDC_PLISTLOADBTN,  OnLoadBtnClk)
	ON_WM_CONTEXTMENU()
	ON_WM_ACTIVATE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSaverList,CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,  OnCustomDraw)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK,OnColumnClick)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED,OnItemChanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK,      OnDblClick)
	ON_NOTIFY_REFLECT(NM_RCLICK,      OnRtClick)
	ON_NOTIFY_REFLECT(NM_CLICK,       OnClick)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA,0,0xFFFF,OnTTNeedText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW,0,0xFFFF,OnTTNeedText)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSaverInfoBox,CExtRichEditCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSaverPreviewWnd,CWnd)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSaverPreviewBox,CExtStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSaverInfoDlg,CExtDialog)
	ON_BN_CLICKED(IDC_EDITTHEMESBTN,  OnEditThemesBtnClk)
	ON_BN_CLICKED(IDC_EDITHELPBTN,    OnHelpBtnClk)
	ON_BN_CLICKED(IDC_MUSICBROWSEBTN, OnBrowseBtnClk)
	ON_BN_CLICKED(IDC_MUSICCYCLERAD,  OnMusicCycleBtnClk)
	ON_BN_CLICKED(IDC_MUSICSHUFFLERAD,OnMusicShuffleBtnClk)
	ON_BN_CLICKED(IDC_DISABLEPREVCHK, OnDisablePrevChkClk)
	ON_MESSAGE(WM_HELP,OnWmHelp)
	ON_WM_CONTEXTMENU()
	ON_WM_SHOWWINDOW()
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CEditThemesDlg,CExtDialog)
	ON_BN_CLICKED(IDC_NEWTHEMEBTN,   OnNewBtnClk)
	ON_BN_CLICKED(IDC_DELTHEMEBTN,   OnDelBtnClk)
	ON_BN_CLICKED(IDC_RENAMETHEMEBTN,OnRenBtnClk)
	ON_BN_CLICKED(IDC_DEFTHEMESBTN,  OnDefBtnClk)
	ON_BN_CLICKED(IDC_THEMESHELPBTN, OnHelpBtnClk)
	ON_MESSAGE(WM_HELP,OnWmHelp)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CNewThemeDlg,CExtDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CRenameThemeDlg,CExtDialog)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CThemesList,CListBox)
	ON_WM_CONTEXTMENU()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSaverPlaylist,CPlaylistCtrl)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED,OnItemChanged)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CSaverSortBox,CExtComboBox)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// globals //

// main property page
CSaverPage* g_lpSaverPage=NULL;
// screensaver info list
CSaverInfo* g_lpSaverInfo=NULL;
// screensaver list
CSaverList* g_lpSaverList=NULL;
// saver list header
CExtHeaderCtrl* g_lpSaverListHdr=NULL;
// screensaver icons
CImageList* g_lpSaverIcons=NULL;
// page init flag
BOOL g_bSaverPageInit=FALSE;
// page init-ok flag
BOOL g_bSaverPageInitOK=FALSE;
// current saver selection
CSaverInfo* g_lpCurSaver=NULL;
// list control fonts
CFont* g_lpLCFont=NULL;
CFont* g_lpLCFontBold=NULL;
// saver info box
CSaverInfoBox* g_lpSaverInfoBox=NULL;
// buttons
CExtButton* g_lpClearSelBtn=NULL;
CExtButton* g_lpAddSaverBtn=NULL;
CExtButton* g_lpSaverSettingsBtn=NULL;
CExtButton* g_lpPreviewSaverBtn=NULL;
CExtButton* g_lpEditSaverInfoBtn=NULL;
// checkboxes
CExtButton* g_lpMiniPreviewChk=NULL;
// bitmaps
CBitmap* g_lpRatingBmp=NULL;
CBitmap* g_lpDimRatingBmp=NULL;
// settings
DWORD g_dwLastSlsFlag=SLS_TITLEASC;
BOOL g_bShowSaverInfo=TRUE;
BOOL g_bShowRatingImgs=TRUE;
BOOL g_bShowPopupInfo=TRUE;
BOOL g_bShowSaverPreview=TRUE;
BOOL g_bShowPListPopup=TRUE;
// last saver list selection flag
BOOL g_bLastSLSelFlag=FALSE;
// saver preview window objects
CSaverPreviewBox* g_lpSaverPrevBox=NULL;
CSaverPreviewWnd* g_lpSaverPrevWnd=NULL;
CBitmap* g_lpSaverCompBmp=NULL;
CBitmap* g_lpSaverScrnBmp=NULL;
// preview timer objects
UINT g_nPrevTimerId=NULL;
LPPROCESS_INFORMATION g_lpPrevPI=NULL;
// saver info dialog
CSaverInfoDlg* g_lpSaverInfoDlg=NULL;
// saver info icon
CExtStatic* g_lpSaverInfoIcon=NULL;
// themes list info
DWORD g_dwNumThemes=0;
DWORD g_dwMaxThemes=0;
LPSTR* g_lplpThemes=NULL;
// theme selection box
CExtComboBox* g_lpThemeSelBox=NULL;
// edit themes button
CExtButton* g_lpEditThemesBtn=NULL;
// rating selection box
CExtComboBox* g_lpRatingSelBox=NULL;
// edit saver help button
CExtButton* g_lpEditHelpBtn=NULL;
// music selection box
CExtEdit* g_lpMusicSelBox=NULL;
// music browse button
CExtButton* g_lpMusicBrowseBtn=NULL;
// music playback buttons
CExtButton* g_lpMusicCycleRad=NULL;
CExtButton* g_lpMusicShuffleRad=NULL;
// saver description label
CExtStatic* g_lpSaverDescLabel=NULL;
// saver description box
CExtEdit* g_lpSaverDescEdit=NULL;
// no-mini-preview button
CExtButton* g_lpNoMiniPrevChk=NULL;
// edit themes dialogs
CEditThemesDlg* g_lpEditThemesDlg=NULL;
CEditThemesDlg* g_lpEditThemesDlgA=NULL;
CEditThemesDlg* g_lpEditThemesDlgB=NULL;
// edit themes list
CThemesList* g_lpThemesList=NULL;
// edit themes buttons
CExtButton* g_lpNewThemeBtn=NULL;
CExtButton* g_lpDelThemeBtn=NULL;
CExtButton* g_lpRenThemeBtn=NULL;
CExtButton* g_lpDefThemesBtn=NULL;
CExtButton* g_lpThemesHelpBtn=NULL;
// new theme dialog
CNewThemeDlg* g_lpNewThemeDlg=NULL;
// new theme edit control
CExtEdit* g_lpNewThemeEdit=NULL;
// rename theme dialog
CRenameThemeDlg* g_lpRenThemeDlg=NULL;
// rename theme edit control
CExtEdit* g_lpRenThemeEdit=NULL;
// saver playlist control
CSaverPlaylist* g_lpSaverPlaylist=NULL;
// saver playlist header
CExtHeaderCtrl* g_lpSaverPlaylistHdr=NULL;
// saver playlist buttons
CExtButton* g_lpPListUpBtn=NULL;
CExtButton* g_lpPListDownBtn=NULL;
CExtButton* g_lpPListTopBtn=NULL;
CExtButton* g_lpPListBottomBtn=NULL;
CExtButton* g_lpPListDeleteBtn=NULL;
CExtButton* g_lpPListClearBtn=NULL;
CExtButton* g_lpPListSaveBtn=NULL;
CExtButton* g_lpPListLoadBtn=NULL;
// invalid playlist flag
BOOL g_bInvPListItems=FALSE;
// saver playlist sort box
CSaverSortBox* g_lpSaverSortBox=NULL;
// music manager dialog
CMusicManagerDlg* g_lpMusicManagerDlgB=NULL;
// screen-up timer id
UINT g_nScrnUpTimerId=NULL;
// saver-hook dll handle
HMODULE g_hSvrHookDll=NULL;
// saver-hook function pointer
CREATESAVERHOOK CreateSaverHook=NULL;

// functions //

// CSaverInfo::CSaverInfo()

CSaverInfo::CSaverInfo()
{
	// init values
	lpPath=NULL;
	lpRegPath=NULL;
	lpTitle=NULL;
	lpIcon=NULL;
	lpIconSm=NULL;
	lpTheme=NULL;
	dwRating=0;
	lpDesc=NULL;
	lpMusic=NULL;
	bShuffle=FALSE;
	bNoPreview=FALSE;
	bLoadOK=FALSE;
	lpNextSaver=NULL;
	bNew=FALSE;
	dwDupIdx=0;
	bIsDup=FALSE;
}

// CSaverInfo::DeleteSaverNode()

void CSaverInfo::DeleteSaverNode(void)
{
	// delete next saver (if available)
	if(lpNextSaver)
		lpNextSaver->DeleteSaverNode();

	// reset load-ok flag
	bLoadOK=FALSE;

	// release all objects
	FreeMem((LPVOID*)&lpPath);
	FreeMem((LPVOID*)&lpRegPath);
	FreeMem((LPVOID*)&lpTitle);
	FreeMem((LPVOID*)&lpTheme);
	FreeMem((LPVOID*)&lpDesc);
	FreeMem((LPVOID*)&lpMusic);
	FreeClassObject(lpIcon);
	FreeClassObject(lpIconSm);
	FreeClassObject(lpNextSaver);
}

// CSaverInfo::AddSaverInfo()

BOOL CSaverInfo::AddSaverInfo(LPSTR lpFilePath,
							  LPSTR lpFileName)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpFilePath||
	   !lpFileName)
	{
		DisplayErrorMessage("Invalid string value.",
							"AddSaverInfo()",
							FALSE);
		return(FALSE);
	}
#endif

	// handle to saver module
	HINSTANCE hInst=(HINSTANCE)INVALID_HANDLE_VALUE;

	// handle to saver icon
	HICON hIcon=(HICON)INVALID_HANDLE_VALUE;

	// secondary title
	LPSTR lpTitle2=NULL;

	// check for next saver
	if(lpNextSaver)
	{
		// add to next saver
		lpNextSaver->AddSaverInfo(lpFilePath,
								  lpFileName);
	}
	else
	{
		// allocate next saver
		AllocClassObject(lpNextSaver,
						 CSaverInfo);

		// check new object
		if(!lpNextSaver)
			return(FALSE);

		// allocate memory for path
		if(!AllocMem((LPVOID*)&lpPath,
					 strlen(lpFilePath)+strlen(lpFileName)+1))
			return(FALSE);

		// copy path to title
		strcpy(lpPath,
			   lpFilePath);

		// remove "*.scr"
		lpPath[strlen(lpPath)-5]=0;

		// add filename
		strcat(lpPath,
			   lpFileName);

		// load saver module
		hInst=LoadLibrary(lpPath);

		// check handle
		if(hInst)
		{
			AddWinResource

			LockGlobalMsg()

			// load first string resource (should be saver title)
			if(LoadString(hInst,
						  1,
						  g_lpMsg,
						  _MAX_PATH-1))
			{
				// check for this app
				if(strcmp(g_lpMsg,
						  ApplicationLongName())==0)
				{
					if(FreeLibrary(hInst))
						RemoveWinResource
					UnlockGlobalMsg()
					return(FALSE);
				}

				// allocate memory for title
				if(!AllocMem((LPVOID*)&lpTitle,
							 strlen(g_lpMsg)+3))
				{
					if(FreeLibrary(hInst))
						RemoveWinResource
					UnlockGlobalMsg()
					return(FALSE);
				}

				// copy ' '
				strcpy(lpTitle,
					   " ");
				
				// add filename
				strcat(lpTitle,
					   g_lpMsg);

				// add ' '
				strcat(lpTitle," ");
			}

			UnlockGlobalMsg()

			// close screensaver module
			if(FreeLibrary(hInst))
				RemoveWinResource
		}
		else
		{
			// not a screensaver
			return(FALSE);
		}

		// allocate memory for secondary title
		if(!AllocMem((LPVOID*)&lpTitle2,
					 strlen(lpFileName)+3))
		{
			if(FreeLibrary(hInst))
				RemoveWinResource
			return(FALSE);
		}

		// copy ' '
		strcpy(lpTitle2,
			   " ");
		
		// add filename
		strcat(lpTitle2,
			   lpFileName);

		// remove ".scr"
		lpTitle2[strlen(lpTitle2)-4]=0;

		// add ' '
		strcat(lpTitle2," ");

		// check for uc/lc
		if(lpTitle2[1]>='A'&&
		   lpTitle2[1]<='Z'&&
		   lpTitle2[2]>='a'&&
		   lpTitle2[2]<='z')
		{
			// release original title
			FreeMem((LPVOID*)&lpTitle);
		}
		else
		{
			// check for title
			if(lpTitle)
			{
				// release secondary title
				FreeMem((LPVOID*)&lpTitle2);
			}
		}

		// check title (again)
		if(!lpTitle)
		{
			// copy pointer to secondary title
			lpTitle=lpTitle2;
		}

		// load saver icon
		hIcon=ExtractIcon(AfxGetInstanceHandle(),
						  lpPath,
						  0);

		// check icon handle
		if(hIcon)
			AddWinResource
		else
		{
			// load default icon
			hIcon=LoadIcon(NULL,
						   IDI_WINLOGO);

			// check icon handle
			if(hIcon)
				AddWinResource
		}

		// check for windows xp saver
		if(strcmp(lpTitle,
				  " Windows XP ")==0)
		{
			// create bitmap (black bkg)
			lpIcon=CreateBitmapFromIcon(hIcon,
										RGB(0,0,0));
		}
		else
		{
			// create bitmap (window bkg)
			lpIcon=CreateBitmapFromIcon(hIcon,
										GetSysColor(COLOR_WINDOW));
		}

		// check new object
		if(!lpIcon)
			return(FALSE);

		// destroy icon handle
		if(DestroyIcon(hIcon))
			RemoveWinResource

		// resize to small-icon size
		if(!ResizeBitmap(&lpIconSm,
						 lpIcon,
						 16,16))
			return(FALSE);

		// make safe path
		if(!MakeSafeRegString(lpPath,
							  &lpRegPath))
			return(FALSE);

		// get remaining info
		if(!GetScreensaverData(lpRegPath,
							   &lpTheme,
							   &dwRating,
							   &lpDesc,
							   &lpMusic,
							   &bShuffle,
							   &bNoPreview,
							   &bNew,
							   &dwDupIdx,
							   &bIsDup))
			return(FALSE);

		// set load-ok flag
		bLoadOK=TRUE;
	}

	// ok
	return(TRUE);
}

// GetScreensaversFromFolder()

BOOL GetScreensaversFromFolder(LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetScreensaversFromFolder()",
							FALSE);
		return(FALSE);
	}
#endif

	// file search handle
	HANDLE hSearch=INVALID_HANDLE_VALUE;

	// find file data
	WIN32_FIND_DATA wfdFindData;

	// append search parameters
	strcat(lpPath,
		   (lpPath[strlen(lpPath)-1]=='\\' ? "*.scr" : "\\*.scr"));

	// find first saver
	hSearch=FindFirstFile(lpPath,
						  &wfdFindData);

	// check search handle
	if(hSearch!=INVALID_HANDLE_VALUE)
	{
		AddWinResource

		// add info to saver list
		g_lpSaverInfo->AddSaverInfo(lpPath,
									wfdFindData.cFileName);

		// repeat for all savers
		while(FindNextFile(hSearch,
						   &wfdFindData))
		{
			// add info to saver list
			g_lpSaverInfo->AddSaverInfo(lpPath,
										wfdFindData.cFileName);
		}

		// close search handle
		if(FindClose(hSearch))
			RemoveWinResource
	}

	// ok
	return(TRUE);
}

// GetScreensaverData()

BOOL GetScreensaverData(LPSTR lpRegPath,
						LPSTR* lplpTheme,
						LPDWORD lpdwRating,
						LPSTR* lplpDesc,
						LPSTR* lplpMusic,
						LPBOOL lpbShuffle,
						LPBOOL lpbNoPreview,
						LPBOOL lpbNew,
						LPDWORD lpdwDupIdx,
						LPBOOL lpbIsDup)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpRegPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetScreensaverData()",
							FALSE);
		return(FALSE);
	}

	// verify pointers
	if(!lplpTheme||
	   !lpdwRating||
	   !lplpDesc||
	   !lplpMusic||
	   !lpbShuffle||
	   !lpbNoPreview||
	   !lpbNew||
	   !lpdwDupIdx||
	   !lpbIsDup)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"GetScreensaverData()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// length of buffer
	DWORD dwLen;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	// create registry key
	strcpy(g_lpMsg,
		   ApplicationRegistryPath());
	strcat(g_lpMsg,
		   "SaverInfo\\");
	strcat(g_lpMsg,
		   lpRegPath);

	// open registry key
	if(lpRegKey->Open(HKEY_CURRENT_USER,
					  g_lpMsg)==ERROR_SUCCESS)
	{
		AddWinResource

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		LockGlobalLongMsg()

		// check for theme
		if(lpRegKey->QueryValue(g_lpLongMsg,
								"Theme",
								&dwLen)!=ERROR_SUCCESS)
		{
			// get default theme
			GetDefaultTheme(g_lpLongMsg,
							lpRegPath);
		}
		
		// clip theme
		g_lpLongMsg[MAX_THEME_LEN]=0;

		// allocate memory for theme
		if(!AllocMem((LPVOID*)lplpTheme,
					 strlen(g_lpLongMsg)+1))
		{
			UnlockGlobalLongMsg()
			return(FALSE);
		}

		// copy theme
		strcpy((*lplpTheme),
			   g_lpLongMsg);

		UnlockGlobalLongMsg()

		// validate theme
		if(!ValidateTheme(lplpTheme))
			return(FALSE);

		LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// check for rating
		if(lpRegKey->QueryValue(g_lpLongMsg,
								"Rating",
								&dwLen)==ERROR_SUCCESS)
		{
			// convert rating to value
			(*lpdwRating)=atoi(g_lpLongMsg);

			// validate rating
			if((*lpdwRating)>5)
				(*lpdwRating)=0;
		}
		else
		{
			// set default rating
			(*lpdwRating)=GetDefaultRating(lpRegPath);
		}

		UnlockGlobalLongMsg()
		LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// check for description
		if(lpRegKey->QueryValue(g_lpLongMsg,
								"Desc",
								&dwLen)!=ERROR_SUCCESS)
		{
			// get default description
			GetDefaultDesc(g_lpLongMsg,
						   lpRegPath);
		}
		else
		{
			// check string
			if(strlen(g_lpLongMsg)==0)
			{
				// get default description
				GetDefaultDesc(g_lpLongMsg,
							   lpRegPath);
			}
		}		

		// force end of string
		g_lpLongMsg[MAX_SAVER_DESC]=NULL;

		// allocate memory for description
		if(!AllocMem((LPVOID*)lplpDesc,
					 strlen(g_lpLongMsg)+1))
		{
			UnlockGlobalLongMsg()
			return(FALSE);
		}

		// copy description
		strcpy((*lplpDesc),
			   g_lpLongMsg);

		UnlockGlobalLongMsg()
		LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// get music file
		if(lpRegKey->QueryValue(g_lpLongMsg,
								"Music",
								&dwLen)==ERROR_SUCCESS)
		{
			// check string
			if(strlen(g_lpLongMsg)>0)
			{
				// allocate memory for music file
				if(!AllocMem((LPVOID*)lplpMusic,
							 strlen(g_lpLongMsg)+1))
				{
					UnlockGlobalLongMsg()
					return(FALSE);
				}

				// copy music file
				strcpy((*lplpMusic),
					   g_lpLongMsg);
			}
		}

		UnlockGlobalLongMsg()
		LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// check for shuffle flag
		if(lpRegKey->QueryValue(g_lpLongMsg,
								"Shuffle",
								&dwLen)==ERROR_SUCCESS)
		{
			// convert to flag value
			(*lpbShuffle)=atoi(g_lpLongMsg);

			// validate flag
			if((*lpbShuffle)>1)
				(*lpbShuffle)=0;
		}
		else
		{
			// set default flag
			(*lpbShuffle)=FALSE;
		}

		UnlockGlobalLongMsg()
		LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// check for no-preview flag
		if(lpRegKey->QueryValue(g_lpLongMsg,
								"NoPreview",
								&dwLen)==ERROR_SUCCESS)
		{
			// convert to flag value
			(*lpbNoPreview)=atoi(g_lpLongMsg);

			// validate flag
			if((*lpbNoPreview)>1)
				(*lpbNoPreview)=0;
		}
		else
		{
			// set default flag
			(*lpbNoPreview)=FALSE;
		}

		UnlockGlobalLongMsg()
		LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// check for duplication index
		if(lpRegKey->QueryValue(g_lpLongMsg,
								"DupIndex",
								&dwLen)==ERROR_SUCCESS)
		{
			// convert to numeric value
			(*lpdwDupIdx)=(DWORD)atoi(g_lpLongMsg);
		}
		else
		{
			// set default value
			(*lpdwDupIdx)=0;
		}

		UnlockGlobalLongMsg()

		// reset duplicate flag (always)
		(*lpbIsDup)=FALSE;

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}
	else
	{
		LockGlobalLongMsg()

		// check first-run flag
		if(!g_bFirstRun)
		{
			// set new flag
			(*lpbNew)=TRUE;

			// set theme to new
			strcpy(g_lpLongMsg,
				   "New!");
		}
		else
		{
			// get default theme
			GetDefaultTheme(g_lpLongMsg,
							lpRegPath);
		}

		// allocate memory for theme
		if(!AllocMem((LPVOID*)lplpTheme,
					 strlen(g_lpLongMsg)+1))
		{
			UnlockGlobalLongMsg()
			return(FALSE);
		}

		// copy theme
		strcpy((*lplpTheme),
			   g_lpLongMsg);

		UnlockGlobalLongMsg()

		// set default rating
		(*lpdwRating)=GetDefaultRating(lpRegPath);

		LockGlobalLongMsg()

		// get default description
		GetDefaultDesc(g_lpLongMsg,
					   lpRegPath);

		// allocate memory for description
		if(!AllocMem((LPVOID*)lplpDesc,
					 strlen(g_lpLongMsg)+1))
		{
			UnlockGlobalLongMsg()
			return(FALSE);
		}

		// copy description
		strcpy((*lplpDesc),
			   g_lpLongMsg);

		UnlockGlobalLongMsg()

		// set music to none
		(*lplpMusic)=NULL;

		// set default shuffle flag
		(*lpbShuffle)=FALSE;

		// set default no-preview flag
		(*lpbNoPreview)=FALSE;

		// set duplicate index
		(*lpdwDupIdx)=0;

		// reset duplicate flag (always)
		(*lpbIsDup)=FALSE;
	}

	// relese key interface
	FreeClassObject(lpRegKey);

	// ok
	return(TRUE);
}

// GetScreensaverName()

void GetScreensaverName(LPSTR lpName,
						LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpName||
	   !lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetScreensaverName()",
							FALSE);
		return;
	}
#endif

	// copy path to name
	strcpy(lpName,
		   lpPath);

	// remove "_scr"
	lpName[strlen(lpName)-4]=0;

	// clip to last "_"
	strcpy(lpName,
		   strrchr(lpName,
				   '_')+1);
}

// GetDefaultTheme()

void GetDefaultTheme(LPSTR lpTheme,
					 LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpTheme||
	   !lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetDefaultTheme()",
							FALSE);
		return;
	}
#endif

	LockGlobalMsg()
	
	// get saver name
	GetScreensaverName(g_lpMsg,
					   lpPath);

	// check for windows savers
	if(stricmp(g_lpMsg,"logon")==0||
	   stricmp(g_lpMsg,"scrnsave")==0||
	   stricmp(g_lpMsg,"ss3dfo")==0||
	   stricmp(g_lpMsg,"ssbezier")==0||
	   stricmp(g_lpMsg,"ssflwbox")==0||
	   stricmp(g_lpMsg,"ssmarque")==0||
	   stricmp(g_lpMsg,"ssmypics")==0||
	   stricmp(g_lpMsg,"ssmyst")==0||
	   stricmp(g_lpMsg,"sspipes")==0||
	   stricmp(g_lpMsg,"ssstars")==0||
	   stricmp(g_lpMsg,"sstext3d")==0)
	{
		// set windows theme
		strcpy(lpTheme,
			   "Windows");
	}
	else
	{
		// set default theme
		strcpy(lpTheme,
			   NO_SEL_TEXT);
	}

	UnlockGlobalMsg()
}

// GetDefaultRating()

DWORD GetDefaultRating(LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetDefaultRating()",
							FALSE);
		return(0);
	}
#endif

	// return value
	DWORD dwRet;
	
	LockGlobalMsg()

	// get saver name
	GetScreensaverName(g_lpMsg,
					   lpPath);

	// check for windows savers
	if(stricmp(g_lpMsg,"logon")==0||
	   stricmp(g_lpMsg,"scrnsave")==0||
	   stricmp(g_lpMsg,"ss3dfo")==0||
	   stricmp(g_lpMsg,"ssbezier")==0||
	   stricmp(g_lpMsg,"ssflwbox")==0||
	   stricmp(g_lpMsg,"ssmarque")==0||
	   stricmp(g_lpMsg,"ssmypics")==0||
	   stricmp(g_lpMsg,"ssmyst")==0||
	   stricmp(g_lpMsg,"sspipes")==0||
	   stricmp(g_lpMsg,"ssstars")==0||
	   stricmp(g_lpMsg,"sstext3d")==0)
	{
		// 3-star rating
		dwRet=3;
	}
	else
	{
		// no rating
		dwRet=0;
	}

	UnlockGlobalMsg()
	
	// return rating
	return(dwRet);
}

// GetDefaultDesc()

void GetDefaultDesc(LPSTR lpDesc,
					LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpDesc||
	   !lpPath)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetDefaultDesc()",
							FALSE);
		return;
	}
#endif

	LockGlobalMsg()

	// get saver name
	GetScreensaverName(g_lpMsg,
					   lpPath);

	// check for windows savers
	if(stricmp(g_lpMsg,"logon")==0)
		strcpy(lpDesc,
			   "Windows XP default screensaver.");
	else if(stricmp(g_lpMsg,"scrnsave")==0)
		strcpy(lpDesc,
			   "The original screensaver. The name says it all.");
	else if(stricmp(g_lpMsg,"ss3dfo")==0)
		strcpy(lpDesc,
			   "Assorted shapes float and flutter around your computer screen.");
	else if(stricmp(g_lpMsg,"ssbezier")==0)
		strcpy(lpDesc,
			   "Watch as an array of dancing curves soothes your troubles away.");
	else if(stricmp(g_lpMsg,"ssflwbox")==0)
		strcpy(lpDesc,
			   "Three-dimensional geometric shapes morph and float on your screen.");
	else if(stricmp(g_lpMsg,"ssmarque")==0)
		strcpy(lpDesc,
			   "Display your own personalized message for all to see.");
	else if(stricmp(g_lpMsg,"ssmypics")==0)
		strcpy(lpDesc,
			   "Put on a slideshow of your favorite pictures.");
	else if(stricmp(g_lpMsg,"ssmyst")==0)
		strcpy(lpDesc,
			   "\"Mystify your mind\" with a display of dancing, color-changing lines.");
	else if(stricmp(g_lpMsg,"sspipes")==0)
		strcpy(lpDesc,
			   "A three-dimensional system of pipes is constructed while you watch.");
	else if(stricmp(g_lpMsg,"ssstars")==0)
		strcpy(lpDesc,
			   "Blast through the outer reaches of space from the comfort of your desktop.");
	else if(stricmp(g_lpMsg,"sstext3d")==0)
		strcpy(lpDesc,
			   "Display a personal message floating in three dimensions.");
	else
		strcpy(lpDesc,
			   NO_DESC_TEXT);

	UnlockGlobalMsg()
}

// LoadScreensaverInfo()

BOOL LoadScreensaverInfo(BOOL bListOnly)
{
	// search path string
	LPSTR lpPath;

	// allocate search path string
	if(!AllocMem((LPVOID*)&lpPath,
				 _MAX_PATH))
		return(FALSE);

	// create saver list
	AllocClassObject(g_lpSaverInfo,
					 CSaverInfo);

	// check new object
	if(!g_lpSaverInfo)
	{
		FreeMem((LPVOID*)&lpPath);
		return(FALSE);
	}

	// get system folder
	if(!GetSystemDirectory(lpPath,
						   _MAX_PATH-1))
	{
		DisplayErrorMessage("Unable to read Windows system directory.");
		FreeMem((LPVOID*)&lpPath);
		return(FALSE);
	}

	// get screensavers
	if(!GetScreensaversFromFolder(lpPath))
	{
		FreeMem((LPVOID*)&lpPath);
		return(FALSE);
	}
	
	// get windows folder
	if(!GetWindowsDirectory(lpPath,
							_MAX_PATH-1))
	{
		DisplayErrorMessage("Unable to read Windows root directory.");
		FreeMem((LPVOID*)&lpPath);
		return(FALSE);
	}

	// get screensavers
	if(!GetScreensaversFromFolder(lpPath))
	{
		FreeMem((LPVOID*)&lpPath);
		return(FALSE);
	}

	// free search string
	FreeMem((LPVOID*)&lpPath);

	// search additional folders
	if(!GetScreensaversFromUserFolders())
		return(FALSE);

	// check list flag
	if(!bListOnly)
	{
		// assign duplicate ids
		if(!AssignDuplicateSaverIDs())
			return(FALSE);

		// assemble icon list
		if(!AssembleIconList())
			return(FALSE);

		// create saver list control
		AllocClassObject(g_lpSaverList,
						 CSaverList);

		// check new object
		if(!g_lpSaverList)
			return(FALSE);

		// create saver list header control
		AllocClassObject(g_lpSaverListHdr,
						 CExtHeaderCtrl);

		// check new object
		if(!g_lpSaverListHdr)
			return(FALSE);
	}

	// ok
	return(TRUE);
}

// ReleaseScreensaverInfo()

void ReleaseScreensaverInfo(void)
{
	// free saver list header
	FreeClassObject(g_lpSaverListHdr);

	// free saver list control
	FreeClassObject(g_lpSaverList);

	// release icon list
	ReleaseIconList();

	// delete saver info
	if(g_lpSaverInfo)
		g_lpSaverInfo->DeleteSaverNode();

	// free saver info
	FreeClassObject(g_lpSaverInfo);
}

// CSaverInfo::AddIconToGlobalList()

BOOL CSaverInfo::AddIconToGlobalList(void)
{
	// check load-ok flag
	if(bLoadOK)
	{
		// add icon to list
		if(g_lpSaverIcons->Add(lpIconSm,
							   (COLORREF)NULL)==-1)
		{
			DisplayNEErrorMessage("Cannot add icon to image list.");
			return(FALSE);
		}
	}

	// check next saver
	if(lpNextSaver)
	{
		// add next icon
		if(!lpNextSaver->AddIconToGlobalList())
			return(FALSE);
	}

	// ok
	return(TRUE);
}

// CSaverInfo::AddInfoToGlobalList()

BOOL CSaverInfo::AddInfoToGlobalList(int nIndex)
{
	// check load-ok flag
	if(bLoadOK)
	{
		// add title
		g_lpSaverList->InsertItem(nIndex,
								  lpTitle,
								  nIndex);

		// add theme
		g_lpSaverList->SetItem(nIndex,
							   1,
							   LVIF_TEXT,
							   lpTheme,
							   NULL,
							   NULL,
							   NULL,
							   NULL);

		// add rating
		g_lpSaverList->SetItem(nIndex,
							   2,
							   LVIF_TEXT,
							   GetRatingString(dwRating),
							   NULL,
							   NULL,
							   NULL,
							   NULL);

		// set pointer to data
		g_lpSaverList->SetItemData(nIndex,
								   (DWORD)this);

		// increment index
		nIndex++;
	}

	// check next saver
	if(lpNextSaver)
	{
		// add next icon
		if(!lpNextSaver->AddInfoToGlobalList(nIndex))
			return(FALSE);
	}

	// ok
	return(TRUE);
}

// AssembleIconList()

BOOL AssembleIconList(void)
{
	// allocate image list
	AllocClassObject(g_lpSaverIcons,
					 CImageList);

	// check new object
	if(!g_lpSaverIcons)
		return(FALSE);

	// create image list
	if(!g_lpSaverIcons->Create(16,16,
							   ILC_COLORDDB,
							   4,
							   4))
	{
		DisplayErrorMessage("Cannot create icon list.");
		return(FALSE);
	}

	// add icons
	if(!g_lpSaverInfo->AddIconToGlobalList())
		return(FALSE);

	// ok
	return(TRUE);
}

// ReleaseIconList()

void ReleaseIconList(void)
{
	// release image list
	FreeClassObject(g_lpSaverIcons);
}

// GetRatingString()

LPSTR GetRatingString(DWORD dwRating)
{
	// check rating
	switch(dwRating)
	{
	case(1): return("1 Star");
	case(2): return("2 Stars");
	case(3): return("3 Stars");
	case(4): return("4 Stars");
	case(5): return("5 Stars");
	default: return("Not rated");
	}
}

// SaverListSort()

int CALLBACK SaverListSort(LPARAM lParam1,
						   LPARAM lParam2,
						   LPARAM lParamSort)
{
	// cast parameters to data
	CSaverInfo* lpInfo1=(CSaverInfo*)lParam1;
	CSaverInfo* lpInfo2=(CSaverInfo*)lParam2;
	DWORD dwFlag=(DWORD)lParamSort;

	// comparison value
	int nVal;

	// negation value
	int nNeg;

	// check flag
	switch(dwFlag)
	{
	// title
	case(SLS_TITLEASC):
	case(SLS_TITLEDES):

		// set negation value
		nNeg=(dwFlag==SLS_TITLEASC ? 1 : -1);

		// compare titles
		nVal=stricmp(lpInfo1->lpTitle,
					 lpInfo2->lpTitle);

		// check result
		if(nVal==0)
		{
			// compare themes
			nVal=stricmp(lpInfo1->lpTheme,
						 lpInfo2->lpTheme);

			// check result
			if(nVal==0)
			{
				// compare ratings
				if(lpInfo1->dwRating<lpInfo2->dwRating)
					return(nNeg);
				else
					return(-nNeg);
			}
			else
				return(nVal*nNeg);
		}
		else
			return(nVal*nNeg);

	// theme
	case(SLS_THEMEASC):
	case(SLS_THEMEDES):

		// set negation value
		nNeg=(dwFlag==SLS_THEMEASC ? 1 : -1);

		// compare themes
		nVal=stricmp(lpInfo1->lpTheme,
					 lpInfo2->lpTheme);

		// check result
		if(nVal==0)
		{
			// compare titles
			nVal=stricmp(lpInfo1->lpTitle,
						 lpInfo2->lpTitle);

			// check result
			if(nVal==0)
			{
				// compare ratings
				if(lpInfo1->dwRating<lpInfo2->dwRating)
					return(nNeg);
				else
					return(-nNeg);
			}
			else
				return(nVal*nNeg);
		}
		else
			return(nVal*nNeg);

	// rating
	case(SLS_RATINGASC):
	case(SLS_RATINGDES):

		// set negation value
		nNeg=(dwFlag==SLS_RATINGASC ? 1 : -1);
		
		// compare ratings
		if(lpInfo1->dwRating<lpInfo2->dwRating)
			nVal=1;
		else if(lpInfo1->dwRating==lpInfo2->dwRating)
			nVal=0;
		else
			nVal=-1;

		// check result
		if(nVal==0)
		{
			// compare titles
			nVal=stricmp(lpInfo1->lpTitle,
						 lpInfo2->lpTitle);

			// check result
			if(nVal==0)
			{
				// compare themes
				return(stricmp(lpInfo1->lpTitle,
							   lpInfo2->lpTitle));
			}
			else
				return(nVal*nNeg);
		}
		else
			return(nVal*nNeg);

	// invalid flag
	default:

#ifdef DEBUG_MODE
		// alert user
		DisplayErrorMessage("Invalid saver list sort parameter.");
#endif

		// return default value
		return(0);
	}
}

// CSaverList::OnColumnClick()

void CSaverList::OnColumnClick(NMHDR* pNMHDR,
							   LRESULT* pResult)
{
	// get pointer to notification header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// sort column
	SortSaverListColumn(lpLV->iSubItem);
}

// CSaverList::QuerySelection()

BOOL CSaverList::QuerySelection(void)
{
	// check for selection
	return(GetFirstSelectedItemPosition() ? TRUE : FALSE);
}

// CSaverList::GetSelection()

int CSaverList::GetSelection(void)
{
	// position value
	POSITION pos;

	// get first position
	pos=GetFirstSelectedItemPosition();

	// check position
	return(pos ? GetNextSelectedItem(pos) : -1);
}

// SortSaverListColumn()

void SortSaverListColumn(int nCol)
{
	// check column
	switch(nCol)
	{
	// title column
	case(0):

		// set sort flag
		g_dwLastSlsFlag=(g_dwLastSlsFlag==SLS_TITLEASC ? SLS_TITLEDES : SLS_TITLEASC);

		// ok
		break;

	// theme column
	case(1):

		// set sort flag
		g_dwLastSlsFlag=(g_dwLastSlsFlag==SLS_THEMEASC ? SLS_THEMEDES : SLS_THEMEASC);

		// ok
		break;

	// rating column
	case(2):

		// set sort flag
		g_dwLastSlsFlag=(g_dwLastSlsFlag==SLS_RATINGASC ? SLS_RATINGDES : SLS_RATINGASC);

		// ok
		break;
	}

	// sort items
	g_lpSaverList->SortItems(SaverListSort,
							 g_dwLastSlsFlag);

	// update sort images
	UpdateSaverListSortImages();

	// check for selection
	if(g_lpSaverList->QuerySelection())
	{
		// make sure selection is visible
		g_lpSaverList->EnsureVisible(g_lpSaverList->GetSelection(),
									 FALSE);
	}

	// set modified state
	g_lpSaverPage->SetModified();
}

// CSaverList::OnRtClick()

void CSaverList::OnRtClick(NMHDR* pNMHDR,
						   LRESULT* pResult)
{
	// get pointer to notification header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// show popup menu
	ShowPopupMenu(IDC_SAVERLIST,
				  (DWORD)lpLV->iItem,
				  (DWORD)g_lpCurSaver);

	// check for selection
	g_bLastSLSelFlag=(QuerySelection() ? TRUE : FALSE);
}

// CSaverList::OnClick()

void CSaverList::OnClick(NMHDR* pNMHDR,
						 LRESULT* pResult)
{
	// get pointer to notification header
	LPNMLISTVIEW lpLV=(LPNMLISTVIEW)pNMHDR;

	// check for selection
	if(QuerySelection())
	{
		// set flag
		g_bLastSLSelFlag=TRUE;
	}
	else
	{
		// check last selection
		if(g_bLastSLSelFlag)
		{
			// play sound (annoying!)
			//PlaySound(IDR_CLEARSELSND);

			// reset flag
			g_bLastSLSelFlag=FALSE;
		}
	}
}

// CSaverList::OnNotify()

BOOL CSaverList::OnNotify(WPARAM wParam,
						  LPARAM lParam,
						  LRESULT* pResult)
{
	// cast pointer to notification header
	LPNMHDR lpNM=(LPNMHDR)lParam;

	// cast pointer to tooltip info header
	LPNMTTCUSTOMDRAW lpTTCD=(LPNMTTCUSTOMDRAW)lParam;

	// cast pointer to extended notification header
	LPNMHEADER lpNMHdr=(LPNMHEADER)lParam;

	// check notification code
	switch(lpNM->code)
	{
	// right click
	case(NM_RCLICK):

		// show popup menu
		ShowPopupMenu(IDC_SLISTHEAD);

		// check for selection
		g_bLastSLSelFlag=(QuerySelection() ? TRUE : FALSE);

		// ok
		return(TRUE);

	// header resized
	case(HDN_ENDTRACKA):
	case(HDN_ENDTRACKW):
		
		// check width
		if(lpNMHdr->pitem->cxy<MIN_LIST_WD)
		{
			// keep width in range
			lpNMHdr->pitem->cxy=MIN_LIST_WD;
		}

		// invalidate window
		Invalidate();

		// set modified state
		g_lpSaverPage->SetModified();

		// ok
		return(TRUE);

	// tooltip custom draw
	case(NM_CUSTOMDRAW):

		// assume default processing
		(*pResult)=CDRF_DODEFAULT;

		// check draw stage
		switch(lpTTCD->nmcd.dwDrawStage)
		{
		// general pre-paint stage
		case(CDDS_PREPAINT):

			// set new flags
			lpTTCD->uDrawFlags=DT_LEFT;

			LockGlobalErrorMsg()

			// get window text
			if(!::GetWindowText(lpTTCD->nmcd.hdr.hwndFrom,
								g_lpErrorMsg,
								_MAX_PATH-1))
			{
				UnlockGlobalErrorMsg()
				return(TRUE);
			}
			
			// compute new rect
			if(!DrawText(lpTTCD->nmcd.hdc,
						 g_lpErrorMsg,
						 -1,
						 &lpTTCD->nmcd.rc,
						 lpTTCD->uDrawFlags|DT_CALCRECT))
			{
				UnlockGlobalErrorMsg()
				return(TRUE);
			}

			UnlockGlobalErrorMsg()

			// ok
			break;
		}

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

// CSaverPage::OnAddSaverBtnClk()

void CSaverPage::OnAddSaverBtnClk(void)
{
	// add current saver
	AddCurSaverToPlaylist();
}

// CSaverPage::OnClearSelBtnClk()

void CSaverPage::OnClearSelBtnClk(void)
{
	// clear current selection
	ClearCurSaver();
}

// CSaverList::OnDblClick()

void CSaverList::OnDblClick(NMHDR* pNMHDR,
							LRESULT* pResult)
{
	// edit current saver
	EditCurSaverInfo();
}

// ClearCurSaver()

BOOL ClearCurSaver(void)
{
	// check selection
	if(g_lpSaverList->QuerySelection())
	{
		// clear selection
		if(!g_lpSaverList->SetItemState(g_lpSaverList->GetSelection(),
										NULL,
										LVIS_SELECTED))
		{
			DisplayErrorMessage("Unable to clear selection.");
			return(FALSE);
		}

		// reset flag
		g_bLastSLSelFlag=FALSE;

		// play sound
		PlaySound(IDR_CLEARSELSND);
	}

	// set focus back to saver list
	g_lpSaverList->SetFocus();

	// ok
	return(TRUE);
}

// CSaverPage::OnContextMenu()

void CSaverPage::OnContextMenu(CWnd* pWnd,
							   CPoint pos)
{
	// check for clear button
	if(IsPointInWindow(&pos,
					   g_lpClearSelBtn))
		g_lpClearSelBtn->OnContextMenu(pWnd,
									   pos);

	// check for add button
	if(IsPointInWindow(&pos,
					   g_lpAddSaverBtn))
		g_lpAddSaverBtn->OnContextMenu(pWnd,
									   pos);

	// check for saver info box
	if(IsPointInWindow(&pos,
					   g_lpSaverInfoBox))
		g_lpSaverInfoBox->OnContextMenu(pWnd,
										pos);

	// check for settings button
	if(IsPointInWindow(&pos,
					   g_lpSaverSettingsBtn))
		g_lpSaverSettingsBtn->OnContextMenu(pWnd,
											pos);

	// check for preview button
	if(IsPointInWindow(&pos,
					   g_lpPreviewSaverBtn))
		g_lpPreviewSaverBtn->OnContextMenu(pWnd,
										   pos);

	// check for edit info button
	if(IsPointInWindow(&pos,
					   g_lpEditSaverInfoBtn))
		g_lpEditSaverInfoBtn->OnContextMenu(pWnd,
										    pos);
	
	// check for preview box
	if(IsPointInWindow(&pos,
					   g_lpSaverPrevBox))
		g_lpSaverPrevBox->OnContextMenu(pWnd,
										pos);
	
	// check for up button
	if(IsPointInWindow(&pos,
					   g_lpPListUpBtn))
		g_lpPListUpBtn->OnContextMenu(pWnd,
									  pos);
	
	// check for down button
	if(IsPointInWindow(&pos,
					   g_lpPListDownBtn))
		g_lpPListDownBtn->OnContextMenu(pWnd,
										pos);
	
	// check for top button
	if(IsPointInWindow(&pos,
					   g_lpPListTopBtn))
		g_lpPListTopBtn->OnContextMenu(pWnd,
									   pos);
	
	// check for bottom button
	if(IsPointInWindow(&pos,
					   g_lpPListBottomBtn))
		g_lpPListBottomBtn->OnContextMenu(pWnd,
										  pos);
	
	// check for delete button
	if(IsPointInWindow(&pos,
					   g_lpPListDeleteBtn))
		g_lpPListDeleteBtn->OnContextMenu(pWnd,
						 				  pos);
	
	// check for clear button
	if(IsPointInWindow(&pos,
					   g_lpPListClearBtn))
		g_lpPListClearBtn->OnContextMenu(pWnd,
						 				 pos);
	
	// check for save button
	if(IsPointInWindow(&pos,
					   g_lpPListSaveBtn))
		g_lpPListSaveBtn->OnContextMenu(pWnd,
						 				pos);
	
	// check for saver sort box
	if(IsPointInWindow(&pos,
					   g_lpSaverSortBox))
		g_lpSaverSortBox->OnContextMenu(pWnd,
										pos);
}

// ToggleSaverListDetails()

void ToggleSaverListDetails(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// update flag
		g_bShowSaverInfo=(g_bShowSaverInfo ? FALSE : TRUE);
	
		// set modified state
		g_lpSaverPage->SetModified();
	}
		
	// check info flag
	if(g_bShowSaverInfo)
	{
		// switch to report view
		g_lpSaverList->ModifyStyle(LVS_LIST,
								   LVS_REPORT);

		// update sort images
		UpdateSaverListSortImages();
	}
	else
	{
		// switch to list view
		g_lpSaverList->ModifyStyle(LVS_REPORT,
								   LVS_LIST);

		// validate sort flag
		if(g_dwLastSlsFlag==SLS_THEMEASC||
		   g_dwLastSlsFlag==SLS_RATINGASC)
			g_dwLastSlsFlag=SLS_TITLEASC;
		else if(g_dwLastSlsFlag==SLS_THEMEDES||
			    g_dwLastSlsFlag==SLS_RATINGDES)
			g_dwLastSlsFlag=SLS_TITLEDES;

		// sort items
		g_lpSaverList->SortItems(SaverListSort,
								 g_dwLastSlsFlag);
	}
}

// ToggleSaverListPopupInfo()

void ToggleSaverListPopupInfo(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// update flag
		g_bShowPopupInfo=(g_bShowPopupInfo ? FALSE : TRUE);

		// set modified state
		g_lpSaverPage->SetModified();
	}
}

// BuildSaverList()

BOOL BuildSaverList(void)
{
	// list control width
	int nListWidth;

	// position rectangle
	RECT rPos;

	// header control
	CHeaderCtrl* lpHdr=NULL;

	// attach saver list (in report view)
	if(!CaptureDlgControl(g_lpSaverPage,
						  g_lpSaverList,
						  IDC_SAVERLIST))
		return(FALSE);

	// set extended style flags
	g_lpSaverList->SetExtendedStyle(LVS_EX_FULLROWSELECT);

	// set image list
	g_lpSaverList->SetImageList(g_lpSaverIcons,
								LVSIL_SMALL);

	// get saver list size
	g_lpSaverList->GetClientRect(&rPos);

	// set saver list width
	nListWidth=(rPos.right-rPos.left)-GetSystemMetrics(SM_CXVSCROLL);

	// add title column
	if(g_lpSaverList->InsertColumn(0,
								   "Name",
								   LVCFMT_LEFT,
								   LoadOptionInt("Savers_TitleListWd",
												 MIN_LIST_WD,
												 nListWidth,
												 nListWidth-(nListWidth>>1)),
								   0)==-1)
	{
		DisplayErrorMessage("Unable to add 'Title' column to screensaver list.");
		return(FALSE);
	}

	// add theme column
	if(g_lpSaverList->InsertColumn(1,
								   "Theme",
								   LVCFMT_LEFT,
								   LoadOptionInt("Savers_ThemeListWd",
												 MIN_LIST_WD,
												 nListWidth,
												 (nListWidth>>2)),
								   1)==-1)
	{
		DisplayErrorMessage("Unable to add 'Theme' column to screensaver list.");
		return(FALSE);
	}

	// add rating column
	if(g_lpSaverList->InsertColumn(2,
								   "Rating",
								   LVCFMT_LEFT,
								   LoadOptionInt("Savers_RatingListWd",
												 MIN_LIST_WD,
												 nListWidth,
												 (nListWidth>>2)),
								   2)==-1)
	{
		DisplayErrorMessage("Unable to add 'Rating' column to screensaver list.");
		return(FALSE);
	}

	// reset saver list width
	nListWidth=(rPos.right-rPos.left);

	// switch to list view
	g_lpSaverList->ModifyStyle(LVS_REPORT,
							   LVS_LIST);

	// set width of list view column
	g_lpSaverList->SetColumnWidth(0,
								  (nListWidth>>1));

	// switch back to report view
	g_lpSaverList->ModifyStyle(LVS_LIST,
							   LVS_REPORT);

	// add screensaver data
	if(!g_lpSaverInfo->AddInfoToGlobalList())
		return(FALSE);

	// set last sort flag
	g_dwLastSlsFlag=(DWORD)LoadOptionInt("Savers_SLSFlag",
										 SLS_TITLEASC,
										 SLS_RATINGDES,
										 SLS_TITLEASC);

	// check info flag
	if(!g_bShowSaverInfo)
	{
		// validate sort flag
		if(g_dwLastSlsFlag==SLS_THEMEASC||
		   g_dwLastSlsFlag==SLS_RATINGASC)
			g_dwLastSlsFlag=SLS_TITLEASC;
		else if(g_dwLastSlsFlag==SLS_THEMEDES||
			    g_dwLastSlsFlag==SLS_RATINGDES)
			g_dwLastSlsFlag=SLS_TITLEDES;
	}

	// sort items
	g_lpSaverList->SortItems(SaverListSort,
							 g_dwLastSlsFlag);

	// get header control
	lpHdr=g_lpSaverList->GetHeaderCtrl();

	// check header control
	if(!lpHdr)
	{
		DisplayErrorMessage("Unable to find list control header.");
		return(FALSE);
	}

	// subclass header control
	if(!g_lpSaverListHdr->SubclassWindow(lpHdr->m_hWnd))
	{
		DisplayErrorMessage("Unable to attach list control header.");
		return(FALSE);
	}
	
	// remove full-drag flag
	g_lpSaverListHdr->ModifyStyle(HDS_FULLDRAG,
								  NULL);

	// update sort images
	UpdateSaverListSortImages();

	// hide info if necessary
	if(!g_bShowSaverInfo)
		ToggleSaverListDetails(FALSE);

	// show rating images if necesary
	if(g_bShowRatingImgs)
		ToggleSaverListRatings(FALSE);

	// ok
	return(TRUE);
}

// ToggleSaverListRatings()

void ToggleSaverListRatings(BOOL bUpdate)
{
	// counter
	int nCount;

	// number of items
	int nNumItems;

	// item data
	LVITEM lvi;

	// saver info
	CSaverInfo* lpSaverInfo=NULL;
	
	// check update flag
	if(bUpdate)
	{
		// update flag
		g_bShowRatingImgs=(g_bShowRatingImgs ? FALSE : TRUE);

		// set modified state
		g_lpSaverPage->SetModified();
	}

	// get number of items
	nNumItems=g_lpSaverList->GetItemCount();

	// check number of items
	if(nNumItems)
	{
		// update each item
		for(nCount=0;nCount<nNumItems;nCount++)
		{
			// check flag
			if(!g_bShowRatingImgs)
			{
				// cast pointer to info
				lpSaverInfo=(CSaverInfo*)g_lpSaverList->GetItemData(nCount);

				// check pointer
				if(lpSaverInfo)
				{
					// prepare item info
					lvi.mask=LVIF_TEXT;
					lvi.iItem=nCount;
					lvi.iSubItem=2;
					lvi.pszText=GetRatingString(lpSaverInfo->dwRating);

					// set item info
					g_lpSaverList->SetItem(&lvi);
				}
			}
			else
			{
				// cast pointer to info
				lpSaverInfo=(CSaverInfo*)g_lpSaverList->GetItemData(nCount);

				// check pointer
				if(lpSaverInfo)
				{
					// check rating
					if(lpSaverInfo->dwRating)
					{
						// prepare item info
						lvi.mask=LVIF_TEXT;
						lvi.iItem=nCount;
						lvi.iSubItem=2;
						lvi.pszText=NULL_STRING;

						// set item info
						g_lpSaverList->SetItem(&lvi);
					}
					else
					{
						// prepare item info
						lvi.mask=LVIF_TEXT;
						lvi.iItem=nCount;
						lvi.iSubItem=2;
						lvi.pszText="Not rated";

						// set item info
						g_lpSaverList->SetItem(&lvi);
					}
				}
			}
		}
	}

	// force redraw
	g_lpSaverList->Invalidate();
}

// UpdateSaverListSortImages()

void UpdateSaverListSortImages(void)
{
	// check saver list
	if(!g_lpSaverList)
	{
#ifdef DEBUG_MODE
		DisplayErrorMessage("Invalid pointer value.",
							"UpdateSaverListSortImages()",
							FALSE);
#endif
		return;
	}
	
	// header item
	HDITEM hdi;

	// set header mask
	hdi.mask=HDI_BITMAP|
			 HDI_FORMAT;

	// set format for title column
	hdi.fmt=HDF_LEFT|
			HDF_BITMAP|
			HDF_BITMAP_ON_RIGHT|
			HDF_STRING;

	// set bitmap for title column
	if(g_dwLastSlsFlag==SLS_TITLEASC)
		hdi.hbm=(HBITMAP)g_lpSortUp->m_hObject;
	else if(g_dwLastSlsFlag==SLS_TITLEDES)
		hdi.hbm=(HBITMAP)g_lpSortDn->m_hObject;
	else
		hdi.hbm=(HBITMAP)g_lpSortNa->m_hObject;

	// update title column
	g_lpSaverListHdr->SetItem(0,
							  &hdi);

	// set header mask
	hdi.mask=HDI_BITMAP|
			 HDI_FORMAT;

	// set format for theme/rating columns
	hdi.fmt=HDF_CENTER|
			HDF_BITMAP|
			HDF_BITMAP_ON_RIGHT|
			HDF_STRING;

	// set bitmap for theme column
	if(g_dwLastSlsFlag==SLS_THEMEASC)
		hdi.hbm=(HBITMAP)g_lpSortUp->m_hObject;
	else if(g_dwLastSlsFlag==SLS_THEMEDES)
		hdi.hbm=(HBITMAP)g_lpSortDn->m_hObject;
	else
		hdi.hbm=(HBITMAP)g_lpSortNa->m_hObject;

	// update theme column
	g_lpSaverListHdr->SetItem(1,
							  &hdi);

	// set bitmap for rating column
	if(g_dwLastSlsFlag==SLS_RATINGASC)
		hdi.hbm=(HBITMAP)g_lpSortUp->m_hObject;
	else if(g_dwLastSlsFlag==SLS_RATINGDES)
		hdi.hbm=(HBITMAP)g_lpSortDn->m_hObject;
	else
		hdi.hbm=(HBITMAP)g_lpSortNa->m_hObject;

	// update rating column
	g_lpSaverListHdr->SetItem(2,
							  &hdi);
}

// CSaverList::OnCustomDraw()

void CSaverList::OnCustomDraw(NMHDR* pNMHDR,
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

	// pointer to item data
	CSaverInfo* lpSaverInfo=NULL;
	
	// selected item
	int nSelItem;

	// gdi objects
	CGdiObject* lpGdiObj=NULL;
	HGDIOBJ hGdiObj=(HGDIOBJ)INVALID_HANDLE_VALUE;

	// device context
	HDC hDC=(HDC)INVALID_HANDLE_VALUE;
	
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
			rcMain.top+=10;

			// set text parameters
			lpDC->SetTextColor(clrTxt);
			lpDC->SetBkColor(clrBkg);

			// clear rect
			lpDC->FillRect(rcMain,
						   &CBrush(clrBkg));

			// select saver list font
			lpGdiObj=lpDC->SelectObject(GetFont());

			// draw text
			lpDC->DrawText("No screensavers found! ",
						   -1,
						   rcMain,
						   DT_CENTER|
						   DT_WORDBREAK|
						   DT_NOPREFIX);

			// restore saver list object
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

		// check details flag
		if(g_bShowSaverInfo)
		{
			// get notification of subitem draw & post-paint
			(*pResult)=CDRF_NOTIFYSUBITEMDRAW|
					   CDRF_NOTIFYPOSTPAINT;
		}
		else
		{
			// set background color
			lpLVCD->clrTextBk=GetSysColor(COLOR_WINDOW);
		}

		// create fonts (just in case)
		if(CreateListControlFonts(lpLVCD->nmcd.hdc))
		{
			// get device context
			lpDC=CDC::FromHandle(lpLVCD->nmcd.hdc);

			// check device context
			if(lpDC)
			{
				// cast pointer to item data
				lpSaverInfo=(CSaverInfo*)lpLVCD->nmcd.lItemlParam;

				// select font as needed
				lpDC->SelectObject(lpSaverInfo->bNew ? g_lpLCFontBold : g_lpLCFont);

				// add new font flag
				(*pResult)|=CDRF_NEWFONT;
			}
		}

		// ok
		break;

	// subitem pre-paint stage
	case(CDDS_ITEMPREPAINT|CDDS_SUBITEM):

		// check details flag
		if(g_bShowSaverInfo)
		{
			// set background color
			if( ((g_dwLastSlsFlag==SLS_TITLEASC ||g_dwLastSlsFlag==SLS_TITLEDES) &&lpLVCD->iSubItem==0) ||
			    ((g_dwLastSlsFlag==SLS_THEMEASC ||g_dwLastSlsFlag==SLS_THEMEDES) &&lpLVCD->iSubItem==1) ||
			    ((g_dwLastSlsFlag==SLS_RATINGASC||g_dwLastSlsFlag==SLS_RATINGDES)&&lpLVCD->iSubItem==2) )
				lpLVCD->clrTextBk=DarkenColor(GetSysColor(COLOR_WINDOW),5);
			else
				lpLVCD->clrTextBk=GetSysColor(COLOR_WINDOW);
		}

		// ok
		break;

	// item post-paint stage
	case(CDDS_ITEMPOSTPAINT):

		// check rating images flag
		if(g_bShowRatingImgs)
		{
			// cast pointer to item data
			lpSaverInfo=(CSaverInfo*)lpLVCD->nmcd.lItemlParam;

			// check rating
			if(lpSaverInfo->dwRating>0)
			{
				// get rating rectangle
				if(!GetSubItemRect(lpLVCD->nmcd.dwItemSpec,
								   2,
								   LVIR_BOUNDS,
								   rcDest))
					return;

				// get selection
				nSelItem=(QuerySelection() ? GetSelection() : -1);

				// set source rectangle
				rcSrc.SetRect(0,0,
							  (lpSaverInfo->dwRating*12)-1,11);

				// adjust rectangle widths
				if(rcSrc.Width()>rcDest.Width())
				{
					// clip right side of source
					rcSrc.right=rcDest.Width()-1;
				}
				else
				{
					// center destination
					rcDest.left+=(rcDest.Width()-rcSrc.Width())/2;
				}

				// adjust rectangle heights
				if(rcSrc.Height()>rcDest.Height())
				{
					// clip right bottom of source
					rcSrc.bottom=rcDest.Height()-1;
				}
				else
				{
					// center destination
					rcDest.top+=(rcDest.Height()-rcSrc.Height())/2;
				}

				// create device context
				hDC=CreateCompatibleDC(lpLVCD->nmcd.hdc);

				// check device context
				if(hDC)
				{
					AddWinResource

					// select bitmap based on selection
					hGdiObj=SelectObject(hDC,
										 (nSelItem==(int)lpLVCD->nmcd.dwItemSpec ? g_lpDimRatingBmp->m_hObject : g_lpRatingBmp->m_hObject));

					// copy bitmap
					TransparentBlt(lpLVCD->nmcd.hdc,
								   rcDest.left,
								   rcDest.top,
								   rcSrc.Width(),
								   rcSrc.Height(),
								   hDC,
								   0,0,
								   rcSrc.Width(),
								   rcSrc.Height(),
								   RGB(255,0,255));

					// restore object
					SelectObject(hDC,
								 hGdiObj);

					// delete device context
					if(DeleteDC(hDC))
						RemoveWinResource
				}
				
				// skip default processing
				(*pResult)=CDRF_SKIPDEFAULT;
			}
		}
		
		// ok
		break;
	}
}

// ComputeColNum()

DWORD ComputeColNum(DWORD dwItemVal,
					DWORD dwItemsPerCol)
{
	// compute value
	return((dwItemVal-(dwItemVal%dwItemsPerCol))/dwItemsPerCol);
}

// CSaverInfo::QueryNewSavers()

DWORD CSaverInfo::QueryNewSavers(void)
{
	// init current count
	DWORD dwCount=0;
	
	// check for next saver
	if(lpNextSaver)
	{
		// get count of next saver
		dwCount=lpNextSaver->QueryNewSavers();
	}

	// check load-ok flag
	if(bLoadOK)
	{
		// check new flag
		if(bNew)
			dwCount++;
	}

	// return count
	return(dwCount);
}

// SetCurSaverRating()

void SetCurSaverRating(DWORD dwRating,
					   BOOL bUpdate)
{
	// current selection
	int nSelItem;

	// item data
	LVITEM lvi;
	
	// check for current saver
	if(!g_lpCurSaver)
		return;

	// set new rating
	g_lpCurSaver->dwRating=dwRating;

	// get selection index
	nSelItem=g_lpSaverList->GetSelection();	
	
	// prepare item info
	lvi.mask=LVIF_TEXT;
	lvi.iItem=nSelItem;
	lvi.iSubItem=2;

	// check rating images flag
	if(!g_bShowRatingImgs)
		lvi.pszText=GetRatingString(g_lpCurSaver->dwRating);
	else
		lvi.pszText=(g_lpCurSaver->dwRating ? NULL_STRING : "Not rated");

	// set item info
	g_lpSaverList->SetItem(&lvi);

	// check update flag
	if(bUpdate)
	{
		// update item
		g_lpSaverList->RedrawItems(nSelItem,
								   nSelItem);

		// update window
		g_lpSaverList->UpdateWindow();

		// update saver info
		UpdateSaverInfoBox(g_lpCurSaver);

		// set modified state
		g_lpSaverPage->SetModified();
	}
}

// CSaverInfo::SaveRatings()

void CSaverInfo::SaveRatings(void)
{
	// registry key interface
	CRegKey* lpRegKey;
	
	// check load-ok flag
	if(bLoadOK)
	{
		// get key interface
		AllocClassObject(lpRegKey,
						 CRegKey);

		// check new object
		if(!lpRegKey)
			return;

		LockGlobalMsg()

		// create registry key
		strcpy(g_lpMsg,
			   ApplicationRegistryPath());
		strcat(g_lpMsg,
			   "SaverInfo\\");
		strcat(g_lpMsg,
			   lpRegPath);

		// create registry key
		if(lpRegKey->Create(HKEY_CURRENT_USER,
							g_lpMsg,
							REG_NONE,
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS,
							NULL,
							NULL)==ERROR_SUCCESS)
		{
			AddWinResource

			// save value
			lpRegKey->SetValue(itoa(dwRating,
									g_lpMsg,
									10),
							   "Rating");

			// close registry key
			if(lpRegKey->Close()==ERROR_SUCCESS)
				RemoveWinResource
		}

		UnlockGlobalMsg()

		// relese key interface
		FreeClassObject(lpRegKey);
	}
	
	// check next saver
	if(lpNextSaver)
	{
		// save next saver
		lpNextSaver->SaveRatings();
	}
}

// SetRegularScrollBars()

void SetRegularScrollBars(CWnd* lpWnd)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"SetRegularScrollBars()",
							FALSE);
		return;
	}
#endif

	// initialize flat scroll bars
	if(!InitializeFlatSB(lpWnd->m_hWnd))
		return;

	// set scroll bar styles
	FlatSB_SetScrollProp(lpWnd->m_hWnd,
						 WSB_PROP_HSTYLE,
						 FSB_REGULAR_MODE,
						 TRUE);
	FlatSB_SetScrollProp(lpWnd->m_hWnd,
						 WSB_PROP_VSTYLE,
						 FSB_REGULAR_MODE,
						 TRUE);
}

// CSaverList::PreSubclassWindow()

void CSaverList::PreSubclassWindow(void)
{
	// call base function
	CListCtrl::PreSubclassWindow();

	// enable tooltips
	EnableToolTips(TRUE);
}

// CSaverList::CellRectFromPoint()

int CSaverList::CellRectFromPoint(CPoint point,
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
			nRectWidth=nStringWidth+20;

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

// CSaverList::OnToolHitTest()

int CSaverList::OnToolHitTest(CPoint point,
							  TOOLINFO *pTI) const
{
	// item number
	int nItem;

	// bounding rect
	CRect rRect;

	// check flags
	if(g_bShowSaverInfo||
	   !g_bShowPopupInfo)
		return(-1);

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
	pTI->hwnd    =m_hWnd;
	pTI->uId     =(UINT)(nItem+1);
	pTI->lpszText=LPSTR_TEXTCALLBACK;
	pTI->rect    =rRect;

	// return id
	return(pTI->uId);
}

// CSaverList::OnTTNeedText()

BOOL CSaverList::OnTTNeedText(UINT nID,
							  NMHDR* pNMHDR,
							  LRESULT* pResult)
{
	// cast pointers to tooltip info
	LPTOOLTIPTEXTA lpTTTa=(LPTOOLTIPTEXTA)pNMHDR;
	LPTOOLTIPTEXTW lpTTTw=(LPTOOLTIPTEXTW)pNMHDR;

	// saver info
	CSaverInfo* lpSaverInfo;

	// check flags
	if(g_bShowSaverInfo||
	   !g_bShowPopupInfo)
		return(FALSE);

	// get actual id
	nID=pNMHDR->idFrom;

	// check for winnt auto tooltip
	if(nID==0)
		return(FALSE);

	// get saver info
	lpSaverInfo=(CSaverInfo*)GetItemData(nID-1);

	// check saver info
	if(!lpSaverInfo)
		return(FALSE);

	// prepare text
	strcpy(g_lpTTMsg,"Name:");
	strcat(g_lpTTMsg,lpSaverInfo->lpTitle);
	strcat(g_lpTTMsg,"\nTheme: ");
	strcat(g_lpTTMsg,lpSaverInfo->lpTheme);
	strcat(g_lpTTMsg,"\nRating: ");
	strcat(g_lpTTMsg,GetRatingString(lpSaverInfo->dwRating));

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

// UpdateSaverInfoBox()

UpdateSaverInfoBox(CSaverInfo* lpSaverInfo)
{
	// edit stream info
	EDITSTREAM es;

	// check saver info box
	if(!IsWindow(g_lpSaverInfoBox->m_hWnd))
		return(TRUE);

	// scroll box to top
	g_lpSaverInfoBox->ScrollToTop();

	// remove saver icon
	g_lpSaverInfoBox->RemoveBitmaps();

	LockGlobalLongMsg()
	
	// output rtf header
	strcpy(g_lpLongMsg,"{\\rtf1\\ansi\\deff0"
					   "{\\fonttbl{\\f0\\fnil\\fcharset0 MS Shell Dlg;}}"
					   "\\viewkind4\\uc1\\pard\\lang1033\\f0\\fs17"
					   "\\tx956\\tx1688");

	// output white space
	strcat(g_lpLongMsg,"\\fs6\\par\\fs17");

	// output name
	strcat(g_lpLongMsg,"\\tab\\b Name:\\b0\\tab ");
	if(lpSaverInfo)
		strcat(g_lpLongMsg,&lpSaverInfo->lpTitle[1]);

	// output theme
	strcat(g_lpLongMsg,"\\par\\tab\\b Theme:\\b0\\tab ");
	if(lpSaverInfo)
		strcat(g_lpLongMsg,lpSaverInfo->lpTheme);

	// output rating
	strcat(g_lpLongMsg,"\\par\\tab\\b Rating:\\b0\\tab ");
	if(lpSaverInfo)
		strcat(g_lpLongMsg,GetRatingString(lpSaverInfo->dwRating));

	// output music
	strcat(g_lpLongMsg,"\\par\\tab\\b Music:\\b0\\tab ");
	if(lpSaverInfo)
	{
		// get music file
		if(GetFilenameFromPath(g_lpMsg,
							   _MAX_PATH-1,
							   lpSaverInfo->lpMusic))
			strcat(g_lpLongMsg,
				   g_lpMsg);
		else
			strcat(g_lpLongMsg,
				   NO_SEL_TEXT);
	}

	// output divider
	strcat(g_lpLongMsg,"\\fs6\\par\\fs17\\uld");
	AddCharsToString(g_lpLongMsg,'_',48);
	strcat(g_lpLongMsg,"\\ul0\\fs6\\par\\fs17");

	// output description
	strcat(g_lpLongMsg,"\\par\\b Description:\\b0\\par ");
	if(lpSaverInfo)
	{
		strcat(g_lpLongMsg,"\\'b7  ");
		strcat(g_lpLongMsg,lpSaverInfo->lpDesc);
	}
	
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

	// stream text to info box
	g_lpSaverInfoBox->StreamIn(SF_RTF,
							   es);

	UnlockGlobalLongMsg()

	// check info pointer
	if(lpSaverInfo)
	{		
		// add saver icon
		g_lpSaverInfoBox->AddBitmap(10,10,
									lpSaverInfo->lpIcon,
									6,
									GetSysColor(COLOR_GRAYTEXT),
									GetSysColor(COLOR_WINDOW),
									GetSysColor(COLOR_WINDOWTEXT));

		// enable info box
		g_lpSaverInfoBox->Enable();

		// enable buttons
		g_lpSaverSettingsBtn->Enable();
		g_lpPreviewSaverBtn->Enable();
		g_lpEditSaverInfoBtn->Enable();
	}
	else
	{
		// add null icon
		g_lpSaverInfoBox->AddBitmap(10,10,
									g_lpNullIcon,
									6,
									LightenColor(GetSysColor(COLOR_GRAYTEXT),2),
									GetSysColor(COLOR_BTNFACE),
									GetSysColor(COLOR_GRAYTEXT));
		
		// disable info box
		g_lpSaverInfoBox->Disable();

		// disable buttons
		g_lpSaverSettingsBtn->Disable();
		g_lpPreviewSaverBtn->Disable();
		g_lpEditSaverInfoBtn->Disable();
	}
	
	// ok
	return(TRUE);
}

// CSaverPage::OnSettingsBtnClk()

void CSaverPage::OnSettingsBtnClk(void)
{
	// run settings
	RunCurSaverSettings();
}

// CSaverPage::OnPreviewBtnClk()

void CSaverPage::OnPreviewBtnClk(void)
{
	// run preview
	RunCurSaverPreview();
}

// CSaverPage::OnEditInfoBtnClk()

void CSaverPage::OnEditInfoBtnClk(void)
{
	// edit current saver
	EditCurSaverInfo();
}

// StreamInCallback()

DWORD CALLBACK StreamInCallback(DWORD dwCookie,
								LPBYTE pbBuff,
								LONG cb,
								LONG* pcb)
{
	// cast pointer to input buffer
	LPSTR lpInBuf=(LPSTR)dwCookie;

	// set bytes read
	if(cb>(LONG)strlen(lpInBuf))
		cb=(LONG)strlen(lpInBuf);

	// copy bytes
	CopyMemory(pbBuff,
			   lpInBuf,
			   cb);

	// copy bytes read
	(*pcb)=cb;

	// shorten string
	strcpy(lpInBuf,
		   &lpInBuf[cb]);

	// ok
	return(NULL);
}

// CSaverInfoBox::OnLButtonDblClk()

void CSaverInfoBox::OnLButtonDblClk(UINT nFlags,
									CPoint point)
{
	// edit current saver
	EditCurSaverInfo();
}

// CSaverList::OnKeyDown()

void CSaverList::OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags)
{
	// check for esc key
	if(nChar==VK_ESCAPE)
		ClearCurSaver();

	// check for enter key
	if(nChar==VK_RETURN)
		EditCurSaverInfo();

	// check for right arrow
	if(nChar==VK_RIGHT)
	{
		// must be in detail mode
		if(g_bShowSaverInfo)
		{
			// add to playlist
			AddCurSaverToPlaylist();
		}
	}

	// call base method
	CListCtrl::OnKeyDown(nChar,
						 nRepCnt,
						 nFlags);
}

// CSaverInfoBox::OnKeyDown()

void CSaverInfoBox::OnKeyDown(UINT nChar,
							  UINT nRepCnt,
							  UINT nFlags)
{
	// check for esc key
	if(nChar==VK_ESCAPE)
		ClearCurSaver();

	// check for enter key
	if(nChar==VK_RETURN)
		EditCurSaverInfo();

	// call base method
	CExtRichEditCtrl::OnKeyDown(nChar,
								nRepCnt,
								nFlags);
}

// CSaverInfoBox::OnSetFocus()

void CSaverInfoBox::OnSetFocus(CWnd* pOldWnd)
{
	// give focus to saver list
	g_lpSaverList->SetFocus();
}

// CSaverInfoBox::OnSetCursor()

BOOL CSaverInfoBox::OnSetCursor(CWnd* pWnd,
								UINT nHitTest,
								UINT message)
{
	// refuse to change cursor
	return(FALSE);
}

// CSaverPreviewBox::OnPaint()

void CSaverPreviewBox::OnPaint(void)
{
	// paint struct
	PAINTSTRUCT ps;
	
	// begin paint
	BeginPaint(&ps);

	// draw bitmap
	DrawBitmap(&ps);

	// end paint
	EndPaint(&ps);

	// redraw saver window
	RedrawSaver();
}

// CSaverPreviewBox::RedrawSaver()

void CSaverPreviewBox::RedrawSaver(void)
{
	// saver window
	CWnd* lpSaverWnd=NULL;
	
	// check preview window
	if(g_lpSaverPrevWnd)
	{
		// check for saver
		if(g_lpSaverPrevWnd->bPIValid)
		{
			// get first child
			lpSaverWnd=g_lpSaverPrevWnd->GetTopWindow();

			// check window
			if(lpSaverWnd)
			{
				// force window to redraw
				lpSaverWnd->RedrawWindow();
			}
		}
		else
		{
			// redraw screen
			g_lpSaverPrevWnd->RedrawWindow();
		}
	}
}

// CSaverPage::OnShowWindow()

void CSaverPage::OnShowWindow(BOOL bShow,
							  UINT nStatus)
{
	// call base method
	CPropertyPage::OnShowWindow(bShow,
								nStatus);
}

// CSaverPage::OnActivate()

void CSaverPage::OnActivate(UINT nState,
							CWnd* pWndOther,
							BOOL bMinimized)
{
	// call base method
	CPropertyPage::OnActivate(nState,
							  pWndOther,
							  bMinimized);
}

// CSaverPage::OnShowPreviewChkClk()

void CSaverPage::OnShowPreviewChkClk(void)
{
	// toggle preview
	ToggleSaverPreview();
}

// ToggleSaverPreview()

void ToggleSaverPreview(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// update flag
		g_bShowSaverPreview=(g_bShowSaverPreview ? FALSE : TRUE);
	
		// check for current saver
		if(g_lpCurSaver)
		{
			// check no-preview flag
			if(g_lpCurSaver->bNoPreview)
			{
				// check new flag
				if(g_bShowSaverPreview)
				{
					// alert user
					DisplayInfoMessage("You have chosen to turn off the mini-preview for this screensaver.\n\nIf you would like to change this setting, click the 'Edit Info' button.");
				}
			}
		}

		// set modified state
		g_lpSaverPage->SetModified();
	}

	// set check state
	g_lpMiniPreviewChk->SetCheck(g_bShowSaverPreview ? 1 : 0);

	// check flag
	if(g_bShowSaverPreview)
	{
		// start preview
		g_lpSaverPrevWnd->StartPreview();
	}
	else
	{
		// end preview
		g_lpSaverPrevWnd->StopPreview();
	}
}

// CSaverPreviewBox::DrawBitmap()

void CSaverPreviewBox::DrawBitmap(LPPAINTSTRUCT lpPS)
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
	if(!lpCompBmp)
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
		goto CSaverPreviewBox_DrawBitmap1;

	// save state
	nDestState=lpDestDC->SaveDC();

	// create source dc
	AllocClassObject(lpSrcDC,
					 CDC);
	
	// check for error
	if(!lpSrcDC)
		goto CSaverPreviewBox_DrawBitmap1;

	// create compatible dc
	if(!lpSrcDC->CreateCompatibleDC(lpDestDC))
		goto CSaverPreviewBox_DrawBitmap1;
	else
		AddWinResource

	// select bitmap
	lpGdiObj=lpSrcDC->SelectObject(lpCompBmp);

	// copy bitmap
	TransparentBlt(lpDestDC->m_hDC,
				   rBmp.left,
				   rBmp.top,
				   rBmp.Width(),
				   rBmp.Height(),
				   lpSrcDC->m_hDC,
				   rBmp.left,
				   rBmp.top,
				   rBmp.Width(),
				   rBmp.Height(),
				   RGB(255,0,255));

	// restore object
	lpSrcDC->SelectObject(lpGdiObj);

// error exit point
CSaverPreviewBox_DrawBitmap1:;

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

// CSaverPreviewBox::CSaverPreviewBox()

CSaverPreviewBox::CSaverPreviewBox(UINT nID)
{
	// save id
	nCtrlId=nID;
	
	// init bitmap
	lpCompBmp=NULL;

	// call base method
	CExtStatic::CExtStatic();
}

// CSaverPreviewWnd::CSaverPreviewWnd()

CSaverPreviewWnd::CSaverPreviewWnd()
{
	// reset values
	InitStruct(pi);
	bPIValid=FALSE;
	lpScrnBmp=NULL;
	bScrnUp=FALSE;

	// call base constructor
	CWnd::CWnd();
}

// InitSaverPreviewWnd()

BOOL InitSaverPreviewWnd(void)
{
	// create preview box
	AllocClassObject(g_lpSaverPrevBox,
					 CSaverPreviewBox(IDC_PREVIEWWND));

	// check for error
	if(!g_lpSaverPrevBox)
		return(FALSE);

	// create preview window
	AllocClassObject(g_lpSaverPrevWnd,
					 CSaverPreviewWnd);

	// check for error
	if(!g_lpSaverPrevWnd)
		return(FALSE);

	// add computer bitmap
	if(!LoadBitmap(&g_lpSaverCompBmp,
				   IDB_COMPUTER))
		return(FALSE);

	// add screen bitmap
	if(!LoadBitmap(&g_lpSaverScrnBmp,
				   IDB_SCREEN))
		return(FALSE);

	// set screen-up flag
	g_lpSaverPrevWnd->bScrnUp=TRUE;

	// ok
	return(TRUE);
}

// ReleaseSaverPreviewWnd()

void ReleaseSaverPreviewWnd(void)
{
	// free bitmaps
	FreeClassObject(g_lpSaverCompBmp);
	FreeClassObject(g_lpSaverScrnBmp);

	// free objects
	FreeClassObject(g_lpSaverPrevWnd);
	FreeClassObject(g_lpSaverPrevBox);
	
	// un-register class
	if(UnregisterClass("SSDemoParent",
					   AfxGetInstanceHandle()))
		RemoveWinResource
}

// CreateSaverPreviewWnd()

BOOL CreateSaverPreviewWnd(void)
{
	// preview computer size
	#define CX_PREVCMP 180
	#define CY_PREVCMP 156

	// preview screen size
	#define CX_PREVSCR 152
	#define CY_PREVSCR 112

	// extended window class
	WNDCLASSEX wcx;

	// window rects
	CRect rWnd;
	CRect rParentWnd;

	// center point
	CPoint pCtr;

	// preview blank screen bitmap
	CBitmap* lpSaveBmp=NULL;

	// attach preview box
	if(!CaptureDlgControl(g_lpSaverPage,
						  g_lpSaverPrevBox,
						  IDC_PREVIEWWND))
		return(FALSE);

	// get window rects
	g_lpSaverPrevBox->GetWindowRect(&rWnd);
	g_lpSaverPage->GetWindowRect(&rParentWnd);

	// adjust window rect
	rWnd.left  -=rParentWnd.left;
	rWnd.right -=rParentWnd.left;
	rWnd.top   -=rParentWnd.top;
	rWnd.bottom-=rParentWnd.top;

	// get center point
	pCtr=rWnd.CenterPoint();

	// scale to proper size
	rWnd.left  =pCtr.x-(CX_PREVCMP/2);
	rWnd.right =rWnd.left+CX_PREVCMP;
	rWnd.top   =pCtr.y-(CY_PREVCMP/2);
	rWnd.bottom=rWnd.top+CY_PREVCMP;

	// set new size
	g_lpSaverPrevBox->SetWindowPos(NULL,
								   rWnd.left,
								   rWnd.top,
								   rWnd.Width(),
								   rWnd.Height(),
								   SWP_NOZORDER);

	// set for screen size
	rWnd.left  =(CX_PREVCMP/2)-(CX_PREVSCR/2);
	rWnd.right =rWnd.left+CX_PREVSCR;
	rWnd.top   =((CY_PREVCMP/2)-(CY_PREVSCR/2))-9;
	rWnd.bottom=rWnd.top+CY_PREVSCR;

	// prepare preview class
	wcx.cbSize       =sizeof(wcx);
	wcx.style        =NULL;
	wcx.lpfnWndProc  =DefWindowProc;
	wcx.cbClsExtra   =NULL;
	wcx.cbWndExtra   =0;
	wcx.hInstance    =AfxGetInstanceHandle();
	wcx.hIcon        =NULL;
	wcx.hIconSm      =NULL;
	wcx.hCursor      =NULL;
	wcx.hbrBackground=NULL;
	wcx.lpszMenuName =NULL;
	wcx.lpszClassName="SSDemoParent";

	// register preview class
	if(!RegisterClassEx(&wcx))
	{
		DisplayErrorMessage("Unable to register preview window class.");
		return(FALSE);
	}
	else
		AddWinResource

	// create window	
	if(!g_lpSaverPrevWnd->CreateEx(WS_EX_LEFT|
								   WS_EX_LTRREADING|
								   WS_EX_RIGHTSCROLLBAR,
								   "SSDemoParent",
								   NULL,
								   WS_CHILDWINDOW|
								   WS_VISIBLE|
								   WS_CLIPCHILDREN|
								   WS_OVERLAPPED,
								   rWnd.left,
								   rWnd.top,
								   rWnd.Width(),
								   rWnd.Height(),
								   g_lpSaverPrevBox->m_hWnd,
								   NULL,
								   NULL))
	{
		DisplayErrorMessage("Unable to create preview window.");
		return(FALSE);
	}

	// set bitmaps
	g_lpSaverPrevBox->SetComputerBitmap(g_lpSaverCompBmp);
	g_lpSaverPrevWnd->SetScreenBitmap(g_lpSaverScrnBmp);

	// ok
	return(TRUE);
}

// CSaverPreviewBox::SetComputerBitmap()

void CSaverPreviewBox::SetComputerBitmap(CBitmap* lpBmp)
{
#ifdef DEBUG_MODE
	// verify bitmap
	if(!lpBmp)
	{
		DisplayErrorMessage("Invalid bitmap pointer.",
							"CSaverPreviewBox::SetComputerBitmap()",
							FALSE);
		return;
	}
#endif

	// copy pointer
	lpCompBmp=lpBmp;
}

// SetCurrentSaver()

BOOL SetCurrentSaver(CSaverInfo* lpSaverInfo)
{
	// check for null
	if(lpSaverInfo==NULL)
	{
		// check swap timer
		if(g_nFSwapId)
		{
			// no change
			return(FALSE);
		}
	}

	// check for match
	if(g_lpCurSaver!=lpSaverInfo)
	{
		// save value
		g_lpCurSaver=lpSaverInfo;

		// start preview
		g_lpSaverPrevWnd->StartPreviewOnDelay(PREVIEW_QUICKDELAY);

		// updated
		return(TRUE);
	}

	// not updated
	return(FALSE);
}

// CSaverPreviewWnd::StartPreviewOnDelay()

void CSaverPreviewWnd::StartPreviewOnDelay(UINT nDelay)
{
	// stop any running preview
	StopPreview();

	// check timer
	if(g_nPrevTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nPrevTimerId);

		// reset id
		g_nPrevTimerId=NULL;
	}

	// set timer
	g_nPrevTimerId=::SetTimer(NULL,
							  DUMMY_TIMER_ID,
							  nDelay,
							  OnPrevDelayTimerProc);
}

// OnPrevDelayTimerProc()

void CALLBACK OnPrevDelayTimerProc(HWND hWnd,
								   UINT uMsg,
								   UINT idEvent,
								   DWORD dwTime)
{
	// kill timer
	::KillTimer(NULL,
				g_nPrevTimerId);

	// reset id
	g_nPrevTimerId=NULL;

	// start preview
	g_lpSaverPrevWnd->StartPreview();
}

// CSaverPreviewWnd::StartPreviewOnClose()

void CSaverPreviewWnd::StartPreviewOnClose(UINT nDelay,
										   LPPROCESS_INFORMATION lpPI)
{
	// check timer
	if(g_nPrevTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nPrevTimerId);

		// reset id
		g_nPrevTimerId=NULL;
	}

	// set process info
	g_lpPrevPI=lpPI;

	// set close timer
	g_nPrevTimerId=::SetTimer(NULL,
							  DUMMY_TIMER_ID,
							  nDelay,
							  OnPrevCloseTimerProc);
}

// OnPrevCloseTimerProc()

void CALLBACK OnPrevCloseTimerProc(HWND hWnd,
								   UINT uMsg,
								   UINT idEvent,
								   DWORD dwTime)
{
	// check for process
	if(!GetWndFromProcess(g_lpPrevPI))
	{
		// kill timer
		::KillTimer(NULL,
					g_nPrevTimerId);

		// reset id
		g_nPrevTimerId=NULL;

		// restart preview
		RestartSaverPreview(NULL);
	}
}

// RestartSaverPreview()

void RestartSaverPreview(DWORD dwData)
{
	// restore master volume
	MasterVolume(MV_RESTORE);

	// release dx audio
	DXAudioRelease();
	
	// set simple timer
	g_nPrevTimerId=::SetTimer(NULL,
							  DUMMY_TIMER_ID,
							  PREVIEW_QUICKDELAY,
							  OnPrevDelayTimerProc);
}

// CSaverPreviewWnd::StartPreview()

void CSaverPreviewWnd::StartPreview(void)
{
	// set saver info
	CSaverInfo* lpSaverInfo=g_lpCurSaver;

	// running preview object
	CWnd* lpPrevWnd=NULL;
	
	// last bad saver
	static CSaverInfo* lpLastBadSaver=NULL;

	// stop running preview
	StopPreview();

	// check timer
	if(g_nPrevTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nPrevTimerId);

		// reset id
		g_nPrevTimerId=NULL;
	}

	// check preview flag
	if(!g_bShowSaverPreview)
	{
		// clear info
		lpSaverInfo=NULL;
	}

	// check saver info
	if(!lpSaverInfo)
		return;

	// check for no-preview flag
	if(lpSaverInfo->bNoPreview)
		return;

	// check for preview window
	if(IsWindow(m_hWnd))
	{
		// check for bad saver
		if(lpLastBadSaver!=lpSaverInfo)
		{
			LockGlobalMsg()
			
			// begin command line
			strcpy(g_lpMsg,
				   "\"");
			
			// copy saver path
			strcat(g_lpMsg,
				   lpSaverInfo->lpPath);

			// add preview command
			strcat(g_lpMsg,
				   "\" /p ");

			// add window handle
			strcat(g_lpMsg,
				   ultoa((unsigned long)m_hWnd,
						 g_lpLongMsg,
						 10));

			// execute saver
			if(ExecuteExternalApp(g_lpMsg,
								  &pi))
			{
				// wait for process to start
				WaitForInputIdle(pi.hProcess,
								 INFINITE);

				// get window handle
				lpPrevWnd=GetTopWindow();

				// check handle
				if(lpPrevWnd)
				{
					// disable window
					lpPrevWnd->EnableWindow(FALSE);

					// set valid flag
					bPIValid=TRUE;

					// reset bad saver flag
					lpLastBadSaver=NULL;

					// check screen-up timer
					if(g_nScrnUpTimerId)
					{
						// kill timer
						::KillTimer(NULL,
									g_nScrnUpTimerId);

						// reset id
						g_nScrnUpTimerId=NULL;
					}

					// clear screen-up flag
					bScrnUp=FALSE;

					// add resource
					AddWinResource
				}
				else
				{
					// save as bad saver
					lpLastBadSaver=lpSaverInfo;
				}
			}

			UnlockGlobalMsg()
		}
	}
}

// CSaverPreviewWnd::StopPreview()

void CSaverPreviewWnd::StopPreview(void)
{
	// running preview object
	CWnd* lpPrevWnd=NULL;

	// check timer
	if(g_nPrevTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nPrevTimerId);

		// reset id
		g_nPrevTimerId=NULL;
	}

	// check for preview window
	if(IsWindow(m_hWnd))
	{
		// check for running saver
		if(bPIValid)
		{
			// get preview window
			lpPrevWnd=GetTopWindow();

			// check pointer
			if(lpPrevWnd)
			{
				// close preview
				lpPrevWnd->SendMessage(WM_CLOSE);
				
				// wait for idle
				WaitForInputIdle(pi.hProcess,
								 INFINITE);

				// check for window
				if(GetTopWindow())
				{
					// quit preview
					lpPrevWnd->SendMessage(WM_QUIT,
										   NULL);
					
					// wait for idle
					WaitForInputIdle(pi.hProcess,
									 INFINITE);

					// check for window
					if(GetTopWindow())
					{
#ifdef DEBUG_MODE
						// alert to abnormality
						DisplayInfoMessage("Process terminated!");
#endif

						// terminate process
						TerminateProcess(pi.hProcess,
										 NULL);
					}
				}
			}

			// reset valid flag
			bPIValid=FALSE;

			// check screen-up timer
			if(g_nScrnUpTimerId)
			{
				// kill timer
				::KillTimer(NULL,
							g_nScrnUpTimerId);

				// reset id
				g_nScrnUpTimerId=NULL;
			}

			// set timer
			g_nScrnUpTimerId=::SetTimer(NULL,
										DUMMY_TIMER_ID,
										PREVIEW_SCRNUPDELAY,
										OnScrnUpTimerProc);

			// remove resource
			RemoveWinResource
		}

		// update computer
		g_lpSaverPrevBox->RedrawWindow();
	}
}

// CSaverPreviewWnd::OnPaint()

void CSaverPreviewWnd::OnPaint(void)
{
	// paint struct
	PAINTSTRUCT ps;

	// begin paint
	BeginPaint(&ps);

	// check for no-saver
	if(!bPIValid)
	{
		// draw screen
		DrawBitmap(&ps);
	}

	// end paint
	EndPaint(&ps);
}

// RunCurSaverSettings()

BOOL RunCurSaverSettings(void)
{
	// process info
	static PROCESS_INFORMATION pi;

	// new window
	HWND hWnd=(HWND)INVALID_HANDLE_VALUE;

	// stop any running preview
	g_lpSaverPrevWnd->StopPreview();

	// check current saver
	if(g_lpCurSaver==NULL)
		return(FALSE);

	LockGlobalMsg()

	// begin command line
	strcpy(g_lpMsg,
		   "\"");
	
	// copy saver path
	strcat(g_lpMsg,
		   g_lpCurSaver->lpPath);

	// add configure command
	strcat(g_lpMsg,
		   "\" /c:");

	// add window handle
	strcat(g_lpMsg,
		   ultoa((unsigned long)g_lpMainSheet->m_hWnd,
				 g_lpLongMsg,
				 10));

	// execute saver
	if(ExecuteExternalApp(g_lpMsg,
						  &pi))
	{
		// wait for init
		WaitForInputIdle(pi.hProcess,
						 INFINITE);

		// get window handle
		hWnd=GetWndFromProcess(&pi);

		// check window handle
		if(hWnd)
		{
			// restart after close
			g_lpSaverPrevWnd->StartPreviewOnClose(PREVIEW_CLOSEDELAY,
												  &pi);
		}
		else
		{
			// restart now
			g_lpSaverPrevWnd->StartPreviewOnDelay(PREVIEW_QUICKDELAY);
		}
	}
	else
	{
		// restart preview
		g_lpSaverPrevWnd->StartPreviewOnDelay(PREVIEW_QUICKDELAY);
	}

	UnlockGlobalMsg()

	// ok
	return(TRUE);
}

// RunCurSaverPreview()

BOOL RunCurSaverPreview(void)
{
	// saver playback info
	static SVRPLAYINFO spi;

	// stop any running preview
	g_lpSaverPrevWnd->StopPreview();

	// check current saver
	if(g_lpCurSaver==NULL)
		return(FALSE);

	// prepare playback info
	spi.lpSaverInfo          =g_lpCurSaver;
	spi.dwMinToPlay          =0;
	spi.lpfnTimeoutCallback  =NULL;
	spi.dwTimeoutData        =NULL;
	spi.lpfnUserCloseCallback=RestartSaverPreview;
	spi.dwUserCloseData      =NULL;

	// save & half master volume
	MasterVolume(MV_SAVE);
	MasterVolume(MV_HALF);

	// init dx audio
	if(g_bUseDXSynth)
		DXAudioInit(TRUE);

	// begin playback
	if(!PlaybackSaver(&spi))
		return(FALSE);

	// ok
	return(TRUE);
}

// CSaverPreviewWnd::OnDestroy()

void CSaverPreviewWnd::OnDestroy(void)
{
	// stop preview
	StopPreview();

	// call base method
	CWnd::OnDestroy();
}

// EditCurSaverInfo()

BOOL EditCurSaverInfo(void)
{
	// check current saver
	if(g_lpCurSaver==NULL)
		return(FALSE);

	// run dialog box
	g_lpSaverInfoDlg->DoModal();

	// ok
	return(TRUE);
}

// LoadThemes()

BOOL LoadThemes(void)
{
	// reset counter
	DWORD dwCount=0;

	// get themes
	while(AddTheme(dwCount))
	{
		// increment counter
		dwCount++;
	}

	// check count
	if(!dwCount)
	{
		// load default themes
		if(!SetDefaultThemes())
			return(FALSE);
	}

	// ok
	return(TRUE);
}

// ReleaseThemes()

void ReleaseThemes(void)
{
	// counter
	DWORD dwCount;
	
	// check themes
	if(g_dwNumThemes)
	{
		// release themes
		for(dwCount=0;dwCount<g_dwNumThemes;dwCount++)
			FreeMem((LPVOID*)&g_lplpThemes[dwCount]);

		// release themes list
		FreeMem((LPVOID*)&g_lplpThemes);

		// reset counters
		g_dwNumThemes=0;
		g_dwMaxThemes=0;
	}
}

// SetDefaultThemes()

BOOL SetDefaultThemes(void)
{
	// release themes
	ReleaseThemes();

	// add default list
	if(!(AddTheme("Windows")&&
		 AddTheme("Art")&&
		 AddTheme("Cartoons")&&
		 AddTheme("Nature")&&
		 AddTheme("Miscellaneous")&&
		 AddTheme("People")&&
		 AddTheme("Science")&&
		 AddTheme("Vehicles")&&
		 AddTheme("3-D")&&
		 AddTheme("Movies")&&
		 AddTheme("Kids")&&
		 AddTheme("Music")&&
		 AddTheme("Celebrities")&&
		 AddTheme("Sports")&&
		 AddTheme("TV")&&
		 AddTheme("Games")&&
		 AddTheme("Holidays")&&
		 AddTheme("Humorous")&&
		 AddTheme("Animals")&&
		 AddTheme(NO_SEL_TEXT)))
		return(FALSE);

	// ok
	return(TRUE);
}

// SaveThemes()

BOOL SaveThemes(void)
{
	// counter
	DWORD dwCount;
	
	// check themes
	if(g_dwNumThemes)
	{
		// save each theme
		for(dwCount=0;dwCount<g_dwNumThemes;dwCount++)
		{
			// save theme
			if(!SaveTheme(dwCount,
						  g_lplpThemes[dwCount]))
				return(FALSE);
		}

		// output terminator
		if(!SaveTheme(dwCount,
					  NULL_STRING))
			return(FALSE);
	}	
	
	// ok
	return(TRUE);
}

// ValidateTheme()

BOOL ValidateTheme(LPSTR* lplpTheme)
{
	// counter
	DWORD dwCount;
	
	// compare theme with defaults
	if(!strcmp((*lplpTheme),"Windows")||
	   !strcmp((*lplpTheme),NO_SEL_TEXT))
	{
		// ok
		return(TRUE);
	}

	// compare with list
	for(dwCount=0;dwCount<g_dwNumThemes;dwCount++)
	{
		// check theme
		if(!strcmp((*lplpTheme),
				   g_lplpThemes[dwCount]))
		{
			// ok
			return(TRUE);
		}
	}

	// not found, so free theme
	FreeMem((LPVOID*)lplpTheme);

	// allocate new theme
	if(!AllocMem((LPVOID*)lplpTheme,
				 strlen(NO_SEL_TEXT)+1))
		return(FALSE);

	// set theme to none
	strcpy((*lplpTheme),
		   NO_SEL_TEXT);

	// ok
	return(TRUE);
}

// AddTheme()

BOOL AddTheme(LPSTR lpTheme)
{
	// check theme counter
	if(g_dwNumThemes==0)
	{
		// allocate list
		if(!AllocMem((LPVOID*)&g_lplpThemes,
					 sizeof(LPSTR)*THEME_ALLOC_INC))
			return(FALSE);

		// set max themes
		g_dwMaxThemes=THEME_ALLOC_INC;
	}
	else if(g_dwNumThemes==g_dwMaxThemes)
	{
		// expand list
		if(!ExpandMem((LPVOID*)&g_lplpThemes,
					  sizeof(LPSTR)*g_dwMaxThemes,
					  sizeof(LPSTR)*THEME_ALLOC_INC))
			return(FALSE);

		// increment max themes
		g_dwMaxThemes+=THEME_ALLOC_INC;
	}

	// allocate memory for theme
	if(!AllocMem((LPVOID*)&g_lplpThemes[g_dwNumThemes],
				 strlen(lpTheme)+1))
		return(FALSE);

	// copy theme
	strcpy(g_lplpThemes[g_dwNumThemes],
		   lpTheme);

	// increment counter
	g_dwNumThemes++;

	// ok
	return(TRUE);
}

// AddTheme()

BOOL AddTheme(DWORD dwNum)
{
	// registry key interface
	CRegKey* lpRegKey=NULL;

	// length of buffer
	DWORD dwLen;

	// return value
	BOOL bRet=FALSE;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	LockGlobalMsg()

	// create registry key
	strcpy(g_lpMsg,
		   ApplicationRegistryPath());
	strcat(g_lpMsg,
		   "Themes\\");

	// open registry key
	if(lpRegKey->Open(HKEY_CURRENT_USER,
					  g_lpMsg)==ERROR_SUCCESS)
	{
		AddWinResource

		// create key name
		sprintf(g_lpMsg,
				"Theme%u",
				dwNum);

		LockGlobalLongMsg()

		// set length of buffer
		dwLen=LONG_MSG_SIZE-1;

		// check for theme
		if(lpRegKey->QueryValue(g_lpLongMsg,
								g_lpMsg,
								&dwLen)==ERROR_SUCCESS)
		{
			// check length
			if(strlen(g_lpLongMsg))
			{
				// clip theme
				g_lpLongMsg[MAX_THEME_LEN]=0;
				
				// add theme
				bRet=AddTheme(g_lpLongMsg);
			}
			else
				bRet=FALSE;
		}

		UnlockGlobalLongMsg()

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}
	
	UnlockGlobalMsg()

	// relese key interface
	FreeClassObject(lpRegKey);

	// return result
	return(bRet);
}

// SaveTheme()

BOOL SaveTheme(DWORD dwNum,
			   LPSTR lpTheme)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpTheme)
	{
		DisplayErrorMessage("Invalid string value.",
							"SaveTheme()",
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
	strcat(g_lpLongMsg,
		   "Themes\\");

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

		LockGlobalMsg()

		// create key name
		sprintf(g_lpMsg,
				"Theme%u",
				dwNum);

		// set value
		if(lpRegKey->SetValue(lpTheme,
							  g_lpMsg)==ERROR_SUCCESS)
		{
			// set return value
			bRet=TRUE;
		}

		UnlockGlobalMsg()

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

// CSaverInfoDlg::ReleaseDialog()

void CSaverInfoDlg::ReleaseDialog(void)
{
	// free apply button
	FreeClassObject(g_lpApplyBtn);

	// free music path
	FreeMem((LPVOID*)&lpMusicPath);

	// free dialog boxes
	FreeClassObject(g_lpEditThemesDlgA);
	FreeClassObject(g_lpChangeMusicDlg);
	FreeClassObject(g_lpMusicManagerDlgB);
}

// SaveCurrentSaverInfo()

BOOL SaveCurSaverInfo(void)
{
	// registry key interface
	CRegKey* lpRegKey=NULL;

	// set return value
	BOOL bRet=TRUE;

	// check current saver
	if(g_lpCurSaver==NULL)
		return(FALSE);

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	LockGlobalMsg()

	// create registry key
	strcpy(g_lpMsg,
		   ApplicationRegistryPath());
	strcat(g_lpMsg,
		   "SaverInfo\\");
	strcat(g_lpMsg,
		   g_lpCurSaver->lpRegPath);

	// create registry key
	if(lpRegKey->Create(HKEY_CURRENT_USER,
					    g_lpMsg,
						REG_NONE,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS,
						NULL,
						NULL)==ERROR_SUCCESS)
	{
		AddWinResource

		// save theme
		if(lpRegKey->SetValue(g_lpCurSaver->lpTheme,
							  "Theme")!=ERROR_SUCCESS)
			bRet=FALSE;

		// save rating
		if(lpRegKey->SetValue(itoa(g_lpCurSaver->dwRating,
								   g_lpMsg,
								   10),
							  "Rating")!=ERROR_SUCCESS)
			bRet=FALSE;

		// save description
		if(lpRegKey->SetValue(g_lpCurSaver->lpDesc,
							  "Desc")!=ERROR_SUCCESS)
			bRet=FALSE;

		// check music file
		if(g_lpCurSaver->lpMusic)
		{
			// save music file
			if(lpRegKey->SetValue(g_lpCurSaver->lpMusic,
								  "Music")!=ERROR_SUCCESS)
				bRet=FALSE;
		}
		else
		{
			// save description
			if(lpRegKey->SetValue(NULL_STRING,
								  "Music")!=ERROR_SUCCESS)
				bRet=FALSE;
		}

		// save shuffle flag
		if(lpRegKey->SetValue(itoa(g_lpCurSaver->bShuffle,
								   g_lpMsg,
								   10),
							  "Shuffle")!=ERROR_SUCCESS)
			bRet=FALSE;

		// save no-mini-preview flag
		if(lpRegKey->SetValue(itoa(g_lpCurSaver->bNoPreview,
								   g_lpMsg,
								   10),
							  "NoPreview")!=ERROR_SUCCESS)
			bRet=FALSE;

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}

	UnlockGlobalMsg()

	// relese key interface
	FreeClassObject(lpRegKey);

	// ok
	return(bRet);
}

// CSaverInfoDlg::OnEditThemesBtnClk()

void CSaverInfoDlg::OnEditThemesBtnClk(void)
{
	// window rects
	CRect rWnd;
	CRect rInv;

	// get window rect
	GetWindowRect(rWnd);

	// set rect to make window invisible
	rInv.left  =(rWnd.left+rWnd.right)/2;
	rInv.top   =(rWnd.top+rWnd.bottom)/2;
	rInv.right =rInv.left;
	rInv.bottom=rInv.top;

	// move window
	MoveWindow(rInv);

	// edit themes
	EditThemes(g_lpEditThemesDlgA);

	// restore window
	MoveWindow(rWnd);
}

// CSaverInfoDlg::OnHelpBtnClk()

void CSaverInfoDlg::OnHelpBtnClk(void)
{
	// show help file
	ShowHelp(IDC_EDITSAVERDLG,
			 NULL);
}

// CSaverInfoDlg::OnCommand()

BOOL CSaverInfoDlg::OnCommand(WPARAM wParam,
							  LPARAM lParam)
{
	// check message
	switch(HIWORD(wParam))
	{
	// combo box selection change
	case(CBN_SELCHANGE):

		// play sound
		PlaySound(IDR_NEWSELSND);

		// set modified state
		SetModified();

		// ok
		break;

	// edit control change
	case(EN_CHANGE):

		// check id
		if(LOWORD(wParam)==IDC_SAVERDESCEDT)
		{
			LockGlobalMsg()

			// set remaining text
			sprintf(g_lpMsg,
					"Description: (%d characters remaining)",
					MAX_SAVER_DESC-g_lpSaverDescEdit->GetWindowTextLength());

			// set description text
			g_lpSaverDescLabel->SetWindowText(g_lpMsg);

			UnlockGlobalMsg()

			// set modified state
			SetModified();
		}

		// ok
		break;

	// edit control max text
	case(EN_MAXTEXT):

		// check id
		if(LOWORD(wParam)==IDC_SAVERDESCEDT)
		{
			// play sound
			PlaySound(FORCE_DEFSND);
		}

		// ok
		break;
	}

	// call base method
	return(CExtDialog::OnCommand(wParam,
								 lParam));
}

// CSaverInfoDlg::OnContextMenu()

void CSaverInfoDlg::OnContextMenu(CWnd* pWnd,
								  CPoint pos)
{
	// check for cycle button
	if(IsPointInWindow(&pos,
					   g_lpMusicCycleRad))
		g_lpMusicCycleRad->OnContextMenu(pWnd,
									     pos);

	// check for shuffle button
	if(IsPointInWindow(&pos,
					   g_lpMusicShuffleRad))
		g_lpMusicShuffleRad->OnContextMenu(pWnd,
									       pos);

	// call base method
	CExtDialog::OnContextMenu(pWnd,
							  pos);
}

// CSaverInfoDlg::OnBrowseBtnClk()

void CSaverInfoDlg::OnBrowseBtnClk(void)
{
	// browse for music file
	BrowseMusicFiles();
}

// CSaverInfoDlg::OnMusicCycleBtnClk()

void CSaverInfoDlg::OnMusicCycleBtnClk(void)
{
	// set cycle radio button
	SetMusicCycleRad();

	// set modified state
	SetModified();
}

// CSaverInfoDlg::OnMusicShuffleBtnClk()

void CSaverInfoDlg::OnMusicShuffleBtnClk(void)
{
	// set shuffle radio button
	SetMusicShuffleRad();

	// set modified state
	SetModified();
}

// CSaverInfoDlg::SetMusicCycleRad()

void CSaverInfoDlg::SetMusicCycleRad(void)
{
	// check cycle button
	g_lpMusicCycleRad->SetCheck(1);
	
	// uncheck shuffle button
	g_lpMusicShuffleRad->SetCheck(0);
}

// CSaverInfoDlg::SetMusicShuffleRad()

void CSaverInfoDlg::SetMusicShuffleRad(void)
{
	// uncheck cycle button
	g_lpMusicCycleRad->SetCheck(0);
	
	// check shuffle button
	g_lpMusicShuffleRad->SetCheck(1);
}

// EditThemes()

BOOL EditThemes(CEditThemesDlg* lpEditThemesDlg)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpEditThemesDlg)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"EditThemes()",
							FALSE);
		return(FALSE);
	}
#endif

	// copy pointer
	g_lpEditThemesDlg=lpEditThemesDlg;

	// run dialog box
	g_lpEditThemesDlg->DoModal();

	// reset pointer
	g_lpEditThemesDlg=NULL;

	// ok
	return(TRUE);
}

// CEditThemesDlg::InitDialog()

BOOL CEditThemesDlg::InitDialog(void)
{
	// counter
	DWORD dwCount;

	// create apply button
	if(!CreateExtButton(&g_lpSubApplyBtn,
						IDC_APPLY))
		return(FALSE);

	// capture apply button
	if(!CaptureApplyBtn(g_lpSubApplyBtn))
		return(FALSE);

	// capture themes list
	if(!CaptureDlgControl(this,
						  g_lpThemesList,
						  IDC_THEMESLIST))
		return(FALSE);

	// add themes to list
	for(dwCount=0;dwCount<g_dwNumThemes;dwCount++)
	{
		// add theme
		if(g_lpThemesList->AddString(g_lplpThemes[dwCount])<0)
		{
			DisplayErrorMessage("Unable to add theme to themes list.");
			return(FALSE);
		}
	}

	// check for windows theme
	if(g_lpThemesList->SearchForString("Windows")==-1)
	{
		// add theme
		if(g_lpThemesList->AddString("Windows")<0)
		{
			DisplayErrorMessage("Unable to add theme to themes list.");
			return(FALSE);
		}
	}

	// check for null theme
	if(g_lpThemesList->SearchForString(NO_SEL_TEXT)==-1)
	{
		// add theme
		if(g_lpThemesList->AddString(NO_SEL_TEXT)<0)
		{
			DisplayErrorMessage("Unable to add theme to themes list.");
			return(FALSE);
		}
	}

	// capture new button
	if(!CaptureDlgControl(this,
						  g_lpNewThemeBtn,
						  IDC_NEWTHEMEBTN))
		return(FALSE);

	// capture delete button
	if(!CaptureDlgControl(this,
						  g_lpDelThemeBtn,
						  IDC_DELTHEMEBTN))
		return(FALSE);

	// capture rename button
	if(!CaptureDlgControl(this,
						  g_lpRenThemeBtn,
						  IDC_RENAMETHEMEBTN))
		return(FALSE);

	// capture defaults button
	if(!CaptureDlgControl(this,
						  g_lpDefThemesBtn,
						  IDC_DEFTHEMESBTN))
		return(FALSE);

	// capture help button
	if(!CaptureDlgControl(this,
						  g_lpThemesHelpBtn,
						  IDC_THEMESHELPBTN))
		return(FALSE);

	// create new theme dialog
	AllocClassObject(g_lpNewThemeDlg,
					 CNewThemeDlg(IDD_NEWTHEME,
								  this));

	// check new object
	if(!g_lpNewThemeDlg)
		return(FALSE);

	// create rename theme dialog
	AllocClassObject(g_lpRenThemeDlg,
					 CRenameThemeDlg(IDD_RENAMETHEME,
									 this));

	// check new object
	if(!g_lpRenThemeDlg)
		return(FALSE);

	// ok
	return(TRUE);
}

// CEditThemesDlg::ReleaseDialog()

void CEditThemesDlg::ReleaseDialog(void)
{
	// free dialog boxes
	FreeClassObject(g_lpNewThemeDlg);
	FreeClassObject(g_lpRenThemeDlg);

	// free apply button
	FreeClassObject(g_lpSubApplyBtn);
}

// CEditThemesDlg::OnNewBtnClk()

void CEditThemesDlg::OnNewBtnClk(void)
{
	// add new theme
	if(g_lpThemesList)
		g_lpThemesList->AddNewTheme();
}

// CEditThemesDlg::OnDelBtnClk()

void CEditThemesDlg::OnDelBtnClk(void)
{
	// delete selection
	if(g_lpThemesList)
		g_lpThemesList->DeleteSelection();
}

// CEditThemesDlg::OnRenBtnClk()

void CEditThemesDlg::OnRenBtnClk(void)
{
	// rename selection
	if(g_lpThemesList)
		g_lpThemesList->RenameSelection();
}

// CEditThemesDlg::OnDefBtnClk()

void CEditThemesDlg::OnDefBtnClk(void)
{
	// reset defaults
	if(g_lpThemesList)
		g_lpThemesList->ResetDefThemes();
}

// CEditThemesDlg::OnHelpBtnClk()

void CEditThemesDlg::OnHelpBtnClk(void)
{
	// show help file
	ShowHelp(IDC_EDITTHEMESDLG,
			 NULL);
}

// CEditThemesDlg::OnCommand()

BOOL CEditThemesDlg::OnCommand(WPARAM wParam,
							   LPARAM lParam)
{
	// check message
	switch(HIWORD(wParam))
	{
	// combo box selection change
	case(LBN_SELCHANGE):

		// check for selection
		if(g_lpThemesList->QuerySelection())
		{
			// enable delete button
			g_lpDelThemeBtn->Enable();

			// enable rename button as req'd
			if(g_lpThemesList->GetSelCount()==1)
				g_lpRenThemeBtn->Enable();
			else
				g_lpRenThemeBtn->Disable();
		}
		else
		{
			// disable buttons
			g_lpDelThemeBtn->Disable();
			g_lpRenThemeBtn->Disable();
		}

		// play sound
		PlaySound(IDR_NEWSELSND);

		// ok
		break;
	}

	// call base method
	return(CExtDialog::OnCommand(wParam,
								 lParam));
}

// CEditThemesDlg::OnContextMenu()

void CEditThemesDlg::OnContextMenu(CWnd* pWnd,
								   CPoint pos)
{
	// check for delete button
	if(IsPointInWindow(&pos,
					   g_lpDelThemeBtn))
		g_lpDelThemeBtn->OnContextMenu(pWnd,
									   pos);

	// check for rename button
	if(IsPointInWindow(&pos,
					   g_lpRenThemeBtn))
		g_lpRenThemeBtn->OnContextMenu(pWnd,
									   pos);

	// call base method
	CExtDialog::OnContextMenu(pWnd,
							  pos);
}

// CThemesList::OnKeyDown()

void CThemesList::OnKeyDown(UINT nChar,
						    UINT nRepCnt,
						    UINT nFlags)
{
	// check for esc key
	if(nChar==VK_ESCAPE)
		ClearSelection();

	// check for del key
	if(nChar==VK_DELETE)
		DeleteSelection();

	// call base method
	CListBox::OnKeyDown(nChar,
						 nRepCnt,
						 nFlags);
}

// CThemesList::AddNewTheme()

BOOL CThemesList::AddNewTheme(void)
{
	// run dialog box
	g_lpNewThemeDlg->DoModal();

	// ok
	return(TRUE);
}

// CThemesList::ClearSelection()

BOOL CThemesList::ClearSelection(BOOL bPlaySnd)
{
	// clear selection
	SetSel(-1,FALSE);

	// play sound
	if(bPlaySnd)
		PlaySound(IDR_CLEARSELSND);

	// disable delete & rename buttons
	g_lpDelThemeBtn->Disable();
	g_lpRenThemeBtn->Disable();

	// ok
	return(TRUE);
}

// CThemesList::QuerySelection()

BOOL CThemesList::QuerySelection(void)
{
	// check for selection
	if(GetSelCount()==0)
		return(FALSE);

	// ok
	return(TRUE);
}

// CEditThemesDlg::PreTranslateMessage()

BOOL CEditThemesDlg::PreTranslateMessage(MSG* pMsg)
{
	// check for key-down message
	if(pMsg->message==WM_KEYDOWN)
	{
		// check for esc
		if(pMsg->wParam==VK_ESCAPE)
		{
			// eat message
			return(FALSE);
		}
	}
	
	// call base method
	return(CExtDialog::PreTranslateMessage(pMsg));
}

// CNewThemeDlg::InitDialog()

BOOL CNewThemeDlg::InitDialog(void)
{
	// capture new theme edit control
	if(!CaptureDlgControl(this,
						  g_lpNewThemeEdit,
						  IDC_NEWTHEMEEDT))
		return(FALSE);

	// set text limit
	g_lpNewThemeEdit->SetLimitText(MAX_THEME_LEN);

	// reset window shown flag
	bWinShown=FALSE;

	// ok
	return(TRUE);
}

// CNewThemeDlg::ApplyChanges()

void CNewThemeDlg::ApplyChanges(void)
{
	// theme id
	int nThemeId;

	LockGlobalMsg()

	// get new theme
	g_lpNewThemeEdit->GetWindowText(g_lpMsg,
									_MAX_PATH-1);

	// clip theme
	g_lpMsg[MAX_THEME_LEN]=0;

	// check length
	if(strlen(g_lpMsg)==0)
	{
		// alert user
		DisplayInfoMessage("Please enter a new theme to add.");

		// return focus
		g_lpNewThemeEdit->SetFocus();

		// set flag
		CloseNotOK();

		UnlockGlobalMsg()

		// try again
		return;
	}

	// compare with existing
	if(g_lpThemesList->SearchForString(g_lpMsg)!=-1)
	{
		// alert user
		DisplayInfoMessage("The theme you entered is already in the list.");

		// return focus
		g_lpNewThemeEdit->SetFocus();

		// select all
		g_lpNewThemeEdit->SetSel(0,-1);

		// set flag
		CloseNotOK();

		UnlockGlobalMsg()

		// try again
		return;
	}

	// add to list & save index
	nThemeId=g_lpThemesList->AddString(g_lpMsg);

	// check index
	if(nThemeId<0)
		DisplayErrorMessage("Unable to add theme to list.");

	UnlockGlobalMsg()

	// clear selection
	g_lpThemesList->ClearSelection(FALSE);

	// select new theme
	g_lpThemesList->SetSel(nThemeId);

	// enable delete & rename button
	g_lpDelThemeBtn->Enable();
	g_lpRenThemeBtn->Enable();

	// set modified state
	g_lpEditThemesDlg->SetModified();

	// call base method
	CExtDialog::ApplyChanges();
}

// CNewThemeDlg::ReleaseDialog()

void CNewThemeDlg::ReleaseDialog(void)
{
}

// CNewThemeDlg::OnCommand()

BOOL CNewThemeDlg::OnCommand(WPARAM wParam,
							 LPARAM lParam)
{
	// check message
	switch(HIWORD(wParam))
	{
	// edit control max text
	case(EN_MAXTEXT):

		// play sound
		PlaySound(FORCE_DEFSND);

		// ok
		break;
	}

	// call base method
	return(CExtDialog::OnCommand(wParam,
								 lParam));
}

// CNewThemeDlg::OnShowWindow()

void CNewThemeDlg::OnShowWindow(BOOL bShow,
							    UINT nStatus)
{
	// check show flag
	if(bShow)
	{
		// check shown flag
		if(!bWinShown)
		{
			// post new-theme message
			PostCommand(g_lpMainSheet,
						IDM_NWTHM_INIT);
			
			// set flag
			bWinShown=TRUE;
		}
	}

	// call base method
	CExtDialog::OnShowWindow(bShow,
							 nStatus);
}

// CThemesList::OnContextMenu()

void CThemesList::OnContextMenu(CWnd* pWnd,
								CPoint pos)
{
	// check visibility
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
			ShowPopupMenu(IDC_THEMESLIST);
		}
		else
		{
			// call base method
			CListBox::OnContextMenu(pWnd,
									pos);
		}
	}
}

// CThemesList::DeleteSelection()

BOOL CThemesList::DeleteSelection(void)
{
	// number of selections
	int nNumSel;

	// counter
	int nCount;

	// selection list
	int* lpnSel=NULL;

	// show no-delete message flag
	BOOL bShowNoDel=FALSE;
	
	// check selection
	if(!QuerySelection())
		return(TRUE);

	// get number of selections
	nNumSel=GetSelCount();

	// allocate memory for selection list
	if(!AllocMem((LPVOID*)&lpnSel,
				 sizeof(int)*nNumSel))
		return(FALSE);

	// get selection list
	if(GetSelItems(nNumSel,
				   lpnSel)!=nNumSel)
	{
		DisplayErrorMessage("Unable to retreive theme selection list.");
		FreeMem((LPVOID*)&lpnSel);
		return(FALSE);
	}

	// sort list
	SortIntList(lpnSel,
				nNumSel);

	LockGlobalLongMsg()

	// begin message
	strcpy(g_lpLongMsg,
		   "The following theme");

	// add 's' if necessary
	if(nNumSel>1)
		strcat(g_lpLongMsg,"s");
	
	// continue message
	strcat(g_lpLongMsg,
		   " will be deleted:\n");

	// add themes
	for(nCount=0;nCount<nNumSel;nCount++)
	{
		// get theme
		GetText(lpnSel[nCount],
				g_lpMsg);
		
		// not too many
		if(nCount>=9)
		{
			// add ellipsis to last item
			if(nCount==9)
				strcat(g_lpLongMsg,
					   "\n    ...more");
		}
		else
		{
			// add tab & bullet
			strcat(g_lpLongMsg,
				   "\n    \xb7 ");

			// add theme
			strcat(g_lpLongMsg,
				   g_lpMsg);
		}

		// check for required items
		if((strcmp(g_lpMsg,"Windows")  ==0)||
		   (strcmp(g_lpMsg,NO_SEL_TEXT)==0))
		{
			// set flag
			bShowNoDel=TRUE;

			// invalidate item
			lpnSel[nCount]=-1;
		}
	}

	// finish message
	strcat(g_lpLongMsg,
		   "\n\nAre you sure?");

	// query user
	if(DisplayMessageBox(g_lpEditThemesDlg->m_hWnd,
						 g_lpLongMsg,
						 (LPSTR)ApplicationName(),
						 MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		// run thru list (backwards)
		for(nCount=nNumSel-1;nCount>=0;nCount--)
		{
			// check item
			if(lpnSel[nCount]!=-1)
			{
				// delete theme
				DeleteString(lpnSel[nCount]);
			}
		}

		// clear selection
		ClearSelection(FALSE);

		// scroll to top
		SetTopIndex(0);

		// set modified state
		g_lpEditThemesDlg->SetModified();

		// check no-del flag
		if(bShowNoDel)
		{
			// alert user
			DisplayInfoMessage("The default themes (None and Windows) cannot be deleted.");
		}
	}

	UnlockGlobalLongMsg()

	// free selection list
	FreeMem((LPVOID*)&lpnSel);

	// ok
	return(TRUE);
}

// CThemesList::ResetDefThemes()

BOOL CThemesList::ResetDefThemes(void)
{
	// query user
	if(DisplayMessageBox(g_lpEditThemesDlg->m_hWnd,
						 "This command will delete all existing themes and replace them with the default themes.\n\nAre you sure?",
						 (LPSTR)ApplicationName(),
						 MB_YESNO|MB_ICONWARNING)!=IDYES)
	{
		// stop here
		return(TRUE);
	}

	// remove existing themes
	ResetContent();

	// add default themes
	if((AddString("Windows")<0)||
	   (AddString("Art")<0)||
	   (AddString("Cartoons")<0)||
	   (AddString("Nature")<0)||
	   (AddString("Miscellaneous")<0)||
	   (AddString("People")<0)||
	   (AddString("Science")<0)||
	   (AddString("Vehicles")<0)||
	   (AddString("3-D")<0)||
	   (AddString("Movies")<0)||
	   (AddString("Kids")<0)||
	   (AddString("Music")<0)||
	   (AddString("Celebrities")<0)||
	   (AddString("Sports")<0)||
	   (AddString("TV")<0)||
	   (AddString("Games")<0)||
	   (AddString("Holidays")<0)||
	   (AddString("Humorous")<0)||
	   (AddString("Animals")<0)||
	   (AddString(NO_SEL_TEXT)<0))
	{
		DisplayErrorMessage("Unable to add theme to list.");
		return(FALSE);
	}

	// clear selection
	ClearSelection(FALSE);

	// scroll to top
	SetTopIndex(0);

	// set modified state
	g_lpEditThemesDlg->SetModified();

	// ok
	return(TRUE);
}

// CSaverInfo::SaverThemeIsDeleted()

BOOL CSaverInfo::SaverThemeIsDeleted(CThemesList* lpThemes)
{
#ifdef DEBUG_MODE
	// verify list
	if(!lpThemes)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CSaverInfo::SaverThemeIsDeleted()",
							FALSE);
		return(FALSE);
	}
#endif

	// return value
	BOOL bRet=FALSE;

	// check for next saver
	if(lpNextSaver)
	{
		// check next saver
		bRet=lpNextSaver->SaverThemeIsDeleted(lpThemes);
	}

	// check return value
	if(!bRet)
	{
		// check load flag
		if(bLoadOK)
		{
			// check this saver
			if(lpThemes->SearchForString(lpTheme)==-1)
				bRet=TRUE;
		}
	}

	// ok
	return(bRet);
}

// CSaverInfo::ValidateThemes()

void CSaverInfo::ValidateThemes(void)
{
	// check for next saver
	if(lpNextSaver)
	{
		// validate next saver
		lpNextSaver->ValidateThemes();
	}

	// check load flag
	if(bLoadOK)
	{
		// validate this saver
		ValidateTheme(&lpTheme);
	}
}

// CSaverInfo::SaveThemes()

void CSaverInfo::SaveThemes(void)
{
	// registry key interface
	CRegKey* lpRegKey;
	
	// check load-ok flag
	if(bLoadOK)
	{
		// get key interface
		AllocClassObject(lpRegKey,
						 CRegKey);

		// check new object
		if(!lpRegKey)
			return;

		LockGlobalMsg()

		// create registry key
		strcpy(g_lpMsg,
			   ApplicationRegistryPath());
		strcat(g_lpMsg,
			   "SaverInfo\\");
		strcat(g_lpMsg,
			   lpRegPath);

		// create registry key
		if(lpRegKey->Create(HKEY_CURRENT_USER,
							g_lpMsg,
							REG_NONE,
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS,
							NULL,
							NULL)==ERROR_SUCCESS)
		{
			AddWinResource

			// save value
			lpRegKey->SetValue(lpTheme,
							   "Theme");

			// close registry key
			if(lpRegKey->Close()==ERROR_SUCCESS)
				RemoveWinResource
		}

		UnlockGlobalMsg()

		// relese key interface
		FreeClassObject(lpRegKey);
	}
	
	// check next saver
	if(lpNextSaver)
	{
		// save next saver
		lpNextSaver->SaveThemes();
	}
}

// CEditThemesDlg::ApplyChanges()

void CEditThemesDlg::ApplyChanges(void)
{
	// number of themes
	int nNumThemes;

	// counter
	int nCount;

	// number of savers
	int nNumSavers;

	// counter #2
	DWORD dwCount;

	// check themes
	if(g_lpSaverInfo->SaverThemeIsDeleted(g_lpThemesList))
	{
		// check must-close flag
		if(!bMustClose)
		{
			// query user
			if(DisplayMessageBox(m_hWnd,
								 "You have chosen to delete a theme that is currently in use.\nAny screensavers that use deleted themes will be reset to None.\n\nAre you sure?",
								 (LPSTR)ApplicationName(),
								 MB_YESNO|MB_ICONWARNING)!=IDYES)
			{
				// don't close
				CloseNotOK();
				
				// try again
				return;
			}
		}

		// set saver info dialog modified
		if(g_lpSaverInfoDlg)
			if(IsWindow(g_lpSaverInfoDlg->m_hWnd))
				g_lpSaverInfoDlg->SetModified();
	}

	// release themes list
	ReleaseThemes();

	// get number of themes
	nNumThemes=g_lpThemesList->GetCount();

	// check for error
	if(nNumThemes<0)
	{
		DisplayErrorMessage("Unable to get number of themes in list.");
		return;
	}

	// add themes
	for(nCount=0;nCount<nNumThemes;nCount++)
	{
		LockGlobalMsg()
		
		// get theme
		if(g_lpThemesList->GetText(nCount,
								   g_lpMsg)==LB_ERR)
		{
			DisplayErrorMessage("Unable to read theme from list.");
			return;
		}

		// add theme
		AddTheme(g_lpMsg);

		UnlockGlobalMsg()
	}

	// save themes (to registry)
	SaveThemes();
	
	// validate themes (in saver list)
	g_lpSaverInfo->ValidateThemes();

	// save themes (in saver list)
	g_lpSaverInfo->SaveThemes();

	// check for theme selection box
	if(IsWindow(g_lpThemeSelBox->m_hWnd))
	{
		// delete themes from box
		while(g_lpThemeSelBox->DeleteString(0)!=CB_ERR)	{}

		// add new themes to box
		for(dwCount=0;dwCount<g_dwNumThemes;dwCount++)
		{
			// add theme
			if(g_lpThemeSelBox->AddString(g_lplpThemes[dwCount])<0)
			{
				DisplayErrorMessage("Unable to add theme to list.");
				return;
			}
		}

		// highlight first selection
		g_lpThemeSelBox->SetCurSel(0);

		// highlight current theme
		g_lpThemeSelBox->SelectStringExact(g_lpCurSaver->lpTheme);
	}

	// check for saver list window
	if(IsWindow(g_lpSaverList->m_hWnd))
	{
		// get number of savers in list
		nNumSavers=g_lpSaverList->GetItemCount();

		// update saver list
		if(nNumSavers)
			for(nCount=0;nCount<nNumSavers;nCount++)
			{
				// cast pointer to saver info
				CSaverInfo* lpSaverInfo=(CSaverInfo*)g_lpSaverList->GetItemData(nCount);

				// check pointer
				if(lpSaverInfo)
				{
					// update theme
					g_lpSaverList->SetItem(nCount,
										   1,
										   LVIF_TEXT,
										   lpSaverInfo->lpTheme,
										   NULL,
										   NULL,
										   NULL,
										   NULL);
				}
#ifdef DEBUG_MODE
				else
				{
					DisplayErrorMessage("Invalid saver info.",
										"CEditThemesDlg::ApplyChanges()",
										FALSE);
					return;
				}
#endif
			}

		// update items
		g_lpSaverList->RedrawItems(0,
								   g_lpSaverList->GetItemCount()-1);

		// update window
		g_lpSaverList->UpdateWindow();
	}

	// update saver info box
	UpdateSaverInfoBox(g_lpCurSaver);

	// call base method
	CExtDialog::ApplyChanges();
}

// CSaverInfoDlg::ClearMusicSel()

BOOL CSaverInfoDlg::ClearMusicSel(void)
{
	// query user
	if(DisplayMessageBox(m_hWnd,
						 "Are you sure you want to set the music for this screensaver to None?",
						 (LPSTR)ApplicationName(),
						 MB_YESNO|MB_ICONQUESTION)==IDNO)
		return(FALSE);

	// free music path
	FreeMem((LPVOID*)&lpMusicPath);
					
	// fill in 'none'
	g_lpMusicSelBox->SetWindowText(NO_SEL_TEXT);

	// uncheck radio buttons
	g_lpMusicCycleRad->SetCheck(0);
	g_lpMusicShuffleRad->SetCheck(0);

	// disable buttons
	g_lpMusicCycleRad->Disable();
	g_lpMusicShuffleRad->Disable();

	// set modified state
	SetModified();

	// ok
	return(TRUE);
}

// CThemesList::RenameSelection()

BOOL CThemesList::RenameSelection(void)
{
	// selected theme
	int nThemeId;

	// check for selection
	if(!QuerySelection())
	{
		DisplayInfoMessage("Please select a theme to rename.");
		return(FALSE);
	}
	else if(GetSelCount()>1)
	{
		DisplayInfoMessage("Please select only one theme to rename.");
		return(FALSE);
	}

	// get selection id
	if(GetSelItems(1,
				   &nThemeId)==LB_ERR)
	{
		DisplayErrorMessage("Unable to get theme selection from list.");
		return(FALSE);
	}

	LockGlobalMsg()
	
	// get selection text
	if(GetText(nThemeId,
			   g_lpMsg)==LB_ERR)
	{
		DisplayErrorMessage("Unable to get theme selection text.");
		UnlockGlobalMsg()
		return(FALSE);
	}

	// check for default themes
	if((strcmp(g_lpMsg,"Windows")  ==0)||
	   (strcmp(g_lpMsg,NO_SEL_TEXT)==0))
	{
		// alert user
		DisplayInfoMessage("The default themes (None and Windows) cannot be renamed.");
		
		// clear selection
		ClearSelection(FALSE);

		UnlockGlobalMsg()

		// ok
		return(FALSE);
	}

	UnlockGlobalMsg()

	// run dialog box
	g_lpRenThemeDlg->DoModal();

	// ok
	return(TRUE);
}

// CRenameThemeDlg::InitDialog()

BOOL CRenameThemeDlg::InitDialog(void)
{
	// capture rename theme edit control
	if(!CaptureDlgControl(this,
						  g_lpRenThemeEdit,
						  IDC_RENAMETHEMEEDT))
		return(FALSE);

	// set text limit
	g_lpRenThemeEdit->SetLimitText(MAX_THEME_LEN);

	// reset window shown flag
	bWinShown=FALSE;

	// ok
	return(TRUE);
}

// CRenameThemeDlg::ReleaseDialog()

void CRenameThemeDlg::ReleaseDialog(void)
{
}

// CRenameThemeDlg::OnCommand()

BOOL CRenameThemeDlg::OnCommand(WPARAM wParam,
								LPARAM lParam)
{
	// check message
	switch(HIWORD(wParam))
	{
	// edit control max text
	case(EN_MAXTEXT):

		// play sound
		PlaySound(FORCE_DEFSND);

		// ok
		break;
	}

	// call base method
	return(CExtDialog::OnCommand(wParam,
								 lParam));
}

// CRenameThemeDlg::OnShowWindow()

void CRenameThemeDlg::OnShowWindow(BOOL bShow,
								   UINT nStatus)
{
	// check show flag
	if(bShow)
	{
		// check shown flag
		if(!bWinShown)
		{
			// post rename-theme message
			PostCommand(g_lpMainSheet,
						IDM_RNTHM_INIT);
			
			// set flag
			bWinShown=TRUE;
		}
	}

	// call base method
	CExtDialog::OnShowWindow(bShow,
							 nStatus);
}

// CThemesList::SearchForString()

int CThemesList::SearchForString(LPSTR lpFind)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFind)
	{
		DisplayErrorMessage("Invalid string value.",
							"CThemesList::SearchForString()",
							FALSE);
		return(LB_ERR);
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
		if(nMatch==LB_ERR||
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
		if(GetText(nMatch,
				   g_lpLongMsg)==LB_ERR)
		{
			UnlockGlobalLongMsg()

			// not found
			return(-1);
		}

		// check for match
		if(strcmp(g_lpLongMsg,
				  lpFind)==0)
		{
			UnlockGlobalLongMsg()

			// ok
			return(nMatch);
		}

		UnlockGlobalLongMsg()
	}
}

// CRenameThemeDlg::ApplyChanges()

void CRenameThemeDlg::ApplyChanges(void)
{
	// theme id
	int nThemeId;
	
	// window rects
	CRect rWnd1;
	CRect rWnd2;
	CRect rWnd3;

	LockGlobalMsg()

	// get new theme
	g_lpRenThemeEdit->GetWindowText(g_lpMsg,
									_MAX_PATH-1);

	// clip theme
	g_lpMsg[MAX_THEME_LEN]=0;

	// check length
	if(strlen(g_lpMsg)==0)
	{
		// alert user
		DisplayInfoMessage("Please enter a new name for this theme.");

		// return focus
		g_lpRenThemeEdit->SetFocus();

		// set flag
		CloseNotOK();

		UnlockGlobalMsg()

		// try again
		return;
	}

	// get selection from list
	if(g_lpThemesList->GetSelItems(1,
								   &nThemeId)!=1)
	{
		DisplayErrorMessage("Unable to read selected theme.");
		return;
	}

	LockGlobalLongMsg()

	// get old theme text
	if(g_lpThemesList->GetText(nThemeId,
							   g_lpLongMsg)==LB_ERR)
	{
		DisplayErrorMessage("Unable to read selected theme text.");
		UnlockGlobalMsg()
		UnlockGlobalLongMsg()
		return;
	}

	// compare with current
	if(strcmp(g_lpMsg,
			  g_lpLongMsg)==0)
	{
		UnlockGlobalMsg()
		UnlockGlobalLongMsg()

		// call base method
		CExtDialog::ApplyChanges();

		// no need to continue
		return;
	}

	UnlockGlobalLongMsg()

	// compare with existing
	if(g_lpThemesList->SearchForString(g_lpMsg)!=-1)
	{
		// alert user
		DisplayInfoMessage("The theme you entered is already in the list.");

		// return focus
		g_lpRenThemeEdit->SetFocus();

		// select all
		g_lpRenThemeEdit->SetSel(0,-1);

		// set flag
		CloseNotOK();

		UnlockGlobalMsg()

		// try again
		return;
	}

	LockGlobalLongMsg()

	// get old theme text (again)
	if(g_lpThemesList->GetText(nThemeId,
							   g_lpLongMsg)==LB_ERR)
	{
		DisplayErrorMessage("Unable to read selected theme text.");
		UnlockGlobalMsg()
		UnlockGlobalLongMsg()
		return;
	}

	UnlockGlobalLongMsg()

	// check for used theme
	if(g_lpSaverInfo->ThemeIsUsed(g_lpLongMsg))
	{
		// check must-close flag
		if(!g_lpEditThemesDlg->bMustClose)
		{
			// query user
			if(DisplayMessageBox(m_hWnd,
								 "You will not be able to cancel your changes after this command.\n\nAre you sure?",
								 (LPSTR)ApplicationName(),
								 MB_YESNO|MB_ICONWARNING)!=IDYES)
			{
				// return focus
				g_lpRenThemeEdit->SetFocus();

				// select all
				g_lpRenThemeEdit->SetSel(0,-1);

				// set flag
				CloseNotOK();

				UnlockGlobalMsg()
				UnlockGlobalLongMsg()

				// try again
				return;
			}
			else
			{
				// get button rects
				g_lpNewThemeBtn->GetWindowRect(&rWnd1);
				g_lpEditThemesDlg->lpApplyBtn->GetWindowRect(&rWnd2);

				// convert to client
				g_lpEditThemesDlg->ScreenToClient(&rWnd1);
				g_lpEditThemesDlg->ScreenToClient(&rWnd2);

				// resize close button rect
				rWnd3.left  =rWnd1.left;
				rWnd3.top   =rWnd2.top;
				rWnd3.right =rWnd1.right;
				rWnd3.bottom=rWnd2.bottom;

				// resize close button
				g_lpEditThemesDlg->lpApplyBtn->MoveWindow(&rWnd3);

				// dialog must close
				g_lpEditThemesDlg->ApplyToClose();
			}
		}
	}

	// replace existing themes
	g_lpSaverInfo->ReplaceThemes(g_lpLongMsg,
								 g_lpMsg);

	UnlockGlobalLongMsg()

	// delete selection
	if(g_lpThemesList->DeleteString(nThemeId)==LB_ERR)
		DisplayErrorMessage("Unable to remove current theme.");

	// add new theme & save index
	nThemeId=g_lpThemesList->AddString(g_lpMsg);

	// check index
	if(nThemeId<0)
		DisplayErrorMessage("Unable to add theme to list.");

	UnlockGlobalMsg()

	// clear selection
	g_lpThemesList->ClearSelection(FALSE);

	// select new theme
	g_lpThemesList->SetSel(nThemeId);

	// enable delete & rename buttons
	g_lpDelThemeBtn->Enable();
	g_lpRenThemeBtn->Enable();

	// set modified state
	g_lpEditThemesDlg->SetModified();

	// call base method
	CExtDialog::ApplyChanges();
}

// CSaverInfo::ReplaceThemes()

void CSaverInfo::ReplaceThemes(LPSTR lpOldTheme,
							   LPSTR lpNewTheme)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpOldTheme||
	   !lpNewTheme)
	{
		DisplayErrorMessage("Invalid string value.",
							"CSaverInfo::ReplaceThemes()",
							FALSE);
		return;
	}
#endif

	// check for next saver
	if(lpNextSaver)
	{
		// replace next saver
		lpNextSaver->ReplaceThemes(lpOldTheme,
								   lpNewTheme);
	}

	// check load flag
	if(bLoadOK)
	{
		// compare with old theme
		if(strcmp(lpTheme,
				  lpOldTheme)==0)
		{
			// free old theme
			FreeMem((LPVOID*)&lpTheme);

			// allocate new theme
			if(!AllocMem((LPVOID*)&lpTheme,
						 strlen(lpNewTheme)+1))
				return;

			// copy new theme
			strcpy(lpTheme,
				   lpNewTheme);
		}
	}
}

// CSaverInfo::ThemeIsUsed()

BOOL CSaverInfo::ThemeIsUsed(LPSTR lpOldTheme)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpOldTheme)
	{
		DisplayErrorMessage("Invalid string value.",
							"CSaverInfo::ThemeIsUsed()",
							FALSE);
		return(FALSE);
	}
#endif

	// check for next saver
	if(lpNextSaver)
	{
		// compare next saver
		if(lpNextSaver->ThemeIsUsed(lpOldTheme))
			return(TRUE);
	}

	// check load flag
	if(bLoadOK)
	{
		// compare themes
		if(strcmp(lpTheme,
				  lpOldTheme)==0)
		{
			// ok
			return(TRUE);
		}
	}

	// not found
	return(FALSE);
}

// CSaverInfoDlg::InitDialog()

BOOL CSaverInfoDlg::InitDialog(void)
{
	// saver title window
	CWnd* lpTitle=NULL;

	// counter
	DWORD dwCount;

	// reset music path
	lpMusicPath=NULL;

	// create apply button
	if(!CreateExtButton(&g_lpApplyBtn,
						IDC_APPLY))
		return(FALSE);

	// capture apply button
	if(!CaptureApplyBtn(g_lpApplyBtn))
		return(FALSE);

	// capture icon window
	if(!CaptureDlgControl(this,
						  g_lpSaverInfoIcon,
						  IDC_SAVERINFOICON))
		return(FALSE);

	// make icon window invisible but active
	g_lpSaverInfoIcon->SetWindowPos(NULL,
								    0,0,
								    0,0,
								    SWP_NOCOPYBITS|
								    SWP_NOMOVE|
								    SWP_NOZORDER);

	// get title window
	lpTitle=GetDlgItem(IDC_SAVERNAME);

	// check window
	if(!lpTitle)
	{
		DisplayErrorMessage("Unable to locate screensaver title window.");
		return(FALSE);
	}

	// set saver title
	lpTitle->SetWindowText(g_lpCurSaver->lpTitle);

	// set bold font
	if(g_lpLCFontBold)
		lpTitle->SetFont(g_lpLCFontBold);

	// capture theme selection box
	if(!CaptureDlgControl(this,
						  g_lpThemeSelBox,
						  IDC_THEMESELBOX))
		return(FALSE);

	// set extended user interface
	g_lpThemeSelBox->SetExtendedUI();

	// add themes to box
	for(dwCount=0;dwCount<g_dwNumThemes;dwCount++)
	{
		// add theme
		if(g_lpThemeSelBox->AddString(g_lplpThemes[dwCount])<0)
		{
			DisplayErrorMessage("Unable to add theme to list.");
			return(FALSE);
		}
	}

	// highlight first selection
	g_lpThemeSelBox->SetCurSel(0);

	// highlight current theme
	g_lpThemeSelBox->SelectStringExact(g_lpCurSaver->lpTheme);

	// capture edit themes button
	if(!CaptureDlgControl(this,
						  g_lpEditThemesBtn,
						  IDC_EDITTHEMESBTN))
		return(FALSE);

	// capture rating selection box
	if(!CaptureDlgControl(this,
						  g_lpRatingSelBox,
						  IDC_RATINGSELBOX))
		return(FALSE);

	// fill in ratings
	if((g_lpRatingSelBox->AddString("Not rated")<0)||
	   (g_lpRatingSelBox->AddString("1 Star")<0)||
	   (g_lpRatingSelBox->AddString("2 Stars")<0)||
	   (g_lpRatingSelBox->AddString("3 Stars")<0)||
	   (g_lpRatingSelBox->AddString("4 Stars")<0)||
	   (g_lpRatingSelBox->AddString("5 Stars")<0))
	{
		DisplayErrorMessage("Unable to add rating string to selection list.");
		return(FALSE);
	}

	// highlight first selection
	g_lpRatingSelBox->SetCurSel(0);

	// highlight current rating
	g_lpRatingSelBox->SetCurSel(g_lpCurSaver->dwRating);

	// capture help button
	if(!CaptureDlgControl(this,
						  g_lpEditHelpBtn,
						  IDC_EDITHELPBTN))
		return(FALSE);

	// capture music selection box
	if(!CaptureDlgControl(this,
						  g_lpMusicSelBox,
						  IDC_MUSICSELBOX))
		return(FALSE);

	// set no-cursor on music box
	g_lpMusicSelBox->SetNoCursor();

	// capture browse button
	if(!CaptureDlgControl(this,
						  g_lpMusicBrowseBtn,
						  IDC_MUSICBROWSEBTN))
		return(FALSE);

	// capture cycle radio button
	if(!CaptureDlgControl(this,
						  g_lpMusicCycleRad,
						  IDC_MUSICCYCLERAD))
		return(FALSE);

	// capture shuffle radio button
	if(!CaptureDlgControl(this,
						  g_lpMusicShuffleRad,
						  IDC_MUSICSHUFFLERAD))
		return(FALSE);

	// check music file
	if(g_lpCurSaver->lpMusic)
	{
		// allocate memory for path
		if(!AllocMem((LPVOID*)&lpMusicPath,
					 strlen(g_lpCurSaver->lpMusic)+1))
			return(FALSE);

		// copy path
		strcpy(lpMusicPath,
			   g_lpCurSaver->lpMusic);
	}

	// check music path
	if(lpMusicPath)
	{
		LockGlobalMsg()

		// get filename
		GetFilenameFromPath(g_lpMsg,
							_MAX_PATH-1,
							lpMusicPath);

		// fill in file
		g_lpMusicSelBox->SetWindowText(g_lpMsg);
		
		UnlockGlobalMsg()
	}
	else
	{
		// fill in none
		g_lpMusicSelBox->SetWindowText(NO_SEL_TEXT);
	}

	// check for playlist
	if(IsValidPlaylist(lpMusicPath))
	{
		// enable radio buttons
		g_lpMusicCycleRad->Enable();
		g_lpMusicShuffleRad->Enable();

		// check shuffle flag
		if(g_lpCurSaver->bShuffle)
			SetMusicShuffleRad();
		else
			SetMusicCycleRad();
	}

	// capture description edit box
	if(!CaptureDlgControl(this,
						  g_lpSaverDescEdit,
						  IDC_SAVERDESCEDT))
		return(FALSE);

	// set text limit
	g_lpSaverDescEdit->SetLimitText(MAX_SAVER_DESC);

	// check for description
	if(strcmp(g_lpCurSaver->lpDesc,
			  NO_DESC_TEXT)!=0)
	{
		// check length
		if(strlen(g_lpCurSaver->lpDesc)>MAX_SAVER_DESC)
		{
			// clip string
			g_lpCurSaver->lpDesc[MAX_SAVER_DESC]=0;
		}

		// set text
		g_lpSaverDescEdit->SetWindowText(g_lpCurSaver->lpDesc);
	}

	// capture description label
	if(!CaptureDlgControl(this,
						  g_lpSaverDescLabel,
						  IDC_SAVERDESC))
		return(FALSE);

	LockGlobalMsg()

	// set remaining text
	sprintf(g_lpMsg,
			"Description: (%d characters remaining)",
			MAX_SAVER_DESC-g_lpSaverDescEdit->GetWindowTextLength());

	// set description text
	g_lpSaverDescLabel->SetWindowText(g_lpMsg);

	UnlockGlobalMsg()
	
	// capture no-mini-preview checkbox
	if(!CaptureDlgControl(this,
						  g_lpNoMiniPrevChk,
						  IDC_DISABLEPREVCHK))
		return(FALSE);

	// check for no preview
	if(g_lpCurSaver->bNoPreview)
	{
		// set check
		g_lpNoMiniPrevChk->SetCheck(1);
	}

	// create edit themes dialog
	AllocClassObject(g_lpEditThemesDlgA,
					 CEditThemesDlg(IDD_EDITTHEMES,
								    this));

	// check new object
	if(!g_lpEditThemesDlgA)
		return(FALSE);

	// create change music dialog
	AllocClassObject(g_lpChangeMusicDlg,
					 CChangeMusicDlg(IDD_CHANGEMUSIC,
								     this));

	// check new object
	if(!g_lpChangeMusicDlg)
		return(FALSE);

	// create music manager dialog
	g_lpMusicManagerDlgB=CreateMusicManagerDlg(this);

	// check new object
	if(!g_lpMusicManagerDlgB)
		return(FALSE);

	// reset shown flag
	bWinShown=FALSE;

	// ok
	return(TRUE);
}

// CSaverInfoDlg::ApplyChanges()

void CSaverInfoDlg::ApplyChanges(void)
{
	// selected item
	int nSelItem;

	// item data
	LVITEM lvi;

	LockGlobalMsg()

	// get new theme
	g_lpThemeSelBox->GetWindowText(g_lpMsg,
								   _MAX_PATH-1);

	// release old theme
	FreeMem((LPVOID*)&g_lpCurSaver->lpTheme);

	// allocate memory for new theme
	if(!AllocMem((LPVOID*)&g_lpCurSaver->lpTheme,
				 strlen(g_lpMsg)+1))
		ForceImmediateExit();

	// copy new theme
	strcpy(g_lpCurSaver->lpTheme,
		   g_lpMsg);

	UnlockGlobalMsg()

	// copy new rating
	g_lpCurSaver->dwRating=g_lpRatingSelBox->GetCurSel();

	// release music
	if(g_lpCurSaver->lpMusic)
		FreeMem((LPVOID*)&g_lpCurSaver->lpMusic);

	// check for new music
	if(lpMusicPath)
	{
		// allocate memory for music
		if(AllocMem((LPVOID*)&g_lpCurSaver->lpMusic,
					strlen(lpMusicPath)+1))
		{
			// copy music
			strcpy(g_lpCurSaver->lpMusic,
				   lpMusicPath);
		}
	}

	// check shuffle button
	if(g_lpMusicShuffleRad->GetCheck()==1)
	{
		// set flag
		g_lpCurSaver->bShuffle=TRUE;
	}
	else
	{
		// reset flag
		g_lpCurSaver->bShuffle=FALSE;
	}

	// release old description
	FreeMem((LPVOID*)&g_lpCurSaver->lpDesc);

	LockGlobalLongMsg()

	// get new description
	g_lpSaverDescEdit->GetWindowText(g_lpLongMsg,
									 LONG_MSG_SIZE);

	// check string
	if(strlen(g_lpLongMsg)==0)
	{
		// copy null description
		strcpy(g_lpLongMsg,
			   NO_DESC_TEXT);
	}

	// allocate new description
	if(AllocMem((LPVOID*)&g_lpCurSaver->lpDesc,
				strlen(g_lpLongMsg)+1))
	{
		// copy string
		strcpy(g_lpCurSaver->lpDesc,
			   g_lpLongMsg);
	}

	UnlockGlobalLongMsg()

	// check no-preview button
	if(g_lpNoMiniPrevChk->GetCheck()==1)
	{
		// set flag
		g_lpCurSaver->bNoPreview=TRUE;

		// stop any running preview
		g_lpSaverPrevWnd->StopPreview();
	}
	else
	{
		// reset flag
		g_lpCurSaver->bNoPreview=FALSE;

		// start preview (if not already running)
		if(!g_lpSaverPrevWnd->bPIValid)
			g_lpSaverPrevWnd->StartPreviewOnDelay(PREVIEW_QUICKDELAY);
	}

	// get saver list selection
	nSelItem=g_lpSaverList->GetSelection();

	// update rating in saver list
	SetCurSaverRating(g_lpCurSaver->dwRating,
					  FALSE);

	// prepare item info
	lvi.mask    =LVIF_TEXT;
	lvi.iItem   =nSelItem;
	lvi.iSubItem=1;
	lvi.pszText =g_lpCurSaver->lpTheme;

	// set item info
	g_lpSaverList->SetItem(&lvi);

	// reset new flag
	g_lpCurSaver->bNew=FALSE;

	// update item
	g_lpSaverList->RedrawItems(nSelItem,
							   nSelItem);

	// update window
	g_lpSaverList->UpdateWindow();

	// update saver info
	UpdateSaverInfoBox(g_lpCurSaver);

	// save changes
	SaveCurSaverInfo();

	// call base method
	CExtDialog::ApplyChanges();
}

// CSaverInfoDlg::OnDisablePrevChkClk()

void CSaverInfoDlg::OnDisablePrevChkClk(void)
{
	// set modified state
	SetModified();
}

// DrawBitmapWithBorder()

BOOL DrawBitmapWithBorder(CWnd* lpTargetWnd,
						  CBitmap* lpBmp,
						  int nX,
						  int nY,
						  int nBdrOfs,
						  COLORREF clrBdr,
						  COLORREF clrBkg,
						  COLORREF clrShadow)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lpBmp||
	   !lpTargetWnd)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"DrawBitmapWithBorder()",
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

	// bitmap data
	BITMAP bm;

	// bitmap sizes
	int nSX;
	int nSY;

	// adjust position by border
	nX+=nBdrOfs;
	nY+=nBdrOfs;

	// gdi object
	CGdiObject* lpGdiObj=NULL;

	// get bitmap data
	if(!lpBmp->GetBitmap(&bm))
	{
		DisplayNEErrorMessage("Unable to read bitmap data.");
		return(FALSE);
	}

	// get sizes
	nSX=bm.bmWidth;
	nSY=bm.bmHeight;

	// get device context
	lpDestDC=lpTargetWnd->GetDC();

	// check for error
	if(!lpDestDC)
	{
		DisplayNEErrorMessage("Cannot get window device context.");
		goto DrawBitmapWithBorder1;
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

		// draw shadow
		lpDestDC->FillSolidRect(rDraw,
								clrShadow);

		// set border rect
		rDraw.left  =(nX-nBdrOfs);
		rDraw.right =rDraw.left+nSX+(nBdrOfs*2);
		rDraw.top   =(nY-nBdrOfs);
		rDraw.bottom=rDraw.top+nSY+(nBdrOfs*2);

		// draw border
		lpDestDC->FillSolidRect(rDraw,
								clrBdr);

		// set background rect
		rDraw.left  =(nX-nBdrOfs)+1;
		rDraw.right =(rDraw.left+nSX+(nBdrOfs*2))-2;
		rDraw.top   =(nY-nBdrOfs)+1;
		rDraw.bottom=(rDraw.top+nSY+(nBdrOfs*2))-2;

		// draw background
		lpDestDC->FillSolidRect(rDraw,
								clrBkg);
	}

	// set bitmap rect
	rDraw.left  =nX;
	rDraw.right =rDraw.left+nSX;
	rDraw.top   =nY;
	rDraw.bottom=rDraw.top+nSY;

	// allocate source dc
	AllocClassObject(lpSrcDC,
					 CDC);

	// check object
	if(!lpSrcDC)
	{
		DisplayNEErrorMessage("Cannot find bitmap device context.");
		goto DrawBitmapWithBorder1;
	}

	// create source dc
	if(!lpSrcDC->CreateCompatibleDC(lpDestDC))
	{
		DisplayNEErrorMessage("Cannot create bitmap device context.");
		goto DrawBitmapWithBorder1;
	}
	else
		AddWinResource

	// select object
	lpGdiObj=lpSrcDC->SelectObject(lpBmp);

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
		DisplayNEErrorMessage("Unable to draw bitmap.");
		lpSrcDC->SelectObject(lpGdiObj);
		goto DrawBitmapWithBorder1;
	}

	// restore objec
	lpSrcDC->SelectObject(lpGdiObj);

	// ok
	bRet=TRUE;

// error exit point
DrawBitmapWithBorder1:;

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
		if(lpTargetWnd->ReleaseDC(lpDestDC))
			RemoveWinResource
	}

	// ok
	return(bRet);
}

// CSaverInfoDlg::OnPaint()

void CSaverInfoDlg::OnPaint(void)
{
	// call base method
	CExtDialog::OnPaint();

	// draw bitmap
	DrawBitmapWithBorder(g_lpSaverInfoIcon,
						 g_lpCurSaver->lpIcon,
						 0,0,
						 6,
						 GetSysColor(COLOR_GRAYTEXT),
						 GetSysColor(COLOR_WINDOW),
						 GetSysColor(COLOR_WINDOWTEXT));
}

// CSaverPage::OnUpBtnClk()

void CSaverPage::OnUpBtnClk(void)
{
	// relay command
	g_lpSaverPlaylist->MoveSelUp();
}

// CSaverPage::OnDownBtnClk()

void CSaverPage::OnDownBtnClk(void)
{
	// relay command
	g_lpSaverPlaylist->MoveSelDown();
}

// CSaverPage::OnTopBtnClk()

void CSaverPage::OnTopBtnClk(void)
{
	// relay command
	g_lpSaverPlaylist->MoveSelTop();
}

// CSaverPage::OnBottomBtnClk()

void CSaverPage::OnBottomBtnClk(void)
{
	// relay command
	g_lpSaverPlaylist->MoveSelBottom();
}

// CSaverPage::OnDeleteBtnClk()

void CSaverPage::OnDeleteBtnClk(void)
{
	// relay command
	g_lpSaverPlaylist->DeleteSel();
}

// CSaverPage::OnClearBtnClk()

void CSaverPage::OnClearBtnClk(void)
{
	// clear list
	g_lpSaverPlaylist->ClearList();

	// set first-to-play flag
	g_lpSaverPage->bResetFtP=TRUE;
}

// CSaverPage::OnSaveBtnClk()

void CSaverPage::OnSaveBtnClk(void)
{
	// save file
	g_lpSaverPlaylist->SaveListFile(GetSaverPListFilterList(),
									"Save Screensaver Playlist",
									"Path_SaverPList",
									"PSSL",
									"spl");
}

// CSaverPage::OnLoadBtnClk()

void CSaverPage::OnLoadBtnClk(void)
{
	// message box result
	int nMBRes;

	// check item count
	if(g_lpSaverPlaylist->GetItemCount())
	{
		// check saved flag
		if(!g_lpSaverPlaylist->bIsSaved)
		{
			// query user
			nMBRes=DisplayMessageBox(m_hWnd,
									 "The current playlist has not been saved.\n\nWould you like to save it now?",
									 (LPSTR)ApplicationName(),
									 MB_YESNOCANCEL|MB_ICONQUESTION);

			// check result
			if(nMBRes==IDYES)
			{
				// save list
				OnSaveBtnClk();

				// stop here
				return;
			}
			else if(nMBRes==IDCANCEL)
			{
				// stop here
				return;
			}
		}
	}

	// reset flag
	g_bInvPListItems=FALSE;

	// relay command
	g_lpSaverPlaylist->LoadListFile(GetSaverPListFilterList(),
									"Load Screensaver Playlist",
									"Path_SaverPList",
									CheckSaverPListFileCallback);

	// check flag
	if(g_bInvPListItems)
		AlertInvSaverPlaylistItems();

	// set first-to-play flag
	bResetFtP=TRUE;
}

// AddCurSaverToPlaylist()

BOOL AddCurSaverToPlaylist(void)
{
	// check current saver
	if(g_lpCurSaver==NULL)
		return(FALSE);

	// add saver
	g_lpSaverPlaylist->AddToList((LPVOID)g_lpCurSaver);

	// make sure selection is visible
	g_lpSaverList->EnsureVisible(g_lpSaverList->GetSelection(),
								 FALSE);

	// switch focus back and forth to playlist to indicate action
	PerformFocusSwap(g_lpSaverPlaylist,
					 g_lpSaverList,
					 75,2);

	// play sound
	PlaySound(IDR_ADDSAVERSND);

	// ok
	return(TRUE);
}

// CSaverPlaylist::OnNotify()

BOOL CSaverPlaylist::OnNotify(WPARAM wParam,
							  LPARAM lParam,
							  LRESULT* pResult)
{
	// cast pointer to notification header
	LPNMHDR lpNM=(LPNMHDR)lParam;

	// cast pointer to tooltip info header
	LPNMTTCUSTOMDRAW lpTTCD=(LPNMTTCUSTOMDRAW)lParam;

	// check notification code
	switch(lpNM->code)
	{
	// tooltip custom draw
	case(NM_CUSTOMDRAW):

		// assume default processing
		(*pResult)=CDRF_DODEFAULT;

		// check draw stage
		switch(lpTTCD->nmcd.dwDrawStage)
		{
		// general pre-paint stage
		case(CDDS_PREPAINT):

			// set new flags
			lpTTCD->uDrawFlags=DT_LEFT;

			LockGlobalTTMsg()

			// get window text
			if(!::GetWindowText(lpTTCD->nmcd.hdr.hwndFrom,
								g_lpTTMsg,
								_MAX_PATH-1))
			{
				UnlockGlobalTTMsg()
				return(TRUE);
			}
			
			// compute new rect
			if(!DrawText(lpTTCD->nmcd.hdc,
						 g_lpTTMsg,
						 -1,
						 &lpTTCD->nmcd.rc,
						 lpTTCD->uDrawFlags|DT_CALCRECT))
			{
				UnlockGlobalTTMsg()
				return(TRUE);
			}
			
			UnlockGlobalTTMsg()

			// ok
			break;
		}

		// ok
		return(TRUE);

	// all other messages
	default:

		// call base function
		return(CPlaylistCtrl::OnNotify(wParam,
									   lParam,
									   pResult));
	}
}

// CSaverPage::OnSetActive()

BOOL CSaverPage::OnSetActive(void)
{
	// call init
	if(!Initialize())
		ForceImmediateExit();

	// ok
	return(TRUE);
}

// CSaverPage::Initialize()

BOOL CSaverPage::Initialize(void)
{
	// call base function
	if(!CPropertyPage::OnSetActive())
		return(FALSE);

	// check initialized flag
	if(g_bSaverPageInit)
		return(g_bSaverPageInitOK);

	// set init flag
	g_bSaverPageInit=TRUE;

	// build saver list
	if(!BuildSaverList())
		return(FALSE);

	// attach clear saver button
	if(!CaptureDlgControl(this,
						  g_lpClearSelBtn,
						  IDC_CLEARSELBTN))
		return(FALSE);

	// attach add saver button
	if(!CaptureDlgControl(this,
						  g_lpAddSaverBtn,
						  IDC_ADDSAVERBTN))
		return(FALSE);
	
	// attach playlist up button
	if(!CaptureDlgControl(this,
						  g_lpPListUpBtn,
						  IDC_PLISTUPBTN))
		return(FALSE);

	// attach playlist down button
	if(!CaptureDlgControl(this,
						  g_lpPListDownBtn,
						  IDC_PLISTDOWNBTN))
		return(FALSE);

	// attach playlist top button
	if(!CaptureDlgControl(this,
						  g_lpPListTopBtn,
						  IDC_PLISTTOPBTN))
		return(FALSE);

	// attach playlist bottom button
	if(!CaptureDlgControl(this,
						  g_lpPListBottomBtn,
						  IDC_PLISTBOTTOMBTN))
		return(FALSE);

	// set as bitmap buttons
	g_lpPListUpBtn->SetSpclBitmapButton(FALSE,
										&g_lpPListUpBmp,
										&g_lpPListUpBmpGr);
	g_lpPListDownBtn->SetSpclBitmapButton(FALSE,
										  &g_lpPListDownBmp,
										  &g_lpPListDownBmpGr);
	g_lpPListTopBtn->SetSpclBitmapButton(FALSE,
										 &g_lpPListTopBmp,
										 &g_lpPListTopBmpGr);
	g_lpPListBottomBtn->SetSpclBitmapButton(FALSE,
											&g_lpPListBottomBmp,
											&g_lpPListBottomBmpGr);
	
	// attach playlist delete button
	if(!CaptureDlgControl(this,
						  g_lpPListDeleteBtn,
						  IDC_PLISTDELBTN))
		return(FALSE);

	// attach playlist clear button
	if(!CaptureDlgControl(this,
						  g_lpPListClearBtn,
						  IDC_PLISTCLRBTN))
		return(FALSE);

	// attach playlist save button
	if(!CaptureDlgControl(this,
						  g_lpPListSaveBtn,
						  IDC_PLISTSAVEBTN))
		return(FALSE);

	// attach playlist load button
	if(!CaptureDlgControl(this,
						  g_lpPListLoadBtn,
						  IDC_PLISTLOADBTN))
		return(FALSE);

	// attach saver sort box
	if(!CaptureDlgControl(this,
						  g_lpSaverSortBox,
						  IDC_PLISTSORTCBX))
		return(FALSE);

	// add items to sort box
	if((g_lpSaverSortBox->AddString("Sort Items by:")<0)||
	   (g_lpSaverSortBox->AddString("\xb7 Name (A-Z)")<0)||
	   (g_lpSaverSortBox->AddString("\xb7 Name (Z-A)")<0)||
	   (g_lpSaverSortBox->AddString("\xb7 Theme (A-Z)")<0)||
	   (g_lpSaverSortBox->AddString("\xb7 Theme (Z-A)")<0)||
	   (g_lpSaverSortBox->AddString("\xb7 Rating (5-1)")<0)||
	   (g_lpSaverSortBox->AddString("\xb7 Rating (1-5)")<0))
	{
		DisplayErrorMessage("Unable to add item to sort list.");
		return(FALSE);
	}

	// select first string
	g_lpSaverSortBox->SetCurSel(0);

	// attach saver playlist
	if(!CaptureDlgControl(this,
						  g_lpSaverPlaylist,
						  IDC_CURRPLIST))
		return(FALSE);

	// set playlist buttons
	g_lpSaverPlaylist->SetButtonPtrs(g_lpPListUpBtn,
									 g_lpPListDownBtn,
									 g_lpPListTopBtn,
									 g_lpPListBottomBtn,
									 g_lpPListDeleteBtn,
									 g_lpPListClearBtn,
									 g_lpPListSaveBtn,
									 g_lpPListLoadBtn);

	// set playlist auxilliary controls
	g_lpSaverPlaylist->SetAuxCtrlPtrs(g_lpSaverSortBox,
									  g_lpPListSaveBtn);

	// set playlist callbacks
	g_lpSaverPlaylist->SetCallbacks(GetSaverTitle,
									GetSaverSaveData,
									GetSaverItemData,
									GetSaverTooltip);
									
	// set playlist parent window
	g_lpSaverPlaylist->SetParentPropPage(this);

	// initialize playlist
	if(!g_lpSaverPlaylist->Init("Screensavers to Show:"))
		return(FALSE);

	// load playlist
	if(!g_lpSaverPlaylist->LoadListReg(ApplicationRegistryPath(),
									   "CurrPList"))
		return(FALSE);
	
	// attach saver info box
	if(!CaptureDlgControl(this,
						  g_lpSaverInfoBox,
						  IDC_SAVERINFO))
		return(FALSE);

	// attach settings button
	if(!CaptureDlgControl(this,
						  g_lpSaverSettingsBtn,
						  IDC_SETTINGSBTN))
		return(FALSE);

	// attach preview button
	if(!CaptureDlgControl(this,
						  g_lpPreviewSaverBtn,
						  IDC_PREVIEWBTN))
		return(FALSE);

	// attach edit info button
	if(!CaptureDlgControl(this,
						  g_lpEditSaverInfoBtn,
						  IDC_EDITINFOBTN))
		return(FALSE);

	// create preview window
	if(!CreateSaverPreviewWnd())
		return(FALSE);

	// attach preview checkbox
	if(!CaptureDlgControl(this,
						  g_lpMiniPreviewChk,
						  IDC_SHOWPREVIEWCHK))
		return(FALSE);

	// load preview flag
	g_bShowSaverPreview=(BOOL)LoadOptionInt("Savers_MiniPreview",
											0,
											1,
											1);

	// update checkbox
	ToggleSaverPreview(FALSE);

	// update saver info
	if(!UpdateSaverInfoBox(NULL))
		return(FALSE);

	// create saver info dialog
	AllocClassObject(g_lpSaverInfoDlg,
					 CSaverInfoDlg(IDD_SAVERINFO,
								   this));

	// check new object
	if(!g_lpSaverInfoDlg)
		return(FALSE);

	// add tooltips to buttons
	if(AddToolTip(g_lpMainToolTip,g_lpPListUpBtn,"Move Up"))
		if(AddToolTip(g_lpMainToolTip,g_lpPListDownBtn,"Move Down"))
			if(AddToolTip(g_lpMainToolTip,g_lpPListTopBtn,"Move to Top"))
				AddToolTip(g_lpMainToolTip,g_lpPListBottomBtn,"Move to Bottom");

	// reset first-to-play flag
	bResetFtP=FALSE;

	// set init-ok flag
	g_bSaverPageInitOK=TRUE;

	// ok
	return(TRUE);
}

// CSaverPage::OnOK()

void CSaverPage::OnOK(void)
{
	// rectangle object
	CRect rRect;

	// column width values
	int nColWd1;
	int nColWd2;
	int nColWd3;

	// first-to-play index
	int nFtPIdx;

	// check initialized flag
	if(g_bSaverPageInitOK)
	{
		// check number of items
		if(g_lpSaverList->GetItemCount()>0)
		{
			// check info flag
			if(g_bShowSaverInfo)
			{
				// get theme list rect
				g_lpSaverList->GetSubItemRect(0,1,
											  LVIR_BOUNDS,
											  rRect);

				// get theme list width
				nColWd2=rRect.Width();
				
				// get rating list rect
				g_lpSaverList->GetSubItemRect(0,2,
											  LVIR_BOUNDS,
											  rRect);

				// get rating list width
				nColWd3=rRect.Width();
				
				// get title list rect
				g_lpSaverList->GetSubItemRect(0,0,
											  LVIR_BOUNDS,
											  rRect);

				// get title list width
				nColWd1=rRect.Width()-(nColWd2+nColWd3);
				
				// save saver list widths
				SaveOptionInt("Savers_TitleListWd",
							  nColWd1);
				SaveOptionInt("Savers_ThemeListWd",
							  nColWd2);
				SaveOptionInt("Savers_RatingListWd",
							  nColWd3);

			}

			// save ratings
			g_lpSaverInfo->SaveRatings();
		}

		// save last sort flag
		SaveOptionInt("Savers_SLSFlag",
					  (int)g_dwLastSlsFlag);

		// save details flag
		SaveOptionInt("Savers_SListInfo",
					  (int)g_bShowSaverInfo);

		// save rating images flag
		SaveOptionInt("Savers_RatingImgs",
					  (int)g_bShowRatingImgs);

		// save popup info flag
		SaveOptionInt("Savers_PopupInfo",
					  (int)g_bShowPopupInfo);

		// save mini-preview flag
		SaveOptionInt("Savers_MiniPreview",
					  (int)g_bShowSaverPreview);

		// check playlist
		if(g_lpSaverPlaylist->GetItemCount()==0)
			DisplayOptMessageBox("The screensaver playlist is empty!\n\nA default screensaver will be shown when ProSaver is activated.",
								 (LPSTR)ApplicationName(),
								 MB_OK|MB_ICONEXCLAMATION,
								 "MsgBox_PListEmpty");

		// save playlist
		g_lpSaverPlaylist->SaveListReg(ApplicationRegistryPath(),
									   "CurrPList");

		// get first-to-play index
		nFtPIdx=LoadOptionInt("Savers_NextPlay",
							  0,
							  65535,
							  0);

		// compare values
		if(nFtPIdx>g_lpSaverPlaylist->GetItemCount()||
		   bResetFtP)
		{
			// reset value
			SaveOptionInt("Savers_NextPlay",
						  0);

			// reset flag
			bResetFtP=FALSE;
		}
	}

	// apply general changes
	g_lpMainSheet->ApplyChanges();

	// call base function
	CPropertyPage::OnOK();
}

// GetSaverTitle()

BOOL GetSaverTitle(LPSTR lpStr,
				   LPVOID lpItemData)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetSaverTitle()",
							FALSE);
		return(FALSE);
	}
#endif

	// cast pointer to saver info
	CSaverInfo* lpSaverInfo=(CSaverInfo*)lpItemData;

	// check for saver info
	if(!lpSaverInfo)
		return(FALSE);
	
	LockGlobalMsg()
	
	// copy title (exclude opening space)
	strcpy(g_lpMsg,
		   &lpSaverInfo->lpTitle[1]);

	// remove closing space
	g_lpMsg[strlen(g_lpMsg)-1]=0;

	// copy to string
	strcpy(lpStr,
		   g_lpMsg);

	UnlockGlobalMsg()

	// ok
	return(TRUE);
}

// GetSaverSaveData()

BOOL GetSaverSaveData(LPSTR lpStr,
					  LPVOID lpItemData)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetSaverSaveData()",
							FALSE);
		return(FALSE);
	}
#endif

	// cast pointer to saver info
	CSaverInfo* lpSaverInfo=(CSaverInfo*)lpItemData;

	// check for saver info
	if(!lpSaverInfo)
		return(FALSE);
	
	// copy registry path
	strcpy(lpStr,
		   lpSaverInfo->lpRegPath);

	// ok
	return(TRUE);
}

// GetSaverItemData()

LPVOID GetSaverItemData(LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetSaverItemData()",
							FALSE);
		return(FALSE);
	}
#endif

	// item data
	LPVOID lpItemData;
	
	// search for saver
	lpItemData=g_lpSaverInfo->FindSaver(lpStr);

	// check for data
	if(!lpItemData)
	{
		// set flag
		g_bInvPListItems=TRUE;

		// set invalid data
		lpItemData=IGNORE_ITEM_DATA;
	}

	// ok
	return(lpItemData);
}

// CSaverInfo::FindSaver()

LPVOID CSaverInfo::FindSaver(LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"CSaverInfo::FindSaver()",
							FALSE);
		return(FALSE);
	}
#endif

	// check ok flag
	if(bLoadOK)
	{
		// compare with registry path
		if(strcmp(lpStr,
				  lpRegPath)==0)
		{
			// return pointer to this saver
			return((LPVOID)this);
		}
	}

	// check for next saver
	if(lpNextSaver)
		return(lpNextSaver->FindSaver(lpStr));
	else
		return(NULL);
}

// CSaverInfo::FindSaverByTitle()

CSaverInfo* CSaverInfo::FindSaverByTitle(LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"CSaverInfo::FindSaverByTitle()",
							FALSE);
		return(FALSE);
	}
#endif

	// check ok flag
	if(bLoadOK)
	{
		// compare with title
		if(strcmp(lpStr,
				  lpTitle)==0)
		{
			// return pointer to this saver
			return(this);
		}
	}

	// check for next saver
	if(lpNextSaver)
		return(lpNextSaver->FindSaverByTitle(lpStr));
	else
		return(NULL);
}

// GetSaverTooltip()

BOOL GetSaverTooltip(LPSTR lpStr,
					 LPVOID lpItemData)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetSaverTooltip()",
							FALSE);
		return(FALSE);
	}
#endif

	// saver info
	CSaverInfo* lpSaverInfo;

	// check flag
	if(!g_bShowPListPopup)
		return(FALSE);

	// check item data
	if(!lpItemData)
		return(FALSE);

	// get saver info
	lpSaverInfo=(CSaverInfo*)lpItemData;

	// prepare text
	strcpy(lpStr,"Name:");
	strcat(lpStr,lpSaverInfo->lpTitle);
	strcat(lpStr,"\nTheme: ");
	strcat(lpStr,lpSaverInfo->lpTheme);
	strcat(lpStr,"\nRating: ");
	strcat(lpStr,GetRatingString(lpSaverInfo->dwRating));

	// ok
	return(TRUE);
}

// AlertInvSaverPlaylistItems()

void AlertInvSaverPlaylistItems(void)
{
	// counters
	int nCount;
	int nCount2;

	// max items
	int nMaxItems;

	// playlist data
	LPPLAYLISTDATA lpData;

	// string pointer
	LPSTR lpStr;

	// make sure playlist is valid
	if(!g_lpSaverPlaylist)
		return;

	// get max items
	nMaxItems=g_lpSaverPlaylist->GetItemCount();

	// check for items
	if(!nMaxItems)
		return;

	// reset secondary counter
	nCount2=0;

	LockGlobalLongMsg()
	
	// prepare message
	strcpy(g_lpLongMsg,
		   "The following playlist item(s) could not be found:\n");

	// run through items
	for(nCount=0;nCount<nMaxItems;nCount++)
	{
		// get data
		if(g_lpSaverPlaylist->GetPlaylistItemData(nCount,
												  &lpData))
		{
			// check data
			if(lpData)
			{
				// check title
				if(lpData->lpTitle)
				{
					// check title length
					if(strlen(lpData->lpTitle)>0)
					{
						// check for data
						if(lpData->lpUserData==NULL)
						{
							// search for title
							lpStr=strstr(g_lpLongMsg,
										 lpData->lpTitle);

							// check for string
							if(!lpStr)
							{
								// not too many
								if(nCount2>=9)
								{
									// add ellipsis to last item
									if(nCount2==9)
										strcat(g_lpLongMsg,
											   "\n    ...more");
								}
								else
								{
									// add tab & bullet
									strcat(g_lpLongMsg,
										   "\n    \xb7 ");

									// add title
									strcat(g_lpLongMsg,
										   lpData->lpTitle);
								}

								// increment secondary counter
								nCount2++;
							}
						}
					}
				}
			}
		}
	}

	// finish message
	strcat(g_lpLongMsg,
		   "\n\nDo you want to remove these items from the playlist?");

	UnlockGlobalLongMsg()

	// query user to remove
	if(DisplayOptMessageBox(g_lpLongMsg,
							ApplicationName(),
							MB_YESNO|
							MB_ICONEXCLAMATION,
							"MsgBox_RemoveInv")==IDYES)
	{
		// purge items
		g_lpSaverPlaylist->PurgeInvalid(TRUE);
	}
	else
	{
		// alert user about items
		DisplayOptMessageBox(INV_PLIST_MSG,
							 ApplicationName(),
							 MB_OK|
							 MB_ICONINFORMATION,
							 "MsgBox_InvGrayed");
	}
}

// CSaverInfo::GetNumNewSavers()

int CSaverInfo::GetNumNewSavers(void)
{
	// reset counter
	int nCount=0;

	// check next saver
	if(lpNextSaver)
	{
		// get new count
		nCount=lpNextSaver->GetNumNewSavers();
	}

	// check flags
	if(bLoadOK&&
	   bNew)
	{
		// increment counter
		nCount++;
	}

	// ok
	return(nCount);
}

// CSaverInfo::AlertNewSavers()

void CSaverInfo::AlertNewSavers(LPSTR lpMsg,
								int nCount)
{
	// number of new savers
	int nNumNew;

	// check for existing message
	if(!lpMsg)
	{
		// get new savers
		nNumNew=GetNumNewSavers();

		// check count
		if(!nNumNew)
			return;

		LockGlobalLongMsg()

		// prepare text
		strcpy(g_lpLongMsg,
			   (nNumNew==1 ? "A new screensaver has" :"New screensavers have"));
		strcat(g_lpLongMsg,
			   " been found!\n");
	}

	// check flags
	if(bLoadOK&&
	   bNew)
	{
		// not too many
		if(nCount>=9)
		{
			// add ellipsis to last item
			if(nCount==9)
				strcat(g_lpLongMsg,
					   "\n    ...more");
		}
		else
		{
			// add tab & bullet
			strcat(g_lpLongMsg,
				   "\n    \xb7 ");

			// add title (minus leading space)
			strcat(g_lpLongMsg,
				   &lpTitle[1]);
		}

		// increment counter
		nCount++;
	}

	// check next saver
	if(lpNextSaver)
		lpNextSaver->AlertNewSavers(g_lpLongMsg,
									nCount);

	// check for existing message
	if(!lpMsg)
	{
		// close message
		strcat(g_lpLongMsg,
			   "\n\nThe new item");
		strcat(g_lpLongMsg,
			   (nNumNew==1 ? " is" : "s are"));
		strcat(g_lpLongMsg,
			   " highlighted in bold text.");

		/* (don't like this)
		LockGlobalErrorMsg()

		// save message
		strcpy(g_lpErrorMsg,
			   g_lpLongMsg);
		
		UnlockGlobalLongMsg()

		// highlight first new item
		g_lpSaverList->HighlightFirstNewSaver();

		LockGlobalLongMsg()

		// restore message
		strcpy(g_lpLongMsg,
			   g_lpErrorMsg);
		
		UnlockGlobalErrorMsg()
		*/

		UnlockGlobalLongMsg()

		// alert user
		DisplayOptMessageBox(g_lpLongMsg,
							 ApplicationName(),
							 MB_OK|
							 MB_ICONINFORMATION,
							 "MsgBox_NewSavers");
	}
}

// CSaverList::HighlightFirstNewSaver()

void CSaverList::HighlightFirstNewSaver(void)
{
	// counter
	int nCount;

	// number of items
	int nNumItems;
	
	// pointer to saver info
	CSaverInfo* lpSaverInfo;

	// get item count
	nNumItems=GetItemCount();

	// check item count
	if(nNumItems==0)
		return;

	// run through list
	for(nCount=0;nCount<nNumItems;nCount++)
	{
		// get item data
		lpSaverInfo=(CSaverInfo*)GetItemData(nCount);

		// check data
		if(lpSaverInfo)
		{
			// check flags
			if(lpSaverInfo->bLoadOK&&
			   lpSaverInfo->bNew)
			{
				// make item visible
				EnsureVisible(nCount,
							  FALSE);

				// highlight item
				SetItemState(nCount,
							 LVIS_FOCUSED|
							 LVIS_SELECTED,
							 0xFF);

				// capture focus
				SetFocus();
				
				// stop here
				return;
			}
		}
	}
}

// CSaverPlaylist::HighlightSelInSaverList()

void CSaverPlaylist::HighlightSelInSaverList(void)
{
	// current selection
	int nItem;

	// playlist data
	LPPLAYLISTDATA lpPD;

	// list control find info
	LVFINDINFO lvfi;

	// check for selection
	nItem=GetSelection();

	// verify selection
	if(nItem<0)
		return;

	// get item data
	if(!GetPlaylistItemData(nItem,
							&lpPD))
		return;

	// check item data
	if(!lpPD)
		return;

	// prepare find info
	lvfi.flags =LVFI_PARAM;
	lvfi.lParam=(LPARAM)lpPD->lpUserData;

	// find saver in list
	nItem=g_lpSaverList->FindItem(&lvfi);

	// check item
	if(nItem<0)
		return;

	// make item visible
	g_lpSaverList->EnsureVisible(nItem,
								 FALSE);

	// perform focus swap
	PerformFocusSwap(g_lpSaverList,
					 this,
					 75,1);

	// highlight item
	g_lpSaverList->SetItemState(nItem,
								LVIS_FOCUSED|
								LVIS_SELECTED,
								0xFF);
}

// CSaverPlaylist::OnKeyDown()

void CSaverPlaylist::OnKeyDown(UINT nChar,
							   UINT nRepCnt,
							   UINT nFlags)
{
	// check for left arrow
	if(nChar==VK_LEFT)
	{
		// do nothing
	}

	// call base method
	CPlaylistCtrl::OnKeyDown(nChar,
							 nRepCnt,
							 nFlags);
}

// CSaverSortBox::CSaverSortBox()

CSaverSortBox::CSaverSortBox(UINT nID)
{
	// save id
	nCtrlId=nID;

	// reset flags
	bBoxDown=FALSE;

	// call base constructor
	CExtComboBox::CExtComboBox();
}

// CSaverSortBox::OnCommand()

BOOL CSaverSortBox::OnCommand(WPARAM wParam,
							  LPARAM lParam)
{
	// call base method
	return(CExtComboBox::OnCommand(wParam,
								   lParam));
}

// CSaverPage::OnCommand()

BOOL CSaverPage::OnCommand(WPARAM wParam,
						   LPARAM lParam)
{
	// check control id
	switch(LOWORD(wParam))
	{
	// playlist sort box
	case(IDC_PLISTSORTCBX):

		// verify sort box control
		if(g_lpSaverSortBox)
		{
			// check notification message
			switch(HIWORD(wParam))
			{
			// show dropdown
			case(CBN_DROPDOWN):

				// set flag
				g_lpSaverSortBox->bBoxDown=TRUE;

				// ok
				break;

			// hide dropdown
			case(CBN_CLOSEUP):

				// set flag
				g_lpSaverSortBox->bBoxDown=FALSE;

				// reset selection
				g_lpSaverSortBox->SetCurSel(0);

				// ok
				break;

			// selection change ok
			case(CBN_SELENDOK):

				// sort based on selection
				SortSaverPlaylist(g_lpSaverSortBox->GetCurSel());
				
				// reset selection
				g_lpSaverSortBox->SetCurSel(0);

				// ok
				break;
			}
		}

		// ok
		break;
	}

	// call base method
	return(CPropertyPage::OnCommand(wParam,
									lParam));
}

// CSaverSortBox::OnKeyDown()

void CSaverSortBox::OnKeyDown(UINT nChar,
							  UINT nRepCnt,
							  UINT nFlags)
{
	// check box state
	if(!bBoxDown)
	{
		// eat direction keys
		if(nChar==VK_LEFT||
		   nChar==VK_RIGHT||
		   nChar==VK_UP||
		   nChar==VK_DOWN||
		   nChar==VK_HOME||
		   nChar==VK_END||
		   nChar==VK_PRIOR||
		   nChar==VK_NEXT)
			return;
	}
	
	// call base method
	CExtComboBox::OnKeyDown(nChar,
							nRepCnt,
							nFlags);
}

// CSaverPlaylist::QueryPurgeInv()

void CSaverPlaylist::QueryPurgeInv(void)
{
	// selected item
	int nItem;

	// query user
	if(DisplayMessageBox(g_lpSaverPage->m_hWnd,
						 "All invalid items will be deleted.\n\nAre you sure?",
						 (LPSTR)ApplicationName(),
						 MB_YESNO|MB_ICONQUESTION)==IDYES)
	{
		// check for selection
		if(g_lpSaverPlaylist->QuerySelection())
		{
			// get selection
			nItem=g_lpSaverPlaylist->GetSelection();

			// clear selection
			g_lpSaverPlaylist->SetItemState(nItem,
											NULL,
											0xFF);
		}

		// purge invalid items
		PurgeInvalid();

		// scroll to top
		g_lpSaverPlaylist->EnsureVisible(0,
										 FALSE);

		// set parent modified
		g_lpSaverPage->SetModified();
	}
}

// SortSaverPlaylist()

void SortSaverPlaylist(int nCode)
{
	// selected item
	int nItem;

	// check code
	if(nCode==0)
		return;

	// check for selection
	if(g_lpSaverPlaylist->QuerySelection())
	{
		// get selection
		nItem=g_lpSaverPlaylist->GetSelection();

		// clear selection
		g_lpSaverPlaylist->SetItemState(nItem,
										NULL,
										0xFF);
	}

	// play sound
	PlaySound(IDR_SORTSND);

	// perform sort
	g_lpSaverPlaylist->SortItems(SortSaverPlaylistCallback,
								 (DWORD)nCode);

	// renumber items
	g_lpSaverPlaylist->RenumberItems();

	// scroll to top
	g_lpSaverPlaylist->EnsureVisible(0,
									 FALSE);

	// set parent modified
	g_lpSaverPlaylist->SetParentModified();
}

// SortSaverPlaylistCallback()

int CALLBACK SortSaverPlaylistCallback(LPARAM lParam1,
									   LPARAM lParam2,
									   LPARAM lParamSort)
{
	// init return value
	int nRet=0;

	// set data indices (indexing system is 1-based)
	int nIndex1=((int)lParam1)-1;
	int nIndex2=((int)lParam2)-1;

	// cast pointers to item data
	LPPLAYLISTDATA lpPD1=&g_lpSaverPlaylist->lpPListData[nIndex1];
	LPPLAYLISTDATA lpPD2=&g_lpSaverPlaylist->lpPListData[nIndex2];

	// pointers to saver info
	CSaverInfo* lpSI1=NULL;
	CSaverInfo* lpSI2=NULL;

	// verify item data
	if(lpPD1&&
	   lpPD2)
	{
		// cast pointers to saver info
		lpSI1=(CSaverInfo*)lpPD1->lpUserData;
		lpSI2=(CSaverInfo*)lpPD2->lpUserData;

		// check code
		switch(lParamSort)
		{
		// by name (asc)
		case(1):

			// compare titles
			nRet=stricmp(lpPD1->lpTitle,
						 lpPD2->lpTitle);

			// ok
			break;

		// by name (des)
		case(2):

			// compare titles
			nRet=-stricmp(lpPD1->lpTitle,
						  lpPD2->lpTitle);

			// ok
			break;

		// by theme (asc)
		case(3):

			// check items
			if(lpSI1&&lpSI2)
			{
				// compare themes
				nRet=stricmp(lpSI1->lpTheme,
							 lpSI2->lpTheme);
			}
			else if(lpSI1&&!lpSI2)
			{
				// #1 is first
				nRet=-1;
			}
			else if(!lpSI1&&lpSI2)
			{
				// #2 is first
				nRet=1;
			}

			// check return value
			if(nRet==0)
			{
				// sort by name (asc) instead
				nRet=SortSaverPlaylistCallback(lParam1,
											   lParam2,
											   1);
			}

			// ok
			break;

		// by theme (des)
		case(4):

			// check items
			if(lpSI1&&lpSI2)
			{
				// compare themes
				nRet=-stricmp(lpSI1->lpTheme,
							  lpSI2->lpTheme);
			}
			else if(lpSI1&&!lpSI2)
			{
				// #1 is first
				nRet=-1;
			}
			else if(!lpSI1&&lpSI2)
			{
				// #2 is first
				nRet=1;
			}

			// check return value
			if(nRet==0)
			{
				// sort by name (des) instead
				nRet=SortSaverPlaylistCallback(lParam1,
											   lParam2,
											   2);
			}

			// ok
			break;

		// by rating (asc)
		case(5):

			// check items
			if(lpSI1&&lpSI2)
			{
				// compare ratings
				if(lpSI1->dwRating<lpSI2->dwRating)
					nRet=1;
				else if(lpSI1->dwRating>lpSI2->dwRating)
					nRet=-1;
			}
			else if(lpSI1&&!lpSI2)
			{
				// #1 is first
				nRet=-1;
			}
			else if(!lpSI1&&lpSI2)
			{
				// #2 is first
				nRet=1;
			}

			// check return value
			if(nRet==0)
			{
				// sort by name (asc) instead
				nRet=SortSaverPlaylistCallback(lParam1,
											   lParam2,
											   1);
			}

			// ok
			break;

		// by rating (des)
		case(6):

			// check items
			if(lpSI1&&lpSI2)
			{
				// compare ratings
				if(lpSI1->dwRating<lpSI2->dwRating)
					nRet=-1;
				else if(lpSI1->dwRating>lpSI2->dwRating)
					nRet=1;
			}
			else if(lpSI1&&!lpSI2)
			{
				// #1 is first
				nRet=-1;
			}
			else if(!lpSI1&&lpSI2)
			{
				// #2 is first
				nRet=1;
			}

			// check return value
			if(nRet==0)
			{
				// sort by name (des) instead
				nRet=SortSaverPlaylistCallback(lParam1,
											   lParam2,
											   2);
			}

			// ok
			break;
		}
	}

	// ok
	return(nRet);
}

// TogglePListPopupInfo()

void TogglePListPopupInfo(void)
{
	// toggle value
	g_bShowPListPopup=(g_bShowPListPopup ? FALSE : TRUE);

	// set modified state
	g_lpSaverPage->SetModified();
}

// GetScreensaversFromUserFolders()

BOOL GetScreensaversFromUserFolders(void)
{
	// load search paths & add
	return(LoadSearchPathsFromReg(ApplicationRegistryPath(),
								  "SearchPaths",
								  TRUE));
}

// AssignDuplicateSaverIDs()

BOOL AssignDuplicateSaverIDs(void)
{
	// pointers to saver info
	CSaverInfo* lpSaver     =NULL;
	CSaverInfo* lpFoundSaver=NULL;

	// string length
	int nLen;

	// reset saver info pointer
	lpSaver=g_lpSaverInfo;

	// loop through savers
	while(lpSaver)
	{
		// check load flag
		if(lpSaver->bLoadOK)
		{
			// check for next saver
			if(lpSaver->lpNextSaver)
			{
				// search for duplicate
				lpFoundSaver=lpSaver->lpNextSaver->FindSaverByTitle(lpSaver->lpTitle);

				// check return
				if(lpFoundSaver)
				{
					// set flags for both
					lpSaver->bIsDup     =TRUE;
					lpFoundSaver->bIsDup=TRUE;
				}
			}
		}

		// move to next saver
		lpSaver=lpSaver->lpNextSaver;
	}

	// reset saver info pointer
	lpSaver=g_lpSaverInfo;

	// loop through savers
	while(lpSaver)
	{
		// check load flag
		if(lpSaver->bLoadOK)
		{
			// check duplicate flag
			if(lpSaver->bIsDup)
			{
				// check duplicate index
				if(lpSaver->dwDupIdx==0)
				{
					// get new index
					lpSaver->dwDupIdx=GetNextDuplicateSaverID(&lpSaver->lpTitle[1]);
				}

				// get title length
				nLen=strlen(lpSaver->lpTitle);

				LockGlobalMsg()

				// prepare duplicate text
				sprintf(g_lpMsg,
						"[%u] ",
						lpSaver->dwDupIdx);

				// expand title string
				ExpandMem((LPVOID*)&lpSaver->lpTitle,
						  nLen+1,
						  strlen(g_lpMsg)+1);

				// add duplicate text
				strcat(lpSaver->lpTitle,
					   g_lpMsg);

				UnlockGlobalMsg()
			}
		}

		// move to next saver
		lpSaver=lpSaver->lpNextSaver;
	}

	// save duplicate ids
	g_lpSaverInfo->SaveDuplicateIDs();

	// ok
	return(TRUE);
}

// CSaverInfo::SaveDuplicateIDs()

void CSaverInfo::SaveDuplicateIDs(void)
{
	// registry key interface
	CRegKey* lpRegKey;
	
	// check load-ok flag
	if(bLoadOK)
	{
		// get key interface
		AllocClassObject(lpRegKey,
						 CRegKey);

		// check new object
		if(!lpRegKey)
			return;

		LockGlobalMsg()

		// create registry key
		strcpy(g_lpMsg,
			   ApplicationRegistryPath());
		strcat(g_lpMsg,
			   "SaverInfo\\");
		strcat(g_lpMsg,
			   lpRegPath);

		// create registry key
		if(lpRegKey->Create(HKEY_CURRENT_USER,
							g_lpMsg,
							REG_NONE,
							REG_OPTION_NON_VOLATILE,
							KEY_ALL_ACCESS,
							NULL,
							NULL)==ERROR_SUCCESS)
		{
			AddWinResource

			// save value
			lpRegKey->SetValue(itoa(dwDupIdx,
									g_lpMsg,
									10),
							   "DupIndex");

			// close registry key
			if(lpRegKey->Close()==ERROR_SUCCESS)
				RemoveWinResource
		}

		UnlockGlobalMsg()

		// relese key interface
		FreeClassObject(lpRegKey);
	}
	
	// check next saver
	if(lpNextSaver)
	{
		// save next saver
		lpNextSaver->SaveDuplicateIDs();
	}
}

// GetNextDuplicateSaverID()

DWORD GetNextDuplicateSaverID(LPSTR lpTitle)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpTitle)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetNextDuplicateSaverID()",
							FALSE);
		return(0);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey;

	// reset index value
	DWORD dwIndex=0;
	
	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(0);

	LockGlobalMsg()

	// create registry key
	strcpy(g_lpMsg,
		   ApplicationRegistryPath());
	strcat(g_lpMsg,
		   "DupIDs\\");

	// create registry key
	if(lpRegKey->Create(HKEY_CURRENT_USER,
						g_lpMsg,
						REG_NONE,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS,
						NULL,
						NULL)==ERROR_SUCCESS)
	{
		AddWinResource

		// check for value
		if(lpRegKey->QueryValue(dwIndex,
								lpTitle)==ERROR_SUCCESS)
		{
			// increment index
			dwIndex++;
		}
		else
		{
			// set default index
			dwIndex=1;
		}

		// save new value
		lpRegKey->SetValue(dwIndex,
						   lpTitle);

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}

	UnlockGlobalMsg()

	// relese key interface
	FreeClassObject(lpRegKey);
	
	// ok
	return(dwIndex);
}

// CSaverList::OnSetFocus()

void CSaverList::OnSetFocus(CWnd* pOldWnd)
{
	// call base method
	CListCtrl::OnSetFocus(pOldWnd);
}

// CSaverPlaylist::OnSetFocus()

void CSaverPlaylist::OnSetFocus(CWnd* pOldWnd)
{
	// call base method
	CPlaylistCtrl::OnSetFocus(pOldWnd);
}

// CSaverList::OnItemChanged()

void CSaverList::OnItemChanged(NMHDR* pNMHDR,
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

	// check playlist
	if(g_lpSaverPlaylist)
	{
		// check window
		if(IsWindow(g_lpSaverPlaylist->m_hWnd))
		{
			// check selection
			if(g_lpSaverPlaylist->QuerySelection())
			{
				// get selection
				nSel=g_lpSaverPlaylist->GetSelection();

				// get playlist data
				if(g_lpSaverPlaylist->GetPlaylistItemData(nSel,
														  &lpPD))
				{
					// compare item data
					if(lpPD->lpUserData==(LPVOID)GetItemData(lpLV->iItem))
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
			g_lpSaverPlaylist->SetItemState(nSel,
											NULL,
											LVIS_SELECTED);
		}

		// save as current
		SetCurrentSaver((CSaverInfo*)GetItemData(lpLV->iItem));

		// enable buttons
		g_lpClearSelBtn->Enable();
		g_lpAddSaverBtn->Enable();

		// update saver info
		UpdateSaverInfoBox(g_lpCurSaver);

		// redraw item
		RedrawItems(lpLV->iItem,
					lpLV->iItem);

		// update window
		UpdateWindow();

		// play sound (unless focus swapping)
		if(g_nFSwapId==0)
			PlaySound(IDR_NEWSELSND);
	}
	
	// cleared selection
	if(!(lpLV->uNewState&LVIS_SELECTED)&&
	   lpLV->uOldState&LVIS_SELECTED)
	{
		// check equal flag
		if(bItemsAreEqual)
		{
			// clear playlist selection
			g_lpSaverPlaylist->SetItemState(nSel,
											NULL,
											LVIS_SELECTED);
		}

		// clear current saver
		SetCurrentSaver(NULL);

		// disable buttons
		g_lpAddSaverBtn->Disable();
		g_lpClearSelBtn->Disable();

		// update saver info
		UpdateSaverInfoBox(NULL);

		// redraw item
		RedrawItems(lpLV->iItem,
					lpLV->iItem);

		// update window
		UpdateWindow();
	}

	// set return value
	(*pResult)=NULL;
}

// CSaverPlaylist::OnItemChanged()

void CSaverPlaylist::OnItemChanged(NMHDR* pNMHDR,
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

	// get item data
	if(GetPlaylistItemData(lpLV->iItem,
						   &lpPD))
	{
		// check saver list
		if(g_lpSaverList)
		{
			// check window
			if(IsWindow(g_lpSaverList->m_hWnd))
			{
				// check selection
				if(g_lpSaverList->QuerySelection())
				{
					// get selection
					nSel=g_lpSaverList->GetSelection();

					// compare item data
					if(g_lpSaverList->GetItemData(nSel)==(DWORD)lpPD->lpUserData)
						bItemsAreEqual=TRUE;
					else
						bItemsAreEqual=FALSE;
				}
			}
		}
	}
	else
	{
		// clear item data
		lpPD=NULL;
	}

	// new selection
	if(lpLV->uNewState&LVIS_SELECTED&&
	   !(lpLV->uOldState&LVIS_SELECTED))
	{
		// check item data
		if(lpPD)
		{
			// check equal flag
			if(!bItemsAreEqual)
			{
				// clear saver list selection
				g_lpSaverList->SetItemState(nSel,
											NULL,
											LVIS_SELECTED);
			}

			// set as current
			SetCurrentSaver((CSaverInfo*)lpPD->lpUserData);
		}
		else
		{
			// clear current saver
			SetCurrentSaver(NULL);
		}

		// update saver info
		UpdateSaverInfoBox(g_lpCurSaver);
	}
	
	// cleared selection
	if(!(lpLV->uNewState&LVIS_SELECTED)&&
	   lpLV->uOldState&LVIS_SELECTED)
	{
		// check moving flag
		if(!bMoving)
		{
			// check equal flag
			if(bItemsAreEqual)
			{
				// clear saver list selection
				g_lpSaverList->SetItemState(nSel,
											NULL,
											LVIS_SELECTED);
			}

			// clear current saver
			SetCurrentSaver(NULL);

			// update saver info
			UpdateSaverInfoBox(g_lpCurSaver);
		}
	}

	// call base method
	CPlaylistCtrl::OnItemChanged(pNMHDR,
								 pResult);
}

// CSaverPreviewWnd::SetScreenBitmap()

void CSaverPreviewWnd::SetScreenBitmap(CBitmap* lpBmp)
{
#ifdef DEBUG_MODE
	// verify bitmap
	if(!lpBmp)
	{
		DisplayErrorMessage("Invalid bitmap pointer.",
							"CSaverPreviewWnd::SetScreenBitmap()",
							FALSE);
		return;
	}
#endif

	// copy pointer
	lpScrnBmp=lpBmp;
}

// CSaverPreviewWnd::DrawBitmap()

void CSaverPreviewWnd::DrawBitmap(LPPAINTSTRUCT lpPS)
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
	if(!lpScrnBmp)
		return;

	// check flag
	if(!bScrnUp)
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
		goto CSaverPreviewWnd_DrawBitmap1;

	// save state
	nDestState=lpDestDC->SaveDC();

	// create source dc
	AllocClassObject(lpSrcDC,
					 CDC);
	
	// check for error
	if(!lpSrcDC)
		goto CSaverPreviewWnd_DrawBitmap1;

	// create compatible dc
	if(!lpSrcDC->CreateCompatibleDC(lpDestDC))
		goto CSaverPreviewWnd_DrawBitmap1;
	else
		AddWinResource

	// select bitmap
	lpGdiObj=lpSrcDC->SelectObject(lpScrnBmp);

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
CSaverPreviewWnd_DrawBitmap1:;

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

// OnScrnUpTimerProc()

void CALLBACK OnScrnUpTimerProc(HWND hWnd,
								UINT uMsg,
								UINT idEvent,
								DWORD dwTime)
{
	// kill timer
	::KillTimer(NULL,
				g_nScrnUpTimerId);

	// reset id
	g_nScrnUpTimerId=NULL;

	// set flag
	g_lpSaverPrevWnd->bScrnUp=TRUE;

	// redraw screen
	g_lpSaverPrevWnd->RedrawWindow();
}

// CSaverInfoDlg::OnShowWindow()

void CSaverInfoDlg::OnShowWindow(BOOL bShow,
							     UINT nStatus)
{
	// window rect
	CRect rWnd;
	
	// check show flag
	if(bShow)
	{
		// check shown flag
		if(!bWinShown)
		{
			// get dialog rect
			g_lpSaverInfoDlg->GetWindowRect(&rWnd);

			// offset to better position
			rWnd.OffsetRect(SIDLG_OFFSET);

			// set new position
			g_lpSaverInfoDlg->MoveWindow(&rWnd);

			// post init message
			PostCommand(g_lpMainSheet,
						IDM_SINFO_INIT);
			
			// set flag
			bWinShown=TRUE;
		}
	}

	// call base method
	CExtDialog::OnShowWindow(bShow,
							 nStatus);
}

// InitSaverHookProc()

BOOL InitSaverHookProc(void)
{
	LockGlobalErrorMsg()

	// copy install path
	strcpy(g_lpErrorMsg,
		   g_lpInstPath);

	// add library name
	strcat(g_lpErrorMsg,
		   "\\svrhook.dll");

	// load library
	g_hSvrHookDll=LoadLibrary(g_lpErrorMsg);

	// check for error
	if(g_hSvrHookDll==NULL)
	{
		DisplayErrorMessage("Unable to load library 'svrhook.dll'");
		UnlockGlobalErrorMsg()
		return(FALSE);
	}
	else
		AddWinResource

	UnlockGlobalErrorMsg()

	// get function address
	CreateSaverHook=(CREATESAVERHOOK)GetProcAddress(g_hSvrHookDll,
													(LPCSTR)1);

	// check for error
	if(CreateSaverHook==NULL)
	{
		DisplayErrorMessage("Unable to load function from library 'svrhook.dll'");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// ReleaseSaverHookProc()

void ReleaseSaverHookProc(void)
{
	// reset function pointer
	CreateSaverHook=NULL;

	// release dll
	if(FreeLibrary(g_hSvrHookDll))
		RemoveWinResource
}

// CSaverInfoDlg::OnWmHelp()

LRESULT CSaverInfoDlg::OnWmHelp(WPARAM wParam,
								LPARAM lParam)
{
	// show help
	ShowHelp(IDC_EDITSAVERDLG,
			 NULL);

	// ok
	return(TRUE);
}

// CEditThemesDlg::OnWmHelp()

LRESULT CEditThemesDlg::OnWmHelp(WPARAM wParam,
								 LPARAM lParam)
{
	// show help
	ShowHelp(IDC_EDITTHEMESDLG,
			 NULL);

	// ok
	return(TRUE);
}

// GetNextSaverString()

BOOL GetNextSaverString(LPSTR lpStr,
						int* lpnCurId,
						BOOL bCountOnly)
{
#ifdef DEBUG_MODE
	// check flag
	if(bCountOnly)
	{
		// verify pointer
		if(!lpnCurId)
		{
			DisplayErrorMessage("Invalid pointer value.",
								"GetNextSaverString()",
								FALSE);
			return(FALSE);
		}
	}
	else
	{
		// verify string
		if(!lpStr)
		{
			DisplayErrorMessage("Invalid string value.",
								"GetNextSaverString()",
								FALSE);
			return(FALSE);
		}
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// buffer length
	DWORD dwLen;

	// set continue flag
	BOOL bCont=TRUE;

	// reset counter
	int nCount=0;

	// get next saver
	int nCur=LoadOptionInt("Savers_NextPlay",
						   0,
						   -1,
						   0);

	// set return id
	if(lpnCurId)
		(*lpnCurId)=nCur;

	// clear string
	if(!bCountOnly)
		lpStr[0]=0;

	// get key interface
	AllocClassObject(lpRegKey,
					 CRegKey);

	// check new object
	if(!lpRegKey)
		return(FALSE);

	LockGlobalMsg()

	// create registry key
	strcpy(g_lpMsg,
		   ApplicationRegistryPath());
	strcat(g_lpMsg,
		   "CurrPList");

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
							// check count-only
							if(!bCountOnly)
							{
								// compare ids
								if(nCount==nCur)
								{
									// we have a winner!
									strcpy(lpStr,
										   g_lpLongMsg);

									// stop here
									bCont=FALSE;
								}
							}

							UnlockGlobalLongMsg()
						}
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

	// check count-only
	if(bCountOnly)
	{
		// set return value
		(*lpnCurId)=nCount-1;

		// ok
		return(TRUE);
	}
	else
	{
		// check for string
		if(strlen(lpStr)==0)
		{
			// check current id
			if(nCur==0)
			{
				// no savers
				return(FALSE);
			}
			else
			{
				// clear index
				SaveOptionInt("Savers_NextPlay",
							  0);

				// try again
				return(GetNextSaverString(lpStr,
										  lpnCurId,
										  bCountOnly));
			}
		}
		else
		{
			// set next index
			SaveOptionInt("Savers_NextPlay",
						  nCur+1);

			// ok
			return(TRUE);
		}
	}
}

// eof //

// Copyright 2006 WaveBreak Software

