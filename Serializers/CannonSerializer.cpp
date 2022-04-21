#include "CannonSerializer.h"

#include <rapidjson/istreamwrapper.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include <fstream>
#include <iostream>

CannonSerializer::CannonSerializer()
{

}

void CannonSerializer::LoadCannon(std::string loadPath, Cannon& cannon)
{
	std::ifstream ifs(loadPath);
	rapidjson::IStreamWrapper isw{ ifs };

	rapidjson::Document document;
	document.SetObject();
	document.ParseStream(isw);

	const rapidjson::Value& positionNode = document["position"];
	cannon.position.x = positionNode.GetArray()[0].GetFloat();
	cannon.position.y = positionNode.GetArray()[1].GetFloat();
	cannon.position.z = positionNode.GetArray()[2].GetFloat();

	const rapidjson::Value& startYawNode = document["startYaw"];
	float startYawDegrees = startYawNode.GetFloat();
	cannon.SetYaw(glm::radians(startYawDegrees));

	const rapidjson::Value& startPitchNode = document["startPitch"];
	float startPitchDegrees = startPitchNode.GetFloat();
	cannon.SetPitch(glm::radians(startPitchDegrees));

	const rapidjson::Value& yawRangeNode = document["yawRange"];
	cannon.SetMinYaw(glm::radians(startYawDegrees - yawRangeNode.GetFloat()));
	cannon.SetMaxYaw(glm::radians(startYawDegrees + yawRangeNode.GetFloat()));

	const rapidjson::Value& pitchRangeNode = document["pitchRange"];
	cannon.SetMinPitch(glm::radians(startPitchDegrees));
	cannon.SetMaxPitch(glm::radians(startPitchDegrees + pitchRangeNode.GetFloat()));
}