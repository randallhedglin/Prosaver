// Copyright 2006 WaveBreak Software

// source.h -- application core header

// window messages //

#define IDM_MSHEET_INIT   WM_APP+100
#define IDM_MSHEET_CLRCHG WM_APP+101
#define IDM_NWTHM_INIT    WM_APP+102
#define IDM_RNTHM_INIT    WM_APP+103
#define IDM_SINFO_INIT    WM_APP+104
#define IDM_MUSMAN_INIT   WM_APP+105
#define IDM_BROWSEMUSIC   WM_APP+106
#define IDM_PBACKWND_INIT WM_APP+107
#define IDM_SYSTRAY_EVENT WM_APP+108

#define IDM_SLIST_ADD        WM_APP+200
#define IDM_SLIST_EDIT       WM_APP+201
#define IDM_SLIST_DETAILS    WM_APP+202
#define IDM_SLIST_RATINGS    WM_APP+203
#define IDM_SLIST_TITLESORT  WM_APP+204
#define IDM_SLIST_THEMESORT  WM_APP+205
#define IDM_SLIST_RATINGSORT WM_APP+206
#define IDM_SLIST_SETRATING0 WM_APP+207
#define IDM_SLIST_SETRATING1 WM_APP+208
#define IDM_SLIST_SETRATING2 WM_APP+209
#define IDM_SLIST_SETRATING3 WM_APP+210
#define IDM_SLIST_SETRATING4 WM_APP+211
#define IDM_SLIST_SETRATING5 WM_APP+212
#define IDM_SLIST_POPUPINFO  WM_APP+213

#define IDM_SIBOX_SETTINGS WM_APP+300
#define IDM_SIBOX_PREVIEW  WM_APP+301
#define IDM_SIBOX_SHOWPREV WM_APP+302

#define IDM_SDESC_UNDO   WM_APP+400
#define IDM_SDESC_CUT    WM_APP+401
#define IDM_SDESC_COPY   WM_APP+402
#define IDM_SDESC_PASTE  WM_APP+403
#define IDM_SDESC_DEL    WM_APP+404
#define IDM_SDESC_SELALL WM_APP+405

#define IDM_MUSIC_LOADFILE  WM_APP+500
#define IDM_MUSIC_LOADPLIST WM_APP+501
#define IDM_MUSIC_CLEARSEL  WM_APP+502
#define IDM_MUSIC_OPENMGR   WM_APP+503

#define IDM_THEME_NEW   WM_APP+600
#define IDM_THEME_DEL   WM_APP+601
#define IDM_THEME_REN   WM_APP+602
#define IDM_THEME_CLEAR WM_APP+603

#define IDM_NWTHM_UNDO   WM_APP+700
#define IDM_NWTHM_CUT    WM_APP+701
#define IDM_NWTHM_COPY   WM_APP+702
#define IDM_NWTHM_PASTE  WM_APP+703
#define IDM_NWTHM_DEL    WM_APP+704
#define IDM_NWTHM_SELALL WM_APP+705

#define IDM_RNTHM_UNDO   WM_APP+800
#define IDM_RNTHM_CUT    WM_APP+801
#define IDM_RNTHM_COPY   WM_APP+802
#define IDM_RNTHM_PASTE  WM_APP+803
#define IDM_RNTHM_DEL    WM_APP+804
#define IDM_RNTHM_SELALL WM_APP+805

#define IDM_PLIST_SORTNAMEAZ   WM_APP+900
#define IDM_PLIST_SORTNAMEZA   WM_APP+901
#define IDM_PLIST_SORTTHEMEAZ  WM_APP+902
#define IDM_PLIST_SORTTHEMEZA  WM_APP+903
#define IDM_PLIST_SORTRATING51 WM_APP+904
#define IDM_PLIST_SORTRATING15 WM_APP+905
#define IDM_PLIST_CLEARLIST    WM_APP+906
#define IDM_PLIST_SAVELIST     WM_APP+907
#define IDM_PLIST_LOADLIST     WM_APP+908
#define IDM_PLIST_PURGEINV     WM_APP+909
#define IDM_PLIST_MOVEUP       WM_APP+910
#define IDM_PLIST_MOVEDOWN     WM_APP+911
#define IDM_PLIST_MOVETOP      WM_APP+912
#define IDM_PLIST_MOVEBOTTOM   WM_APP+913
#define IDM_PLIST_DELETESEL    WM_APP+914
#define IDM_PLIST_TOGGLEPOPUP  WM_APP+915

#define IDM_SPATH_ADDPATH WM_APP+1000
#define IDM_SPATH_CHGPATH WM_APP+1001
#define IDM_SPATH_DELPATH WM_APP+1002

#define IDM_FLIST_OPENFOLDER WM_APP+1100
#define IDM_FLIST_ADDFILE    WM_APP+1101
#define IDM_FLIST_PLAYFILE   WM_APP+1102

#define IDM_APLST_SORTNAMEAZ  WM_APP+1200
#define IDM_APLST_SORTNAMEZA  WM_APP+1201
#define IDM_APLST_SORTTYPEAZ  WM_APP+1202
#define IDM_APLST_SORTTYPEZA  WM_APP+1203
#define IDM_APLST_CLEARLIST   WM_APP+1206
#define IDM_APLST_SAVELIST    WM_APP+1207
#define IDM_APLST_LOADLIST    WM_APP+1208
#define IDM_APLST_PURGEINV    WM_APP+1209
#define IDM_APLST_MOVEUP      WM_APP+1210
#define IDM_APLST_MOVEDOWN    WM_APP+1211
#define IDM_APLST_MOVETOP     WM_APP+1212
#define IDM_APLST_MOVEBOTTOM  WM_APP+1213
#define IDM_APLST_DELETESEL   WM_APP+1214
#define IDM_APLST_TOGGLEPOPUP WM_APP+1215

#define IDM_SPREV_SETTINGS WM_APP+1300
#define IDM_SPREV_FULLPREV WM_APP+1301

#define IDM_SYSTRY_RUNPS   WM_APP+1400
#define IDM_SYSTRY_OPENPS  WM_APP+1401
#define IDM_SYSTRY_OPENCPL WM_APP+1402
#define IDM_SYSTRY_HIDEME  WM_APP+1403
#define IDM_SYSTRY_PURCH   WM_APP+1405
#define IDM_SYSTRY_DBGEXIT WM_APP+1406

