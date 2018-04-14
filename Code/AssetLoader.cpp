#include "AssetLoader.h"
#include "system_resources.h"
#include <memory>
using namespace sf;
using namespace std;

std::vector<sf::Sprite> AssetLoader::sprites;

void AssetLoader::LoadAssets()
{
	static shared_ptr<Texture> librarian(Resources::get<sf::Texture>("Librarian.png"));
	static shared_ptr<Texture> chest(Resources::get<sf::Texture>("Chests.png"));
	static shared_ptr<Texture> enemy(Resources::get<sf::Texture>("Enemy.png"));
	static shared_ptr<Texture> enviroment(Resources::get<sf::Texture>("Enviroment.png"));
	static shared_ptr<Texture> health(Resources::get<sf::Texture>("Health.png"));
	static shared_ptr<Texture> trap(Resources::get<sf::Texture>("Traps.png"));

	//idle
	IntRect rect = IntRect(38, 1, 33, 60);
	sprites.push_back(Sprite(*librarian, rect));
	//jump
	rect = IntRect(73, 1, 39, 60);
	sprites.push_back(Sprite(*librarian, rect));
	//Bam
	rect = IntRect(113, 1, 57, 60);
	sprites.push_back(Sprite(*librarian, rect));
	//climb
	rect = IntRect(174, 1, 25, 65);
	sprites.push_back(Sprite(*librarian, rect));
	//Ladder
	rect = IntRect(0, 0, 31, 181);
	sprites.push_back(Sprite(*librarian, rect));
	///CHEST///
	//blue chest
	rect = IntRect(0, 0, 50, 30);
	sprites.push_back(Sprite(*chest, rect));
	//yellow chest
	rect = IntRect(52, 0, 50, 30);
	sprites.push_back(Sprite(*chest, rect));
	///ENEMY///
	//enemy
	rect = IntRect(0, 0, 61, 37);
	sprites.push_back(Sprite(*enemy, rect));
	//enemy dead
	rect = IntRect(72, 0, 67, 37);
	sprites.push_back(Sprite(*enemy, rect));
	///HEALTH///
	//heart
	rect = IntRect(0, 0, 94, 82);
	sprites.push_back(Sprite(*health, rect));
	//half heart
	rect = IntRect(94, 0, 94, 82);
	sprites.push_back(Sprite(*health, rect));
	//heart container
	rect = IntRect(188, 0, 94, 82);
	sprites.push_back(Sprite(*health, rect));
	//heart sheild
	rect = IntRect(282, 0, 114, 107);
	sprites.push_back(Sprite(*health, rect));
	///TRAPS///
	//bounce pad
	rect = IntRect(7, 7, 71, 22);
	sprites.push_back(Sprite(*trap, rect));
	//Long spikes
	rect = IntRect(0, 39, 262, 26);
	sprites.push_back(Sprite(*trap, rect));
	//spike
	rect = IntRect(95, 0, 38, 26);
	sprites.push_back(Sprite(*trap, rect));
	//lever left
	rect = IntRect(154, 0, 45, 25);
	sprites.push_back(Sprite(*trap, rect));
	//lever right
	rect = IntRect(214, 0, 47, 27);
	sprites.push_back(Sprite(*trap, rect));
	///ENVIROMENT///
	//blank bottom right inner corner
	rect = IntRect(404, 0, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank down
	rect = IntRect(606, 0, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank bottom left inner corner
	rect = IntRect(807, 0, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank right
	rect = IntRect(403, 202, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank background
	rect = IntRect(605, 202, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank left
	rect = IntRect(807, 202, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank top right inner corner
	rect = IntRect(403, 404, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank top
	rect = IntRect(606, 404, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank top left inner corner
	rect = IntRect(807, 404, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank top left outer corner
	rect = IntRect(0, 402, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank top right outer corner
	rect = IntRect(202, 402, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank bottom left outer courner
	rect = IntRect(0, 605, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//blank bottom right outer corner
	rect = IntRect(201, 605, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//
	//bottom right inner corner
	rect = IntRect(404, 606, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//down
	rect = IntRect(605, 606, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//bottom left inner corner
	rect = IntRect(807, 606, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//right
	rect = IntRect(403, 807, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//background
	rect = IntRect(606, 807, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//left
	rect = IntRect(807, 807, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//top right inner corner
	rect = IntRect(403, 1008, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//top
	rect = IntRect(605, 1008, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//top right inner corner
	rect = IntRect(807, 1008, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//top left outer corner
	rect = IntRect(0, 807, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//top right outer corner
	rect = IntRect(202, 807, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//bottom left outer corner
	rect = IntRect(0, 1008, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//borrom right outer corner
	rect = IntRect(201, 1008, 200, 200);
	sprites.push_back(Sprite(*enviroment, rect));
	//
	//single platform 100 x 10
	rect = IntRect(9, 317, 100, 10);
	sprites.push_back(Sprite(*enviroment, rect));
	//single platform lef 10x10
	rect = IntRect(116, 317, 10, 10);
	sprites.push_back(Sprite(*enviroment, rect));
	//single platform middle 10x10
	rect = IntRect(132, 317, 10, 10);
	sprites.push_back(Sprite(*enviroment, rect));
	//single platform right
	rect = IntRect(147, 317, 10, 10);
	sprites.push_back(Sprite(*enviroment, rect));
	//double platform 100x20
	rect = IntRect(165, 317, 100, 20);
	sprites.push_back(Sprite(*enviroment, rect));
	//double platform left
	rect = IntRect(272, 317, 20, 20);
	sprites.push_back(Sprite(*enviroment, rect));
	//double platform middle
	rect = IntRect(297, 317, 20, 20);
	sprites.push_back(Sprite(*enviroment, rect));
	//double platform right
	rect = IntRect(321, 317, 20, 20);
	sprites.push_back(Sprite(*enviroment, rect));
	//mechanical platform
	rect = IntRect(143, 348, 50, 10);
	sprites.push_back(Sprite(*enviroment, rect));
	//bricks
	rect = IntRect(8, 344, 117, 46);
	sprites.push_back(Sprite(*enviroment, rect));
#ifdef SOUND
	sounds.push_back(Resources::get<SoundBuffer>("collection.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("collect2.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("damage.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("game over.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("Heal.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("jump.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("jump2.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("jump3.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("taser.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("taser2.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("upgrade.wav"));
	sounds.push_back(Resources::get<SoundBuffer>("woosh.wav"));
#endif // SOUND
}