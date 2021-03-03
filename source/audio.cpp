// Copyright 2006 WaveBreak Software

// audio.cpp -- audio settings functions

// includes //

#include"main.h"

// message maps //

BEGIN_MESSAGE_MAP(CChangeMusicDlg,CExtDialog)
	ON_BN_CLICKED(IDC_LOADAUDFILEBTN,OnLoadAudioFileBtnClk)
	ON_BN_CLICKED(IDC_LOADPLISTBTN,  OnLoadAudioPlaylistBtnClk)
	ON_BN_CLICKED(IDC_CLEARMUSBTN,   OnClearAudioFileBtnClk)
	ON_BN_CLICKED(IDC_EDITAUDIOBTN,  OnOpenMusicManagerBtnClk)
	ON_BN_CLICKED(IDC_CHGMUSHELPBTN, OnChangeAudioHelpBtnClk)
	ON_MESSAGE(WM_HELP,OnWmHelp)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CMusicManagerDlg,CExtDialog)
	ON_BN_CLICKED(IDC_FILEBACKBTN,        OnBackBtnClk)
	ON_BN_CLICKED(IDC_FILEUPBTN,          OnUpBtnClk)
	ON_BN_CLICKED(IDC_CLEARAUDIOSELBTN,   OnClearSelBtnClk)
	ON_BN_CLICKED(IDC_ADDAUDIOFILEBTN,    OnAddFileBtnClk)
	ON_BN_CLICKED(IDC_PLAYBTN,            OnPlayBtnClk)
	ON_BN_CLICKED(IDC_PAUSEBTN,           OnPauseBtnClk)
	ON_BN_CLICKED(IDC_STOPBTN,            OnStopBtnClk)
	ON_BN_CLICKED(IDC_FULLREWBTN,         OnFullRewBtnClk)
	ON_BN_CLICKED(IDC_REWBTN,             OnRewBtnClk)
	ON_BN_CLICKED(IDC_FWDBTN,             OnFwdBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTUPBTN,    OnPListUpBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTTOPBTN,   OnPListTopBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTDOWNBTN,  OnPListDownBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTBOTTOMBTN,OnPListBottomBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTDELBTN,   OnPListDeleteBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTCLRBTN,   OnPListClearBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTSAVEBTN,  OnPListSaveBtnClk)
	ON_BN_CLICKED(IDC_AUDIOPLISTLOADBTN,  OnPListLoadBtnClk)
	ON_BN_CLICKED(IDC_ENABLEPBCCHK,       OnEnablePBCChkClk)
	ON_BN_CLICKED(IDC_WINSYNTHRAD,        OnWinSynthRadClk)
	ON_BN_CLICKED(IDC_DXSYNTHRAD,         OnDXSynthRadClk)
	ON_BN_CLICKED(IDC_REVERBCHK,          OnReverbChkClk)
	ON_BN_CLICKED(IDC_CHORUSCHK,          OnChorusChkClk)
	ON_BN_CLICKED(IDC_MUSMANHELPBTN,      OnHelpBtnClk)
	ON_BN_CLICKED(IDC_INSTALLDXBTN,       OnInstallDXBtnClk)
	ON_MESSAGE(WM_HELP,OnWmHelp)
	ON_WM_CONTEXTMENU()
	ON_WM_HSCROLL()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAudioPlaylist,CPlaylistCtrl)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED,OnItemChanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK,      OnDblClick)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAudioExtComboBox,CExtComboBox)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAudioPosSlider,CExtSliderCtrl)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAudioInfoBox,CExtRichEditCtrl)
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CAudioSortBox,CExtComboBox)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// globals //

// audio-init flag
BOOL g_bAudioInit=FALSE;
// change-music dialog
CChangeMusicDlg* g_lpChangeMusicDlg=NULL;
// change music buttons
CExtButton* g_lpLoadAudioFileBtn=NULL;
CExtButton* g_lpLoadAudioPlaylistBtn=NULL;
CExtButton* g_lpClearAudioFileBtn=NULL;
CExtButton* g_lpOpenMusicManagerBtn=NULL;
CExtButton* g_lpChangeAudioHelpBtn=NULL;
// current music manager
CMusicManagerDlg* g_lpCurMusicMgrDlg=NULL;
// music dialog history box
CHistoryComboBox* g_lpAudioHistoryCbx=NULL;
// folder controls
CFolderCtrlButton* g_lpFileBackBtn=NULL;
CFolderCtrlButton* g_lpFileUpBtn=NULL;
// music dialog buttons
CExtButton* g_lpClearAudioSelBtn=NULL;
CExtButton* g_lpAddAudioFileBtn=NULL;
CExtButton* g_lpAudioPListUpBtn=NULL;
CExtButton* g_lpAudioPListTopBtn=NULL;
CExtButton* g_lpAudioPListDownBtn=NULL;
CExtButton* g_lpAudioPListBottomBtn=NULL;
CExtButton* g_lpAudioPListDelBtn=NULL;
CExtButton* g_lpAudioPListClearBtn=NULL;
CExtButton* g_lpAudioPListSaveBtn=NULL;
CExtButton* g_lpAudioPListLoadBtn=NULL;
CExtButton* g_lpPlayBtn=NULL;
CExtButton* g_lpPauseBtn=NULL;
CExtButton* g_lpStopBtn=NULL;
CExtButton* g_lpFullRewBtn=NULL;
CExtButton* g_lpRewBtn=NULL;
CExtButton* g_lpFwdBtn=NULL;
CExtButton* g_lpMusicMgrHelpBtn=NULL;
CExtButton* g_lpInstallDXBtn=NULL;
// music dialog file list
CFileListCtrl* g_lpAudioFileList=NULL;
// music dialog combo boxes
CAudioExtComboBox* g_lpFileTypeCbx=NULL;
CAudioSortBox* g_lpAudioPListSortCbx=NULL;
// music dialog audio playlist
CAudioPlaylist* g_lpAudioPList=NULL;
// music dialog file info
CAudioInfoBox* g_lpAudioInfoBox=NULL;
// music dialog static controls
CExtStatic* g_lpAudioPosTxt=NULL;
CExtStatic* g_lpNextHkyTxt=NULL;
CExtStatic* g_lpVolUpHkyTxt=NULL;
CExtStatic* g_lpVolDownHkyTxt=NULL;
CExtStatic* g_lpMuteHkyTxt=NULL;
CExtStatic* g_lpDXFXTxt=NULL;
// music dialog position indicator
CAudioPosSlider* g_lpAudioPosSld=NULL;
// music dialog checkboxes
CExtButton* g_lpEnablePBCChk=NULL;
CExtButton* g_lpReverbChk=NULL;
CExtButton* g_lpChorusChk=NULL;
// music dialog hotkey controls
CExtHotKeyCtrl* g_lpNextHky=NULL;
CExtHotKeyCtrl* g_lpVolUpHky=NULL;
CExtHotKeyCtrl* g_lpVolDownHky=NULL;
CExtHotKeyCtrl* g_lpMuteHky=NULL;
// music dialog radio buttons
CExtButton* g_lpWinSynthRad=NULL;
CExtButton* g_lpDXSynthRad=NULL;
// tooltip control
CToolTipCtrl* g_lpMusicMgrToolTip=NULL;
// music manager hide windows
CWnd* g_lpMMWndToHide1=NULL;
CWnd* g_lpMMWndToHide2=NULL;
// music manager window rects
CRect g_rMMWnd1,g_rMMWnd2;
CRect g_rMMInv1,g_rMMInv2;
// extension groups
CExtensionGroup* g_lpAudioExtGrp=NULL;
CExtensionGroup* g_lpPListExtGrp=NULL;
// current audio extension list
CExtensionList* g_lpCurAudExtList=NULL;
// audio playback window
HWND g_hMCIWnd=(HWND)INVALID_HANDLE_VALUE;
// current audio info
LPFILELISTDATA g_lpCurAudioFLD=NULL;
UINT g_nCurAudioDevID=NULL;
// current audio timer info
UINT g_nCurAudioTimerID=NULL;
// audio pause flag
BOOL g_bAudioPause=FALSE;
// audio position update flag
BOOL g_bNoAudioPosUpdate=FALSE;
// mp3 flag
BOOL g_bCurAudioIsMP3=FALSE;
// playlist file info
LPFILELISTDATA* g_lplpAPListFileData=NULL;
DWORD g_dwNumAPListFileData=0;
// previous popup info flag
BOOL g_bShowPListPopupPrev=FALSE;
// audio hotkey flag
BOOL g_bEnableAudioHotkeys=FALSE;
// audio hotkey values
DWORD g_dwNextHky=NULL;
DWORD g_dwVolUpHky=NULL;
DWORD g_dwVolDownHky=NULL;
DWORD g_dwMuteHky=NULL;
// synthesizer flags
BOOL g_bDXSynthOK=FALSE;
BOOL g_bUseDXSynth=FALSE;
BOOL g_bUseDXReverb=FALSE;
BOOL g_bUseDXChorus=FALSE;
// last-saved playlist
LPSTR g_lpLastSavedPList=NULL;
// audio temp file
LPSTR g_lpAudioTempFile=NULL;
// master volume settings
DWORD g_dwSavedVolume=0;
BOOL g_bVolumeSaved=FALSE;

// functions //

// ValidateMusicFile()

BOOL ValidateMusicFile(LPSTR* lplpMusic)
{
#ifdef DEBUG_MODE
	// check pointer
	if(!lplpMusic)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ValidateMusicFile()",
							FALSE);
		return(FALSE);
	}
#endif

	// check for filename
	if(*lplpMusic)
	{
		// verify music file
		if(IsValidMusicFile(*lplpMusic))
			return(TRUE);

		// delete invalid file
		FreeMem((LPVOID*)lplpMusic);
	}

	// ok
	return(TRUE);
}

// BrowseMusicFiles()

BOOL BrowseMusicFiles(void)
{
	// verify dialog
	if(!g_lpChangeMusicDlg)
		return(FALSE);

	// run dialog
	g_lpChangeMusicDlg->DoModal();

	// ok
	return(TRUE);
}

// CChangeMusicDlg::InitDialog()

BOOL CChangeMusicDlg::InitDialog(void)
{
	// capture single-file button
	if(!CaptureDlgControl(this,
						  g_lpLoadAudioFileBtn,
						  IDC_LOADAUDFILEBTN))
		return(FALSE);

	// capture playlist button
	if(!CaptureDlgControl(this,
						  g_lpLoadAudioPlaylistBtn,
						  IDC_LOADPLISTBTN))
		return(FALSE);

	// capture clear button
	if(!CaptureDlgControl(this,
						  g_lpClearAudioFileBtn,
						  IDC_CLEARMUSBTN))
		return(FALSE);

	// capture manager button
	if(!CaptureDlgControl(this,
						  g_lpOpenMusicManagerBtn,
						  IDC_EDITAUDIOBTN))
		return(FALSE);

	// capture help button
	if(!CaptureDlgControl(this,
						  g_lpChangeAudioHelpBtn,
						  IDC_CHGMUSHELPBTN))
		return(FALSE);

	// check current selection
	if(!g_lpSaverInfoDlg->lpMusicPath)
	{
		// disable clear button
		g_lpClearAudioFileBtn->Disable();
	}	

	// ok
	return(TRUE);
}

// CChangeMusicDlg::ReleaseDialog()

void CChangeMusicDlg::ReleaseDialog(void)
{
	// no release req'd
}

// CChangeMusicDlg::OnClearAudioFileBtnClk()

void CChangeMusicDlg::OnClearAudioFileBtnClk(void)
{
	// clear selection
	if(g_lpSaverInfoDlg->ClearMusicSel())
	{
		// end dialog
		if(IsWindow(m_hWnd))
			OnCancel();
	}
}

// CChangeMusicDlg::OnChangeAudioHelpBtnClk()

void CChangeMusicDlg::OnChangeAudioHelpBtnClk(void)
{
	// show help file
	ShowHelp(IDC_CHGMUSICDLG,
			 NULL);
}

// CChangeMusicDlg::OnContextMenu()

void CChangeMusicDlg::OnContextMenu(CWnd* pWnd,
									CPoint pos)
{
	// check for clear button
	if(IsPointInWindow(&pos,
					   g_lpClearAudioFileBtn))
		g_lpClearAudioFileBtn->OnContextMenu(pWnd,
											 pos);
}

// CChangeMusicDlg::OnLoadAudioFileBtnClk()

void CChangeMusicDlg::OnLoadAudioFileBtnClk(void)
{
	// load file
	LoadAudioFile(AFT_AUDIO);
}

// CChangeMusicDlg::OnLoadAudioPlaylistBtnClk()
	
void CChangeMusicDlg::OnLoadAudioPlaylistBtnClk(void)
{
	// load file
	LoadAudioFile(AFT_PLIST);
}

// CChangeMusicDlg::LoadAudioFile()

void CChangeMusicDlg::LoadAudioFile(DWORD dwType)
{
	// dialog strings
	LPSTR  lpFilterList =NULL;
	LPCSTR lpCaption    =NULL;
	LPCSTR lpStartDirReg=NULL;

	// check file type
	if(dwType==AFT_AUDIO)
	{
		// set strings
		lpFilterList =GetAudioFileFilterList();
		lpCaption    ="Load Single Audio File";
		lpStartDirReg="Path_AudioFile";
	}
	else
	{
		// set strings
		lpFilterList =GetPlaylistFilterList();
		lpCaption    ="Load ProSaver Audio Playlist";
		lpStartDirReg="Path_AudioPList";
	}

	// set start dir flag
	BOOL bUseStartDir=TRUE;

	// check for music path
	if(g_lpSaverInfoDlg->lpMusicPath)
	{
		LockGlobalTTMsg()
		
		// copy string
		strcpy(g_lpTTMsg,
			   g_lpSaverInfoDlg->lpMusicPath);

		// check type
		if(dwType==AFT_AUDIO)
		{
			// check for existing playlist
			if(IsValidMusicFile(g_lpSaverInfoDlg->lpMusicPath))
				if(!IsValidPlaylist(g_lpSaverInfoDlg->lpMusicPath))
				{
					// reset start dir flag
					bUseStartDir=FALSE;
				}
		}
		else
		{
			// check for existing playlist
			if(IsValidMusicFile(g_lpSaverInfoDlg->lpMusicPath))
				if(IsValidPlaylist(g_lpSaverInfoDlg->lpMusicPath))
				{
					// reset start dir flag
					bUseStartDir=FALSE;
				}
		}

		UnlockGlobalTTMsg()
	}

	LockGlobalLongMsg()
	LockGlobalTTMsg()

	// copy string
	strcpy(g_lpLongMsg,
		   g_lpTTMsg);

	// check start dir flag
	if(bUseStartDir)
	{
		// check registry path
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
			else
			{
				// set flag
				bUseStartDir=TRUE;
			}
		}
		else
		{
			// reset text
			strcpy(g_lpLongMsg,
				   NULL_STRING);
		}
	}

	UnlockGlobalTTMsg()
	LockGlobalMsg()

	// copy path
	strcpy(g_lpMsg,
		   g_lpLongMsg);

	UnlockGlobalLongMsg()

	// set callback
	g_lpFileOpenDlg->SetCheckFileCallback(CheckAudioFileCallback);

	// configure dialog box
	g_lpFileOpenDlg->m_ofn.lStructSize =sizeof(OPENFILENAME);
	g_lpFileOpenDlg->m_ofn.hwndOwner   =m_hWnd;
	g_lpFileOpenDlg->m_ofn.lpstrFilter =lpFilterList;
	g_lpFileOpenDlg->m_ofn.nFilterIndex=1;
	g_lpFileOpenDlg->m_ofn.lpstrFile   =g_lpMsg;
	g_lpFileOpenDlg->m_ofn.nMaxFile    =_MAX_PATH-1;
	g_lpFileOpenDlg->m_ofn.lpstrTitle  =lpCaption;
	g_lpFileOpenDlg->m_ofn.Flags       |=OFN_OVERWRITEPROMPT;

	// check start dir flag
	if(!bUseStartDir)
	{
		// reset value
		g_lpFileOpenDlg->m_ofn.lpstrInitialDir=NULL;
	}
	else
	{
		LockGlobalTTMsg()

		// copy path
		strcpy(g_lpTTMsg,
			   g_lpMsg);

		// clear filename
		strcpy(g_lpMsg,
			   NULL_STRING);

		// set start dir
		g_lpFileOpenDlg->m_ofn.lpstrInitialDir=g_lpTTMsg;
		
		UnlockGlobalTTMsg()
	}

	// clear remaining items
	g_lpFileOpenDlg->m_ofn.hInstance        =NULL;
	g_lpFileOpenDlg->m_ofn.lpstrCustomFilter=NULL;
	g_lpFileOpenDlg->m_ofn.nMaxCustFilter   =0;
	g_lpFileOpenDlg->m_ofn.lpstrFileTitle   =NULL;
	g_lpFileOpenDlg->m_ofn.nMaxFileTitle    =0;
	g_lpFileOpenDlg->m_ofn.nFileOffset      =0;
	g_lpFileOpenDlg->m_ofn.nFileExtension   =0;
	g_lpFileOpenDlg->m_ofn.lpstrDefExt      =NULL;
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

		// update audio
		UpdateAudio(g_lpMsg);

		// close dialog
		if(IsWindow(m_hWnd))
			OnCancel();
	}

	UnlockGlobalMsg()
}

// CChangeMusicDlg::UpdateAudio()

void CChangeMusicDlg::UpdateAudio(LPSTR lpFile)
{
	// release old path
	FreeMem((LPVOID*)&g_lpSaverInfoDlg->lpMusicPath);

	// allocate new path
	if(AllocMem((LPVOID*)&g_lpSaverInfoDlg->lpMusicPath,
				strlen(lpFile)+1))
	{
		// copy path
		strcpy(g_lpSaverInfoDlg->lpMusicPath,
			   lpFile);

		// check no-music flag
		if(g_bPlaybackPageInitOK)
		{
			if(g_lpNoMusicChk->GetCheck()==1)
				DisplayInfoMessage(NO_MUSIC_MSG);
		}
		else if(g_bNoMusic)
			DisplayInfoMessage(NO_MUSIC_MSG);

		// check for playlist
		if(IsValidPlaylist(lpFile))
		{
			// enable buttons
			g_lpMusicCycleRad->Enable();
			g_lpMusicShuffleRad->Enable();

			// set check
			g_lpSaverInfoDlg->SetMusicCycleRad();
		}
		else
		{
			// uncheck radio buttons
			g_lpMusicCycleRad->SetCheck(0);
			g_lpMusicShuffleRad->SetCheck(0);

			// disable buttons
			g_lpMusicCycleRad->Disable();
			g_lpMusicShuffleRad->Disable();
		}

		// get filename
		GetFilenameFromPath(lpFile,
							_MAX_PATH-1,
							g_lpSaverInfoDlg->lpMusicPath);

		// set as current file
		g_lpMusicSelBox->SetWindowText(lpFile);
	}
	else
	{
		// set to none
		g_lpMusicSelBox->SetWindowText(NO_SEL_TEXT);

		// uncheck radio buttons
		g_lpMusicCycleRad->SetCheck(0);
		g_lpMusicShuffleRad->SetCheck(0);

		// disable buttons
		g_lpMusicCycleRad->Disable();
		g_lpMusicShuffleRad->Disable();
	}

	// set parent modified
	g_lpSaverInfoDlg->SetModified();
}

// CheckAudioFileCallback()

