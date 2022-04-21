#pragma once

#include "Model.h"
#include "Light.h"

#include <vector>

class Scene 
{
public:
	std::string name;
	std::vector<Model> models;
	std::vector<Light> lights;

	Scene(std::string name);
	~Scene();
};