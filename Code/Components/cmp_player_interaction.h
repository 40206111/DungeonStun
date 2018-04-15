#pragma once
#include "ecm.h"
#include "..\Cooldown.h"

class PlayerInteraction : public Component {
private:
	sf::Vector2f aimDirection;
	bool inSVM = false;
	bool isGrounded = false;
	int antiMoves = 0;
	int antiFire = 0;

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

	void Update(const double &dt) override;
	void render() override {}
};