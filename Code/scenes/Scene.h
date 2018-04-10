#pragma once
#include "../Entity.h"
#include "../EntityManager.h"
#include "../InputManager.h"
#include <vector>
#include <memory>

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	//virtual
	virtual void Update(double dt) {}
	virtual void Render() {}
	virtual void Load() {}
	virtual void Reset() {}

	std::vector<std::shared_ptr<Entity>> &getEnts() {}
protected:
	EntityManager _ents;
};