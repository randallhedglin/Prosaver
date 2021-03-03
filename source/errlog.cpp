// Copyright 2006 WaveBreak Software

// errlog.cpp -- error logging system

// includes //

#include"main.h"

// functions //

// CErrorLog::CErrorLog()

CErrorLog::CErrorLog()
{
	// reset all members
	m_bIsInit        =FALSE;
	m_bLogMode       =FALSE;
	m_lpFilename     =NULL;
	m_lpMemBlock     =NULL;
	m_lpdwLineOfs    =NULL;
	m_dwLineLimit    =0;
	m_dwCurLineOfs   =0;
	m_dwMaxLineOfs   =0;
	m_dwFirstLineOfs =0;
	m_dwCurMemBlkSize=0;
	m_dwMaxMemBlkSize=0;
}

// CErrorLog::~CErrorLog()

CErrorLog::~CErrorLog()
{
	// call release
	Release();
}

// CErrorLog::Init()

BOOL CErrorLog::Init(LPSTR lpFilename,
					 DWORD dwLineLimit)
{
#ifdef DEBUG_MODE
	// verify string
	if(lpFilename==NULL)
	{
		DisplayErrorMessage("Invalid string value.",
							"CErrorLog::Init()",
							FALSE);
		return(FALSE);
	}
#endif

	// allocate memory for filename
	if(!AllocMem((LPVOID*)&m_lpFilename,
				 strlen(lpFilename)+1))
		return(FALSE);

	// copy filename
	strcpy(m_lpFilename,
		   lpFilename);

	// copy line limit
	m_dwLineLimit=dwLineLimit;

	// set init flag
	m_bIsInit=TRUE;

	// assume we are logging
	SetLogMode(TRUE);

	// load existing log
	Load();

	// ok
	return(TRUE);
}

// CErrorLog::Release()

void CErrorLog::Release(void)
{
	// perform final dump
	Dump();

	// release filename
	FreeMem((LPVOID*)&m_lpFilename);

	// release line offset table
	FreeMem((LPVOID*)&m_lpdwLineOfs);

	// release memory block
	FreeMem((LPVOID*)&m_lpMemBlock);

	// reset remaining members
	m_bIsInit        =FALSE;
	m_bLogMode       =FALSE;
	m_dwLineLimit    =0;
	m_dwCurLineOfs   =0;
	m_dwMaxLineOfs   =0;
	m_dwFirstLineOfs =0;
	m_dwCurMemBlkSize=0;
	m_dwMaxMemBlkSize=0;
}

// CErrorLog::ChangeLineLimit()

BOOL CErrorLog::ChangeLineLimit(DWORD dwLineLimit)
{
	// check init
	if(IsInit())
	{
		// set new line limit
		m_dwLineLimit=dwLineLimit;

		// ok
		return(TRUE);
	}

	// not init
	return(FALSE);
}

// CErrorLog::IsInit()

BOOL CErrorLog::IsInit(void)
{
	// return flag
	return(m_bIsInit);
}

// CErrorLog::GetLineLimit()

DWORD CErrorLog::GetLineLimit(void)
{
	// check init
	if(IsInit())
	{
		// return limit
		return(m_dwLineLimit);
	}

	// not init
	return(0);
}

// CErrorLog::AddDivider()

BOOL CErrorLog::AddDivider(int nLen)
{
	// string object
	CString lpStr;

	// counter
	int nCount;

	// check init
	if(IsInit())
	{
		// check log mode
		if(m_bLogMode)
		{
			// add '*'s
			for(nCount=0;nCount<nLen;nCount++)
				lpStr+="*";

			// add divider
			return(AddString(NULL,
							 (LPSTR)(LPCTSTR)lpStr));
		}
	}

	// not init
	return(FALSE);
}

// GetCurrentTimeStr()

