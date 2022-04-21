#include "SceneSerializer.h"

#include <fstream>
#include <vector>


SceneSerializer::SceneSerializer(Scene& scene, Camera& camera)
	: scene(scene), camera(camera)
{
}

static void SerializeModel(YAML::Emitter& emitter, const Model& model)
{
	emitter << YAML::BeginMap;
	emitter << YAML::Key << "Path";
	emitter << YAML::Value << model.GetFullPath();

	// TODO: Deserialize model position and stuff

	emitter << YAML::EndMap;
}

static void SerializeCamera(YAML::Emitter& emitter, const Camera& camera)
{
	emitter << YAML::BeginMap;
	emitter << YAML::Key << "PosX";
	emitter << YAML::Value << camera.position.x;
	emitter << YAML::Key << "PosY";
	emitter << YAML::Value << camera.position.y;
	emitter << YAML::Key << "PosZ";
	emitter << YAML::Value << camera.position.z;

	emitter << YAML::Key << "Yaw";
	emitter << YAML::Value << camera.yaw;
	emitter << YAML::Key << "Pitch";
	emitter << YAML::Value << camera.pitch;

	emitter << YAML::Key << "DirectionX";
	emitter << YAML::Value << camera.direction.x;
	emitter << YAML::Key << "DirectionY";
	emitter << YAML::Value << camera.direction.y;
	emitter << YAML::Key << "DirectionZ";
	emitter << YAML::Value << camera.direction.z;

	emitter << YAML::Key << "Sensitivity";
	emitter << YAML::Value << camera.sensitivity;

	emitter << YAML::EndMap;
}

void SceneSerializer::Serialize(const std::string& path)
{
	YAML::Emitter emitter;
	emitter << YAML::BeginMap;
	emitter << YAML::Key << "Scene";
	emitter << YAML::Value << scene.name;

	emitter << YAML::Key << "Camera";
	SerializeCamera(emitter, camera);

	emitter << YAML::Key << "Models" << YAML::Value << YAML::BeginSeq;
	for (Model model : scene.models)
	{
		SerializeModel(emitter, model);
	}
	emitter << YAML::EndSeq;

	emitter << YAML::EndMap;

	std::ofstream fout(path);
	fout << emitter.c_str();
}

bool SceneSerializer::Deserialize(const std::string& path)
{
	std::ifstream ifstream(path);
	std::stringstream ss;
	ss << ifstream.rdbuf();

	YAML::Node root = YAML::Load(ss.str());
	if (!root["Scene"]) // Make sure the scene node exists
		return false;

	scene.name = root["Scene"].as<std::string>();

	YAML::Node cameraNode = root["Camera"];
	if (cameraNode)
	{
		this->camera.position.x = cameraNode["PosX"].as<float>();
		this->camera.position.y = cameraNode["PosY"].as<float>();
		this->camera.position.z = cameraNode["PosZ"].as<float>();

		this->camera.yaw= cameraNode["Yaw"].as<float>();
		this->camera.pitch = cameraNode["Pitch"].as<float>();

		this->camera.direction.x = cameraNode["DirectionX"].as<float>();
		this->camera.direction.y = cameraNode["DirectionY"].as<float>();
		this->camera.direction.z = cameraNode["DirectionZ"].as<float>();

		this->camera.sensitivity = cameraNode["Sensitivity"].as<float>();
	}

	YAML::Node models = root["Models"];
	if (models) // We have models to load
	{
		for (YAML::Node meshNode : models)
		{
			// TODO: Deserialize models
		}
	}
	return true;
}