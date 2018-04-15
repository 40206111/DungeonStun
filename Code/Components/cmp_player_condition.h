#pragma once

#include "ecm.h"

class PlayerInteraction;

class PlayerCondition : public Component {
private:
	std::shared_ptr<PlayerInteraction> playerInt;
	// Health sprites
	int maxHealth = 6;
	int currentHealth = 6;
	int tempHealth = 0;
public:
	void Update(const double &dt) override;
	void render() override;

	void TakeDamage(int);
	void Heal(int);

	PlayerCondition() = delete;
	explicit PlayerCondition(Entity*);
	~PlayerCondition() = default;
};