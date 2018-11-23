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

	ShaderFloat* _Shininess;		//�߹�ĵ�������
	Vector4* _SpecularColor;		//���ʱ����ܾ��淴��Ĳ������ƣ�˥��ϵ����
	Vector4* _AmbientColor;		//���ʱ����ܻ�����Ĳ������ƣ�˥��ϵ����
	Vector4* _DiffuseColor;		//���ʱ�����������Ĳ������ƣ�˥��ϵ����

	Vector3 CalculateNormal(const Vector2 &uv, const Vector3 &normal);
};

