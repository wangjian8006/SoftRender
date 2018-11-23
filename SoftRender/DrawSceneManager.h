#pragma once

#include "DrawCamera.h"
#include "DrawObject.h"
#include "DrawDevice.h"
#include "DrawDeviceContext.h"
#include "DrawDirectionalLight.h"
#include <vector>

class DrawSceneManager
{
public:
	static void Init(DrawDevice *device);
	static DrawSceneManager* GetInstance();
private:
	static DrawSceneManager* s_Instance;

public:
	DrawSceneManager(DrawDevice *device);
	~DrawSceneManager(void);

	void Update();
	void Renderer();
	void LateUpdate();

	void SetMainCamera(DrawCamera *camera);
	DrawCamera* GetMainCamera();
	bool ContainsObject(DrawObject *object);
	void RegisterObject(DrawObject *object);

	DrawDeviceContext* GetDrawDeviceContext();
	DrawDirectionalLight* GetDirectionalLight();

private:
	DrawDevice *m_device;
	DrawCamera *m_mainCamera;
	std::vector<DrawObject*> m_sceneObjects;
	DrawDeviceContext* m_deviceContext;
	DrawDirectionalLight* m_directionLight;
};

