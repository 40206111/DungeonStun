#pragma once

#include "cmp_physics.h"
#include "..\Cooldown.h"

class ProjectilePhysics : public PhysicsComponent {
protected:
	sf::Vector2f direction;
	float speed;
	float maxSpeed;
	Cooldown death = Cooldown(1.0);
public:
	ProjectilePhysics() = delete;
	explicit ProjectilePhysics(Entity* p, const float size);
	~ProjectilePhysics() { PhysicsComponent::~PhysicsComponent(); }

	void Update(const double &dt) override;
	void render()override {}

	void SetDirection(sf::Vector2f);
};