BOOL CheckAudioFileCallback(void)
{
	// substring
	LPSTR lpSubStr;

	// check audio file
	if(!IsValidMusicFile(g_lpMsg))
	{
		LockGlobalTTMsg()

		// begin message
		strcpy(g_lpTTMsg,"The file you have selected is not ");

		// add text as needed
		if(strlen(g_lpMsg)<3)
			strcat(g_lpTTMsg,"valid");
		else
		{
			// set substring pointer
			lpSubStr=&g_lpMsg[strlen(g_lpMsg)-3];

			// check for playlist
			if((stricmp(lpSubStr,"apl")==0)||
			   (stricmp(lpSubStr,"spl")==0))
				strcat(g_lpTTMsg,"a valid ProSaver audio playlist");
			else
				strcat(g_lpTTMsg,"in a valid audio format");
		}

		// complete message
		strcat(g_lpTTMsg,
			   ".\n\nPlease select another file.");

		// alert user
		DisplayInfoMessage(g_lpTTMsg);

		UnlockGlobalTTMsg()

		// try again
		return(TRUE);
	}

	// file is ok
	return(FALSE);
}

// CChangeMusicDlg::OnOpenMusicManagerBtnClk()

void CChangeMusicDlg::OnOpenMusicManagerBtnClk(void)
{
	// change-music flag
	BOOL bChgMus;

	// check for change-music dialog
	if(IsWindow(g_lpChangeMusicDlg->m_hWnd))
	{
		// set flag
		bChgMus=TRUE;

		// close dialog
		g_lpChangeMusicDlg->OnCancel();
	}
	else
	{
		// clear flag
		bChgMus=FALSE;
	}

	// allocate memory for last-saved list
	if(!AllocMem((LPVOID*)&g_lpLastSavedPList,
				 _MAX_PATH+1))
		ForceImmediateExit();

	// clear path
	g_lpLastSavedPList[0]=0;

	// show music manager
	ShowMusicManager(g_lpMusicManagerDlgB,
					 g_lpSaverInfoDlg,
					 g_lpMainSheet);

	// check last-saved list
	if(strlen(g_lpLastSavedPList))
	{
		LockGlobalMsg()

		// get filename
		if(GetFilenameFromPath(g_lpMsg,
							   _MAX_PATH,
							   g_lpLastSavedPList))
		{
			LockGlobalLongMsg()

			// prepare message
			sprintf(g_lpLongMsg,
					"The last playlist you saved was '%s'.\n\nWould you like to assign this playlist to the current screensaver?",
					g_lpMsg);

			// query user
			if(DisplayMessageBox(g_lpMainSheet->m_hWnd,
								 g_lpLongMsg,
								 (LPSTR)ApplicationName(),
								 MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				UnlockGlobalLongMsg()

				// update audio
				UpdateAudio(g_lpLastSavedPList);

				// clear change-music flag
				bChgMus=FALSE;
			}
			else
				UnlockGlobalLongMsg()
		}
		
		UnlockGlobalMsg()
	}

	// free last-saved list
	FreeMem((LPVOID*)&g_lpLastSavedPList);
	
	// check change-music flag
	if(bChgMus)
	{
		// re-display dialog
		PostCommand(g_lpMainSheet,
					IDM_BROWSEMUSIC);
	}
}

// ShowMusicManager()

void ShowMusicManager(CMusicManagerDlg* lpMusicManager,
					  CWnd* lpWndToHide1,
					  CWnd* lpWndToHide2)
{
	// save hide windows
	g_lpMMWndToHide1=lpWndToHide1;
	g_lpMMWndToHide2=lpWndToHide2;

	// check for dialog
	if(lpMusicManager)
	{
		// set current dialog
		g_lpCurMusicMgrDlg=lpMusicManager;

		// run dialog
		lpMusicManager->DoModal();

		// clear current dialog
		g_lpCurMusicMgrDlg=NULL;
	}
#ifdef DEBUG_MODE
	else
	{
		DisplayErrorMessage("Invalid pointer value.",
							"ShowMusicManager()",
							FALSE);
	}
#endif

	// clear hide windows
	g_lpMMWndToHide1=NULL;
	g_lpMMWndToHide2=NULL;
}

// CreateMusicManagerDlg()

CMusicManagerDlg* CreateMusicManagerDlg(CWnd* lpParent)
{
#ifdef DEBUG_MODE
	// verify pointer
	if(!lpParent)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"CreateMusicManagerDlg()",
							FALSE);
		return(NULL);
	}
#endif

	// return value
	CMusicManagerDlg* lpMM=NULL;

	// allocate music manager
	AllocClassObject(lpMM,
					 CMusicManagerDlg(IDD_MUSICMGR,
									  lpParent));

	// ok
	return(lpMM);
}

// CMusicManagerDlg::OnContextMenu()

void CMusicManagerDlg::OnContextMenu(CWnd* pWnd,
									 CPoint pos)
{
	// check for file back button
	if(IsPointInWindow(&pos,
					   g_lpFileBackBtn))
		g_lpFileBackBtn->OnContextMenu(pWnd,
									   pos);

	// check for file up button
	if(IsPointInWindow(&pos,
					   g_lpFileUpBtn))
		g_lpFileUpBtn->OnContextMenu(pWnd,
									 pos);

	// check for clear audio selection button
	if(IsPointInWindow(&pos,
					   g_lpClearAudioSelBtn))
		g_lpClearAudioSelBtn->OnContextMenu(pWnd,
											pos);

	// check for add audio file button
	if(IsPointInWindow(&pos,
					   g_lpAddAudioFileBtn))
		g_lpAddAudioFileBtn->OnContextMenu(pWnd,
										   pos);

	// check for audio playlist sort box
	if(IsPointInWindow(&pos,
					   g_lpAudioPListSortCbx))
		g_lpAudioPListSortCbx->OnContextMenu(pWnd,
											 pos);

	// check for audio playlist up button
	if(IsPointInWindow(&pos,
					   g_lpAudioPListUpBtn))
		g_lpAudioPListUpBtn->OnContextMenu(pWnd,
										   pos);

	// check for audio playlist top button
	if(IsPointInWindow(&pos,
					   g_lpAudioPListTopBtn))
		g_lpAudioPListTopBtn->OnContextMenu(pWnd,
											pos);

	// check for audio playlist down button
	if(IsPointInWindow(&pos,
					   g_lpAudioPListDownBtn))
		g_lpAudioPListDownBtn->OnContextMenu(pWnd,
											 pos);

	// check for audio playlist bottom button
	if(IsPointInWindow(&pos,
					   g_lpAudioPListBottomBtn))
		g_lpAudioPListBottomBtn->OnContextMenu(pWnd,
											   pos);

	// check for audio playlist delete button
	if(IsPointInWindow(&pos,
					   g_lpAudioPListDelBtn))
		g_lpAudioPListDelBtn->OnContextMenu(pWnd,
											pos);

	// check for audio playlist clear button
	if(IsPointInWindow(&pos,
					   g_lpAudioPListClearBtn))
		g_lpAudioPListClearBtn->OnContextMenu(pWnd,
											  pos);

	// check for audio playlist save button
	if(IsPointInWindow(&pos,
					   g_lpAudioPListSaveBtn))
		g_lpAudioPListSaveBtn->OnContextMenu(pWnd,
											 pos);

	// check for audio file info box
	if(IsPointInWindow(&pos,
					   g_lpAudioInfoBox))
		g_lpAudioInfoBox->OnContextMenu(pWnd,
										pos);

	// check for play button
	if(IsPointInWindow(&pos,
					   g_lpPlayBtn))
		g_lpPlayBtn->OnContextMenu(pWnd,
								   pos);

	// check for pause button
	if(IsPointInWindow(&pos,
					   g_lpPauseBtn))
		g_lpPauseBtn->OnContextMenu(pWnd,
									pos);

	// check for stop button
	if(IsPointInWindow(&pos,
					   g_lpStopBtn))
		g_lpStopBtn->OnContextMenu(pWnd,
								   pos);

	// check for full rewind button
	if(IsPointInWindow(&pos,
					   g_lpFullRewBtn))
		g_lpFullRewBtn->OnContextMenu(pWnd,
								      pos);

	// check for rewind button
	if(IsPointInWindow(&pos,
					   g_lpRewBtn))
		g_lpRewBtn->OnContextMenu(pWnd,
								  pos);

	// check for forward button
	if(IsPointInWindow(&pos,
					   g_lpFwdBtn))
		g_lpFwdBtn->OnContextMenu(pWnd,
								  pos);

	// check for audio position slider
	if(IsPointInWindow(&pos,
					   g_lpAudioPosSld))
		g_lpAudioPosSld->OnContextMenu(pWnd,
									   pos);

	// check for next hotkey
	if(IsPointInWindow(&pos,
					   g_lpNextHky))
		g_lpNextHky->OnContextMenu(pWnd,
								   pos);

	// check for volume up hotkey
	if(IsPointInWindow(&pos,
					   g_lpVolUpHky))
		g_lpVolUpHky->OnContextMenu(pWnd,
									pos);

	// check for volume down hotkey
	if(IsPointInWindow(&pos,
					   g_lpVolDownHky))
		g_lpVolDownHky->OnContextMenu(pWnd,
									  pos);

	// check for mute hotkey
	if(IsPointInWindow(&pos,
					   g_lpMuteHky))
		g_lpMuteHky->OnContextMenu(pWnd,
								   pos);

	// check for directx synth radio
	if(IsPointInWindow(&pos,
					   g_lpDXSynthRad))
		g_lpDXSynthRad->OnContextMenu(pWnd,
									  pos);

	// check for reverb checkbox
	if(IsPointInWindow(&pos,
					   g_lpReverbChk))
		g_lpReverbChk->OnContextMenu(pWnd,
									 pos);

	// check for chorus checkbox
	if(IsPointInWindow(&pos,
					   g_lpChorusChk))
		g_lpChorusChk->OnContextMenu(pWnd,
									 pos);

	// check for apply button
	if(IsPointInWindow(&pos,
					   g_lpSubApplyBtn))
		g_lpSubApplyBtn->OnContextMenu(pWnd,
									   pos);
}

// CMusicManagerDlg::OnCommand()

BOOL CMusicManagerDlg::OnCommand(WPARAM wParam,
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
		case(IDC_NEXTHKY):
		case(IDC_VOLUPHKY):
		case(IDC_VOLDNHKY):
		case(IDC_MUTEHKY):

			// reset duplicate flag
			bDup=FALSE;

			// get specific id
			switch(LOWORD(wParam))
			{
			// next hotkey
			case(IDC_NEXTHKY):

				// check for hotkey
				if(LOWORD(g_lpNextHky->GetHotKey()))
				{
					// compare with volume-up
					if(g_lpNextHky->GetHotKey()==g_lpVolUpHky->GetHotKey())
					{
						// set volume-up to none
						g_lpVolUpHky->SetHotKey(NULL,
												NULL);

						// set flash window
						lpFlashWnd=g_lpVolUpHky;

						// set flag
						bDup=TRUE;
					}

					// compare with volume-down
					if(g_lpNextHky->GetHotKey()==g_lpVolDownHky->GetHotKey())
					{
						// set volume-down to none
						g_lpVolDownHky->SetHotKey(NULL,
												  NULL);

						// set flash window
						lpFlashWnd=g_lpVolDownHky;

						// set flag
						bDup=TRUE;
					}

					// compare with mute
					if(g_lpNextHky->GetHotKey()==g_lpMuteHky->GetHotKey())
					{
						// set mute to none
						g_lpMuteHky->SetHotKey(NULL,
											   NULL);

						// set flash window
						lpFlashWnd=g_lpMuteHky;

						// set flag
						bDup=TRUE;
					}
				}

				// ok
				break;

			// volume-up hotkey
			case(IDC_VOLUPHKY):

				// check for hotkey
				if(LOWORD(g_lpVolUpHky->GetHotKey()))
				{
					// compare with next
					if(g_lpVolUpHky->GetHotKey()==g_lpNextHky->GetHotKey())
					{
						// set next to none
						g_lpNextHky->SetHotKey(NULL,
											   NULL);

						// set flash window
						lpFlashWnd=g_lpNextHky;

						// set flag
						bDup=TRUE;
					}

					// compare with volume-down
					if(g_lpVolUpHky->GetHotKey()==g_lpVolDownHky->GetHotKey())
					{
						// set volume-down to none
						g_lpVolDownHky->SetHotKey(NULL,
												  NULL);

						// set flash window
						lpFlashWnd=g_lpVolDownHky;

						// set flag
						bDup=TRUE;
					}

					// compare with mute
					if(g_lpVolUpHky->GetHotKey()==g_lpMuteHky->GetHotKey())
					{
						// set mute to none
						g_lpMuteHky->SetHotKey(NULL,
											   NULL);

						// set flash window
						lpFlashWnd=g_lpMuteHky;

						// set flag
						bDup=TRUE;
					}
				}

				// ok
				break;

			// volume-down hotkey
			case(IDC_VOLDNHKY):

				// check for hotkey
				if(LOWORD(g_lpVolDownHky->GetHotKey()))
				{
					// compare with next
					if(g_lpVolDownHky->GetHotKey()==g_lpNextHky->GetHotKey())
					{
						// set next to none
						g_lpNextHky->SetHotKey(NULL,
											   NULL);

						// set flash window
						lpFlashWnd=g_lpNextHky;

						// set flag
						bDup=TRUE;
					}

					// compare with volume-up
					if(g_lpVolDownHky->GetHotKey()==g_lpVolUpHky->GetHotKey())
					{
						// set volume-up to none
						g_lpVolUpHky->SetHotKey(NULL,
												NULL);

						// set flash window
						lpFlashWnd=g_lpVolUpHky;

						// set flag
						bDup=TRUE;
					}

					// compare with mute
					if(g_lpVolDownHky->GetHotKey()==g_lpMuteHky->GetHotKey())
					{
						// set mute to none
						g_lpMuteHky->SetHotKey(NULL,
											   NULL);

						// set flash window
						lpFlashWnd=g_lpMuteHky;

						// set flag
						bDup=TRUE;
					}
				}

				// ok
				break;

			// mute hotkey
			case(IDC_MUTEHKY):

				// check for hotkey
				if(LOWORD(g_lpMuteHky->GetHotKey()))
				{
					// compare with next
					if(g_lpMuteHky->GetHotKey()==g_lpNextHky->GetHotKey())
					{
						// set next to none
						g_lpNextHky->SetHotKey(NULL,
											   NULL);

						// set flash window
						lpFlashWnd=g_lpNextHky;

						// set flag
						bDup=TRUE;
					}

					// compare with volume-up
					if(g_lpMuteHky->GetHotKey()==g_lpVolUpHky->GetHotKey())
					{
						// set volume-up to none
						g_lpVolUpHky->SetHotKey(NULL,
												NULL);

						// set flash window
						lpFlashWnd=g_lpVolUpHky;

						// set flag
						bDup=TRUE;
					}

					// compare with volume-down
					if(g_lpMuteHky->GetHotKey()==g_lpVolDownHky->GetHotKey())
					{
						// set volume-down to none
						g_lpVolDownHky->SetHotKey(NULL,
												  NULL);

						// set flash window
						lpFlashWnd=g_lpVolDownHky;

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
									 "MsgBox_DupHotkey2");
			}

			// set modified state
			SetModified();
		}

		// ok
		break;
	}

	// check control id
	switch(LOWORD(wParam))
	{
	// playlist sort box
	case(IDC_AUDIOPLISTSORTCBX):

		// verify sort box control
		if(g_lpAudioPListSortCbx)
		{
			// check notification message
			switch(HIWORD(wParam))
			{
			// show dropdown
			case(CBN_DROPDOWN):

				// set flag
				g_lpAudioPListSortCbx->bBoxDown=TRUE;

				// ok
				break;

			// hide dropdown
			case(CBN_CLOSEUP):

				// set flag
				g_lpAudioPListSortCbx->bBoxDown=FALSE;

				// reset selection
				g_lpAudioPListSortCbx->SetCurSel(0);

				// ok
				break;

			// selection change ok
			case(CBN_SELENDOK):

				// sort based on selection
				SortAudioPlaylist(g_lpAudioPListSortCbx->GetCurSel());
				
				// reset selection
				g_lpAudioPListSortCbx->SetCurSel(0);

				// ok
				break;
			}
		}

		// ok
		break;
	}

	// call base method
	return(CExtDialog::OnCommand(wParam,
								 lParam));
}

// CMusicManagerDlg::ApplyChanges()

void CMusicManagerDlg::ApplyChanges(void)
{
	// index
	int nIndex;

	// folder info
	CDirTree* lpDirTree;

	// clear current folder
	SaveOptionString("Music_CurPath",
					 NULL_STRING);

	// get current folder
	nIndex=g_lpAudioHistoryCbx->GetCurSel();

	// check for error
	if(nIndex!=CB_ERR)
	{
		// get item data
		lpDirTree=(CDirTree*)g_lpAudioHistoryCbx->GetItemData(nIndex);

		// check item data
		if(lpDirTree)
		{
			// check for namespace root
			if(!lpDirTree->bIsNSRoot)
			{
				// check for immediate descendant
				if(!lpDirTree->lpParent->bIsNSRoot)
				{
					LockGlobalMsg()

					// get folder path
					if(SHGetPathFromIDList(lpDirTree->lpItemIDList,
										   g_lpMsg))
					{
						// save current path
						SaveOptionString("Music_CurPath",
										 g_lpMsg);
					}

					UnlockGlobalMsg()
				}
			}
		}
	}

	// save current file type
	SaveOptionInt("Music_TypeIdx",
				  g_lpFileTypeCbx->GetCurSel());

	// save popup info flag
	SaveOptionInt("Savers_PListPopup",
				  (int)g_bShowPListPopup);

	// update stored popup info flag
	g_bShowPListPopupPrev=g_bShowPListPopup;

	// save options
	SaveAudioOptions();

	// call base method
	CExtDialog::ApplyChanges();
}

// CMusicManagerDlg::ReleaseDialog()

void CMusicManagerDlg::ReleaseDialog(void)
{
	// message box result
	int nMBRes;

	// new window position
	CRect rMMgrWndPosNew;

	// offset values
	int nXOfs;
	int nYOfs;

	// check playlist saved flag
	if(!g_lpAudioPList->bIsSaved)
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
			OnPListSaveBtnClk();

			// no close
			CloseNotOK();

			// stop here
			return;
		}
		else if(nMBRes==IDCANCEL)
		{
			// no close
			CloseNotOK();

			// stop here
			return;
		}
	}

	// stop music
	UpdateCurrentAudio(TRUE);

	// clear current data
	g_lpCurAudioFLD=NULL;

	// reset bitmap buttons
	g_lpFileBackBtn->bSpclBtn        =FALSE;
	g_lpFileUpBtn->bSpclBtn          =FALSE;
	g_lpPlayBtn->bSpclBtn            =FALSE;
	g_lpPauseBtn->bSpclBtn           =FALSE;
	g_lpStopBtn->bSpclBtn            =FALSE;
	g_lpFullRewBtn->bSpclBtn         =FALSE;
	g_lpRewBtn->bSpclBtn             =FALSE;
	g_lpFwdBtn->bSpclBtn             =FALSE;
	g_lpAudioPListUpBtn->bSpclBtn    =FALSE;
	g_lpAudioPListTopBtn->bSpclBtn   =FALSE;
	g_lpAudioPListDownBtn->bSpclBtn  =FALSE;
	g_lpAudioPListBottomBtn->bSpclBtn=FALSE;

	// free apply button
	FreeClassObject(g_lpSubApplyBtn);

	// release history box
	g_lpAudioHistoryCbx->Release();

	// release tooltip control
	ReleaseToolTips(&g_lpMusicMgrToolTip);

	// release audio playlist
	g_lpAudioPList->Release();

	// release playlist file info
	ReleaseAudioPlaylistFileData();

	// revert popup info flag
	g_bShowPListPopup=g_bShowPListPopupPrev;

	// check update flag
	if(bUpdatePos)
	{
		// get new window position
		GetWindowRect(&rMMgrWndPosNew);

		// compute window offsets
		nXOfs=rMMgrWndPosNew.left-rMMgrWndPos.left;
		nYOfs=rMMgrWndPosNew.top -rMMgrWndPos.top;

		// offset window positions
		if(g_lpMMWndToHide2) g_rMMWnd2.OffsetRect(nXOfs,nYOfs);
		if(g_lpMMWndToHide1) g_rMMWnd1.OffsetRect(nXOfs,nYOfs);

		// keep on screen (as needed)
		if(g_lpMMWndToHide2==g_lpMainSheet) KeepRectsOnScreen(&g_rMMWnd2,&g_rMMWnd1);
		if(g_lpMMWndToHide1==g_lpMainSheet) KeepRectsOnScreen(&g_rMMWnd1);

		// restore windows
		if(g_lpMMWndToHide2) g_lpMMWndToHide2->MoveWindow(&g_rMMWnd2);
		if(g_lpMMWndToHide1) g_lpMMWndToHide1->MoveWindow(&g_rMMWnd1);
	}
}

