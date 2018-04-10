#pragma once
#include "Scene.h"
#include <memory>

//gamesize
static uint16_t gameWidth = 1280;
static uint16_t gameHeight = 720;

extern sf::Font font;
extern std::shared_ptr<InputManager> player1;
extern std::shared_ptr<Scene> homeScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> settingsScene;
extern std::shared_ptr<Scene> graphicsScene;
extern std::shared_ptr<Scene> activeScene;

class HomeScene : public Scene
{
private:
	sf::Texture homescreen;
	sf::Sprite background;
	sf::Text text;
public:
	HomeScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class MenuScene : public Scene
{
private:
	std::vector<sf::Text> text;
	//Menu buttons
	std::bitset<3> menu;
	//currently selected
	int current = 0;

public:
	MenuScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class SettingsScene : public Scene
{
private:
	std::vector<sf::Text> text;
	//Menu buttons
	std::bitset<3> menu;
	//currently selected
	int current = 0;
public:
	SettingsScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class GraphicsScene : public Scene
{
private:
	std::vector<sf::Text> text;
	//Menu buttons
	std::bitset<3> menu;
	//currently selected
	int current = 0;
public:
	GraphicsScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};