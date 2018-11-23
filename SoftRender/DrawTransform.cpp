#include "DrawTransform.h"


DrawTransform::DrawTransform(DrawObject *drawObject, bool noScale)
{
	this->worldMatrix.Identity();
	this->m_drawObject = drawObject;
	this->m_vScale.x = this->m_vScale.y = this->m_vScale.z = 1.0f;
	this->m_bMatrixDirty = false;
	this->m_bNoScale = noScale;
}

DrawTransform::~DrawTransform(void)
{
}

DrawObject* DrawTransform::GetDrawObject()
{
	return this->m_drawObject;
}
void DrawTransform::SetPosition(Vector3 &pos)
{
	this->m_vPosition.CopyFrom(pos);
	this->UpdateTransform();
}
Vector3 DrawTransform::GetPosition()
{
	Vector3 pos;
	pos.CopyFrom(this->m_vPosition);
	return pos;
}
void DrawTransform::SetScale(Vector3 &scale)
{
	if (this->m_bNoScale == true) return;
	this->m_vScale.CopyFrom(scale);
	this->UpdateTransform();
}
Vector3 DrawTransform::GetScale()
{
	Vector3 scale;
	scale.CopyFrom(this->m_vScale);
	return scale;
}

void DrawTransform::SetEulerAngle(Vector3 &angle)
{
	this->m_vEulerAngle.CopyFrom(angle);
	this->UpdateTransform();
}
Vector3 DrawTransform::GetEulerAngle()
{
	Vector3 euler;
	euler.CopyFrom(this->m_vEulerAngle);
	return euler;
}

void DrawTransform::SetOrientation(Vector3 &dir, Vector3 &up)
{
	Matrix4x4 rotation;
	DrawMath::LookAtToRotationMatrix(dir, up, rotation);
	Vector3 euler;
	DrawMath::MatrixToEuler(rotation, euler);
	this->SetEulerAngle(euler);
}
Vector3 DrawTransform::GetForwad()
{
	Vector3 forward;
	Matrix4x4 world = this->GetWorldMatrix();
	world.CopyColumnTo(forward, 2);
	return forward;
}
void DrawTransform::SetForwad(Vector3 &dir)
{
	SetOrientation(dir, Vector3::Up());
}
void DrawTransform::LookAt(Vector3 &target)
{
	Vector3 dir = target - this->GetPosition();
	this->SetOrientation(dir, Vector3::Up());
}
void DrawTransform::LookAt(Vector3 &target, Vector3 &upAxis)
{
	Vector3 dir = target - this->GetPosition();
	this->SetOrientation(dir, upAxis);
}

void DrawTransform::UpdateTransform()
{
	this->m_bMatrixDirty = true;
}

Matrix4x4 DrawTransform::GetWorldMatrix()
{
	Matrix4x4 m;
	if (this->m_bMatrixDirty == true)
	{
		DrawMath::MatrixSetTRS(this->m_vPosition, this->m_vEulerAngle, this->m_vScale, this->worldMatrix);
		this->m_bMatrixDirty = false;
	}
	m.CopyFrom(this->worldMatrix);
	return m;
}