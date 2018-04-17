#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "../game.h"
#include "InputManager.h"
#include "cmp_player_interaction.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isGrounded() const {
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	const float halfPlrHeigt = -0.15;//size.y * .5f;
	const float halfPlrWidth = size.x * .5f;
	b2WorldManifold manifold;
	for (const auto& contact : touch) {
		contact->GetWorldManifold(&manifold);
		const int numPoints = contact->GetManifold()->pointCount;
		bool onTop = numPoints > 0;
		// If all contacts are below the player.
		for (int j = 0; j < numPoints; j++) {
			onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
		}
		if (onTop) {
			playerInt->SetGroundedState(true);
			return true;
		}
	}
	playerInt->SetGroundedState(false);
	return false;
}

void PlayerPhysicsComponent::SetSvmState(bool state) {
	if (state) {
		playerInt->SetSvmState(true);
		this->_body->SetGravityScale(0.0f);
		this->_body->SetLinearVelocity({ 0.0f,0.0f });
		teleport(Vector2f(_parent->getPosition().x, _parent->getPosition().y - 2.0f));
		// Inform player interaction about no shooting
		playerInt->PreventFiring();
	}
	else {
		svmCD.Reset();
		playerInt->SetSvmState(false);
		grounded = false;
		this->_body->SetGravityScale(1.0f);
		// Let player know this inhibition is removed for shooting
		playerInt->AllowFiring();
	}
}

void PlayerPhysicsComponent::Jump(const Vector2f &pos) {
	setVelocity(Vector2f(getVelocity().x, 0.0f));
	teleport(Vector2f(pos.x, pos.y - 2.0f));
	impulse(Vector2f(0, -6.0f));
}

void PlayerPhysicsComponent::Update(const double &dt) {
	svmCD.Update(dt);
	maybeGrounded.Update(dt);
	const auto pos = _parent->getPosition();

	//Teleport to start if we fall off map.
	if (pos.y > ls::getHeight() * ls::getTileSize() + ls::getOffset().y) {
		//if (false){
		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}
	// If the player can move
	if (playerInt->CanMove()) {
		// If svm button toggle svm state
		if (player1->GetButtonDown(InputManager::SVM) &&
			svmCD.Ready() && !playerInt->InSvm() && isGrounded()) {
			SetSvmState(true);
		}
		// if not in SVM do regular movement
		if (!playerInt->InSvm()) {
			if (player1->GetButtonHeld(InputManager::LEFT) ||
				player1->GetButtonHeld(InputManager::RIGHT)) {
				// Moving Either Left or Right
				if (player1->GetButtonHeld(InputManager::RIGHT)) {
					if (getVelocity().x < maxVelocity.x)
						impulse({ (float)(dt * groundspeed), 0 });
				}
				else {
					if (getVelocity().x > -maxVelocity.x)
						impulse({ -(float)(dt * groundspeed), 0 });
				}
			}
			else {
				// Dampen X axis movement
				dampen({ 0.9f, 1.0f });
			}
		}
		// If in svm behave differently
		else {
			if (player1->GetButtonDown(InputManager::LEFT)) {
				setVelocity({ -(float)(dt * groundspeed * 15.0f), 0.0f });
				Jump(pos);
				SetSvmState(false);
			}
			if (player1->GetButtonDown(InputManager::RIGHT)) {
				setVelocity({ (float)(dt * groundspeed * 15.0f),  0.0f });
				Jump(pos);
				SetSvmState(false);
			}
			if (player1->GetButtonHeld(InputManager::MENUUP) ||
				player1->GetButtonHeld(InputManager::MENUDOWN)) {
				// Move either up or down
				if (player1->GetButtonHeld(InputManager::MENUUP)) {
					impulse({ 0, -(float)(dt * groundspeed) });
				}
				else {
					impulse({ 0, (float)(dt * groundspeed) });
				}
			}
			else {
				dampen({ 0.0f, 0.5f });
			}
		}

		// Handle Jump
		if (player1->GetButtonDown(InputManager::JUMP)) {
			grounded = isGrounded();
			if (grounded || playerInt->InSvm()) {
				Jump(pos);
				if (playerInt->InSvm()) {
					SetSvmState(false);
				}
			}
			grounded = false;
		}
	}
	// If player cannot move
	else {
		if (playerInt->InSvm()) {
			SetSvmState(false);
		}
		// Dampen X axis movement
		dampen({ 0.9f, 1.0f });
	}

	//Are we in air?
	if (!grounded) {
		maybeGrounded.Reset();
		// Check to see if we have landed yet
		grounded = isGrounded();
		// disable friction while jumping
		setFriction(0.f);
	}
	else {
		if (!maybeGrounded.Ready()) {
			grounded = isGrounded();
		}
		setFriction(0.9f);
	}


	// Clamp velocity.
	auto v = getVelocity();
	v.x = copysign(min(abs(v.x), maxVelocity.x), v.x);
	v.y = copysign(min(abs(v.y), maxVelocity.y), v.y);
	setVelocity(v);

	PhysicsComponent::Update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
	const Vector2f& size)
	: PhysicsComponent(p, true, size) {
	this->size = sv2_to_bv2(size, true);
	maxVelocity = Vector2f(200.f, 400.f);
	groundspeed = 30.f;
	grounded = false;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);
	_body->GetFixtureList()[0].SetRestitution(0.0f);

	_body->SetUserData("player");
}
