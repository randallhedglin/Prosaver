// Copyright 2006 WaveBreak Software

// svrmgr.cpp -- saver manager functionality

// includes //

#include"main.h"

// on-close timer objects
UINT g_nOnCloseTimerId=0;
LPPROCESS_INFORMATION g_lpOnClosePI=NULL;
LPSVRPLAYINFO g_lpOnCloseSPI=NULL;
// on-timeout timer objects
UINT g_nOnTimeoutTimerId=0;
LPPROCESS_INFORMATION g_lpOnTimeoutPI=NULL;
LPSVRPLAYINFO g_lpOnTimeoutSPI=NULL;
// song-playing flag
BOOL g_bSongPlaying=FALSE;
// dx segment index
DWORD g_dwCurSongSegIdx=NO_OBJECT;
// dx song timer id
UINT g_nDXSongTimerId=NULL;
// dx song was-playing flag
BOOL g_bDXSongWasPlaying=FALSE;

// functions //

// PlaybackSaver()

BOOL PlaybackSaver(LPSVRPLAYINFO lpSPI)
{
#ifdef DEBUG_MODE
	// check playback info
	if(!lpSPI)
	{
		DisplayErrorMessage("Invalid playback info.",
							"PlaybackSaver()",
							FALSE);
		return(FALSE);
	}
#endif

	// process info
	static PROCESS_INFORMATION pi;

#ifdef SHAREWARE_MODE
	// check trial days
	if(g_dwTrialDays==0)
	{
		// only run default saver
		lpSPI->lpSaverInfo=NULL;
	}
#endif

	// init hotkeys
	InitPlaybackHotkeys();

	LockGlobalMsg()

	// begin command line
	strcpy(g_lpMsg,
		   "\"");

	// check saver info
	if(lpSPI->lpSaverInfo==NULL)
	{		
		// copy install path
		strcat(g_lpMsg,
			   g_lpInstPath);

		// add default saver
		strcat(g_lpMsg,
			   "\\ProSaver.exe\" w~4000");

		// no time limit on def saver
		lpSPI->dwMinToPlay=0;
	}
	else
	{
		// copy saver path
		strcat(g_lpMsg,
			   lpSPI->lpSaverInfo->lpPath);

		// add full-screen command
		strcat(g_lpMsg,
			   "\" /s");
	}

	UnlockGlobalMsg()

	// save screensaver flag
	SaveWin9XScreensaverFlag();

	// execute saver
	if(ExecuteExternalApp(g_lpMsg,
						  &pi))
	{
		// wait for init
		WaitForInputIdle(pi.hProcess,
						 INFINITE);

		// init close
		InitOnCloseTimer(PREVIEW_CLOSEDELAY,
						 &pi,
						 lpSPI);

		// init timeout
		InitOnTimeoutTimer(NULL,
						   &pi,
						   lpSPI);

		// check for window
		if(GetWndFromProcess(&pi))
		{
			// hook window messages
			if(CreateSaverHook)
				CreateSaverHook(pi.dwThreadId);

			// check error log
			if(g_lpErrorLog->IsInit())
			{
				LockGlobalErrorMsg()

				// prepare string
				strcpy(g_lpErrorMsg,
					   "Screensaver playback successful: \"");

				// check saver info
				if(lpSPI->lpSaverInfo)
					strcat(g_lpErrorMsg,
						   lpSPI->lpSaverInfo->lpPath);
				else
					strcat(g_lpErrorMsg,
						   "Default Screensaver");

				// complete string
				strcat(g_lpErrorMsg,
					   "\".");

				// output to error log
				g_lpErrorLog->AddString("INFO",
										g_lpErrorMsg);

				// dump error log
				g_lpErrorLog->Dump();

				UnlockGlobalErrorMsg()
			}

			// check music flag
			if(!g_bNoMusic)
			{
				// play next song
				PlayNextSong(lpSPI);
			}

			// restore screensaver flag
			SaveWin9XScreensaverFlag(TRUE);

			// ok
			return(TRUE);
		}
	}

	// stop song
	StopSong();

	// release hotkeys
	ReleasePlaybackHotkeys();

	// check error log
	if(g_lpErrorLog->IsInit())
	{
		LockGlobalErrorMsg()

		// prepare string
		strcpy(g_lpErrorMsg,
			   "Screensaver playback failed: \"");

		// check saver info
		if(lpSPI->lpSaverInfo)
			strcat(g_lpErrorMsg,
				   lpSPI->lpSaverInfo->lpPath);
		else
			strcat(g_lpErrorMsg,
				   "Default Screensaver");

		// complete string
		strcat(g_lpErrorMsg,
			   "\".");

		// output to error log
		g_lpErrorLog->AddString("INFO",
								g_lpErrorMsg);

		// dump error log
		g_lpErrorLog->Dump();

		UnlockGlobalErrorMsg()
	}

	// restore screensaver flag
	SaveWin9XScreensaverFlag(TRUE);

	// no good
	return(FALSE);
}

// InitOnCloseTimer()

void InitOnCloseTimer(UINT nDelay,
					  LPPROCESS_INFORMATION lpPI,
					  LPSVRPLAYINFO lpSPI)
{
	// dummy flag
	BOOL bDummy;

	// check timer
	if(g_nOnCloseTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nOnCloseTimerId);

		// reset id
		g_nOnCloseTimerId=NULL;
	}

	// set screen-saver-running flag
	SystemParametersInfo(SPI_SCREENSAVERRUNNING,
						 TRUE,
						 &bDummy,
						 0);

	// disallow system saver
	g_bAllowWinSaver=FALSE;

	// copy data
	g_lpOnClosePI =lpPI;
	g_lpOnCloseSPI=lpSPI;

	// set close timer
	g_nOnCloseTimerId=::SetTimer(NULL,
								 DUMMY_TIMER_ID,
								 nDelay,
								 OnCloseTimerProc);
}

// InitOnTimeoutTimer()

void InitOnTimeoutTimer(UINT nDelay,
					    LPPROCESS_INFORMATION lpPI,
					    LPSVRPLAYINFO lpSPI)
{
	// dummy flag
	BOOL bDummy;

	// check timer
	if(g_nOnTimeoutTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nOnTimeoutTimerId);

		// reset id
		g_nOnTimeoutTimerId=NULL;
	}

	// check duration
	if(lpSPI->dwMinToPlay==0)
		return;

	// recalculate delay
	nDelay=(int)(lpSPI->dwMinToPlay*60*1000);

	// set screen-saver-running flag
	SystemParametersInfo(SPI_SCREENSAVERRUNNING,
						 TRUE,
						 &bDummy,
						 0);

	// disallow system saver
	g_bAllowWinSaver=FALSE;

	// copy data
	g_lpOnTimeoutPI =lpPI;
	g_lpOnTimeoutSPI=lpSPI;

	// set timeout timer
	g_nOnTimeoutTimerId=::SetTimer(NULL,
								   DUMMY_TIMER_ID,
								   nDelay,
								   OnTimeoutTimerProc);
}

