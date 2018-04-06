#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

Menu::Menu(sf::RenderWindow &window) : Screen(window)
{
	if (!homescreen.loadFromFile("Assets/imgs/9 to die home.png")) {}
	background = sf::Sprite(homescreen);
	font.loadFromFile("Assets/font/rm_typerighter_old.ttf");
	for (int i = 0; i < 3; i++)
	{
		text.push_back(sf::Text());
		text[i].setFont(font);
		text[i].setCharacterSize(238);
	}

	text[0].setString("Press Any Button To Continue");
	text[1].setString("Settings");
	text[2].setString("Exit");
}

void Menu::Update(sf::RenderWindow &window, float dt)
{
	iMan->Update(dt);
	if (!start)
	{
		if (iMan->GetButtonDown(iMan->MENUDOWN)|| iMan->GetAnaDown(iMan->D))
		{
			menu.reset(current);
			text[current].setColor(sf::Color::White);
			current++;
			if (current > 2)
			{
				current = 0;
			}
			menu.set(current);
		}
		if (iMan->GetButtonDown(iMan->MENUUP) || iMan->GetAnaDown(iMan->U))
		{
			menu.reset(current);
			text[current].setColor(sf::Color::White);
			current--;
			if (current < 0)
			{
				current = 2;
			}
			menu.set(current);
		}
		if (iMan->GetButtonDown(iMan->FULLSCREEN))
		{
			fullscreen = !fullscreen;
			if (fullscreen)
			{
				int style = sf::Style::Default | sf::Style::Fullscreen;
				std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();
				window.create(VModes.at(0), "Workin' 9 to Die", style);
			}
			else
			{
				window.create(VideoMode(1280, 720), "Workin' 9 to Die");
			}
		}
		if (!first && iMan->GetButtonDown(iMan->ACCEPT))
		{
			if (menu.test(0))
			{
			}
			if (menu.test(1))
			{
			}
			if (menu.test(2))
			{
				window.close();
			}
		}
		if (!first && iMan->GetButtonDown(iMan->BACK))
		{
			start = true;
			first = true;
			text[0].setString("Press Any Button To Continue");
			text[0].setColor(sf::Color::White);
			menu.reset(0);
			menu.reset(1);
			menu.reset(2);
		}
		else {
			first = false;
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return;
			}
		}
	}
	else {
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				return;
			}

			bool anyKey = false;
			int testVal = -1;
			//get joystick id
			if (start && event.type == sf::Event::JoystickButtonPressed)
			{
				iMan->controlerid = event.joystickMove.joystickId;
				iMan->activeControls = iMan->keyMaps["PS4"];
				anyKey = true;
				testVal = event.key.alt;
			}

			if (start && event.type == sf::Event::KeyPressed)
			{
				iMan->activeControls = iMan->keyMaps["keyboard"];
				anyKey = true;
				testVal = event.key.code;
			}

			if (anyKey) {
				start = false;
				text[0].setString("Play");
				menu.set(current);

				if (testVal == iMan->activeControls.controls[iMan->BACK].first 
					|| testVal == iMan->activeControls.controls[iMan->BACK].second)
				{
					window.close();
				}
			}

			if (start && event.type == sf::Event::JoystickConnected)
			{
				text[0].setString("Press Any Button To Continue");
				text[0].setColor(sf::Color::White);
			}

			if (event.type == sf::Event::JoystickDisconnected)
			{
				if (!start && iMan->activeControls.controlType == "PS4" && iMan->controlerid == event.joystickMove.joystickId)
				{
					start = true;
					text[0].setString("Controller Disconnected...");
					text[0].setColor(sf::Color::Red);
					menu.reset(0);
					menu.reset(1);
					menu.reset(2);
				}
			}
		}
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
		text[0].setPosition((window.getSize().x * 0.5f) - (text[0].getLocalBounds().width * 0.5f), window.getSize().y - (text[0].getLocalBounds().height * 4));
		window.draw(text[0]);
	}
	else
	{
		text[0].setPosition((window.getSize().x * 0.5f) - (text[0].getLocalBounds().width), (window.getSize().y * 0.5f) - (text[0].getLocalBounds().height * 3));
		text[1].setPosition((window.getSize().x * 0.5f) - (text[1].getLocalBounds().width), window.getSize().y * 0.5f - (text[1].getLocalBounds().height));
		text[2].setPosition((window.getSize().x * 0.5f) - (text[2].getLocalBounds().width), (window.getSize().y * 0.5f) + (text[2].getLocalBounds().height * 1));
		for (int i = 0; i < text.size(); ++i)
		{
			if (menu.test(i))
				text[i].setColor(sf::Color::Yellow);
			window.draw(text[i]);
		}
	}
}