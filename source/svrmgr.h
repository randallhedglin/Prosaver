// Copyright 2006 WaveBreak Software

// svrmgr.h -- saver manager functionality header

// constants //

// window titles
#define WND_PBTITLE  "ProSaver Playback Window"
#define WND_TSRTITLE "ProSaver SysTray Window"

// hotkey ids
#define ID_STARTSVRHKY 1
#define ID_NEXTSVRHKY  2
#define ID_OPENPSHKY   3
#define ID_NEXTSONGHKY 4
#define ID_VOLUPHKY    5
#define ID_VOLDOWNHKY  6
#define ID_VOLMUTEHKY  7

// structures //

typedef struct tagSVRPLAYINFO
{
	// saver info
	CSaverInfo* lpSaverInfo;
	// duration
	DWORD dwMinToPlay;
	// timeout callback
	void (*lpfnTimeoutCallback) (DWORD);
	// timeout data
	DWORD dwTimeoutData;
	// user-close callback
	void (*lpfnUserCloseCallback) (DWORD);
	// user-close data
	DWORD dwUserCloseData;
} SVRPLAYINFO,*LPSVRPLAYINFO;

// globals //

// on-close timer objects
extern UINT g_nOnCloseTimerId;
extern LPPROCESS_INFORMATION g_lpOnClosePI;
extern LPSVRPLAYINFO g_lpOnCloseSPI;
// on-timeout timer objects
extern UINT g_nOnTimeoutTimerId;
extern LPPROCESS_INFORMATION g_lpOnTimeoutPI;
extern LPSVRPLAYINFO g_lpOnTimeoutSPI;
// song-playing flag
extern BOOL g_bSongPlaying;
// dx segment index
extern DWORD g_dwCurSongSegIdx;
// dx song timer id
extern UINT g_nDXSongTimerId;
// dx song was-playing flag
extern BOOL g_bDXSongWasPlaying;

// prototypes //

// playback functions

extern BOOL PlaybackSaver(LPSVRPLAYINFO lpSPI);

extern void InitOnCloseTimer(UINT nDelay,
							 LPPROCESS_INFORMATION lpPI,
							 LPSVRPLAYINFO lpSPI);

extern void CALLBACK OnCloseTimerProc(HWND hWnd,
									  UINT uMsg,
									  UINT idEvent,
									  DWORD dwTime);

extern void InitOnTimeoutTimer(UINT nDelay,
							   LPPROCESS_INFORMATION lpPI,
							   LPSVRPLAYINFO lpSPI);

extern void CALLBACK OnTimeoutTimerProc(HWND hWnd,
										UINT uMsg,
										UINT idEvent,
										DWORD dwTime);

extern void PlayNextSaver(BOOL bShuffle);

extern void PlayNextSaverCallback(DWORD dwData);

extern void SaveWin9XScreensaverFlag(BOOL bRestore=FALSE);

extern void CALLBACK OnDXSongTimerProc(HWND hWnd,
									   UINT uMsg,
									   UINT idEvent,
									   DWORD dwTime);

// main window functions

extern BOOL InitRunPSWindow(void);

extern void ReleaseRunPSWindow(void);

extern BOOL AddRunPSWindowClass(void);

extern void RemoveRunPSWindowClass(void);

extern LRESULT CALLBACK RunPSWindowProc(HWND hWnd,
										UINT Msg,
										WPARAM wParam,
										LPARAM lParam);

extern void ClosePSWindow(DWORD dwData);

// audio playback functions

extern void PlayNextSong(LPSVRPLAYINFO lpNewSPI=NULL,
						 BOOL bUseShuffleFlag=TRUE);

extern BOOL PlaySong(LPSTR lpFile);

extern void StopSong(void);

// hotkey functions

extern BOOL InitPlaybackHotkeys(void);

extern void ReleasePlaybackHotkeys(void);

extern void OnNextSaverHky(void);

extern void OnNextSongHky(void);

extern void OnVolUpHky(void);

extern void OnVolDownHky(void);

extern void OnVolMuteHky(void);

extern BOOL InitTSRModeHotkeys(void);

extern void ReleaseTSRModeHotkeys(void);

extern void OnStartSaverHky(void);

extern void OnOpenPSHky(void);

// tsr-mode functions

extern BOOL InitTSRMode(void);

extern void ExecTSRMode(void);

extern void ReleaseTSRMode(void);

extern BOOL AddTSRModeWindowClass(void);

extern void ReleaseTSRModeWindowClass(void);

extern BOOL CreateTSRModeWindow(void);

extern void DestroyTSRModeWindow(void);

extern LRESULT CALLBACK TSRModeWindowProc(HWND hWnd,
										  UINT Msg,
										  WPARAM wParam,
										  LPARAM lParam);

extern BOOL IsTSRActive(void);

extern BOOL RestartTSR(void);

extern BOOL HideTSRIcon(void);

extern BOOL EnsureTSRModeAutoRun(void);

// macros //

// macro to convert hotkey modifiers
#define HotkeyMods(d) (((d)&HOTKEYF_CONTROL)?MOD_CONTROL:NULL)|(((d)&HOTKEYF_ALT)?MOD_ALT:NULL)|(((d)&HOTKEYF_SHIFT)?MOD_SHIFT:NULL)

// eof //

// Copyright 2006 WaveBreak Software
