#pragma once

#include "GLCommon.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector> 
#include <fstream>
#include <sstream>

#include "ShaderManager.h"
#include "Camera.h"
#include "Scene.h"
#include "SceneSerializer.h"
#include "Light.h"
#include "Model.h"
#include "Cannon.h"
#include "World.h"
#include "ProjectileSerializer.h"
#include "CannonSerializer.h"
#include "CollisionDetector.h"
#include "Target.h"

const float windowWidth = 1200;
const float windowHeight = 640;
bool editMode = true;

ShaderManager gShaderManager;

const std::string sceneName = "Project_1";
Scene scene(sceneName);

Camera camera(windowHeight, windowWidth);
float moveSpeed = 1.1f;

int currentEditIndex = 0;

bool onePressed = false;
bool twoPressed = false;
bool threePressed = false;
bool fourPressed = false;

bool isLeftDown = false;
bool isRightDown = false;;
bool isUpDown = false;;
bool isDownDown = false;;

static bool copyFile(std::string src, std::string dest)
{
	std::ifstream ifSrc(src, std::ios::binary);
	std::ofstream ofDest(dest, std::ios::binary);
	ofDest << ifSrc.rdbuf();
	return ifSrc && ofDest;
}

static bool doesFileExist(std::string path)
{
	std::ifstream ifs(path);
	return ifs.good();
}

static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Movement controls
	if (!editMode)
	{
		if (key == GLFW_KEY_W)
		{
			camera.position += camera.direction * moveSpeed;
		}
		if (key == GLFW_KEY_A)
		{
			// Rotate our camera's direction 90 degrees to the left
			glm::vec3 left;
			constexpr float theta = glm::radians(90.0f);
			left.x = camera.direction.x * cos(theta) + camera.direction.z * sin(theta);
			left.y = 0.0f;
			left.z = -camera.direction.x * sin(theta) + camera.direction.z * cos(theta);
			camera.position += left * moveSpeed;
		}
		if (key == GLFW_KEY_S)
		{
			camera.position -= camera.direction * moveSpeed;
		}
		if (key == GLFW_KEY_D)
		{
			// Rotate our camera's direction 90 degrees to the right
			glm::vec3 right;
			constexpr float theta = glm::radians(-90.0f);
			right.x = camera.direction.x * cos(theta) + camera.direction.z * sin(theta);
			right.y = 0.0f;
			right.z = -camera.direction.x * sin(theta) + camera.direction.z * cos(theta);
			camera.position += right * moveSpeed;
		}
		if (key == GLFW_KEY_SPACE)
		{
			camera.position.y += moveSpeed;
		}
	}

	if (key == GLFW_KEY_UP)
	{
		if (action == GLFW_PRESS)
		{
			isUpDown = true;
		}
		else if (action == GLFW_RELEASE)
		{
			isUpDown = false;
		}
	}
	if (key == GLFW_KEY_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			isRightDown = true;
		}
		else if (action == GLFW_RELEASE)
		{
			isRightDown = false;
		}
	}
	if (key == GLFW_KEY_DOWN)
	{
		if (action == GLFW_PRESS)
		{
			isDownDown = true;
		}
		else if (action == GLFW_RELEASE)
		{
			isDownDown = false;
		}
	}
	if (key == GLFW_KEY_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			isLeftDown = true;
		}
		else if (action == GLFW_RELEASE)
		{
			isLeftDown = false;
		}
	}

	if (key == GLFW_KEY_1)
	{
		if (action == GLFW_PRESS)
		{
			onePressed = true;
		}
		else if (action == GLFW_RELEASE)
		{
			onePressed = false;
		}
	}
	if (key == GLFW_KEY_2)
	{
		if (action == GLFW_PRESS)
		{
			twoPressed = true;
		}
		else if (action == GLFW_RELEASE)
		{
			twoPressed = false;
		}
	}
	if (key == GLFW_KEY_3)
	{
		if (action == GLFW_PRESS)
		{
			threePressed = true;
		}
		else if (action == GLFW_RELEASE)
		{
			threePressed = false;
		}
	}
	if (key == GLFW_KEY_4)
	{
		if (action == GLFW_PRESS)
		{
			fourPressed = true;
		}
		else if (action == GLFW_RELEASE)
		{
			fourPressed = false;
		}
	}

	// Toggle cursor view
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		editMode = !editMode;
		int cursorOption = editMode ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
		glfwSetInputMode(window, GLFW_CURSOR, cursorOption);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!editMode)
	{
		camera.MoveCamera(xpos, ypos);
	}
}