LPSTR GetCurrentTimeStr(void)
{
	// strings
	static char lpStr[32];
	char lpYear[6];

	// current time
	SYSTEMTIME stCur;

	// time digits
	WORD wDay1;
	WORD wDay2;
	WORD wHour1;
	WORD wHour2;
	WORD wMin1;
	WORD wMin2;
	WORD wSec1;
	WORD wSec2;
	WORD wMSec1;
	WORD wMSec2;
	WORD wMSec3;

	// counter
	int nCtr;

	// clear string
	lpStr[0]=NULL;

	// get current time
	GetLocalTime(&stCur);

	// macros to extract digits
	#define GetDigits2(n,a,b)   a=n/10;  n-=(a*10);  b=n;
	#define GetDigits3(n,a,b,c) a=n/100; n-=(a*100); b=n/10; n-=(b*10); c=n;

	// extract digits
	GetDigits2(stCur.wDay,         wDay1, wDay2);
	GetDigits2(stCur.wHour,        wHour1,wHour2);
	GetDigits2(stCur.wMinute,      wMin1, wMin2);
	GetDigits2(stCur.wSecond,      wSec1, wSec2);
	GetDigits3(stCur.wMilliseconds,wMSec1,wMSec2,wMSec3);

	// add day of week
	switch(stCur.wDayOfWeek)
	{
	case(0): strcat(lpStr,"Sun "); break;
	case(1): strcat(lpStr,"Mon "); break;
	case(2): strcat(lpStr,"Tue "); break;
	case(3): strcat(lpStr,"Wed "); break;
	case(4): strcat(lpStr,"Thu "); break;
	case(5): strcat(lpStr,"Fri "); break;
	case(6): strcat(lpStr,"Sat "); break;
	}

	// set counter
	nCtr=strlen(lpStr);

	// add day
	lpStr[nCtr++]='0'+wDay1;
	lpStr[nCtr++]='0'+wDay2;
	lpStr[nCtr++]=NULL;

	// add month
	switch(stCur.wMonth)
	{
	case(1):  strcat(lpStr,"-Jan-"); break;
	case(2):  strcat(lpStr,"-Feb-"); break;
	case(3):  strcat(lpStr,"-Mar-"); break;
	case(4):  strcat(lpStr,"-Apr-"); break;
	case(5):  strcat(lpStr,"-May-"); break;
	case(6):  strcat(lpStr,"-Jun-"); break;
	case(7):  strcat(lpStr,"-Jul-"); break;
	case(8):  strcat(lpStr,"-Aug-"); break;
	case(9):  strcat(lpStr,"-Sep-"); break;
	case(10): strcat(lpStr,"-Oct-"); break;
	case(11): strcat(lpStr,"-Nov-"); break;
	case(12): strcat(lpStr,"-Dec-"); break;
	}

	// add year
	strcat(lpStr,
		   itoa((int)stCur.wYear,
				lpYear,
				10));

	// add ' '
	strcat(lpStr," ");

	// set counter
	nCtr=strlen(lpStr);

	// add time
	lpStr[nCtr++]='0'+wHour1;
	lpStr[nCtr++]='0'+wHour2;
	lpStr[nCtr++]=':';
	lpStr[nCtr++]='0'+wMin1;
	lpStr[nCtr++]='0'+wMin2;
	lpStr[nCtr++]=':';
	lpStr[nCtr++]='0'+wSec1;
	lpStr[nCtr++]='0'+wSec2;
	lpStr[nCtr++]='.';
	lpStr[nCtr++]='0'+wMSec1;
	lpStr[nCtr++]='0'+wMSec2;
	lpStr[nCtr++]='0'+wMSec3;
	lpStr[nCtr++]=NULL;

	// return string
	return(lpStr);
}

// CErrorLog::AddString()

