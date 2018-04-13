#include "gameScene.h"
#include "LevelSystem.h"
#include "ecm.h"
#include "engine.h"
#include "..\Game.h"
#include "..\Components\cmp_sprite.h"
#include "..\Components\cmp_player_physics.h"

using namespace std;
using namespace sf;

void GameScene::Load() {
}

void GameScene::UnLoad() {
	Scene::UnLoad();
}

void GameScene::Reset() {
	// reset player position
}

void GameScene::ShowMenu() {
	menuUp = true;
	activeMenu = menuScene;
}

void GameScene::HideMenu() {
	menuUp = false;
	activeMenu = menuScene;
}

void GameScene::Update(const double &dt) {
	if (menuUp) {
		// menu update
		if (player1->GetButtonDown(InputManager::MENU)) {
			HideMenu();
		}
		else {
			menuScene->Update(dt);
		}
	}
	else {
		// run EM update
		Scene::Update(dt);
		if (player1->GetButtonDown(InputManager::MENU)) {
			ShowMenu();
		}
	}
}

void GameScene::Render() {
	if (!menuUp || showBehind) {
		// render game if not paused, or boolean set
		Scene::Render();
	}
	if (menuUp) {
		// render menu on top
		menuScene->Render();
	}
}