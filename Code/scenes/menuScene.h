#pragma once
#include "textScene.h"
#include <SFML/Graphics.hpp>

class MenuScene : public TextScene
{
private:

public:
	MenuScene() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
};