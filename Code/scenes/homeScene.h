#pragma once
#include "engine.h"
#include <SFML/Graphics.hpp>

class HomeScene : public Scene
{
private:
	sf::Texture homescreen;
	sf::Sprite background;
	sf::Text text;
	std::shared_ptr<Entity> screen;
	bool showBehind = false;
public:
	HomeScene() = default;
	bool RenderBehind() { return showBehind; }
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	void ReSize() override;
};