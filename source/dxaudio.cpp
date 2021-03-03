// Copyright 2006 WaveBreak Software

// dxaudio.cpp -- DirectX Audio wrapper

// includes //

#include"main.h"

// message maps //

BEGIN_MESSAGE_MAP(CDXAudioInitDlg,CExtDialog)
END_MESSAGE_MAP()

// initialize globals //

// audio initialized flag
BOOL g_bDXAudioInit=FALSE;
// audio init-attempt flag
BOOL g_bDXAudioInitAttempt=FALSE;
// performance interface
IDirectMusicPerformance8* g_lpPerformance=NULL;
// audio loader interface
IDirectMusicLoader8* g_lpAudioLoader=NULL;
// default audiopath interface
IDirectMusicAudioPath8* g_lpDefAudioPath=NULL;
// default audiopath buffer
IDirectSoundBuffer8* g_lpDefAudioBuf=NULL;
// audio segment counters
DWORD g_dwNumAudioSeg=0;
DWORD g_dwMaxAudioSeg=0;
// audio segment data
LPBYTE* g_lplpAudioData=NULL;
IDirectMusicSegment8** g_lplpAudioSeg=NULL;
// primary audio buffer
IDirectSoundBuffer* g_lpPrimaryBuf=NULL;
// primary segment data
IDirectMusicSegment8* g_lpPrimarySeg=NULL;
// dx audio init dialog
CDXAudioInitDlg* g_lpDXAudioInitDlg=NULL;

// functions //

// DXAudioInit()

BOOL DXAudioInit(BOOL bShowStatus)
{
	// check init-attempt flag
	if(g_bDXAudioInitAttempt)
		return(g_bDXAudioInit);

	// set init-attempt flag
	g_bDXAudioInitAttempt=TRUE;

	// show status window
	if(bShowStatus)
		ShowDXStatusBox();

	// set temporary init flag
	BOOL bInit=TRUE;

	// init performance
	if(bInit) if(!InitPerformance())   bInit=FALSE;

	// init audio loader
	if(bInit) if(!InitAudioLoader())   bInit=FALSE;

	// init default audiopath
	if(bInit) if(!InitDefAudioPath())  bInit=FALSE;

	// init primary buffer
	if(bInit) if(!InitPrimaryBuffer()) bInit=FALSE;

	// copy flag
	g_bDXAudioInit=bInit;

	// check flag
	if(!bInit)
	{
		// hide status window
		HideDXStatusBox();

		// no good
		return(FALSE);
	}

	// reset volume levels
	SetAudioMasterVolume(1.0F);

	// add chorus effect
	if(g_bUseDXChorus)
		SetAudioPathFXChorus();

	// hide status window
	HideDXStatusBox();

	// ok
	return(TRUE);
}

// DXAudioRelease()

void DXAudioRelease(void)
{
	// purge objects
	PurgeAudioObjects();

	// release interfaces
	ReleasePrimaryBuffer();
	ReleaseDefAudioPath();
	ReleaseAudioLoader();
	ReleasePerformance();

	// reset initialized flags
	g_bDXAudioInit       =FALSE;
	g_bDXAudioInitAttempt=FALSE;
}

// InitPerformance()

BOOL InitPerformance(void)
{
	// create performance
	HRESULT hr=CoCreateInstance(CLSID_DirectMusicPerformance,
								NULL,
								CLSCTX_INPROC,
								IID_IDirectMusicPerformance8,
								(LPVOID*)&g_lpPerformance);

	// check for error
	if(FAILED(hr))
	{
		DisplayNEDXErrorMessage("Failed to create DirectX performance object.",
								NULL,
								hr);
		return(FALSE);
	}
	else
		AddCOMResource;

	// init performance
	hr=g_lpPerformance->InitAudio(NULL,
								  NULL,
								  g_hWnd,
								  (g_bUseDXReverb ? DMUS_APATH_SHARED_STEREOPLUSREVERB : DMUS_APATH_DYNAMIC_STEREO),
								  128,
								  DMUS_AUDIOF_ALL,
								  NULL);

	// check for error
	if(FAILED(hr))
	{
		DisplayNEDXErrorMessage("Failed to initialize DirectX performance object.",
								NULL,
								hr);
		return(FALSE);
	}

	// ok
	return(TRUE);
}

