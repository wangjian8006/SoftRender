#pragma once

#include <windows.h>
#include "Vector.h"

class DrawTexture
{
public:
	DrawTexture(unsigned int width, unsigned int height);
	~DrawTexture(void);

	void SetPixel(unsigned int x, unsigned int y, unsigned int color);
	unsigned int GetPixel(unsigned int x, unsigned int y);

	unsigned int Sample(const Vector2 &uv);
	DrawColor SampleColor(const Vector2 &uv);

private:
	unsigned int *bits;

	unsigned int m_iWidth;
	unsigned int m_iHeight;
};

