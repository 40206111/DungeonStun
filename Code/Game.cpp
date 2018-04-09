#include "Game.h"
#include "SystemRenderer.h"
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

void HomeScene::Update(double dt)
{	
	//check if controller disconnected
	if (!sf::Joystick::isConnected(player1->controlerid) && player1->activeControls.controlType == "PS4")
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
			player1->activeControls = player1->keyMaps["PS4"];
			anyKey = true;
			testVal = event.key.alt;
		}

		//if keyboard key pressed
		if (event.type == sf::Event::KeyPressed)
		{
			player1->activeControls = player1->keyMaps["keyboard"];
			anyKey = true;
			testVal = event.key.code;
		}

		// if any key pressed
		if (anyKey) {
				//exit if back pressed
				if (testVal == player1->activeControls.controls[player1->BACK].first
					|| testVal == player1->activeControls.controls[player1->BACK].second)
				{
					Renderer::Shutdown();
					Renderer::GetWindow().close();
				}
				//next scene if not fullscreen
				if (testVal != player1->activeControls.controls[player1->FULLSCREEN].first
					|| testVal != player1->activeControls.controls[player1->FULLSCREEN].second)
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

///MENU SCENE///

//Load method
void MenuScene::Load()
{
	//Load Text
	for (int i = 0; i < 3; i++)
	{
		text.push_back(sf::Text());
		text[i].setFont(font);
	}
	text[0].setString("Play");
	text[1].setString("Settings");
	text[2].setString("Exit");
	menu.set(current);
}

void MenuScene::Update(double dt)
{
	//update input
	player1->Update(dt);

	//if keyboard controls allow mouse input
	if (player1->activeControls.controlType == "keyboard")
	{
		//if mouse over text 0
		if (player1->mMoved && player1->onText(text[0]))
		{
			text[1].setColor(sf::Color::White);
			text[2].setColor(sf::Color::White);
			menu.set(0);
			menu.reset(1);
			menu.reset(2);
		}
		//if mouse over text 1
		else if (player1->mMoved && player1->onText(text[1]))
		{
			text[0].setColor(sf::Color::White);
			text[2].setColor(sf::Color::White);
			menu.reset(0);
			menu.set(1);
			menu.reset(2);
		}
		//if mouse over text 2
		else if (player1->mMoved && player1->onText(text[2]))
		{
			text[0].setColor(sf::Color::White);
			text[1].setColor(sf::Color::White);
			menu.reset(0);
			menu.reset(1);
			menu.set(2);
		}
	}

	//if menu down
	if (player1->GetButtonDown(player1->MENUDOWN) || player1->GetAnaDown(player1->D))
	{
		//highlight next bit of text
		menu.reset(current);
		text[current].setColor(sf::Color::White);
		//loop round text
		current++;
		if (current > 2)
		{
			current = 0;
		}
		menu.set(current);
	}
	if (player1->GetButtonDown(player1->MENUUP) || player1->GetAnaDown(player1->U))
	{
		//highlight next bit of text
		menu.reset(current);
		text[current].setColor(sf::Color::White);
		//loop round text
		current--;
		if (current < 0)
		{
			current = 2;
		}
		menu.set(current);
	}
	//Fullscreen window
	if (player1->GetButtonDown(player1->FULLSCREEN))
	{
		Renderer::ToggleFullscreen();
	}
	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		//Play Game
		if (menu.test(0))
		{
		}
		//Settings
		if (menu.test(1))
		{
			activeScene = settingsScene;
		}
		//Exit
		if (menu.test(2))
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
		}
	}
	//Back
	if (player1->GetButtonDown(player1->BACK))
	{
		//reset text colouurs
		text[1].setColor(sf::Color::White);
		text[2].setColor(sf::Color::White);
		//set current to 0
		current = 0;
		//reset menu options bits
		menu.set(0);
		menu.reset(1);
		menu.reset(2);
		//set active screen
		activeScene = homeScene;
	}

	//poll events
	Event event;
	while (Renderer::GetWindow().pollEvent(event))
	{
		//Close window
		if (event.type == Event::Closed)
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
			return;
		}
		//If controller disconected
		if (event.type == sf::Event::JoystickDisconnected)
		{
			if (player1->activeControls.controlType == "PS4" && player1->controlerid == event.joystickMove.joystickId)
			{
				//reset text colouurs
				text[1].setColor(sf::Color::White);
				text[2].setColor(sf::Color::White);
				//set current to 0
				current = 0;
				//reset menu options bits
				menu.set(0);
				menu.reset(1);
				menu.reset(2);
				//set active screen
				activeScene = homeScene;
			}
		}
	}
}

