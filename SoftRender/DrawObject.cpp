#include "DrawObject.h"

DrawObject::DrawObject(void)
{
	this->transform = new DrawTransform(this);
}

DrawObject::~DrawObject(void)
{
}

DrawTransform* DrawObject::GetTransform()
{
	return this->transform;
}