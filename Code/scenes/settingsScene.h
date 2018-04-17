#pragma once
#include "textScene.h"
#include <SFML/Graphics.hpp>

class SettingsScene : public TextScene
{
private:
public:
	SettingsScene() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
};