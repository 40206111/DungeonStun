#pragma once

#include "engine.h"

class GameWorkshop : public Scene {
protected:
	std::shared_ptr<Entity> player;
	std::vector<Entity*> enemies;
	std::vector<Entity*> projectiles;

public:
	GameWorkshop() = default;
	~GameWorkshop() = default;

	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	void Reset() override;
};