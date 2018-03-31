#include "Menu.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Menu::Menu(sf::RenderWindow &window) : Screen(window)
{
	if (!homescreen.loadFromFile("Assets/imgs/9 to die home.png")) {}
	background = sf::Sprite(homescreen);
	font.loadFromFile("Assets/font/rm_typerighter_old.ttf");
	text.setFont(font);
	text2.setFont(font);
	text3.setFont(font);
	text.setCharacterSize(238);
	text2.setCharacterSize(238);
	text3.setCharacterSize(238);
	text.setString("Press Any Button To Continue");
	text2.setString("Settings");
	text3.setString("Exit");
}

void Menu::Update(sf::RenderWindow &window, float dt)
{
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

		if (event.type == sf::Event::JoystickDisconnected)
		{
			if (!start && iMan->activeControls.controlType == "PS4" && iMan->controlerid == event.joystickMove.joystickId)
			{
				start = true;
			}
		}
	}

	if (!start)
	{
		text.setString("Play");
		text.setColor(sf::Color::Yellow);
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}
}

void Menu::Render(sf::RenderWindow &window)
{
	if (start)
	{
		window.draw(background);
		background.setScale(
			window.getSize().x / background.getLocalBounds().width,
			window.getSize().y / background.getLocalBounds().height);
		text.setPosition((window.getSize().x * 0.5f) - (text.getLocalBounds().width * 0.5f), window.getSize().y - (text.getLocalBounds().height * 4));
	}
	window.draw(text);
	if (!start)
	{
		text.setPosition((window.getSize().x * 0.5f) - (text.getLocalBounds().width), (window.getSize().y * 0.5f) - (text.getLocalBounds().height * 3));
		window.draw(text2);
		text2.setPosition((window.getSize().x * 0.5f) - (text.getLocalBounds().width), window.getSize().y * 0.5f - (text.getLocalBounds().height));
		window.draw(text3);
		text3.setPosition((window.getSize().x * 0.5f) - (text.getLocalBounds().width), (window.getSize().y * 0.5f) + (text.getLocalBounds().height * 1));
	}
}