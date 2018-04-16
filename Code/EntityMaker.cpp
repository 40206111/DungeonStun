#include "EntityMaker.h"
#include "Components\cmp_enemy_ai.h"
#include "Components\cmp_sprite.h"
#include "Components\cmp_player_physics.h"
#include "Components\cmp_player_interaction.h"

using namespace std;
using namespace sf;

weak_ptr<Entity> EntityMaker::player;

void EntityMaker::MakeEnemy(std::shared_ptr<Entity> e) {
	auto eai = e->addComponent<EnemyAIComponent>();
	eai->SetPlayer(player);
	auto es = e->addComponent<ShapeComponent>();
	Vector2f enemySize = Vector2f(30.0f, 20.0f);
	es->setShape<RectangleShape>(enemySize);
	es->getShape().setFillColor(Color::Blue);
	es->getShape().setOrigin(enemySize);
}

void EntityMaker::MakePlayer(std::shared_ptr<Entity> e)
{
	player = e;
	auto s = e->addComponent<ShapeComponent>();
	Vector2f playerSize = Vector2f(20.0f, 30.0f);
	s->setShape<RectangleShape>(playerSize);
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(playerSize);
	auto pPhys = e->addComponent<PlayerPhysicsComponent>(playerSize);
	pPhys->SetPlayerInteraction(e->addComponent<PlayerInteraction>());
}

void EntityMaker::MakeEntity(shared_ptr<Entity> e, EntityMaker::Prefab p) {
	switch (p)
	{
	case EntityMaker::ENEMY:
		MakeEnemy(e);
		break;
	case EntityMaker::PLAYER:
		MakePlayer(e);
		break;
	case EntityMaker::WALL:
		break;
	case EntityMaker::CHEST:
		break;
	case EntityMaker::PLATFORM:
		break;
	default:
		break;
	}
}