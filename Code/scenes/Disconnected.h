#pragma once
#include "textScene.h"
#include <SFML/Graphics.hpp>

class Disconnected : public Scene
{
private:
	bool loaded = false;
	sf::Text discont;
public:
	Disconnected() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
};