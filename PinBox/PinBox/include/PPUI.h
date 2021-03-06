#pragma once
#ifndef _PP_UI_H_
#define _PP_UI_H_
#include <3ds.h>
#include "PPGraphics.h"
#include "PPSessionManager.h"

//#define UI_DEBUG 1

typedef std::function<int()> PopupCallback;
typedef std::function<void(void* arg1, void* arg2)> ResultCallback;

class PPLog
{
private:
	const u32						mLogMaxSize = 100;
	std::vector<std::string>		mLogContainer;
	Mutex*							mLogMutex;
	
public:
	void							InitLog();
	void							Write(const char* log);
};


class PPUI
{

public:
	static u32 getKeyDown();
	static u32 getKeyHold();
	static u32 getKeyUp();
	static circlePosition getLeftCircle();
	static circlePosition getRightCircle();

	static u32 getSleepModeState();

	static void UpdateInput();
	static bool TouchDownOnArea(float x, float y, float w, float h);
	static bool TouchUpOnArea(float x, float y, float w, float h);

	// SCREEN
	static int DrawIdleTopScreen(PPSessionManager *sessionManager);
	static int DrawNumberInputScreen( const char* label, ResultCallback cancel, ResultCallback ok);
	static int DrawBottomScreenUI(PPSessionManager *sessionManager);
	static int DrawIdleBottomScreen(PPSessionManager *sessionManager);
	
	// BUTTON
	static bool FlatButton(float x, float y, float w, float h, const char* label);
	static bool FlatDarkButton(float x, float y, float w, float h, const char* label);
	static bool FlatColorButton(float x, float y, float w, float h, const char* label, ppColor colNormal, ppColor colActive, ppColor txtCol);

	// TEXT
	static void InputField(float x, float y, float w, float h, const char* defaultValue, const char* placeHolder);
	static void LabelBox(float x, float y, float w, float h, const char* label, ppColor bgColor, ppColor txtColor);

	// POPUP
	static bool HasPopup();
	static PopupCallback GetPopup();
	static void ClosePopup();
	static void AddPopup(PopupCallback callback);

	// LOG
	static int LogWindow(float x, float y, float w, float h);
};

#endif