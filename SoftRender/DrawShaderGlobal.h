#pragma once
#include "Vector.h"
class DrawShaderGlobal
{
public:
	static Vector3 s_lightDir;
	static Vector4 s_lightColor;
	static Vector4 s_lightAmbient;
	static void SetLight(const Vector3 &dir, const DrawColor& color, const DrawColor &ambient);
};