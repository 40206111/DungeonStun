#pragma once
#include "engine.h"
#include <SFML/Graphics.hpp>

class GameOver : public Scene
{
private:
	sf::Text text;
public:
	GameOver() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void ReSize() override;
};