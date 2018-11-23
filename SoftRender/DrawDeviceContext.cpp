#include "DrawDeviceContext.h"


DrawDeviceContext::DrawDeviceContext(DrawDevice *device)
{
	m_device = device;
	this->m_pVertexOut1 = new DrawVertexOut();
	this->m_pVertexOut2 = new DrawVertexOut();
	this->m_pVertexOut3 = new DrawVertexOut();
	this->m_pVertexOutMidTemp = new DrawVertexOut();
	this->m_pVertexOutLeft = new DrawVertexOut();
	this->m_pVertexOutRight = new DrawVertexOut();
	this->m_pVertexOutDraw = new DrawVertexOut();
}

DrawDeviceContext::~DrawDeviceContext(void)
{

}

bool DrawDeviceContext::SimpleCVVCullCheck(const DrawVertexOut* out)
{
	/*float w = vertex.w;
	if (vertex.x < -w || vertex.x > w)
		return true;
	if (vertex.y < -w || vertex.y > w)
		return true;
	if (vertex.z < 0.0f || vertex.z > w)
		return true;*/
	Vector4 vertex = out->posH;

	if (vertex.x >= -vertex.w && vertex.x <= vertex.w &&
		vertex.y >= -vertex.w && vertex.y <= vertex.w &&
		vertex.z >= 0.f && vertex.z <= vertex.w)
	{
		return true;
	}
	return false;
}

//清理framebuffer以及zbuffer
void DrawDeviceContext::ClearBuffer(int color)
{
	this->m_device->ClearBuffer(color);
}

void DrawDeviceContext::ToScreenSpace(DrawVertexOut* out)
{
	//归一化,转齐次坐标
	float rhw = 1.0f / out->posH.w;

	out->oneDivz = rhw;
	out->posH = out->posH * rhw;
	out->color = out->color * rhw;
	out->normal = out->normal * rhw;
	out->uv = out->uv * rhw;
	
	//转屏幕坐标
	Vector4 vec = out->posH;

	vec.x = (vec.x + 1.0f) * 0.5f * this->m_device->GetDeviceWidth();
	vec.y = (vec.y + 1.0f) * 0.5f * this->m_device->GetDeviceHeight();
	vec.z = (vec.z + 1.0f) * 0.5f;
	vec.w = vec.w;
	out->posH = vec;
}

void DrawDeviceContext::DrawPrimitive(DrawShader* shader, const DrawVertexIn* v1, const DrawVertexIn* v2, const DrawVertexIn* v3)
{
	m_pShader = shader;

	//坐标转换
	this->m_pShader->VS(v1, this->m_pVertexOut1);
	this->m_pShader->VS(v2, this->m_pVertexOut2);
	this->m_pShader->VS(v3, this->m_pVertexOut3);

	//裁剪
	if (SimpleCVVCullCheck(this->m_pVertexOut1) == false) return;
	if (SimpleCVVCullCheck(this->m_pVertexOut2) == false) return;
	if (SimpleCVVCullCheck(this->m_pVertexOut3) == false) return;

	//转屏幕坐标
	this->ToScreenSpace(this->m_pVertexOut1);
	this->ToScreenSpace(this->m_pVertexOut2);
	this->ToScreenSpace(this->m_pVertexOut3);

	//光栅化
	DrawTriangle(this->m_pVertexOut1, this->m_pVertexOut2, this->m_pVertexOut3);

	//画线
	/*Vector4 p1 = this->m_pVertexOut1->posH;
	Vector4 p2 = this->m_pVertexOut2->posH;
	Vector4 p3 = this->m_pVertexOut3->posH;
	DrawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, 0);
	DrawLine((int)p1.x, (int)p1.y, (int)p3.x, (int)p3.y, 0);
	DrawLine((int)p3.x, (int)p3.y, (int)p2.x, (int)p2.y, 0);*/
}

// 画像素
void DrawDeviceContext::DrawPixel(int x, int y, int color)
{
	this->m_device->DrawPixel(x, y, color);
}

