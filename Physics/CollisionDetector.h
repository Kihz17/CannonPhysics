#pragma once

#include "Particle.h"

class CollisionDetector
{
public:
	CollisionDetector();

	bool CheckCollision(Particle* p1, Particle* p2);
};