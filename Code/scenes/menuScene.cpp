#include "menuScene.h"
#include "../Game.h"
#include "../SystemRenderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

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
	text[0].setColor(sf::Color::Yellow);
	text[1].setString("Settings");
	text[2].setString("Exit");
	textAmount = text.size();
	previousScene = homeScene;
}

void MenuScene::Update(double dt)
{
	TextScene::Update(dt);

	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		switch (current)
		{
		case 0:
			break;
		case 1:
			ChangeCurrent(0);
			activeScene = settingsScene;
			break;
		case 2:
			Renderer::Shutdown();
			Renderer::GetWindow().close();
			break;
		default:
			break;
		}
	}
}

//Render Method
void MenuScene::Render()
{
	TextScene::Render();
}
