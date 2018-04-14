#pragma once
#include "ecm.h"

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

	void Update(const double &dt) override;
	void render() override {}
};