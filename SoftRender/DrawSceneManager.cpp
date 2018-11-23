#include "DrawSceneManager.h"
#include "DrawMeshRenderer.h"

DrawSceneManager* DrawSceneManager::s_Instance = NULL;

void DrawSceneManager::Init(DrawDevice *device)
{
	if (DrawSceneManager::s_Instance != NULL) return;
	DrawSceneManager::s_Instance = new DrawSceneManager(device);
}

DrawSceneManager* DrawSceneManager::GetInstance()
{
	return DrawSceneManager::s_Instance;
}

DrawSceneManager::DrawSceneManager(DrawDevice *device)
{
	this->m_device = device;
	this->m_deviceContext = new DrawDeviceContext(device);
	this->m_directionLight = new DrawDirectionalLight();
}

DrawSceneManager::~DrawSceneManager(void)
{
}

DrawDirectionalLight* DrawSceneManager::GetDirectionalLight()
{
	return this->m_directionLight;
}

DrawDeviceContext* DrawSceneManager::GetDrawDeviceContext()
{
	return this->m_deviceContext;
}
void DrawSceneManager::Update()
{
	for (std::vector<DrawObject*>::iterator it = this->m_sceneObjects.begin(); it < this->m_sceneObjects.end(); ++it)
	{
		(*it)->Update();
	}
}
void DrawSceneManager::Renderer()
{
	//ClearBuffert
	this->m_deviceContext->ClearBuffer(this->m_mainCamera->GetBackColor());
	if (this->m_mainCamera == NULL) return;
	this->m_mainCamera->Update();

	DrawShaderGlobal::SetLight(this->m_directionLight->GetTransform()->GetForwad(), this->m_directionLight->color, this->m_directionLight->ambient);
	
	for (std::vector<DrawObject*>::iterator it = this->m_sceneObjects.begin(); it < this->m_sceneObjects.end(); ++it)
	{
		(*it)->Renderer(this->m_mainCamera);
	}
}
void DrawSceneManager::LateUpdate()
{
	for (std::vector<DrawObject*>::iterator it = this->m_sceneObjects.begin(); it < this->m_sceneObjects.end(); ++it)
	{
		(*it)->LateUpdate();
	}
}
void DrawSceneManager::SetMainCamera(DrawCamera *camera)
{
	this->m_mainCamera = camera;
}
DrawCamera* DrawSceneManager::GetMainCamera()
{
	return this->m_mainCamera;
}
bool DrawSceneManager::ContainsObject(DrawObject *object)
{
	for (std::vector<DrawObject*>::iterator it = this->m_sceneObjects.begin(); it < this->m_sceneObjects.end(); ++it)
	{
		if ((*it) == object) return true;
	}
	return false;
}
void DrawSceneManager::RegisterObject(DrawObject *object)
{
	if (ContainsObject(object) == true) return;
	this->m_sceneObjects.push_back(object);
}