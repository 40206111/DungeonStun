#pragma once

#define SOUND

#include <SFML/Graphics.hpp>
#include <memory>
#ifdef SOUND
#include <SFML/Audio/Sound.hpp>

#endif // SOUND

class AssetLoader
{
public:
	AssetLoader() = default;
	~AssetLoader() = default;

	//enum describing the images in the vector
	enum IMAGES {
		LIB_IDLE, LIB_JUMP, LIB_BAM, LIB_CLIMB, LIB_LADDER,
		BLUE_CHEST, YELLOW_CHEST,
		ENEMY, ENEMY_KO,
		HEART, HALF_HEART, HEART_CONTAINTER, HEART_SHEILD,
		BOUNCE_PAD, LONG_SPIKES, SPIKE, LEVER_LEFT, lEVER_RIGHT,
		BBRIC, BD, BBLIC, BR, BLANK_BACKGROUND, BL, BTRIC, BT, BTLIC, BTLOC, BTROC, BBLOC, BBROC,
		BRIC, D, BLIC, R, BACKGROUND, L, TRIC, T, TLIC, TLOC, TROC, BLOC, BROC,
		SINGLE_P_LONG, SINGLE_P_LEFT, SINGLE_P_MIDDLE, SINGLE_P_RIGHT,
		DOUBLE_P_LONG, DOUBLE_P_lEFT, DOUBLE_P_MIDDLE, DOUBLE_P_RIGHT,
		MECHANICAL_PLATFORM, BRICKS
	};

	//enum describing the sound effects in the sounds vector
	enum sfx {
		COLLECT,
		DAMAGE, GAME_OVER, HEAL,
		JUMP, JUMP2, JUMP3, 
		TASER,
		UPGRADE,
	};
	//vector of sprites
	static std::vector<sf::Sprite> sprites;

	//sounds
#ifdef SOUND
	static std::vector<std::shared_ptr<sf::SoundBuffer>> sounds;
#endif // SOUND

	//load assets method
	static void LoadAssets();
};