#define IDM_DISPLAYTUT1 WM_APP+1500
#define IDM_DISPLAYTUT2 WM_APP+1501
#define IDM_DISPLAYTUT3 WM_APP+1502
#define IDM_DISPLAYTUT4 WM_APP+1503
#define IDM_DISPLAYTUT5 WM_APP+1504
#define IDM_DISPLAYTUT6 WM_APP+1505
#define IDM_DISPLAYTUT7 WM_APP+1506

#define IDM_MSHEET_HELP           0xA000+100
#define IDM_DLGOK_HELP            0xA000+101
#define IDM_DLGCANCEL_HELP        0xA000+102
#define IDM_DLGAPPLY_HELP         0xA000+103
#define IDM_DEFOK_HELP            0xA000+104
#define IDM_DEFCANCEL_HELP        0xA000+105
#define IDM_DEFAPPLY_HELP         0xA000+106
#define IDM_GHELPBTN_HELP         0xA000+107
#define IDM_ABOUTBTN_HELP         0xA000+108
#define IDM_PREFSBTN_HELP         0xA000+109
#define IDM_PURCHBTN_HELP         0xA000+110
#define IDM_SLIST_HELP            0xA000+111
#define IDM_CLEARSEL_HELP         0xA000+112
#define IDM_ADDSAVER_HELP         0xA000+113
#define IDM_SAVERINFO_HELP        0xA000+114
#define IDM_SETTINGS_HELP         0xA000+115
#define IDM_PREVIEW_HELP          0xA000+116
#define IDM_EDITINFO_HELP         0xA000+117
#define IDM_PREVIEWWND_HELP       0xA000+118
#define IDM_SHOWPREV_HELP         0xA000+119
#define IDM_THEMESEL_HELP         0xA000+120
#define IDM_EDITTHEMES_HELP       0xA000+121
#define IDM_RATINGSEL_HELP        0xA000+122
#define IDM_EDITHELP_HELP         0xA000+123
#define IDM_MUSICSEL_HELP         0xA000+124
#define IDM_MUSICBROWSE_HELP      0xA000+125
#define IDM_MUSICCYCLE_HELP       0xA000+126
#define IDM_MUSICSHUFFLE_HELP     0xA000+127
#define IDM_SAVERDESC_HELP        0xA000+128
#define IDM_NOMINIPREV_HELP       0xA000+129
#define IDM_THEMESLIST_HELP       0xA000+130
#define IDM_NEWTHEME_HELP         0xA000+131
#define IDM_DELTHEME_HELP         0xA000+132
#define IDM_RENTHEME_HELP         0xA000+133
#define IDM_DEFTHEMES_HELP        0xA000+134
#define IDM_THEMESHELP_HELP       0xA000+135
#define IDM_NEWTHEMEEDIT_HELP     0xA000+136
#define IDM_RENTHEMEEDIT_HELP     0xA000+137
#define IDM_LOADMUSFILE_HELP      0xA000+138
#define IDM_LOADMUSPLIST_HELP     0xA000+139
#define IDM_CLEARMUSFILE_HELP     0xA000+140
#define IDM_EDITAUDIO_HELP        0xA000+141
#define IDM_CHANGEMUS_HELP        0xA000+142
#define IDM_CURRPLIST_HELP        0xA000+143
#define IDM_PLISTSORT_HELP        0xA000+144
#define IDM_PLISTUP_HELP          0xA000+145
#define IDM_PLISTDOWN_HELP        0xA000+146
#define IDM_PLISTTOP_HELP         0xA000+147
#define IDM_PLISTBOTTOM_HELP      0xA000+148
#define IDM_PLISTDELETE_HELP      0xA000+149
#define IDM_PLISTCLEAR_HELP       0xA000+150
#define IDM_PLISTSAVE_HELP        0xA000+151
#define IDM_PLISTLOAD_HELP        0xA000+152
#define IDM_ONESAVER_HELP         0xA000+153
#define IDM_MULTISAVER_HELP       0xA000+154
#define IDM_SHOWSAVEREDT_HELP     0xA000+155
#define IDM_SHOWSAVERSPIN_HELP    0xA000+156
#define IDM_SAVERCYCLE_HELP       0xA000+157
#define IDM_SAVERSHUFFLE_HELP     0xA000+158
#define IDM_ENABLEHKEYS_HELP      0xA000+159
#define IDM_STARTSAVERHKY_HELP    0xA000+160
#define IDM_SKIPSAVERHKY_HELP     0xA000+161
#define IDM_OPENPSHKY_HELP        0xA000+162
#define IDM_CLEARSCREEN_HELP      0xA000+163
#define IDM_NOMUSIC_HELP          0xA000+164
#define IDM_OPENTHEMES_HELP       0xA000+165
#define IDM_OPENMUSICMGR_HELP     0xA000+166
#define IDM_ADVWARNING_HELP       0xA000+167
#define IDM_SHOWADVANCED_HELP     0xA000+168
#define IDM_SEARCHPATHLIST_HELP   0xA000+169
#define IDM_ADDPATH_HELP          0xA000+170
#define IDM_CHANGEPATH_HELP       0xA000+171
#define IDM_DELETEPATH_HELP       0xA000+172
#define IDM_SYSTEMTRAY_HELP       0xA000+173
#define IDM_KEEPCURRENT_HELP      0xA000+174
#define IDM_HIDEADVANCED_HELP     0xA000+175
#define IDM_ERRORLOGCHK_HELP      0xA000+176
#define IDM_MAXLINESEDT_HELP      0xA000+177
#define IDM_MAXLINESSPIN_HELP     0xA000+178
#define IDM_ERRORLOGBTN_HELP      0xA000+179
#define IDM_RESETMSGBTN_HELP      0xA000+180
#define IDM_HIDEADVBTN_HELP       0xA000+181
#define IDM_AUDIOHISTORY_HELP     0xA000+182
#define IDM_FILEBACKBTN_HELP      0xA000+183
#define IDM_FILEUPBTN_HELP        0xA000+184
#define IDM_AUDIOFILELIST_HELP    0xA000+185
#define IDM_FILETYPE_HELP         0xA000+186
#define IDM_CLEARAUDIOSEL_HELP    0xA000+187
#define IDM_ADDAUDIOFILE_HELP     0xA000+188
#define IDM_AUDIOPLIST_HELP       0xA000+189
#define IDM_AUDIOPLISTSORT_HELP   0xA000+190
#define IDM_AUDIOPLISTUP_HELP     0xA000+191
#define IDM_AUDIOPLISTTOP_HELP    0xA000+192
#define IDM_AUDIOPLISTDOWN_HELP   0xA000+193
#define IDM_AUDIOPLISTBOTTOM_HELP 0xA000+194
#define IDM_AUDIOPLISTDEL_HELP    0xA000+195
#define IDM_AUDIOPLISTCLR_HELP    0xA000+196
#define IDM_AUDIOPLISTSAVE_HELP   0xA000+197
#define IDM_AUDIOPLISTLOAD_HELP   0xA000+198
#define IDM_AUDIOINFO_HELP        0xA000+199
#define IDM_PLAYBTN_HELP          0xA000+200
#define IDM_PAUSEBTN_HELP         0xA000+201
#define IDM_STOPBTN_HELP          0xA000+202
#define IDM_FULLREWBTN_HELP       0xA000+203
#define IDM_REWBTN_HELP           0xA000+204
#define IDM_FWDBTN_HELP           0xA000+205
#define IDM_AUDIOPOS_HELP         0xA000+206
#define IDM_ENABLEPBC_HELP        0xA000+207
#define IDM_NEXTHKY_HELP          0xA000+208
#define IDM_VOLUPHKY_HELP         0xA000+209
#define IDM_VOLDNHKY_HELP         0xA000+210
#define IDM_MUTEHKY_HELP          0xA000+211
#define IDM_WINSYNTH_HELP         0xA000+212
#define IDM_DXSYNTH_HELP          0xA000+213
#define IDM_REVERB_HELP           0xA000+214
#define IDM_CHORUS_HELP           0xA000+215
#define IDM_MUSICMGRHELP_HELP     0xA000+216
#define IDM_INSTALLDX_HELP        0xA000+217
#define IDM_PLAYSFX_HELP          0xA000+218
#define IDM_TOOLTIPS_HELP         0xA000+219
#define IDM_SPLASHSCRN_HELP       0xA000+220
#define IDM_SAVERLISTDET_HELP     0xA000+221
#define IDM_RATINGIMGS_HELP       0xA000+222
#define IDM_SLISTPOPUP_HELP       0xA000+223
#define IDM_PLISTPOPUP_HELP       0xA000+224
#define IDM_PREFERENCES_HELP      0xA000+225
#define IDM_WBSLINK_HELP          0xA000+226
#define IDM_ASPLINK_HELP          0xA000+227
#define IDM_VIEWLICBTN_HELP       0xA000+228
#define IDM_VIEWREADMEBTN_HELP    0xA000+229
#define IDM_PSBUYLINK_HELP        0xA000+230
#define IDM_ORDERBTN_HELP         0xA000+231
#define IDM_MAILFORMBTN_HELP      0xA000+232

