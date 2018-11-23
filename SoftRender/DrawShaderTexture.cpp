#include "DrawShaderTexture.h"

void DrawShaderTexture::VS(const DrawVertexIn *in, DrawVertexOut *out)
{
	out->posH = this->m_mvpMatrix.MultiplyPoint(in->pos);
 	out->uv = in->uv;
}
DrawColor DrawShaderTexture::PS(const DrawVertexOut *out)
{
	return this->_MainTex->SampleColor(out->uv);
}
void DrawShaderTexture::SetupProperty(const char* propertyName, void* propertyObject)
{
	if (strcmp(propertyName, "_MainTex") == 0)
	{
		this->_MainTex = (DrawTexture*)propertyObject;
	}
}