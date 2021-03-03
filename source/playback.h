// Copyright 2006 WaveBreak Software

// playback.h -- playback settings header

// constants //

// search list change notification message
#define SPATH_CHGNOTIFY "Changes to the screensaver search path list\nwill take effect the next time ProSaver is started."

// classes //

class CPlaybackPage:public CPropertyPage
{
public:
	// constructor override
	CPlaybackPage(UINT nIDTemplate,
				  UINT nIDCaption=0):CPropertyPage(nIDTemplate,
												   nIDCaption) {}

	// message handlers
	afx_msg void OnOneSaverRadClk(void);
	afx_msg void OnMultiSaverRadClk(void);
	afx_msg void OnSaverCycleRadClk(void);
	afx_msg void OnSaverShuffleRadClk(void);
	afx_msg void OnEnableHotkeysChkClk(void);
	afx_msg void OnClearScreenChkClk(void);
	afx_msg void OnMusicPlaybackChkClk(void);
	afx_msg void OnOpenThemesBtnClk(void);
	afx_msg void OnOpenMusicBtnClk(void);
	afx_msg void OnShowAdvancedBtnClk(void);
	afx_msg void OnAddPathBtnClk(void);
	afx_msg void OnChangePathBtnClk(void);
	afx_msg void OnDeletePathBtnClk(void);
	afx_msg void OnSystemTrayChkClk(void);
	afx_msg void OnKeepCurrentChkClk(void);
	afx_msg void OnHideAdvancedChkClk(void);
	afx_msg void OnErrorLogChkClk(void);
	afx_msg void OnErrorLogBtnClk(void);
	afx_msg void OnResetMessagesBtnClk(void);
	afx_msg void OnHideAdvancedBtnClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// system overrides
	virtual BOOL OnSetActive(void);
	virtual void OnOK(void);
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);

	// initialization
	BOOL Initialize(void);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CPathListCtrl:public CListCtrl
{
public:
	// constructor override
	CPathListCtrl(UINT nID);

	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnItemChanged(NMHDR* pNMHDR,
							   LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);

	// notification handlers
	afx_msg void OnCustomDraw(NMHDR* pNMHDR,
							  LRESULT* pResult);
	afx_msg BOOL OnTTNeedText(UINT nID,
							  NMHDR* pNMHDR,
							  LRESULT* pResult);

	// system overrides
	virtual void PreSubclassWindow(void);
	virtual int OnToolHitTest(CPoint point,
							  TOOLINFO* pTI) const;

	// current selection functions
	BOOL QuerySelection(void);
	int GetSelection(void);
	BOOL ChangeSelection(void);
	BOOL DeleteSelection(void);

	// misc. methods
	int CellRectFromPoint(CPoint point,
						  LPRECT lprCell) const;
	BOOL AddPath(LPSTR lpPath=NULL,
				 BOOL bDefault=FALSE,
				 BOOL bSilent=FALSE);
	BOOL PathIsInList(LPSTR lpPath);

	// control id
	UINT nCtrlId;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

// globals //

// main property page
extern CPlaybackPage* g_lpPlaybackPage;
// page init flag
extern BOOL g_bPlaybackPageInit;
// page init-ok flag
extern BOOL g_bPlaybackPageInitOK;
// radio buttons
extern CExtButton* g_lpOneSaverRad;
extern CExtButton* g_lpMultiSaverRad;
extern CExtButton* g_lpSaverCycleRad;
extern CExtButton* g_lpSaverShuffleRad;
// static controls
extern CExtStatic* g_lpShowSaverTxt;
extern CExtStatic* g_lpShowSaverMinTxt;
extern CExtStatic* g_lpStartSaverTxt;
extern CExtStatic* g_lpSkipSaverTxt;
extern CExtStatic* g_lpOpenPSTxt;
extern CExtStatic* g_lpMaxLinesTxt;
// read-only edit controls
extern CExtEdit* g_lpAdvWarningTxt;
// edit controls
extern CExtEdit* g_lpShowSaverEdit;
extern CExtEdit* g_lpMaxLinesEdit;
// checkboxes
extern CExtButton* g_lpEnableHotkeysChk;
extern CExtButton* g_lpClearScreenChk;
extern CExtButton* g_lpNoMusicChk;
extern CExtButton* g_lpSystemTrayChk;
extern CExtButton* g_lpKeepCurrentChk;
extern CExtButton* g_lpHideAdvancedChk;
extern CExtButton* g_lpErrorLogChk;
// hotkey controls
extern CExtHotKeyCtrl* g_lpStartSaverHky;
extern CExtHotKeyCtrl* g_lpSkipSaverHky;
extern CExtHotKeyCtrl* g_lpOpenPSHky;
// pushbutton controls
extern CExtButton* g_lpOpenThemesBtn;
extern CExtButton* g_lpOpenMusicBtn;
extern CExtButton* g_lpShowAdvancedBtn;
extern CExtButton* g_lpAddPathBtn;
extern CExtButton* g_lpChangePathBtn;
extern CExtButton* g_lpDeletePathBtn;
extern CExtButton* g_lpErrorLogBtn;
extern CExtButton* g_lpResetMessagesBtn;
extern CExtButton* g_lpHideAdvancedBtn;
// search path list
extern CPathListCtrl* g_lpSearchPathList;
// misc. flags
extern BOOL g_bMultiSavers;
extern BOOL g_bCycleSavers;
extern BOOL g_bEnableHotkeys;
extern BOOL g_bClearScreen;
extern BOOL g_bNoMusic;
extern BOOL g_bSystemTray;
extern BOOL g_bKeepCurrent;
extern BOOL g_bHideAdvanced;
extern BOOL g_bKeepErrorLog;
// playback minutes
extern int g_nPlayMinutes;
// hotkey values
extern DWORD g_dwStartSaverHky;
extern DWORD g_dwSkipSaverHky;
extern DWORD g_dwOpenPSHky;
// search path image list
extern CImageList* g_lpSPathImageList;
// advanced-viewed flag
extern BOOL g_bAdvOptViewed;
// static boxes
extern CStatic* g_lpSearchPathBox;
extern CStatic* g_lpErrorLogBox;
// error-log lines
extern int g_nErrorLogLines;
// music manager dialog
extern CMusicManagerDlg* g_lpMusicManagerDlgA;
// advanced-visible flag
extern BOOL g_bAdvOptVisible;

// prototypes //

// playback option functions

BOOL LoadPlaybackOptions(void);

void SavePlaybackOptions(void);

// search path functions

BOOL AddSearchPathsToList(void);

BOOL LoadSearchPathsFromReg(LPCSTR lpAppKey,
							LPCSTR lpSubKey,
							BOOL bScanAddOnly=FALSE);

BOOL SaveSearchPathsToReg(LPCSTR lpAppKey,
						  LPCSTR lpSubKey);

BOOL CreateSearchPathImageList(void);

// dialog manipulation functions

void SetMultiSavers(BOOL bUpdate=TRUE);

void SetOneSaver(BOOL bUpdate=TRUE);

void SetCycleSavers(BOOL bUpdate=TRUE);

void SetShuffleSavers(BOOL bUpdate=TRUE);

void ToggleHotkeys(BOOL bUpdate=TRUE);

void ToggleClearScreen(BOOL bUpdate=TRUE);

void ToggleMusicPlayback(BOOL bUpdate=TRUE);

void ShowAdvancedOptions(BOOL bShow=TRUE);

BOOL LoadAdvancedOptions(void);

void SaveAdvancedOptions(void);

void ToggleSystemTray(BOOL bUpdate=TRUE);

void ToggleKeepCurrent(BOOL bUpdate=TRUE);

void ToggleHideAdvanced(BOOL bUpdate=TRUE);

void ToggleErrorLog(BOOL bUpdate=TRUE);

BOOL ViewErrorLog(void);

BOOL RestoreBlockedMessages(void);

// eof //

// Copyright 2006 WaveBreak Software
