#pragma once

#include "Projectile.h"

#include <glm/vec3.hpp>

#include <map>

class ProjectileManager
{
public:
	// Create a projectile of a given type
	Projectile* CreateProjectile(ProjectileType type, glm::vec3& position, glm::vec3& direction);

	// Registers a projectile type
	void RegisterProjectile(ProjectileType type, sProjectileInfo info);

private:
	std::map<ProjectileType, sProjectileInfo> projectileRegistry;
};