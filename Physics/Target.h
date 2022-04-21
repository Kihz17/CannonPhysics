#pragma once

#include "Particle.h"

#include <glm/vec3.hpp>

class Target : public Particle
{
public:
	Target(glm::vec3& position);

	virtual void OnCollision(Particle* collidedWith);

	virtual bool IsValid();
};