#pragma once
class DrawObject;
#include "DrawObject.h"
#include "DrawMath.h"

class DrawCamera : public DrawObject
{
public:
	DrawCamera(void);
	~DrawCamera(void);

	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();

	void setNear(float near);
	void setFar(float far);
	void setFOV(float fov);
	void setWidthAndHeight(float width, float height);

	float getNear();
	float getFar();
	float getFOV();

	//Rect viewPort;

	void Update();
	void Renderer(DrawObject* camera);
	void LateUpdate();

	int GetBackColor();

protected:
	Matrix4x4 m_view;					//摄像机坐标转换
	Matrix4x4 m_projection;			//3D 到2D 投影转换

	float m_fNear;
	float m_fFar;
	float m_fFOV;
	float m_fAspect;
	bool m_bProjectDirty;

	int m_backColor;
};