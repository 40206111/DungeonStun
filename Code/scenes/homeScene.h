#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class HomeScene : public Scene
{
private:
	sf::Texture homescreen;
	sf::Sprite background;
	sf::Text text;
public:
	HomeScene() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
};