// constants //

// misc control id values
#define IDC_MAINSHEET      0xB000+100
#define IDC_DLGOKBTN       0xB000+101
#define IDC_DLGCANCELBTN   0xB000+102
#define IDC_DLGAPPLYBTN    0xB000+103
#define IDC_GHELPBTN       0xB000+104
#define IDC_ABOUTBTN       0xB000+105
#define IDC_PREFSBTN       0xB000+106
#define IDC_PURCHBTN       0xB000+107
#define IDC_DEFOKBTN       0xB000+108
#define IDC_DEFCANCELBTN   0xB000+109
#define IDC_DEFAPPLYBTN    0xB000+110
#define IDC_SLISTHEAD      0xB000+111
#define IDC_EDITSAVERDLG   0xB000+112
#define IDC_EDITTHEMESDLG  0xB000+113
#define IDC_CHGMUSICDLG    0xB000+114
#define IDC_CURRPLISTHEAD  0xB000+115
#define IDC_SHOWSVRSPIN    0xB000+116
#define IDC_MAXLINESSPIN   0xB000+117
#define IDC_AUDIOPLISTHEAD 0xB000+118
#define IDC_MUSICMGRDLG    0xB000+119
#define IDC_PREFERENCESDLG 0xB000+120
#define IDC_SYSTRAYICON    0xB000+121

// file view commands
#define IDM_VIEW_ICONS  0x7029
#define IDM_VIEW_LIST   0x702B
#define IDM_VIEW_DETAIL 0x702C
#define IDM_VIEW_THUMBS 0x702D
#define IDM_VIEW_TILES  0x702E

// max description length
#define MAX_SAVER_DESC 1000

// default sound id
#define ID_DEFSND    0xFFFFFFFFL
#define FORCE_DEFSND ID_DEFSND,TRUE

// no-selection text
#define NO_SEL_TEXT  "(None)"
#define NO_DESC_TEXT "(No description entered)"
#define NO_ITEM_TEXT "(Item not found)"

// minimum list width
#define MIN_LIST_WD 24

// playlist data increment
#define PLIST_DATA_INC 16

// ignore item data flag
#define IGNORE_ITEM_DATA ((LPVOID)0xFFFFFFFFL)

// saver info dialog offsets
#define SIDLG_OFFSET -80,5
#define SIDLG_NEGOFS 80,-5

// splash screen delay
#define SPLASH_DELAY 1250

// hand cursor (if not set)
#ifndef IDC_HAND
	#define IDC_HAND MAKEINTRESOURCE(32649)
#endif

// id index values
#define APID_NORMAL   0
#define APID_VERSION  1
#define APID_MINIPREV 2
#define APID_DEFSVR   3
#define APID_RUNPS    4
#define APID_TSRMODE  5

// misc. text items
#define INV_ITEMS_MSG "Some playlist items could not be found.\n\nInvalid items are shown in gray text the playlist."

#ifdef SHAREWARE_MODE
// trial days
#define TRIALDAYS_MAX 30
#endif

// executable name
#define EXE_NAME "ProSaver.scr"

// context-help window values
#define CHW_INITXSIZE   320
#define CHW_INITYSIZE   50
#define CHW_SHADOWSIZE  6
#define CHW_LMARGINSIZE 16
#define CHW_RMARGINSIZE 8
#define CHW_TMARGINSIZE 8
#define CHW_BMARGINSIZE 8
#define CHW_LINKGUTTER  14
#define CHW_LINKXSIZE   140
#define CHW_LINKYSIZE   16
#define CHW_RLINKMARGIN 12
#define CHW_BLINKMARGIN -2

// structures //

typedef struct tagPLAYLISTDATA
{
	// pointer to user data. NOTE: must be first so that user can cast this structure as pointer to his own data
	LPVOID lpUserData;
	// pointer to title string
	LPSTR lpTitle;
	// pointer to save string
	LPSTR lpSave;
} PLAYLISTDATA,*LPPLAYLISTDATA;

typedef struct tagFILELISTDATA
{
	// folder flags
	BOOL bIsFolder;
	BOOL bIsLinkToFolder;
	// pointer to data
	LPVOID lpData;
} FILELISTDATA,*LPFILELISTDATA;

