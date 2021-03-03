// Copyright 2006 WaveBreak Software

// audio.h -- audio settings header

// constants //

// audio file types
#define AFT_AUDIO 1
#define AFT_PLIST 2

// audio error messages
#define NO_MUSIC_MSG  "Music playback has been disabled for all screensavers!\n\nYou can change this setting under the 'Program Options' tab."
#define INV_PLIST_MSG "Invalid items are shown in gray text in the playlist."

// audio timeout values
#define AUDIO_TIMEOUT       250
#define AUDIO_TIMEOUT_WAIT  300
#define AUDIO_TIMEOUT_BRIEF 50

// mp3 correction value
#define MP3_CORR_VAL 150

// audio reload flag
#define CURAUDIO_RELOAD ((LPFILELISTDATA)0xFFFFFFFFL)

// useful asf id's
static const GUID ASF_Header_Object             ={0x75B22630,0x668E,0x11CF,{0xA6,0xD9,0x00,0xAA,0x00,0x62,0xCE,0x6C}};
static const GUID ASF_Content_Description_Object={0x75B22633,0x668E,0x11CF,{0xA6,0xD9,0x00,0xAA,0x00,0x62,0xCE,0x6C}};

// master volume commands
#define MV_INIT    0
#define MV_GET     1
#define MV_SET     2
#define MV_RELEASE 3
#define MV_SAVE    4
#define MV_RESTORE 5
#define MV_HALF    6

// classes //

class CChangeMusicDlg:public CExtDialog
{
public:
	// constructor
	CChangeMusicDlg(UINT nIDTemplate,
				    CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
												      pParentWnd) {}

	// message handlers
	afx_msg void OnLoadAudioFileBtnClk(void);
	afx_msg void OnLoadAudioPlaylistBtnClk(void);
	afx_msg void OnClearAudioFileBtnClk(void);
	afx_msg void OnOpenMusicManagerBtnClk(void);
	afx_msg void OnChangeAudioHelpBtnClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg LRESULT OnWmHelp(WPARAM wParam,
							 LPARAM lParam);

	// system overrides
	virtual BOOL InitDialog(void);
	virtual void ReleaseDialog(void);

