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
	cooldowns.push_back(&shootAnim);
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

void PlayerInteraction::SetPlayerSprite(std::weak_ptr<SpriteComponent> sc)
{
	playerSprite = sc;

	Vector2f pos = playerSprite.lock()->getSprite().getPosition();
	Vector2f scale = playerSprite.lock()->getSprite().getScale();
	Vector2f origin = playerSprite.lock()->getSprite().getOrigin();

	playerWalk.setPosition(pos);
	playerWalk.setScale(scale);
	playerWalk.setOrigin(origin);

	playerJump.setPosition(pos);
	playerJump.setScale(scale);
	playerJump.setOrigin(origin);

	playerShoot.setPosition(pos);
	playerShoot.setScale(scale);
	playerShoot.setOrigin(origin);

	playerClimb.setPosition(pos);
	playerClimb.setScale(scale);
	playerClimb.setOrigin(origin);
}

float dot(Vector2f a, Vector2f b) {
	return a.x * b.x + a.y * b.y;
}

void PlayerInteraction::Update(const double &dt) {
	// Update all cooldowns
	for (Cooldown* cd : cooldowns) {
		cd->Update(dt);
	}
	// Change animation state
	prevState = currState;
	if (!shootAnim.Ready()) {
		currState = SHOOT;
	}
	else if (inSVM) {
		currState = CLIMB;
	}
	else if (!isGrounded) {
		currState = JUMP;
	}
	else {
		currState = WALK;
	}
	// If animation state changed
	if (prevState != currState) {
		// Swap sprite
		switch (currState)
		{
		case PlayerInteraction::WALK:
			playerSprite.lock()->setSprite(playerWalk);
			break;
		case PlayerInteraction::JUMP:
			playerSprite.lock()->setSprite(playerJump);
			break;
		case PlayerInteraction::CLIMB:
			playerSprite.lock()->setSprite(playerClimb);
			break;
		case PlayerInteraction::SHOOT:
			playerSprite.lock()->setSprite(playerShoot);
			break;
		default:
			break;
		}
		Vector2f currScale = playerSprite.lock()->getSprite().getScale();
		currScale.x = copysign(currScale.x, (aimDirection.x < 0 ? -1 : 1));
		playerSprite.lock()->getSprite().setScale(currScale);
	}

	/// Aim start---------------------
	//  Update aim direction
	Vector2f dir;
	if (player1->activeControls->controlType == "PS4") {
		dir = Vector2f(Joystick::getAxisPosition(player1->controlerid, Joystick::Z), Joystick::getAxisPosition(player1->controlerid, Joystick::R));
	}
	else {
		dir = (Vector2f)sf::Mouse::getPosition(Renderer::GetWindow()) - _parent->getPosition();
	}
	if (dir != Vector2f(0.0f, 0.0f)) {
		dir = normalize(dir);
	}
	float prev = aimDirection.x;
	aimDirection = dir;
	float curr = aimDirection.x;
	if (prev * curr < 0) {
		Vector2f currScale = playerSprite.lock()->getSprite().getScale();
		currScale.x = copysign(currScale.x, (curr < 0 ? -1 : 1));
		playerSprite.lock()->getSprite().setScale(currScale);
	}

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
		&& !blocking && antiFire == 0) {
		if (dot(aimDirection, { 0 , -1 }) < -0.5f) {
			int side = (aimDirection.x > 0 ? 1 : -1);
			aimDirection = normalize(Vector2f(sqrtf(2), 1));
			aimDirection.x *= side;
		}
		// Do a shoot
		shared_ptr<Entity> proj = dynamic_cast<GameScene*>(_parent->scene)->SpawnEntity(em::PROJECTILE);
		shared_ptr<ProjectilePhysics> pphys = proj->get_components<ProjectilePhysics>()[0];
		pphys->teleport(_parent->getPosition() + Vector2f(0.0f, -playerSize.y / 2.0f) + aimDirection * 25.0f);
		pphys->SetDirection({ aimDirection });
		printf("dir: %f\n", dot(aimDirection, { 0 , -1 }));
		fireCD.Reset();
		shootAnim.Reset();
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
		// ------------------------------


	}
	/// Active end---------------------------

	// player collides with chest
	if (false) {
		// open the chest
	}
}