BOOL CErrorLog::AddString(LPSTR lpType,
						  LPSTR lpStr)
{
#ifdef DEBUG_MODE
	// verify string
	if(lpStr==NULL)
	{
		DisplayErrorMessage("Invalid string value.",
							"CErrorLog::AddString()",
							FALSE);
		return(FALSE);
	}
#endif

	// string object
	CString lpNewStr;

	// string length
	DWORD dwLen;
	
	// substring pointer
	LPSTR lpSubStr=NULL;

	// check init
	if(IsInit())
	{
		// check log mode
		if(m_bLogMode)
		{
			// find newline
			lpSubStr=strchr(lpStr,
							'\n');

			// check newline
			if(lpSubStr)
			{
				// clip string
				lpSubStr[0]=NULL;

				// add string
				if(!AddString(lpType,
							  lpStr))
					return(FALSE);

				// add remaining string
				return(AddString(lpType,
								 &lpSubStr[1]));
			}
			else
			{
				// check length
				if(strlen(lpStr)>0)
				{
					// check for type
					if(lpType)
					{
						// add current time
						lpNewStr+=GetCurrentTimeStr();

						// add ' ('
						lpNewStr+=" (";

						// add type
						lpNewStr+=lpType;

						// add ') >> '
						lpNewStr+=") >> ";

						// add string
						lpNewStr+=lpStr;
					}
					else
					{
						// copy string
						lpNewStr+=lpStr;
					}

					// get length
					dwLen=(DWORD)lpNewStr.GetLength();

					// check memory block
					if((m_dwCurMemBlkSize+dwLen+1)>=m_dwMaxMemBlkSize)
					{
						// check for block
						if(m_dwMaxMemBlkSize==0)
						{
							// allocate block
							if(!AllocMem((LPVOID*)&m_lpMemBlock,
										 sizeof(char)*ERRLOG_MEMINC))
								return(FALSE);

							// set size
							m_dwMaxMemBlkSize=ERRLOG_MEMINC;
						}
						else
						{
							// expand block
							if(!ExpandMem((LPVOID*)&m_lpMemBlock,
										  sizeof(char)*m_dwMaxMemBlkSize,
										  sizeof(char)*ERRLOG_MEMINC))
								return(FALSE);

							// set size
							m_dwMaxMemBlkSize+=ERRLOG_MEMINC;
						}
					}

					// check offset list
					if((m_dwCurLineOfs+1)>=m_dwMaxLineOfs)
					{
						// check for list
						if(m_dwCurLineOfs==0)
						{
							// allocate block
							if(!AllocMem((LPVOID*)&m_lpdwLineOfs,
										 sizeof(DWORD)*ERRLOG_LINEINC))
								return(FALSE);

							// set size
							m_dwMaxLineOfs=ERRLOG_LINEINC;
						}
						else
						{
							// expand block
							if(!ExpandMem((LPVOID*)&m_lpdwLineOfs,
										  sizeof(DWORD)*m_dwMaxLineOfs,
										  sizeof(DWORD)*ERRLOG_LINEINC))
								return(FALSE);

							// set size
							m_dwMaxLineOfs+=ERRLOG_LINEINC;
						}
					}

					// save offset
					m_lpdwLineOfs[m_dwCurLineOfs++]=m_dwCurMemBlkSize;

					// add string
					strcpy(&m_lpMemBlock[m_dwCurMemBlkSize],
						   (LPCSTR)(LPCTSTR)lpNewStr);

					// add to current block
					m_dwCurMemBlkSize+=dwLen+1;
				}

				// ok
				return(TRUE);
			}
		}
	}

	// not init
	return(FALSE);
}

// CErrorLog::Dump()

BOOL CErrorLog::Dump(void)
{
	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// digits
	int nD1;
	int nD2;
	int nD3;
	int nD4;

	// counter
	DWORD dwCount;

	// check init
	if(IsInit())
	{
		// check log mode
		if(m_bLogMode)
		{
			// compact data
			if(!Compact())
				return(FALSE);

			// open file for output
			hFile=CreateFile(m_lpFilename,
							 GENERIC_WRITE,
							 NULL,
							 NULL,
							 CREATE_ALWAYS,
							 NULL,
							 NULL);

			// check handle
			if(hFile==INVALID_HANDLE_VALUE)
				return(FALSE);
			else
				AddWinResource

			// init digits
			nD4=0;
			nD3=0;
			nD2=0;
			nD1=1;

			// output lines
			for(dwCount=m_dwFirstLineOfs;dwCount<m_dwCurLineOfs;dwCount++)
			{
				// set digits
				g_lpErrorMsg[0]='0'+nD4;
				g_lpErrorMsg[1]='0'+nD3;
				g_lpErrorMsg[2]='0'+nD2;
				g_lpErrorMsg[3]='0'+nD1;
				g_lpErrorMsg[4]=' ';
				g_lpErrorMsg[5]=NULL;

				// add string
				strcat(g_lpErrorMsg,
					   &m_lpMemBlock[m_lpdwLineOfs[dwCount]]);

				// add cr/lf
				strcat(g_lpErrorMsg,
					   "\x0d\x0a");

				// output string
				if(!WriteFile(hFile,
							  (LPVOID)g_lpErrorMsg,
							  strlen(g_lpErrorMsg),
							  TRUE))
					break;

				// update digits
				nD1++; if(nD1>9)
					{ nD1=0; nD2++; if(nD2>9)
						{ nD2=0; nD3++; if(nD3>9)
							{ nD3=0; nD4++; if(nD4>9)
								nD4=0; } } } }

			// close file
			if(CloseHandle(hFile))
				RemoveWinResource

			// ok
			return(TRUE);
		}
	}

	// not init
	return(FALSE);
}

// CErrorLog::Load()