	// misc. methods
	void LoadAudioFile(DWORD dwType);
	void UpdateAudio(LPSTR lpFile);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CMusicManagerDlg:public CExtDialog
{
public:
	// constructor
	CMusicManagerDlg(UINT nIDTemplate,
					 CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
													   pParentWnd) {}

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);
	virtual void ReleaseDialog(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnBackBtnClk(void);
	afx_msg void OnUpBtnClk(void);
	afx_msg void OnClearSelBtnClk(void);
	afx_msg void OnAddFileBtnClk(void);
	afx_msg void OnPlayBtnClk(void);
	afx_msg void OnPauseBtnClk(void);
	afx_msg void OnStopBtnClk(void);
	afx_msg void OnFullRewBtnClk(void);
	afx_msg void OnRewBtnClk(void);
	afx_msg void OnFwdBtnClk(void);
	afx_msg void OnPListUpBtnClk(void);
	afx_msg void OnPListTopBtnClk(void);
	afx_msg void OnPListDownBtnClk(void);
	afx_msg void OnPListBottomBtnClk(void);
	afx_msg void OnPListDeleteBtnClk(void);
	afx_msg void OnPListClearBtnClk(void);
	afx_msg void OnPListSaveBtnClk(void);
	afx_msg void OnPListLoadBtnClk(void);
	afx_msg void OnHScroll(UINT nSBCode,
						   UINT nPos,
						   CScrollBar* pScrollBar);
	afx_msg void OnEnablePBCChkClk(void);
	afx_msg void OnWinSynthRadClk(void);
	afx_msg void OnDXSynthRadClk(void);
	afx_msg void OnReverbChkClk(void);
	afx_msg void OnChorusChkClk(void);
	afx_msg void OnHelpBtnClk(void);
	afx_msg void OnInstallDXBtnClk(void);
	afx_msg void OnShowWindow(BOOL bShow,
							  UINT nStatus);
	afx_msg LRESULT OnWmHelp(WPARAM wParam,
							 LPARAM lParam);

	// misc. methods
	BOOL PostInitDialog(void);

	// window position
	CRect rMMgrWndPos;
	// update flag
	BOOL bUpdatePos;
	// window-shown flag
	BOOL bWinShown;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CAudioPlaylist:public CPlaylistCtrl
{
public:
	// system overrides
	virtual BOOL OnNotify(WPARAM wParam,
						  LPARAM lParam,
						  LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// notification handlers
	afx_msg void OnItemChanged(NMHDR* pNMHDR,
							   LRESULT* pResult);
	afx_msg void OnDblClick(NMHDR* pNMHDR,
							LRESULT* pResult);

	// message handlers
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	// misc. methods
	void QueryPurgeInv(void);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CAudioExtComboBox:public CExtComboBox
{
public:
	// constructor override
	CAudioExtComboBox(UINT nID);

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);

	// misc. methods
	void SetParentDlg(CExtDialog* lpDlg);

	// parent dialog
	CExtDialog* lpParentDlg;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CAudioPosSlider:public CExtSliderCtrl
{
public:
	// constructor override
	CAudioPosSlider(UINT nID);

	// message handlers
	afx_msg void OnHScroll(UINT nSBCode,
						   UINT nPos,
						   CScrollBar* pScrollBar);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CAudioInfoBox:public CExtRichEditCtrl
{
public:
	// constructor
	CAudioInfoBox(UINT nID):CExtRichEditCtrl(nID) {}

	// message handlers
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd,
							 UINT nHitTest,
							 UINT message);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CAudioSortBox:public CExtComboBox
{
public:
	// constructor override
	CAudioSortBox(UINT nID);

	// message handlers
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);

	// box down flag
	BOOL bBoxDown;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

// globals //

// audio-init flag
extern BOOL g_bAudioInit;
// change music dialog
extern CChangeMusicDlg* g_lpChangeMusicDlg;
// change music buttons
extern CExtButton* g_lpLoadAudioFileBtn;
extern CExtButton* g_lpLoadAudioPlaylistBtn;
extern CExtButton* g_lpClearAudioFileBtn;
extern CExtButton* g_lpOpenMusicManagerBtn;
extern CExtButton* g_lpChangeAudioHelpBtn;
// current music manager
extern CMusicManagerDlg* g_lpCurMusicMgrDlg;
// music dialog history box
extern CHistoryComboBox* g_lpAudioHistoryCbx;
// folder controls
extern CFolderCtrlButton* g_lpFileBackBtn;
extern CFolderCtrlButton* g_lpFileUpBtn;
// music dialog buttons
extern CExtButton* g_lpClearAudioSelBtn;
extern CExtButton* g_lpAddAudioFileBtn;
extern CExtButton* g_lpAudioPListUpBtn;
extern CExtButton* g_lpAudioPListTopBtn;
extern CExtButton* g_lpAudioPListDownBtn;
extern CExtButton* g_lpAudioPListBottomBtn;
extern CExtButton* g_lpAudioPListDelBtn;
extern CExtButton* g_lpAudioPListClearBtn;
extern CExtButton* g_lpAudioPListSaveBtn;
extern CExtButton* g_lpAudioPListLoadBtn;
extern CExtButton* g_lpPlayBtn;
extern CExtButton* g_lpPauseBtn;
extern CExtButton* g_lpStopBtn;
extern CExtButton* g_lpFullRewBtn;
extern CExtButton* g_lpRewBtn;
extern CExtButton* g_lpFwdBtn;
extern CExtButton* g_lpMusicMgrHelpBtn;
extern CExtButton* g_lpInstallDXBtn;
// music dialog file list
extern CFileListCtrl* g_lpAudioFileList;
// music dialog combo boxes
extern CAudioExtComboBox* g_lpFileTypeCbx;
extern CAudioSortBox* g_lpAudioPListSortCbx;
// music dialog audio playlist
extern CAudioPlaylist* g_lpAudioPList;
// music dialog file info
extern CAudioInfoBox* g_lpAudioInfoBox;
// music dialog static controls
extern CExtStatic* g_lpAudioPosTxt;
extern CExtStatic* g_lpNextHkyTxt;
extern CExtStatic* g_lpVolUpHkyTxt;
extern CExtStatic* g_lpVolDownHkyTxt;
extern CExtStatic* g_lpMuteHkyTxt;
extern CExtStatic* g_lpDXFXTxt;
// music dialog position indicator
extern CAudioPosSlider* g_lpAudioPosSld;
// music dialog checkboxes
extern CExtButton* g_lpEnablePBCChk;
extern CExtButton* g_lpReverbChk;
extern CExtButton* g_lpChorusChk;
// music dialog hotkey controls
extern CExtHotKeyCtrl* g_lpNextHky;
extern CExtHotKeyCtrl* g_lpVolUpHky;
extern CExtHotKeyCtrl* g_lpVolDownHky;
extern CExtHotKeyCtrl* g_lpMuteHky;
// music dialog radio buttons
extern CExtButton* g_lpWinSynthRad;
extern CExtButton* g_lpDXSynthRad;
// tooltip control
extern CToolTipCtrl* g_lpMusicMgrToolTip;
// music manager hide windows
extern CWnd* g_lpMMWndToHide1;
extern CWnd* g_lpMMWndToHide2;
// music manager window rects
extern CRect g_rMMWnd1,g_rMMWnd2;
extern CRect g_rMMInv1,g_rMMInv2;
// extension groups
extern CExtensionGroup* g_lpAudioExtGrp;
extern CExtensionGroup* g_lpPListExtGrp;
// current audio extension list
extern CExtensionList* g_lpCurAudExtList;
// audio playback window
extern HWND g_hMCIWnd;
// current audio info
extern LPFILELISTDATA g_lpCurAudioFLD;
extern UINT g_nCurAudioDevID;
// current audio timer
extern UINT g_nCurAudioTimerID;
// audio pause flag
extern BOOL g_bAudioPause;
// audio position update flag
extern BOOL g_bNoAudioPosUpdate;
// mp3 flag
extern BOOL g_bCurAudioIsMP3;
// playlist file info
extern LPFILELISTDATA* g_lplpAPListFileData;
extern DWORD g_dwNumAPListFileData;
// previous popup info flag
extern BOOL g_bShowPListPopupPrev;
// audio hotkey flag
extern BOOL g_bEnableAudioHotkeys;
// audio hotkey values
extern DWORD g_dwNextHky;
extern DWORD g_dwVolUpHky;
extern DWORD g_dwVolDownHky;
extern DWORD g_dwMuteHky;
// synthesizer flags
extern BOOL g_bDXSynthOK;
extern BOOL g_bUseDXSynth;
extern BOOL g_bUseDXReverb;
extern BOOL g_bUseDXChorus;
// last-saved playlist
extern LPSTR g_lpLastSavedPList;
// audio temp file
extern LPSTR g_lpAudioTempFile;
// master volume settings
extern DWORD g_dwSavedVolume;
extern BOOL g_bVolumeSaved;

// prototypes //

// music manipulation functions

extern BOOL BrowseMusicFiles(void);

extern BOOL ValidateMusicFile(LPSTR* lplpMusic);

extern BOOL IsValidMusicFile(LPSTR lpMusic,
							 BOOL bIncPlaylists=TRUE);

extern BOOL IsValidPlaylist(LPSTR lpMusic);

extern LPSTR GetAudioFileFilterList(void);

extern LPSTR GetPlaylistFilterList(void);

extern BOOL CheckAudioFileCallback(void);

extern BOOL GetAudioFileInfo(HWND hMCIWnd,
							 CFileInfo* lpFileInfo,
							 LPSTR lpPath);

extern BOOL SetCurrentAudio(LPFILELISTDATA lpFLD);

extern void UpdateCurrentAudio(BOOL bClear);

extern void CALLBACK CurAudioTimerProc(HWND hWnd,
									   UINT uMsg,
									   UINT idEvent,
									   DWORD dwTime);

extern BOOL UpdateAudioInfoBox(CFileInfo* lpFileInfo);

extern void UpdateAudioTimer(BOOL bClear=FALSE);

extern void WaitForAudioTimeout(void);

extern void UpdateAudioPosText(long lTimeCur=-1);

extern BOOL GetAudioTitle(LPSTR lpStr,
						  LPVOID lpItemData);

extern BOOL GetAudioSaveData(LPSTR lpStr,
						     LPVOID lpItemData);

extern LPVOID GetAudioItemData(LPSTR lpStr);

extern BOOL GetAudioTooltip(LPSTR lpStr,
							LPVOID lpItemData);

extern void SortAudioPlaylist(int nCode);

extern int CALLBACK SortAudioPlaylistCallback(LPARAM lParam1,
											  LPARAM lParam2,
											  LPARAM lParamSort);

extern BOOL AddAudioPlaylistFileData(LPFILELISTDATA* lplpFileData,
									 CDirTree* lpParentDirTree,
									 LPSTR lpFile);

extern void ReleaseAudioPlaylistFileData(void);

extern BOOL SetAudioPListValues(LPSTR lpFile,
							    int nNextPlay,
							    int nLastValid);
	
extern BOOL GetAudioPListValues(LPSTR lpFile,
							    int* lpnNextPlay,
							    int* lpnLastValid);

extern BOOL GetAudioPListFile(LPSTR lpPListFile,
							  int nIndex,
							  LPSTR lpAudioFile);

extern BOOL GetAudioPListItemCount(LPSTR lpPListFile,
								   int* lpnCount);

extern BOOL TestMP3Output(BOOL bSilent=FALSE,
						  BOOL bReset=FALSE);

extern BOOL CreateAudioTempFile(void);

extern BOOL DeleteAudioTempFile(void);

extern BOOL GetNextMusicString(LPSTR lpPlaylist,
							   LPSTR lpStr,
							   int* lpnCurId,
							   BOOL bCountOnly);

// error handling functions

extern BOOL DisplayMCIErrorMessage(LPSTR lpError=NULL);

extern BOOL DisplayNEMCIErrorMessage(LPSTR lpError=NULL);

// init/shutdown functions

extern void ShowMusicManager(CMusicManagerDlg* lpMusicManager,
							 CWnd* lpWndToHide1=NULL,
							 CWnd* lpWndToHide2=NULL);

extern CMusicManagerDlg* CreateMusicManagerDlg(CWnd* lpParent);

extern BOOL InitAudioSupport(BOOL bNotifyPos,
							 BOOL bSilent);

extern void ReleaseAudioSupport(void);

extern void AlertInvAudioPlaylistItems(void);

extern void ToggleAudioPListPopupInfo(void);

extern void ToggleAudioHotkeys(BOOL bUpdate=TRUE);

extern BOOL LoadAudioOptions(void);

extern BOOL SaveAudioOptions(void);

extern BOOL SetWinSynth(BOOL bUpdate=TRUE);

extern BOOL SetDXSynth(BOOL bUpdate=TRUE);

extern void ToggleReverb(BOOL bUpdate=TRUE);

extern void ToggleChorus(BOOL bUpdate=TRUE);

// misc. functions

extern BOOL ReadTag(HANDLE hFile,
					LPSTR lpTag,
					DWORD dwNumBytes);

extern BOOL ReadWideTag(HANDLE hFile,
						LPSTR lpTag,
						DWORD dwNumBytes);

extern unsigned int ByteCount(LPSTR lpStr,
							  char cByte);

extern BOOL MasterVolume(DWORD dwCmd,
						 LPDWORD lpdwData=NULL);

// macros //

#define MCICmd(cmd) { cmd; DisplayMCIErrorMessage(); }

// eof //

// Copyright 2006 WaveBreak Software
