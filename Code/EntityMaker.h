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
	static void MakeProjectile(std::shared_ptr<Entity>);
	static void MakeWall(std::shared_ptr<Entity>);
	static void MakeChest(std::shared_ptr<Entity>);
	static void MakePlatform(std::shared_ptr<Entity>);
public:
	enum Prefab{ENEMY, PLAYER, PROJECTILE, WALL, CHEST, PLATFORM};

	static void MakeEntity(std::shared_ptr<Entity>, Prefab);
};