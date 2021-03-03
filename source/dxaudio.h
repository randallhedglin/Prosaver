// Copyright 2006 WaveBreak Software

// dxaudio.h -- DirectX Audio wrapper header

// classes

class CDXAudioInitDlg:public CExtDialog
{
public:
	// constructor
	CDXAudioInitDlg():CExtDialog() {}

	// declare message map
	DECLARE_MESSAGE_MAP()
};

// globals //

// audio initialized flag
extern BOOL g_bDXAudioInit;
// audio init-attempt flag
extern BOOL g_bDXAudioInitAttempt;
// performance interface
extern IDirectMusicPerformance8* g_lpPerformance;
// audio loader interface
extern IDirectMusicLoader8* g_lpAudioLoader;
// default audiopath interface
extern IDirectMusicAudioPath8* g_lpDefAudioPath;
// default audiopath buffer
extern IDirectSoundBuffer8* g_lpDefAudioBuf;
// audio segment counters
extern DWORD g_dwNumAudioSeg;
extern DWORD g_dwMaxAudioSeg;
// audio segment data
extern LPBYTE* g_lplpAudioData;
extern IDirectMusicSegment8** g_lplpAudioSeg;
// primary audio buffer
extern IDirectSoundBuffer* g_lpPrimaryBuf;
// primary segment data
extern IDirectMusicSegment8* g_lpPrimarySeg;
// dx audio init dialog
extern CDXAudioInitDlg* g_lpDXAudioInitDlg;

// constants //

// allocation block size
#define BLOCK_ALLOC_INC 1

// prototypes //

// object handling functions

extern BOOL DXAudioInit(BOOL bShowStatus);

extern void DXAudioRelease(void);

extern BOOL InitPerformance(void);

extern void ReleasePerformance(void);

extern BOOL InitAudioLoader(void);

extern void ReleaseAudioLoader(void);

extern void ClearAudioCache(void);

extern BOOL InitDefAudioPath(void);

extern void ReleaseDefAudioPath(void);

extern void SetAudioMasterVolume(float fVol);

extern void InvalidateAudioData(void);

extern BOOL InitPrimaryBuffer(void);

extern void ReleasePrimaryBuffer(void);

extern void StartPrimaryBuffer(void);

extern void StopPrimaryBuffer(void);

extern void PurgeAudioObjects(void);

extern void ShowDXStatusBox(void);

extern void HideDXStatusBox(void);

// audio segment functions

extern DWORD GetNextAudioSegment(void);

extern DWORD AddAudioSegment(LPCSTR lpFile);

extern void PlayPrimaryAudioSegment(DWORD dwIndex);

extern void StopAudioSegment(DWORD dwIndex);

extern void PurgeAudioSegments(void);

extern BOOL IsAudioSegmentPlaying(DWORD dwIndex);

extern void StopAllAudioSegments(void);

// audiopath functions

extern void SetAudioPathFXChorus(DWORD dwIndex=NO_OBJECT,
								 float fDepth=10,
								 float fFeedback=25,
								 float fFrequency=1.1F,
								 long lWaveform=DSFXCHORUS_WAVE_SIN,
								 float fDelay=16,
								 long lPhase=DSFXCHORUS_PHASE_90,
								 float fWetDryMix=50);

extern void SetAudioPathFXCompressor(DWORD dwIndex=NO_OBJECT,
									 float fGain=0,
									 float fAttack=10,
									 float fRelease=200,
									 float fThreshold=-20,
									 float fRatio=3,
									 float fPredelay=4);

extern void SetAudioPathFXDistortion(DWORD dwIndex=NO_OBJECT,
									 float fGain=-18,
									 float fEdge=15,
									 float fPostEQCenterFrequency=2400,
									 float fPostEQBandwidth=2400,
									 float fPreLowpassCutoff=8000);

extern void SetAudioPathFXEcho(DWORD dwIndex=NO_OBJECT,
							   float fFeedback=50,
							   float fLeftDelay=500,
							   float fRightDelay=500,
							   BOOL bSwapDelays=FALSE,
							   float fWetDryMix=50);

extern void SetAudioPathFXFlanger(DWORD dwIndex=NO_OBJECT,
								  float fDepth=100,
								  float fFeedback=-50,
								  float fFrequency=0.25F,
								  long lWaveform=DSFXFLANGER_WAVE_SIN,
								  float fDelay=2,
								  long lPhase=DSFXFLANGER_PHASE_ZERO,
								  float fWetDryMix=50);

extern void SetAudioPathFXGargle(DWORD dwIndex=NO_OBJECT,
								 DWORD dwRateHz=20,
								 DWORD dwWaveShape=DSFXGARGLE_WAVE_TRIANGLE);

extern void SetAudioPathFXReverb(DWORD dwIndex=NO_OBJECT,
								 DWORD dwType=DSFX_I3DL2_ENVIRONMENT_PRESET_DEFAULT,
								 long lQuality=2);

extern void SetAudioPathFXNone(DWORD dwIndex=NO_OBJECT);

extern BOOL SetAudioPathFXInterface(DWORD dwIndex,
									REFGUID rguidObject,
									REFGUID rguidInterface,
									LPVOID* lplpObject);

extern void ActivateAudioPath(DWORD dwIndex);

extern void InactivateAudioPath(DWORD dwIndex);

// eof

// Copyright 2006 WaveBreak Software