// InitAudioLoader()

BOOL InitAudioLoader(void)
{
	// create loader
	HRESULT hr=CoCreateInstance(CLSID_DirectMusicLoader,
								NULL,
								CLSCTX_INPROC,
								IID_IDirectMusicLoader8,
								(LPVOID*)&g_lpAudioLoader);

	// check for error
	if(FAILED(hr))
	{
		DisplayNEDXErrorMessage("Failed to create DirectX audio loader interface.",
								NULL,
								hr);
		return(FALSE);
	}
	else
		AddCOMResource;
	
	// ok
	return(TRUE);
}

// ReleasePerformance()

void ReleasePerformance(void)
{
	// check for performance
	if(g_lpPerformance)
	{
		// stop all output
		g_lpPerformance->Stop(NULL,
							  NULL,
							  0,
							  NULL);

		// close performance
		g_lpPerformance->CloseDown();
	}
	
	// release performance
	ReleaseCOMPtr(g_lpPerformance);
}

// ReleaseAudioLoader()

void ReleaseAudioLoader(void)
{
	// release pointer
	ReleaseCOMPtr(g_lpAudioLoader);
}

// StopAllAudioSegments()

void StopAllAudioSegments(void)
{
	// check flag
	if(g_bDXAudioInit)
	{
		// stop all output
		g_lpPerformance->Stop(NULL,
							  NULL,
							  0,
							  NULL);
	}
}

// ClearAudioCache()

void ClearAudioCache(void)
{
	// check flag
	if(g_bDXAudioInit)
	{
		// check interface
		if(g_lpAudioLoader)
		{
			// collect garbage
			g_lpAudioLoader->CollectGarbage();

			// clear cache
			g_lpAudioLoader->ClearCache(GUID_DirectMusicAllTypes);
		}
	}
}

// GetNextAudioSegment()

DWORD GetNextAudioSegment(void)
{
	// check counter
	if(g_dwNumAudioSeg==0)
	{
		// allocate memory
		if(!AllocMem((LPVOID*)&g_lplpAudioData,
					 sizeof(LPBYTE)*BLOCK_ALLOC_INC))
			return(NO_OBJECT);
		if(!AllocMem((LPVOID*)&g_lplpAudioSeg,
					 sizeof(IDirectMusicSegment8*)*BLOCK_ALLOC_INC))
			return(NO_OBJECT);

		// increment counter
		g_dwMaxAudioSeg=BLOCK_ALLOC_INC;
	}
	else if(g_dwNumAudioSeg>=g_dwMaxAudioSeg)
	{
		// expand memory
		if(!ExpandMem((LPVOID*)&g_lplpAudioData,
					  sizeof(LPBYTE)*g_dwMaxAudioSeg,
					  sizeof(LPBYTE)*BLOCK_ALLOC_INC))
			return(NO_OBJECT);
		if(!ExpandMem((LPVOID*)&g_lplpAudioSeg,
					  sizeof(IDirectMusicSegment8*)*g_dwMaxAudioSeg,
					  sizeof(IDirectMusicSegment8*)*BLOCK_ALLOC_INC))
			return(NO_OBJECT);

		// increment counter
		g_dwMaxAudioSeg+=BLOCK_ALLOC_INC;
	}

	// get return index
	DWORD dwIndex=g_dwNumAudioSeg;

	// increment counter
	g_dwNumAudioSeg++;

	// return index
	return(dwIndex);
}

// AddAudioSegment()

