#include "ProjectileSerializer.h"

#include <rapidjson/istreamwrapper.h>

#include <glm/vec3.hpp>

#include <fstream>
#include <iostream>

ProjectileSerializer::ProjectileSerializer()
{

}

void ProjectileSerializer::LoadProjectile(std::string loadPath, sProjectileInfo& projectile)
{
	std::ifstream ifs(loadPath);
	rapidjson::IStreamWrapper isw{ ifs };

	rapidjson::Document document;
	document.SetObject();
	document.ParseStream(isw);

	const rapidjson::Value& sizeNode = document["size"];
	if (VerifyValueExists("size", sizeNode, rapidjson::kNumberType))
	{
		projectile.size = sizeNode.GetFloat();
	}

	const char* dampingKey = "damping";
	const rapidjson::Value& dampingNode = document[dampingKey];
	if (VerifyValueExists(dampingKey, dampingNode, rapidjson::kNumberType))
	{
		projectile.damping = dampingNode.GetFloat();
	}

	const char* massKey = "mass";
	const rapidjson::Value& massNode = document[massKey];
	if (VerifyValueExists(massKey, massNode, rapidjson::kNumberType))
	{
		projectile.mass = massNode.GetFloat();
	}

	const char* muzzleKey = "muzzleVelocity";
	const rapidjson::Value& muzzleNode = document[muzzleKey];
	if (VerifyValueExists(muzzleKey, muzzleNode, rapidjson::kNumberType))
	{
		projectile.velocity = muzzleNode.GetFloat();
	}

	if (document.FindMember("timeLimit") != document.MemberEnd())
	{
		const rapidjson::Value& timeLimitNode = document["timeLimit"];
		if (!timeLimitNode.IsNull() && timeLimitNode.IsFloat())
		{
			projectile.isTimeLimit = true;
			projectile.timeLimit = timeLimitNode.GetFloat();
		}
	}
	else
	{
		projectile.isTimeLimit = false;
		projectile.timeLimit = -1.0f;
	}

	if (document.FindMember("distanceLimit") != document.MemberEnd())
	{
		const rapidjson::Value& distanceLimitNode = document["distanceLimit"];
		if (!distanceLimitNode.IsNull() && distanceLimitNode.IsFloat())
		{
			projectile.isDistanceLimit = true;
			projectile.distanceLimit = distanceLimitNode.GetFloat();
		}
	}
	else
	{
		projectile.isDistanceLimit = false;
		projectile.distanceLimit = -1.0f;
	}
}

bool ProjectileSerializer::VerifyValueExists(const char* key, const rapidjson::Value& value, rapidjson::Type variableType)
{
	bool exists = !value.IsNull();
	if (!exists)
	{
		std::cout << "JSON Value '" << key << "' does not exist!" << std::endl;
		return false;
	}

	bool sameType = value.GetType() == variableType;
	if (!sameType)
	{
		std::cout << "JSON Value '" << key << "' is not of type " << variableType << "!" << std::endl;
	}

	return exists && sameType;;
}