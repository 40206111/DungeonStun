#pragma once
#include "engine.h"
#include "InputManager.h"
#include "scenes\gameScene.h"
#include <memory>

extern sf::Font font;
extern std::shared_ptr<InputManager> player1;
extern std::shared_ptr<Scene> homeScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> settingsScene;
extern std::shared_ptr<Scene> graphicsScene;
extern std::shared_ptr<Scene> controlsScene;
extern std::shared_ptr<Scene> activeScene;
extern GameScene gameScene;
