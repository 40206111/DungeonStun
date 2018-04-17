#include "cmp_player_condition.h"
#include "cmp_player_interaction.h"

using namespace std;
using namespace sf;

PlayerCondition::PlayerCondition(Entity* p) : Component(p) {

}

void PlayerCondition::TakeDamage(int value) {
	if (playerInt->IsBlocking()) {
		return;
	}
	//  If temporary health lose 1 tempHealth
	if (tempHealth > 0) {
		tempHealth--;
	}
	// If no temp health
	else {
		// Reduce health by value, or to 0 if 0 higher
		currentHealth = max(currentHealth - value, 0);
		if (currentHealth == 0) {
			playerInt->SetAlive(false);
		}
	}
}

void PlayerCondition::Heal(int value) {
	// Heal by the value, or to maxHealth if max lower
	currentHealth = min(currentHealth + value, maxHealth);
}

void PlayerCondition::Update(const double &dt) {

}

void PlayerCondition::render() {

	for (int i = 0; i < maxHealth; i+=2)
	{
		Sprite* h = new Sprite();

		if ((currentHealth - i) == 1)
		{
			halfHeart.setPosition(10 + i * 30, 10);
			*h = halfHeart;
			Renderer::Queue(Renderer::UIFORE, h);
		}
		else if (i < currentHealth)
		{
			heart.setPosition(10 + i * 30, 10);
			*h = heart;
			Renderer::Queue(Renderer::UIFORE,h);
		}
		else if (i > currentHealth)
		{
			container.setPosition(10 + i * 30, 10);
			*h = container;
			Renderer::Queue(Renderer::UIMID, h);
		}
	}

	for (int i = 0; i < tempHealth; i++)
	{
		Sprite* h = new Sprite();
		temp.setPosition(5 + i * 60, 5);
		*h = temp;
		Renderer::Queue(Renderer::UIBACK, h);
	}
}

void PlayerCondition::SetTempHeartSprite(sf::Sprite sc)
{
	temp = sc;
	temp.scale(0.5, 0.5);
	container.scale(0.5, 0.5);
	heart.scale(0.5, 0.5);
	halfHeart.scale(0.5, 0.5);
}