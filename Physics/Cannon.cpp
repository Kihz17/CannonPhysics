#include "Cannon.h"

#include <glm/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <iostream>

const float _2PI = M_PI * 2.0f;
const float degreesToFlushCannon = 90.0f; // We need to rotate the cannon 90 degrees in the pitch to make its starting point flush with the ground (this is because the cylinder model is pointing upwards by default)

Cannon::Cannon(glm::vec3 position, glm::vec3 initialDirection, float sensitivity)
	: position(position)
{
	// Convert the initial direction to yaw and pitch
	this->yaw = atan2(initialDirection.x, initialDirection.z);
	this->pitch = glm::radians(degreesToFlushCannon); // Make are starting pitch tiliting slighly upwards

	// Allow the cannon to rotate 1/4 of pi from its current position
	float yawRange = M_PI / 4;
	this->minYaw = this->yaw - yawRange;
	this->maxYaw = this->yaw + yawRange;

	this->minPitch = pitch; // Level with the ground
	this->maxPitch = pitch + (M_PI * (7.0f / 16.0f)); // 7/16ths of PI from its current position

	this->sensitivity = sensitivity;
}

Projectile* Cannon::FireProjectile(ProjectileType type, ProjectileManager& projectileManager)
{
	glm::vec3 direction = this->GetDirection();
	// We want the projectile to start at the cannon's position with an offset of where the cannon is pointing
	// We scale the direction by 3 here because we scale the cylinder model by 3 in the y when we render it
	glm::vec3 startPos = this->position + (direction * 3.0f);

	Projectile* projectile = projectileManager.CreateProjectile(type, startPos, direction);
	return projectile;
}

void Cannon::LookLeft(float deltaTime)
{
	this->yaw = std::max(this->minYaw, this->yaw - (this->sensitivity * deltaTime));
	std::cout << "Yaw: " << this->yaw << " Pitch: " << this->pitch << std::endl;
}

void Cannon::LookRight(float deltaTime)
{
	this->yaw = std::min(this->maxYaw, this->yaw + (this->sensitivity * deltaTime));
	std::cout << "Yaw: " << this->yaw << " Pitch: " << this->pitch << std::endl;
}

void Cannon::LookUp(float deltaTime)
{
	this->pitch = std::min(this->maxPitch, this->pitch + (this->sensitivity * deltaTime));
	std::cout << "Yaw: " << this->yaw << " Pitch: " << this->pitch << std::endl;
}

void Cannon::LookDown(float deltaTime)
{
	this->pitch = std::max(this->minPitch, this->pitch - (this->sensitivity * deltaTime));
	std::cout << "Yaw: " << this->yaw << " Pitch: " << this->pitch << std::endl;
}

float Cannon::GetYaw()
{
	return this->yaw;
}

float Cannon::GetPitch()
{
	return this->pitch;
}

glm::vec3 Cannon::GetDirection()
{
	// Convert our yaw/pitch to a directional vector
	// NOTE: We need to offset by the amount of degrees we initially offset the cannon by to ensure that the vector points the correct direction
	glm::vec3 direction;
	float pitch = this->pitch + glm::radians(degreesToFlushCannon);
	float xz = cos(pitch);
	direction.x = -xz * sin(this->yaw - glm::radians(degreesToFlushCannon));
	direction.y = -sin(pitch);
	direction.z = xz * cos(this->yaw - glm::radians(degreesToFlushCannon));
	glm::normalize(direction);
	return direction;
}

glm::mat3x3 Cannon::GetRotationMatrix()
{
	glm::mat3x3 matrix(1.0f);
	float roll = glm::radians(0.0f); // No roll for the cannon

// Convert sines and cosines for our cannon's euler angles
	double rollSin = sin(roll);
	double rollCos = cos(roll);
	double yawSin = sin(this->yaw);
	double yawCos = cos(this->yaw);
	double pitchSin = sin(this->pitch);
	double pitchCos = cos(this->pitch);

	// Provide the cannon's model with our new rotation matrix
	matrix[0] = glm::vec3(yawCos * pitchCos, rollSin * yawSin * pitchCos - rollCos * pitchSin, rollSin * pitchSin + rollCos * yawSin * pitchCos); // X axis
	matrix[1] = glm::vec3(yawCos * pitchSin, rollCos * pitchCos + rollSin * yawSin * pitchSin, rollCos * yawSin * pitchSin - rollSin * pitchCos); // Y axis
	matrix[2] = glm::vec3(-yawSin, rollSin * yawSin, rollCos * yawCos); // Z axis

	return matrix;
}


void Cannon::SetYaw(float value)
{
	this->yaw = value;
}

void Cannon::SetMinYaw(float value)
{
	this->minYaw = value;
}

void Cannon::SetMaxYaw(float value)
{
	this->maxYaw = value;
}

void Cannon::SetPitch(float value)
{
	this->pitch = value;
}

void Cannon::SetMinPitch(float value)
{
	this->minPitch = value;
}

void Cannon::SetMaxPitch(float value)
{
	this->maxPitch = value;
}