// classes //

// pre-definitions
class CFileListCtrl;
class CDirTree;
class CFolderHistory;

// class definitions
class CMainPropSheet:public CPropertySheet
{
public:
	// constructor override
	CMainPropSheet(LPCTSTR pszCaption,
				   CWnd* pParentWnd=NULL,
				   UINT iSelectPage=0):CPropertySheet(pszCaption,
													  pParentWnd,
													  iSelectPage) {}

	// message handlers
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy(void);
	afx_msg void OnSysColorChange(void);
	afx_msg void OnDevModeChange(LPTSTR lpDeviceName);
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnShowWindow(BOOL bShow,
							  UINT nStatus);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnSysCommand(UINT nID,
							  LPARAM lParam);
	afx_msg LRESULT OnMCINotifyMode(WPARAM wParam,
									LPARAM lParam);
	afx_msg LRESULT OnMCINotifyPos(WPARAM wParam,
								   LPARAM lParam);
	afx_msg LRESULT OnWmHelp(WPARAM wParam,
							 LPARAM lParam);
	afx_msg LRESULT OnWmHotkey(WPARAM wParam,
							   LPARAM lParam);

	// button handlers
	afx_msg void OnGHelpBtn(void);
	afx_msg void OnAboutBtn(void);
	afx_msg void OnPrefsBtn(void);
	afx_msg void OnPurchBtn(void);

