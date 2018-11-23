#pragma once
#include "DrawObject.h"
#include "DrawMath.h"
#include "DrawMaterial.h"
#include "DrawSceneManager.h"

class DrawMeshRenderer : public DrawObject
{
public:
	DrawMeshRenderer(void);
	~DrawMeshRenderer(void);

	void Update();
	void Renderer(DrawObject* camera);
	void LateUpdate();

	DrawMaterial* GetMaterial();
	Vector3* vertexs;
	Vector2* uvs;
	DrawColor* colors;
	Vector3* normals;
	int* triangles;

	void AddVertex(Vector3 &vertex, DrawColor &color, Vector2 &uv, Vector3 &normal);
	void AddTriangle(int a, int b, int c);

private:
	Matrix4x4 m_mvpMatrix;

	DrawVertexIn* m_pInVertex1;
	DrawVertexIn* m_pInVertex2;
	DrawVertexIn* m_pInVertex3;
	DrawMaterial* m_material;
	
	int vertexLen;
	int triangleLen;

	void CalculateMVPMatrix(DrawCamera* camera);
};