// CMusicManagerDlg::InitDialog()

BOOL CMusicManagerDlg::InitDialog(void)
{
	// clear update flag
	bUpdatePos=FALSE;

	// reset playlist-saved flag
	g_lpAudioPList->bIsSaved=TRUE;
	
	// store popup info flag
	g_bShowPListPopupPrev=g_bShowPListPopup;

	// create apply button
	if(!CreateExtButton(&g_lpSubApplyBtn,
						IDC_APPLY))
		return(FALSE);

	// capture apply button
	if(!CaptureApplyBtn(g_lpSubApplyBtn))
		return(FALSE);

	// capture history box
	if(!CaptureDlgControl(this,
						  g_lpAudioHistoryCbx,
						  IDC_HISTORYCBX))
		return(FALSE);

	// capture file back button
	if(!CaptureDlgControl(this,
						  g_lpFileBackBtn,
						  IDC_FILEBACKBTN))
		return(FALSE);

	// set back button images
	g_lpFileBackBtn->SetSpclBitmapButton(FALSE,
										 &g_lpNavBackBmp,
										 &g_lpNavBackBmpGr);

	// capture file up button
	if(!CaptureDlgControl(this,
						  g_lpFileUpBtn,
						  IDC_FILEUPBTN))
		return(FALSE);

	// set back button images
	g_lpFileUpBtn->SetSpclBitmapButton(FALSE,
									   &g_lpNavUpBmp,
									   &g_lpNavUpBmpGr);

	// capture audio file list
	if(!CaptureDlgControl(this,
						  g_lpAudioFileList,
						  IDC_FILELIST))
		return(FALSE);

	// capture file type box
	if(!CaptureDlgControl(this,
						  g_lpFileTypeCbx,
						  IDC_FILETYPECBX))
		return(FALSE);

	// set parent dialog
	g_lpFileTypeCbx->SetParentDlg(this);

	// capture clear audio selection button
	if(!CaptureDlgControl(this,
						  g_lpClearAudioSelBtn,
						  IDC_CLEARAUDIOSELBTN))
		return(FALSE);

	// capture add audio file button
	if(!CaptureDlgControl(this,
						  g_lpAddAudioFileBtn,
						  IDC_ADDAUDIOFILEBTN))
		return(FALSE);

	// capture audio info box
	if(!CaptureDlgControl(this,
						  g_lpAudioInfoBox,
						  IDC_AUDIOINFO))
		return(FALSE);

	// update audio info
	UpdateAudioInfoBox(NULL);

	// capture play button
	if(!CaptureDlgControl(this,
						  g_lpPlayBtn,
						  IDC_PLAYBTN))
		return(FALSE);

	// capture pause button
	if(!CaptureDlgControl(this,
						  g_lpPauseBtn,
						  IDC_PAUSEBTN))
		return(FALSE);

	// capture stop button
	if(!CaptureDlgControl(this,
						  g_lpStopBtn,
						  IDC_STOPBTN))
		return(FALSE);

	// capture full rewind button
	if(!CaptureDlgControl(this,
						  g_lpFullRewBtn,
						  IDC_FULLREWBTN))
		return(FALSE);

	// capture rewind button
	if(!CaptureDlgControl(this,
						  g_lpRewBtn,
						  IDC_REWBTN))
		return(FALSE);

	// capture forward button
	if(!CaptureDlgControl(this,
						  g_lpFwdBtn,
						  IDC_FWDBTN))
		return(FALSE);

	// assign button images
	g_lpPlayBtn->SetSpclBitmapButton(FALSE,
									 &g_lpPlayBmp,
									 &g_lpPlayBmpGr);
	g_lpPauseBtn->SetSpclBitmapButton(FALSE,
									  &g_lpPauseBmp,
									  &g_lpPauseBmpGr);
	g_lpStopBtn->SetSpclBitmapButton(FALSE,
									 &g_lpStopBmp,
									 &g_lpStopBmpGr);
	g_lpFullRewBtn->SetSpclBitmapButton(FALSE,
										&g_lpFullRewBmp,
										&g_lpFullRewBmpGr);
	g_lpRewBtn->SetSpclBitmapButton(FALSE,
									&g_lpRewBmp,
									&g_lpRewBmpGr);
	g_lpFwdBtn->SetSpclBitmapButton(FALSE,
									&g_lpFwdBmp,
									&g_lpFwdBmpGr);

	// capture audio position text
	if(!CaptureDlgControl(this,
						  g_lpAudioPosTxt,
						  IDC_AUDIOPOSTXT))
		return(FALSE);

	// capture audio position slider
	if(!CaptureDlgControl(this,
						  g_lpAudioPosSld,
						  IDC_AUDIOPOSSLD))
		return(FALSE);

	// update timer
	UpdateAudioTimer(TRUE);

	// capture audio playlist up button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListUpBtn,
						  IDC_AUDIOPLISTUPBTN))
		return(FALSE);

	// capture audio playlist top button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListTopBtn,
						  IDC_AUDIOPLISTTOPBTN))
		return(FALSE);

	// capture audio playlist down button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListDownBtn,
						  IDC_AUDIOPLISTDOWNBTN))
		return(FALSE);

	// capture audio playlist bottom button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListBottomBtn,
						  IDC_AUDIOPLISTBOTTOMBTN))
		return(FALSE);

	// set as bitmap buttons
	g_lpAudioPListUpBtn->SetSpclBitmapButton(FALSE,
											 &g_lpPListUpBmp,
											 &g_lpPListUpBmpGr);
	g_lpAudioPListDownBtn->SetSpclBitmapButton(FALSE,
											   &g_lpPListDownBmp,
											   &g_lpPListDownBmpGr);
	g_lpAudioPListTopBtn->SetSpclBitmapButton(FALSE,
											  &g_lpPListTopBmp,
											  &g_lpPListTopBmpGr);
	g_lpAudioPListBottomBtn->SetSpclBitmapButton(FALSE,
												 &g_lpPListBottomBmp,
												 &g_lpPListBottomBmpGr);

	// capture audio playlist delete button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListDelBtn,
						  IDC_AUDIOPLISTDELBTN))
		return(FALSE);

	// capture audio playlist clear button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListClearBtn,
						  IDC_AUDIOPLISTCLRBTN))
		return(FALSE);

	// capture audio playlist save button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListSaveBtn,
						  IDC_AUDIOPLISTSAVEBTN))
		return(FALSE);

	// capture audio playlist load button
	if(!CaptureDlgControl(this,
						  g_lpAudioPListLoadBtn,
						  IDC_AUDIOPLISTLOADBTN))
		return(FALSE);

	// capture audio playlist sort box
	if(!CaptureDlgControl(this,
						  g_lpAudioPListSortCbx,
						  IDC_AUDIOPLISTSORTCBX))
		return(FALSE);

	// add items to sort box
	if((g_lpAudioPListSortCbx->AddString("Sort Items by:")<0)||
	   (g_lpAudioPListSortCbx->AddString("\xb7 Name (A-Z)")<0)||
	   (g_lpAudioPListSortCbx->AddString("\xb7 Name (Z-A)")<0)||
	   (g_lpAudioPListSortCbx->AddString("\xb7 Type (A-Z)")<0)||
	   (g_lpAudioPListSortCbx->AddString("\xb7 Type (Z-A)")<0))
	{
		DisplayNEErrorMessage("Unable to add item to sort list.");
		return(FALSE);
	}

	// select first string
	g_lpAudioPListSortCbx->SetCurSel(0);

	// capture audio playlist
	if(!CaptureDlgControl(this,
						  g_lpAudioPList,
						  IDC_AUDIOPLIST))
		return(FALSE);

	// set playlist buttons
	g_lpAudioPList->SetButtonPtrs(g_lpAudioPListUpBtn,
								  g_lpAudioPListDownBtn,
								  g_lpAudioPListTopBtn,
								  g_lpAudioPListBottomBtn,
								  g_lpAudioPListDelBtn,
								  g_lpAudioPListClearBtn,
								  g_lpAudioPListSaveBtn,
								  g_lpAudioPListLoadBtn);

	// set playlist auxilliary controls
	g_lpAudioPList->SetAuxCtrlPtrs(g_lpAudioPListSortCbx,
								   g_lpAudioPListSaveBtn);

	// set playlist callbacks
	g_lpAudioPList->SetCallbacks(GetAudioTitle,
								 GetAudioSaveData,
								 GetAudioItemData,
								 GetAudioTooltip);

	// initialize playlist
	if(!g_lpAudioPList->Init("Files in Playlist:"))
		return(FALSE);

	// capture playback controls checkbox
	if(!CaptureDlgControl(this,
						  g_lpEnablePBCChk,
						  IDC_ENABLEPBCCHK))
		return(FALSE);

	// capture next hotkey text
	if(!CaptureDlgControl(this,
						  g_lpNextHkyTxt,
						  IDC_NEXTHKYTXT))
		return(FALSE);

	// capture next hotkey
	if(!CaptureDlgControl(this,
						  g_lpNextHky,
						  IDC_NEXTHKY))
		return(FALSE);

	// capture volume up hotkey text
	if(!CaptureDlgControl(this,
						  g_lpVolUpHkyTxt,
						  IDC_VOLUPHKYTXT))
		return(FALSE);

	// capture volume up hotkey
	if(!CaptureDlgControl(this,
						  g_lpVolUpHky,
						  IDC_VOLUPHKY))
		return(FALSE);

	// capture volume down hotkey text
	if(!CaptureDlgControl(this,
						  g_lpVolDownHkyTxt,
						  IDC_VOLDNHKYTXT))
		return(FALSE);

	// capture volume down hotkey
	if(!CaptureDlgControl(this,
						  g_lpVolDownHky,
						  IDC_VOLDNHKY))
		return(FALSE);

	// capture mute hotkey text
	if(!CaptureDlgControl(this,
						  g_lpMuteHkyTxt,
						  IDC_MUTEHKYTXT))
		return(FALSE);

	// capture mute hotkey
	if(!CaptureDlgControl(this,
						  g_lpMuteHky,
						  IDC_MUTEHKY))
		return(FALSE);

	// hotkey rules
	#define HKEY_RULES HKCOMB_NONE,HOTKEYF_CONTROL

	// configure hotkey controls
	g_lpNextHky->SetRules(HKEY_RULES);
	g_lpVolUpHky->SetRules(HKEY_RULES);
	g_lpVolDownHky->SetRules(HKEY_RULES);
	g_lpMuteHky->SetRules(HKEY_RULES);

	// set hotkey values
	g_lpNextHky->SetHotKey(LOWORD(g_dwNextHky),
						   HIWORD(g_dwNextHky));
	g_lpVolUpHky->SetHotKey(LOWORD(g_dwVolUpHky),
							HIWORD(g_dwVolUpHky));
	g_lpVolDownHky->SetHotKey(LOWORD(g_dwVolDownHky),
							  HIWORD(g_dwVolDownHky));
	g_lpMuteHky->SetHotKey(LOWORD(g_dwMuteHky),
						   HIWORD(g_dwMuteHky));

	// capture windows synth radio
	if(!CaptureDlgControl(this,
						  g_lpWinSynthRad,
						  IDC_WINSYNTHRAD))
		return(FALSE);

	// capture directx synth radio
	if(!CaptureDlgControl(this,
						  g_lpDXSynthRad,
						  IDC_DXSYNTHRAD))
		return(FALSE);

	// capture directx effects text
	if(!CaptureDlgControl(this,
						  g_lpDXFXTxt,
						  IDC_DXFXTXT))
		return(FALSE);

	// capture reverb checkbox
	if(!CaptureDlgControl(this,
						  g_lpReverbChk,
						  IDC_REVERBCHK))
		return(FALSE);

	// capture chorus checkbox
	if(!CaptureDlgControl(this,
						  g_lpChorusChk,
						  IDC_CHORUSCHK))
		return(FALSE);

	// capture music manager help button
	if(!CaptureDlgControl(this,
						  g_lpMusicMgrHelpBtn,
						  IDC_MUSMANHELPBTN))
		return(FALSE);

	// capture install directx button
	if(!CaptureDlgControl(this,
						  g_lpInstallDXBtn,
						  IDC_INSTALLDXBTN))
		return(FALSE);

	// check directx
	g_bDXSynthOK=VerifyDirectXVersion();

	// check flag
	if(g_bDXSynthOK)
	{
		// enable radio button
		g_lpDXSynthRad->Enable();

		// hide install button
		g_lpInstallDXBtn->ShowWindow(SW_HIDE);
	}

	// check flag
	if(g_bUseDXSynth)
		SetDXSynth(FALSE);
	else
		SetWinSynth(FALSE);

	// toggle options
	ToggleReverb(FALSE);
	ToggleChorus(FALSE);
	
	// init tooltips
	if(!InitToolTips(&g_lpMusicMgrToolTip,
					 this))
		return(FALSE);

	// enable tooltips as needed
	if(g_bShowToolTips)
		::EnableToolTips(g_lpMusicMgrToolTip);
	else
		DisableToolTips(g_lpMusicMgrToolTip);

	// add tooltips to folder controls
	if(AddToolTip(g_lpMusicMgrToolTip,g_lpFileBackBtn,"Go to Last Folder Visited"))
		AddToolTip(g_lpMusicMgrToolTip,g_lpFileUpBtn,"Up One Level");

	// add tooltips to playlist buttons
	if(AddToolTip(g_lpMusicMgrToolTip,g_lpAudioPListUpBtn,"Move Up"))
		if(AddToolTip(g_lpMusicMgrToolTip,g_lpAudioPListTopBtn,"Move to Top"))
			if(AddToolTip(g_lpMusicMgrToolTip,g_lpAudioPListDownBtn,"Move Down"))
				AddToolTip(g_lpMusicMgrToolTip,g_lpAudioPListBottomBtn,"Move to Bottom");

	// add tooltips to playback buttons
	if(AddToolTip(g_lpMusicMgrToolTip,g_lpPlayBtn,"Play"))
		if(AddToolTip(g_lpMusicMgrToolTip,g_lpPauseBtn,"Pause"))
			if(AddToolTip(g_lpMusicMgrToolTip,g_lpStopBtn,"Stop"))
				if(AddToolTip(g_lpMusicMgrToolTip,g_lpFullRewBtn,"Rewind to Start"))
					if(AddToolTip(g_lpMusicMgrToolTip,g_lpRewBtn,"Rewind"))
						AddToolTip(g_lpMusicMgrToolTip,g_lpFwdBtn,"Fast Forward");

	// check hide window #1
	if(g_lpMMWndToHide1)
	{
		// get window rect
		g_lpMMWndToHide1->GetWindowRect(g_rMMWnd1);

		// set rect to make window invisible
		g_rMMInv1.left  =(g_rMMWnd1.left+g_rMMWnd1.right)/2;
		g_rMMInv1.top   =(g_rMMWnd1.top +g_rMMWnd1.bottom)/2;
		g_rMMInv1.right =g_rMMInv1.left;
		g_rMMInv1.bottom=g_rMMInv1.top;

		// offset position (if req'd)
		if(this==g_lpMusicManagerDlgB)
			g_rMMInv1.OffsetRect(SIDLG_NEGOFS);

		// move window
		g_lpMMWndToHide1->MoveWindow(g_rMMInv1);
	}

	// check hide window #2
	if(g_lpMMWndToHide2)
	{
		// get window rect
		g_lpMMWndToHide2->GetWindowRect(g_rMMWnd2);

		// set rect to make window invisible
		g_rMMInv2.left  =(g_rMMWnd2.left+g_rMMWnd2.right)/2;
		g_rMMInv2.top   =(g_rMMWnd2.top +g_rMMWnd2.bottom)/2;
		g_rMMInv2.right =g_rMMInv2.left;
		g_rMMInv2.bottom=g_rMMInv2.top;

		// offset position (if req'd)
		if(this==g_lpMusicManagerDlgB)
			g_rMMInv2.OffsetRect(SIDLG_NEGOFS);

		// move window
		g_lpMMWndToHide2->MoveWindow(g_rMMInv2);
	}

	// reset shown flag
	bWinShown=FALSE;

	// ok
	return(TRUE);
}

// CMusicManagerDlg::OnBackBtnClk()

void CMusicManagerDlg::OnBackBtnClk(void)
{
	// relay message
	g_lpAudioHistoryCbx->FolderBack();
}

// CMusicManagerDlg::OnUpBtnClk()

void CMusicManagerDlg::OnUpBtnClk(void)
{
	// relay message
	g_lpAudioHistoryCbx->FolderUp();
}

// CMusicManagerDlg::OnClearSelBtnClk()

void CMusicManagerDlg::OnClearSelBtnClk(void)
{
	// clear selection in file list
	g_lpAudioFileList->ClearSelection();

	// clear selection in playlist
	if(g_lpAudioPList->QuerySelection())
	{
		// clear selection
		g_lpAudioPList->SetItemState(g_lpAudioPList->GetSelection(),
									 NULL,
									 LVIS_SELECTED);
	}
}

// CMusicManagerDlg::OnAddFileBtnClk()

void CMusicManagerDlg::OnAddFileBtnClk(void)
{
	// add selection
	g_lpAudioFileList->AddToPlaylist();
}

// CMusicManagerDlg::PreTranslateMessage()

BOOL CMusicManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	// relay message to tooltip control
	if(g_lpMusicMgrToolTip)
		g_lpMusicMgrToolTip->RelayEvent(pMsg);

	// call base method
	return(CExtDialog::PreTranslateMessage(pMsg));
}

// GetAudioFileFilterList();

LPSTR GetAudioFileFilterList(void)
{
	// just to verify
	LockGlobalLongTTMsg()
	UnlockGlobalLongTTMsg()

	// get string
	g_lpAudioExtGrp->GetString(g_lpLongTTMsg);

	// return string
	return(g_lpLongTTMsg);
}

// GetPlaylistFilterList();

LPSTR GetPlaylistFilterList(void)
{
	// just to verify
	LockGlobalLongTTMsg()
	UnlockGlobalLongTTMsg()

	// get string
	g_lpPListExtGrp->GetString(g_lpLongTTMsg);

	// return string
	return(g_lpLongTTMsg);
}

// InitAudioSupport()

BOOL InitAudioSupport(BOOL bNotifyPos,
					  BOOL bSilent)
{
	// load options
	if(!LoadAudioOptions())
		return(FALSE);

	// create mci window
	g_hMCIWnd=MCIWndCreate(g_hWnd,
						   AfxGetInstanceHandle(),
						   MCIWNDF_NOAUTOSIZEWINDOW|
						   MCIWNDF_NOERRORDLG|
						   MCIWNDF_NOMENU|
						   MCIWNDF_NOOPEN|
						   MCIWNDF_NOPLAYBAR|
						   MCIWNDF_NOTIFYANSI|
						   MCIWNDF_NOTIFYMODE|
						   (bNotifyPos ? MCIWNDF_NOTIFYPOS : NULL),
						   NULL);

	// check for error
	if(!g_hMCIWnd)
	{
		if(!bSilent)
			DisplayErrorMessage("Unable to create MCI window for audio playback.");
		return(FALSE);
	}
	else
		AddWinResource

	// hide mci window
	ShowWindow(g_hMCIWnd,
			   SW_HIDE);

	// set update timers
	MCIWndSetTimers(g_hMCIWnd,
					250,
					250);

	// clear pause flag
	g_bAudioPause=FALSE;

	// init master volume
	MasterVolume(MV_INIT);

	// set init flag
	g_bAudioInit=TRUE;

	// ok
	return(TRUE);
}