bool InitializerShaders();

int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Initialize our window
	window = glfwCreateWindow(windowWidth, windowHeight, "Midterm", NULL, NULL);

	// Make sure the window initialized properly
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback); // Tell GLFW where our key callbacks are
	glfwSetCursorPosCallback(window, mouse_callback); // Tell GLFW where our mouse callback is

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress); // Give glad this process ID
	glfwSwapInterval(1);

	if (!InitializerShaders())
	{
		return -1;
	}

	// Setup world
	World* world = new World();
	std::vector<Particle*> particles;

	// Load projectile types
	ProjectileManager projectileManager;
	ProjectileSerializer projectileSerializer;
	{
		sProjectileInfo info;
		std::stringstream ss;
		ss << SOLUTION_DIR << "Extern\\assets\\projectiles\\Bullet.json";
		projectileSerializer.LoadProjectile(ss.str(), info);
		projectileManager.RegisterProjectile(ProjectileType::Bullet, info);
	}
	{
		sProjectileInfo info;
		std::stringstream ss;
		ss << SOLUTION_DIR << "Extern\\assets\\projectiles\\Laser.json";
		projectileSerializer.LoadProjectile(ss.str(), info);
		projectileManager.RegisterProjectile(ProjectileType::Laser, info);
	}
	{
		sProjectileInfo info;
		std::stringstream ss;
		ss << SOLUTION_DIR << "Extern\\assets\\projectiles\\CannonBall.json";
		projectileSerializer.LoadProjectile(ss.str(), info);
		projectileManager.RegisterProjectile(ProjectileType::CannonBall, info);
	}
	{
		sProjectileInfo info;
		std::stringstream ss;
		ss << SOLUTION_DIR << "Extern\\assets\\projectiles\\EnergyBall.json";
		projectileSerializer.LoadProjectile(ss.str(), info);
		projectileManager.RegisterProjectile(ProjectileType::EnergyBall, info);
	}

	// Load in scene
	std::stringstream ss;
	ss << SOLUTION_DIR << "Extern\\assets\\models\\box.obj";
	Model ground(ss.str());
	ss.str("");

	ss << SOLUTION_DIR << "Extern\\assets\\models\\cylinder.obj";
	Model cylinder(ss.str());
	ss.str("");

	ss << SOLUTION_DIR << "Extern\\assets\\models\\SoccerBall.obj";
	Model sphere(ss.str());
	ss.str("");
	
	CannonSerializer cannonSeralizer;
	Cannon cannon(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
	ss << SOLUTION_DIR << "Extern\\assets\\cannons\\Cannon.json";
	cannonSeralizer.LoadCannon(ss.str(), cannon);
	ss.str("");

	// Spawn the camera facing the cannon
	glm::vec3 cannonDir = cannon.GetDirection();
	cannonDir.y = 0.0f;
	cannonDir *= 30.0f;
	camera.position = cannon.position - cannonDir;
	camera.position.y = cannon.position.y + 7.0f;
	camera.direction = cannon.position - camera.position;

	// Add one target
	glm::vec3 targetDir = cannon.GetDirection();
	targetDir *= 40.0f;
	targetDir.y = 0.5f;
	glm::vec3 targetPos = cannon.position + targetDir;
	Particle* target = new Target(targetPos);
	world->AddTarget(target);
	particles.push_back(target);

	CompiledShader shader = *gShaderManager.pGetShaderProgramFromFriendlyName("Shader#1");

	float fpsFrameCount = 0.f;
	float fpsTimeElapsed = 0.f;

	float previousTime = static_cast<float>(glfwGetTime());

	CollisionDetector collisionDetector;

	// Our actual render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// FPS TITLE
		{
			fpsTimeElapsed += deltaTime;
			fpsFrameCount += 1.0f;
			if (fpsTimeElapsed >= 0.03f)
			{
				std::string fps = std::to_string(fpsFrameCount / fpsTimeElapsed);
				std::string ms = std::to_string(1000.f * fpsTimeElapsed / fpsFrameCount);
				std::string newTitle = "FPS: " + fps + "   MS: " + ms;
				glfwSetWindowTitle(window, newTitle.c_str());

	
				fpsTimeElapsed = 0.f;
				fpsFrameCount = 0.f;
			}
		}

		float ratio;
		int width, height;
		glm::mat4 projection;
		glm::mat4 view;

		glfwGetFramebufferSize(window, &width, &height); // Assign width and height to our window width and height
		ratio = width / (float)height;

		glEnable(GL_DEPTH);
		glEnable(GL_DEPTH_TEST); // Enables the Depth Buffer, which decides which pixels will be drawn based on their depth (AKA don't draw pixels that are behind other pixels)

		glViewport(0, 0, width, height); // Specifies the transformation of device coords to window coords 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clears the buffers

		view = camera.GetViewMatrix();
		projection = glm::perspective(0.6f, ratio, 0.1f, 1000.0f);

		glUseProgram(shader.ID);
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "matView"), 1, GL_FALSE, glm::value_ptr(view)); // Assign new view matrix
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "matProjection"), 1, GL_FALSE, glm::value_ptr(projection)); // Assign projection

		if (isRightDown)
		{
			cannon.LookRight(deltaTime);
		}
		else if (isLeftDown)
		{
			cannon.LookLeft(deltaTime);
		}
		else if (isUpDown)
		{
			cannon.LookUp(deltaTime);
		}
		else if (isDownDown)
		{
			cannon.LookDown(deltaTime);
		}

		if (onePressed)
		{
			Projectile* projectile = cannon.FireProjectile(ProjectileType::Bullet, projectileManager);
			if (projectile)
			{
				world->AddParticle(projectile);
				particles.push_back(projectile);
			}

			onePressed = false;
		}
		if (twoPressed)
		{
			Projectile* projectile = cannon.FireProjectile(ProjectileType::Laser, projectileManager);
			if (projectile)
			{
				world->AddParticle(projectile);
				particles.push_back(projectile);
			}
			twoPressed = false;
		}
		if (threePressed)
		{
			Projectile* projectile = cannon.FireProjectile(ProjectileType::CannonBall, projectileManager);
			if (projectile)
			{
				world->AddParticle(projectile);
				particles.push_back(projectile);
			}
			threePressed = false;
		}
		if (fourPressed)
		{
			Projectile* projectile = cannon.FireProjectile(ProjectileType::EnergyBall, projectileManager);
			if (projectile)
			{
				world->AddParticle(projectile);
				particles.push_back(projectile);
			}
			fourPressed = false;
		}

		// Validate all registered particles
		for (std::vector<Particle*>::iterator it = particles.begin(); it != particles.end();)
		{
			Particle* particle = *it;
			if (particle->IsValid())
			{
				it++;
			}
			else
			{ // We are no longer valid
				it = particles.erase(it);
				world->RemoveParticle(particle);
				delete particle; // We are now forever done with this particle, remove it from memory
			}
		}

		// Integrate all particles in the world
		world->Tick(deltaTime);

		// Safety, mostly for first frame
		if (deltaTime == 0.0f)
		{
			deltaTime = 0.03f;
		}

		// Render the models
		ground.Draw(shader, glm::vec3(-10.0f, -1.0f, -5.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(10.0f, 0.2f, 10.0f));
		glm::mat3x3 rot = cannon.GetRotationMatrix();
		cylinder.Draw(shader, cannon.position, rot[0], rot[1], rot[2], glm::vec3(1.0f, 3.0f, 1.0f));

		glm::vec3 position(0.0f);
		for (Particle* p : particles)
		{
			p->GetPosition(position);
			sphere.Draw(shader, position, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(p->GetSize()));
		}

		// Show what we've drawn
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	for (Particle* p : particles)
	{
		world->RemoveParticle(p);
		delete p;
	}

	delete world;

	glfwDestroyWindow(window); // Clean up the window

	glfwTerminate(); 
	exit(EXIT_SUCCESS);
}


bool InitializerShaders()
{
	std::stringstream ss;

	// "Normal" Shader
	Shader vertexShader;
	ss << SOLUTION_DIR << "Extern\\assets\\shaders\\vertexShader.glsl";
	vertexShader.fileName = ss.str();
	ss.str("");

	Shader fragmentShader;
	ss << SOLUTION_DIR << "Extern\\assets\\shaders\\fragmentShader.glsl";
	fragmentShader.fileName = ss.str();
	ss.str("");

	bool success = gShaderManager.createProgramFromFile("Shader#1", vertexShader, fragmentShader);
	if (success)
	{
		std::cout << "Shaders compiled OK" << std::endl;
	}
	else
	{
		std::cout << "Error making shaders: " << std::endl;
		std::cout << gShaderManager.getLastError() << std::endl;
		return 1;
	}

	return success;
}