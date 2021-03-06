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

	Cooldown svmCD = Cooldown(3.0f);
	Cooldown maybeGrounded = Cooldown(0.1f);
	std::shared_ptr<PlayerInteraction> playerInt;

	void Jump(const sf::Vector2f &pos);
	void SetSvmState(bool);
	bool isGrounded() const;
public:
	void SetPlayerInteraction(std::shared_ptr<PlayerInteraction> pi) { playerInt = pi; }

	void Update(const double &dt) override;

	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);
	PlayerPhysicsComponent() = delete;
};