// ReleaseAudioSupport()

void ReleaseAudioSupport(void)
{
	// restore master volume
	MasterVolume(MV_RESTORE);

	// release master volume
	MasterVolume(MV_RELEASE);

	// check mci window
	if(g_hMCIWnd!=(HWND)INVALID_HANDLE_VALUE&&
	   g_hMCIWnd!=NULL)
	{
		// stop current file
		MCIWndStop(g_hMCIWnd);

		// clear pause flag
		g_bAudioPause=FALSE;

		// destroy window
		MCIWndDestroy(g_hMCIWnd);

		// reset handle
		g_hMCIWnd=(HWND)INVALID_HANDLE_VALUE;

		// clear init flag
		g_bAudioInit=FALSE;

		RemoveWinResource
	}
}

// CAudioExtComboBox::CAudioExtComboBox()

CAudioExtComboBox::CAudioExtComboBox(UINT nID)
{
	// copy id
	nCtrlId=nID;

	// reset values
	lpParentDlg=NULL;

	// call base method
	CExtComboBox::CExtComboBox();
}

// CAudioExtComboBox::OnCommand()

BOOL CAudioExtComboBox::OnCommand(WPARAM wParam,
								  LPARAM lParam)
{
	// current selection
	int nSelItem;

	// check message
	switch(HIWORD(wParam))
	{
	// combo box selection
	case(CBN_SELCHANGE):

		// hide list
		ShowDropDown(FALSE);

		// get selection
		nSelItem=GetCurSel();

		// check selection
		if(nSelItem!=CB_ERR)
		{
			// set current extension list
			g_lpCurAudExtList=(CExtensionList*)GetItemData(nSelItem);

			// update folder
			g_lpAudioFileList->ShowFolder(-1,
										  FALSE);
		}

		// play sound
		PlaySound(IDR_NEWSELSND);

		// set parent modified
		if(lpParentDlg)
			lpParentDlg->SetModified();

		// ok
		break;
	}

	// call base method
	return(CExtComboBox::OnCommand(wParam,
								   lParam));
}

// DisplayMCIErrorMessage()

BOOL DisplayMCIErrorMessage(LPSTR lpError)
{
	LockGlobalLongTTMsg()
	
	// get error string
	if(!MCIWndGetError(g_hMCIWnd,
					   g_lpLongTTMsg,
					   LONG_MSG_SIZE))
	{
		UnlockGlobalLongTTMsg()

		// no error reported
		return(FALSE);
	}

	LockGlobalTTMsg()

	// check for error message
	if(!lpError)
	{
		// copy default message
		strcpy(g_lpTTMsg,
			   "Media device error:");

		// assign to error
		lpError=g_lpTTMsg;
	}

	// display error message
	DisplayErrorMessage(lpError,
						g_lpLongTTMsg,
						FALSE);

	UnlockGlobalTTMsg()
	UnlockGlobalLongTTMsg()

	// error found
	return(TRUE);
}

// DisplayNEMCIErrorMessage()

BOOL DisplayNEMCIErrorMessage(LPSTR lpError)
{
#ifdef SHOW_NE_ERRORS
#ifdef DEBUG_MODE
	// alert user
	DisplayInfoMessage("Non-essential error:");
#endif
#else
	// check for control key
	if(IsKeyDown(VK_CONTROL))
#endif
	// display error
	return(DisplayMCIErrorMessage(lpError));
#ifndef SHOW_NE_ERRORS
	else return(TRUE);
#endif
}

// CAudioExtComboBox::SetParentDlg()

void CAudioExtComboBox::SetParentDlg(CExtDialog* lpDlg)
{
	// copy value
	lpParentDlg=lpDlg;
}

// ReadTag()

BOOL ReadTag(HANDLE hFile,
			 LPSTR lpTag,
			 DWORD dwNumBytes)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid handle value.",
							"ReadTag()",
							FALSE);
		return(FALSE);
	}

	// verify string
	if(!lpTag)
	{
		DisplayErrorMessage("Invalid string value.",
							"ReadTag()",
							FALSE);
		return(FALSE);
	}
#endif

	// clear string
	lpTag[0]=0;

	// check bytes
	if(dwNumBytes)
	{
		// read tag
		if(!ReadFile(hFile,
					 lpTag,
					 dwNumBytes,
					 TRUE))
			return(FALSE);

		// set null terminator
		lpTag[dwNumBytes]=0;
	}

	// ok
	return(TRUE);
}

// ReadWideTag()

BOOL ReadWideTag(HANDLE hFile,
				 LPSTR lpTag,
				 DWORD dwNumBytes)
{
#ifdef DEBUG_MODE
	// verify handle
	if(hFile==NULL||
	   hFile==INVALID_HANDLE_VALUE)
	{
		DisplayErrorMessage("Invalid handle value.",
							"ReadWideTag()",
							FALSE);
		return(FALSE);
	}

	// verify string
	if(!lpTag)
	{
		DisplayErrorMessage("Invalid string value.",
							"ReadWideTag()",
							FALSE);
		return(FALSE);
	}
#endif

	// clear string
	lpTag[0]=0;

	// check bytes
	if(dwNumBytes)
	{
		LockGlobalLongTTMsg()

		// read tag
		if(!ReadFile(hFile,
					 g_lpLongTTMsg,
					 (dwNumBytes*2),
					 TRUE))
		{
			UnlockGlobalLongTTMsg()
			return(FALSE);
		}

		// set null terminator
		g_lpLongTTMsg[(dwNumBytes*2)+0]=0;
		g_lpLongTTMsg[(dwNumBytes*2)+1]=0;

		// convert to multi-byte
		if(!WideCharToMultiByte(CP_ACP,
								NULL,
								(LPCWSTR)g_lpLongTTMsg,
								-1,
								lpTag,
								_MAX_PATH,
								NULL,
								NULL))
		{
			UnlockGlobalLongTTMsg()
			return(FALSE);
		}

		UnlockGlobalLongTTMsg()
	}

	// ok
	return(TRUE);
}

// ByteCount()

unsigned int ByteCount(LPSTR lpStr,
					   char cByte)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"ByteCount()",
							FALSE);
		return(FALSE);
	}
#endif

	// reset byte counter
	unsigned int nCount=0;

	// reset pointer
	int nPtr=0;

	// check target byte
	if(cByte!=-1)
	{
		// check bytes
		while(lpStr[nPtr]!=0)
		{
			// compare values
			if(lpStr[nPtr]==cByte)
				nCount++;

			// increment pointer
			nPtr++;
		}
	}
	else
	{
		// check bytes
		while(lpStr[nPtr]!=0)
		{
			// compare values
			if(lpStr[nPtr]<=32||
			   lpStr[nPtr]>=128)
				nCount++;

			// increment pointer
			nPtr++;
		}
	}

	// ok
	return(nCount);
}

// GetAudioFileInfo()

BOOL GetAudioFileInfo(HWND hMCIWnd,
					  CFileInfo* lpFileInfo,
					  LPSTR lpPath)
{
#ifdef DEBUG_MODE
	// verify window
	if(!IsWindow(hMCIWnd))
	{
		DisplayErrorMessage("Invalid window.",
							"GetAudioFileInfo()",
							FALSE);
		return(FALSE);
	}

	// verify pointers
	if(!lpFileInfo||
	   !lpPath)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"GetAudioFileInfo()",
							FALSE);
		return(FALSE);
	}
#endif

	// length value
	int nLen;

	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// multimedia file handle
	HMMIO hMMIO=(HMMIO)INVALID_HANDLE_VALUE;

	// multimedia file info
	MMIOINFO mmioInfo;

	// multimedia chunk info
	MMCKINFO mmckInfo;

	// input string
	char lpInput[31];

	// reset type flags
	BOOL bIsMidi=FALSE;
	BOOL bIsWave=FALSE;

	// wave file data
	WAVEFORMATEX wfx;

	// sample rate digits
	int nSR1;
	int nSR2;

	// guid (for wma)
	GUID guid;

	// asf object sizes
	DWORD dwObjSzLo;
	DWORD dwObjSzHi;

	// header objects
	DWORD dwNumObj;

	// asf file data
	WORD wTitleLen;
	WORD wAuthorLen;
	WORD wCopyrightLen;
	WORD wDescriptionLen;
	WORD wRatingLen;

	// set return value
	BOOL bRet=FALSE;

	// check for existing data
	if(lpFileInfo->lpFileData)
	{
		// copy mp3 flag
		g_bCurAudioIsMP3=(BOOL)lpFileInfo->dwUserData;

		// stop here
		return(TRUE);
	}

	// clear mp3 flag
	g_bCurAudioIsMP3=FALSE;

	LockGlobalLongMsg()
	
	// set string pointer
	LPSTR lpStr=g_lpLongMsg;
	
	// set millisecond format
	if(MCIWndSetTimeFormat(hMCIWnd,
						   "ms")!=0)
	{
		DisplayMCIErrorMessage();
		goto GetAudioFileInfo1;
	}

	// get audio length
	nLen=MCIWndGetLength(hMCIWnd);

	// clear string
	lpStr[0]=0;

	// output name
	strcat(lpStr,"Name:\xfe");
	strcat(lpStr,lpFileInfo->lpTitle);
	strcat(lpStr,"\xff");

	LockGlobalTTMsg()

	// convert extension to uppercase
	strcpy(g_lpTTMsg,lpFileInfo->lpExtension);
	strupr(g_lpTTMsg);

	// output type
	strcat(lpStr,"Type:\xfe");
	strcat(lpStr,g_lpTTMsg);
	strcat(lpStr," File\xff");

	// get time string
	if(!GetHmsStringFromMsVal(g_lpTTMsg,
							  (long)nLen))
	{
		UnlockGlobalTTMsg()
		goto GetAudioFileInfo1;
	}

	// output length
	strcat(lpStr,"Length:\xfe");
	strcat(lpStr,g_lpTTMsg);
	strcat(lpStr,"\xff");

	UnlockGlobalTTMsg()
			
	// open file
	hFile=CreateFile(lpPath,
					 GENERIC_READ,
					 FILE_SHARE_READ,
					 NULL,
					 OPEN_EXISTING,
					 NULL,
					 NULL);

	// check for error
	if(hFile==INVALID_HANDLE_VALUE)
		goto GetAudioFileInfo2;
	else
		AddWinResource

	// reset multimedia info
	ZeroMemory(&mmioInfo,
			   sizeof(mmioInfo));

	// set file handle
	mmioInfo.adwInfo[0]=(DWORD)hFile;

	// open multimedia file
	hMMIO=mmioOpen(NULL,
				   &mmioInfo,
				   MMIO_READ);

	// check for error
	if(hMMIO==NULL)
		goto GetAudioFileInfo2;
	else
		AddWinResource

	// get first chunk
	if(mmioDescend(hMMIO,
				   &mmckInfo,
				   NULL,
				   NULL)==MMSYSERR_NOERROR)
	{
		// check for midi type
		if(mmckInfo.ckid==mmioFOURCC('M','T','h','d'))
			bIsMidi=TRUE;
		else if(mmckInfo.ckid==mmioFOURCC('R','I','F','F'))
		{
			// check type
			if(mmckInfo.fccType==mmioFOURCC('R','M','I','D'))
				bIsMidi=TRUE;
			else if(mmckInfo.fccType==mmioFOURCC('W','A','V','E'))
				bIsWave=TRUE;
		}
	}

	// check file type
	if(bIsMidi)
	{
		// no useful info in MIDI files
	}
	else if(bIsWave)
	{
		// set id for format
		mmckInfo.ckid=mmioFOURCC('f','m','t',' ');

		// find format chunk
		if(mmioDescend(hMMIO,
					   &mmckInfo,
					   NULL,
					   MMIO_FINDCHUNK)==MMSYSERR_NOERROR)
		{
			// seek to data
			if(SetFilePointer(hFile,
							  mmckInfo.dwDataOffset,
							  NULL,
							  FILE_BEGIN)!=0xFFFFFFFFL)
			{
				// read format
				if(ReadFile(hFile,
							&wfx,
							sizeof(wfx),
							TRUE))
				{
					// get sample rate digits
					nSR1=wfx.nSamplesPerSec/1000;
					nSR2=((wfx.nSamplesPerSec%1000)+50)/100;

					LockGlobalTTMsg()
					
					// prepare sample rate
					sprintf(g_lpTTMsg,
						    "%d.%d kHz",
							nSR1,
							nSR2);

					// output sample rate
					strcat(lpStr,"Quality:\xfe");
					strcat(lpStr,g_lpTTMsg);
					strcat(lpStr,"\xff");

					// prepare channels
					sprintf(g_lpTTMsg,
						    "%d",
							wfx.nChannels);

					// output sample rate
					strcat(lpStr,"Channels:\xfe");
					strcat(lpStr,g_lpTTMsg);
					strcat(lpStr,"\xff");

					UnlockGlobalTTMsg()
				}
			}
		}
	}

	// close multimedia file
	if(mmioClose(hMMIO,
				 MMIO_FHOPEN)==0)
		RemoveWinResource

	// check flags
	if(!bIsMidi&&
	   !bIsWave)
	{
		// seek to start (for wma files)
		if(SetFilePointer(hFile,
						  0,
						  NULL,
						  FILE_BEGIN)==0xFFFFFFFFL)
			goto GetAudioFileInfo2;

		// read guid
		if(!ReadFile(hFile,
					 &guid,
					 sizeof(guid),
					 TRUE))
			goto GetAudioFileInfo2;

		// check for header
		if(guid==ASF_Header_Object)
		{
			// skip object size
			if(SetFilePointer(hFile,
							  8,
							  NULL,
							  FILE_CURRENT)==0xFFFFFFFFL)
				goto GetAudioFileInfo2;

			// get object count
			if(!ReadFile(hFile,
						 &dwNumObj,
						 sizeof(DWORD),
						 TRUE))
				goto GetAudioFileInfo2;

			// skip reserved flags
			if(SetFilePointer(hFile,
							  2,
							  NULL,
							  FILE_CURRENT)==0xFFFFFFFFL)
				goto GetAudioFileInfo2;

			// check each object
			while(dwNumObj)
			{
				// read guid
				if(!ReadFile(hFile,
							 &guid,
							 sizeof(guid),
							 TRUE))
					goto GetAudioFileInfo2;

				// check for description
				if(guid==ASF_Content_Description_Object)
				{
					// skip object size
					if(SetFilePointer(hFile,
									  8,
									  NULL,
									  FILE_CURRENT)==0xFFFFFFFFL)
						goto GetAudioFileInfo2;

					// read data lengths
					if(!ReadFile(hFile,
								 &wTitleLen,
								 sizeof(WORD),
								 TRUE)||
					   !ReadFile(hFile,
								 &wAuthorLen,
								 sizeof(WORD),
								 TRUE)||
					   !ReadFile(hFile,
								 &wCopyrightLen,
								 sizeof(WORD),
								 TRUE)||
					   !ReadFile(hFile,
								 &wDescriptionLen,
								 sizeof(WORD),
								 TRUE)||
					   !ReadFile(hFile,
								 &wRatingLen,
								 sizeof(WORD),
								 TRUE))
						goto GetAudioFileInfo2;

					LockGlobalTTMsg()
					
					// read title
					if(ReadWideTag(hFile,
								   g_lpTTMsg,
								   wTitleLen/2))
					{
						// check string
						if(strlen(g_lpTTMsg)!=ByteCount(g_lpTTMsg,-1))
						{
							// output title
							strcat(lpStr,"Title:\xfe");
							strcat(lpStr,g_lpTTMsg);
							strcat(lpStr,"\xff");
						}
					}

					// read author
					if(ReadWideTag(hFile,
								   g_lpTTMsg,
								   wAuthorLen/2))
					{
						// check string
						if(strlen(g_lpTTMsg)!=ByteCount(g_lpTTMsg,-1))
						{
							// output author
							strcat(lpStr,"Author:\xfe");
							strcat(lpStr,g_lpTTMsg);
							strcat(lpStr,"\xff");
						}
					}

					// read copyright
					if(ReadWideTag(hFile,
								   g_lpTTMsg,
								   wCopyrightLen/2))
					{
						// check string
						if(strlen(g_lpTTMsg)!=ByteCount(g_lpTTMsg,-1))
						{
							// output copyright
							strcat(lpStr,"Copyright:\xfe");
							strcat(lpStr,g_lpTTMsg);
							strcat(lpStr,"\xff");
						}
					}

					// read description
					if(ReadWideTag(hFile,
								   g_lpTTMsg,
								   wDescriptionLen/2))
					{
						// check string
						if(strlen(g_lpTTMsg)!=ByteCount(g_lpTTMsg,-1))
						{
							// output description
							strcat(lpStr,"Description:\xfe");
							strcat(lpStr,g_lpTTMsg);
							strcat(lpStr,"\xff");
						}
					}

					// read rating
					if(ReadWideTag(hFile,
								   g_lpTTMsg,
								   wRatingLen/2))
					{
						// check string
						if(strlen(g_lpTTMsg)!=ByteCount(g_lpTTMsg,-1))
						{
							// output rating
							strcat(lpStr,"Rating:\xfe");
							strcat(lpStr,g_lpTTMsg);
							strcat(lpStr,"\xff");
						}
					}

					UnlockGlobalTTMsg()

					// stop here
					break;
				}
				else
				{
					// read object sizes
					if(!ReadFile(hFile,
								 &dwObjSzLo,
								 sizeof(DWORD),
								 TRUE)||
					   !ReadFile(hFile,
								 &dwObjSzHi,
								 sizeof(DWORD),
								 TRUE))
						goto GetAudioFileInfo2;

					// compensate for overflow
					if(dwObjSzLo<24)
						dwObjSzHi--;

					// remove header size
					dwObjSzLo-=24;					

					// skip to next object
					if(SetFilePointer(hFile,
									  dwObjSzLo,
									  (long*)&dwObjSzHi,
									  FILE_CURRENT)==0xFFFFFFFFL)
					{
						// verify error
						if(GetLastError()!=NO_ERROR)
							goto GetAudioFileInfo2;
					}

					// update counter
					dwNumObj--;
				}
			}
		}
		else
		{
			// seek to end-128 (for mp3 files)
			if(SetFilePointer(hFile,
							  -128,
							  NULL,
							  FILE_END)==0xFFFFFFFFL)
				goto GetAudioFileInfo2;

			// read tag
			if(!ReadTag(hFile,
						lpInput,
						3))
				goto GetAudioFileInfo2;

			// check string
			if(strcmp(lpInput,
					  "TAG")==0)
			{
				// read track name
				if(ReadTag(hFile,
						   lpInput,
						   30))
				{
					// check string
					if(strlen(lpInput)!=ByteCount(lpInput,-1))
					{
						// output track name
						strcat(lpStr,"Song:\xfe");
						strcat(lpStr,lpInput);
						strcat(lpStr,"\xff");
					}
				}

				// read artist
				if(ReadTag(hFile,
						   lpInput,
						   30))
				{
					// check string
					if(strlen(lpInput)!=ByteCount(lpInput,-1))
					{
						// output artist
						strcat(lpStr,"Artist:\xfe");
						strcat(lpStr,lpInput);
						strcat(lpStr,"\xff");
					}
				}

				// read album
				if(ReadTag(hFile,
						   lpInput,
						   30))
				{
					// check string
					if(strlen(lpInput)!=ByteCount(lpInput,-1))
					{
						// output album
						strcat(lpStr,"Album:\xfe");
						strcat(lpStr,lpInput);
						strcat(lpStr,"\xff");
					}
				}

				// read year
				if(ReadTag(hFile,
						   lpInput,
						   4))
				{
					// check string
					if(strlen(lpInput)!=ByteCount(lpInput,-1))
					{
						// output year
						strcat(lpStr,"Year:\xfe");
						strcat(lpStr,lpInput);
						strcat(lpStr,"\xff");
					}
				}

				// read comments
				if(ReadTag(hFile,
						   lpInput,
						   30))
				{
					// check string
					if(strlen(lpInput)!=ByteCount(lpInput,-1))
					{
						// output comments
						strcat(lpStr,"Comments:\xfe");
						strcat(lpStr,lpInput);
						strcat(lpStr,"\xff");
					}
				}
				
				// set mp3 flag
				g_bCurAudioIsMP3=TRUE;
			}
		}
	}

	// allocate memory for data
	if(!AllocMem((LPVOID*)&lpFileInfo->lpFileData,
				 strlen(lpStr)+1))
		goto GetAudioFileInfo2;

	// copy data
	strcpy(lpFileInfo->lpFileData,
		   lpStr);

	// ok
	bRet=TRUE;

