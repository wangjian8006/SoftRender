#include "DrawCamera.h"


DrawCamera::DrawCamera(void)
{
	this->transform = new DrawTransform(this, true);
	this->m_fFOV = this->m_fAspect = 0.0f;
	this->m_fNear = 0.1f;
	this->m_fFar = 1000.0f;
	this->m_bProjectDirty = true;

	this->m_backColor = 0xff;
}

DrawCamera::~DrawCamera(void)
{
}

int DrawCamera::GetBackColor()
{
	return this->m_backColor;
}

Matrix4x4 DrawCamera::GetViewMatrix()
{
	Matrix4x4 viewMartix = this->GetTransform()->GetWorldMatrix();
	viewMartix.Inverse();
	//将矩阵改成右手坐标系的矩阵，即z取反
	viewMartix.m[2][0] = viewMartix.m[2][0] * -1;
	viewMartix.m[2][1] = viewMartix.m[2][1] * -1;
	viewMartix.m[2][2] = viewMartix.m[2][2] * -1;
	viewMartix.m[2][3] = viewMartix.m[2][3] * -1;
	return viewMartix;
}

Matrix4x4 DrawCamera::GetProjectionMatrix()
{
	if (this->m_bProjectDirty == true)
	{
		DrawMath::MatrixPerspective(this->m_projection, this->m_fFOV, this->m_fAspect, this->m_fNear, this->m_fFar);
		this->m_bProjectDirty = false;
	}
	return this->m_projection;
}

void DrawCamera::setNear(float n)
{
	this->m_fNear = n;
	this->m_bProjectDirty = true;
}
void DrawCamera::setFar(float f)
{
	this->m_fFar = f;
}
void DrawCamera::setFOV(float fov)
{
	this->m_fFOV = fov * DrawMath::Deg2Rad;
}
void DrawCamera::setWidthAndHeight(float width, float height)
{
	this->m_fAspect = width / height;
}

float DrawCamera::getNear()
{
	return this->m_fNear;
}
float DrawCamera::getFar()
{
	return this->m_fFar;
}
float DrawCamera::getFOV()
{
	return this->m_fFOV;
}

void DrawCamera::Update()
{

}
void DrawCamera::Renderer(DrawObject* camera)
{

}
void DrawCamera::LateUpdate()
{

}