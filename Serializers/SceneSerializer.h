#pragma once

#include "Scene.h"
#include "Camera.h"

#include<yaml-cpp/yaml.h>
#include <string>

class SceneSerializer
{
public:
	SceneSerializer(Scene& scene, Camera& camera);

	void Serialize(const std::string& path);
	bool Deserialize(const std::string& path);

private:
	Scene& scene;
	Camera& camera;
};