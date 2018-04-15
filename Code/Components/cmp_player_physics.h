#pragma once

#include "cmp_physics.h"
#include "../Cooldown.h"

class PlayerInteraction;

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 size;
	sf::Vector2f maxVelocity;
	bool grounded;
	float groundspeed;

	bool inSVM = false;
	Cooldown svmCD = Cooldown(3.0);
	int antiMoves = 0;
	std::shared_ptr<PlayerInteraction> playerInt;

	void SetSvmState(bool);
	bool isGrounded() const;
public:
	void SetPlayerInteraction(std::shared_ptr<PlayerInteraction> pi) { playerInt = pi; }

	void Update(const double &dt) override;

	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);
	PlayerPhysicsComponent() = delete;
};