// OnCloseTimerProc()

void CALLBACK OnCloseTimerProc(HWND hWnd,
							   UINT uMsg,
							   UINT idEvent,
							   DWORD dwTime)
{
	// dummy flag
	BOOL bDummy;

	// check for process
	if(!GetWndFromProcess(g_lpOnClosePI))
	{
		// kill timer
		::KillTimer(NULL,
					g_nOnCloseTimerId);

		// reset id
		g_nOnCloseTimerId=NULL;

		// check timeout timer
		if(g_nOnTimeoutTimerId)
		{
			// kill timer
			::KillTimer(NULL,
						g_nOnTimeoutTimerId);

			// reset id
			g_nOnTimeoutTimerId=NULL;
		}

		// stop song
		StopSong();

		// release hotkeys
		ReleasePlaybackHotkeys();

		// clear screen-saver-running flag
		SystemParametersInfo(SPI_SCREENSAVERRUNNING,
							 FALSE,
							 &bDummy,
							 0);

		// allow system saver
		g_bAllowWinSaver=TRUE;

		// check for user-close callback
		if(g_lpOnCloseSPI->lpfnUserCloseCallback)
			g_lpOnCloseSPI->lpfnUserCloseCallback(g_lpOnCloseSPI->dwUserCloseData);
	}
}

// OnTimeoutTimerProc()

void CALLBACK OnTimeoutTimerProc(HWND hWnd,
							     UINT uMsg,
							     UINT idEvent,
							     DWORD dwTime)
{
	// dummy flag
	BOOL bDummy;

	// reset window handle
	hWnd=(HWND)INVALID_HANDLE_VALUE;

	// kill timer
	::KillTimer(NULL,
				g_nOnTimeoutTimerId);

	// reset id
	g_nOnTimeoutTimerId=NULL;

	// check close timer
	if(g_nOnCloseTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nOnCloseTimerId);

		// reset id
		g_nOnCloseTimerId=NULL;
	}

	// stop song
	StopSong();

	// release hotkeys
	ReleasePlaybackHotkeys();

	// save screensaver flag
	SaveWin9XScreensaverFlag();

	// get process window
	hWnd=GetWndFromProcess(g_lpOnTimeoutPI);

	// check handle
	if(hWnd==NULL||
	   hWnd==(HWND)INVALID_HANDLE_VALUE)
	{
#ifdef DEBUG_MODE
		// alert to abnormality
		DisplayInfoMessage("Process terminated!");
#endif

		// terminate process
		TerminateProcess(g_lpOnTimeoutPI->hProcess,
						 NULL);
	}
	else
	{
		// close preview
		SendMessage(hWnd,
					WM_CLOSE,
					NULL,
					NULL);
		
		// wait for idle
		WaitForInputIdle(g_lpOnTimeoutPI->hProcess,
						 INFINITE);

		// get process window
		hWnd=GetWndFromProcess(g_lpOnTimeoutPI);

		// check handle
		if(hWnd)
		{
			// quit preview
			SendMessage(hWnd,
						WM_QUIT,
						NULL,
						NULL);
			
			// wait for idle
			WaitForInputIdle(g_lpOnTimeoutPI->hProcess,
							 INFINITE);

			// check for window
			if(GetWndFromProcess(g_lpOnTimeoutPI))
			{
#ifdef DEBUG_MODE
				// alert to abnormality
				DisplayInfoMessage("Process terminated!");
#endif

				// terminate process
				TerminateProcess(g_lpOnTimeoutPI->hProcess,
								 NULL);
			}
		}
	}
	
	// clear screen-saver-running flag
	SystemParametersInfo(SPI_SCREENSAVERRUNNING,
						 FALSE,
						 &bDummy,
						 0);

	// allow system saver
	g_bAllowWinSaver=TRUE;

	// restore screensaver flag
	SaveWin9XScreensaverFlag(TRUE);

	// check clear-screen flag
	if(g_bClearScreen)
	{
		// hide & show main window
		ShowWindow(g_hWnd,SW_HIDE);
		ShowWindow(g_hWnd,SW_SHOW);
	}

	// check for timeout callback
	if(g_lpOnTimeoutSPI->lpfnTimeoutCallback)
		g_lpOnTimeoutSPI->lpfnTimeoutCallback(g_lpOnTimeoutSPI->dwTimeoutData);
}

// InitRunPSWindow()

BOOL InitRunPSWindow(void)
{
	// load saver info
	if(!LoadScreensaverInfo(TRUE))
		return(FALSE);

	// add window class
	if(!AddRunPSWindowClass())
		return(FALSE);

	// create application window
	g_hWnd=CreateWindowEx(WS_EX_TOPMOST,
						  ApplicationID(APID_RUNPS),
						  WND_PBTITLE,
						  WS_POPUP|
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
		DisplayErrorMessage("Unable to create playback window.");
		return(FALSE);
	}
	else
		AddWinResource;

	// wait for splash screen
	WaitForSplashScreen();

	// clear screen (if req'd)
	ShowWindow(g_hWnd,
			   (g_bClearScreen ? SW_SHOW : SW_HIDE));

	// post init message
	PostCommand(g_hWnd,
				IDM_PBACKWND_INIT);

	// ok
	return(TRUE);
}

// ReleaseRunPSWindow()

void ReleaseRunPSWindow(void)
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
	RemoveRunPSWindowClass();

	// release screensaver info
	ReleaseScreensaverInfo();
}

// AddRunPSWindowClass()

BOOL AddRunPSWindowClass(void)
{
	// create class for this window
	WNDCLASSEX wcx;
	wcx.cbSize       =sizeof(WNDCLASSEX);
	wcx.style        =CS_OWNDC;
	wcx.lpfnWndProc  =RunPSWindowProc;
	wcx.cbClsExtra   =NULL;
	wcx.cbWndExtra   =NULL;
	wcx.hInstance    =g_MainApp.m_hInstance;
	wcx.hIcon        =NULL;
	wcx.hIconSm      =NULL;
	wcx.hCursor      =LoadCursor(NULL,IDC_ARROW);
	wcx.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName =NULL;
	wcx.lpszClassName=ApplicationID(APID_RUNPS);

	// register window class
	if(!RegisterClassEx(&wcx))
		return(FALSE);
	else
		AddWinResource;

	// ok
	return(TRUE);
}