DWORD AddAudioSegment(LPCSTR lpFile)
{
	// used for error checking
	HRESULT hr;

	// get return index
	DWORD dwIndex=GetNextAudioSegment();

	// check index
	if(dwIndex==NO_OBJECT)
		return(NO_OBJECT);

	// check flag
	if(g_bDXAudioInit)
	{
		// reset audio data pointer
		g_lplpAudioData[dwIndex]=NULL;

		LockGlobalLongMsg()

		// convert filename to wide string
		MakeWideString((LPWSTR)g_lpLongMsg,
					   lpFile);

		// load segment
		hr=g_lpAudioLoader->LoadObjectFromFile(CLSID_DirectMusicSegment,
											   IID_IDirectMusicSegment8,
											   (LPWSTR)g_lpLongMsg,
											   (LPVOID*)&g_lplpAudioSeg[dwIndex]);

		UnlockGlobalLongMsg()

		// check for error
		if(FAILED(hr))
		{
			DisplayNEDXErrorMessage("Unable to load audio segment.",
								    (LPSTR)lpFile,
								    hr);
			return(NO_OBJECT);
		}
		else
			AddCOMResource;

		// set parameters for std midi (fails silently if file is not midi)
		g_lplpAudioSeg[dwIndex]->SetParam(GUID_StandardMIDIFile,
										  0xFFFFFFFFL,
										  0,
										  0,
										  NULL);
		
		// download any necessary resources
		hr=g_lplpAudioSeg[dwIndex]->Download(g_lpPerformance);
		
		// check for error
		if(FAILED(hr))
		{
			DisplayNEDXErrorMessage("Unable to download audio resources.",
								    (LPSTR)lpFile,
								    hr);
			return(NO_OBJECT);
		}

		// return index
		return(dwIndex);
	}

	// no good
	return(NO_OBJECT);
}

// StopAudioSegment()

void StopAudioSegment(DWORD dwIndex)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex>=g_dwNumAudioSeg)
	{
		DisplayFatalErrorMessage("Invalid audio segment index.",
								 "PlayAudioSegment()",
								 FALSE);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// stop segment
		g_lpPerformance->StopEx(g_lplpAudioSeg[dwIndex],
								0,
								NULL);
	}
}

// PurgeAudioSegments()

void PurgeAudioSegments(void)
{
	// counter
	DWORD dwCount;
	
	// stop all output
	StopAllAudioSegments();

	// check counter
	if(g_dwNumAudioSeg)
	{
		// unload objects
		if(g_lpAudioLoader)
			for(dwCount=0;dwCount<g_dwNumAudioSeg;dwCount++)
				if(g_lplpAudioSeg[dwCount])
				{
					// unload instrument data
					g_lplpAudioSeg[dwCount]->Unload(g_lpPerformance);

					// release object from loader
					g_lpAudioLoader->ReleaseObjectByUnknown(g_lplpAudioSeg[dwCount]);
				}

		// clear audio cache
		ClearAudioCache();

		// free segment memory & release
		for(dwCount=0;dwCount<g_dwNumAudioSeg;dwCount++)
		{
			// free memory
			FreeMem((LPVOID*)&g_lplpAudioData[dwCount]);
			
			// release interface
			ReleaseCOMPtr(g_lplpAudioSeg[dwCount]);
		}
	}

	// free memory objects
	FreeMem((LPVOID*)&g_lplpAudioData);
	FreeMem((LPVOID*)&g_lplpAudioSeg);
		
	// reset counters
	g_dwNumAudioSeg=0;
	g_dwMaxAudioSeg=0;
}

// PlayPrimaryAudioSegment()

