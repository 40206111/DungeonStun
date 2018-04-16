#pragma once

#include "cmp_physics.h"

class ProjectilePhysics : public PhysicsComponent {
protected:
	sf::Vector2f direction;
	float speed;
	float maxSpeed;
public:
	ProjectilePhysics() = delete;
	explicit ProjectilePhysics(Entity* p, const sf::Vector2f& size);
	~ProjectilePhysics() = default;

	void Update(const double &dt) override;
	void render()override {}
};