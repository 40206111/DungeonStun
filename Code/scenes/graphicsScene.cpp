#include "graphicsScene.h"
#include "../Game.h"
#include "../SystemRenderer.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

///GRAPHICS SCENE///

//Load method
void GraphicsScene::Load()
{
	//Load Text
	for (int i = 0; i < 4; i++)
	{
		text.push_back(sf::Text());
		text[i].setFont(font);
	}
	text[0].setString("Resolution: " + to_string(gameWidth) + "x" + to_string(gameHeight));
	text[0].setColor(sf::Color::Yellow);
	text[1].setString("Apply");

	if (Renderer::GetFullscreen())
	{
		text[2].setString("Fullscreen: true");
	}
	else
	{
		text[2].setString("Fullscreen: false");
	}
	text[3].setString("Back");
	textAmount = text.size();
	previousScene = settingsScene;
	fullscreen = Renderer::GetFullscreen();
}

//Update method
void GraphicsScene::Update(double dt)
{
	TextScene::Update(dt);
	//Fullscreen window
	if (fullscreen != Renderer::GetFullscreen())
	{
		fullscreen = Renderer::GetFullscreen();
		if (fullscreen)
		{
			text[2].setString("Fullscreen: true");
		}
		else
		{
			text[2].setString("Fullscreen: false");
		}
	}
	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		switch (current)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			Renderer::ToggleFullscreen();
			break;
		case 3:
			ChangeCurrent(0);
			activeScene = previousScene;
			break;
		default:
			break;
		}
	}
}

//render Method
void GraphicsScene::Render()
{
	TextScene::Render();
}
