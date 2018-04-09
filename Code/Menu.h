#pragma once
#include "InputManager.h"
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <bitset>
#include <vector>

//Class to create start menus
class Menu : public Screen
{
public:
	//Constructors
	Menu(sf::RenderWindow &window);
	~Menu() = default;

	//Methods
	void Update(sf::RenderWindow &window, float dt);
	void Render(sf::RenderWindow &window);
private:
	//Menu buttons
	std::bitset<3> menu;
	//currently selected
	int current = 0;
	//bool to test if on start menu
	bool start = true;
	bool first = true;
	bool fullscreen = false;
	//Textures and text
	sf::Texture homescreen;
	sf::Sprite background;
	sf::Font font;
	std::vector<sf::Text> text;
};