// RemoveRunPSWindowClass()

void RemoveRunPSWindowClass(void)
{
	// un-register class
	if(UnregisterClass(ApplicationID(APID_RUNPS),
					   g_MainApp.m_hInstance))
		RemoveWinResource;
}

// RunPSWindowProc()

LRESULT CALLBACK RunPSWindowProc(HWND hWnd,
								 UINT Msg,
								 WPARAM wParam,
								 LPARAM lParam)
{
	// paint info
	PAINTSTRUCT ps;

	// dummy flag
	BOOL bDummy;

	// check for messages that we are interested in
	switch(Msg)
	{
	// create window
	case(WM_CREATE):

		// set screen-saver-running flag
		SystemParametersInfo(SPI_SCREENSAVERRUNNING,
							 TRUE,
							 &bDummy,
							 0);

		// hide cursor
		while(ShowCursor(FALSE)>=0)
		{}

		// ok
		return(NULL);

	// close message
	case(WM_CLOSE):

		// restore cursor
		while(ShowCursor(TRUE)<0)
		{}

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

	// user has ended session
	case(WM_ENDSESSION):

		// check flags
		if((BOOL)wParam==TRUE||
		   (BOOL)lParam==TRUE)
			ForceImmediateExit();
		
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
		
	// mouse buttons
	case(WM_LBUTTONDOWN):
	case(WM_MBUTTONDOWN):
	case(WM_RBUTTONDOWN):

		// close window (fail-safe)
		SendMessage(g_hWnd,
					WM_CLOSE,
					NULL,
					NULL);

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

			// ok
			return(NULL);
		}

		// ok
		break;

	// window commands
	case(WM_COMMAND):

		// check id
		switch(HIWORD(wParam))
		{
		// initialized
		case(IDM_PBACKWND_INIT):

			// play saver
			PlayNextSaver(g_bCycleSavers ? FALSE : TRUE);

			// ok
			return(NULL);

		// all other commands
		default:

			// ok
			break;
		}

		// ok
		break;

	// mci window notification
	case(MCIWNDM_NOTIFYMODE):

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

		// ok
		return(NULL);

	// hotkey messages
	case(WM_HOTKEY):

		// check hotkey id
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

	// let windows process all other messages
	return(DefWindowProc(hWnd,Msg,wParam,lParam));
}

// PlayNextSaver()

void PlayNextSaver(BOOL bShuffle)
{
	// first bad id
	static int nFirstBadId=-1;

	// saver play info (must be static)
	static SVRPLAYINFO spi;

	// last-played id
	int nLastValidId;

	// current id
	int nCurId;

	// number of ids
	int nNumId;

	// saver info
	CSaverInfo* lpSaverInfo=NULL;

	// check shuffle flag
	if(bShuffle)
	{
		// get number of ids
		if(!GetNextSaverString(NULL,
							   &nNumId,
							   TRUE))
		{
			// run w/o shuffle
			PlayNextSaver(FALSE);

			// stop here
			return;
		}

		// check for none
		if(nNumId<=0)
		{
			// run w/o shuffle
			PlayNextSaver(FALSE);

			// stop here
			return;
		}

		// get new id
		nCurId=rand()%nNumId;

		// get last valid id
		nLastValidId=LoadOptionInt("Savers_LastValid",
								   0,
								   -1,
								   -1);

		// make different from last
		if(nCurId==nLastValidId)
			nCurId++;

		// set next id
		SaveOptionInt("Savers_NextPlay",
					  nCurId);

		// run w/o shuffle
		PlayNextSaver(FALSE);

		// stop here
		return;
	}
	else
	{
		LockGlobalTTMsg()
		
		// get saver string
		if(!GetNextSaverString(g_lpTTMsg,
							   &nCurId,
							   FALSE))
		{
			UnlockGlobalTTMsg()

			// prepare play info
			spi.lpSaverInfo          =NULL;
			spi.dwMinToPlay          =0;
			spi.lpfnTimeoutCallback  =NULL;
			spi.dwTimeoutData        =NULL;
			spi.lpfnUserCloseCallback=ClosePSWindow;
			spi.dwUserCloseData      =NULL;

			// run default saver
			if(!PlaybackSaver(&spi))
				ClosePSWindow(NULL);

			// stop here
			return;
		}

		// find saver
		lpSaverInfo=(CSaverInfo*)g_lpSaverInfo->FindSaver(g_lpTTMsg);

		UnlockGlobalTTMsg()

		// check saver
		if(lpSaverInfo)
		{
			// reset first bad id
			nFirstBadId=-1;

			// save as last good id
			SaveOptionInt("Savers_LastValid",
						  nCurId);

			// prepare play info
			spi.lpSaverInfo          =lpSaverInfo;
			spi.dwMinToPlay          =(g_bMultiSavers ? (DWORD)g_nPlayMinutes : 0);
			spi.lpfnTimeoutCallback  =PlayNextSaverCallback;
			spi.dwTimeoutData        =NULL;
			spi.lpfnUserCloseCallback=ClosePSWindow;
			spi.dwUserCloseData      =NULL;

			// run screensaver
			if(!PlaybackSaver(&spi))
				ClosePSWindow(NULL);

			// stop here
			return;
		}
		else
		{
			// check first bad id
			if(nFirstBadId==-1)
			{
				// save this id
				nFirstBadId=nCurId;

				// try again (do not shuffle!)
				PlayNextSaver(FALSE);

				// stop here
				return;
			}
			else
			{
				// compare with first bad
				if(nFirstBadId==nCurId)
				{
					// prepare play info
					spi.lpSaverInfo          =NULL;
					spi.dwMinToPlay          =0;
					spi.lpfnTimeoutCallback  =NULL;
					spi.dwTimeoutData        =NULL;
					spi.lpfnUserCloseCallback=ClosePSWindow;
					spi.dwUserCloseData      =NULL;

					// run default saver
					if(!PlaybackSaver(&spi))
						ClosePSWindow(NULL);

					// stop here
					return;
				}
				else
				{
					// try again (do not shuffle!)
					PlayNextSaver(FALSE);

					// stop here
					return;
				}
			}
		}
	}
}

// ClosePSWindow()

void ClosePSWindow(DWORD dwData)
{
	// show main window
	ShowWindow(g_hWnd,
			   SW_SHOW);

	// restore cursor
	while(ShowCursor(TRUE)<0)
	{}

	// confirm password
	if(ConfirmScreensaverPassword())
	{
		// send close message
		SendMessage(g_hWnd,
					WM_CLOSE,
					NULL,
					NULL);

		// ok
		return;
	}

	// hide cursor
	while(ShowCursor(FALSE)>=0)
	{}

	// clear screen (if req'd)
	ShowWindow(g_hWnd,
			   (g_bClearScreen ? SW_SHOW : SW_HIDE));

	// post init message
	PostCommand(g_hWnd,
				IDM_PBACKWND_INIT);
}

