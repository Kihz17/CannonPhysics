#include "Target.h"

#include "PhysicsUtils.h"

Target::Target(glm::vec3& position)
	: Particle(1.0f, position)
{

}

void Target::OnCollision(Particle* collidedWith)
{
	glm::vec3 pos = collidedWith->GetPosition();
	this->SetPosition(glm::vec3(pos.x + getRandom(-6.0f, 6.0f), pos.y + getRandom(-6.0f, 6.0f), pos.z + getRandom(-6.0f, 6.0f)));
}

bool Target::IsValid()
{
	return true;
}