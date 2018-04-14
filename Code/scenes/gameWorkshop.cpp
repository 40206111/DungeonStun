#include "gameWorkshop.h"
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
	static shared_ptr<Texture> librarian(Resources::get<sf::Texture>("Librarian.png"));
	static shared_ptr<Texture> chest(Resources::get<sf::Texture>("Chests.png"));
	static shared_ptr<Texture> enemy(Resources::get<sf::Texture>("Enemy.png"));
	static shared_ptr<Texture> enviroment(Resources::get<sf::Texture>("Enviroment.png"));
	static shared_ptr<Texture> health(Resources::get<sf::Texture>("Health.png"));
	static shared_ptr<Texture> trap(Resources::get<sf::Texture>("Traps.png"));

	///LIBRARIAN///
	//idle
	IntRect rect = IntRect(38, 1, 33, 60);
	//jump
	//IntRect rect = IntRect(73, 1, 39, 60);
	//Bam
	//IntRect rect = IntRect(113, 1, 57, 60);
	//climb
	//IntRect rect = IntRect(174, 1, 25, 65);
	//Ladder
	//IntRect rect = IntRect(0, 0, 31, 181);
	///CHEST///
	//blue chest
	//IntRect rect = IntRect(0, 0, 50, 30);
	//yellow chest
	//IntRect rect = IntRect(52, 0, 50, 30);
	///ENEMY///
	//enemy
	//IntRect rect = IntRect(0, 0, 61, 37);
	//enemy dead
	//IntRect rect = IntRect(72, 0, 67, 37);
	///HEALTH///
	//heart
	//IntRect rect = IntRect(0, 0, 94, 82);
	//half heart
	//IntRect rect = IntRect(94, 0, 94, 82);
	//heart container
	//IntRect rect = IntRect(188, 0, 94, 82);
	//heart sheild
	//IntRect rect = IntRect(282, 0, 114, 107);
	///TRAPS///
	//bounce pad
	//IntRect rect = IntRect(7, 7, 71, 22);
	//Long spikes
	//IntRect rect = IntRect(0, 39, 262, 26);
	//spike
	//IntRect rect = IntRect(95, 0, 38, 26);
	//lever left
	//IntRect rect = IntRect(154, 0, 45, 25);
	//lever right
	//IntRect rect = IntRect(214, 0, 47, 27);
	///ENVIROMENT///
	//blank bottom right inner corner
	//IntRect rect = IntRect(404, 0, 200, 200);
	//blank down
	//IntRect rect = IntRect(606, 0, 200, 200);
	//blank bottom left inner corner
	//IntRect rect = IntRect(807, 0, 200, 200);
	//blank right
	//IntRect rect = IntRect(403, 202, 200, 200);
	//blank background
	//IntRect rect = IntRect(605, 202, 200, 200);
	//blank left
	//IntRect rect = IntRect(807, 202, 200, 200);
	//blank top right inner corner
	//IntRect rect = IntRect(403, 404, 200, 200);
	//blank top
	//IntRect rect = IntRect(606, 404, 200, 200);
	//blank top left inner corner
	//IntRect rect = IntRect(807, 404, 200, 200);
	//blank top left outer corner
	//IntRect rect = IntRect(0, 402, 200, 200);
	//blank top right outer corner
	//IntRect rect = IntRect(202, 402, 200, 200);
	//blank bottom left outer courner
	//IntRect rect = IntRect(0, 605, 200, 200);
	//blank bottom right outer corner
	//IntRect rect = IntRect(201, 605, 200, 200);
	//
	//bottom right inner corner
	//IntRect rect = IntRect(404, 606, 200, 200);
	//bottom
	//IntRect rect = IntRect(605, 606, 200, 200);
	//bottom left inner corner
	//IntRect rect = IntRect(807, 606, 200, 200);
	//right
	//IntRect rect = IntRect(403, 807, 200, 200);
	//background
	//IntRect rect = IntRect(606, 807, 200, 200);
	//left
	//IntRect rect = IntRect(807, 807, 200, 200);
	//top right inner corner
	//IntRect rect = IntRect(403, 1008, 200, 200);
	//top
	//IntRect rect = IntRect(605, 1008, 200, 200);
	//top right inner corner
	//IntRect rect = IntRect(807, 1008, 200, 200);
	//top left outer corner
	//IntRect rect = IntRect(0, 807, 200, 200);
	//top right outer corner
	//IntRect rect = IntRect(202, 807, 200, 200);
	//bottom left outer corner
	//IntRect rect = IntRect(0, 1008, 200, 200);
	//borrom right outer corner
	//IntRect rect = IntRect(201, 1008, 200, 200);
	//
	//single platform 100 x 10
	//IntRect rect = IntRect(9, 317, 100, 10);
	//single platform lef 10x10
	//IntRect rect = IntRect(116, 317, 10, 10);
	//single platform middle 10x10
	//IntRect rect = IntRect(132, 317, 10, 10);
	//single platform right
	//IntRect rect = IntRect(147, 317, 10, 10);
	//double platform 100x20
	//IntRect rect = IntRect(165, 317, 100, 20);
	//double platform left
	//IntRect rect = IntRect(272, 317, 20, 20);
	//double platform middle
	//IntRect rect = IntRect(297, 317, 20, 20);
	//double platform right
	//IntRect rect = IntRect(321, 317, 20, 20);
	//mechanical platform
	//IntRect rect = IntRect(143, 348, 50, 10);
	//bricks
	//IntRect rect = IntRect(8, 344, 117, 46);

	Sprite lib = Sprite(*librarian, rect);
	Sprite chst = Sprite(*chest, rect);
	Sprite enem = Sprite(*enemy, rect);
	Sprite heart = Sprite(*health, rect);
	Sprite trp = Sprite(*trap, rect);
	Sprite enviro = Sprite(*enviroment, rect);

	Vector2f playerSize = Vector2f(20.0f, 30.0f);
	player = makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	auto s = player->addComponent<SpriteComponent>();
	s->setSprite(lib);
	//s->setShape<RectangleShape>(playerSize);
	//s->getShape().setFillColor(Color::Blue);
	//s->getShape().setOrigin(playerSize);
	//player->addComponent<PlayerPhysicsComponent>(playerSize);
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