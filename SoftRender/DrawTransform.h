#pragma once

class DrawObject;

#include "DrawObject.h"
#include "Matrix.h"
#include "Vector.h"
#include "DrawMath.h"
#include <vector>

class DrawTransform
{
public:
	DrawTransform(DrawObject *drawObject, bool noScale = false);
	~DrawTransform(void);

	void SetPosition(Vector3 &pos);
	Vector3 GetPosition();

	void SetScale(Vector3 &scale);
	Vector3 GetScale();

	void SetEulerAngle(Vector3 &angle);
	Vector3 GetEulerAngle();

	void SetOrientation(Vector3 &dir, Vector3 &up);
	void LookAt(Vector3 &target);
	void LookAt(Vector3 &target, Vector3 &upAxis);
	Vector3 GetForwad();
	void SetForwad(Vector3 &dir);
	
	DrawObject* GetDrawObject();

	Matrix4x4 GetWorldMatrix();
protected:
	Matrix4x4 worldMatrix;						//¼ÇÂ¼ÊÀ½ç¾ØÕó

	Vector3 m_vEulerAngle;
	Vector3 m_vPosition;
	Vector3 m_vScale;

	bool m_bMatrixDirty;
	bool m_bNoScale;

	DrawObject* m_drawObject;

	void UpdateTransform();
};