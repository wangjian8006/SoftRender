#include "DrawShaderColor.h"

void DrawShaderColor::VS(const DrawVertexIn *in, DrawVertexOut *out)
{
	out->posH = this->m_mvpMatrix.MultiplyPoint(in->pos);
 	out->color = in->color;
 	out->uv = in->uv;
}
DrawColor DrawShaderColor::PS(const DrawVertexOut *out)
{
	return out->color;
}