void PlayPrimaryAudioSegment(DWORD dwIndex)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex>=g_dwNumAudioSeg)
	{
		DisplayFatalErrorMessage("Invalid audio segment index.",
								 "PlayPrimaryAudioSegment()",
								 FALSE);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// set start point
		g_lplpAudioSeg[dwIndex]->SetStartPoint(0);

		// play segment
		g_lpPerformance->PlaySegmentEx(g_lplpAudioSeg[dwIndex],
									   NULL,
									   NULL,
									   DMUS_SEGF_NOINVALIDATE|DMUS_SEGF_AFTERPREPARETIME,
									   0,
									   NULL,
									   NULL,
									   NULL);
	}
}

// IsAudioSegmentPlaying()

BOOL IsAudioSegmentPlaying(DWORD dwIndex)
{
	// check index
	if(dwIndex>=g_dwNumAudioSeg)
		return(FALSE);

	// check flag
	if(g_bDXAudioInit)
	{
		// check segment
		if(g_lpPerformance->IsPlaying(g_lplpAudioSeg[dwIndex],
									  NULL)==S_OK)
			return(TRUE);
	}

	// not playing
	return(FALSE);
}

// InitDefAudioPath()

BOOL InitDefAudioPath(void)
{
	// check interface
	if(g_lpPerformance)
	{
		// get audiopath
		HRESULT hr=g_lpPerformance->GetDefaultAudioPath(&g_lpDefAudioPath);

		// check for error
		if(FAILED(hr))
		{
			DisplayNEDXErrorMessage("Failed to get default audio path object.",
									NULL,
									hr);
			return(FALSE);
		}
		else
			AddCOMResource;

		// get default audiopath buffer
		hr=g_lpDefAudioPath->GetObjectInPath(DMUS_PCHANNEL_ALL,
											 DMUS_PATH_BUFFER,
											 0,
											 GUID_NULL,
											 0,
											 IID_IDirectSoundBuffer8,
											 (LPVOID*)&g_lpDefAudioBuf);

		// check for error
		if(FAILED(hr))
		{
			DisplayNEDXErrorMessage("Failed to get default audio buffer object.",
									NULL,
									hr);
			return(FALSE);
		}
		else
			AddCOMResource;
	}

	// ok
	return(TRUE);
}

// ReleaseDefAudioPath()

void ReleaseDefAudioPath(void)
{
	// release pointers
	ReleaseCOMPtr(g_lpDefAudioPath);
	ReleaseCOMPtr(g_lpDefAudioBuf);
}

// InvalidateAudioData()

void InvalidateAudioData(void)
{
	// check flag
	if(g_bDXAudioInit)
	{
		// invalidate performance
		g_lpPerformance->Invalidate(0,
									NULL);
	}
}

// InitPrimaryBuffer()

BOOL InitPrimaryBuffer(void)
{
	// check interface
	if(g_lpDefAudioPath)
	{
		// used for error checking
		HRESULT hr;

		// get primary buffer
		hr=g_lpDefAudioPath->GetObjectInPath(0,
											 DMUS_PATH_PRIMARY_BUFFER,
											 0,
											 GUID_NULL,
											 0,
											 IID_IDirectSoundBuffer,
											 (LPVOID*)&g_lpPrimaryBuf);

		// check for error
		if(FAILED(hr))
		{
			DisplayNEDXErrorMessage("Failed to get primary audio buffer object.",
									NULL,
									hr);
			return(FALSE);
		}
		else
			AddCOMResource;
	}

	// ok
	return(TRUE);
}

// ReleasePrimaryBuffer()

void ReleasePrimaryBuffer(void)
{
	// release interface
	ReleaseCOMPtr(g_lpPrimaryBuf);
}

// StartPrimaryBuffer()

void StartPrimaryBuffer(void)
{
	// check flag
	if(g_bDXAudioInit)
	{
		// play primary buffer
		g_lpPrimaryBuf->Play(NULL,
							 NULL,
							 DSBPLAY_LOOPING);
	}
}

// StopPrimaryBuffer()

void StopPrimaryBuffer(void)
{
	// check flag
	if(g_bDXAudioInit)
	{
		// stop primary buffer
		g_lpPrimaryBuf->Stop();
	}
}

