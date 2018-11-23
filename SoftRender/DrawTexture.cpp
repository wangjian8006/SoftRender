#include "DrawTexture.h"


DrawTexture::DrawTexture(unsigned int width, unsigned int height)
{
	bits = new unsigned int[height * width];
	this->m_iWidth = width;
	this->m_iHeight = height;

	memset(bits, 0, this->m_iHeight * this->m_iWidth * sizeof(unsigned int));
}

DrawTexture::~DrawTexture(void)
{
}

void DrawTexture::SetPixel(unsigned int x, unsigned int y, unsigned int color)
{
	if (x >= this->m_iWidth || y >= this->m_iHeight) return;
	this->bits[y * this->m_iHeight + x] = color;
}
unsigned int DrawTexture::GetPixel(unsigned int x, unsigned int y)
{
	if (x >= this->m_iWidth || y >= this->m_iHeight) return 0;
	return this->bits[y * this->m_iHeight + x];
}
unsigned int DrawTexture::Sample(const Vector2 &uv)
{
	if (uv.x >= 0 && uv.x <= 1 && uv.y >= 0 && uv.y <= 1)
	{
		UINT x = (UINT)(uv.x * (this->m_iWidth - 1));
		UINT y = (UINT)(uv.y * (this->m_iHeight - 1));
		return this->bits[y * this->m_iHeight + x];
	}
	else
	{
		float u = uv.x;
		float v = uv.y;

		if (uv.x > 1) u = uv.x - static_cast<int>(uv.x);
		else if (uv.x < 0) u = (static_cast<int>(-uv.x) + 1) + uv.x;

		if (uv.y > 1) v = uv.y - static_cast<int>(uv.y);
		else if (uv.y < 0) v = (static_cast<int>(-uv.y) + 1) + uv.y;

		//printf("%f %f\r\n", u, v);

		UINT x = (UINT)(u * (this->m_iWidth - 1.0f));
		UINT y = (UINT)(v * (this->m_iHeight - 1.0f));
		return this->bits[y * this->m_iHeight + x];
	}
}

DrawColor DrawTexture::SampleColor(const Vector2 &uv)
{
	unsigned int color = this->Sample(uv);
	return DrawColor::IntToColor(color);
}