// PlayNextSaverCallback()

void PlayNextSaverCallback(DWORD dwData)
{
	// post init message
	PostCommand(g_hWnd,
				IDM_PBACKWND_INIT);
}

// SaveWin9XScreensaverFlag()

void SaveWin9XScreensaverFlag(BOOL bRestore)
{
#ifdef DEBUG_MODE
	// init flag
	static BOOL bInit=FALSE;

	// check flags
	if(bRestore&&
	   !bInit)
	{
		DisplayErrorMessage("Cannot restore without saving first!",
							"SaveWin9XScreensaverFlag()",
							FALSE);
		return;
	}
	
	// set init
	bInit=TRUE;
#endif

	// registry key handle
	HKEY hKey=(HKEY)INVALID_HANDLE_VALUE;

	// key value data
	static DWORD dwValType=NULL;
	static DWORD dwValSize=sizeof(DWORD);

	// password flags
	static DWORD dwUsePwdNew=NULL;
	static DWORD dwUsePwdOld=NULL;

	// open password flag key
	if(RegOpenKeyEx(HKEY_CURRENT_USER,
					"Control Panel\\Desktop",
					0,
					KEY_READ,
					&hKey)==ERROR_SUCCESS)
	{
		// check restore flag
		if(!bRestore)
		{
			// read old password flag
			if(RegQueryValueEx(hKey,
							   "ScreenSaveUsePassword",
							   NULL,
							   &dwValType,
							   (LPBYTE)&dwUsePwdOld,
							   &dwValSize)==ERROR_SUCCESS)
			{
				// set new password flag
				RegSetValueEx(hKey,
							  "ScreenSaveUsePassword",
							  NULL,
							  dwValType,
							  (LPBYTE)&dwUsePwdNew,
							  dwValSize);
			}
		}
		else
		{
			// restore old password flag
			RegSetValueEx(hKey,
						  "ScreenSaveUsePassword",
						  NULL,
						  dwValType,
						  (LPBYTE)&dwUsePwdOld,
						  dwValSize);
		}

		// close key
		RegCloseKey(hKey);
	}
}

// PlayNextSong()

void PlayNextSong(LPSVRPLAYINFO lpNewSPI,
				  BOOL bUseShuffleFlag)
{
	// pointer to playback info
	static LPSVRPLAYINFO lpSPI=NULL;

	// playlist flag
	static BOOL bIsPlaylist=FALSE;

	// pointer to music
	static LPSTR lpMusic=NULL;

	// first bad id
	static int nFirstBadId=-1;

	// last-played id
	int nLastValidId;

	// current id
	int nCurId;

	// number of ids
	int nNumId;

	// shuffle flag
	BOOL bShuffle;

	// next-play id
	int nNextPlay;

	// check for new info
	if(lpNewSPI)
	{
		// save info
		lpSPI=lpNewSPI;

		// reset music
		lpMusic=NULL;

		// check for saver info
		if(!lpSPI->lpSaverInfo)
			return;

		// copy music
		lpMusic=lpSPI->lpSaverInfo->lpMusic;

		// check music
		if(lpMusic)
		{
			// set playlist flag
			bIsPlaylist=IsValidAudioPList(lpMusic);

			// check playlist flag
			if(bIsPlaylist)
			{
				// check error log
				if(g_lpErrorLog->IsInit())
				{
					LockGlobalErrorMsg()

					// prepare string
					strcpy(g_lpErrorMsg,
						   ">> Playlist loaded successfully: \"");

					// add filename
					strcat(g_lpErrorMsg,
						   lpMusic);

					// complete string
					strcat(g_lpErrorMsg,
						   "\".");

					// output to error log
					g_lpErrorLog->AddString("INFO",
											g_lpErrorMsg);

					// dump error log
					g_lpErrorLog->Dump();

					UnlockGlobalErrorMsg()
				}
			}
		}
	}

#ifdef DEBUG_MODE
	// check info
	if(!lpSPI)
	{
		DisplayErrorMessage("Invalid playback info.",
							"PlayNextSong()",
							FALSE);
		return;
	}
#endif

	// check for music
	if(!lpMusic)
		return;

	// check for playlist
	if(!bIsPlaylist)
	{
		// play individual song
		PlaySong(lpMusic);

		// stop here
		return;
	}

	// check use-shuffle flag
	if(bUseShuffleFlag)
	{
		// copy flag
		bShuffle=lpSPI->lpSaverInfo->bShuffle;
	}
	else
	{
		// clear flag
		bShuffle=FALSE;
	}

	// check shuffle flag
	if(bShuffle)
	{
		// get number of ids
		if(!GetNextMusicString(lpMusic,
							   NULL,
							   &nNumId,
							   TRUE))
		{
			// run w/o shuffle
			PlayNextSong(NULL,
						 FALSE);

			// stop here
			return;
		}

		// check for none
		if(nNumId<=0)
		{
			// run w/o shuffle
			PlayNextSong(NULL,
						 FALSE);

			// stop here
			return;
		}

		// get new id
		nCurId=rand()%nNumId;

		// get last valid id
		GetAudioPListValues(lpMusic,
							NULL,
							&nLastValidId);

		// make different from last
		if(nCurId==nLastValidId)
			nCurId++;

		// set next id
		SetAudioPListValues(lpMusic,
							nCurId,
							nLastValidId);

		// run w/o shuffle
		PlayNextSong(NULL,
					 FALSE);

		// stop here
		return;
	}
	else
	{
		LockGlobalTTMsg()
		
		// get music string
		if(!GetNextMusicString(lpMusic,
							   g_lpTTMsg,
							   &nCurId,
							   FALSE))
		{
			UnlockGlobalTTMsg()

			// stop here
			return;
		}

		UnlockGlobalTTMsg()

		// play song
		if(PlaySong(g_lpTTMsg))
		{
			// reset first bad id
			nFirstBadId=-1;

			// get next play id
			GetAudioPListValues(lpMusic,
								&nNextPlay,
								NULL);

			// save last valid id
			SetAudioPListValues(lpMusic,
								nNextPlay,
								nCurId);

			// stop here
			return;
		}
		else
		{
			// check first bad id
			if(nFirstBadId==-1)
			{
				// save this id
				nFirstBadId=nCurId;

				// try again (do not shuffle!)
				PlayNextSong(NULL,
							 FALSE);

				// stop here
				return;
			}
			else
			{
				// compare with first bad
				if(nFirstBadId==nCurId)
				{
					// stop here
					return;
				}
				else
				{
					// try again (do not shuffle!)
					PlayNextSong(NULL,
								 FALSE);

					// stop here
					return;
				}
			}
		}
	}
}

