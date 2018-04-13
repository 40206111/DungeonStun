#pragma once

#include "engine.h"

class GameScene : public Scene {
protected:
	std::shared_ptr<Entity> player;
	std::vector<Entity*> enemies;
	std::vector<Entity*> projectiles;
	std::shared_ptr<Scene> activeMenu;
	bool menuUp = false;
	const bool showBehind = false;

public:
	GameScene() = default;
	GameScene(bool);
	~GameScene() = default;

	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	void Reset() override;
};