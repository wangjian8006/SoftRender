#pragma once

#include "DrawShader.h"
#include "DrawTexture.h"
#include "DrawShaderType.h"

class DrawShaderLight : public DrawShader
{
public:
	void VS(const DrawVertexIn *in, DrawVertexOut *out);
	DrawColor PS(const DrawVertexOut *out);
	void SetupProperty(const char* propertyName, void* propertyObject);
private:
	DrawTexture* _MainTex;
	DrawTexture* _NormalTex;

	ShaderFloat* _Shininess;		//高光的迭代次数
	Vector4* _SpecularColor;		//材质表面受镜面反射的参数控制（衰减系数）
	Vector4* _AmbientColor;		//材质表面受环境光的参数控制（衰减系数）
	Vector4* _DiffuseColor;		//材质表面受漫反射的参数控制（衰减系数）

	Vector3 CalculateNormal(const Vector2 &uv, const Vector3 &normal);
};

