#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Menu.h"
#include <iostream>
using namespace sf;
using namespace std;

Screen *current;

void Render(RenderWindow &window)
{
	current->Render(window);
}

void Load()
{		
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	static bool start = true;
	current->Update(window, dt);
}

int main()
{
	int style = sf::Style::Default | sf::Style::Fullscreen;
	std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();
	RenderWindow window(VModes.at(0), "Workin' 9 to Die", style);
	Load();
	current = new Menu(window);

	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}