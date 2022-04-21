#include "CollisionDetector.h"

#include <glm/glm.hpp>

CollisionDetector::CollisionDetector()
{

}

bool CollisionDetector::CheckCollision(Particle* p1, Particle* p2)
{
	if (!p1 || !p2)
	{
		return false;
	}

	// All we are doing here is checking if the distance between the 2 particles are less than the sum of the radii
	float distance = glm::distance(p1->GetPosition(), p2->GetPosition());
	if (distance < (p1->GetRadius() + p2->GetRadius()))
	{ // We have collided
		return true;
	}

	return false;
}