// PlaySong()

BOOL PlaySong(LPSTR lpFile)
{
#ifdef DEBUG_MODE
	// verify string
	if(!lpFile)
	{
		DisplayErrorMessage("Invalid string value.",
							"PlaySong()",
							FALSE);
		return(FALSE);
	}
#endif

	// stop any running song
	StopSong();

	// check file
	if(!DoesFileExist(lpFile))
	{
		// check error log
		if(g_lpErrorLog->IsInit())
		{
			LockGlobalErrorMsg()

			// prepare string
			strcpy(g_lpErrorMsg,
				   ">> Audio file not found: \"");

			// add filename
			strcat(g_lpErrorMsg,
				   lpFile);

			// complete string
			strcat(g_lpErrorMsg,
				   "\".");

			// output to error log
			g_lpErrorLog->AddString("INFO",
									g_lpErrorMsg);

			// dump error log
			g_lpErrorLog->Dump();

			UnlockGlobalErrorMsg()
		}

		// stop here
		return(FALSE);
	}

	// begin wait
	::BeginWaitCursor();

	// check dx flag
	if(g_bUseDXSynth)
	{
		// init dx audio
		DXAudioInit(FALSE);

		// attempt to open with dx
		g_dwCurSongSegIdx=AddAudioSegment(lpFile);
	}

	// check dx index
	if(g_dwCurSongSegIdx!=NO_OBJECT)
	{
		// play file
		PlayPrimaryAudioSegment(g_dwCurSongSegIdx);

		// set song timer
		g_nDXSongTimerId=::SetTimer(NULL,
									DUMMY_TIMER_ID,
									500,
									OnDXSongTimerProc);

		// set playing flag
		g_bSongPlaying=TRUE;

		// reset dx was-playing flag
		g_bDXSongWasPlaying=FALSE;

		// check error log
		if(g_lpErrorLog->IsInit())
		{
			LockGlobalErrorMsg()

			// prepare string
			strcpy(g_lpErrorMsg,
				   ">> DirectX Audio file playback successful: \"");

			// add filename
			strcat(g_lpErrorMsg,
				   lpFile);

			// complete string
			strcat(g_lpErrorMsg,
				   "\".");

			// output to error log
			g_lpErrorLog->AddString("INFO",
									g_lpErrorMsg);

			// dump error log
			g_lpErrorLog->Dump();

			UnlockGlobalErrorMsg()
		}

		// end wait
		::EndWaitCursor();

		// stop here
		return(TRUE);
	}

	// open file w/ mci
	if(MCIWndOpen(g_hMCIWnd,
				  lpFile,
				  NULL)!=0)
	{
		// wait for mci
		Sleep(AUDIO_TIMEOUT_WAIT);

		// try again
		if(MCIWndOpen(g_hMCIWnd,
					  lpFile,
					  NULL)!=0)
		{
			// test mp3 output
			TestMP3Output();

			// check error log
			if(g_lpErrorLog->IsInit())
			{
				LockGlobalErrorMsg()

				// prepare string
				strcpy(g_lpErrorMsg,
					   ">> Failed to open audio file: \"");

				// add filename
				strcat(g_lpErrorMsg,
					   lpFile);

				// complete string
				strcat(g_lpErrorMsg,
					   "\".");

				// output to error log
				g_lpErrorLog->AddString("INFO",
										g_lpErrorMsg);

				// dump error log
				g_lpErrorLog->Dump();

				UnlockGlobalErrorMsg()
			}

			// end wait
			::EndWaitCursor();

			// stop here
			return(FALSE);
		}
	}

	// get valid id
	g_nCurAudioDevID=MCIWndGetDeviceID(g_hMCIWnd);

	// wait for ready
	MCIWaitForReady(g_nCurAudioDevID);

	// check for mp3
	if(g_bCurAudioIsMP3)
	{
		// reset mp3 test
		TestMP3Output(TRUE,
					  TRUE);
	}

	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// begin playback
		if(MCIWndPlay(g_hMCIWnd)!=0)
		{
			// display error
			DisplayMCIErrorMessage();

			// check error log
			if(g_lpErrorLog->IsInit())
			{
				LockGlobalErrorMsg()

				// prepare string
				strcpy(g_lpErrorMsg,
					   ">> Failed to play audio file: \"");

				// add filename
				strcat(g_lpErrorMsg,
					   lpFile);

				// complete string
				strcat(g_lpErrorMsg,
					   "\".");

				// output to error log
				g_lpErrorLog->AddString("INFO",
										g_lpErrorMsg);

				// dump error log
				g_lpErrorLog->Dump();

				UnlockGlobalErrorMsg()
			}

			// end wait
			::EndWaitCursor();
	
			// no good
			return(FALSE);
		}
	}

	// set playing flag
	g_bSongPlaying=TRUE;
	
	// check error log
	if(g_lpErrorLog->IsInit())
	{
		LockGlobalErrorMsg()

		// prepare string
		strcpy(g_lpErrorMsg,
			   ">> Audio file playback successful: \"");

		// add filename
		strcat(g_lpErrorMsg,
			   lpFile);

		// complete string
		strcat(g_lpErrorMsg,
			   "\".");

		// output to error log
		g_lpErrorLog->AddString("INFO",
								g_lpErrorMsg);

		// dump error log
		g_lpErrorLog->Dump();

		UnlockGlobalErrorMsg()
	}

	// end wait
	::EndWaitCursor();

	// ok
	return(TRUE);
}

// StopSong()

void StopSong(void)
{
	// begin wait
	::BeginWaitCursor();

	// check for dx timer
	if(g_nDXSongTimerId)
	{
		// kill timer
		::KillTimer(NULL,
					g_nDXSongTimerId);

		// reset id
		g_nDXSongTimerId=NULL;
	}

	// check dx index
	if(g_dwCurSongSegIdx!=NO_OBJECT)
	{
		// stop output
		StopAllAudioSegments();

		// clear playing flags
		g_bSongPlaying     =FALSE;
		g_bDXSongWasPlaying=FALSE;

		// purge segments
		PurgeAudioObjects();

		// clear index
		g_dwCurSongSegIdx=NO_OBJECT;

		// end wait
		::EndWaitCursor();

		// stop here
		return;
	}

	// wait for timeout
	WaitForAudioTimeout();

	// check for device
	if(g_nCurAudioDevID)
	{
		// clear playing flag
		g_bSongPlaying=FALSE;

		// stop device
		if(MCIWndStop(g_hMCIWnd)!=0)
		{
			// display error
			DisplayMCIErrorMessage();
		}

		// check for current file
		if(g_nCurAudioDevID)
		{

			// close current file
			MCIWndClose(g_hMCIWnd);
			
			// wait for not-ready
			MCIWaitForNotReady(g_nCurAudioDevID);

			// clear id
			g_nCurAudioDevID=NULL;
		}

		// end wait
		::EndWaitCursor();

		// stop here
		return;
	}
}

