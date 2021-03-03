// Copyright 2006 WaveBreak Software

// savers.h -- screensaver settings header

// constants //

// saver list sort flags
#define SLS_TITLEASC  1
#define SLS_TITLEDES  2
#define SLS_THEMEASC  3
#define SLS_THEMEDES  4
#define SLS_RATINGASC 5
#define SLS_RATINGDES 6

// preview window delays
#define PREVIEW_QUICKDELAY  150
#define PREVIEW_CLOSEDELAY  500
#define PREVIEW_SCRNUPDELAY 300

// dummy timer id
#define DUMMY_TIMER_ID 0x1000

// theme allocation increment
#define THEME_ALLOC_INC 8

// max theme length
#define MAX_THEME_LEN 24

// type definitions //

typedef BOOL (WINAPI *CREATESAVERHOOK) (DWORD);

// classes //

class CSaverPage:public CPropertyPage
{
public:
	// constructor override
	CSaverPage(UINT nIDTemplate,
			   UINT nIDCaption=0):CPropertyPage(nIDTemplate,
												nIDCaption) {}

	// message handlers
	afx_msg void OnClearSelBtnClk(void);
	afx_msg void OnAddSaverBtnClk(void);
	afx_msg void OnSettingsBtnClk(void);
	afx_msg void OnPreviewBtnClk(void);
	afx_msg void OnEditInfoBtnClk(void);
	afx_msg void OnShowPreviewChkClk(void);
	afx_msg void OnUpBtnClk(void);
	afx_msg void OnDownBtnClk(void);
	afx_msg void OnTopBtnClk(void);
	afx_msg void OnBottomBtnClk(void);
	afx_msg void OnDeleteBtnClk(void);
	afx_msg void OnClearBtnClk(void);
	afx_msg void OnSaveBtnClk(void);
	afx_msg void OnLoadBtnClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnActivate(UINT nState,
							CWnd* pWndOther,
							BOOL bMinimized);
	afx_msg void OnShowWindow(BOOL bShow,
							  UINT nStatus);

	// system overrides
	virtual BOOL OnSetActive(void);
	virtual void OnOK(void);
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);

	// initialization
	BOOL Initialize(void);

	// first-to-play flag
	BOOL bResetFtP;

	// message map
	DECLARE_MESSAGE_MAP()
};

class CSaverList:public CListCtrl
{
public:
	// notification handlers
	afx_msg void OnCustomDraw(NMHDR* pNMHDR,
							  LRESULT* pResult);
	afx_msg void OnColumnClick(NMHDR* pNMHDR,
							   LRESULT* pResult);
	afx_msg void OnItemChanged(NMHDR* pNMHDR,
							   LRESULT* pResult);
	afx_msg void OnDblClick(NMHDR* pNMHDR,
						    LRESULT* pResult);
	afx_msg void OnRtClick(NMHDR* pNMHDR,
						   LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR,
						 LRESULT* pResult);
	afx_msg BOOL OnTTNeedText(UINT nID,
							  NMHDR* pNMHDR,
							  LRESULT* pResult);

	// message handlers
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	
	// system overrides
	virtual void PreSubclassWindow(void);
	virtual BOOL OnNotify(WPARAM wParam,
						  LPARAM lParam,
						  LRESULT* pResult);
	virtual int OnToolHitTest(CPoint point,
							  TOOLINFO* pTI) const;

	// current selection functions
	BOOL QuerySelection(void);
	int GetSelection(void);

