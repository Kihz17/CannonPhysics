#pragma once

#include "Projectile.h"

#include <rapidjson/document.h>

#include <string>

class ProjectileSerializer
{
public:
	ProjectileSerializer();

	void LoadProjectile(std::string loadPath, sProjectileInfo& projectile);

protected:
	bool VerifyValueExists(const char* key, const rapidjson::Value& value, rapidjson::Type variableType);
};