#include "cmp_projectile_physics.h"

using namespace std;
using namespace sf;

ProjectilePhysics::ProjectilePhysics(Entity * p, const sf::Vector2f & size)
	: PhysicsComponent(p, true, size)
{
	direction = { -1.0f, 0.0f };
}

void ProjectilePhysics::Update(const double & dt)
{
	Vector2f mov = (float)dt * direction * speed;
	impulse(mov);

	Vector2f v = getVelocity();
	if (v != Vector2f(0, 0)) {
		float len = length(v);
		if (len > maxSpeed) {
			v = maxSpeed * v / len;
			setVelocity(v);
		}
	}

}
