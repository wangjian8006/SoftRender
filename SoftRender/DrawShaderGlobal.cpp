#include "DrawShaderGlobal.h"

Vector3 DrawShaderGlobal::s_lightDir = Vector3();
Vector4 DrawShaderGlobal::s_lightColor = Vector4();
Vector4 DrawShaderGlobal::s_lightAmbient = Vector4();

void DrawShaderGlobal::SetLight(const Vector3 &dir, const DrawColor& color, const DrawColor &ambient)
{
	DrawShaderGlobal::s_lightDir = dir;
	DrawShaderGlobal::s_lightColor = DrawColor::ColorToFloat(color);
	DrawShaderGlobal::s_lightAmbient = DrawColor::ColorToFloat(ambient);
	
	DrawShaderGlobal::s_lightDir.Normalize();
}