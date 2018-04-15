#include "cmp_player_condition.h"
#include "cmp_player_interaction.h"

using namespace std;
using namespace sf;

PlayerCondition::PlayerCondition(Entity* p) : Component(p) {

}

void PlayerCondition::TakeDamage(int value) {
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

}