#include "DrawMath.h"

#include "DrawCamera.h"
#include "DrawMeshRenderer.h"
#include "DrawSceneManager.h"
#include "DrawTexture.h"

#include "DrawShaderType.h"
#include "DrawShaderColor.h"
#include "DrawShaderTexture.h"
#include "DrawShaderLight.h"

#include "DrawWindow.h"
#include "DrawDevice.h"

#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;

DrawTexture* LoadTexture(const WCHAR* filePath)
{
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	Bitmap* bmp = new Bitmap(filePath);
	if (!bmp)
	{
		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return NULL;
	}
	else
	{
		UINT height = bmp->GetHeight();
		UINT width = bmp->GetWidth();
		Color color;
		DrawTexture* texture = new DrawTexture(width, height);

		for (UINT y = 0; y < height; y++)
			for (UINT x = 0; x < width; x++)
			{
				bmp->GetPixel(x, y, &color);
				texture->SetPixel(x, y, color.GetValue());
			}
		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return texture;
	}
}

///³õÊ¼»¯Íø¸ñ
DrawMeshRenderer* InitMesh()
{
	DrawMeshRenderer* mesh = new DrawMeshRenderer();

	mesh->vertexs = new Vector3[24];
	mesh->uvs = new Vector2[24];
	mesh->colors = new DrawColor[24];
	mesh->normals = new Vector3[24];
	mesh->triangles = new int[36];

	mesh->AddVertex(Vector3(-1, -1, -1), DrawColor(255, 0, 0, 255), Vector2(0, 1), Vector3(0, 0, -1));
	mesh->AddVertex(Vector3(-1, 1, -1), DrawColor(0, 255, 0, 255), Vector2(0, 0), Vector3(0, 0, -1));
	mesh->AddVertex(Vector3(1, 1, -1), DrawColor(255, 0, 255, 255), Vector2(1, 0), Vector3(0, 0, -1));
	mesh->AddVertex(Vector3(1, -1, -1), DrawColor(255, 255, 0, 255), Vector2(1, 1), Vector3(0, 0, -1));

	mesh->AddVertex(Vector3(-1, -1, 1), DrawColor(255, 0, 0, 255), Vector2(0, 1), Vector3(-1, 0, 0));
	mesh->AddVertex(Vector3(-1, 1, 1), DrawColor(0, 255, 0, 255), Vector2(0, 0), Vector3(-1, 0, 0));
	mesh->AddVertex(Vector3(-1, 1, -1), DrawColor(255, 0, 255, 255), Vector2(1, 0), Vector3(-1, 0, 0));
	mesh->AddVertex(Vector3(-1, -1, -1), DrawColor(255, 255, 0, 255), Vector2(1, 1), Vector3(-1, 0, 0));

	mesh->AddVertex(Vector3(1, -1, 1), DrawColor(255, 0, 0, 255), Vector2(0, 1), Vector3(0, 0, 1));
	mesh->AddVertex(Vector3(1, 1, 1), DrawColor(0, 255, 0, 255), Vector2(0, 0), Vector3(0, 0, 1));
	mesh->AddVertex(Vector3(-1, 1, 1), DrawColor(255, 0, 255, 255), Vector2(1, 0), Vector3(0, 0, 1));
	mesh->AddVertex(Vector3(-1, -1, 1), DrawColor(255, 255, 0, 255), Vector2(1, 1), Vector3(0, 0, 1));

	mesh->AddVertex(Vector3(1, -1, -1), DrawColor(255, 0, 0, 255), Vector2(0, 1), Vector3(1, 0, 0));
	mesh->AddVertex(Vector3(1, 1, -1), DrawColor(0, 255, 0, 255), Vector2(0, 0), Vector3(1, 0, 0));
	mesh->AddVertex(Vector3(1, 1, 1), DrawColor(255, 0, 255, 255), Vector2(1, 0), Vector3(1, 0, 0));
	mesh->AddVertex(Vector3(1, -1, 1), DrawColor(255, 255, 0, 255), Vector2(1, 1), Vector3(1, 0, 0));

	mesh->AddVertex(Vector3(-1, 1, -1), DrawColor(255, 0, 0, 255), Vector2(0, 1), Vector3(0, 1, 0));
	mesh->AddVertex(Vector3(-1, 1, 1), DrawColor(0, 255, 0, 255), Vector2(0, 0), Vector3(0, 1, 0));
	mesh->AddVertex(Vector3(1, 1, 1), DrawColor(255, 0, 255, 255), Vector2(1, 0), Vector3(0, 1, 0));
	mesh->AddVertex(Vector3(1, 1, -1), DrawColor(255, 255, 0, 255), Vector2(1, 1), Vector3(0, 1, 0));

	mesh->AddVertex(Vector3(-1, -1, 1), DrawColor(255, 0, 0, 255), Vector2(0, 1), Vector3(0, -1, 0));
	mesh->AddVertex(Vector3(-1, -1, -1), DrawColor(0, 255, 0, 255), Vector2(0, 0), Vector3(0, -1, 0));
	mesh->AddVertex(Vector3(1, -1, -1), DrawColor(255, 0, 255, 255), Vector2(1, 0), Vector3(0, -1, 0));
	mesh->AddVertex(Vector3(1, -1, 1), DrawColor(255, 255, 0, 255), Vector2(1, 1), Vector3(0, -1, 0));

	mesh->AddTriangle(0, 1, 2);
	mesh->AddTriangle(0, 2, 3);
	mesh->AddTriangle(4, 5, 6);
	mesh->AddTriangle(4, 6, 7);
	mesh->AddTriangle(8, 9, 10);
	mesh->AddTriangle(8, 10, 11); 
	mesh->AddTriangle(12, 13, 14);
	mesh->AddTriangle(12, 14, 15);
	mesh->AddTriangle(16, 17, 18);
	mesh->AddTriangle(16, 18, 19);
	mesh->AddTriangle(20, 21, 22);
	mesh->AddTriangle(20, 22, 23);

	mesh->GetTransform()->SetEulerAngle(Vector3(80, 0, 0));

	//mesh->GetMaterial()->shader = new DrawShaderColor();
	//mesh->GetMaterial()->shader = new DrawShaderTexture();
	mesh->GetMaterial()->shader = new DrawShaderLight();
	mesh->GetMaterial()->SetPropertyObject("_MainTex", LoadTexture(L"./Resources/test.png"));
	mesh->GetMaterial()->SetPropertyObject("_BumpMap", LoadTexture(L"./Resources/testn.png"));

	mesh->GetMaterial()->SetPropertyObject("_Shininess", new ShaderFloat(1.0f));
	mesh->GetMaterial()->SetPropertyObject("_SpecularColor", new Vector4(0.5, 0.5, 0.5, 0));
	mesh->GetMaterial()->SetPropertyObject("_AmbientColor", new Vector4(1.0, 1.0, 1.0, 0));
	mesh->GetMaterial()->SetPropertyObject("_DiffuseColor", new Vector4(1.0, 1.0, 1.0, 0));

	DrawSceneManager::GetInstance()->GetDirectionalLight()->color = DrawColor(128, 208, 128, 1);
	DrawSceneManager::GetInstance()->GetDirectionalLight()->ambient = DrawColor(128, 128, 128, 1);
	DrawSceneManager::GetInstance()->GetDirectionalLight()->GetTransform()->SetEulerAngle(Vector3(45, 45, 45));
	return mesh;
}

