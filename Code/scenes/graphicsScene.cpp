#include "graphicsScene.h"
#include "../Game.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

///GRAPHICS SCENE///

//Load method
void GraphicsScene::Load()
{
	if (!loaded)
	{
		//Load Text
		for (int i = 0; i < 4; i++)
		{
			text.push_back(sf::Text());
			text[i].setFont(font);
		}
		textAmount = text.size();
		previousScene = settingsScene;
		loaded = true;
	}
	ReSize();
	fullscreen = Renderer::GetFullscreen();
	shownRes = Renderer::currentRes;
	text[0].setString("Resolution: " + to_string(Renderer::resolutions[Renderer::currentRes].first) + "x" + to_string(Renderer::resolutions[Renderer::currentRes].second));
	text[0].setColor(sf::Color::Yellow);

	if (Renderer::GetFullscreen())
	{
		text[1].setString("Fullscreen: true");
	}
	else
	{
		text[1].setString("Fullscreen: false");
	}
	text[2].setString("Back");
}

//Update method
void GraphicsScene::Update(const double &dt)
{
	TextScene::Update(dt);
	//Fullscreen window
	if (fullscreen != Renderer::GetFullscreen())
	{
		fullscreen = Renderer::GetFullscreen();
		if (fullscreen)
		{
			text[1].setString("Fullscreen: true");
		}
		else
		{
			text[1].setString("Fullscreen: false");
		}

	}
	//Right
	if (player1->GetButtonDown(player1->MENURIGHT) || player1->GetAnaDown(player1->R))
	{
		if (current == 0)
		{
			shownRes += 1;
			if (shownRes >= Renderer::resolutions.size())
			{
				shownRes = 0;
			}
			text[0].setString("Resolution: " + to_string(Renderer::resolutions[shownRes].first) + "x" + to_string(Renderer::resolutions[shownRes].second));
		}
	}
	//Left
	if (player1->GetButtonDown(player1->MENULEFT) || player1->GetAnaDown(player1->L))
	{
		if (current == 0)
		{
			shownRes -= 1;
			if (shownRes <= 0)
			{
				shownRes = Renderer::resolutions.size() - 1;
			}
			text[0].setString("Resolution: " + to_string(Renderer::resolutions[shownRes].first) + "x" + to_string(Renderer::resolutions[shownRes].second));
		}
	}
	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		switch (current)
		{
		case 0:
			Renderer::setResolution(shownRes);
			Engine::Resize();
			break;
		case 1:
			Renderer::ToggleFullscreen();
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
void GraphicsScene::Render()
{
	TextScene::Render();
}

void GraphicsScene::UnLoad() {
	TextScene::UnLoad();
}