// PurgeAllAudioObjects()

void PurgeAudioObjects(void)
{
	// purge all objects
	PurgeAudioSegments();
}

// SetAudioPathFXChorus()

void SetAudioPathFXChorus(DWORD dwIndex,
						  float fDepth,
						  float fFeedback,
						  float fFrequency,
						  long lWaveform,
						  float fDelay,
						  long lPhase,
						  float fWetDryMix)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXChorus()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path
		InactivateAudioPath(dwIndex);

		// get effect interface
		IDirectSoundFXChorus8* lpFX;
		if(SetAudioPathFXInterface(dwIndex,
								   GUID_DSFX_STANDARD_CHORUS,
								   IID_IDirectSoundFXChorus8,
								   (LPVOID*)&lpFX))
		{
			// prepare effect description
			DSFXChorus fx;
			fx.fWetDryMix=fWetDryMix;
			fx.fDepth    =fDepth;
			fx.fFeedback =fFeedback;
			fx.fFrequency=fFrequency;
			fx.lWaveform =lWaveform;
			fx.fDelay    =fDelay;
			fx.lPhase    =lPhase;

			// set effect parameters
			lpFX->SetAllParameters(&fx);

			// release interface
			ReleaseCOMPtr(lpFX);
		}

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// SetAudioPathFXCompressor()

void SetAudioPathFXCompressor(DWORD dwIndex,
							  float fGain,
							  float fAttack,
							  float fRelease,
							  float fThreshold,
							  float fRatio,
							  float fPredelay)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXCompressor()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path
		InactivateAudioPath(dwIndex);

		// get effect interface
		IDirectSoundFXCompressor8* lpFX;
		if(SetAudioPathFXInterface(dwIndex,
								   GUID_DSFX_STANDARD_COMPRESSOR,
								   IID_IDirectSoundFXCompressor8,
								   (LPVOID*)&lpFX))
		{
			// prepare effect description
			DSFXCompressor fx;
			fx.fGain     =fGain;
			fx.fAttack   =fAttack;
			fx.fRelease  =fRelease;
			fx.fThreshold=fThreshold;
			fx.fRatio    =fRatio;
			fx.fPredelay =fPredelay;

			// set effect parameters
			lpFX->SetAllParameters(&fx);

			// release interface
			ReleaseCOMPtr(lpFX);
		}

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// SetAudioPathFXDistortion()

void SetAudioPathFXDistortion(DWORD dwIndex,
							  float fGain,
							  float fEdge,
							  float fPostEQCenterFrequency,
							  float fPostEQBandwidth,
							  float fPreLowpassCutoff)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXDistortion()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path
		InactivateAudioPath(dwIndex);

		// get effect interface
		IDirectSoundFXDistortion8* lpFX;
		if(SetAudioPathFXInterface(dwIndex,
								   GUID_DSFX_STANDARD_DISTORTION,
								   IID_IDirectSoundFXDistortion8,
								   (LPVOID*)&lpFX))
		{
			// prepare effect description
			DSFXDistortion fx;
			fx.fGain                 =fGain;
			fx.fEdge                 =fEdge;
			fx.fPostEQCenterFrequency=fPostEQCenterFrequency;
			fx.fPostEQBandwidth      =fPostEQBandwidth;
			fx.fPreLowpassCutoff     =fPreLowpassCutoff;

			// set effect parameters
			lpFX->SetAllParameters(&fx);

			// release interface
			ReleaseCOMPtr(lpFX);
		}

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// SetAudioPathFXEcho()