// error exit #2
GetAudioFileInfo2:;

	// close file
	if(CloseHandle(hFile))
		RemoveWinResource

// error exit #1
GetAudioFileInfo1:;

	UnlockGlobalLongMsg()

	// store mp3 flag
	lpFileInfo->dwUserData=(DWORD)g_bCurAudioIsMP3;

	// ok
	return(bRet);
}

// SetCurrentAudio()

BOOL SetCurrentAudio(LPFILELISTDATA lpFLD)
{
	// temporary data
	LPFILELISTDATA lpTemp=NULL;

	// check for reload
	if(lpFLD==CURAUDIO_RELOAD)
	{
		// save current data
		lpTemp=g_lpCurAudioFLD;

		// clear audio
		SetCurrentAudio(NULL);

		// reload audio
		return(SetCurrentAudio(lpTemp));
	}

	// check for null
	if(!lpFLD)
	{
		// check for swap timer
		if(g_nFSwapId)
		{
			// no change
			return(FALSE);
		}
	}

	// check for same file
	if(g_lpCurAudioFLD==lpFLD)
	{
		// no change
		return(FALSE);
	}

	// check timer id
	if(g_nCurAudioTimerID)
	{
		// kill timer
		KillTimer(NULL,
				  g_nCurAudioTimerID);

		// reset id
		g_nCurAudioTimerID=0;
	}

	// stop music
	UpdateCurrentAudio(TRUE);

	// copy file list data
	g_lpCurAudioFLD=lpFLD;

	// set timer
	g_nCurAudioTimerID=SetTimer(NULL,
								NULL,
								AUDIO_TIMEOUT,
								CurAudioTimerProc);

	// ok
	return(TRUE);
}

// WaitForAudioTimeout()

void WaitForAudioTimeout(void)
{
	// check for timer
	if(g_nCurAudioTimerID)
	{
		// begin wait cursor
		::BeginWaitCursor();

		// wait for timer
		Sleep(AUDIO_TIMEOUT_WAIT);

		// end wait cursor
		::EndWaitCursor();
	}
}

// CurAudioTimerProc()

void CALLBACK CurAudioTimerProc(HWND hWnd,
								UINT uMsg,
								UINT idEvent,
								DWORD dwTime)
{
	// kill timer
	KillTimer(NULL,
			  g_nCurAudioTimerID);

	// reset id
	g_nCurAudioTimerID=0;

	// update current audio
	UpdateCurrentAudio(FALSE);
}

// UpdateAudioInfoBox()

BOOL UpdateAudioInfoBox(CFileInfo* lpFileInfo)
{
	// edit stream info
	EDITSTREAM es;

	// counters
	int nCount;
	size_t nCount2;

	// current byte
	BYTE cByte;

	// reset info-added flag
	BOOL bInfoAdded=FALSE;

	// check audio info box
	if(!IsWindow(g_lpAudioInfoBox->m_hWnd))
		return(TRUE);

	// scroll box to top
	g_lpAudioInfoBox->ScrollToTop();

	LockGlobalLongMsg()
	
	// output rtf header
	strcpy(g_lpLongMsg,"{\\rtf1\\ansi\\deff0"
					   "{\\fonttbl{\\f0\\fnil\\fcharset0 MS Shell Dlg;}}"
					   "\\viewkind4\\uc1\\pard\\lang1033\\f0\\fs17"
					   "\\tx725\\tx1100");

	// check for info
	if(lpFileInfo)
	{
		// check for data
		if(lpFileInfo->lpFileData)
		{
			// output starting data
			strcat(g_lpLongMsg,"\\b ");

			// set counter
			nCount=strlen(g_lpLongMsg);

			// output bytes
			for(nCount2=0;nCount2<strlen(lpFileInfo->lpFileData);nCount2++)
			{
				// read byte
				cByte=lpFileInfo->lpFileData[nCount2];

				// check byte
				if(cByte==0xFF)
				{
					// output data
					strcat(g_lpLongMsg,"\\par\\b ");

					// update counter
					nCount=strlen(g_lpLongMsg);
				}
				else if(cByte==0xFE)
				{
					// output data
					strcat(g_lpLongMsg,"\\b0\\tab ");

					// update counter
					nCount=strlen(g_lpLongMsg);
				}
				else
				{
					// copy byte
					g_lpLongMsg[nCount]=cByte;

					// increment counter
					nCount++;

					// set terminator
					g_lpLongMsg[nCount]=0;
				}
			}

			// set flag
			bInfoAdded=TRUE;
		}
	}

	// check info-added flag
	if(!bInfoAdded)
	{
		// output default data
		strcat(g_lpLongMsg,"\\b Name:\\par Type:\\par Length:\\par ");
	}

	// close rtf data
	strcat(g_lpLongMsg,"\\b0 }");

	UnlockGlobalLongMsg()

	// correct for newlines
	CorrectRTFNewLines(g_lpLongMsg);

	LockGlobalLongMsg()

	// prepare edit stream
	es.dwCookie=(DWORD)g_lpLongMsg;
	es.dwError=NULL;
	es.pfnCallback=StreamInCallback;

	// stream text to info box
	g_lpAudioInfoBox->StreamIn(SF_RTF,
							   es);

	UnlockGlobalLongMsg()

	// enable window (req'd for proper disable)
	g_lpAudioInfoBox->Enable();

	// disable if req'd
	if(!lpFileInfo)
		g_lpAudioInfoBox->Disable();

	// ok
	return(TRUE);
}

// UpdateCurrentAudio()

void UpdateCurrentAudio(BOOL bClear)
{
	// pointer to file info
	CFileInfo* lpFileInfo;

	// dialog must be initialized (check any control)
	if(!IsWindow(g_lpPlayBtn->m_hWnd))
		return;

	// check clear flag
	if(bClear)
	{
		// begin wait
		::BeginWaitCursor();

		// check for current file
		if(g_nCurAudioDevID)
		{
			// close current file
			MCIWndClose(g_hMCIWnd);
			
			// wait for not-ready
			MCIWaitForNotReady(g_nCurAudioDevID);

			// clear pause flag
			g_bAudioPause=FALSE;

			// clear id
			g_nCurAudioDevID=NULL;

			// clear info
			UpdateAudioInfoBox(NULL);
		}

		// disable buttons
		g_lpClearAudioSelBtn->Disable();
		g_lpAddAudioFileBtn->Disable();

		// disable audio controls
		g_lpPlayBtn->Disable();
		g_lpPauseBtn->Disable();
		g_lpStopBtn->Disable();
		g_lpFullRewBtn->Disable();
		g_lpRewBtn->Disable();
		g_lpFwdBtn->Disable();

		// clear timer
		UpdateAudioTimer(TRUE);

		// end wait
		::EndWaitCursor();

		// stop here
		return;
	}

	// check for no-file
	if(g_lpCurAudioFLD==NULL)
		return;

	// enable clear button
	if(g_lpAudioFileList->QuerySelection())
		g_lpClearAudioSelBtn->Enable();

	// must not be folder or link
	if(g_lpCurAudioFLD->bIsFolder||
	   g_lpCurAudioFLD->bIsLinkToFolder)
		return;

	// cast pointer to file info
	lpFileInfo=(CFileInfo*)g_lpCurAudioFLD->lpData;

	LockGlobalMsg()

	// get full path
	if(!lpFileInfo->GetPath(g_lpMsg))
	{
		UnlockGlobalMsg()
		return;
	}

	// begin wait
	::BeginWaitCursor();

	// open file
	if(MCIWndOpen(g_hMCIWnd,
				  g_lpMsg,
				  NULL)!=0)
	{
		// wait for mci
		Sleep(AUDIO_TIMEOUT_WAIT);

		// try again
		if(MCIWndOpen(g_hMCIWnd,
					  g_lpMsg,
					  NULL)!=0)
		{
			// test mp3 output
			TestMP3Output();

			// end wait
			::EndWaitCursor();

			UnlockGlobalMsg()

			// stop here
			return;
		}
	}

	// get audio info
	GetAudioFileInfo(g_hMCIWnd,
					 lpFileInfo,
					 g_lpMsg);

	UnlockGlobalMsg()

	// get valid id
	g_nCurAudioDevID=MCIWndGetDeviceID(g_hMCIWnd);

	// wait for ready
	MCIWaitForReady(g_nCurAudioDevID);

	// clear pause flag
	g_bAudioPause=FALSE;

	// update audio info
	UpdateAudioInfoBox(lpFileInfo);

	// enable add button
	if(g_lpAudioFileList->QuerySelection())
		g_lpAddAudioFileBtn->Enable();

	// enable play button
	g_lpPlayBtn->Enable();

	// update timer
	UpdateAudioTimer();

	// check for mp3
	if(g_bCurAudioIsMP3)
	{
		// reset mp3 test
		TestMP3Output(TRUE,
					  TRUE);
	}

	// end wait
	::EndWaitCursor();
}

// UpdateAudioTimer()

void UpdateAudioTimer(BOOL bClear)
{
	// enabled flag
	static BOOL bTimerEnabled=FALSE;

	// timer range
	static long lTimeMin;
	static long lTimeMax;

	// current time
	long lTimeCur;

	// current mode
	long lMode;

	// check clear flag
	if(bClear)
	{
		// check enabled flag
		if(bTimerEnabled)
		{
			// reset text
			g_lpAudioPosTxt->SetWindowText("0:00/0:00");

			// reset slider range
			g_lpAudioPosSld->SetRange(0,1);

			// reset slider position
			g_lpAudioPosSld->SetPos(0);

			// clear tic marks
			g_lpAudioPosSld->ClearTics();

			// redraw slider
			g_lpAudioPosSld->RedrawWindow();

			// disable controls
			g_lpAudioPosTxt->Disable();
			g_lpAudioPosSld->Disable();

			// disable buttons
			g_lpFullRewBtn->Disable();
			g_lpRewBtn->Disable();
			g_lpFwdBtn->Disable();

			// clear flag
			bTimerEnabled=FALSE;
		}
	}
	else
	{
		// check for device
		if(g_nCurAudioDevID)
		{
			// check enabled flag
			if(!bTimerEnabled)
			{
				// get timer range
				lTimeMin=MCIWndGetStart(g_hMCIWnd);
				lTimeMax=MCIWndGetEnd(g_hMCIWnd);

				// check length
				if((lTimeMax-lTimeMin)>60000)
				{
					// offset min to correct for some mp3s
					if(g_bCurAudioIsMP3)
						lTimeMin+=MP3_CORR_VAL;
				}

				// reset slider range
				g_lpAudioPosSld->SetRange(lTimeMin,
										  lTimeMax);

				// add tic marks
				AutoSetSliderTics(g_lpAudioPosSld,
								  6);

				// enable controls
				g_lpAudioPosTxt->Enable();
				g_lpAudioPosSld->Enable();

				// set flag
				bTimerEnabled=TRUE;

				// reset audio position
				if(MCIWndSeek(g_hMCIWnd,
							  lTimeMin)!=0)
				{
					// display error
					DisplayNEMCIErrorMessage();
				}
			}

			// check update flag
			if(g_bNoAudioPosUpdate)
			{
				// use position as time
				lTimeCur=g_lpAudioPosSld->GetPos();
			}
			else
			{
				// wait for ready
				while(TRUE)
				{
					// get current mode
					lMode=MCIWndGetMode(g_hMCIWnd,
										NULL,
										NULL);

					// check mode
					if(lMode!=MCI_MODE_SEEK)
						break;

					// wait a bit
					Sleep(AUDIO_TIMEOUT_BRIEF);
				}

				// get current time
				lTimeCur=MCIWndGetPosition(g_hMCIWnd);

				// set slider position
				g_lpAudioPosSld->SetPos(lTimeCur-lTimeMin);
			}

			// update position text
			UpdateAudioPosText(lTimeCur);

			// check position
			if(lTimeCur==lTimeMin)
			{
				// disable rewind controls
				g_lpFullRewBtn->Disable();
				g_lpRewBtn->Disable();

				// enable forward control
				g_lpFwdBtn->Enable();
			}
			else if(lTimeCur==lTimeMax)
			{
				// enable rewind controls
				g_lpFullRewBtn->Enable();
				g_lpRewBtn->Enable();

				// disable forward control
				g_lpFwdBtn->Disable();
			}
			else
			{
				// check & enable all controls
				if(!g_lpFullRewBtn->bEnabled) g_lpFullRewBtn->Enable();
				if(!g_lpRewBtn->bEnabled)     g_lpRewBtn->Enable();
				if(!g_lpFwdBtn->bEnabled)     g_lpFwdBtn->Enable();
			}
		}
	}
}

// CAudioPosSlider::CAudioPosSlider()

CAudioPosSlider::CAudioPosSlider(UINT nID)
{
	// copy id
	nCtrlId=nID;

	// call base method
	CExtSliderCtrl::CExtSliderCtrl();
}

// CMusicManagerDlg::OnHScroll()

void CMusicManagerDlg::OnHScroll(UINT nSBCode,
								 UINT nPos,
								 CScrollBar* pScrollBar)
{
	// call base method
	CExtDialog::OnHScroll(nSBCode,
						  nPos,
						  pScrollBar);

	// check scrollbar
	if(pScrollBar)
		if(pScrollBar==(CScrollBar*)g_lpAudioPosSld)
		{
			// relay message
			g_lpAudioPosSld->OnHScroll(nSBCode,
									   nPos,
									   pScrollBar);
		}
}

// CMusicManagerDlg::OnPlayBtnClk()

void CMusicManagerDlg::OnPlayBtnClk(void)
{
	// reset error flag
	BOOL bErr=FALSE;

	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// set no-update
		g_bNoAudioPosUpdate=TRUE;

		// check pause flag
		if(g_bAudioPause)
		{
			// resume playback
			if(MCIWndPlayFrom(g_hMCIWnd,
							  MCIWndGetPosition(g_hMCIWnd))!=0)
				bErr=TRUE;
		}
		else
		{
			// begin playback
			if(MCIWndPlay(g_hMCIWnd)!=0)
				bErr=TRUE;
		}

		// check for error
		if(bErr)
		{
			// display error
			DisplayMCIErrorMessage();
		}
		else
		{
			// disable play
			g_lpPlayBtn->Disable();
			
			// enable pause/stop
			g_lpPauseBtn->Enable();
			g_lpStopBtn->Enable();

			// clear pause flag
			g_bAudioPause=FALSE;
		}

		// clear no-update
		g_bNoAudioPosUpdate=FALSE;

		// update timer
		UpdateAudioTimer();
	}
}

// CMusicManagerDlg::OnPauseBtnClk()

void CMusicManagerDlg::OnPauseBtnClk(void)
{
	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// set no-update
		g_bNoAudioPosUpdate=TRUE;

		// set pause flag
		g_bAudioPause=TRUE;

		// stop device
		if(MCIWndStop(g_hMCIWnd)!=0)
		{
			// display error
			DisplayMCIErrorMessage();

			// clear pause flag
			g_bAudioPause=FALSE;
		}
		else
		{
			// disable pause
			g_lpPauseBtn->Disable();

			// enable play
			g_lpPlayBtn->Enable();
		}

		// clear no-update
		g_bNoAudioPosUpdate=FALSE;

		// update timer
		UpdateAudioTimer();
	}
}

// CMusicManagerDlg::OnStopBtnClk()

void CMusicManagerDlg::OnStopBtnClk(void)
{
	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// set no-update
		g_bNoAudioPosUpdate=TRUE;

		// stop device
		if(MCIWndStop(g_hMCIWnd)!=0)
		{
			// display error
			DisplayMCIErrorMessage();
		}
		else
		{
			// disable pause/stop
			g_lpPauseBtn->Disable();
			g_lpStopBtn->Disable();

			// enable play
			g_lpPlayBtn->Enable();

			// clear pause flag
			g_bAudioPause=FALSE;

			// perform full rewind
			OnFullRewBtnClk();
		}

		// clear no-update
		g_bNoAudioPosUpdate=FALSE;

		// update timer
		UpdateAudioTimer();
	}
}

// CMusicManagerDlg::OnFullRewBtnClk()

void CMusicManagerDlg::OnFullRewBtnClk(void)
{
	// current mode
	long lMode;

	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// set no-update
		g_bNoAudioPosUpdate=TRUE;

		// get mode
		lMode=MCIWndGetMode(g_hMCIWnd,
							NULL,
							NULL);

		// check for play mode
		if(lMode==MCI_MODE_PLAY)
		{
			// resume playing
			MCIWndPlayFrom(g_hMCIWnd,
						   g_lpAudioPosSld->GetRangeMin());
		}
		else
		{
			// seek to start
			if(MCIWndSeek(g_hMCIWnd,
						  g_lpAudioPosSld->GetRangeMin())!=0)
			{
				// display error
				DisplayNEMCIErrorMessage();
			}
		}

		// clear no-update
		g_bNoAudioPosUpdate=FALSE;

		// update timer
		UpdateAudioTimer();
	}
}

// CMusicManagerDlg::OnRewBtnClk()

void CMusicManagerDlg::OnRewBtnClk(void)
{
	// positon values
	int nMinPos;
	int nCurPos;
	int nNewPos;

	// page size
	int nPageSz;

	// current mode
	long lMode;

	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// set no-update
		g_bNoAudioPosUpdate=TRUE;

		// get position values
		nMinPos=g_lpAudioPosSld->GetRangeMin();
		nCurPos=g_lpAudioPosSld->GetPos();

		// get page size
		nPageSz=g_lpAudioPosSld->GetPageSize();

		// set new position
		nNewPos=nCurPos-nPageSz;

		// check for overflow
		if(nNewPos<nMinPos)
			nNewPos=nMinPos;

		// get mode
		lMode=MCIWndGetMode(g_hMCIWnd,
							NULL,
							NULL);

		// check for play mode
		if(lMode==MCI_MODE_PLAY)
		{
			// resume playing
			MCIWndPlayFrom(g_hMCIWnd,
						   nNewPos);
		}
		else
		{
			// update position
			if(MCIWndSeek(g_hMCIWnd,
						  nNewPos)!=0)
			{
				// display error
				DisplayNEMCIErrorMessage();
			}
		}

		// clear no-update
		g_bNoAudioPosUpdate=FALSE;

		// update timer
		UpdateAudioTimer();
	}
}

// CMusicManagerDlg::OnFwdBtnClk()

