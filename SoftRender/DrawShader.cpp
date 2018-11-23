#include "DrawShader.h"

DrawShader::DrawShader(void)
{
}

DrawShader::~DrawShader(void)
{
}
void DrawShader::SetMVPMatrix(const Matrix4x4 &mt)
{
	this->m_mvpMatrix.CopyFrom(mt);
}
void DrawShader::SetEyePos(const Vector3 &eye)
{
	this->m_eyePos.CopyFrom(eye);
}
void DrawShader::SetWorld(const Matrix4x4 &mt)
{
	this->m_worldMatrix.CopyFrom(mt);
	this->m_worldInvTranspose.CopyFrom(this->m_worldMatrix);
	this->m_worldInvTranspose.Inverse();
	this->m_worldInvTranspose.Transpose();
}
void DrawShader::SetupProperty(const char* propertyName, void* propertyObject)
{

}