void SetAudioPathFXEcho(DWORD dwIndex,
						float fFeedback,
						float fLeftDelay,
						float fRightDelay,
						BOOL bSwapDelays,
						float fWetDryMix)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXEcho()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path
		InactivateAudioPath(dwIndex);

		// get effect interface
		IDirectSoundFXEcho8* lpFX;
		if(SetAudioPathFXInterface(dwIndex,
								   GUID_DSFX_STANDARD_ECHO,
								   IID_IDirectSoundFXEcho8,
								   (LPVOID*)&lpFX))
		{
			// prepare effect description
			DSFXEcho fx;
			fx.fWetDryMix =fWetDryMix;
			fx.fFeedback  =fFeedback;
			fx.fLeftDelay =fLeftDelay;
			fx.fRightDelay=fRightDelay;
			fx.lPanDelay  =(long)bSwapDelays;

			// set effect parameters
			lpFX->SetAllParameters(&fx);

			// release interface
			ReleaseCOMPtr(lpFX);
		}

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// SetAudioPathFXFlanger()

void SetAudioPathFXFlanger(DWORD dwIndex,
						   float fDepth,
						   float fFeedback,
						   float fFrequency,
						   long lWaveform,
						   float fDelay,
						   long lPhase,
						   float fWetDryMix)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXFlanger()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path
		InactivateAudioPath(dwIndex);

		// get effect interface
		IDirectSoundFXFlanger8* lpFX;
		if(SetAudioPathFXInterface(dwIndex,
								   GUID_DSFX_STANDARD_FLANGER,
								   IID_IDirectSoundFXFlanger8,
								   (LPVOID*)&lpFX))
		{
			// prepare effect description
			DSFXFlanger fx;
			fx.fWetDryMix=fWetDryMix;
			fx.fDepth    =fDepth;
			fx.fFeedback =fFeedback;
			fx.fFrequency=fFrequency;
			fx.lWaveform =lWaveform;
			fx.fDelay    =fDelay;
			fx.lPhase    =lPhase;

			// set effect parameters
			lpFX->SetAllParameters(&fx);

			// release interface
			ReleaseCOMPtr(lpFX);
		}

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// SetAudioPathFXGargle()

void SetAudioPathFXGargle(DWORD dwIndex,
						  DWORD dwRateHz,
						  DWORD dwWaveShape)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXGargle()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path
		InactivateAudioPath(dwIndex);

		// get effect interface
		IDirectSoundFXGargle8* lpFX;
		if(SetAudioPathFXInterface(dwIndex,
								   GUID_DSFX_STANDARD_GARGLE,
								   IID_IDirectSoundFXGargle8,
								   (LPVOID*)&lpFX))
		{
			// prepare effect description
			DSFXGargle fx;
			fx.dwRateHz   =dwRateHz;
			fx.dwWaveShape=dwWaveShape;

			// set effect parameters
			lpFX->SetAllParameters(&fx);

			// release interface
			ReleaseCOMPtr(lpFX);
		}

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// SetAudioPathFXReverb()

void SetAudioPathFXReverb(DWORD dwIndex,
						  DWORD dwType,
						  long lQuality)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXReverb()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path
		InactivateAudioPath(dwIndex);

		// get effect interface
		IDirectSoundFXI3DL2Reverb8* lpFX;
		if(SetAudioPathFXInterface(dwIndex,
								   GUID_DSFX_STANDARD_I3DL2REVERB,
								   IID_IDirectSoundFXI3DL2Reverb8,
								   (LPVOID*)&lpFX))
		{
			// set type
			lpFX->SetPreset(dwType);

			// set quality
			lpFX->SetQuality(lQuality);

			// release interface
			ReleaseCOMPtr(lpFX);
		}

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// SetAudioPathFXNone()

void SetAudioPathFXNone(DWORD dwIndex)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXNone()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// set pointer to buffer
		IDirectSoundBuffer8* lpBuf;
		if(dwIndex==NO_OBJECT)
			lpBuf=g_lpDefAudioBuf;

		// disable path
		InactivateAudioPath(dwIndex);

		// set no effects
		lpBuf->SetFX(0,
					 NULL,
					 NULL);

		// enable path
		ActivateAudioPath(dwIndex);
	}
}

