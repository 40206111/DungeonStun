#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include <iostream>
using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;

void Render(RenderWindow &window)
{
}

void Load()
{
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Workin' 9 to Die");
	Load();

	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}