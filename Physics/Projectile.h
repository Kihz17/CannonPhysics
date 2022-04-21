#pragma once

#include "Particle.h"

#include <glm/vec3.hpp>

enum ProjectileType
{
	Bullet,
	Laser,
	CannonBall,
	EnergyBall
};

struct sProjectileInfo
{
	float size;
	float damping;
	float mass;
	float velocity;

	bool isTimeLimit;
	float timeLimit;

	bool isDistanceLimit;
	float distanceLimit;
};

class Projectile : public Particle
{
public:
	Projectile(float mass, glm::vec3 position, glm::vec3 velocity, float size, bool isTimed, float timeLimit, bool hasDistanceLimit, float distanceLimit);

	virtual void Integrate(float deltaTime);

	virtual bool IsValid();

private:

	bool bIsTimed;
	float mTimeLimit;
	float mTimeLived;

	bool bHasDistanceLimit;
	float mDistanceLimit;
	glm::vec3 mOriginalPosition;
};
