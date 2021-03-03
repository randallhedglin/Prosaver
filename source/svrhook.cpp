// Copyright 2006 WaveBreak Software

// svrhook.cpp -- saver hook procedture

// includes //

#include"svrhook.h"

// globals //

// handle to hook proc
HHOOK g_hHook=(HHOOK)INVALID_HANDLE_VALUE;

// functions //

// CreateSaverHook()

BOOL WINAPI CreateSaverHook(DWORD dwThreadId)
{
	// get handle to this module
	HMODULE hSvrHookDll=GetModuleHandle("svrhook.dll");

	// check handle
	if(hSvrHookDll==NULL)
		return(FALSE);

	// define hook proc
	typedef LRESULT (CALLBACK *SAVERHOOKGETMSGPROC) (int,WPARAM,LPARAM);

	// find hook proc
 	SAVERHOOKGETMSGPROC SaverHookGetMsgProcA=(SAVERHOOKGETMSGPROC)GetProcAddress(hSvrHookDll,
																				 (LPCSTR)2);

	// check proc address
	if(SaverHookGetMsgProcA==NULL)
		return(FALSE);

	// hook saver thread
	g_hHook=SetWindowsHookEx(WH_GETMESSAGE,
							 (HOOKPROC)SaverHookGetMsgProcA,
							 hSvrHookDll,
							 dwThreadId);

	// check for error
	if(g_hHook==NULL)
		return(FALSE);

	// ok
	return(TRUE);
}

// SaverHookGetMsgProc()

LRESULT CALLBACK SaverHookGetMsgProc(int nCode,
									 WPARAM wParam,
									 LPARAM lParam)
{
	// check code
	if(nCode<0)
	{
		// must pass it on
		return(CallNextHookEx(g_hHook,
							  nCode,
							  wParam,
							  lParam));
	}

	// cast pointer to message
	LPMSG lpMsg=(LPMSG)lParam;

	// check message
	switch(lpMsg->message)
	{
	// quitting
	case(WM_QUIT):

		// unhook window
		UnhookWindowsHookEx(g_hHook);

		// reset handle
		g_hHook=(HHOOK)INVALID_HANDLE_VALUE;

		// ok
		break;

	// key-down messages
	case(WM_KEYDOWN):
	case(WM_SYSKEYDOWN):

		// check ctrl-alt-shift
		if(IsKeyDown(VK_CONTROL)||
		   IsKeyDown(VK_MENU)||
		   IsKeyDown(VK_SHIFT))
		{
			// eat message
			lpMsg->message=NULL;

			// stop here
			return(0);
		}

		// ok
		break;

	// key-up messages
	case(WM_KEYUP):
	case(WM_SYSKEYUP):

		// eat message
		lpMsg->message=NULL;

		// stop here
		return(0);
	}

	// pass it on
	return(CallNextHookEx(g_hHook,
						  nCode,
						  wParam,
						  lParam));
}

// eof //
