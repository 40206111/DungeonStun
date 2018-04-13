#include <SFML/Graphics.hpp>
#include "system_renderer.h"
#include "Game.h"
#include "scenes\homeScene.h"
#include "scenes\menuScene.h"
#include "scenes\settingsScene.h"
#include "scenes\graphicsScene.h"
#include "scenes\controlsScene.h"
#include "scenes\gameScene.h"
#include <iostream>
#include "Serializer.h"
using namespace sf;
using namespace std;

sf::Font font;
shared_ptr<InputManager> player1;
shared_ptr<Scene> homeScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> settingsScene;
shared_ptr<Scene> graphicsScene;
shared_ptr<Scene> activeScene;
shared_ptr<Scene> controlsScene;
GameScene gameScene;

void Render()
{
	activeScene->Render();
	Renderer::Render();
}

void Load()
{	
	font.loadFromFile("Assets/font/rm_typerighter_old.ttf");
	player1.reset(new InputManager());
	Serializer::DeSerialize("Assets/save/player1.txt", player1);
	homeScene.reset(new HomeScene());
	menuScene.reset(new MenuScene());
	settingsScene.reset(new SettingsScene());
	graphicsScene.reset(new GraphicsScene());
	controlsScene.reset(new ControlsScene());
	homeScene->Load();
	menuScene->Load();
	settingsScene->Load();
	graphicsScene->Load();
	controlsScene->Load();
	activeScene = homeScene;
}

void Update()
{
	static Clock clock;
	float dt = clock.restart().asSeconds();
	if (activeScene != homeScene) {
		player1->Update(dt);
	}
	activeScene->Update(dt);
}

int main()
{
	RenderWindow window(VideoMode(Renderer::resolutions[Renderer::currentRes].first, Renderer::resolutions[Renderer::currentRes].second), "Workin' 9 to Die");
	Renderer::Initialise(window);
	Load();

	while (window.isOpen())
	{
		window.clear();
		Update();
		Render();
		window.display();
	}
	Engine::Start(Renderer::resolutions[Renderer::currentRes].first, Renderer::resolutions[Renderer::currentRes].second, "Dungeon Stun", &gameScene);
	return 0;
}