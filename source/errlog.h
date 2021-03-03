// Copyright 2006 WaveBreak Software

// errlog.h -- error logging header

// constants //

#define ERRLOG_LINEINC 32
#define ERRLOG_MEMINC  4096

// classes //

class CErrorLog
{
public:
	// contruction/destruction
	CErrorLog();
	~CErrorLog();

	// initialization/shutdown
	BOOL Init(LPSTR lpFilename,
			  DWORD dwLineLimit);
	void Release(void);

	// operations
	BOOL ChangeLineLimit(DWORD dwLineLimit);
	void SetLogMode(BOOL bLogMode);
	BOOL AddDivider(int nLen);
	BOOL AddString(LPSTR lpType,
				   LPSTR lpStr);
	BOOL Load(void);
	BOOL Dump(void);
	BOOL Compact(void);

	// info functions
	BOOL IsInit(void);
	DWORD GetLineLimit(void);

	// initialized flag
	BOOL m_bIsInit;
	// log mode flag
	BOOL m_bLogMode;
	// copy of filename
	LPSTR m_lpFilename;
	// line limit
	DWORD m_dwLineLimit;
	// line offset table
	LPDWORD m_lpdwLineOfs;
	// line offset counters
	DWORD m_dwCurLineOfs;
	DWORD m_dwMaxLineOfs;
	DWORD m_dwFirstLineOfs;
	// memory block
	LPSTR m_lpMemBlock;
	// memory block sizes
	DWORD m_dwCurMemBlkSize;
	DWORD m_dwMaxMemBlkSize;
};

// prototypes //

extern LPSTR GetCurrentTimeStr(void);

// eof //

// Copyright 2006 WaveBreak Software
