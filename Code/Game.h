#pragma once
#include "Scene.h"
#include <memory>

extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> settingsScene;
extern std::shared_ptr<Scene> activeScene;

class MenuScene : public Scene
{
private:
	sf::Text text;
	sf::Texture homescreen;
	sf::Sprite background;
	sf::Font font;
public:
	MenuScene();
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};

class SettingsScene : public Scene
{
private:
	std::vector<sf::Text> text;
public:
	SettingsScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};