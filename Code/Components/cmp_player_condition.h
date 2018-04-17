#pragma once

#include "ecm.h"
#include <SFML\Graphics.hpp>

class PlayerInteraction;

class PlayerCondition : public Component {
private:
	std::shared_ptr<PlayerInteraction> playerInt;
	// Health sprites
	int maxHealth = 4;
	int currentHealth = 3;
	int tempHealth = 3;
	sf::Sprite container;
	sf::Sprite heart;
	sf::Sprite halfHeart;
	sf::Sprite temp;
public:
	void Update(const double &dt) override;
	void render() override;

	void TakeDamage(int);
	void Heal(int);

	void SetContainerSprite(sf::Sprite sc) { container = sc; }
	void SetHeartSprite(sf::Sprite sc) { heart = sc; }
	void SetHalfHeartSprite(sf::Sprite sc) { halfHeart = sc; }
	void SetTempHeartSprite(sf::Sprite sc);

	PlayerCondition() = delete;
	explicit PlayerCondition(Entity*);
	~PlayerCondition() = default;
};