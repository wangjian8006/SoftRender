#pragma once

#include "DrawShader.h"
#include "DrawTexture.h"

class DrawShaderTexture : public DrawShader
{
public:
	void VS(const DrawVertexIn *in, DrawVertexOut *out);
	DrawColor PS(const DrawVertexOut *out);
	void SetupProperty(const char* propertyName, void* propertyObject);

private:
	DrawTexture* _MainTex;
};