DrawCamera* InitCamera(float w, float h)
{
	DrawCamera* camera = new DrawCamera();
	camera->setFOV(60);
	camera->setWidthAndHeight(w, h);
	camera->GetTransform()->SetPosition(Vector3(10, 0, 0));
	//camera->setFar(100.0f);
	//camera->setNear(1.0f);
	camera->GetTransform()->LookAt(Vector3(0, 0, 0), Vector3::Up());

	//printf("%s\r\n", camera->GetProjectionMatrix().toString());
	return camera;
}

void DrawDataPrepare()
{
	DrawMeshRenderer* mesh = InitMesh();
	DrawCamera* camera = InitCamera(800, 600);
	DrawSceneManager::GetInstance()->SetMainCamera(camera);
	DrawSceneManager::GetInstance()->RegisterObject(mesh);
}

DrawDevice* s_device;
DrawWindow* s_window;

bool DeviceInit(int w, int h)
{
	s_device = new DrawDevice(w, h);
	s_window = new DrawWindow(s_device);
	if (s_window->InitWindow(w, h, _T("window")) != 0) return false;
	return true;
}

int main()
{
	if (DeviceInit(800, 600) == false) return 1;
	DrawSceneManager::Init(s_device);

	DrawDataPrepare();
	
	while(!s_window->CheckClose())
	{
		DrawSceneManager::GetInstance()->Update();
		DrawSceneManager::GetInstance()->Renderer();
		DrawSceneManager::GetInstance()->LateUpdate();

		s_window->WindowUpdate();
		Sleep(1);
	}
	return 0;
}