#pragma once

#include "ecm.h"
#include "cmp_actor_movement.h"
#include "../Cooldown.h"

class EnemyAIComponent : public ActorMovementComponent {
protected:
	std::weak_ptr<Entity> player;
	sf::Vector2f _direction;
	bool idling = false;
	std::vector<Cooldown*> cooldowns;
	Cooldown idleTime = Cooldown(0.3);
	Cooldown moveTime = Cooldown(0.8);

public:
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	~EnemyAIComponent() = default;

	void SetPlayer(std::weak_ptr<Entity> p) { player = p; }

	void Update(const double &dt) override;
};