//Render Method
void MenuScene::Render()
{
	//set text positions to fit screen
	text[0].setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text[0].getLocalBounds().width), (Renderer::GetWindow().getSize().y * 0.5f) - (text[0].getLocalBounds().height * 3));
	text[1].setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text[1].getLocalBounds().width), Renderer::GetWindow().getSize().y * 0.5f - (text[1].getLocalBounds().height));
	text[2].setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text[2].getLocalBounds().width), (Renderer::GetWindow().getSize().y * 0.5f) + (text[2].getLocalBounds().height * 1));
	//render text
	for (int i = 0; i < text.size(); ++i)
	{
		text[i].setCharacterSize(Renderer::GetWindow().getSize().x / 10);
		if (menu.test(i))
			text[i].setColor(sf::Color::Yellow);
		Renderer::Queue(&text[i]);
	}
}

///SETTINGS SCENE///

//Load method
void SettingsScene::Load()
{
	//Load Text
	for (int i = 0; i < 3; i++)
	{
		text.push_back(sf::Text());
		text[i].setFont(font);
	}
	text[0].setString("Graphics");
	text[1].setString("Controls");
	text[2].setString("Back");
	menu.set(current);
}

//Update method
void SettingsScene::Update(double dt)
{
	//update input
	player1->Update(dt);

	//if keyboard controls allow mouse input
	if (player1->activeControls.controlType == "keyboard")
	{
		//if mouse over text 0
		if (player1->mMoved && player1->onText(text[0]))
		{
			text[1].setColor(sf::Color::White);
			text[2].setColor(sf::Color::White);
			menu.set(0);
			menu.reset(1);
			menu.reset(2);
		}
		//if mouse over text 1
		else if (player1->mMoved && player1->onText(text[1]))
		{
			text[0].setColor(sf::Color::White);
			text[2].setColor(sf::Color::White);
			menu.reset(0);
			menu.set(1);
			menu.reset(2);
		}
		//if mouse over text 2
		else if (player1->mMoved && player1->onText(text[2]))
		{
			text[0].setColor(sf::Color::White);
			text[1].setColor(sf::Color::White);
			menu.reset(0);
			menu.reset(1);
			menu.set(2);
		}
	}

	//if menu down
	if (player1->GetButtonDown(player1->MENUDOWN) || player1->GetAnaDown(player1->D))
	{
		//highlight next bit of text
		menu.reset(current);
		text[current].setColor(sf::Color::White);
		//loop round text
		current++;
		if (current > 2)
		{
			current = 0;
		}
		menu.set(current);
	}
	if (player1->GetButtonDown(player1->MENUUP) || player1->GetAnaDown(player1->U))
	{
		//highlight next bit of text
		menu.reset(current);
		text[current].setColor(sf::Color::White);
		//loop round text
		current--;
		if (current < 0)
		{
			current = 2;
		}
		menu.set(current);
	}
	//Fullscreen window
	if (player1->GetButtonDown(player1->FULLSCREEN))
	{
		Renderer::ToggleFullscreen();
	}
	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		//Graphics
		if (menu.test(0))
		{
		}
		//Controls
		if (menu.test(1))
		{
		}
		//Back
		if (menu.test(2))
		{
			//reset text colouurs
			text[1].setColor(sf::Color::White);
			text[2].setColor(sf::Color::White);
			//set current to 0
			current = 0;
			//reset menu options bits
			menu.set(0);
			menu.reset(1);
			menu.reset(2);
			//set active screen
			activeScene = menuScene;
		}
	}
	//Back
	if (player1->GetButtonDown(player1->BACK))
	{
		//reset text colouurs
		text[1].setColor(sf::Color::White);
		text[2].setColor(sf::Color::White);
		//set current to 0
		current = 0;
		//reset menu options bits
		menu.set(0);
		menu.reset(1);
		menu.reset(2);
		//set active screen
		activeScene = menuScene;
	}

	//poll events
	Event event;
	while (Renderer::GetWindow().pollEvent(event))
	{
		//Close window
		if (event.type == Event::Closed)
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
			return;
		}
		//If controller disconected
		if (event.type == sf::Event::JoystickDisconnected)
		{
			if (player1->activeControls.controlType == "PS4" && player1->controlerid == event.joystickMove.joystickId)
			{
				//reset text colouurs
				text[1].setColor(sf::Color::White);
				text[2].setColor(sf::Color::White);
				//set current to 0
				current = 0;
				//reset menu options bits
				menu.set(0);
				menu.reset(1);
				menu.reset(2);
				//set active screen
				activeScene = homeScene;
			}
		}
	}
}

//render Method
void SettingsScene::Render()
{
	//set text positions to fit screen
	text[0].setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text[0].getLocalBounds().width), (Renderer::GetWindow().getSize().y * 0.5f) - (text[0].getLocalBounds().height * 3));
	text[1].setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text[1].getLocalBounds().width), Renderer::GetWindow().getSize().y * 0.5f - (text[1].getLocalBounds().height));
	text[2].setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text[2].getLocalBounds().width), (Renderer::GetWindow().getSize().y * 0.5f) + (text[2].getLocalBounds().height * 1));
	//render text
	for (int i = 0; i < text.size(); ++i)
	{
		text[i].setCharacterSize(Renderer::GetWindow().getSize().x / 10);
		if (menu.test(i))
			text[i].setColor(sf::Color::Yellow);
		Renderer::Queue(&text[i]);
	}
}