	// misc. functions
	int CellRectFromPoint(CPoint point,
						  LPRECT lprCell) const;
	void HighlightFirstNewSaver(void);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSaverInfoBox:public CExtRichEditCtrl
{
public:
	// constructor
	CSaverInfoBox(UINT nID):CExtRichEditCtrl(nID) {}

	// notification handlers
	afx_msg void OnDblClick(NMHDR* pNMHDR,
						    LRESULT* pResult);

	// message handlers
	afx_msg void OnLButtonDblClk(UINT nFlags,
								 CPoint point);
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd,
							 UINT nHitTest,
							 UINT message);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSaverPreviewBox:public CExtStatic
{
public:
	// constructor
	CSaverPreviewBox(UINT nID);

	// message handlers
	afx_msg void OnPaint(void);

	// bitmap functions
	void SetComputerBitmap(CBitmap* lpBmp);
	void DrawBitmap(LPPAINTSTRUCT lpPS=NULL);
	void RedrawSaver(void);
	
	// computer bitmap
	CBitmap* lpCompBmp;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSaverPreviewWnd:public CWnd
{
public:
	// constructor
	CSaverPreviewWnd();

	// message handlers
	afx_msg void OnPaint(void);
	afx_msg void OnDestroy(void);

	// update functions
	void StartPreview(void);
	void StartPreviewOnDelay(UINT nDelay);
	void StartPreviewOnClose(UINT nDelay,
							 LPPROCESS_INFORMATION lpPI);
	void StopPreview(void);

	// bitmap functions
	void SetScreenBitmap(CBitmap* lpBmp);
	void DrawBitmap(LPPAINTSTRUCT lpPS=NULL);

	// current process info
	PROCESS_INFORMATION pi;
	// process info valid flag
	BOOL bPIValid;
	// screen bitmap
	CBitmap* lpScrnBmp;
	// screen-up flag
	BOOL bScrnUp;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSaverInfoDlg:public CExtDialog
{
public:
	// constructor
	CSaverInfoDlg(UINT nIDTemplate,
				  CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
												    pParentWnd) {}

	// message handlers
	afx_msg void OnEditThemesBtnClk(void);
	afx_msg void OnHelpBtnClk(void);
	afx_msg void OnBrowseBtnClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnMusicCycleBtnClk(void);
	afx_msg void OnMusicShuffleBtnClk(void);
	afx_msg void OnDisablePrevChkClk(void);
	afx_msg void OnPaint(void);
	afx_msg void OnShowWindow(BOOL bShow,
							  UINT nStatus);
	afx_msg LRESULT OnWmHelp(WPARAM wParam,
							 LPARAM lParam);

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);
	virtual void ReleaseDialog(void);

	// music functions
	void SetMusicCycleRad(void);
	void SetMusicShuffleRad(void);
	BOOL ClearMusicSel(void);

	// full music path
	LPSTR lpMusicPath;
	// window-shown flag
	BOOL bWinShown;
		
	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CEditThemesDlg:public CExtDialog
{
public:
	// constructor
	CEditThemesDlg(UINT nIDTemplate,
				   CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
												     pParentWnd) {}

	// message handlers
	afx_msg void OnNewBtnClk(void);
	afx_msg void OnDelBtnClk(void);
	afx_msg void OnRenBtnClk(void);
	afx_msg void OnDefBtnClk(void);
	afx_msg void OnHelpBtnClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg LRESULT OnWmHelp(WPARAM wParam,
							 LPARAM lParam);

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);
	virtual void ReleaseDialog(void);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CThemesList:public CListBox
{
public:
	// message handlers
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);

	// theme manipulation methods
	BOOL AddNewTheme(void);
	BOOL DeleteSelection(void);
	BOOL RenameSelection(void);
	BOOL ResetDefThemes(void);
	BOOL ClearSelection(BOOL bPlaySnd=TRUE);
	BOOL QuerySelection(void);
	int SearchForString(LPSTR lpszFind);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSaverInfo
{
public:
	// constructor
	CSaverInfo();

	// saver info methods
	BOOL AddIconToGlobalList(void);
	BOOL AddInfoToGlobalList(int nIndex=0);
	BOOL AddSaverInfo(LPSTR lpFilePath,
					  LPSTR lpFileName);
	DWORD QueryNewSavers(void);

	// data access methods
	void SaveRatings(void);
	void SaveThemes(void);
	void SaveDuplicateIDs(void);

	// cleanup methods
	void DeleteSaverNode(void);

	// theme checking methods
	BOOL SaverThemeIsDeleted(CThemesList* lpThemes);
	BOOL ThemeIsUsed(LPSTR lpOldTheme);
	void ValidateThemes(void);
	void ReplaceThemes(LPSTR lpOldTheme,
					   LPSTR lpNewTheme);

	// search methods
	LPVOID FindSaver(LPSTR lpStr);
	CSaverInfo* FindSaverByTitle(LPSTR lpStr);

	// misc. methods
	int GetNumNewSavers(void);
	void AlertNewSavers(LPSTR lpMsg=NULL,
						int nCount=0);

	// saver path
	LPSTR lpPath;
	// registry path
	LPSTR lpRegPath;
	// saver title
	LPSTR lpTitle;
	// saver icons
	CBitmap* lpIcon;
	CBitmap* lpIconSm;
	// saver theme
	LPSTR lpTheme;
	// saver rating
	DWORD dwRating;
	// saver description
	LPSTR lpDesc;
	// music file
	LPSTR lpMusic;
	// shuffle flag
	BOOL bShuffle;
	// no-preview flag
	BOOL bNoPreview;
	// load ok flag
	BOOL bLoadOK;
	// next saver in list
	CSaverInfo* lpNextSaver;
	// new saver flag
	BOOL bNew;
	// duplication index
	DWORD dwDupIdx;
	// duplication flag
	BOOL bIsDup;
};

class CNewThemeDlg:public CExtDialog
{
public:
	// constructor
	CNewThemeDlg(UINT nIDTemplate,
				 CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
												   pParentWnd) {}

	// message handlers
	void OnShowWindow(BOOL bShow,
					  UINT nStatus);

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);
	virtual void ReleaseDialog(void);

	// window shown flag
	BOOL bWinShown;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CRenameThemeDlg:public CExtDialog
{
public:
	// constructor
	CRenameThemeDlg(UINT nIDTemplate,
					CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
													  pParentWnd) {}

	// message handlers
	void OnShowWindow(BOOL bShow,
					  UINT nStatus);

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);
	virtual void ReleaseDialog(void);

	// window shown flag
	BOOL bWinShown;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSaverPlaylist:public CPlaylistCtrl
{
public:
	// system overrides
	virtual BOOL OnNotify(WPARAM wParam,
						  LPARAM lParam,
						  LRESULT* pResult);

	// notification handlers
	afx_msg void OnItemChanged(NMHDR* pNMHDR,
							   LRESULT* pResult);

	// message handlers
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	// misc. methods
	void HighlightSelInSaverList(void);
	void QueryPurgeInv(void);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSaverSortBox:public CExtComboBox
{
public:
	// constructor override
	CSaverSortBox(UINT nID);

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

// main property page
extern CSaverPage* g_lpSaverPage;
// screensaver info list
extern CSaverInfo* g_lpSaverInfo;
// screensaver list
extern CSaverList* g_lpSaverList;
// saver list header
extern CExtHeaderCtrl* g_lpSaverListHdr;
// screensaver icons
extern CImageList* g_lpSaverIcons;
// page init flag
extern BOOL g_bSaverPageInit;
// page init-ok flag
extern BOOL g_bSaverPageInitOK;
// current saver selection
extern CSaverInfo* g_lpCurSaver;
// list control fonts
extern CFont* g_lpLCFont;
extern CFont* g_lpLCFontBold;
// saver info box
extern CSaverInfoBox* g_lpSaverInfoBox;
// buttons
extern CExtButton* g_lpClearSelBtn;
extern CExtButton* g_lpAddSaverBtn;
extern CExtButton* g_lpSaverSettingsBtn;
extern CExtButton* g_lpPreviewSaverBtn;
extern CExtButton* g_lpEditSaverInfoBtn;
// checkboxes
extern CExtButton* g_lpMiniPreviewChk;
// bitmaps
extern CBitmap* g_lpRatingBmp;
extern CBitmap* g_lpDimRatingBmp;
// options
extern DWORD g_dwLastSlsFlag;
extern BOOL g_bShowSaverInfo;
extern BOOL g_bShowRatingImgs;
extern BOOL g_bShowPopupInfo;
extern BOOL g_bShowSaverPreview;
extern BOOL g_bShowPListPopup;
// last saver list selection flag
extern BOOL g_bLastSLSelFlag;
// saver preview window objects
extern CSaverPreviewBox* g_lpSaverPrevBox;
extern CSaverPreviewWnd* g_lpSaverPrevWnd;
extern CBitmap* g_lpSaverCompBmp;
extern CBitmap* g_lpSaverScrnBmp;
// preview timer objects
extern UINT g_nPrevTimerId;
extern LPPROCESS_INFORMATION g_lpPrevPI;
// saver info dialog
extern CSaverInfoDlg* g_lpSaverInfoDlg;
// saver info icon
extern CExtStatic* g_lpSaverInfoIcon;
// themes list info
extern DWORD g_dwNumThemes;
extern DWORD g_dwMaxThemes;
extern LPSTR* g_lplpThemes;
// theme selection box
extern CExtComboBox* g_lpThemeSelBox;
// edit themes button
extern CExtButton* g_lpEditThemesBtn;
// rating selection box
extern CExtComboBox* g_lpRatingSelBox;
// edit saver help button
extern CExtButton* g_lpEditHelpBtn;
// music selection box
extern CExtEdit* g_lpMusicSelBox;
// music browse button
extern CExtButton* g_lpMusicBrowseBtn;
// music playback buttons
extern CExtButton* g_lpMusicCycleRad;
extern CExtButton* g_lpMusicShuffleRad;
// saver description label
extern CExtStatic* g_lpSaverDescLabel;
// saver description box
extern CExtEdit* g_lpSaverDescEdit;
// no-mini-preview button
extern CExtButton* g_lpNoMiniPrevChk;
// edit themes dialog
extern CEditThemesDlg* g_lpEditThemesDlg;
extern CEditThemesDlg* g_lpEditThemesDlgA;
extern CEditThemesDlg* g_lpEditThemesDlgB;
// edit themes list
extern CThemesList* g_lpThemesList;
// edit themes buttons
extern CExtButton* g_lpNewThemeBtn;
extern CExtButton* g_lpDelThemeBtn;
extern CExtButton* g_lpRenThemeBtn;
extern CExtButton* g_lpDefThemesBtn;
extern CExtButton* g_lpThemesHelpBtn;
// new theme dialog
extern CNewThemeDlg* g_lpNewThemeDlg;
// new theme edit control
extern CExtEdit* g_lpNewThemeEdit;
// rename theme dialog
extern CRenameThemeDlg* g_lpRenThemeDlg;
// rename theme edit control
extern CExtEdit* g_lpRenThemeEdit;
// saver playlist control
extern CSaverPlaylist* g_lpSaverPlaylist;
// saver playlist header
extern CExtHeaderCtrl* g_lpSaverPlaylistHdr;
// saver playlist buttons
extern CExtButton* g_lpPListUpBtn;
extern CExtButton* g_lpPListDownBtn;
extern CExtButton* g_lpPListTopBtn;
extern CExtButton* g_lpPListBottomBtn;
extern CExtButton* g_lpPListDeleteBtn;
extern CExtButton* g_lpPListClearBtn;
extern CExtButton* g_lpPListSaveBtn;
extern CExtButton* g_lpPListLoadBtn;
// invalid playlist flag
extern BOOL g_bInvPListItems;
// saver playlist sort box
extern CSaverSortBox* g_lpSaverSortBox;
// music manager dialog
extern CMusicManagerDlg* g_lpMusicManagerDlgB;
// screen-up timer id
extern UINT g_nScrnUpTimerId;
// saver-hook dll handle
extern HMODULE g_hSvrHookDll;
// saver-hook function pointer
extern CREATESAVERHOOK CreateSaverHook;

// prototypes //

// screensaver functions

extern BOOL LoadScreensaverInfo(BOOL bListOnly=FALSE);

extern void ReleaseScreensaverInfo(void);

extern BOOL GetScreensaversFromFolder(LPSTR lpPath);

extern BOOL GetScreensaversFromUserFolders(void);

extern BOOL GetScreensaverData(LPSTR lpPath,
							   LPSTR* lplpTheme,
							   LPDWORD lpdwRating,
							   LPSTR* lplpDesc,
							   LPSTR* lplpMusic,
							   LPBOOL lpbShuffle,
							   LPBOOL lpbNoPreview,
							   LPBOOL lpbNew,
							   LPDWORD lpdwDupIdx,
							   LPBOOL lpbIsDup);

extern void GetDefaultTheme(LPSTR lpTheme,
							LPSTR lpPath);

extern DWORD GetDefaultRating(LPSTR lpPath);

extern void GetDefaultDesc(LPSTR lpDesc,
						   LPSTR lpPath);

extern void GetScreensaverName(LPSTR lpName,
							   LPSTR lpPath);

extern LPSTR GetRatingString(DWORD dwRating);

extern BOOL AssembleIconList(void);

extern void ReleaseIconList(void);

extern BOOL AddCurSaverToPlaylist(void);

extern BOOL EditCurSaverInfo(void);

extern BOOL ClearCurSaver(void);

extern BOOL BuildSaverList(void);

extern BOOL RunCurSaverSettings(void);

extern BOOL RunCurSaverPreview(void);

extern BOOL SetCurrentSaver(CSaverInfo* lpSaverInfo);

extern BOOL InitSaverPreviewWnd(void);

extern BOOL CreateSaverPreviewWnd(void);

extern void ReleaseSaverPreviewWnd(void);

extern void CALLBACK OnPrevDelayTimerProc(HWND hWnd,
										  UINT uMsg,
										  UINT idEvent,
										  DWORD dwTime);

extern void CALLBACK OnPrevCloseTimerProc(HWND hWnd,
										  UINT uMsg,
										  UINT idEvent,
										  DWORD dwTime);

extern BOOL SaveCurSaverInfo(void);

extern BOOL GetSaverTitle(LPSTR lpStr,
						  LPVOID lpItemData);

extern BOOL GetSaverSaveData(LPSTR lpStr,
						     LPVOID lpItemData);

extern LPVOID GetSaverItemData(LPSTR lpStr);

extern BOOL GetSaverTooltip(LPSTR lpStr,
							LPVOID lpItemData);

extern int CALLBACK SaverListSort(LPARAM lParam1,
								  LPARAM lParam2,
								  LPARAM lParamSort);

extern void ToggleSaverListDetails(BOOL bUpdate=TRUE);

extern void ToggleSaverListRatings(BOOL bUpdate=TRUE);

extern void ToggleSaverListPopupInfo(BOOL bUpdate=TRUE);

extern void ToggleSaverPreview(BOOL bUpdate=TRUE);

extern void SortSaverListColumn(int nCol);

extern void UpdateSaverListSortImages(void);

extern BOOL UpdateSaverInfoBox(CSaverInfo* lpSaverInfo);

extern void SetCurSaverRating(DWORD dwRating,
							  BOOL bUpdate=TRUE);

extern void AlertInvSaverPlaylistItems(void);

extern void SortSaverPlaylist(int nCode);

extern int CALLBACK SortSaverPlaylistCallback(LPARAM lParam1,
											  LPARAM lParam2,
											  LPARAM lParamSort);

extern void TogglePListPopupInfo(void);

extern BOOL AssignDuplicateSaverIDs(void);

extern DWORD GetNextDuplicateSaverID(LPSTR lpTitle);

extern void CALLBACK OnScrnUpTimerProc(HWND hWnd,
									   UINT uMsg,
									   UINT idEvent,
									   DWORD dwTime);

extern BOOL InitSaverHookProc(void);

extern void ReleaseSaverHookProc(void);

extern void RestartSaverPreview(DWORD dwData);

extern BOOL GetNextSaverString(LPSTR lpStr,
							   int* lpnCurId,
							   BOOL bCountOnly);

// themes functions

extern BOOL EditThemes(CEditThemesDlg* lpEditThemesDlg);

extern BOOL LoadThemes(void);

extern BOOL SetDefaultThemes(void);

extern BOOL SaveThemes(void);

extern BOOL ValidateTheme(LPSTR* lplpTheme);

extern BOOL AddTheme(DWORD dwNum);

extern BOOL AddTheme(LPSTR lpTheme);

extern BOOL SaveTheme(DWORD dwNum,
					  LPSTR lpTheme);

extern void ReleaseThemes(void);

// misc functions

extern void SetRegularScrollBars(CWnd* lpWnd);

extern DWORD ComputeColNum(DWORD dwItemVal,
						   DWORD dwItemsPerCol);

extern BOOL DrawBitmapWithBorder(CWnd* lpTargetWnd,
								 CBitmap* lpBmp,
								 int nX,
								 int nY,
								 int nBdrOfs=0,
								 COLORREF clrBdr=NULL,
								 COLORREF clrBkg=NULL,
								 COLORREF clrShadow=NULL);

extern DWORD CALLBACK StreamInCallback(DWORD dwCookie,
									   LPBYTE pbBuff,
									   LONG cb,
									   LONG* pcb);

// eof //

// Copyright 2006 WaveBreak Software