// ActivateAudioPath()

void ActivateAudioPath(DWORD dwIndex)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "ActivateAudioPath()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// enable path as needed
		if(dwIndex==NO_OBJECT)
			g_lpDefAudioPath->Activate(TRUE);
	}
}

// InactivateAudioPath()

void InactivateAudioPath(DWORD dwIndex)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "InactivateAudioPath()",
								 NULL);
		return;
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// disable path as needed
		if(dwIndex==NO_OBJECT)
			g_lpDefAudioPath->Activate(FALSE);
	}
}

// SetAudioPathFXInterface()

BOOL SetAudioPathFXInterface(DWORD dwIndex,
							 REFGUID rguidObject,
							 REFGUID rguidInterface,
							 LPVOID* lplpObject)
{
#ifdef DEBUG_MODE
	// verify index
	if(dwIndex!=NO_OBJECT)
	{
		DisplayFatalErrorMessage("Invalid audio path index.",
								 "SetAudioPathFXInterface()",
								 NULL);
		return(FALSE);
	}
#endif

	// check flag
	if(g_bDXAudioInit)
	{
		// get pointers to buffer
		IDirectSoundBuffer8* lpBuf;
		if(dwIndex==NO_OBJECT)
			lpBuf=g_lpDefAudioBuf;

		// prepare effect description
		DSEFFECTDESC dsed;
		dsed.dwSize       =sizeof(DSEFFECTDESC);
		dsed.dwFlags      =NULL;
		dsed.guidDSFXClass=rguidObject;
		dsed.dwReserved1  =NULL;
		dsed.dwReserved2  =NULL;

		// result code
		DWORD dwResult;

		// used for error checking
		HRESULT hr;

		// set effect on buffer
		hr=lpBuf->SetFX(1,
						&dsed,
						&dwResult);

		// check for error
		if(FAILED(hr))
		{
			DisplayNEDXErrorMessage("Unable to create effect interface.",
									NULL,
									hr);
			return(FALSE);
		}

		// get effect interface
		hr=lpBuf->GetObjectInPath(rguidObject,
								  0,
								  rguidInterface,
								  lplpObject);

		// check for error
		if(FAILED(hr))
		{
			DisplayNEDXErrorMessage("Unable to set effect interface.",
									NULL,
									hr);
			return(FALSE);
		}
		else
			AddCOMResource;

		// ok
		return(TRUE);
	}

	// no good
	return(FALSE);
}

// SetAudioMasterVolume()

void SetAudioMasterVolume(float fVol)
{
	// check flag
	if(g_bDXAudioInit)
	{
		// pointer to audiopath
		IDirectMusicAudioPath8* lpPath;

		// set pointer to primary audiopath
		lpPath=g_lpDefAudioPath;

		// clip volume if necessary
		if(fVol<0)
			fVol=0;
		else if(fVol>1)
			fVol=1;

		// adjust volume curve
		fVol=(float)sqrt(fVol);

		// compute attenuation value
		long lAtt=((long)(fVol*9600))-9600;

		// set volume of audiopath
		lpPath->SetVolume(lAtt,
						  0);
	}
}

// ShowDXStatusBox()

void ShowDXStatusBox(void)
{
	// create dialog
	AllocClassObject(g_lpDXAudioInitDlg,
					 CDXAudioInitDlg);

	// show window
	if(g_lpDXAudioInitDlg)
		g_lpDXAudioInitDlg->Create(IDD_DXINIT,
								   g_lpMainSheet);
}

// HideDXStatusBox()

void HideDXStatusBox(void)
{
	// check for window
	if(g_lpDXAudioInitDlg)
	{
		// cancel window
		g_lpDXAudioInitDlg->OnCancel();

		// release dialog
		FreeClassObject(g_lpDXAudioInitDlg);		
	}
}

// eof //

// Copyright 2006 WaveBreak Software
