#pragma once

#include "engine.h"
#include "..\EntityMaker.h"

class GameScene : public Scene {
protected:
	std::shared_ptr<Entity> player;
	std::vector<std::shared_ptr<Entity>> enemies;
	std::vector<std::shared_ptr<Entity>> projectiles;
	std::shared_ptr<Scene> activeMenu;
	std::shared_ptr<Entity> screen;
	bool showBehind = false;

public:
	GameScene() = default;
	~GameScene() = default;

	bool RenderBehind() { return showBehind; }
	std::shared_ptr<Entity> SpawnEntity(em::Prefab);

	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	void Reset() override;
};