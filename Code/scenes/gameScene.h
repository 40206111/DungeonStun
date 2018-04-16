#pragma once

#include "engine.h"

class GameScene : public Scene {
protected:
	std::shared_ptr<Entity> player;
	std::vector<Entity*> enemies;
	std::vector<Entity*> projectiles;
	std::shared_ptr<Scene> activeMenu;
	std::shared_ptr<Entity> screen;
	std::shared_ptr<Entity> background;
	bool showBehind = false;

public:
	GameScene() = default;
	~GameScene() = default;

	bool RenderBehind() { return showBehind; }

	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	void Reset() override;
	void ReSize() override;
};