void CMusicManagerDlg::OnFwdBtnClk(void)
{
	// positon values
	int nMaxPos;
	int nCurPos;
	int nNewPos;

	// page size
	int nPageSz;

	// current mode
	long lMode;

	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// set no-update
		g_bNoAudioPosUpdate=TRUE;

		// get position values
		nMaxPos=g_lpAudioPosSld->GetRangeMax();
		nCurPos=g_lpAudioPosSld->GetPos();

		// get page size
		nPageSz=g_lpAudioPosSld->GetPageSize();

		// set new position
		nNewPos=nCurPos+nPageSz;

		// check for overflow
		if(nNewPos>nMaxPos)
			nNewPos=nMaxPos;

		// get mode
		lMode=MCIWndGetMode(g_hMCIWnd,
							NULL,
							NULL);

		// check for play mode
		if(lMode==MCI_MODE_PLAY)
		{
			// resume playing
			MCIWndPlayFrom(g_hMCIWnd,
						   nNewPos);
		}
		else
		{
			// update position
			if(MCIWndSeek(g_hMCIWnd,
						  nNewPos)!=0)
			{
				// display error
				DisplayNEMCIErrorMessage();
			}
		}

		// clear no-update
		g_bNoAudioPosUpdate=FALSE;

		// update timer
		UpdateAudioTimer();
	}
}

// CAudioInfoBox::OnSetFocus()

void CAudioInfoBox::OnSetFocus(CWnd* pOldWnd)
{
	// give focus to file list
	g_lpAudioFileList->SetFocus();
}

// CAudioInfoBox::OnSetCursor()

BOOL CAudioInfoBox::OnSetCursor(CWnd* pWnd,
								UINT nHitTest,
								UINT message)
{
	// refuse to change cursor
	return(FALSE);
}

// UpdateAudioPosText()

void UpdateAudioPosText(long lTimeCur)
{
	// timer strings
	char lpStr1[32];
	char lpStr2[16];

	// get timer range
	long lTimeMin=g_lpAudioPosSld->GetRangeMin();
	long lTimeMax=g_lpAudioPosSld->GetRangeMax();

	// check current time
	if(lTimeCur==-1)
	{
		// get current position
		lTimeCur=g_lpAudioPosSld->GetPos();
	}

	// get current time string
	GetHmsStringFromMsVal(lpStr1,
						  lTimeCur-lTimeMin);

	// add "/"
	strcat(lpStr1,"/");

	// get end time string
	GetHmsStringFromMsVal(lpStr2,
						  lTimeMax-lTimeMin);

	// add to string
	strcat(lpStr1,
		   lpStr2);

	// update text
	g_lpAudioPosTxt->SetWindowText(lpStr1);
}

// CAudioPosSlider::OnHScroll()

void CAudioPosSlider::OnHScroll(UINT nSBCode,
								UINT nPos,
								CScrollBar* pScrollBar)
{
	// new positon
	int nNewPos;

	// current mode
	static long lMode=NULL;

	// call base method
	CExtSliderCtrl::OnHScroll(nSBCode,
							  nPos,
							  pScrollBar);

	// check for device
	if(g_nCurAudioDevID)
	{
		// check notification code
		switch(nSBCode)
		{
		// user tracking
		case(TB_THUMBTRACK):

			// check mode
			if(!lMode)
			{
				// set no-update
				g_bNoAudioPosUpdate=TRUE;

				// get mode
				lMode=MCIWndGetMode(g_hMCIWnd,
									NULL,
									NULL);

				// check for play mode
				if(lMode==MCI_MODE_PLAY)
				{
					// set pause flag
					g_bAudioPause=TRUE;

					// stop output
					MCIWndStop(g_hMCIWnd);
				}
			}

			// update position text
			UpdateAudioPosText();

			// ok
			break;

		// update now
		default:

			// wait for timeout
			WaitForAudioTimeout();

			// set no-update
			g_bNoAudioPosUpdate=TRUE;

			// check mode
			if(!lMode)
			{
				// get mode
				lMode=MCIWndGetMode(g_hMCIWnd,
									NULL,
									NULL);
			}

			// get new position
			nNewPos=GetPos();

			// check for play mode
			if(lMode==MCI_MODE_PLAY)
			{
				// resume playing
				MCIWndPlayFrom(g_hMCIWnd,
							   nNewPos);

				// clear pause flag
				g_bAudioPause=FALSE;
			}
			else
			{
				// update position
				if(MCIWndSeek(g_hMCIWnd,
							  nNewPos)!=0)
				{
					// display error
					DisplayNEMCIErrorMessage();
				}
			}

			// clear mode
			lMode=NULL;

			// clear no-update
			g_bNoAudioPosUpdate=FALSE;

			// ok
			break;
		}

		// update timer
		UpdateAudioTimer();
	}
}

// CMusicManagerDlg::OnPListUpBtnClk()

void CMusicManagerDlg::OnPListUpBtnClk(void)
{
	// relay message
	g_lpAudioPList->MoveSelUp();
}

// CMusicManagerDlg::OnPListTopBtnClk()

void CMusicManagerDlg::OnPListTopBtnClk(void)
{
	// relay message
	g_lpAudioPList->MoveSelTop();
}

// CMusicManagerDlg::OnPListDownBtnClk()

void CMusicManagerDlg::OnPListDownBtnClk(void)
{
	// relay message
	g_lpAudioPList->MoveSelDown();
}

// CMusicManagerDlg::OnPListBottomBtnClk()

void CMusicManagerDlg::OnPListBottomBtnClk(void)
{
	// relay message
	g_lpAudioPList->MoveSelBottom();
}

// CMusicManagerDlg::OnPListDeleteBtnClk()

void CMusicManagerDlg::OnPListDeleteBtnClk(void)
{
	// relay message
	g_lpAudioPList->DeleteSel();
}

// CMusicManagerDlg::OnPListClearBtnClk()

void CMusicManagerDlg::OnPListClearBtnClk(void)
{
	// relay message
	g_lpAudioPList->ClearList();
}

// CMusicManagerDlg::OnPListSaveBtnClk()

void CMusicManagerDlg::OnPListSaveBtnClk(void)
{
	LockGlobalErrorMsg()
	
	// save file
	if(g_lpAudioPList->SaveListFile(GetAudioPListFilterList(),
									"Save ProSaverAudio Playlist",
									"Path_AudioPList",
									"PSAL",
									"apl",
									g_lpErrorMsg))
	{
		// copy last-saved playlist
		if(g_lpLastSavedPList)
			strcpy(g_lpLastSavedPList,
				   g_lpErrorMsg);

		// reset list index
		SetAudioPListValues(g_lpErrorMsg,
						    0,
						    -1);
	}

	UnlockGlobalErrorMsg()
}

// CMusicManagerDlg::OnPListLoadBtnClk()

void CMusicManagerDlg::OnPListLoadBtnClk(void)
{
	// message box result
	int nMBRes;

	// check item count
	if(g_lpAudioPList->GetItemCount())
	{
		// check saved flag
		if(!g_lpAudioPList->bIsSaved)
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
				OnPListSaveBtnClk();

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

	// just to verify
	LockGlobalErrorMsg()
	UnlockGlobalErrorMsg()

	// relay command
	g_lpAudioPList->LoadListFile(GetAudioPListFilterList(),
								 "Load ProSaver Audio Playlist",
								 "Path_AudioPList",
								 CheckAudioPListFileCallback,
								 g_lpErrorMsg);

	// check flag
	if(g_bInvPListItems)
		AlertInvAudioPlaylistItems();
}

// AlertInvAudioPlaylistItems()

void AlertInvAudioPlaylistItems(void)
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
	if(!g_lpAudioPList)
		return;

	// get max items
	nMaxItems=g_lpAudioPList->GetItemCount();

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
		if(g_lpAudioPList->GetPlaylistItemData(nCount,
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
							"MsgBox_RemoveInv2")==IDYES)
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
							 "MsgBox_InvGrayed2");
	}
}

// CAudioPlaylist::OnNotify()

BOOL CAudioPlaylist::OnNotify(WPARAM wParam,
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

			// get window text
			if(!::GetWindowText(lpTTCD->nmcd.hdr.hwndFrom,
								g_lpTTMsg,
								_MAX_PATH-1))
				return(TRUE);
			
			// compute new rect
			if(!DrawText(lpTTCD->nmcd.hdc,
						 g_lpTTMsg,
						 -1,
						 &lpTTCD->nmcd.rc,
						 lpTTCD->uDrawFlags|DT_CALCRECT))
				return(TRUE);
			
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

// CAudioPlaylist::OnItemChanged()

void CAudioPlaylist::OnItemChanged(NMHDR* pNMHDR,
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
		// check file list
		if(g_lpAudioFileList)
		{
			// check window
			if(IsWindow(g_lpAudioFileList->m_hWnd))
			{
				// check selection
				if(g_lpAudioFileList->QuerySelection())
				{
					// get selection
					nSel=g_lpAudioFileList->GetSelection();

					// compare item data
					if(PlaylistDataMatchesAudioItemData(lpPD->lpUserData,
														(LPVOID)g_lpAudioFileList->GetItemData(nSel)))
						bItemsAreEqual=TRUE;
					else
						bItemsAreEqual=FALSE;
				}
			}
		}
	}
	else
	{
		// clear playlist data
		lpPD=NULL;
	}

	// new selection
	if(lpLV->uNewState&LVIS_SELECTED&&
	   !(lpLV->uOldState&LVIS_SELECTED))
	{
		// check item data
		if(lpPD)
		{
			// check equal items
			if(!bItemsAreEqual)
			{
				// clear file list selection
				g_lpAudioFileList->SetItemState(nSel,
												NULL,
												LVIS_SELECTED);
			}
			else
			{
				// enable buttons
				g_lpClearAudioSelBtn->Enable();
				g_lpAddAudioFileBtn->Enable();
			}

			// save as current
			SetCurrentAudio((LPFILELISTDATA)lpPD->lpUserData);
		}
		else
		{
			// clear current audio
			SetCurrentAudio(NULL);
		}
	}
	
	// cleared selection
	if(!(lpLV->uNewState&LVIS_SELECTED)&&
	   lpLV->uOldState&LVIS_SELECTED)
	{
		// check moving flag
		if(!bMoving)
		{
			// check equal items
			if(bItemsAreEqual)
			{
				// clear file list selection
				g_lpAudioFileList->SetItemState(nSel,
												NULL,
												LVIS_SELECTED);
			}

			// clear current audio
			SetCurrentAudio(NULL);
		}
	}

	// call base method
	CPlaylistCtrl::OnItemChanged(pNMHDR,
								 pResult);
}

// CAudioPlaylist::OnKeyDown()

void CAudioPlaylist::OnKeyDown(UINT nChar,
							   UINT nRepCnt,
							   UINT nFlags)
{
	// check for left arrow
	if(nChar==VK_LEFT)
	{
		// nothing special
	}

	// call base method
	CPlaylistCtrl::OnKeyDown(nChar,
							 nRepCnt,
							 nFlags);
}

// CAudioPlaylist::OnSetFocus()

void CAudioPlaylist::OnSetFocus(CWnd* pOldWnd)
{
	// call base method
	CPlaylistCtrl::OnSetFocus(pOldWnd);
}

// CAudioPlaylist::QueryPurgeInv()

void CAudioPlaylist::QueryPurgeInv(void)
{
	// selected item
	int nItem;

	// query user
	if(DisplayMessageBox(g_lpCurMusicMgrDlg->m_hWnd,
						 "All invalid items will be deleted.\n\nAre you sure?",
						 (LPSTR)ApplicationName(),
						 MB_YESNO|MB_ICONWARNING)==IDYES)
	{
		// check for selection
		if(QuerySelection())
		{
			// get selection
			nItem=GetSelection();

			// clear selection
			SetItemState(nItem,
						 NULL,
						 0xFF);
		}

		// purge invalid items
		PurgeInvalid();

		// scroll to top
		EnsureVisible(0,
					  FALSE);

		// set parent modified
		g_lpCurMusicMgrDlg->SetModified();
	}
}

// IsValidMusicFile()

BOOL IsValidMusicFile(LPSTR lpMusic,
					  BOOL bIncPlaylists)
{
#ifdef DEBUG_MODE
	// check for music manager
	if(g_lpCurMusicMgrDlg)
	{
		DisplayInfoMessage("Cannot call IsValidMusicFile() while Music Manager is active!");
		return(FALSE);
	}
#endif

	// check for file
	if(!lpMusic)
	{
		// not valid
		return(FALSE);
	}

	// check for playlist
	if(bIncPlaylists)
		if(IsValidPlaylist(lpMusic))
			return(TRUE);

	// begin wait
	::BeginWaitCursor();

	// open file
	if(MCIWndOpen(g_hMCIWnd,
				  lpMusic,
				  NULL)!=0)
	{
		// wait a bit
		Sleep(AUDIO_TIMEOUT_WAIT);

		// try again
		if(MCIWndOpen(g_hMCIWnd,
					  lpMusic,
					  NULL)!=0)
		{
			// end wait
			::EndWaitCursor();

			// test mp3 output
			if(TestMP3Output(TRUE))
			{
				// bad file
				return(FALSE);
			}
			else
			{
				// can't be sure - allow it
				return(TRUE);
			}
		}
	}

	// wait for it
	Sleep(AUDIO_TIMEOUT_WAIT);

	// close file
	MCIWndClose(g_hMCIWnd);

	// end wait cursor
	::EndWaitCursor();

	// ok
	return(TRUE);
}

// IsValidPlaylist()

BOOL IsValidPlaylist(LPSTR lpMusic)
{
	// check for file
	if(!lpMusic)
	{
		// not valid
		return(FALSE);
	}

	// check file existence
	if(!DoesFileExist(lpMusic))
		return(FALSE);

	// check playlist
	if(IsValidAudioPList(lpMusic))
		return(TRUE);

	// not found
	return(FALSE);
}

// GetAudioItemData()

LPVOID GetAudioItemData(LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetAudioItemData()",
							FALSE);
		return(FALSE);
	}
#endif

	// item data
	LPVOID lpItemData=NULL;

	// add audio data
	AddAudioPlaylistFileData((LPFILELISTDATA*)&lpItemData,
							 g_lpAudioHistoryCbx->lpDirTree,
							 lpStr);

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

// ReleaseAudioPlaylistFileData()

void ReleaseAudioPlaylistFileData(void)
{
	// pointer to file info
	CFileInfo* lpFileInfo=NULL;

	// release objects
	while(g_dwNumAPListFileData)
	{
		// decrement counter
		g_dwNumAPListFileData--;

		// cast pointer to file info
		lpFileInfo=(CFileInfo*)g_lplpAPListFileData[g_dwNumAPListFileData]->lpData;

		// delete info
		if(lpFileInfo)
			lpFileInfo->Delete();

		// free object
		FreeClassObject(lpFileInfo);

		// free file data
		FreeMem((LPVOID*)&g_lplpAPListFileData[g_dwNumAPListFileData]);
	}

	// free list
	if(g_lplpAPListFileData)
		FreeMem((LPVOID*)&g_lplpAPListFileData);
}

// AddAudioPlaylistFileData()

BOOL AddAudioPlaylistFileData(LPFILELISTDATA* lplpFileData,
							  CDirTree* lpParentDirTree,
							  LPSTR lpFile)
{
#ifdef DEBUG_MODE
	// verify pointers
	if(!lplpFileData||
	   !lpParentDirTree)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"AddAudioPlaylistFileData()",
							FALSE);
		return(FALSE);
	}

	// verify string
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"AddAudioPlaylistFileData()",
							FALSE);
		return(FALSE);
	}
#endif

	// item id list
	LPITEMIDLIST lpItemIDList=NULL;

	// pointer to file data
	LPFILELISTDATA lpFLD=NULL;

	// pointer to file info
	CFileInfo* lpFileInfo=NULL;

	// reset return value
	(*lplpFileData)=NULL;

	// check for current list
	if(g_dwNumAPListFileData==0)
	{
		// create list
		if(!AllocMem((LPVOID*)&g_lplpAPListFileData,
					 sizeof(LPFILELISTDATA)))
			return(FALSE);
	}
	else
	{
		// expand list
		if(!ExpandMem((LPVOID*)&g_lplpAPListFileData,
					  sizeof(LPFILELISTDATA)*g_dwNumAPListFileData,
					  sizeof(LPFILELISTDATA)*(g_dwNumAPListFileData+1)))
			return(FALSE);
	}

	// allocate file list data
	if(!AllocMem((LPVOID*)&g_lplpAPListFileData[g_dwNumAPListFileData],
				 sizeof(FILELISTDATA)))
		return(FALSE);

	// copy pointer to file data
	lpFLD=g_lplpAPListFileData[g_dwNumAPListFileData];

	// check new object
	if(!lpFLD)
		return(FALSE);

	// create file info
	AllocClassObject(lpFileInfo,
					 CFileInfo);

	// copy pointer
	lpFLD->lpData=(LPVOID)lpFileInfo;

	// update counter
	g_dwNumAPListFileData++;

	LockGlobalMsg()
	
	// copy path
	strcpy(g_lpMsg,
		   lpFile);

	// get path id list
	lpItemIDList=GetIDListFromPath(g_lpCurMusicMgrDlg->m_hWnd,
								   g_lpMsg,
								   TRUE);

	UnlockGlobalMsg()

	// check for error
	if(!lpItemIDList)
		return(FALSE);

	// add file info
	if(!lpFileInfo->Add(lpParentDirTree,
						lpItemIDList))
		return(FALSE);

	// set flags
	lpFLD->bIsFolder=FALSE;
	lpFLD->bIsLinkToFolder=FALSE;

	// set return value
	(*lplpFileData)=lpFLD;

	// ok
	return(TRUE);
}

// GetAudioSaveData()

BOOL GetAudioSaveData(LPSTR lpStr,
					  LPVOID lpItemData)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetAudioSaveData()",
							FALSE);
		return(FALSE);
	}
#endif

	// cast pointer to file data
	LPFILELISTDATA lpFileData=(LPFILELISTDATA)lpItemData;

	// check for file data
	if(!lpFileData)
		return(FALSE);

	// cast pointer to file info
	CFileInfo* lpFileInfo=(CFileInfo*)lpFileData->lpData;

	// check for file info
	if(!lpFileInfo)
		return(FALSE);
	
	// copy path
	if(!lpFileInfo->GetPath(lpStr))
		return(FALSE);

	// ok
	return(TRUE);
}

// GetAudioTitle()

BOOL GetAudioTitle(LPSTR lpStr,
				   LPVOID lpItemData)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetAudioTitle()",
							FALSE);
		return(FALSE);
	}
#endif

	// cast pointer to file data
	LPFILELISTDATA lpFileData=(LPFILELISTDATA)lpItemData;

	// check for file data
	if(!lpFileData)
		return(FALSE);

	// cast pointer to file info
	CFileInfo* lpFileInfo=(CFileInfo*)lpFileData->lpData;

	// check for file info
	if(!lpFileInfo)
		return(FALSE);

	// copy title
	strcpy(lpStr,
		   lpFileInfo->lpTitle);

	// ok
	return(TRUE);
}

// GetAudioTooltip()

BOOL GetAudioTooltip(LPSTR lpStr,
					 LPVOID lpItemData)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpStr)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetAudioTooltip()",
							FALSE);
		return(FALSE);
	}
#endif

	// cast pointer to file data
	LPFILELISTDATA lpFileData=(LPFILELISTDATA)lpItemData;

	// check for file data
	if(!lpFileData)
		return(FALSE);

	// cast pointer to file info
	CFileInfo* lpFileInfo=(CFileInfo*)lpFileData->lpData;

	// check for file info
	if(!lpFileInfo)
		return(FALSE);

	// check flag
	if(!g_bShowPListPopup)
		return(FALSE);

	LockGlobalLongTTMsg()
	
	// copy extension
	strcpy(g_lpLongTTMsg,
		   lpFileInfo->lpExtension);

	// convert to uppercase
	strupr(g_lpLongTTMsg);

	// prepare text
	strcpy(lpStr,"Name: ");
	strcat(lpStr,lpFileInfo->lpTitle);
	strcat(lpStr,"\nType: ");
	strcat(lpStr,g_lpLongTTMsg);
	strcat(lpStr," File");

	UnlockGlobalLongTTMsg()

	// ok
	return(TRUE);
}

