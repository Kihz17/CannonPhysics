#include "Projectile.h"

#include <glm/glm.hpp>
#include <iostream>

Projectile::Projectile(float mass, glm::vec3 position, glm::vec3 velocity, float size, bool isTimed, float timeLimit, bool hasDistanceLimit, float distanceLimit)
	: Particle(mass, position)
{
	this->SetRadius(size * 2.2f);
	this->SetVelocity(velocity);

	this->bIsTimed = isTimed;
	this->mTimeLimit = timeLimit;

	this->bHasDistanceLimit = hasDistanceLimit;
	this->mDistanceLimit = distanceLimit;
	this->mOriginalPosition = position;
}

void Projectile::Integrate(float deltaTime)
{
	Particle::Integrate(deltaTime);
	this->mTimeLived += deltaTime;
}

bool Projectile::IsValid()
{
	bool aboveGround = this->GetPosition().y > -3.0f;
	bool isExpired = bIsTimed && this->mTimeLimit > this->mTimeLimit;
	bool isTooFar = this->bHasDistanceLimit && glm::distance(this->mOriginalPosition, this->GetPosition()) > this->mDistanceLimit;
	return aboveGround && !isExpired && !isTooFar;
}