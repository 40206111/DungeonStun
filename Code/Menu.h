#pragma once
#include "InputManager.h"
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <bitset>
#include <vector>

class Menu : public Screen
{
public:
	Menu(sf::RenderWindow &window);
	~Menu() = default;

	void Update(sf::RenderWindow &window, float dt);
	void Render(sf::RenderWindow &window);
private:
	std::bitset<3> menu;
	int current = 0;
	bool start = true;
	sf::Texture homescreen;
	sf::Sprite background;
	sf::Font font;
	std::vector<sf::Text> text;
};