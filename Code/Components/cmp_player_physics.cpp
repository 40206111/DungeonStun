#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "../game.h"
#include "InputManager.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isGrounded() const {
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	const float halfPlrHeigt = _size.y * .5f;
	const float halfPlrWidth = _size.x * .5f;
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
			return true;
		}
	}

	return false;
}

void PlayerPhysicsComponent::SetSvmState(bool state) {
	if (state) {
		_inSVM = true;
		this->_body->SetGravityScale(0.0f);
		this->_body->SetLinearVelocity({ 0.0f,0.0f });
		teleport(Vector2f(_parent->getPosition().x, _parent->getPosition().y - 2.0f));
		// Inform player interaction about no shooting
	}
	else {
		svmCD.Reset();
		_inSVM = false;
		this->_body->SetGravityScale(1.0f);
		// Let player know this inhibition is removed for shooting
	}
}

void PlayerPhysicsComponent::Update(const double &dt) {
	svmCD.Update(dt);
	const auto pos = _parent->getPosition();

	//Teleport to start if we fall off map.
	if (pos.y > ls::getHeight() * ls::getTileSize() + ls::getOffset().y) {
		//if (false){
		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}
	// If svm button toggle svm state
	if (player1->GetButtonDown(InputManager::SVM) && svmCD.Ready() && !_inSVM) {
		SetSvmState(true);
	}
	// if not in SVM do regular movement
	if (!_inSVM) {
		if (player1->GetButtonHeld(InputManager::LEFT) ||
			player1->GetButtonHeld(InputManager::RIGHT)) {
			// Moving Either Left or Right
			if (player1->GetButtonHeld(InputManager::RIGHT)) {
				if (getVelocity().x < _maxVelocity.x)
					impulse({ (float)(dt * _groundspeed), 0 });
			}
			else {
				if (getVelocity().x > -_maxVelocity.x)
					impulse({ -(float)(dt * _groundspeed), 0 });
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
			impulse({ -(float)(dt * _groundspeed), 0 });
			SetSvmState(false);
		}
		if (player1->GetButtonDown(InputManager::RIGHT)) {
			impulse({ (float)(dt * _groundspeed), 0 });
			SetSvmState(false);
		}
		if (player1->GetButtonHeld(InputManager::MENUUP) ||
			player1->GetButtonHeld(InputManager::MENUDOWN)) {
			// Move either up or down
			if (player1->GetButtonHeld(InputManager::MENUUP)) {
				impulse({ 0, -(float)(dt * _groundspeed) });
			}
			else {
				impulse({ 0, (float)(dt * _groundspeed) });
			}
		}
		else {
			dampen({ 0.0f, 0.5f });
		}
	}

	// Handle Jump
	if (player1->GetButtonDown(InputManager::JUMP)) {
		_grounded = isGrounded();
		if (_grounded) {
			setVelocity(Vector2f(getVelocity().x, 0.0f));
			teleport(Vector2f(pos.x, pos.y - 2.0f));
			impulse(Vector2f(0, -6.0f));
		}
	}

	//Are we in air?
	if (!_grounded) {
		// Check to see if we have landed yet
		_grounded = isGrounded();
		// disable friction while jumping
		setFriction(0.f);
	}
	else {
		setFriction(0.1f);
	}

	// Clamp velocity.
	auto v = getVelocity();
	v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	setVelocity(v);

	PhysicsComponent::Update(dt);
}

PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
	const Vector2f& size)
	: PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	_maxVelocity = Vector2f(200.f, 400.f);
	_groundspeed = 30.f;
	_grounded = false;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);
}
