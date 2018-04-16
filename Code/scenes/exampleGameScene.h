#pragma once

#include "engine.h"
#include "gameScene.h"

class ExampleGameScene : public GameScene {
protected:

public:
	ExampleGameScene() = default;
	~ExampleGameScene() = default;

	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	void Reset() override;
};