#pragma once

#include <Windows.h>

class DrawDevice
{
public:
	DrawDevice(int w, int h);
	~DrawDevice(void);

	int **framebuffer;
	float **zbuffer;

	void **GetFrameBuffer();
	void SetFrameBuffer(void* buffer);

	int GetDeviceWidth();
	int GetDeviceHeight();

	void ClearBuffer(int color);

	float GetZ(int x, int y);
	void SetZ(int x, int y, float z);
	void DrawPixel(int x, int y, int color);
private:
	int m_iDeviceWidth;
	int m_iDeviceHeight;
};

