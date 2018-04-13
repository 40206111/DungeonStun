#pragma once

#include "engine.h"

class GameScene : public Scene {
protected:
	Entity * player;
	std::vector<Entity*> enemies;
	std::vector<Entity*> projectiles;

public:
	GameScene() = default;
	~GameScene() = default;

	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void Reset() override;
};