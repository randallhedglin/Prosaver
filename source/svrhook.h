// Copyright 2006 WaveBreak Software

// svrhook.h -- saver hook proc header

// defines //

// use strict compiling
#define STRICT
// exclude unnecessary code
#define VC_EXTRALEAN

// includes //

#include<windows.h>
#include<winuser.h>

// constants //

// globals //

// handle to hook proc
extern HHOOK g_hHook;

// export protoypes //

extern _declspec(dllexport) BOOL WINAPI CreateSaverHook(DWORD dwThreadId);

extern _declspec(dllexport) LRESULT CALLBACK SaverHookGetMsgProc(int nCode,
																 WPARAM wParam,
																 LPARAM lParam);

// macros //

#define IsKeyDown(a) (GetAsyncKeyState(a)&0x8000)

// eof //
