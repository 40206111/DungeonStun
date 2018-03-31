#pragma once
#include "InputManager.h"
#include "Screen.h"
#include <SFML/Graphics.hpp>

class Menu : public Screen
{
public:
	Menu(sf::RenderWindow &window);
	~Menu() = default;

	void Update(sf::RenderWindow &window, float dt);
	void Render(sf::RenderWindow &window);
private:
	bool start = true;
	bool play = false;
	bool settings = false;
	bool exit = false;
	sf::Texture homescreen;
	sf::Sprite background;
	sf::Font font;
	sf::Text text;
	sf::Text text2;
	sf::Text text3;
};