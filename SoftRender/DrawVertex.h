#pragma once

#include "Vector.h"
#include "DrawMath.h"

struct DrawVertexIn
{
	//����
	Vector3 pos;

	//����
	Vector3 normal;

	//uv
	Vector2 uv;

	//��ɫ
	DrawColor color;
};

struct DrawVertexOut
{
	//mvpcsת���������
	Vector4 posH;

	//��������
	Vector4 posW;

	//����
	Vector3 normal;

	//uv
	Vector2 uv;

	//��ɫ
	DrawColor color;

	//1/z����Ȳ���
	float oneDivz;

	void Lerp(const DrawVertexOut* a, const DrawVertexOut* b, float rate)
	{
		this->posH.Lerp(a->posH, b->posH, rate);
		this->posW.Lerp(a->posW, b->posW, rate);
		this->normal.Lerp(a->normal, b->normal, rate);
		this->uv.Lerp(a->uv, b->uv, rate);
		this->color.Lerp(a->color, b->color, rate);
		oneDivz = DrawMath::Interp(a->oneDivz, b->oneDivz, rate);
	}
};