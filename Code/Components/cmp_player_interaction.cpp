#include "cmp_player_interaction.h"
#include "..\Game.h"
#include "..\EntityMaker.h"
#include "cmp_projectile_physics.h"
#include "system_physics.h"
#include <stdio.h>

using namespace std;
using namespace sf;

PlayerInteraction::PlayerInteraction(Entity* _parent) : Component(_parent) {
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

float dot(Vector2f a, Vector2f b) {
	return a.x * b.x + a.y * b.y;
}

void PlayerInteraction::Update(const double &dt) {
	// Update all cooldowns
	for (Cooldown* cd : cooldowns) {
		cd->Update(dt);
	}

	/// Aim start---------------------
	//  Update aim directin
	Vector2f dir = (Vector2f)sf::Mouse::getPosition(Renderer::GetWindow()) - _parent->getPosition();
	if (dir != Vector2f(0.0f, 0.0f)) {
		dir = normalize(dir);
	}
	aimDirection = dir;
	/// Aim end-----------------------

	/// Blocking start---------------------
	// If block duration is over
	if (blockDuration.Ready() && blocking) {
		// Stop blocking
		blocking = false;
		// Allow firing
		AllowFiring();
		// Start cooldown
		blockCd.Reset();
	}
	// If block pushed and ready
	if (player1->GetButtonDown(InputManager::SHIELD) && blockCd.Ready() && !blocking) {
		// Activate shield component
		blocking = true;
		// Prevent firing
		PreventFiring();
		// Start duration timer
		blockDuration.Reset();
	}
	/// Blocking end-----------------------

	/// Fire start--------------------
	if (player1->GetButtonHeld(InputManager::FIRE) && fireCD.Ready() 
		&& !blocking) {
		if (dot(aimDirection, { 0 , -1 }) < -0.5f) {
			int side = (aimDirection.x > 0 ? 1 : -1);
			aimDirection = normalize(Vector2f( sqrtf(2), 1 ));
			aimDirection.x *= side;
		}
		// Do a shoot
		shared_ptr<Entity> proj = dynamic_cast<GameScene*>(_parent->scene)->SpawnEntity(em::PROJECTILE);
		shared_ptr<ProjectilePhysics> pphys = proj->get_components<ProjectilePhysics>()[0];
		pphys->teleport(_parent->getPosition() + Vector2f(0.0f, -playerSize.y/2.0f) + aimDirection * 25.0f);
		pphys->SetDirection({ aimDirection });
		printf("dir: %f\n", dot(aimDirection, { 0 , -1 }));
		fireCD.Reset();
	}
	/// Fire end----------------------

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
