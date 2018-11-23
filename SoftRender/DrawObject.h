#pragma once
class DrawTransform;
#include "DrawTransform.h"

class DrawObject
{
public:
	DrawObject(void);
	~DrawObject(void);

	DrawTransform* GetTransform();
	virtual void Update() = 0;
	virtual void Renderer(DrawObject* camera) = 0;
	virtual void LateUpdate() = 0;

protected:
	DrawTransform* transform;		//ģ��U3D��GameObject��Transform��
};