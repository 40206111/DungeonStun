#pragma once
#include "scenes/Scene.h"
#include "InputManager.h"
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