// OnDXSongTimerProc()

void CALLBACK OnDXSongTimerProc(HWND hWnd,
								UINT uMsg,
								UINT idEvent,
								DWORD dwTime)
{
	// check for dx object
	if(g_dwCurSongSegIdx!=NO_OBJECT)
	{
		// check segment
		if(IsAudioSegmentPlaying(g_dwCurSongSegIdx))
		{
			// set was-playing flag
			g_bDXSongWasPlaying=TRUE;
		}
		else
		{
			// check was-playing flag
			if(g_bDXSongWasPlaying)
			{
				// send stop message
				SendMessage(g_hWnd,
							MCIWNDM_NOTIFYMODE,
							NULL,
							MCI_MODE_STOP);
			}
		}
	}
}

// InitPlaybackHotkeys()

BOOL InitPlaybackHotkeys(void)
{
	// reset number failed
	DWORD dwNumFail=0;

	// check flag
	if(g_bEnableHotkeys)
	{
		// register next saver hotkey
		if(!RegisterHotKey(g_hWnd,
						   ID_NEXTSVRHKY,
						   (UINT)HotkeyMods(HIWORD(g_dwSkipSaverHky)),
						   (UINT)LOWORD(g_dwSkipSaverHky)))
			dwNumFail++;
		else
			AddWinResource
	}

	// check flags
	if(g_bEnableAudioHotkeys&&
	   !g_bNoMusic)
	{
		// register next song hotkey
		if(!RegisterHotKey(g_hWnd,
						   ID_NEXTSONGHKY,
						   (UINT)HotkeyMods(HIWORD(g_dwNextHky)),
						   (UINT)LOWORD(g_dwNextHky)))
			dwNumFail++;
		else
			AddWinResource

		// register vol+ hotkey
		if(!RegisterHotKey(g_hWnd,
						   ID_VOLUPHKY,
						   (UINT)HotkeyMods(HIWORD(g_dwVolUpHky)),
						   (UINT)LOWORD(g_dwVolUpHky)))
			dwNumFail++;
		else
			AddWinResource

		// register vol- hotkey
		if(!RegisterHotKey(g_hWnd,
						   ID_VOLDOWNHKY,
						   (UINT)HotkeyMods(HIWORD(g_dwVolDownHky)),
						   (UINT)LOWORD(g_dwVolDownHky)))
			dwNumFail++;
		else
			AddWinResource

		// register mute hotkey
		if(!RegisterHotKey(g_hWnd,
						   ID_VOLMUTEHKY,
						   (UINT)HotkeyMods(HIWORD(g_dwMuteHky)),
						   (UINT)LOWORD(g_dwMuteHky)))
			dwNumFail++;
		else
			AddWinResource
	}

	// check for failures
	if(dwNumFail)
	{
		DisplayNEErrorMessage("Some hotkeys could not be registered with the system.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// ReleasePlaybackHotkeys()

void ReleasePlaybackHotkeys(void)
{
	// unregister hotkeys
	if(UnregisterHotKey(g_hWnd,ID_NEXTSVRHKY))  RemoveWinResource
	if(UnregisterHotKey(g_hWnd,ID_NEXTSONGHKY)) RemoveWinResource
	if(UnregisterHotKey(g_hWnd,ID_VOLUPHKY))    RemoveWinResource
	if(UnregisterHotKey(g_hWnd,ID_VOLDOWNHKY))  RemoveWinResource
	if(UnregisterHotKey(g_hWnd,ID_VOLMUTEHKY))  RemoveWinResource
}

// OnNextSaverHky()

void OnNextSaverHky(void)
{
	// check timer
	if(g_nOnTimeoutTimerId)
	{
		// force timeout
		OnTimeoutTimerProc(NULL,
						   NULL,
						   NULL,
						   NULL);
	}
}

// OnNextSongHky()

void OnNextSongHky(void)
{
	// check for playback mode
	if(g_bSongPlaying)
	{
		// check music flag
		if(!g_bNoMusic)
		{
			// play next song
			PlayNextSong();
		}
	}
}

// OnVolUpHky()

void OnVolUpHky()
{
	// volume value
	DWORD dwVol;

	// get volume
	if(MasterVolume(MV_GET,
					&dwVol))
	{
		// increase volume
		dwVol+=(65536/32);

		// check for overflow
		if(dwVol>65535)
			dwVol=65535;

		// set new volume
		MasterVolume(MV_SET,
					 &dwVol);
	}
}

// OnVolDownHky()

void OnVolDownHky(void)
{
	// volume value
	DWORD dwVol;

	// get volume
	if(MasterVolume(MV_GET,
					&dwVol))
	{
		// decrease volume
		dwVol-=(65536/32);

		// check for overflow
		if(dwVol>65535)
			dwVol=0;

		// set new volume
		MasterVolume(MV_SET,
					 &dwVol);
	}
}

// OnVolMuteHky()

void OnVolMuteHky(void)
{
	// volume value
	DWORD dwVol=0;

	// set zero volume
	MasterVolume(MV_SET,
				 &dwVol);
}

// InitTSRMode()

BOOL InitTSRMode(void)
{
#ifdef SHAREWARE_MODE
	// get trial days remaining
	g_dwTrialDays=GetTrialDaysRemaining();
#endif

	// ensure auto-run
	EnsureTSRModeAutoRun();

	// create window
	if(!CreateTSRModeWindow())
		return(FALSE);

	// init hotkeys
	InitTSRModeHotkeys();

	// ok
	return(TRUE);
}

// ExecTSRMode()

void ExecTSRMode(void)
{
	// use the ol' standby
	ProcessScreensaverMessages();
}

// ReleaseTSRMode()

void ReleaseTSRMode(void)
{
	// release hotkeys
	ReleaseTSRModeHotkeys();

	// destroy window
	DestroyTSRModeWindow();
}

// AddTSRModeWindowClass()

BOOL AddTSRModeWindowClass(void)
{
	// create class for this window
	WNDCLASSEX wcx;
	wcx.cbSize       =sizeof(WNDCLASSEX);
	wcx.style        =CS_OWNDC;
	wcx.lpfnWndProc  =TSRModeWindowProc;
	wcx.cbClsExtra   =NULL;
	wcx.cbWndExtra   =NULL;
	wcx.hInstance    =g_MainApp.m_hInstance;
	wcx.hIcon        =NULL;
	wcx.hIconSm      =NULL;
	wcx.hCursor      =LoadCursor(NULL,IDC_ARROW);
	wcx.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wcx.lpszMenuName =NULL;
	wcx.lpszClassName=ApplicationID(APID_TSRMODE);

	// register window class
	if(!RegisterClassEx(&wcx))
		return(FALSE);
	else
		AddWinResource;

	// ok
	return(TRUE);
}

// ReleaseTSRModeWindowClass()

void ReleaseTSRModeWindowClass(void)
{
	// un-register class
	if(UnregisterClass(ApplicationID(APID_TSRMODE),
					   g_MainApp.m_hInstance))
		RemoveWinResource;
}

// CreateTSRModeWindow()

BOOL CreateTSRModeWindow(void)
{
	// lock application
	if(!LockApplication(ApplicationID(APID_TSRMODE),
						WND_TSRTITLE,
						(LPSTR)ApplicationID(APID_TSRMODE),
						TRUE))
	{
		UnlockGlobalMsg()
		return(FALSE);
	}

	// add window class
	if(!AddTSRModeWindowClass())
		return(FALSE);

	// create window
	g_hWnd=CreateWindowEx(NULL,
						  ApplicationID(APID_TSRMODE),
						  WND_TSRTITLE,
						  WS_POPUP,
						  0,0,
						  0,0,
						  NULL,
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

// DestroyTSRModeWindow()

void DestroyTSRModeWindow(void)
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

	// release window class
	ReleaseTSRModeWindowClass();

	// unlock application
	UnlockApplication();
}

// TSRModeWindowProc()

LRESULT CALLBACK TSRModeWindowProc(HWND hWnd,
								   UINT Msg,
								   WPARAM wParam,
								   LPARAM lParam)
{
	// icon data
	static NOTIFYICONDATA nid;
	
	// system tray flag
	static BOOL bSysTray=FALSE;
	
	// check for messages that we are interested in
	switch(Msg)
	{
	// create window
	case(WM_CREATE):

		// get system tray flag
		bSysTray=(BOOL)LoadOptionInt("Adv_SystemTray",
									 0,
									 1,
									 1);

		// check flag
		if(bSysTray)
		{
			// prepare icon data
			nid.cbSize          =sizeof(NOTIFYICONDATA);
			nid.hWnd            =hWnd;
			nid.uID             =NULL;
			nid.uFlags          =NIF_ICON|
								 NIF_MESSAGE|
								 NIF_TIP;
			nid.uCallbackMessage=IDM_SYSTRAY_EVENT;
			nid.hIcon           =(HICON)LoadImage(g_MainApp.m_hInstance,
												  MAKEINTRESOURCE(IDI_MAINICON),
												  IMAGE_ICON,
												  16,16,
												  LR_DEFAULTCOLOR);

			// set tip text
			strcpy(nid.szTip,
				   "ProSaver Screensaver Manager");

			// set icon
			Shell_NotifyIcon(NIM_ADD,
							 &nid);
		}

		// ok
		return(NULL);

	// close message
	case(WM_CLOSE):

		// check flag
		if(bSysTray)
		{
			// remove icon
			Shell_NotifyIcon(NIM_DELETE,
							 &nid);
		}

		// quit application
		PostMessage(g_hWnd,
					WM_QUIT,
					NULL,
					NULL);
		
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

	// system tray events
	case(IDM_SYSTRAY_EVENT):

		// check message
		switch(lParam)
		{
		case(WM_LBUTTONDBLCLK): OpenProSaverConfig();           break;
		case(WM_RBUTTONDOWN):   ShowPopupMenu(IDC_SYSTRAYICON); break;
		}

		// ok
		return(NULL);

	// commands
	case(WM_COMMAND):

		// check message
		switch(HIWORD(wParam))
		{
		// menu selection
		case(0):

			// check message
			switch(LOWORD(wParam))
			{
			case(IDM_SYSTRY_RUNPS):   RunProSaverExe();              return(0);
			case(IDM_SYSTRY_OPENPS):  OpenProSaverConfig();          return(0);
			case(IDM_SYSTRY_OPENCPL): OpenScreensaverControlPanel(); return(0);
			case(IDM_SYSTRY_HIDEME):  HideTSRIcon();                 return(0);
#ifdef SHAREWARE_MODE
			case(IDM_SYSTRY_PURCH):   RunExternalPurchDlg(); return(0);
#endif
			case(IDM_SYSTRY_DBGEXIT): ::SendMessage(g_hWnd,WM_CLOSE,NULL,NULL); return(0);

			default:
#ifdef DEBUG_MODE
				DisplayErrorMessage("Invalid menu item.",
									"TSRModeWindowProc()",
									FALSE);
#endif
				// ok
				break;
			}

			// ok
			break;
		}

		// ok
		break;

	// hotkey messages
	case(WM_HOTKEY):

		// check hotkey id
		switch(wParam)
		{
		case(ID_STARTSVRHKY): OnStartSaverHky(); break;
		case(ID_OPENPSHKY):   OnOpenPSHky();     break;
		}

		// ok
		return(NULL);
	}

	// let windows process all other messages
	return(DefWindowProc(hWnd,Msg,wParam,lParam));
}

// IsTSRActive()

BOOL IsTSRActive(void)
{
	// window object
	CWnd* lpWnd=NULL;

	// find window
	lpWnd=CWnd::FindWindow(ApplicationID(APID_TSRMODE),
						   WND_TSRTITLE);

	// check window object
	if(lpWnd==NULL)
		return(FALSE);

	// check window
	if(!IsWindow(lpWnd->m_hWnd))
		return(FALSE);

	// active
	return(TRUE);
}

// RestartTSR()

BOOL RestartTSR(void)
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
	strcat(g_lpMsg,"\\ProSaver.exe\" w~5000");

	UnlockGlobalErrorMsg()

	// open config box
	BOOL bRet=ExecuteExternalApp(g_lpMsg,
								 (LPCSTR)NULL);

	UnlockGlobalMsg()

	// ok
	return(bRet);
}

// HideTSRIcon()

BOOL HideTSRIcon(void)
{
	// query user
	if(DisplayMessageBox(g_hWnd,
						 "This command will remove the ProSaver icon from the system tray.\n\nAre you sure?",
						 "ProSaver",
						 MB_YESNO|MB_ICONQUESTION)==IDNO)
		return(FALSE);

	// change setting
	if(!SaveOptionInt("Adv_SystemTray",
					  0))
		return(FALSE);

	// restart tsr
	return(RestartTSR());
}

// InitTSRModeHotkeys()

BOOL InitTSRModeHotkeys(void)
{
	// reset number failed
	DWORD dwNumFail=0;

	// temporary hotkey value
	DWORD dwHkTemp;

#ifdef SHAREWARE_MODE
	// check trial days
	if(g_dwTrialDays==0)
		return(FALSE);
#endif

	// check flag
	if(LoadOptionInt("Play_EnableHotkeys",
					 0,
					 1,
					 1))
	{
		// load start-saver hotkey
		dwHkTemp=(DWORD)LoadOptionInt("Play_StartHky",
									  0,
									  -1,
									  (int)(((HOTKEYF_CONTROL|HOTKEYF_ALT)<<16)|'S'));

		// register start-saver hotkey
		if(!RegisterHotKey(g_hWnd,
						   ID_STARTSVRHKY,
						   (UINT)HotkeyMods(HIWORD(dwHkTemp)),
						   (UINT)LOWORD(dwHkTemp)))
			dwNumFail++;
		else
			AddWinResource

		// load open-ps hotkey
		dwHkTemp=(DWORD)LoadOptionInt("Play_OpenPSHky",
									  0,
									  -1,
									  (int)(((HOTKEYF_CONTROL|HOTKEYF_ALT)<<16)|'P'));

		// register open-ps hotkey
		if(!RegisterHotKey(g_hWnd,
						   ID_OPENPSHKY,
						   (UINT)HotkeyMods(HIWORD(dwHkTemp)),
						   (UINT)LOWORD(dwHkTemp)))
			dwNumFail++;
		else
			AddWinResource
	}

	// check for failures
	if(dwNumFail)
	{
		DisplayNEErrorMessage("Some hotkeys could not be registered with the system.");
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// ReleaseTSRModeHotkeys()

void ReleaseTSRModeHotkeys(void)
{
	// unregister hotkeys
	if(UnregisterHotKey(g_hWnd,ID_STARTSVRHKY)) RemoveWinResource
	if(UnregisterHotKey(g_hWnd,ID_OPENPSHKY))   RemoveWinResource
}

// OnStartSaverHky()

void OnStartSaverHky(void)
{
	// start screensaver
	RunProSaverExe();
}

// OnOpenPSHky()

void OnOpenPSHky(void)
{
	// open config
	OpenProSaverConfig();
}

// EnsureTSRModeAutoRun()

BOOL EnsureTSRModeAutoRun(void)
{
	// just to verify
	LockGlobalTTMsg()
	UnlockGlobalTTMsg()

	// get path to common startup folder
	if(FAILED(SHGetSpecialFolderPath(NULL,
									 g_lpTTMsg,
									 CSIDL_COMMON_STARTUP,
									 TRUE)))
	{
		// try alternate common startup folder
		if(FAILED(SHGetSpecialFolderPath(NULL,
										 g_lpTTMsg,
										 CSIDL_COMMON_ALTSTARTUP,
										 TRUE)))
		{
			// try local startup folder
			if(FAILED(SHGetSpecialFolderPath(NULL,
											 g_lpTTMsg,
											 CSIDL_STARTUP,
											 TRUE)))
			{
				// try alternate local startup folder
				if(FAILED(SHGetSpecialFolderPath(NULL,
												 g_lpTTMsg,
												 CSIDL_ALTSTARTUP,
												 TRUE)))
				{
					DisplayNEErrorMessage("Unable to get path to 'Startup' folder.");
					return(FALSE);
				}
			}
		}
	}

	// check path
	if(strlen(g_lpTTMsg)==0)
	{
		DisplayNEErrorMessage("Invalid path to 'Startup' folder.");
		return(FALSE);
	}

	// append file name
	if(g_lpTTMsg[strlen(g_lpTTMsg)-1]=='\\')
		strcat(g_lpTTMsg,
			   "ProSaver.lnk");
	else
		strcat(g_lpTTMsg,
			   "\\ProSaver.lnk");

	// check file
	if(DoesFileExist(g_lpTTMsg))
	{
		// all is well
		return(TRUE);
	}

	// just to verify
	LockGlobalErrorMsg()
	UnlockGlobalErrorMsg()

	// check for install path
	if(!g_lpInstPath)
	{
		// load prefs
		if(!LoadPreferences())
			return(FALSE);

		// begin string
		strcpy(g_lpErrorMsg,
			   "\"");
		
		// add path
		strcat(g_lpErrorMsg,
			   g_lpInstPath);

		// release install path
		FreeMem((LPVOID*)&g_lpInstPath);
	}
	else
	{
		// begin string
		strcpy(g_lpErrorMsg,
			   "\"");
		
		// add path
		strcat(g_lpErrorMsg,
			   g_lpInstPath);
	}

	// append file name
	if(g_lpErrorMsg[strlen(g_lpErrorMsg)-1]=='\\')
		strcat(g_lpErrorMsg,
			   "ProSaver.exe\"");
	else
		strcat(g_lpErrorMsg,
			   "\\ProSaver.exe\"");

	// set shortcut path
	if(g_lpShellLink->SetPath(g_lpErrorMsg)!=NOERROR)
	{
		DisplayNEErrorMessage("Unable to set shortcut path.");
		return(FALSE);
	}

	// set link arguments
	if(g_lpShellLink->SetArguments("w~5000")!=NOERROR)
	{
		DisplayNEErrorMessage("Unable to set shortcut command line arguments.");
		return(FALSE);
	}

	// set show command
	if(g_lpShellLink->SetShowCmd(SW_SHOWDEFAULT)!=NOERROR)
	{
		DisplayNEErrorMessage("Unable to set shortcut show command.");
		return(FALSE);
	}

	// just to verify
	LockGlobalLongTTMsg()
	UnlockGlobalLongTTMsg()

	// convert shortcut path to wide
	MakeWideString((LPWSTR)g_lpLongTTMsg,
				   g_lpTTMsg);

	// save shortcut file
	if(FAILED(g_lpShellLinkPF->Save((LPCOLESTR)g_lpLongTTMsg,
									TRUE)))
	{
		DisplayNEErrorMessage("Unable to save shortcut file.");
		return(FALSE);
	}

	// clear system-tray flag
	SaveOptionInt("Adv_SystemTray",
				  0);

	// ok
	return(TRUE);
}

// eof //

// Copyright 2006 WaveBreak Software
