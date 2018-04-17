#pragma once
#include "ecm.h"
#include "..\Cooldown.h"
#include "cmp_sprite.h"
#include <SFML\Audio.hpp>

class SpriteComponent;

class PlayerInteraction : public Component {
private:
	enum state{WALK, JUMP, CLIMB, SHOOT};
	state currState = WALK;
	state prevState;

	sf::Vector2f aimDirection;
	bool inSVM = false;
	bool blocking = false;
	bool isGrounded = true;
	int antiMoves = 0;
	int antiFire = 0;
	bool isAlive = false;
	sf::Vector2f playerSize;

	sf::Sound sound;

	std::weak_ptr<SpriteComponent> playerSprite;
	sf::Sprite playerWalk;
	sf::Sprite playerJump;
	sf::Sprite playerClimb;
	sf::Sprite playerShoot;

	std::vector<Cooldown*> cooldowns;
	Cooldown blockCd = Cooldown(4.0f);
	Cooldown blockDuration = Cooldown(0.5f);
	Cooldown fireCD = Cooldown(1.0f);
	Cooldown shootAnim = Cooldown(0.3f);
	Cooldown activeCD = Cooldown(15.0f);


public:
	PlayerInteraction() = delete;
	explicit PlayerInteraction(Entity*);
	~PlayerInteraction() = default;

	bool CanMove() { return antiMoves == 0; }
	bool CanFire() { return antiFire == 0; }

	void PreventMoving() { antiMoves++; }
	void AllowMoving() { antiMoves--; }
	void PreventFiring() { antiFire++; }
	void AllowFiring() { antiFire--; }
	void SetSvmState(bool);
	void SetGroundedState(bool b) { isGrounded = b; }
	bool InSvm() { return inSVM; }
	bool IsBlocking() { return blocking; }
	void SetAlive(bool);
	void SetPlayerSize(sf::Vector2f ps) { playerSize = ps; }
	sf::Vector2f GetPlayerSize() { return playerSize; }
	void SetPlayerSprite(std::weak_ptr<SpriteComponent> sc);
	void SetWalkingSprite(sf::Sprite sc) { playerWalk = sc; }
	void SetJumpingSprite(sf::Sprite sc) { playerJump = sc; }
	void SetClimbingSprite(sf::Sprite sc) { playerClimb = sc; }
	void SetShootingSprite(sf::Sprite sc) { playerShoot = sc; }

	void Update(const double &dt) override;
	void render() override {}
};