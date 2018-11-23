#pragma once

#include "Vector.h"
#include "DrawMath.h"

struct DrawVertexIn
{
	//坐标
	Vector3 pos;

	//法线
	Vector3 normal;

	//uv
	Vector2 uv;

	//颜色
	DrawColor color;
};

struct DrawVertexOut
{
	//mvpcs转换后的坐标
	Vector4 posH;

	//世界坐标
	Vector4 posW;

	//法线
	Vector3 normal;

	//uv
	Vector2 uv;

	//颜色
	DrawColor color;

	//1/z，深度测试
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