//画线
void DrawDeviceContext::DrawLine(int x1, int y1, int x2, int y2, int color)
{
	int x, y, rem = 0;
	if (x1 == x2 && y1 == y2)
	{
		DrawPixel(x1, y1, color);
	}else if (x1 == x2)
	{
		int inc = (y1 <= y2)? 1 : -1;
		for (y = y1; y != y2; y += inc) DrawPixel(x1, y, color);
		DrawPixel(x2, y2, color);
	}else if (y1 == y2)
	{
		int inc = (x1 <= x2)? 1 : -1;
		for (x = x1; x != x2; x += inc) DrawPixel(x, y1, color);
		DrawPixel(x2, y2, color);
	}else
	{
		int dx = (x1 < x2)? x2 - x1 : x1 - x2;
		int dy = (y1 < y2)? y2 - y1 : y1 - y2;
		if (dx >= dy) {
			if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; x <= x2; x++) {
				DrawPixel(x, y, color);
				rem += dy;
				if (rem >= dx) {
					rem -= dx;
					y += (y2 >= y1)? 1 : -1;
					DrawPixel(x, y, color);
				}
			}
			DrawPixel(x2, y2, color);
		}
		else
		{
			if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; y <= y2; y++)
			{
				DrawPixel(x, y, color);
				rem += dx;
				if (rem >= dy)
				{
					rem -= dy;
					x += (x2 >= x1)? 1 : -1;
					DrawPixel(x, y, color);
				}
			}
			DrawPixel(x2, y2, color);
		}
	}
}

void DrawDeviceContext::ScanlineFill(const DrawVertexOut* left, const DrawVertexOut* right, int yIndex)
{
	float dx = right->posH.x - left->posH.x;

	for (float x = left->posH.x; x <= right->posH.x; x += 1.f)
	{
		//四舍五入
		int xIndex = static_cast<int>(x + .5f);
		
		if(xIndex >= 0 && xIndex < this->m_device->GetDeviceWidth())
		{
			//插值系数
			float lerpFactor = 0;
			if (dx != 0) lerpFactor = (x - left->posH.x) / dx;

			//深度测试
			//1/z’与x’和y'是线性关系的
			float oneDivZ = DrawMath::Interp(left->oneDivz, right->oneDivz, lerpFactor);
			if (oneDivZ >= this->m_device->GetZ(xIndex, yIndex))
			{
				this->m_device->SetZ(xIndex, yIndex, oneDivZ);

				float w = 1.0f / oneDivZ;
				//插值顶点 原先需要插值的信息均乘以oneDivZ
				//现在得到插值后的信息需要除以oneDivZ得到真实值
				this->m_pVertexOutDraw->Lerp(left, right, lerpFactor);
				this->m_pVertexOutDraw->posH.y = (float)yIndex;
				this->m_pVertexOutDraw->uv.x *= w;
				this->m_pVertexOutDraw->uv.y *= w;

				this->m_pVertexOutDraw->normal.x *= w;
				this->m_pVertexOutDraw->normal.y *= w;
				this->m_pVertexOutDraw->normal.z *= w;

				this->m_pVertexOutDraw->color = this->m_pVertexOutDraw->color * w;

				//画像素点颜色
				DrawColor finalColor = this->m_pShader->PS(this->m_pVertexOutDraw);
				this->DrawPixel(xIndex, yIndex, DrawColor::ColorToInt(finalColor));
			}			
		}	
	}
}

