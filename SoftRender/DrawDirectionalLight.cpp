#include "DrawDirectionalLight.h"


DrawDirectionalLight::DrawDirectionalLight(void)
{
	this->ambient = DrawColor(0, 0, 0, 0);
	this->color = DrawColor(0, 0, 0, 0);
	this->intensity = 1.0f;
}
DrawDirectionalLight::~DrawDirectionalLight(void)
{
}
void DrawDirectionalLight::Update()
{

}
void DrawDirectionalLight::Renderer(DrawObject* camera)
{

}
void DrawDirectionalLight::LateUpdate()
{

}