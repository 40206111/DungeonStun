#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include <iostream>
using namespace sf;
using namespace std;

int gameWidth = 800;
int gameHeight = 600;
InputManager* iMan;

void Render(RenderWindow &window)
{
}

void Load()
{
	iMan = new InputManager();
}

void Update(RenderWindow &window)
{
	static Clock clock;
	float dt = clock.restart().asSeconds();

	iMan->Update(dt);

	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}

		//GET BUTTON CODE 
		//if (event.type == sf::Event::JoystickButtonPressed)
		//{
		//	cout << event.joystickButton.button << endl;
		//}

		if (event.type == sf::Event::JoystickConnected)
		{
			cout << "controller connected: "  << event.joystickMove.joystickId << endl;
		}

		if (event.type == sf::Event::JoystickDisconnected)
		{
			cout << "controller disconnected: " << event.joystickMove.joystickId << endl;
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