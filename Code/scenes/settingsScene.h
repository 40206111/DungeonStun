#pragma once
#include "textScene.h"
#include <SFML/Graphics.hpp>

class SettingsScene : public TextScene
{
private:
public:
	SettingsScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};