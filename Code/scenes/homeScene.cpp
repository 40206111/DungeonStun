#include "homeScene.h"
#include "../Game.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///HOME SCENE///

//Load method
void HomeScene::Load()
{
	//load background
	if (!homescreen.loadFromFile("Assets/imgs/9 to die home.png")) {}
	background = sf::Sprite(homescreen);
	//Load text
	text = sf::Text();
	text.setFont(font);
	text.setString("Press Any Button To Continue");
}

void HomeScene::Update(const double &dt)
{
	if (player1->activeControls != nullptr)
	{
		//check if controller disconnected
		if (!sf::Joystick::isConnected(player1->controlerid) && player1->activeControls->controlType == "PS4")
		{
			text.setString("Controller Disconnected...");
			text.setColor(sf::Color::Red);
		}
		//update input
		player1->Update(dt);

		//check if fullscreen
		if (player1->GetButtonDown(player1->FULLSCREEN))
		{
			Renderer::ToggleFullscreen();
		}
		//Exit
		if (player1->GetButtonDown(player1->BACK))
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
		}
	}

	//Poll events
	Event event;
	while (Renderer::GetWindow().pollEvent(event))
	{
		//if Controller connected
		if (event.type == sf::Event::JoystickConnected)
		{
			text.setString("Press Any Button To Continue");
			text.setColor(sf::Color::White);
		}
		//if window closed
		if (event.type == Event::Closed)
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
			return;
		}

		///check if any key is pressed///
		bool anyKey = false;
		int testVal = -1;
		//if controller button pressed
		if (event.type == sf::Event::JoystickButtonPressed)
		{
			player1->controlerid = event.joystickMove.joystickId;
			player1->activeControls = player1->keyMaps[player1->primaryPS4];
			anyKey = true;
			testVal = event.key.alt;
		}

		//if keyboard key pressed
		if (event.type == sf::Event::KeyPressed)
		{
			player1->activeControls = player1->keyMaps[player1->primaryKeyboard];
			anyKey = true;
			testVal = event.key.code;
		}

		// if any key pressed
		if (anyKey) {
			//exit if back pressed
			if (testVal == player1->activeControls->controls[player1->BACK].first
				|| testVal == player1->activeControls->controls[player1->BACK].second)
			{
				Renderer::Shutdown();
				Renderer::GetWindow().close();
			}
			//next scene if not fullscreen
			if (testVal != player1->activeControls->controls[player1->FULLSCREEN].first
				|| testVal != player1->activeControls->controls[player1->FULLSCREEN].second)
			{
				activeScene = menuScene;
			}
		}
	}
}

//Render method
void HomeScene::Render()
{
	//make background fit screen
	background.setScale(
		Renderer::GetWindow().getSize().x / background.getLocalBounds().width,
		Renderer::GetWindow().getSize().y / background.getLocalBounds().height);
	//Render Background
	Renderer::Queue(&background);

	//make text fit screen
	text.setCharacterSize(Renderer::GetWindow().getSize().x / 10);
	text.setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text.getLocalBounds().width * 0.5f),
		Renderer::GetWindow().getSize().y - (text.getLocalBounds().height * 4));
	//render text
	Renderer::Queue(&text);
}