#pragma once

#include "DrawObject.h"

class DrawDirectionalLight : public DrawObject
{
public:
	DrawDirectionalLight(void);
	~DrawDirectionalLight(void);

	DrawColor color;
	DrawColor ambient;
	float intensity;

	void Update();
	void Renderer(DrawObject* camera);
	void LateUpdate();
};

