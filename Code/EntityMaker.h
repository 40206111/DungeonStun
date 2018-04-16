#pragma once

#include "ecm.h"

#define em EntityMaker

class EntityMaker {
private:
	EntityMaker() = delete;
	~EntityMaker() = delete;
protected:
	static std::weak_ptr<Entity> player;
	static void MakeEnemy(std::shared_ptr<Entity>);
	static void MakePlayer(std::shared_ptr<Entity>);
public:
	enum Prefab{ENEMY, PLAYER, WALL, CHEST, PLATFORM};

	static void MakeEntity(std::shared_ptr<Entity>, Prefab);
};