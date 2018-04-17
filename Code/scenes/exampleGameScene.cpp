#include "exampleGameScene.h"
#include "LevelSystem.h"
#include "ecm.h"
#include "engine.h"
#include "system_physics.h"
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
	ls::loadLevelFile("Assets/level.txt", tileSize);
	float off = Engine::getWindowSize().y - (ls::getHeight() * tileSize);
	ls::setOffset(Vector2f(0.0f, off));
	ls::ReSize();
	// make level physics
	// load player
	player = makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]) + Vector2f(ls::getTileSize()/2.0f, ls::getTileSize() / 2.0f));
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
	//auto eai = en->addComponent<EnemyAIComponent>();
	//eai->SetPlayer(player);
	//auto es = en->addComponent<ShapeComponent>();
	//Vector2f enemySize = Vector2f(30.0f, 20.0f);
	//es->setShape<RectangleShape>(enemySize);
	//es->getShape().setFillColor(Color::Blue);
	//es->getShape().setOrigin(enemySize);

	shared_ptr<Entity> enemm = makeEntity();
	enemies.push_back(enemm);
	enemm->setPosition({ (float)(Engine::getWindowSize().x - Engine::getWindowSize().x / 10), (float)(Engine::getWindowSize().y - Engine::getWindowSize().y / 10) });
	em::MakeEntity(enemm, em::ENEMY);

	shared_ptr<Entity> proj = makeEntity();
	projectiles.push_back(proj);
	proj->setPosition({ (float)(Engine::getWindowSize().x / 2.0f), (float)(Engine::getWindowSize().y / 2.0f) });
	em::MakeEntity(proj, em::PROJECTILE);

	shared_ptr<Entity> world = makeEntity();
	/// Start world colliders
	vector<Vector2f> tileLocs = ls::findTilesV2f(ls::WALL);
	vector<Vector2f> fillLocs = ls::findTilesV2f(ls::FILL);
	for (Vector2f f : fillLocs) {
		tileLocs.push_back(move(f));
	}
	fillLocs.clear();
	b2Body* bod;
	b2BodyDef BodyDef;
	// Is Dynamic(moving), or static(Stationary)
	BodyDef.type = b2_staticBody;
	BodyDef.position = b2Vec2(0, 0);
	// Create the body
	bod = Physics::GetWorld()->CreateBody(&BodyDef);
	bod->SetActive(true);
	float size = Physics::sv2_to_bv2({ ls::getTileSize(), ls::getTileSize() }).x;
	b2Vec2 toMid = b2Vec2(size/2.0f, -size/2.0f);

	for (Vector2f vec : tileLocs) {
		// Create the fixture shape
		b2PolygonShape Shape;
		// SetAsBox box takes HALF-Widths!
		b2Vec2 tPos = Physics::sv2_to_bv2(Physics::invert_height(vec));
		Shape.SetAsBox(size * 0.5f, size * 0.5f, tPos + toMid, 0);
		b2FixtureDef FixtureDef;
		// Fixture properties
		FixtureDef.density = 0.0f;
		FixtureDef.friction = 0.8f;
		FixtureDef.restitution = 0.0f;
		FixtureDef.shape = &Shape;
		// Add to body
		bod->CreateFixture(&FixtureDef);
	}
	/// End world colliders
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
	if (ls::getTileAt(player->getPosition()) == ls::END) {
		Engine::ChangeScene(victoryScene);
	}
	Event event;
	while (Renderer::GetWindow().pollEvent(event))
	{
	}
}

void ExampleGameScene::Render() {
	GameScene::Render();
}