#pragma once
#include "engine.h"
#include <SFML/Graphics.hpp>

class Victory : public Scene
{
private:
	sf::Text text;
public:
	Victory() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void ReSize() override;
};