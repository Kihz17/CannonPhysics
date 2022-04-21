#pragma once

#include <rapidjson/document.h>

#include "Cannon.h"

class CannonSerializer
{
public:
	CannonSerializer();

	void LoadCannon(std::string loadPath, Cannon& cannon);
};