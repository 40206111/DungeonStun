#include "menuScene.h"
#include "../Game.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///MENU SCENE///

//Load method
void MenuScene::Load()
{
	if (!loaded)
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
		textAmount = text.size();
		previousScene = nullptr;
	}
	text[0].setColor(sf::Color::Yellow);
	TextScene::Load();
	loaded = true;
}

void MenuScene::Update(const double &dt)
{
	TextScene::Update(dt);

	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		switch (current)
		{
		case 0:
			Engine::ChangeMenu(nullptr);
			Engine::ChangeScene(egScene);
			break;
		case 1:
			ChangeCurrent(0);
			Engine::ChangeMenu(settingsScene);
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

void MenuScene::UnLoad() {
	TextScene::UnLoad();
}
