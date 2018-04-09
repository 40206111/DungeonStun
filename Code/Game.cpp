#include "Game.h"

///MENU SCENE///

void MenuScene::Load()
{
	if (!homescreen.loadFromFile("Assets/imgs/9 to die home.png")) {}
	background = sf::Sprite(homescreen);
	font.loadFromFile("Assets/font/rm_typerighter_old.ttf");
	text = sf::Text();
	text.setString("Press Any Button To Continue");
}

void MenuScene::Update(double dt)
{

}

void MenuScene::Render()
{

}

///SETTINGS SCENE///

void SettingsScene::Load()
{

}

void SettingsScene::Update(double dt)
{

}

void SettingsScene::Render()
{

}