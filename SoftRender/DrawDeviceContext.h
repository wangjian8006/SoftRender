#pragma once

#include "DrawDevice.h"
#include "DrawMath.h"
#include "DrawShader.h"
#include "DrawMaterial.h"

class DrawDeviceContext
{
public:
	DrawDeviceContext(DrawDevice *device);
	~DrawDeviceContext(void);

	void ClearBuffer(int color);
	void DrawPrimitive(DrawShader* shader, const DrawVertexIn* v1, const DrawVertexIn* v2, const DrawVertexIn* v3);

private:
	DrawDevice *m_device;
	DrawVertexOut* m_pVertexOut1;
	DrawVertexOut* m_pVertexOut2;
	DrawVertexOut* m_pVertexOut3;
	DrawVertexOut* m_pVertexOutMidTemp;

	DrawVertexOut* m_pVertexOutLeft;
	DrawVertexOut* m_pVertexOutRight;

	DrawVertexOut* m_pVertexOutDraw;
	DrawShader* m_pShader;
	
	bool SimpleCVVCullCheck(const DrawVertexOut* out);
	void ToScreenSpace(DrawVertexOut* out);

	void DrawLine(int x1, int y1, int x2, int y2, int color);
	void DrawPixel(int x, int y, int color);
	void DrawTriangle(const DrawVertexOut* v1, const DrawVertexOut* v2, const DrawVertexOut* v3);
	void DrawTriangleBottom(const DrawVertexOut* v1, const DrawVertexOut* v2, const DrawVertexOut* v3);
	void DrawTriangleTop(const DrawVertexOut* v1, const DrawVertexOut* v2, const DrawVertexOut* v3);
	void ScanlineFill(const DrawVertexOut* left, const DrawVertexOut* right, int yIndex);
};