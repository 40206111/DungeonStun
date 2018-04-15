#include "gameWorkshop.h"
#include "../AssetLoader.h"
#include "LevelSystem.h"
#include "ecm.h"
#include "engine.h"
#include "system_resources.h"
#include "..\Game.h"
#include "..\Components\cmp_sprite.h"
#include "..\Components\cmp_player_physics.h"

using namespace std;
using namespace sf;

void GameWorkshop::Load() {
	// load level
	float tileSize = 40.0f;
	ls::loadLevelFile("Assets/level_1.txt", tileSize);
	float off = Engine::getWindowSize().y - (ls::getHeight() * tileSize);
	ls::setOffset(Vector2f(0.0f, off));
	// make level physics
	// load player

	///LIBRARIAN///
	Vector2f playerSize = Vector2f(20.0f, 30.0f);
	player = makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	auto s = player->addComponent<SpriteComponent>();
	s->setSprite(AssetLoader::sprites[AssetLoader::LIB_IDLE]);
	ents.list.push_back(player);
}

void GameWorkshop::UnLoad() {
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void GameWorkshop::Reset() {
	// reset player position
}

void GameWorkshop::Update(const double &dt) {
	// run EM update
	Scene::Update(dt);
}

void GameWorkshop::Render() {
	// Run EM render
	Scene::Render();
}