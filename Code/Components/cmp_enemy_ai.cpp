#include "cmp_enemy_ai.h"

using namespace std;
using namespace sf;

void EnemyAIComponent::Update(const double &dt) {
	for (Cooldown* cd : cooldowns) {
		cd->Update(dt);
	}
	if (!moveTime.Ready()) {
		auto mov = _direction * (float)(dt * _speed);
		/*if (!validMove(_parent->getPosition() + mov)) {
			_direction *= -1.f;
		}*/

		move(mov);
	}
	else {
		if (!idling) {
			idleTime.Reset();
			idling = true;
		}
		if (idleTime.Ready()) {
			moveTime.Reset();
			idling = false;
			if (!player.expired()) {
				_direction = player.lock()->getPosition() - _parent->getPosition();
				_direction = normalize(_direction);
			}
			else {
				_direction = { 0,0 };
			}
		}
	}
	ActorMovementComponent::Update(dt);
}

EnemyAIComponent::EnemyAIComponent(Entity* p) : ActorMovementComponent(p) {
	_direction = Vector2f(1.0f, 0);
	_speed = 100.0f;

	cooldowns.push_back(&moveTime);
	cooldowns.push_back(&idleTime);
}
