#include <SFML/Graphics.hpp>
#include "system_renderer.h"
#include "Game.h"
#include "scenes\homeScene.h"
#include "scenes\menuScene.h"
#include "scenes\settingsScene.h"
#include "scenes\graphicsScene.h"
#include "scenes\controlsScene.h"
#include "scenes\gameScene.h"
#include "scenes\exampleGameScene.h"
#include "scenes\Disconnected.h"
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
shared_ptr<Scene> controlsScene;
shared_ptr<Scene> disconnected;
shared_ptr<Scene> egScene;

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
	disconnected.reset(new Disconnected());
	egScene.reset(new ExampleGameScene());
}

int main()
{
	Load();
	Engine::Start(Renderer::resolutions[Renderer::currentRes].first, Renderer::resolutions[Renderer::currentRes].second, "Working 9 to Die", homeScene);
	return 0;
}