// CAudioSortBox::CAudioSortBox()

CAudioSortBox::CAudioSortBox(UINT nID)
{
	// save id
	nCtrlId=nID;

	// reset flags
	bBoxDown=FALSE;

	// call base constructor
	CExtComboBox::CExtComboBox();
}

// CAudioSortBox::OnCommand()

BOOL CAudioSortBox::OnCommand(WPARAM wParam,
							  LPARAM lParam)
{
	// call base method
	return(CExtComboBox::OnCommand(wParam,
								   lParam));
}

// CAudioSortBox::OnKeyDown()

void CAudioSortBox::OnKeyDown(UINT nChar,
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

// SortAudioPlaylist()

void SortAudioPlaylist(int nCode)
{
	// selected item
	int nItem;

	// check code
	if(nCode==0)
		return;

	// check for selection
	if(g_lpAudioPList->QuerySelection())
	{
		// get selection
		nItem=g_lpAudioPList->GetSelection();

		// clear selection
		g_lpAudioPList->SetItemState(nItem,
									 NULL,
									 0xFF);
	}

	// play sound
	PlaySound(IDR_SORTSND);

	// perform sort
	g_lpAudioPList->SortItems(SortAudioPlaylistCallback,
							  (DWORD)nCode);

	// renumber items
	g_lpAudioPList->RenumberItems();

	// scroll to top
	g_lpAudioPList->EnsureVisible(0,
								  FALSE);

	// set parent modified
	g_lpAudioPList->SetParentModified();
}

// SortAudioPlaylistCallback()

int CALLBACK SortAudioPlaylistCallback(LPARAM lParam1,
									   LPARAM lParam2,
									   LPARAM lParamSort)
{
	// init return value
	int nRet=0;

	// set data indices (indexing system is 1-based)
	int nIndex1=((int)lParam1)-1;
	int nIndex2=((int)lParam2)-1;

	// cast pointers to item data
	LPPLAYLISTDATA lpPD1=&g_lpAudioPList->lpPListData[nIndex1];
	LPPLAYLISTDATA lpPD2=&g_lpAudioPList->lpPListData[nIndex2];

	// pointers to file data
	LPFILELISTDATA lpFD1=NULL;
	LPFILELISTDATA lpFD2=NULL;

	// pointers to file info
	CFileInfo* lpFI1=NULL;
	CFileInfo* lpFI2=NULL;

	// verify item data
	if(lpPD1&&
	   lpPD2)
	{
		// cast pointers to file data
		lpFD1=(LPFILELISTDATA)lpPD1->lpUserData;
		lpFD2=(LPFILELISTDATA)lpPD2->lpUserData;

		// cast pointers to file info
		if(lpFD1) lpFI1=(CFileInfo*)lpFD1->lpData;
		if(lpFD2) lpFI2=(CFileInfo*)lpFD2->lpData;

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

		// by type (asc)
		case(3):

			// check info #1
			if(lpFI1)
			{
				// check info #2
				if(lpFI2)
				{
					// compare extensions
					nRet=stricmp(lpFI1->lpExtension,
								 lpFI2->lpExtension);

					// check result
					if(nRet==0)
					{
						// compare titles
						nRet=stricmp(lpPD1->lpTitle,
									 lpPD2->lpTitle);
					}
				}
				else
				{
					// use #1
					nRet=-1;
				}
			}
			else
			{
				// check info #2
				if(lpFI2)
				{
					// use #2
					nRet=1;
				}
				else
				{
					// compare titles
					nRet=stricmp(lpPD1->lpTitle,
								 lpPD2->lpTitle);
				}
			}

			// ok
			break;

		// by type (des)
		case(4):

			// check info #1
			if(lpFI1)
			{
				// check info #2
				if(lpFI2)
				{
					// compare extensions
					nRet=-stricmp(lpFI1->lpExtension,
								  lpFI2->lpExtension);

					// check result
					if(nRet==0)
					{
						// compare titles
						nRet=-stricmp(lpPD1->lpTitle,
									  lpPD2->lpTitle);
					}
				}
				else
				{
					// use #1
					nRet=-1;
				}
			}
			else
			{
				// check info #2
				if(lpFI2)
				{
					// use #2
					nRet=1;
				}
				else
				{
					// compare titles
					nRet=-stricmp(lpPD1->lpTitle,
								  lpPD2->lpTitle);
				}
			}

			// ok
			break;
		}
	}

	// ok
	return(nRet);
}

// ToggleAudioPListPopupInfo()

void ToggleAudioPListPopupInfo(void)
{
	// toggle value
	g_bShowPListPopup=(g_bShowPListPopup ? FALSE : TRUE);

	// set modified states
	g_lpCurMusicMgrDlg->SetModified();
}

// CMusicManagerDlg::PostInitDialog()

BOOL CMusicManagerDlg::PostInitDialog(void)
{
	// folder info
	CDirTree* lpDirTree=NULL;

	// current file type
	int nFileType;

	// reset folder-shown flag
	BOOL bFolderShown=FALSE;

	// begin wait cursor
	::BeginWaitCursor(this);

	// set modified state (to prevent flashing button)
	SetModified(TRUE);

	// init history box
	if(!g_lpAudioHistoryCbx->Init(this))
	{
		::EndWaitCursor(this);
		return(FALSE);
	}

	// link list to history
	if(!g_lpAudioHistoryCbx->Link(g_lpAudioFileList))
	{
		::EndWaitCursor(this);
		return(FALSE);
	}

	// add file types to box
	if(!g_lpAudioExtGrp->AddToComboBox(g_lpFileTypeCbx))
	{
		::EndWaitCursor(this);
		return(FALSE);
	}

	// get last file type
	nFileType=LoadOptionInt("Music_TypeIdx",
							0,6,
							0);

	// set current file type
	g_lpFileTypeCbx->SetCurSel(nFileType);

	// set as current list
	g_lpCurAudExtList=(CExtensionList*)g_lpFileTypeCbx->GetItemData(nFileType);

	LockGlobalErrorMsg()

	// get current path
	if(LoadOptionString("Music_CurPath",
						g_lpErrorMsg))
	{
		// locate folder
		lpDirTree=g_lpAudioHistoryCbx->lpMyComputer->LocateFolder(g_lpErrorMsg);

		// show folder (if found)
		if(lpDirTree)
			bFolderShown=g_lpAudioFileList->ShowFolder(lpDirTree);
	}

	UnlockGlobalErrorMsg()

	// check folder-shown flag
	if(!bFolderShown)
	{
		// default to 'My Documents'
		if(!g_lpAudioFileList->ShowFolder(1))
		{
			::EndWaitCursor(this);
			return(FALSE);
		}
	}

	// clear modified state
	SetModified(FALSE);

	// end wait cursor
	::EndWaitCursor(this);

	// get window position
	GetWindowRect(&rMMgrWndPos);

	// set update flag
	bUpdatePos=TRUE;

	// check directx
	if(!g_bDXSynthOK)
	{
		// inform user
		DisplayOptMessageBox("Microsoft DirectX version 8.1 or higher has not been found.\n\nThis version of DirectX provides enhanced sound quality for some types of audio files.\n\nClick the 'Download DirectX 8.1' button at any time for more information.",
							 (LPCSTR)ApplicationName(),
							 MB_OK|MB_ICONEXCLAMATION,
							 "MsgBox_NoDX");
	}

	// update enable-hotkeys option
	ToggleAudioHotkeys(FALSE);

	// reset mp3 test
	TestMP3Output(TRUE,
				  TRUE);

	// ok
	return(TRUE);
}

// LoadAudioOptions()

BOOL LoadAudioOptions(void)
{
	// load hotkey flag
	g_bEnableAudioHotkeys=(BOOL)LoadOptionInt("Music_EnableHkeys",
											  0,
											  1,
											  1);

	// load hotkeys
	g_dwNextHky=(DWORD)LoadOptionInt("Music_NextHky",
									 0,
									 -1,
									  (int)(((HOTKEYF_CONTROL|HOTKEYF_EXT)<<16)|VK_RIGHT));
	g_dwVolUpHky=(DWORD)LoadOptionInt("Music_VolUpHky",
									  0,
									  -1,
									  (int)(((HOTKEYF_CONTROL|HOTKEYF_EXT)<<16)|VK_UP));
	g_dwVolDownHky=(DWORD)LoadOptionInt("Music_VolDownHky",
										0,
										-1,
									    (int)(((HOTKEYF_CONTROL|HOTKEYF_EXT)<<16)|VK_DOWN));
	g_dwMuteHky=(DWORD)LoadOptionInt("Music_MuteHky",
									 0,
									 -1,
									 (int)(((HOTKEYF_CONTROL)<<16)|'M'));

	// validate hotkeys
	if(g_dwNextHky   ==g_dwVolUpHky)   g_dwVolUpHky  =NULL;
	if(g_dwNextHky   ==g_dwVolDownHky) g_dwVolDownHky=NULL;
	if(g_dwNextHky   ==g_dwMuteHky)    g_dwMuteHky   =NULL;
	if(g_dwVolUpHky  ==g_dwVolDownHky) g_dwVolDownHky=NULL;
	if(g_dwVolUpHky  ==g_dwMuteHky)    g_dwMuteHky   =NULL;
	if(g_dwVolDownHky==g_dwMuteHky)    g_dwMuteHky   =NULL;

	// load synthesizer flags
	g_bUseDXSynth=(BOOL)LoadOptionInt("Music_UseDXSynth",
									  0,
									  1,
									  1);
	g_bUseDXReverb=(BOOL)LoadOptionInt("Music_UseDXReverb",
									   0,
									   1,
									   1);
	g_bUseDXChorus=(BOOL)LoadOptionInt("Music_UseDXChorus",
									   0,
									   1,
									   1);

	// ok
	return(TRUE);
}

// SaveAudioOptions()

BOOL SaveAudioOptions(void)
{
	// hotkey values
	WORD wNextHky1;
	WORD wNextHky2;
	WORD wVolUpHky1;
	WORD wVolUpHky2;
	WORD wVolDownHky1;
	WORD wVolDownHky2;
	WORD wMuteHky1;
	WORD wMuteHky2;

	// get hotkey values
	g_lpNextHky->GetHotKey(wNextHky1,
						   wNextHky2);
	g_lpVolUpHky->GetHotKey(wVolUpHky1,
							wVolUpHky2);
	g_lpVolDownHky->GetHotKey(wVolDownHky1,
							  wVolDownHky2);
	g_lpMuteHky->GetHotKey(wMuteHky1,
						   wMuteHky2);

	// compute hotkey values
	g_dwNextHky   =(((DWORD)wNextHky2)<<16)   |((DWORD)wNextHky1);
	g_dwVolUpHky  =(((DWORD)wVolUpHky2)<<16)  |((DWORD)wVolUpHky1);
	g_dwVolDownHky=(((DWORD)wVolDownHky2)<<16)|((DWORD)wVolDownHky1);
	g_dwMuteHky   =(((DWORD)wMuteHky2)<<16)   |((DWORD)wMuteHky1);

	// save hotkey flag
	SaveOptionInt("Music_EnableHkeys",
				  (int)g_bEnableAudioHotkeys);

	// save hotkey values
	SaveOptionInt("Music_NextHky",
				  (int)g_dwNextHky);
	SaveOptionInt("Music_VolUpHky",
				  (int)g_dwVolUpHky);
	SaveOptionInt("Music_VolDownHky",
				  (int)g_dwVolDownHky);
	SaveOptionInt("Music_MuteHky",
				  (int)g_dwMuteHky);

	// save synthesizer flags
	SaveOptionInt("Music_UseDXSynth",
				  (int)g_bUseDXSynth);
	SaveOptionInt("Music_UseDXReverb",
				  (int)g_bUseDXReverb);
	SaveOptionInt("Music_UseDXChorus",
				  (int)g_bUseDXChorus);

	// ok
	return(TRUE);
}

// ToggleAudioHotkeys()

void ToggleAudioHotkeys(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bEnableAudioHotkeys=(g_bEnableAudioHotkeys ? FALSE : TRUE);

		// set parent modified
		g_lpCurMusicMgrDlg->SetModified();
	}

	// check flag
	if(g_bEnableAudioHotkeys)
	{
		// set check
		g_lpEnablePBCChk->SetCheck(1);

		// enable controls
		g_lpNextHkyTxt->Enable();
		g_lpNextHky->Enable();
		g_lpVolUpHkyTxt->Enable();
		g_lpVolUpHky->Enable();
		g_lpVolDownHkyTxt->Enable();
		g_lpVolDownHky->Enable();
		g_lpMuteHkyTxt->Enable();
		g_lpMuteHky->Enable();

		// alert user to possible confusion
		if(bUpdate)
			DisplayOptMessageBox("Please note that Screensaver Playback controls only work during screensaver playback.\n\nThey will have no effect during Music Manager playback.",
								 (LPCSTR)ApplicationName(),
								 MB_OK|MB_ICONEXCLAMATION,
								 "MsgBox_PlaybackOnly");
	}
	else
	{
		// clear check
		g_lpEnablePBCChk->SetCheck(0);

		// disable controls
		g_lpNextHkyTxt->Disable();
		g_lpNextHky->Disable();
		g_lpVolUpHkyTxt->Disable();
		g_lpVolUpHky->Disable();
		g_lpVolDownHkyTxt->Disable();
		g_lpVolDownHky->Disable();
		g_lpMuteHkyTxt->Disable();
		g_lpMuteHky->Disable();
	}
}

// CMusicManagerDlg::OnEnablePBCChkClk()

void CMusicManagerDlg::OnEnablePBCChkClk(void)
{
	// toggle hotkeys
	ToggleAudioHotkeys();
}

// CMusicManagerDlg::OnWinSynthRadClk()

void CMusicManagerDlg::OnWinSynthRadClk(void)
{
	// set windows synth
	SetWinSynth();
}

// CMusicManagerDlg::OnDXSynthRadClk()

void CMusicManagerDlg::OnDXSynthRadClk(void)
{
	// set directx synth
	SetDXSynth();
}

// CMusicManagerDlg::OnReverbChkClk()

void CMusicManagerDlg::OnReverbChkClk(void)
{
	// toggle reverb
	ToggleReverb();
}

// CMusicManagerDlg::OnChorusChkClk()

void CMusicManagerDlg::OnChorusChkClk(void)
{
	// toggle chorus
	ToggleChorus();
}

// SetWinSynth()

BOOL SetWinSynth(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// clear flag
		g_bUseDXSynth=FALSE;

		// set parent modified
		g_lpCurMusicMgrDlg->SetModified();
	}

	// update buttons
	g_lpWinSynthRad->SetCheck(1);
	g_lpDXSynthRad->SetCheck(0);

	// disable options
	g_lpDXFXTxt->Disable();
	g_lpReverbChk->Disable();
	g_lpChorusChk->Disable();

	// ok
	return(TRUE);
}

// SetDXSynth()

BOOL SetDXSynth(BOOL bUpdate)
{
	// check availability
	if(!g_bDXSynthOK)
		return(SetWinSynth(bUpdate));

	// check update flag
	if(bUpdate)
	{
		// set flag
		g_bUseDXSynth=TRUE;

		// set parent modified
		g_lpCurMusicMgrDlg->SetModified();
	}

	// update buttons
	g_lpWinSynthRad->SetCheck(0);
	g_lpDXSynthRad->SetCheck(1);

	// enable options
	g_lpDXFXTxt->Enable();
	g_lpReverbChk->Enable();
	g_lpChorusChk->Enable();

	// ok
	return(TRUE);
}

// ToggleReverb()

void ToggleReverb(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// toggle value
		g_bUseDXReverb=(g_bUseDXReverb ? FALSE : TRUE);

		// set parent modified
		g_lpCurMusicMgrDlg->SetModified();
	}

	// update button
	g_lpReverbChk->SetCheck(g_bUseDXReverb ? 1 : 0);
}

// ToggleChorus()

void ToggleChorus(BOOL bUpdate)
{
	// check update flag
	if(bUpdate)
	{
		// toggle value
		g_bUseDXChorus=(g_bUseDXChorus ? FALSE : TRUE);

		// set parent modified
		g_lpCurMusicMgrDlg->SetModified();
	}

	// update button
	g_lpChorusChk->SetCheck(g_bUseDXChorus ? 1 : 0);
}

// CMusicManagerDlg::OnHelpBtnClk()

void CMusicManagerDlg::OnHelpBtnClk(void)
{
	// show help
	ShowHelp(IDC_MUSICMGRDLG,
			 NULL);
}		

// CMusicManagerDlg::OnInstallDXBtnClk()

void CMusicManagerDlg::OnInstallDXBtnClk(void)
{
	// check flag
	if(g_bDXSynthOK)
	{
		// hide window
		g_lpInstallDXBtn->ShowWindow(SW_HIDE);

		// stop here
		return;
	}

	// display information
	if(DisplayMessageBox(m_hWnd,
						 "You will now be directed to the WaveBreak Software website, where you can download\nand install DirectX 8.1. (You must be connected to the Internet to download the file.)\n\nAfter installation is complete, you will need to exit and restart ProSaver Screensaver Manager.",
						 (LPSTR)ApplicationName(),
						 MB_OKCANCEL|MB_ICONINFORMATION)==IDOK)
	{
		// show wait cursor
		::BeginWaitCursor();

		// go to website
		OpenExternalDoc("http://www.wb-software.com/directx.htm");

		// hide wait cursor
		::EndWaitCursor();
	}
}

// SetAudioPListValues()

BOOL SetAudioPListValues(LPSTR lpFile,
						int nNextPlay,
						int nLastValid)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"SetAudioPListValues()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// registry path string
	LPSTR lpRegPath=NULL;

	// reset return value
	BOOL bRet=FALSE;

	// output value
	DWORD dwOutput;

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
		   "APListIndex");

	// open registry key
	if(lpRegKey->Create(HKEY_CURRENT_USER,
						g_lpLongMsg,
						REG_NONE,
						REG_OPTION_NON_VOLATILE,
						KEY_ALL_ACCESS,
						NULL,
						NULL)==ERROR_SUCCESS)
	{
		AddWinResource

		// covert path to reg-safe
		if(MakeSafeRegString(lpFile,
							 &lpRegPath))
		{
			// compute output
			dwOutput=(DWORD)((nNextPlay&0xFFFF)|((nLastValid&0xFFFF)<<16));

			// set value
			if(lpRegKey->SetValue(dwOutput,
								  lpRegPath)==ERROR_SUCCESS)
			{
				// set return value
				bRet=TRUE;
			}

			// free reg-safe path
			FreeMem((LPVOID*)&lpRegPath);
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
	
// GetAudioPListValues()

BOOL GetAudioPListValues(LPSTR lpFile,
						 int* lpnNextPlay,
						 int* lpnLastValid)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetAudioPListValues()",
							FALSE);
		return(FALSE);
	}
