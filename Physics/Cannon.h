#pragma once

#include "Projectile.h"
#include "ProjectileManager.h"
#include "Model.h"

#include <glm/vec3.hpp>;

class Cannon
{
public:
	Cannon(glm::vec3 position, glm::vec3 initialDirection, float sensitivity);

	// Look controls
	void LookLeft(float deltaTime);
	void LookRight(float deltaTime);
	void LookUp(float deltaTime);
	void LookDown(float deltaTime);

	float GetYaw();
	float GetPitch();

	void SetYaw(float value);
	void SetMinYaw(float value);
	void SetMaxYaw(float value);

	void SetPitch(float value);
	void SetMinPitch(float value);
	void SetMaxPitch(float value);

	// Fires a projectile from the cannon
	Projectile* FireProjectile(ProjectileType type, ProjectileManager& projectileManager);

	// Get the direction the cannon is looking at as a vector
	glm::vec3 GetDirection();

	// Get this cannon's rotatiom matrix
	glm::mat3x3 GetRotationMatrix();

	glm::vec3 position;

private:

	float yaw;
	float pitch;

	float sensitivity;

	float minYaw;
	float maxYaw;

	float minPitch;
	float maxPitch;
};