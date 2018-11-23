#include "DrawShaderLight.h"
#include "DrawSceneManager.h"
#include "DrawMath.h"

void DrawShaderLight::VS(const DrawVertexIn *in, DrawVertexOut *out)
{
	out->posH = this->m_mvpMatrix.MultiplyPoint(in->pos);
	out->posW = this->m_worldMatrix.MultiplyPoint(in->pos);
	out->normal = this->m_worldInvTranspose.MultiplyPoint3(in->normal);

 	//out->color = in->color;
 	out->uv = in->uv;
}

DrawColor DrawShaderLight::PS(const DrawVertexOut *out)
{
	//BlinnPhong光照模型
	//N
	Vector3 N = out->normal;
	N.Normalize();
	
	//V
	Vector3 V = this->m_eyePos - out->posW;
	V.Normalize();

	//环境光
	Vector4 ambient = (*_AmbientColor) * DrawShaderGlobal::s_lightAmbient;

	//漫反射
	float diffuseLight = max(Vector3::Dot(N, DrawShaderGlobal::s_lightDir), 0);
	Vector4 diffuse = DrawShaderGlobal::s_lightColor * (*_DiffuseColor) * diffuseLight;

	//计算高光
	Vector3 H = (DrawShaderGlobal::s_lightDir + V);
	H.Normalize();
	float specFactor = pow(max(Vector3::Dot(H, N), 0), _Shininess->_value);
	Vector4 spec = DrawShaderGlobal::s_lightColor * (*_SpecularColor) * specFactor;				//ks * lightcolor * specularLight
	
	DrawColor texColor = this->_MainTex->SampleColor(out->uv);
	DrawColor color = texColor * (ambient + diffuse) + spec;
	return color;
}
void DrawShaderLight::SetupProperty(const char* propertyName, void* propertyObject)
{
	if (strcmp(propertyName, "_MainTex") == 0)
	{
		this->_MainTex = (DrawTexture*)propertyObject;
	}else if (strcmp(propertyName, "_Shininess") == 0)
	{
		this->_Shininess = (ShaderFloat*)propertyObject;
	}else if (strcmp(propertyName, "_SpecularColor") == 0)
	{
		this->_SpecularColor = (Vector4*)propertyObject;
	}else if (strcmp(propertyName, "_AmbientColor") == 0)
	{
		this->_AmbientColor = (Vector4*)propertyObject;
	}else if (strcmp(propertyName, "_DiffuseColor") == 0)
	{
		this->_DiffuseColor = (Vector4*)propertyObject;
	}else if (strcmp(propertyName, "_BumpMap") == 0)
	{
		this->_NormalTex = (DrawTexture*)propertyObject;
	}
}