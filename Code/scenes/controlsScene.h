#pragma once
#include "textScene.h"
#include <SFML/Graphics.hpp>

class ControlsScene : public TextScene
{
private:
public:
	ControlsScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
	void Reset() override;
};