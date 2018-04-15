#include "cmp_player_interaction.h"
#include "../Game.h"

using namespace std;
using namespace sf;

PlayerInteraction::PlayerInteraction(Entity* _parent) : Component(_parent){}

void PlayerInteraction::SetSvmState(bool state) {
	inSVM = state;
}

void PlayerInteraction::Update(const double &dt) {
	//  Update aim directin
	Vector2f dir = (Vector2f)sf::Mouse::getPosition() - _parent->getPosition();
	if (dir != Vector2f(0.0f, 0.0f)) {
		dir = normalize(dir);
	}
	aimDirection = dir;
	//---------------

	if (player1->GetButtonHeld(InputManager::FIRE)) {
		// Do a shoot
		// send projectile at aimDirection
	}
	if (player1->GetButtonDown(InputManager::SHIELD)) {
		// Activate shield component
	}
	if (player1->GetButtonDown(InputManager::SVM)) {
		//Special jump
		// Taken care of in physics
	}
	if (player1->GetButtonDown(InputManager::ACTIVE)) {
		// Active item
		if (CanMove()) {
			PreventMoving();
		}
		else {
			AllowMoving();
		}
	}

	// player collides with chest
	if (false) {
		// open the chest
	}
}
