#pragma once

#include "DrawShader.h"

class DrawShaderColor : public DrawShader
{
public:
	void VS(const DrawVertexIn *in, DrawVertexOut *out);
	DrawColor PS(const DrawVertexOut *out);
};