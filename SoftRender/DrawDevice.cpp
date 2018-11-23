#include "DrawDevice.h"


DrawDevice::DrawDevice(int w, int h)
{
	this->m_iDeviceWidth = w;
	this->m_iDeviceHeight = h;

	this->framebuffer = (int**)malloc(sizeof(void*) * h);
	this->zbuffer = (float**)malloc(sizeof(void*) * h);

	for (int i = 0; i < h; ++i)
	{
		this->framebuffer[i] = (int*)malloc(w * 4);
		this->zbuffer[i] = (float*)malloc(w * 4);
	}
}

DrawDevice::~DrawDevice(void)
{
}

void** DrawDevice::GetFrameBuffer()
{
	return (void**)this->framebuffer;
}

void DrawDevice::SetFrameBuffer(void* buffer)
{
	for (int j = 0; j < this->m_iDeviceHeight; j++) {
		this->framebuffer[j] = (int*)((char*)buffer + this->m_iDeviceWidth * 4 * j);
	}
}

int DrawDevice::GetDeviceWidth()
{
	return this->m_iDeviceWidth;
}
int DrawDevice::GetDeviceHeight()
{
	return this->m_iDeviceHeight;
}

void DrawDevice::ClearBuffer(int color)
{
	int y, x;
	for (y = 0; y < this->m_iDeviceHeight; y++)
	{
		int *dst = this->framebuffer[y];
		for (x = this->m_iDeviceWidth; x > 0; dst++, x--) dst[0] = color;
	}
	for (y = 0; y < this->m_iDeviceHeight; y++)
	{
		float *dst = this->zbuffer[y];
		for (x = this->m_iDeviceWidth; x > 0; dst++, x--) dst[0] = 0.0f;
	}
}

float DrawDevice::GetZ(int x, int y)
{
	if (x >= 0 && x < this->m_iDeviceWidth && y >= 0 && y < this->m_iDeviceHeight)
		return this->zbuffer[y][x];
	else
		return 1.f;
}

void DrawDevice::SetZ(int x, int y, float z)
{
	if (x >= 0 && x < this->m_iDeviceWidth && y >= 0 && y < this->m_iDeviceHeight)
	{
		this->zbuffer[y][x] = z;
	}
}

void DrawDevice::DrawPixel(int x, int y, int color)
{
	if (x >= 0 && y >= 0 &&x < this->m_iDeviceWidth && y < this->m_iDeviceHeight)
	{
		this->framebuffer[y][x] = color;
	}
}