#include "settingsScene.h"
#include "../Game.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///SETTINGS SCENE///

//Load method
void SettingsScene::Load()
{
	if (!loaded)
	{
		//Load Text
		for (int i = 0; i < 3; i++)
		{
			text.push_back(sf::Text());
			text[i].setFont(font);
		}
		text[0].setString("Graphics");
		text[0].setColor(sf::Color::Yellow);
		text[1].setString("Controls");
		text[2].setString("Back");
		textAmount = text.size();
		CalculateSpace();
		previousScene = menuScene;
	}
	TextScene::Load();
	loaded = true;
}

//Update method
void SettingsScene::Update(const double &dt)
{
	TextScene::Update(dt);

	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		switch (current)
		{
		case 0:
			ChangeCurrent(0);
			Engine::ChangeMenu(graphicsScene);
			break;
		case 1:
			ChangeCurrent(0);
			Engine::ChangeMenu(controlsScene);
			break;
		case 2:
			ChangeCurrent(0);
			Engine::ChangeMenu(previousScene);
			break;
		default:
			break;
		}
	}
}

//render Method
void SettingsScene::Render()
{
	TextScene::Render();
}

void SettingsScene::UnLoad() {
	TextScene::UnLoad();
}