#include "EntityMaker.h"
#include "Components\cmp_enemy_ai.h"
#include "Components\cmp_sprite.h"
#include "Components\cmp_player_physics.h"
#include "Components\cmp_player_interaction.h"

using namespace std;
using namespace sf;

weak_ptr<Entity> EntityMaker::player;

void EntityMaker::MakeEnemy(std::shared_ptr<Entity> e) {
	shared_ptr<EnemyAIComponent> ai = e->addComponent<EnemyAIComponent>();
	ai->SetPlayer(player);
	shared_ptr<ShapeComponent> s = e->addComponent<ShapeComponent>();
	Vector2f enemySize = Vector2f(30.0f, 20.0f);
	s->setShape<RectangleShape>(enemySize);
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(enemySize/2.0f);
	s->SetRenderLayer(Renderer::Layer::ENTITIES);
}

void EntityMaker::MakePlayer(std::shared_ptr<Entity> e)
{
	player = e;
	shared_ptr<ShapeComponent> s = e->addComponent<ShapeComponent>();
	Vector2f playerSize = Vector2f(20.0f, 30.0f);
	s->setShape<RectangleShape>(playerSize);
	s->getShape().setFillColor(Color::Blue);
	s->getShape().setOrigin(playerSize/2.0f);
	s->SetRenderLayer(Renderer::Layer::ENTITIES);
	shared_ptr<PlayerPhysicsComponent> pPhys = e->addComponent<PlayerPhysicsComponent>(playerSize);
	pPhys->SetPlayerInteraction(e->addComponent<PlayerInteraction>());
}

void EntityMaker::MakeProjectile(std::shared_ptr<Entity> e)
{
	shared_ptr<ShapeComponent> s = e->addComponent<ShapeComponent>();
	float projSize = 10.0f;
	s->setShape<CircleShape>(projSize);
	s->getShape().setFillColor(Color::Red);
	s->getShape().setOrigin({ projSize / 2.0f, projSize / 2.0f });
	s->SetRenderLayer(Renderer::Layer::PROJECTILES);
}

void EntityMaker::MakeWall(std::shared_ptr<Entity> e)
{
}

void EntityMaker::MakeChest(std::shared_ptr<Entity> e)
{
}

void EntityMaker::MakePlatform(std::shared_ptr<Entity> e)
{
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
	case EntityMaker::PROJECTILE:
		MakeProjectile(e);
		break;
	case EntityMaker::WALL:
		MakeWall(e);
		break;
	case EntityMaker::CHEST:
		MakeChest(e);
		break;
	case EntityMaker::PLATFORM:
		MakePlatform(e);
		break;
	default:
		break;
	}
}