#endif

	// registry key interface
	CRegKey* lpRegKey=NULL;

	// registry path string
	LPSTR lpRegPath=NULL;

	// input value
	DWORD dwInput;

	// reset return value
	BOOL bRet=FALSE;

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
		   "APListIndex");

	// open registry key
	if(lpRegKey->Open(HKEY_CURRENT_USER,
					  g_lpMsg)==ERROR_SUCCESS)
	{
		AddWinResource

		// covert path to reg-safe
		if(MakeSafeRegString(lpFile,
							 &lpRegPath))
		{
			// get value
			if(lpRegKey->QueryValue(dwInput,
								    lpRegPath)==ERROR_SUCCESS)
			{
				// set return value
				bRet=TRUE;
			}

			// free reg-safe path
			FreeMem((LPVOID*)&lpRegPath);
		}

		// close registry key
		if(lpRegKey->Close()==ERROR_SUCCESS)
			RemoveWinResource
	}

	// relese key interface
	FreeClassObject(lpRegKey);

	// check result
	if(bRet)
	{
		// extract values
		if(lpnNextPlay)  (*lpnNextPlay) =(int)LOWORD(dwInput);
		if(lpnLastValid) (*lpnLastValid)=(int)HIWORD(dwInput);
	}
	else
	{
		// set defaults
		if(lpnNextPlay)  (*lpnNextPlay) =0;
		if(lpnLastValid) (*lpnLastValid)=-1;
	}

	// return result
	return(bRet);
}

// GetAudioPListFile()

BOOL GetAudioPListFile(LPSTR lpPListFile,
					   int nIndex,
					   LPSTR lpAudioFile)
{
#ifdef DEBUG_MODE
	// verify strings
	if(!lpPListFile||
	   !lpAudioFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetAudioPListFile()",
							FALSE);
		return(FALSE);
	}
#endif

	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// item count
	int nItemCount;

	// string length
	WORD wStrLen;

	// reset return value
	BOOL bRet=FALSE;

	// open file for input
	hFile=CreateFile(lpPListFile,
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
		DisplayNEErrorMessage("Unable to open the selected playlist:",
							  lpPListFile);
	}
	else
	{
		AddWinResource

		// move pointer to item count
		if(!MoveFilePointer(hFile,
							4))
			goto GetAudioPListFile1;

		// get item count
		if(!ReadFileEnc(hFile,
						&nItemCount,
						sizeof(int)))
			goto GetAudioPListFile1;

		// check index
		if(nIndex<0||
		   nIndex>=nItemCount)
			goto GetAudioPListFile1;

		// loop through items
		while(TRUE)
		{
			// skip index value
			if(!MoveFilePointer(hFile,
								1))
				goto GetAudioPListFile1;

			// read default string length
			if(!ReadFileEnc(hFile,
							&wStrLen,
							sizeof(WORD),
							TRUE))
				goto GetAudioPListFile1;

			// skip default string
			if(!MoveFilePointer(hFile,
								wStrLen))
				goto GetAudioPListFile1;

			// skip index value
			if(!MoveFilePointer(hFile,
								1))
				goto GetAudioPListFile1;

			// read save string length
			if(!ReadFileEnc(hFile,
							&wStrLen,
							sizeof(WORD),
							TRUE))
				goto GetAudioPListFile1;

			// check index
			if(nIndex==0)
			{
				// read string
				if(!ReadFileEnc(hFile,
								lpAudioFile,
								wStrLen,
								TRUE))
					goto GetAudioPListFile1;
				
				// set null terminator
				lpAudioFile[wStrLen]=0;

				// set return value
				bRet=TRUE;

				// stop here
				break;
			}
			else
			{
				// skip save string
				if(!MoveFilePointer(hFile,
									wStrLen))
					goto GetAudioPListFile1;

				// decrement counter
				nIndex--;
			}
		}

// error exit point
GetAudioPListFile1:;

		// close file
		if(CloseHandle(hFile))
			RemoveWinResource
	}

	UnlockGlobalLongMsg()

	// ok
	return(bRet);
}

// CAudioPlaylist::OnDblClick()

void CAudioPlaylist::OnDblClick(NMHDR* pNMHDR,
								LRESULT* pResult)
{
	// relay to file list
	g_lpAudioFileList->OnDblClick(pNMHDR,
								  pResult);
}

// CAudioPlaylist::PreTranslateMessage()

BOOL CAudioPlaylist::PreTranslateMessage(MSG* pMsg)
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
		}
	}

	// call base method
	return(CPlaylistCtrl::PreTranslateMessage(pMsg));
}

// CMusicManagerDlg::OnShowWindow()

void CMusicManagerDlg::OnShowWindow(BOOL bShow,
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
			// post init command
			PostCommand(g_lpMainSheet,
						IDM_MUSMAN_INIT);

			// set flag
			bWinShown=TRUE;
		}
	}

	// call base method
	CExtDialog::OnShowWindow(bShow,
							 nStatus);
}

// TestMP3Output()

BOOL TestMP3Output(BOOL bSilent,
				   BOOL bReset)
{
	// object id
	int nObjId;

	// message flag
	static BOOL bMsgShown=FALSE;

	// check for reset
	if(bReset)
	{
		// clear flag
		bMsgShown=FALSE;

		// stop here
		return(TRUE);
	}

	// check temp file
	if(!g_lpAudioTempFile)
		return(FALSE);

	// open file
	if(MCIWndOpen(g_hMCIWnd,
				  g_lpAudioTempFile,
				  NULL)!=0)
	{
		// wait for mci
		Sleep(AUDIO_TIMEOUT_WAIT);

		// try again
		if(MCIWndOpen(g_hMCIWnd,
					  g_lpAudioTempFile,
					  NULL)!=0)
		{
			// check silent flag
			if(!bSilent)
			{
				// check message flag
				if(!bMsgShown)
				{
					// alert user
					DisplayErrorMessage("Another application is using the system's audio resources.",
										"MP3 file operations will be disabled until these become available.");

					// set flag
					bMsgShown=TRUE;
				}
			}

			// no good
			return(FALSE);
		}
	}

	// get valid id
	nObjId=MCIWndGetDeviceID(g_hMCIWnd);

	// wait for ready
	MCIWaitForReady(nObjId);

	// close current file
	MCIWndClose(g_hMCIWnd);
	
	// wait for not-ready
	MCIWaitForNotReady(nObjId);

	// reset message flag
	bMsgShown=FALSE;

	// ok
	return(TRUE);
}

// CreateAudioTempFile()

BOOL CreateAudioTempFile(void)
{
	// data handles
	HRSRC   hRsrc=(HRSRC)INVALID_HANDLE_VALUE;
	HGLOBAL hData=(HGLOBAL)INVALID_HANDLE_VALUE;
	HANDLE  hFile=INVALID_HANDLE_VALUE;

	// data info
	LPVOID lpData  =NULL;
	DWORD  dwDataSz=0;

	// check for existing file
	if(g_lpAudioTempFile)
		return(TRUE);

	// find resource
	hRsrc=FindResource(NULL,
					   MAKEINTRESOURCE(IDR_NULLMP3),
					   "MP3");

	// check result
	if(hRsrc==NULL)
		return(FALSE);

	// load resource
	hData=LoadResource(NULL,
					   hRsrc);

	// check result
	if(hData==NULL)
		return(FALSE);

	// lock resource
	lpData=LockResource(hData);

	// check result
	if(lpData==NULL)
		return(FALSE);

	// get data size
	dwDataSz=SizeofResource(NULL,
							hRsrc);

	// check result
	if(dwDataSz==0)
		return(FALSE);

	LockGlobalLongMsg()

	// get temporary path
	if(FAILED(SHGetSpecialFolderPath(g_hWnd,
									 g_lpLongMsg,
									 CSIDL_APPDATA,
									 FALSE)))
	{
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	// add temp filename
	strcat(g_lpLongMsg,
		   "\\~tmp000.mp3");
	
	// open temp file
	hFile=CreateFile(g_lpLongMsg,
					 GENERIC_WRITE,
					 NULL,
					 NULL,
					 CREATE_ALWAYS,
					 NULL,
					 NULL);

	// check result
	if(hFile==INVALID_HANDLE_VALUE)
	{
		UnlockGlobalLongMsg()
		return(FALSE);
	}
	else
		AddWinResource

	// output file
	if(!WriteFile(hFile,
				  lpData,
				  dwDataSz,
				  TRUE))
	{
		UnlockGlobalLongMsg()
		if(CloseHandle(hFile))
			RemoveWinResource
		return(FALSE);
	}

	// close handle
	if(CloseHandle(hFile))
		RemoveWinResource

	// allocate temp path
	if(!AllocMem((LPVOID*)&g_lpAudioTempFile,
				 strlen(g_lpLongMsg)+1))
	{
		UnlockGlobalLongMsg()
		return(FALSE);
	}

	// copy path
	strcpy(g_lpAudioTempFile,
		   g_lpLongMsg);

	UnlockGlobalLongMsg()

	// ok
	return(TRUE);
}

// DeleteAudioTempFile()

BOOL DeleteAudioTempFile(void)
{
	// return value
	BOOL bRet;

	// check for existing file
	if(!g_lpAudioTempFile)
		return(TRUE);

	// delete file
	bRet=DeleteFile(g_lpAudioTempFile);

	// free path
	FreeMem((LPVOID*)&g_lpAudioTempFile);

	// ok
	return(bRet);
}

// CChangeMusicDlg::OnWmHelp()

LRESULT CChangeMusicDlg::OnWmHelp(WPARAM wParam,
								  LPARAM lParam)
{
	// show help
	ShowHelp(IDC_CHGMUSICDLG,
			 NULL);

	// ok
	return(TRUE);
}

// CMusicManagerDlg::OnWmHelp()

LRESULT CMusicManagerDlg::OnWmHelp(WPARAM wParam,
								   LPARAM lParam)
{
	// show help
	ShowHelp(IDC_MUSICMGRDLG,
			 NULL);

	// ok
	return(TRUE);
}

// GetNextMusicString()

BOOL GetNextMusicString(LPSTR lpPlaylist,
						LPSTR lpStr,
						int* lpnCurId,
						BOOL bCountOnly)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPlaylist)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetNextMusicString()",
							FALSE);
		return(FALSE);
	}

	// check count flag
	if(bCountOnly)
	{
		// verify pointer
		if(!lpnCurId)
		{
			DisplayErrorMessage("Invalid pointer value.",
								"GetNextMusicString()",
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
								"GetNextMusicString()",
								FALSE);
			return(FALSE);
		}
	}
#endif

	// playlist values
	int nNextPlay;
	int nLastValid;

	// check count-only flag
	if(bCountOnly)
	{
		// get count
		return(GetAudioPListItemCount(lpPlaylist,
									  lpnCurId));
	}

	// get playlist values
	GetAudioPListValues(lpPlaylist,
						&nNextPlay,
						&nLastValid);

	// set return id
	if(lpnCurId)
		(*lpnCurId)=nNextPlay;

	// clear string
	lpStr[0]=0;

	// get filename
	GetAudioPListFile(lpPlaylist,
					  nNextPlay,
					  lpStr);

	// check for string
	if(strlen(lpStr)==0)
	{
		// check current id
		if(nNextPlay==0)
		{
			// no audio
			return(FALSE);
		}
		else
		{
			// clear next-play index
			SetAudioPListValues(lpPlaylist,
								0,
								nLastValid);

			// try again
			return(GetNextMusicString(lpPlaylist,
									  lpStr,
									  lpnCurId,
									  bCountOnly));
		}
	}
	else
	{
		// set next-play index
		SetAudioPListValues(lpPlaylist,
							nNextPlay+1,
							nLastValid);

		// ok
		return(TRUE);
	}
}

// GetAudioPListItemCount()

BOOL GetAudioPListItemCount(LPSTR lpPListFile,
							int* lpnCount)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpPListFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"GetAudioPListItemCount()",
							FALSE);
		return(FALSE);
	}

	// verify pointer
	if(!lpnCount)
	{
		DisplayErrorMessage("Invalid pointer value.",
							"GetAudioPListItemCount()",
							FALSE);
		return(FALSE);
	}
#endif

	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// item count
	int nItemCount;

	// reset return value
	BOOL bRet=FALSE;

	// reset output value
	(*lpnCount)=-1;

	// open file for input
	hFile=CreateFile(lpPListFile,
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
		DisplayNEErrorMessage("Unable to open the selected playlist:",
							  lpPListFile);
	}
	else
	{
		AddWinResource

		// move pointer to item count
		if(!MoveFilePointer(hFile,
							4))
			goto GetAudioPListItemCount1;

		// get item count
		if(!ReadFileEnc(hFile,
						&nItemCount,
						sizeof(int)))
			goto GetAudioPListItemCount1;

		// copy value
		(*lpnCount)=nItemCount;

		// set return
		bRet=TRUE;

// error exit point
GetAudioPListItemCount1:;

		// close file
		if(CloseHandle(hFile))
			RemoveWinResource
	}

	UnlockGlobalLongMsg()

	// ok
	return(bRet);
}

// MasterVolume()

BOOL MasterVolume(DWORD dwCmd,
				  LPDWORD lpdwData)
{
	// initialized flag
	static BOOL bIsInit=FALSE;

	// handle to mixer
	static HMIXER hMixer=(HMIXER)INVALID_HANDLE_VALUE;

	// mixer line info
	static MIXERLINE ml;
	
	// mixer line controls
	static MIXERLINECONTROLS mlc;

	// mixer control
	static MIXERCONTROL mc;

	// mixer control details
	MIXERCONTROLDETAILS mcd;
	MIXERCONTROLDETAILS_UNSIGNED mcdu;

	// error result
	MMRESULT mmResult;

	// temporary value
	DWORD dwTemp;

	// check command
	switch(dwCmd)
	{
	// initialize
	case(MV_INIT):

		// check init flag
		if(bIsInit)
			return(TRUE);

		// open mixer
		mmResult=mixerOpen(&hMixer,
						   MIXER_OBJECTF_MIXER,
						   NULL,
						   NULL,
						   NULL);

		// check result
		if(mmResult!=MMSYSERR_NOERROR)
		{
			DisplayNEErrorMessage("Unable to get master volume control.");
			return(FALSE);
		}
		else
			AddWinResource

		// prepare mixer line info
		ml.cbStruct       =sizeof(MIXERLINE);
		ml.dwComponentType=MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;

		// get info
		mmResult=mixerGetLineInfo((HMIXEROBJ)hMixer,
								  &ml,
								  MIXER_GETLINEINFOF_COMPONENTTYPE);

		// check result
		if(mmResult!=MMSYSERR_NOERROR)
		{
			DisplayNEErrorMessage("Unable to get master volume mixer line info.");
			return(FALSE);
		}

		// prepare mixer line controls
		mlc.cbStruct     =sizeof(MIXERLINECONTROLS);
		mlc.dwLineID     =ml.dwLineID;
		mlc.dwControlType=MIXERCONTROL_CONTROLTYPE_VOLUME;
		mlc.cControls    =1;
		mlc.pamxctrl     =&mc;
		mlc.cbmxctrl     =sizeof(MIXERCONTROL);

		// get line contols
		mmResult=mixerGetLineControls((HMIXEROBJ)hMixer,
									  &mlc,
									  MIXER_GETLINECONTROLSF_ONEBYTYPE);

		// check result
		if(mmResult!=MMSYSERR_NOERROR)
		{
			DisplayNEErrorMessage("Unable to get master volume mixer line controls.");
			return(FALSE);
		}

		// set init flag
		bIsInit=TRUE;

		// ok
		return(TRUE);

	// get volume
	case(MV_GET):

#ifdef DEBUG_MODE
		// verify pointer
		if(!lpdwData)
		{
			DisplayErrorMessage("Invalid pointer value.",
								"MasterVolume()",
								FALSE);
			return(FALSE);
		}
#endif

		// reset return value
		(*lpdwData)=0;

		// check init
		if(!bIsInit)
			return(FALSE);

		// prepare control details
		mcd.cbStruct   =sizeof(MIXERCONTROLDETAILS);
		mcd.hwndOwner  =NULL;
		mcd.dwControlID=mc.dwControlID;
		mcd.paDetails  =&mcdu;
		mcd.cbDetails  =sizeof(MIXERCONTROLDETAILS_UNSIGNED);
		mcd.cChannels  =1;

		// get volume
		mmResult=mixerGetControlDetails((HMIXEROBJ)hMixer,
										&mcd,
										MIXER_SETCONTROLDETAILSF_VALUE);

		// check result
		if(mmResult!=MMSYSERR_NOERROR)
		{
			DisplayNEErrorMessage("Unable to get master volume.");
			return(FALSE);
		}

		// copy new value
		(*lpdwData)=mcdu.dwValue;

		// ok
		return(TRUE);

	// set volume
	case(MV_SET):

#ifdef DEBUG_MODE
		// verify pointer
		if(!lpdwData)
		{
			DisplayErrorMessage("Invalid pointer value.",
								"MasterVolume()",
								FALSE);
			return(FALSE);
		}
#endif

		// check init
		if(!bIsInit)
			return(FALSE);

		// clip volume
		if((*lpdwData)>65535)
			(*lpdwData)=65535;

		// prepare control details
		mcdu.dwValue   =(*lpdwData);
		mcd.cbStruct   =sizeof(MIXERCONTROLDETAILS);
		mcd.hwndOwner  =NULL;
		mcd.dwControlID=mc.dwControlID;
		mcd.paDetails  =&mcdu;
		mcd.cbDetails  =sizeof(MIXERCONTROLDETAILS_UNSIGNED);
		mcd.cChannels  =1;

		// set volume
		mmResult=mixerSetControlDetails((HMIXEROBJ)hMixer,
										&mcd,
										MIXER_SETCONTROLDETAILSF_VALUE);

		// check result
		if(mmResult!=MMSYSERR_NOERROR)
		{
			DisplayNEErrorMessage("Unable to set master volume.");
			return(FALSE);
		}

		// ok
		return(TRUE);

	// release
	case(MV_RELEASE):

		// check mixer handle
		if(hMixer!=(HMIXER)INVALID_HANDLE_VALUE&&
		   hMixer!=NULL)
		{
			// close mixer
			mmResult=mixerClose(hMixer);

			// check result
			if(mmResult==MMSYSERR_NOERROR)
			{
				RemoveWinResource

				// clear handle
				hMixer=(HMIXER)INVALID_HANDLE_VALUE;
			}
		}

		// clear init flag
		bIsInit=FALSE;

		// ok
		return(TRUE);

	// save
	case(MV_SAVE):

		// check init
		if(!bIsInit)
			return(FALSE);

		// check for currently saved value
		if(g_bVolumeSaved)
		{
#ifdef DEBUG_MODE
			DisplayErrorMessage("Volume already saved!",
								"MasterVolume()",
								FALSE);
#endif
			return(FALSE);
		}

		// get volume
		if(MasterVolume(MV_GET,
						&dwTemp))
		{
			// save value
			g_dwSavedVolume=dwTemp;

			// set flag
			g_bVolumeSaved=TRUE;

			// ok
			return(TRUE);
		}

		// problem
		return(FALSE);

	// restore
	case(MV_RESTORE):

		// check init
		if(!bIsInit)
			return(FALSE);

		// check for currently saved value
		if(!g_bVolumeSaved)
		{
#ifdef DEBUG_MODE
			DisplayNEErrorMessage("Volume not saved!",
								  "MasterVolume()",
								  FALSE);
#endif
			return(FALSE);
		}

		// set saved volume
		if(MasterVolume(MV_SET,
						&g_dwSavedVolume))
		{
			// reset value
			g_dwSavedVolume=0;

			// clear flag
			g_bVolumeSaved=FALSE;

			// ok
			return(TRUE);
		}

		// problem
		return(FALSE);

	// half volume
	case(MV_HALF):

		// check init
		if(!bIsInit)
			return(FALSE);

		// get volume
		if(!MasterVolume(MV_GET,
						 &dwTemp))
			return(FALSE);

		// cut in half
		dwTemp=(dwTemp>>1);

		// set new volume
		if(!MasterVolume(MV_SET,
		 				 &dwTemp))
			return(FALSE);

		// ok
		return(TRUE);
	}

#ifdef DEBUG_MODE
	// alert error
	DisplayErrorMessage("Invalid command id.",
						"MasterVolume()",
						FALSE);
#endif

	// no good
	return(FALSE);
}

// eof //

// Copyright 2006 WaveBreak Software
