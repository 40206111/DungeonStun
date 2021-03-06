#pragma once
#include "engine.h"
#include "InputManager.h"
#include "scenes\exampleGameScene.h"
#include <memory>
#include "scenes\gameScene.h"

extern sf::Font font;
extern std::shared_ptr<InputManager> player1;
extern std::shared_ptr<Scene> homeScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> settingsScene;
extern std::shared_ptr<Scene> graphicsScene;
extern std::shared_ptr<Scene> controlsScene;
extern std::shared_ptr<Scene> gameOverScene;
extern std::shared_ptr<Scene> victoryScene;
extern std::shared_ptr<Scene> disconnected;
extern std::shared_ptr<Scene> egScene;
