#include "ProjectileManager.h"

#include <iostream>

Projectile* ProjectileManager::CreateProjectile(ProjectileType type, glm::vec3& position, glm::vec3& direction)
{
	std::map<ProjectileType, sProjectileInfo>::iterator registryIt = this->projectileRegistry.find(type);
	if (registryIt == this->projectileRegistry.end())
	{
		std::cout << "Could not find projectile data for projectile type " << type << std::endl;
		return NULL;
	}

	sProjectileInfo info = registryIt->second;

	float timeLimit = info.isTimeLimit ? info.timeLimit : -1.0f;
	float distanceLimit = info.isDistanceLimit ? info.distanceLimit : -1.0f;
	Projectile* projectile = new Projectile(info.mass, position, direction * info.velocity, info.size, info.isTimeLimit, timeLimit, info.isDistanceLimit, distanceLimit);

	if (type == ProjectileType::EnergyBall)
	{
		projectile->SetAcceleration(direction * 5.0f); // Accelerate over time

		// No gravity
		projectile->SetUseCustomGravity(true);
		projectile->SetCustomGravity(glm::vec3(0.0f)); 
	}

	return projectile;
}

void ProjectileManager::RegisterProjectile(ProjectileType type, sProjectileInfo info)
{
	this->projectileRegistry.insert(std::make_pair(type, info));
}