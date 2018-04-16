#include "cmp_player_interaction.h"
#include "..\Game.h"
#include "..\EntityMaker.h"
#include "cmp_projectile_physics.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

PlayerInteraction::PlayerInteraction(Entity* _parent) : Component(_parent){
	cooldowns.push_back(&blockCd);
	cooldowns.push_back(&blockDuration);
	cooldowns.push_back(&fireCD);
	cooldowns.push_back(&activeCD);
}

void PlayerInteraction::SetSvmState(bool state) {
	inSVM = state;
}

void PlayerInteraction::SetAlive(bool state) {
	isAlive = state;
	if (isAlive) {
	}
	else {
		inSVM = false;
		blocking = false;
	}
}

void PlayerInteraction::Update(const double &dt) {
	// Update all cooldowns
	for (Cooldown* cd : cooldowns) {
		cd->Update(dt);
	}

	/// Aim start---------------------
	//  Update aim directin
	Vector2f dir = (Vector2f)sf::Mouse::getPosition() - _parent->getPosition();
	if (dir != Vector2f(0.0f, 0.0f)) {
		dir = normalize(dir);
	}
	aimDirection = dir;
	/// Aim end-----------------------

	/// Fire start--------------------
	if (player1->GetButtonDown(InputManager::FIRE)) {
		int x = 5;
	}
	if (player1->GetButtonHeld(InputManager::FIRE) && fireCD.Ready()) {
		// Do a shoot
		shared_ptr<Entity> proj = dynamic_cast<GameScene*>(_parent->scene)->SpawnEntity(em::PROJECTILE);
		shared_ptr<ProjectilePhysics> pphys = proj->get_components<ProjectilePhysics>()[0];
		pphys->teleport(_parent->getPosition() + Vector2f(1.0f, 0.0f));
		pphys->SetDirection({ 1.0f,0.0f });
		fireCD.Reset();
	}
	/// Fire end----------------------

	/// Blocking start---------------------
	// If block duration is over
	if (blockDuration.Ready()) {
		// Stop blocking
		blocking = false;
		// Allow firing
		AllowFiring();
		// Start cooldown
		blockCd.Reset();
	}
	// If block pushed and ready
	if (player1->GetButtonDown(InputManager::SHIELD) && blockCd.Ready()) {
		// Activate shield component
		blocking = true;
		// Prevent firing
		PreventFiring();
		// Start duration timer
		blockDuration.Reset();
	}
	/// Blocking end-----------------------

	if (player1->GetButtonDown(InputManager::SVM)) {
		//Special jump
		// Taken care of in physics
	}

	/// Active start------------------------
	if (player1->GetButtonDown(InputManager::ACTIVE) && activeCD.Ready()) {
		// Active item
		// Use the active item
		activeCD.Reset();

		// To test movement impairing---
		if (CanMove()) {
			PreventMoving();
		}
		else {
			AllowMoving();
		}
		// ------------------------------


	}
	/// Active end---------------------------

	// player collides with chest
	if (false) {
		// open the chest
	}
}
