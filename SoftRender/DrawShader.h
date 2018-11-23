#pragma once

#include "DrawVertex.h"
#include "Matrix.h"
#include "DrawMath.h"
#include "DrawShaderGlobal.h"

class DrawShader
{
public:
	DrawShader(void);
	~DrawShader(void);

	virtual void VS(const DrawVertexIn *in, DrawVertexOut *out) = 0;
	virtual DrawColor PS(const DrawVertexOut *out) = 0;

	void SetMVPMatrix(const Matrix4x4 &mt);
	void SetEyePos(const Vector3 &eye);
	void SetWorld(const Matrix4x4 &mt);

	virtual void SetupProperty(const char* propertyName, void* propertyObject);

protected:
	Matrix4x4 m_mvpMatrix;
	Vector3 m_eyePos;
	Matrix4x4 m_worldMatrix;
	Matrix4x4 m_worldInvTranspose;
};