void DrawDeviceContext::DrawTriangleTop(const DrawVertexOut* top1, const DrawVertexOut* top2, const DrawVertexOut* bottom)
{
	float dy = 0;//每次y增加一个像素
	for (float y = top1->posH.y; y <= bottom->posH.y; y += 1.f)
	{
		//四舍五入
		int yIndex = static_cast<int>(y + 0.5f);
		if (yIndex >= 0 && yIndex < m_device->GetDeviceHeight())
		{
			float t = dy / (bottom->posH.y - top1->posH.y);

			//插值生成左右顶点
			this->m_pVertexOutLeft->Lerp(top1, bottom, t);
			this->m_pVertexOutRight->Lerp(top2, bottom, t);
			dy += 1.f;
			//扫描线填充

			if (m_pVertexOutLeft->posH.x < m_pVertexOutRight->posH.x) ScanlineFill(m_pVertexOutLeft, m_pVertexOutRight, yIndex);
			else ScanlineFill(m_pVertexOutRight, m_pVertexOutLeft, yIndex);
		}
		
	}
}

void DrawDeviceContext::DrawTriangleBottom(const DrawVertexOut* top, const DrawVertexOut* bottom1, const DrawVertexOut* bottom2)
{
	float dy = 0;//每次y增加一个像素
	for (float y = top->posH.y; y <= bottom1->posH.y; y += 1.f)
	{
		//四舍五入
		int yIndex = static_cast<int>(y + 0.5f);

		if (yIndex >= 0 && yIndex < this->m_device->GetDeviceHeight())
		{
			float t = dy / (bottom1->posH.y - top->posH.y);

			//插值左右顶点
			this->m_pVertexOutLeft->Lerp(top, bottom1, t);
			this->m_pVertexOutRight->Lerp(top, bottom2, t);
			dy += 1.f;

			//扫描线填充
			if (m_pVertexOutLeft->posH.x < m_pVertexOutRight->posH.x) ScanlineFill(m_pVertexOutLeft, m_pVertexOutRight, yIndex);
			else ScanlineFill(m_pVertexOutRight, m_pVertexOutLeft, yIndex);
		}
	}
}

void DrawDeviceContext::DrawTriangle(const DrawVertexOut* v1, const DrawVertexOut* v2, const DrawVertexOut* v3)
{
	if (v1->posH.y == v2->posH.y)
	{	
		if (v1->posH.y < v3->posH.y) DrawTriangleTop(v1, v2, v3);
		else DrawTriangleBottom(v3, v1, v2);
	}
	else if (v1->posH.y == v3->posH.y)
	{
		if (v1->posH.y < v2->posH.y) DrawTriangleTop(v1, v3, v2);
		else DrawTriangleBottom(v2, v1, v3);
	}
	else if (v2->posH.y == v3->posH.y)
	{
		if (v2->posH.y < v1->posH.y) DrawTriangleTop(v2, v3, v1);
		else DrawTriangleBottom(v1, v2, v3);
	}
	else
	{
		//根据y值将三个顶点排序
		const DrawVertexOut* vss[3] = {v1, v2, v3};
		const DrawVertexOut* temp;
		if (vss[1]->posH.y > vss[0]->posH.y) { SWAP_VALUE(vss[0], vss[1], temp) }
		if (vss[2]->posH.y > vss[0]->posH.y) { SWAP_VALUE(vss[0], vss[2], temp) }
		if (vss[2]->posH.y > vss[1]->posH.y) { SWAP_VALUE(vss[1], vss[2], temp) }

		const DrawVertexOut* top = vss[2];
		const DrawVertexOut* middle = vss[1];
		const DrawVertexOut* bottom = vss[0];

		//printf("%f %f %f\r\n", top->posH.y, middle->posH.y, bottom->posH.y);

		//插值求中间点
		float middleX = (middle->posH.y - top->posH.y) * (bottom->posH.x - top->posH.x) / (bottom->posH.y - top->posH.y) + top->posH.x;
		float dy = middle->posH.y - top->posH.y;
		float t = dy / (bottom->posH.y - top->posH.y);
		
		m_pVertexOutMidTemp->Lerp(top, bottom, t);
		m_pVertexOutMidTemp->posH.x = middleX;
		m_pVertexOutMidTemp->posH.y = middle->posH.y;

		DrawTriangleTop(middle, m_pVertexOutMidTemp, bottom);
		DrawTriangleBottom(top, middle, m_pVertexOutMidTemp);
	}
}