BOOL CErrorLog::Load(void)
{
	// file handle
	HANDLE hFile=INVALID_HANDLE_VALUE;

	// counter
	DWORD dwCount;

	// end-of-file flag
	BOOL bEof;

	// check init
	if(IsInit())
	{
		// open file for input
		hFile=CreateFile(m_lpFilename,
						 GENERIC_READ,
						 NULL,
						 NULL,
						 OPEN_EXISTING,
						 FILE_FLAG_SEQUENTIAL_SCAN,
						 NULL);

		// check handle
		if(hFile==INVALID_HANDLE_VALUE)
			return(FALSE);
		else
			AddWinResource

		// reset eof flag
		bEof=FALSE;

		// input lines
		while(!bEof)
		{
			// reset counter
			dwCount=0;

			// read line
			while(TRUE)
			{
				// read byte
				if(!ReadFile(hFile,
							 &g_lpErrorMsg[dwCount],
							 1,
							 TRUE))
				{
					// end of file
					bEof=TRUE;

					// stop here						
					break;
				}

				// check for cr/lf
				if(g_lpErrorMsg[dwCount]==0x0D||
				   g_lpErrorMsg[dwCount]==0x0A)
				{
					// get next byte
					ReadFile(hFile,
							 &g_lpErrorMsg[dwCount],
							 1,
							 TRUE);

					// check for cr/lf
					if(g_lpErrorMsg[dwCount]==0x0D||
					   g_lpErrorMsg[dwCount]==0x0A)
					{
						// stop here
						break;
					}
				}

				// next byte
				dwCount++;
			}

			// set terminator
			g_lpErrorMsg[dwCount]=NULL;

			// check length
			if(strlen(g_lpErrorMsg)>=5)
			{
				// add string (starting at byte 5)
				AddString(NULL,
						  &g_lpErrorMsg[5]);
			}

		}

		// close file
		if(CloseHandle(hFile))
			RemoveWinResource

		// ok
		return(TRUE);
	}

	// not init
	return(FALSE);
}

// CErrorLog::Compact()

BOOL CErrorLog::Compact(void)
{
	// memory block values
	DWORD dwMemBlkStart;
	DWORD dwMemBlkEnd;
	DWORD dwMemBlkNum;

	// line offset values
	DWORD dwLineOfsStart;
	DWORD dwLineOfsEnd;
	DWORD dwLineOfsNum;

	// counter
	DWORD dwCount;

	// check init
	if(IsInit())
	{
		// check log mode
		if(m_bLogMode)
		{
			// compare line count w/ limit
			if(m_dwCurLineOfs>m_dwLineLimit)
			{
				// compute first line
				m_dwFirstLineOfs=m_dwCurLineOfs-m_dwLineLimit;

				// check for double limit
				if(m_dwFirstLineOfs>m_dwLineLimit)
				{
					// compute line offset values
					dwLineOfsStart=m_dwFirstLineOfs;
					dwLineOfsEnd  =m_dwCurLineOfs;
					dwLineOfsNum  =dwLineOfsEnd-dwLineOfsStart;

					// compute memory block values
					dwMemBlkStart=m_lpdwLineOfs[dwLineOfsStart];
					dwMemBlkEnd  =m_dwCurMemBlkSize;
					dwMemBlkNum  =dwMemBlkEnd-dwMemBlkStart;

					// adjust line offsets
					for(dwCount=0;dwCount<dwLineOfsNum;dwCount++)
						m_lpdwLineOfs[dwCount]=m_lpdwLineOfs[dwLineOfsStart+dwCount]-dwMemBlkStart;

					// compress line offsets
					if(!CompressMem((LPVOID*)&m_lpdwLineOfs,
									sizeof(DWORD)*dwLineOfsNum))
						return(FALSE);

					// adjust current value
					m_dwCurLineOfs=dwLineOfsNum;
					
					// set max to current
					m_dwMaxLineOfs=m_dwCurLineOfs;

					// move memory block
					MoveMemory(m_lpMemBlock,
							   &m_lpMemBlock[dwMemBlkStart],
							   dwMemBlkNum);

					// compress memory block
					if(!CompressMem((LPVOID*)&m_lpMemBlock,
									sizeof(char)*dwMemBlkNum))
						return(FALSE);

					// adjust current value
					m_dwCurMemBlkSize=dwMemBlkNum;

					// set max to current
					m_dwMaxMemBlkSize=m_dwCurMemBlkSize;

					// reset first line
					m_dwFirstLineOfs=0;
				}
			}
			else
			{
				// reset first line
				m_dwFirstLineOfs=0;
			}

			// ok
			return(TRUE);
		}
	}

	// not init
	return(FALSE);
}

// CErrorLog::SetLogMode()

void CErrorLog::SetLogMode(BOOL bLogMode)
{
	// check init
	if(IsInit())
	{
		// copy flag
		m_bLogMode=bLogMode;
	}
}

// eof //

// Copyright 2006 WaveBreak Software

