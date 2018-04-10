#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class MenuScene : public Scene
{
private:
	std::vector<sf::Text> text;
	//Menu buttons
	std::bitset<3> menu;
	//currently selected
	int current = 0;

public:
	MenuScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};