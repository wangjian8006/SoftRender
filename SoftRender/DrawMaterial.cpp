#include "DrawMaterial.h"


DrawMaterial::DrawMaterial(void)
{
}
DrawMaterial::~DrawMaterial(void)
{
}
void DrawMaterial::SetPropertyObject(const char* name, void* object)
{
	char* pName = new char[strlen(name)];

	strcpy(pName, name);

	this->propertys.insert(std::pair<char*, void*>(pName, object));
}
void* DrawMaterial::GetPropertyObject(const char* name)
{
	char* pName = new char[strlen(name)];

	strcpy(pName, name);

	std::map<char*, void*>::iterator iter = this->propertys.find(pName);

	if (iter == this->propertys.end()) return NULL;
	return iter->second;
}

void DrawMaterial::SetupMaterialProperty()
{
	std::map<char*, void*>::iterator iter;

	for(iter = this->propertys.begin(); iter != this->propertys.end(); iter++)
		this->shader->SetupProperty(iter->first, iter->second);
}