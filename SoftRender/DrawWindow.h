#pragma once

#include <Windows.h>
#include <tchar.h>
#include "DrawDevice.h"

class DrawWindow
{
public:
	static bool WINDOW_CLOSE;
	static int KEYS[512];
public:
	DrawWindow(DrawDevice* device);
	//~DrawWindow();

	int InitWindow(int w, int h, const TCHAR* title);
	void WindowUpdate();
	bool CheckClose();

private:
	HWND m_hwnd;
	HDC m_hdc;
	HBITMAP m_ScreenDIB;		// DIB
	HBITMAP m_ScreenOldDIB;		// ÀÏµÄ BITMAP
	int m_iWidth, m_iHeight;

	DrawDevice* m_device;

	void WindowMessageDispatch();
};