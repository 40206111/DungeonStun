#pragma once
#include "InputManager.h"
#include <SFML/Graphics.hpp>

class Screen
{
public:
	Screen(sf::RenderWindow &window);
	virtual ~Screen() = default;

	virtual void Update(sf::RenderWindow &window, float dt);
	 virtual void Render(sf::RenderWindow &window);
protected:
	InputManager* iMan = new InputManager();
};