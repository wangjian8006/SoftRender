#include "DrawMeshRenderer.h"
#include "DrawWindow.h"

DrawMeshRenderer::DrawMeshRenderer(void)
	: DrawObject()
{
	this->m_pInVertex1 = new DrawVertexIn();
	this->m_pInVertex2 = new DrawVertexIn();
	this->m_pInVertex3 = new DrawVertexIn();

	this->colors = NULL;
	this->normals = NULL;

	this->m_material = new DrawMaterial();

	this->vertexLen = this->triangleLen = 0;
}

DrawMeshRenderer::~DrawMeshRenderer(void)
{
}

void DrawMeshRenderer::Update()
{
	/*Vector3 pos = DrawSceneManager::GetInstance()->GetMainCamera()->GetTransform()->GetPosition();
	pos.z += 0.1f;
	DrawSceneManager::GetInstance()->GetMainCamera()->GetTransform()->SetPosition(pos);*/

	//计算M矩阵
	if (DrawWindow::KEYS[VK_UP])
	{
		Vector3 euler = GetTransform()->GetEulerAngle();
		euler.x += 10.0f;
		GetTransform()->SetEulerAngle(euler);
	}
	if (DrawWindow::KEYS[VK_DOWN])
	{
		Vector3 euler = GetTransform()->GetEulerAngle();
		euler.x -= 10.0f;
		GetTransform()->SetEulerAngle(euler);
	}
	if (DrawWindow::KEYS[VK_LEFT])
	{
		Vector3 euler = GetTransform()->GetEulerAngle();
		euler.y += 10.0f;
		GetTransform()->SetEulerAngle(euler);
	}
	if (DrawWindow::KEYS[VK_RIGHT])
	{
		Vector3 euler = GetTransform()->GetEulerAngle();
		euler.y -= 10.0f;
		GetTransform()->SetEulerAngle(euler);
	}


	if (DrawWindow::KEYS[0x41])
	{
		Vector3 pos = GetTransform()->GetPosition();
		pos.z -= 0.1f;
		GetTransform()->SetPosition(pos);
	}
	if (DrawWindow::KEYS['D' - 'A' + 0x41])
	{
		Vector3 pos = GetTransform()->GetPosition();
		pos.z += 0.1f;
		GetTransform()->SetPosition(pos);
	}
	if (DrawWindow::KEYS['W' - 'A' + 0x41])
	{
		Vector3 pos = GetTransform()->GetPosition();
		pos.y -= 0.1f;
		GetTransform()->SetPosition(pos);
	}
	if (DrawWindow::KEYS['S' - 'A' + 0x41])
	{
		Vector3 pos = GetTransform()->GetPosition();
		pos.y += 0.1f;
		GetTransform()->SetPosition(pos);
	}
}

void DrawMeshRenderer::CalculateMVPMatrix(DrawCamera* camera)
{
	this->m_mvpMatrix.CopyFrom(camera->GetProjectionMatrix());
	this->m_mvpMatrix.Append(camera->GetViewMatrix());
	this->m_mvpMatrix.Append(this->transform->GetWorldMatrix());
}

void DrawMeshRenderer::Renderer(DrawObject *camera)
{
	DrawDeviceContext* context = DrawSceneManager::GetInstance()->GetDrawDeviceContext();
	DrawShader* pShader = this->m_material->shader;

	//装载材质属性
	this->m_material->SetupMaterialProperty();

	//计算MVP
	this->CalculateMVPMatrix((DrawCamera*)camera);
	
	pShader->SetEyePos(camera->GetTransform()->GetPosition());
	pShader->SetMVPMatrix(this->m_mvpMatrix);
	pShader->SetWorld(this->transform->GetWorldMatrix());

	//省略
	//上传顶点数据
	//设置索引
	//画三角形

	int len = this->triangleLen;
	for (int i = 0; i < len; i += 3)
	{
		int idx1 = this->triangles[i];
		int idx2 = this->triangles[i + 1];
		int idx3 = this->triangles[i + 2];

		/*m_pInVertex1->Clear();
		m_pInVertex2->Clear();
		m_pInVertex3->Clear();*/

		m_pInVertex1->pos = this->vertexs[idx1];
		m_pInVertex2->pos = this->vertexs[idx2];
		m_pInVertex3->pos = this->vertexs[idx3];

		if (this->colors != NULL)
		{
			m_pInVertex1->color = this->colors[idx1];
			m_pInVertex2->color = this->colors[idx2];
			m_pInVertex3->color = this->colors[idx3];
		}

		if (this->uvs != NULL)
		{
			m_pInVertex1->uv = this->uvs[idx1];
			m_pInVertex2->uv = this->uvs[idx2];
			m_pInVertex3->uv = this->uvs[idx3];
		}

		if (this->normals != NULL)
		{
			m_pInVertex1->normal = this->normals[idx1];
			m_pInVertex2->normal = this->normals[idx2];
			m_pInVertex3->normal = this->normals[idx3];
		}

		context->DrawPrimitive(this->m_material->shader, m_pInVertex1, m_pInVertex2, m_pInVertex3);
	}
}
void DrawMeshRenderer::LateUpdate()
{

}

DrawMaterial* DrawMeshRenderer::GetMaterial()
{
	return this->m_material;
}

void DrawMeshRenderer::AddVertex(Vector3 &vertex, DrawColor &color, Vector2 &uv, Vector3 &normal)
{
	this->vertexs[this->vertexLen] = vertex;
	this->colors[this->vertexLen] = color;
	this->uvs[this->vertexLen] = uv;
	this->normals[this->vertexLen] = normal;
	this->vertexLen++;
}
void DrawMeshRenderer::AddTriangle(int a, int b, int c)
{
	this->triangles[this->triangleLen++] = a;
	this->triangles[this->triangleLen++] = b;
	this->triangles[this->triangleLen++] = c;
}