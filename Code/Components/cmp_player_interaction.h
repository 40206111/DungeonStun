#pragma once
#include "ecm.h"
#include "..\Cooldown.h"

class PlayerInteraction : public Component {
private:
	sf::Vector2f aimDirection;
	bool inSVM = false;
	bool blocking = false;
	bool isGrounded = false;
	int antiMoves = 0;
	int antiFire = 0;
	bool isAlive = false;
	sf::Vector2f playerSize;

	std::vector<Cooldown*> cooldowns;
	Cooldown blockCd = Cooldown(4.0f);
	Cooldown blockDuration = Cooldown(0.5f);
	Cooldown fireCD = Cooldown(1.0f);
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
	bool InSvm() { return inSVM; }
	bool IsBlocking() { return blocking; }
	void SetAlive(bool);
	void SetPlayerSize(sf::Vector2f ps) { playerSize = ps; }
	sf::Vector2f GetPlayerSize() { return playerSize; }

	void Update(const double &dt) override;
	void render() override {}
};