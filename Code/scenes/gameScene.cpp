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
	// load level
	float tileSize = 40.0f;
	ls::loadLevelFile("./Assets/level_1.txt", tileSize);
	float off = Engine::getWindowSize().y - (ls::getHeight() * tileSize);
	ls::setOffset(Vector2f(0.0f, off));
	// make level physics
	// load player
	player = makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	auto s = player->addComponent<ShapeComponent>();
	Vector2f playerSize = Vector2f(20.0f, 30.0f);
	s->setShape<RectangleShape>(playerSize);
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(playerSize);
	player->addComponent<PlayerPhysicsComponent>(playerSize);
	ents.list.push_back(player);
}

void GameScene::UnLoad() {
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void GameScene::Reset() {
	// reset player position
}

void GameScene::Update(const double &dt) {
	// run EM update
	Scene::Update(dt);
}

void GameScene::Render() {
	// Run EM render
	Scene::Render();
}