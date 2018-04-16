#include "gameScene.h"
#include "LevelSystem.h"
#include "ecm.h"
#include "engine.h"
#include "system_resources.h"
#include "system_renderer.h"
#include "..\Game.h"
#include "..\Components\cmp_sprite.h"
#include "..\Components\cmp_player_physics.h"

using namespace std;
using namespace sf;

void GameScene::Load() {
	screen = makeEntity();
	screen->setPosition(Vector2f(0, 0));
	screen->setVisible(false);
	auto s = screen->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(Renderer::GetWindow().getSize()));
	s->getShape().setFillColor(Color(0, 0, 0, 200));
	s->SetRenderLayer(Renderer::Layer::FOREGROUND);
}

void GameScene::UnLoad() {
	Scene::UnLoad();
}

void GameScene::Reset() {
	// reset player position
}

std::shared_ptr<Entity> GameScene::SpawnEntity(em::Prefab p)
{
	shared_ptr<Entity> e = makeEntity();
	switch (p)
	{
	case EntityMaker::ENEMY:
		enemies.push_back(e);
		break;
	case EntityMaker::PROJECTILE:
		projectiles.push_back(e);
		break;
	default:
		break;
	}
	em::MakeEntity(e, p);
	return e;
}

void GameScene::Update(const double &dt) {
	// run EM update
	Scene::Update(dt);
}

void GameScene::Render() {
	if (!Engine::ShowingMenu()) {
		screen->setVisible(false);
		Scene::Render();
		ls::render();
	}
	else if (showBehind) {
		screen->setVisible(true);
		Scene::Render();
		ls::render();
	}
}

void GameScene::ReSize()
{
	ls::ReSize();
}
