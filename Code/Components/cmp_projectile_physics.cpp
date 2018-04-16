#include "cmp_projectile_physics.h"

using namespace std;
using namespace sf;

ProjectilePhysics::ProjectilePhysics(Entity * p, const sf::Vector2f & size)
	: PhysicsComponent(p, true, size)
{
	direction = { -1.0f, 0.0f };
	_body->SetBullet(true);
}

void ProjectilePhysics::Update(const double & dt)
{
	// Check for death
	death.Update(dt);
	if (death.Ready()) {
		is_fordeletion();
		return;
	}

	// Apply impulse
	Vector2f mov = (float)dt * direction * speed;
	impulse(mov);

	// Cap velocity
	Vector2f v = getVelocity();
	if (v != Vector2f(0, 0)) {
		float len = length(v);
		if (len > maxSpeed) {
			v = maxSpeed * v / len;
			setVelocity(v);
		}
	}
	// Update parent pos/rot
	PhysicsComponent::Update(dt);
}
