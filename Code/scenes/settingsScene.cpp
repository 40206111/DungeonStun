#include "settingsScene.h"
#include "../Game.h"
#include "../SystemRenderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

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
	textAmount = text.size();
	previousScene = menuScene;
}

//Update method
void SettingsScene::Update(double dt)
{
	TextScene::Update(dt);

	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		switch (current)
		{
		case 0:
			activeScene = graphicsScene;
			break;
		case 1:
			break;
		case 2:
			ChangeCurrent(0);
			activeScene = menuScene;
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