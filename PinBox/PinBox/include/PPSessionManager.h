#pragma once
#include <vector>
#include "PPSession.h"
#include <webp/decode.h>
#include "opusfile.h"
#include <map>
#include <stack>

typedef struct
{
	u32 frameIndex = 0;
	u32 receivedPieces = 0;
	std::vector<FramePiece*> pieces;
} FrameSet;

typedef std::function<void(int code)> PPNotifyCallback;

class PPSessionManager
{
private:

	PPSession*										m_inputStreamSession = nullptr;
	u32												m_OldDown;
	u32												m_OldHold;
	u32												m_OldUp;
	short											m_OldCX;
	short											m_OldCY;
	short											m_OldCTX;
	short											m_OldCTY;
	bool											m_initInputFirstFrame = false;

	s32												mMainThreadPrio = 0;

	std::vector<PPSession*>							m_screenCaptureSessions;
	int												m_commandSessionIndex = 0;
	u32												m_connectedSession = 0;
	void											_startStreaming();
	void											_oneByOneConnectScreenCapture(int index, const char* ip, const char* port, PPNotifyCallback callback);

	std::vector<FrameSet*>							m_frameTrackTemp;
	std::map<int, FrameSet*>						m_frameTracker;
	Mutex*											m_frameTrackerMutex;
	u32												m_currentDisplayFrame = 0;
	u8*												m_preAllocBuffer = nullptr;
	//------------------------------------------
	// UI ref variables
	//------------------------------------------
	int												mManagerState = -1;
	char											mIPAddress[100] = "192.168.31.183:1234";
public:
	PPSessionManager();
	~PPSessionManager();

	void InitScreenCapture(u32 numberOfSessions);
	void StartStreaming(const char* ip, const char* port);
	void StopStreaming();
	void Close();

	void InitInputStream();
	void UpdateInputStream(u32 down, u32 hold, u32 up, short cx, short cy, short ctx, short cty);

	void SafeTrack(FramePiece* piece);
	void UpdateFrameTracker();

	int GetManagerState() { return mManagerState; };

	//------------------------------------------
	// UI ref functions
	//------------------------------------------
	char* getIPAddress() { return &mIPAddress[0]; }
	void setIPAddress(const char* ip) { snprintf(mIPAddress, sizeof mIPAddress, "%s", ip); }
};