	// system overrides
	virtual BOOL OnNotify(WPARAM wParam,
						  LPARAM lParam,
						  LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// extra button methods
	BOOL CreateExtraButtons(void);
	void DestroyExtraButtons(void);

	// misc. methods
	void ApplyChanges(void);
	
	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CDefButton:public CExtButton
{
public:
	// constructor override
	CDefButton(UINT nID);

	// message handlers
	afx_msg void OnLButtonUp(UINT nFlags,
							 CPoint point);

	// sound functions
	void SetDefSoundId(UINT nID=NULL,
					   BOOL bAsyncFlag=TRUE);

	// sound id
	UINT nSndId;
	// async flag
	BOOL bAsync;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CExtDialog:public CDialog
{
public:
	// constructors
	CExtDialog(UINT nIDTemplate,
			   CWnd* pParentWnd=NULL):CDialog(nIDTemplate,
											  pParentWnd) {}
	CExtDialog():CDialog() {}

	// system overrides
	virtual BOOL OnInitDialog(void);
	virtual void OnOK(void);
	virtual void OnCancel(void);
	virtual void OnShowWindow(BOOL bShow,
							  UINT nStatus);

	// message handlers
	afx_msg void OnApply(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// overridables
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);
	virtual void ReleaseDialog(void);

	// misc. methods
	BOOL CaptureApplyBtn(CExtButton* lpBtn);
	void SetModified(BOOL bState=TRUE);
	void ApplyToClose(void);
	void CloseNotOK(void);

	// window buttons
	CExtButton* lpOKBtn;
	CExtButton* lpCancelBtn;
	CExtButton* lpApplyBtn;
	// close-ok flag
	BOOL bCloseOK;
	// must close flag
	BOOL bMustClose;
	
	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CPlaylistCtrl:public CListCtrl
{
public:
	// constructor
	CPlaylistCtrl();

	// notification handlers
	afx_msg void OnCustomDraw(NMHDR* pNMHDR,
							  LRESULT* pResult);
	afx_msg void OnItemChanged(NMHDR* pNMHDR,
							   LRESULT* pResult);
	afx_msg void OnRtClick(NMHDR* pNMHDR,
						   LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR,
						 LRESULT* pResult);

	// message handlers
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);
	afx_msg BOOL OnTTNeedText(UINT nID,
							  NMHDR* pNMHDR,
							  LRESULT* pResult);

	// system overrides
	virtual BOOL OnNotify(WPARAM wParam,
						  LPARAM lParam,
						  LRESULT* pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow(void);
	virtual int OnToolHitTest(CPoint point,
							  TOOLINFO* pTI) const;

	// initialization
	BOOL Init(LPSTR lpColHead);
	void SetButtonPtrs(CExtButton* lpUp,
					   CExtButton* lpDown,
					   CExtButton* lpTop,
					   CExtButton* lpBottom,
					   CExtButton* lpDelete,
					   CExtButton* lpClear,
					   CExtButton* lpSave,
					   CExtButton* lpLoad);
	void SetAuxCtrlPtrs(CWnd* lpAux1=NULL,
						CWnd* lpAux2=NULL,
						CWnd* lpAux3=NULL,
						CWnd* lpAux4=NULL);
	void SetParentDlg(CExtDialog* lpDlg);
	void SetParentPropPage(CPropertyPage* lpPropPage);
	void SetCtrlIds(UINT nID,
					UINT nHDR);
	void SetCallbacks(BOOL (*lpfnGetItemStringCallback)(LPSTR,LPVOID),
					  BOOL (*lpfnGetItemSaveCallback)(LPSTR,LPVOID),
					  LPVOID (*lpfnGetItemDataCallback)(LPSTR),
					  BOOL (*lpfnGetItemTooltipCallback)(LPSTR,LPVOID));

	// current selection functions
	BOOL QuerySelection(void);
	int GetSelection(void);

	// playlist commands
	BOOL AddToList(LPVOID lpItemData,
				   LPSTR lpTitle=NULL,
				   LPSTR lpSave=NULL,
				   BOOL bLoading=FALSE);
	void MoveSelUp(void);
	void MoveSelDown(void);
	void MoveSelTop(void);
	void MoveSelBottom(void);
	void DeleteSel(void);
	void ClearList(BOOL bSilent=FALSE);
	BOOL SaveListReg(LPCSTR lpAppKey,
				     LPCSTR lpSubKey);
	BOOL LoadListReg(LPCSTR lpAppKey,
				     LPCSTR lpSubKey);
	BOOL SaveListFile(LPSTR lpFilterList,
					  LPCSTR lpCaption,
					  LPCSTR lpStartDirReg,
					  LPCSTR lpFourCC,
					  LPCSTR lpDefExt,
					  LPSTR lpFileRet=NULL);
	BOOL LoadListFile(LPSTR lpFilterList,
					  LPCSTR lpCaption,
					  LPCSTR lpStartDirReg,
					  BOOL (*lpfnCheckFileCallback)(void),
					  LPSTR lpFileRet=NULL);

	// item info functions
	BOOL GetItemString(int nItem,
					   LPSTR lpStr);

	// callback functions
	BOOL (*GetItemStringCallback)(LPSTR,LPVOID);
	BOOL (*GetItemSaveCallback)(LPSTR,LPVOID);
	LPVOID (*GetItemDataCallback)(LPSTR);
	BOOL (*GetItemTooltipCallback)(LPSTR,LPVOID);

	// playlist control functions
	void DisableNavButtons(void);
	void EnableGlobalButtons(void);
	void DisableGlobalButtons(void);
	void SwapItems(int nItem1,
				   int nItem2,
				   BOOL bNoUpdate=FALSE);
	void RenumberItems(void);
	BOOL GetPlaylistItemData(int nItem,
							 LPPLAYLISTDATA* lplpData);
	BOOL HasInvalid(void);
	void PurgeInvalid(BOOL bSilent=FALSE);

	// misc. functions
	void SetParentModified(BOOL bState=TRUE);
	void EnableNavButtons(int nSelItem);
	int CellRectFromPoint(CPoint point,
						  LPRECT lprCell) const;
	void Release(void);

	// control ids
	UINT nCtrlId;
	UINT nHdrId;
	// header control
	CExtHeaderCtrl* lpHdrCtrl;
	// button pointers
	CExtButton* lpUpBtn;
	CExtButton* lpDownBtn;
	CExtButton* lpTopBtn;
	CExtButton* lpBottomBtn;
	CExtButton* lpDeleteBtn;
	CExtButton* lpClearBtn;
	CExtButton* lpSaveBtn;
	CExtButton* lpLoadBtn;
	// parent dialogs
	CExtDialog* lpParentDlg;
	CPropertyPage* lpParentPropPage;
	// pointer to playlist data
	LPPLAYLISTDATA lpPListData;
	// data item counters
	int nNumDataItems;
	int nMaxDataItems;
	// auxilliary controls
	CWnd* lpAuxCtrl1;
	CWnd* lpAuxCtrl2;
	CWnd* lpAuxCtrl3;
	CWnd* lpAuxCtrl4;
	// moving flag
	BOOL bMoving;
	// saved flag
	BOOL bIsSaved;
	
	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CFileInfo
{
public:
	// constructor
	CFileInfo();

	// object manipulation
	BOOL Add(CDirTree* lpParentNode,
			 LPITEMIDLIST lpTempIDList);
	BOOL AddToFileList(CFileListCtrl* lpFileList);
	BOOL Extract(void);
	void Delete(void);

	// object information
	BOOL GetPath(LPSTR lpPathRet);
	
	// pointer to parent
	CDirTree* lpParent;
	// item id list
	LPITEMIDLIST lpItemIDList;
	// next item
	CFileInfo* lpNext;
	// display name
	LPSTR lpDisplayName;
	// title
	LPSTR lpTitle;
	// icon image list
	HIMAGELIST hIconImgs;
	// icon index
	int nIconIdx;
	// extracted flag
	BOOL bExtracted;
	// file list data
	FILELISTDATA fld;
	// shared flag
	BOOL bIsShared;
	// link flang
	BOOL bIsLink;
	// link to folder flag
	BOOL bIsLinkToFolder;
	// extension
	LPSTR lpExtension;
	// file data
	LPSTR lpFileData;
	// user data
	DWORD dwUserData;
};

class CDirTree
{
public:
	// constructor
	CDirTree(HWND hParentWnd);

	// object handling methods
	BOOL CreateNamespaceRoot(CDirTree** lplpMyComputer);
	BOOL ExpandNode(BOOL bIsMyComputer=FALSE,
					BOOL bUseDriveFlag=FALSE,
					BOOL bDriveFlag=FALSE);
	void DeleteNode(void);
	BOOL AddChild(CDirTree* lpParentNode,
				  IShellFolder* lpNewFolder,
				  int nLevel,
				  LPITEMIDLIST lpTempIDList=NULL,
				  int nID=NULL);
	BOOL AddChildSpclFolder(CDirTree* lpParentNode,
							int nID,
							int nLevel);
	BOOL AddSibling(CDirTree* lpParentNode,
					IShellFolder* lpNewFolder,
					int nLevel,
				    LPITEMIDLIST lpTempIDList=NULL,
					int nID=NULL);
	void AlwaysDisplayBranch(BOOL bFlag=TRUE);
	void SetNoSortChildren(BOOL bFlag=TRUE);
	void ClearDisplayFlags(void);
	void SetDisplayFlags(void);
	CDirTree* LocateFolder(LPSTR lpPath);

	// info handling methods
	BOOL ExtractFolderInfo(void);
	BOOL ExtractFiles(void);
	BOOL AddToComboBox(CComboBox* lpCbx);
	BOOL AddFoldersToFileList(CFileListCtrl* lpFileList);
	BOOL AddFilesToFileList(CFileListCtrl* lpFileList);

	// pointer to parent
	CDirTree* lpParent;
	// parent window
	HWND hParent;
	// pointers to descendants
	CDirTree* lpChild;
	CDirTree* lpSibling;
	// shell folder interface
	IShellFolder* lpShellFolder;
	// pointer to id list
	LPITEMIDLIST lpItemIDList;
	// display name
	LPSTR lpDisplayName;
	// indentation level
	int nIndentLevel;
	// icon image list
	HIMAGELIST hIconImgs;
	// icon indices
	int nIconIdx;
	int nOpenIconIdx;
	// expanded flag
	BOOL bExpanded;
	// extracted flag
	BOOL bExtracted;
	// namespace root flag
	BOOL bIsNSRoot;
	// spcl folder id
	int nSpclFolderId;
	// display flags
	BOOL bDisplay;
	BOOL bAlwaysDisplay;
	// file info
	CFileInfo* lpFileInfo;
	// file list data
	FILELISTDATA fld;
	// shared flag
	BOOL bIsShared;
	// link flang
	BOOL bIsLink;
	// no-sort children flag
	BOOL bNoSortChildren;
};

class CHistoryComboBox:public CExtComboBox
{
public:
	// constructor override
	CHistoryComboBox(UINT nID);

	// notification handlers
	afx_msg BOOL OnTTNeedText(UINT nID,
							  NMHDR* pNMHDR,
							  LRESULT* pResult);

	// message handlers
	afx_msg void OnDestroy(void);
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);

	// system overrides
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow(void);
	virtual int OnToolHitTest(CPoint point,
							  TOOLINFO* pTI) const;

	// startup/shutdown
	BOOL Init(CExtDialog* lpParent=NULL);
	BOOL Link(CFileListCtrl* lpList);
	void Release(void);

	// folder manipulation methods
	BOOL ShowFolder(CDirTree* lpDirNode,
					BOOL bSaveInHist=TRUE);
	BOOL SelectFolder(CDirTree* lpDirNode);
	BOOL FolderUp(void);
	BOOL FolderBack(void);

	// directory tree
	CDirTree* lpDirTree;
	// file list
	CFileListCtrl* lpFileList;
	// parent dialog
	CExtDialog* lpParentDlg;
	// no-draw flag
	BOOL bNoDraw;
	// open selection
	int nOpenSel;
	// folder history
	CFolderHistory* lpHistRoot;
	CFolderHistory* lpHistCur;
	// pointer to 'My Computer'
	CDirTree* lpMyComputer;
	// current bounds
	CRect rCurBounds;
	// text-fit flag
	BOOL bTextFit;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CFileListCtrl:public CListCtrl
{
public:
	// constructor/destructor
	CFileListCtrl(UINT nID);

	// notification handlers
	afx_msg void OnCustomDraw(NMHDR* pNMHDR,
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
	afx_msg void OnDestroy(void);
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);

	// system overrides
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow(void);
	virtual int OnToolHitTest(CPoint point,
							  TOOLINFO* pTI) const;

	// current selection functions
	BOOL QuerySelection(void);
	int GetSelection(void);
	void ClearSelection(void);
	BOOL AddToPlaylist(void);

	// folder display methods
	BOOL ShowFolder(CDirTree* lpDirTree,
					BOOL bSaveInHist=TRUE);
	BOOL ShowFolder(int nIndex=-1,
					BOOL bSaveInHist=TRUE);
	BOOL ShowSelFolder(BOOL bSaveInHist=TRUE);
	BOOL ShowLinkedFolder(CFileInfo* lpFileInfo,
						  BOOL bSaveInHist=TRUE);
	BOOL SortFolder(BOOL bAsc=TRUE);
	BOOL ShowFolder(LPSTR lpPath,
					BOOL bSaveInHist=TRUE);

	// misc. methods
	int CellRectFromPoint(CPoint point,
						  LPRECT lprCell) const;

	// control id
	UINT nCtrlId;
	// history combo box
	CHistoryComboBox* lpHistoryCbx;
	// system image list
	CImageList* lpSysImageList;
	// filling flag
	BOOL bIsFilling;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CFolderHistory
{
public:
	// constructor
	CFolderHistory();

	// object handling methods
	BOOL AddNode(CDirTree* lpDirTree);
	void DeleteNode(void);

	// sibling objects
	CFolderHistory* lpPrev;
	CFolderHistory* lpNext;
	// saved folder
	CDirTree* lpSavedTree;
};

class CExtensionList
{
public:
	// constructor
	CExtensionList();

	// object manipulation
	BOOL Init(LPSTR lpDescription);
	int Add(LPSTR lpExt);
	BOOL GetString(LPSTR lpStr);
	int GetMatch(LPSTR lpExt);
	void Release(void);

	// description
	LPSTR lpDesc;
	// extension count
	int nNumExt;
	// extensions
	LPSTR* lplpExt;
};

class CExtensionGroup
{
public:
	// constructor
	CExtensionGroup();

	// object manipulation
	int AddList(LPSTR lpDesc);
	int AddExt(int nIndex,
			   LPSTR lpExt);
	BOOL GetString(LPSTR lpStr);
	CExtensionList* GetExtList(int nIndex);
	BOOL AddToComboBox(CComboBox* lpCbx);
	void Release(void);

	// list count
	int nNumList;
	// extension lists
	CExtensionList** lplpExtList;
};

class CFolderCtrlButton:public CExtButton
{
public:
	// constructor
	CFolderCtrlButton(UINT nID);

	// system overrides
	virtual BOOL PreTranslateMessage(MSG *pMsg);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CPreferencesDlg:public CExtDialog
{
public:
	// constructor
	CPreferencesDlg(UINT nIDTemplate,
				    CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
												      pParentWnd) {}

	// message handlers
	afx_msg void OnSaverListDetChkClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnHelpBtnClk(void);
	afx_msg LRESULT OnWmHelp(WPARAM wParam,
							 LPARAM lParam);

	// system overrides
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CSplashWnd:public CWnd
{
public:
	// constructor
	CSplashWnd();

	// message hanlders
	afx_msg void OnPaint(void);

	// misc. methods
	void DrawBitmap(LPPAINTSTRUCT lpPS=NULL);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CAboutDlg:public CExtDialog
{
public:
	// constructor
	CAboutDlg(UINT nIDTemplate,
			  CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
												pParentWnd) {}

	// message handlers
	afx_msg void OnLButtonDown(UINT nFlags,
							   CPoint point);
	afx_msg void OnMouseMove(UINT nFlags,
							 CPoint point);
	afx_msg void OnLicenseBtnClk(void);
	afx_msg void OnReadMeBtnClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);

	// system overrides
	virtual BOOL InitDialog(void);

	// window-shown flag
	BOOL bWinShown;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CPurchDlg:public CExtDialog
{
public:
	// constructor
	CPurchDlg(UINT nIDTemplate,
			  CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
												pParentWnd) {}

	// system overrides
	virtual BOOL InitDialog(void);
	virtual void ReleaseDialog(void);

	// message handlers
	afx_msg HBRUSH OnCtlColor(CDC* pDC,
							  CWnd* pWnd,
							  UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags,
							   CPoint point);
	afx_msg void OnMouseMove(UINT nFlags,
							 CPoint point);
	afx_msg void OnOrderBtnClk(void);
	afx_msg void OnMailFormBtnClk(void);
	afx_msg void OnContextMenu(CWnd* pWnd,
							   CPoint pos);
	afx_msg void OnShowWindow(BOOL bShow,
							  UINT nStatus);

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CContextHelpWnd:public CWnd
{
public:
	// constructor
	CContextHelpWnd();

	// message handlers
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy(void);
	afx_msg void OnLButtonDown(UINT nFlags,
							   CPoint point);
	afx_msg void OnKeyDown(UINT nChar,
						   UINT nRepCnt,
						   UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar,
							  UINT nRepCnt,
							  UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnPaint(void);
	afx_msg void OnMouseMove(UINT nFlags,
							 CPoint point);

	// system overrides
	virtual BOOL OnNotify(WPARAM wParam,
						  LPARAM lParam,
						  LRESULT* pResult);

	// painting methods
	void PaintWindow(CDC* lpDC);
	void PaintShadow(CDC* lpDC);

	// rich edit controls
	CExtRichEditCtrl* lpHelpTxt;
	CExtRichEditCtrl* lpLinkTxt;
	// stored link data
	DWORD dwSavedLinkData;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

class CWelcomeScrnDlg:public CExtDialog
{
public:
	// constructor
	CWelcomeScrnDlg(UINT nIDTemplate,
					CWnd* pParentWnd=NULL):CExtDialog(nIDTemplate,
													  pParentWnd) {}

	// system overrides
	virtual BOOL InitDialog(void);
	virtual void ApplyChanges(void);
	virtual void ReleaseDialog(void);
	virtual BOOL OnCommand(WPARAM wParam,
						   LPARAM lParam);

	// message hanlders
	afx_msg void OnDblClick(void);
	afx_msg void OnSelChange(void);

	// dialog controls
	CListBox* lpTutorialList;
	CButton* lpShowWndChk;
	// init flag
	BOOL bInitOK;

	// declare message map
	DECLARE_MESSAGE_MAP()
};

// application includes //

#include"resource.h"
#include"audio.h"
#include"savers.h"
#include"playback.h"
#include"svrmgr.h"
#include"dxaudio.h"

// globals //

// main property sheet
extern CMainPropSheet* g_lpMainSheet;
// sort images
extern CBitmap* g_lpSortUp;
extern CBitmap* g_lpSortDn;
extern CBitmap* g_lpSortNa;
// null-icon image
extern CBitmap* g_lpNullIcon;
// first-run flag
extern BOOL g_bFirstRun;
// options
extern BOOL g_bPlaySFX;
extern BOOL g_bShowToolTips;
// default buttons
extern CDefButton* g_lpDefOKBtn;
extern CDefButton* g_lpDefCancelBtn;
extern CDefButton* g_lpDefApplyBtn;
// global apply buttons
extern CExtButton* g_lpApplyBtn;
extern CExtButton* g_lpSubApplyBtn;
// misc. buttons
extern CExtButton* g_lpGHelpBtn;
extern CExtButton* g_lpAboutBtn;
extern CExtButton* g_lpPrefsBtn;
extern CExtButton* g_lpPurchBtn;
// file dialog boxes
extern CExtFileDialog* g_lpFileOpenDlg;
extern CExtFileDialog* g_lpFileSaveDlg;
// playlist sort images
extern CBitmap* g_lpPListUpBmp;
extern CBitmap* g_lpPListDownBmp;
extern CBitmap* g_lpPListTopBmp;
extern CBitmap* g_lpPListBottomBmp;
extern CBitmap* g_lpPListUpBmpGr;
extern CBitmap* g_lpPListDownBmpGr;
extern CBitmap* g_lpPListTopBmpGr;
extern CBitmap* g_lpPListBottomBmpGr;
// last file list selection flag
extern BOOL g_bLastFileSelFlag;
// overlay icons
extern CImageList* g_lpOverlayIcons;
// navigation images
extern CBitmap* g_lpNavBackBmp;
extern CBitmap* g_lpNavBackBmpGr;
extern CBitmap* g_lpNavUpBmp;
extern CBitmap* g_lpNavUpBmpGr;
// tooltip control
extern CToolTipCtrl* g_lpMainToolTip;
// playback control images
extern CBitmap* g_lpPlayBmp;
extern CBitmap* g_lpPauseBmp;
extern CBitmap* g_lpStopBmp;
extern CBitmap* g_lpFullRewBmp;
extern CBitmap* g_lpRewBmp;
extern CBitmap* g_lpFwdBmp;
// playback control images (grayed)
extern CBitmap* g_lpPlayBmpGr;
extern CBitmap* g_lpPauseBmpGr;
extern CBitmap* g_lpStopBmpGr;
extern CBitmap* g_lpFullRewBmpGr;
extern CBitmap* g_lpRewBmpGr;
extern CBitmap* g_lpFwdBmpGr;
// splash screen flag
extern BOOL g_bSplashScreen;
// preferences dialog
extern CPreferencesDlg* g_lpPrefsDlg;
// preferences checkboxes
extern CExtButton* g_lpSplashScreenChk;
extern CExtButton* g_lpPlaySFXChk;
extern CExtButton* g_lpTooltipsChk;
extern CExtButton* g_lpSaverListDetChk;
extern CExtButton* g_lpRatingImagesChk;
extern CExtButton* g_lpSaverListPopupChk;
extern CExtButton* g_lpPlaylistPopupChk;
// preferences help button
extern CExtButton* g_lpPrefsHelpBtn;
// splash screen data
extern CSplashWnd* g_lpSplashWnd;
extern CBitmap* g_lpSplashBmp;
extern DWORD g_dwSplashTime;
// about dialog
extern CAboutDlg* g_lpAboutDlg;
// about box bitmaps
extern CBitmap* g_lpAboutBmp;
extern CBitmap* g_lpWBSLogoBmp;
extern CBitmap* g_lpASPLogoBmp;
// about box controls
extern CExtStatic* g_lpPSIconBox;
extern CExtStatic* g_lpPSTitleTxt;
extern CExtStatic* g_lpWBSLinkBox;
extern CExtStatic* g_lpASPLinkBox;
extern CExtButton* g_lpLicenseBtn;
extern CExtButton* g_lpReadMeBtn;
// purchase dialog
extern CPurchDlg* g_lpPurchDlg;
// purchase bitmaps
extern CBitmap* g_lpCCards1Bmp;
extern CBitmap* g_lpCCards2Bmp;
extern CBitmap* g_lpPSBuyBmp;
// purchase controls
extern CExtStatic* g_lpTrialDaysTxt;
extern CExtStatic* g_lpCCards1Box;
extern CExtStatic* g_lpCCards2Box;
extern CExtStatic* g_lpPSBuyBox;
extern CExtButton* g_lpOrderBtn;
extern CExtButton* g_lpMailFormBtn;
// default cursors
extern HCURSOR g_hArrowCur;
extern HCURSOR g_hHandCur;
// install path
extern LPSTR g_lpInstPath;
#ifdef SHAREWARE_MODE
// trial period data
extern DWORD g_dwTrialDays;
extern UINT g_nTrialDaysTimerID;
extern BOOL g_bTrialTextOn;
#endif
// allow-screensaver flag
extern BOOL g_bAllowWinSaver;
// saver-app init flag
extern BOOL g_bSaverAppInit;
// closing flag
extern BOOL g_bClosing;
// context help window
extern CContextHelpWnd* g_lpContextHelpWnd;

// prototypes //

// application info functions

extern LPCSTR ApplicationName(void);

extern LPCSTR ApplicationLongName(void);

extern LPCSTR ApplicationID(int nAlt=APID_NORMAL);

extern LPCSTR ApplicationIcon(void);

extern LPCSTR ApplicationCursor(void);

extern LPCSTR ApplicationRegistryPath(void);

// application execution functions

extern BOOL ApplicationInit(LPSAVEREXECINFO lpSEI);

extern void ApplicationExec(LPSAVEREXECINFO lpSEI);

extern void ApplicationRelease(LPSAVEREXECINFO lpSEI);

extern void MainSheetIsInit(void);

// main window execution functions

extern BOOL InitMainSheet(BOOL bPurchOnly=FALSE);

extern void ReleaseMainSheet(void);

// popup menu functions

extern void ShowPopupMenu(UINT nIDCtrl,
						  DWORD dwData=NULL,
						  DWORD dwData2=NULL,
						  DWORD dwData3=NULL,
						  DWORD dwData4=NULL);

// user info functions

extern BOOL LoadPreferences(void);

extern BOOL SavePreferences(void);

// gui object functions

extern BOOL CreateSortImages(void);

extern BOOL CreateNullIconImage(void);

extern BOOL CreateListControlFonts(HDC hDC,
								   CFont* lpFont=NULL);

extern BOOL CreatePlaylistBtnImages(void);

extern BOOL LoadOverlayIcons(void);

extern void ReleaseOverlayIcons(void);

extern BOOL CreateNavigationImages(void);

extern BOOL CreatePlaybackCtrlImages(void);

extern BOOL InitSplashScreen(void);

extern void WaitForSplashScreen(void);

extern void ReleaseSplashScreen(void);

extern BOOL InitDefCursors(void);

extern void ReleaseDefCursors(void);

extern void UpdateLCFontLocations(void);

// user interaction functions

extern void PlaySound(UINT nSndID=0xFFFFFFFFL,
					  BOOL bOverrideFlag=FALSE);

extern void PlaySyncSound(UINT nSndID=0xFFFFFFFFL,
						  BOOL bOverrideFlag=FALSE);

extern void ShowAboutDlg(void);

extern void ShowPreferencesDlg(void);

#ifdef SHAREWARE_MODE
extern void ShowPurchaseDlg(void);
#endif

// process checking functions

#ifdef DEBUG_MODE
extern void CheckProcessList(void);

extern BOOL IsProcessInList(LPSTR lpProc,
							LPSTR lpList);
#endif

// extension group functions

extern BOOL InitExtensionGroups(void);

extern void ReleaseExtensionGroups(void);

// playlist functions

extern LPSTR GetSaverPListFilterList(void);

extern LPSTR GetAudioPListFilterList(void);

extern BOOL CheckSaverPListFileCallback(void);

extern BOOL CheckAudioPListFileCallback(void);

extern BOOL IsValidSaverPList(LPSTR lpFile);

extern BOOL IsValidAudioPList(LPSTR lpFile);

extern BOOL IsValidPList(LPSTR lpFile,
						 LPCSTR lpFourCC);

extern BOOL PlaylistDataMatchesAudioItemData(LPVOID lpPD,
											 LPVOID lpID);

// sort functions

extern void SortIntList(int* lpnVal,
						int nNumVal);

extern int CALLBACK SortFileList(LPARAM lParam1,
								 LPARAM lParam2,
								 LPARAM lParamSort);

// trial limit functions

#ifdef SHAREWARE_MODE
extern DWORD GetTrialDaysRemaining(void);
#endif

extern void GetTimeStampLocations(LPSTR lpStr);

extern void ClearTimeStampLocations(LPSTR lpStr,
									DWORD dwBytes);

#ifdef SHAREWARE_MODE
extern void SetTimeStamp(LPTIMESTAMP lpTS,
						 DWORD dwLocID,
						 LPSTR lpTSLoc);

extern void GetTimeStamp(LPTIMESTAMP lpTS,
						 DWORD dwLocID,
						 DWORD dwUniID,
						 LPSTR lpTSLoc);

extern void SortTimeStamps(LPTIMESTAMP lpOut,
						   LPTIMESTAMP lpTS,
						   DWORD dwNumTS);

extern void ShowTrialDays(LPCSTR lpReg);

extern void CheckTrialDays(void);

extern void CALLBACK TrialDaysTimerProc(HWND hWnd,
									    UINT uMsg,
									    UINT idEvent,
									    DWORD dwTime);
#else
extern void ResetTimeStamps(void);
#endif

// mini-preview & def-saver functions

extern BOOL InitPreviewImageWindow(HWND hParentWnd);

extern void ReleasePreviewImageWindow(void);

extern BOOL AddPreviewImageWindowClass(void);

extern void RemovePreviewImageWindowClass(void);

extern LRESULT CALLBACK PreviewImageWindowProc(HWND hWnd,
											   UINT Msg,
											   WPARAM wParam,
											   LPARAM lParam);

extern void ProcessScreensaverMessages(void);

extern BOOL InitDefSaverWindow(void);

extern void ReleaseDefSaverWindow(void);

extern BOOL AddDefSaverWindowClass(void);

extern void RemoveDefSaverWindowClass(void);

extern LRESULT CALLBACK DefSaverWindowProc(HWND hWnd,
										   UINT Msg,
										   WPARAM wParam,
										   LPARAM lParam);

extern void SendCloseMessage(LPDWORD lpdwTimerId,
							 int* lpnTimer);

extern BOOL ConfirmScreensaverPassword(void);

extern void ChangeScreensaverPassword(HWND hParentWnd);

extern BOOL InitScreensaverMode(void);

extern void ExecScreensaverMode(void);

extern void ReleaseScreensaverMode(void);

// context help functions

extern BOOL InitContextHelpWnd(HWND hParentWnd=NULL);

extern BOOL UpdateContextHelpWnd(LPSTR lpText,
								 DWORD dwLinkData=NULL);

extern void ShowContextHelpWnd(int nXPos,
							   int nYPos);

extern void HideContextHelpWnd(void);

extern void ReleaseContextHelpWnd(void);

// misc. functions

extern BOOL KeepProSaverCurrent(void);

#ifdef SHAREWARE_MODE
extern void RunStandAlonePurchDlg(void);

extern BOOL RunExternalPurchDlg(void);
#endif

extern BOOL IsDefragRunning(void);

extern BOOL OpenProSaverConfig(void);

extern BOOL ShowHelp(UINT nIDCtrl,
					 CWnd* lpCtrlWnd);

extern BOOL ShowHelpTopic(DWORD dwLinkData);

extern void KillAllTimers(void);

extern BOOL RunWelcomeScreen(void);

extern BOOL RunProSaverExe(void);

// eof //

// Copyright 2006 WaveBreak Software
