#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include <vector>
#include <memory>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual void Update(double dt);
	virtual void Render();
	virtual void Load();
	std::vector<std::shared_ptr<Entity>> &getEnts();
protected:
	EntityManager _ents;
};