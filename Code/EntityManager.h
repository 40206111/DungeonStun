#pragma once
#include "Entity.h"

struct EntityManager
{
	std::vector<std::shared_ptr<Entity>> list;
	void Update(double dt);
	void Render();
};