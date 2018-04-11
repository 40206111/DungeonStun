#pragma once
#include "TextGridScene.h"
#include <SFML/Graphics.hpp>

class ControlsScene : public TextGridScene
{
private:
public:
	ControlsScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
	void Reset() override;
};