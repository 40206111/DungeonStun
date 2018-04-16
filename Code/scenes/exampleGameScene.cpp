#include "exampleGameScene.h"
#include "LevelSystem.h"
#include "ecm.h"
#include "engine.h"
#include "..\Game.h"
#include "..\Components\cmp_sprite.h"
#include "..\Components\cmp_player_physics.h"
#include "..\Components\cmp_player_interaction.h"
#include "..\Components\cmp_enemy_ai.h"
#include "..\EntityMaker.h"

using namespace std;
using namespace sf;

void ExampleGameScene::Load() {
	GameScene::Load();
	showBehind = true;
	// load level
	float tileSize = 40.0f;
	ls::loadLevelFile("Assets/level_1.txt", tileSize);
	float off = Engine::getWindowSize().y - (ls::getHeight() * tileSize);
	ls::setOffset(Vector2f(0.0f, off));
	// make level physics
	// load player
	player = makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	em::MakeEntity(player, em::PLAYER);
	/*auto s = player->addComponent<ShapeComponent>();
	Vector2f playerSize = Vector2f(20.0f, 30.0f);
	s->setShape<RectangleShape>(playerSize);
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(playerSize);
	auto pPhys = player->addComponent<PlayerPhysicsComponent>(playerSize);
	pPhys->SetPlayerInteraction(player->addComponent<PlayerInteraction>());*/

	auto en = makeEntity();
	enemies.push_back(en);
	en->setPosition({ (float)(Engine::getWindowSize().x - Engine::getWindowSize().x / 10), (float)(Engine::getWindowSize().y / 10) });
	em::MakeEntity(en, em::ENEMY);

	shared_ptr<Entity> enemm = makeEntity();
	enemies.push_back(enemm);
	enemm->setPosition({ (float)(Engine::getWindowSize().x - Engine::getWindowSize().x / 10), (float)(Engine::getWindowSize().y - Engine::getWindowSize().y / 10) });
	em::MakeEntity(enemm, em::ENEMY);
	//auto eai = en->addComponent<EnemyAIComponent>();
	//eai->SetPlayer(player);
	//auto es = en->addComponent<ShapeComponent>();
	//Vector2f enemySize = Vector2f(30.0f, 20.0f);
	//es->setShape<RectangleShape>(enemySize);
	//es->getShape().setFillColor(Color::Blue);
	//es->getShape().setOrigin(enemySize);
}

void ExampleGameScene::UnLoad() {
	player.reset();
	ls::unload();
	GameScene::UnLoad();
}

void ExampleGameScene::Reset() {
	// reset player position
}

void ExampleGameScene::Update(const double &dt) {
	GameScene::Update(dt);
}

void ExampleGameScene::Render() {
	GameScene::Render();
}