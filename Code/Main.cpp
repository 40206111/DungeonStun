#include <SFML/Graphics.hpp>
#include "SystemRenderer.h"
#include "Game.h"
#include <iostream>
using namespace sf;
using namespace std;

sf::Font font;
shared_ptr<Scene> homeScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> settingsScene;
shared_ptr<Scene> activeScene;

void Render()
{
	activeScene->Render();
	Renderer::Render();
}

void Load()
{	
	font.loadFromFile("Assets/font/rm_typerighter_old.ttf");
	homeScene.reset(new HomeScene());
	menuScene.reset(new MenuScene());
	settingsScene.reset(new SettingsScene());
	homeScene->Load();
	menuScene->Load();
	settingsScene->Load();
	activeScene = homeScene;
}

void Update()
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	activeScene->Update(dt);
}

int main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Workin' 9 to Die");
	Renderer::Initialise(window);
	Load();

	while (window.isOpen())
	{
		window.clear();
		Update();
		Render();
		window.display();
	}
	return 0;
}