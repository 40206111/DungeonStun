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
	static bool start = true;

	if (!start)
		iMan->Update(dt);

	Event event;

	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}

		//get joystick id
		if (start && event.type == sf::Event::JoystickButtonPressed)
		{
			iMan->controlerid = event.joystickMove.joystickId;
			iMan->activeControls = iMan->keyMaps["PS4"];
			start = false;
		}

		if (start && event.type == sf::Event::KeyPressed)
		{
			iMan->activeControls = iMan->keyMaps["keyboard"];
			start = false;
		}

		if (event.type == sf::Event::JoystickConnected)
		{
			cout << "controller connected: "  << event.joystickMove.joystickId << endl;

		}

		if (event.type == sf::Event::JoystickDisconnected)
		{
			cout << "controller disconnected: " << event.joystickMove.joystickId << endl;
			if (!start && iMan->activeControls.controlType == "PS4" && iMan->controlerid == event.joystickMove.joystickId)
			{
				start = true;
			}
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