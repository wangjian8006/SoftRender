#pragma once

#include <map>
#include "DrawShader.h"

class DrawMaterial
{
public:
	DrawMaterial(void);
	~DrawMaterial(void);

	DrawShader *shader;

	void SetPropertyObject(const char* name, void* object);
	void* GetPropertyObject(const char* name);

	void SetupMaterialProperty();
private:
	std::map<char*, void*> propertys;
};

