#include "cmp_physics.h"
#include "system_physics.h"

using namespace std;
using namespace sf;

using namespace Physics;

void PhysicsComponent::Update(const double &dt) {
	_parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
	_parent->setRotation((180.0f / b2_pi) * _body->GetAngle());
}

PhysicsComponent::PhysicsComponent(Entity* p, bool dyn,
	const Vector2f& size)
	: Component(p), _dynamic(dyn) {

	b2BodyDef BodyDef;
	 //Is Dynamic(moving), or static(Stationary)
	BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));
	BodyDef.bullet = true;

	//// Create the body
	_body = Physics::GetWorld()->CreateBody(&BodyDef);
	_body->SetActive(true);
	//{
	//	// Create the fixture shape
	//	b2PolygonShape Shape;
	//	// SetAsBox box takes HALF-Widths!
	//	Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f, b2Vec2(0.0f, sv2_to_bv2(size).y * 0.5f),0.0f);
	//	b2FixtureDef FixtureDef;
	//	// Fixture properties
	//	// FixtureDef.density = _dynamic ? 10.f : 0.f;
	//	FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
	//	FixtureDef.restitution = .2;
	//	FixtureDef.shape = &Shape;
	//	// Add to body
	//	_fixture = _body->CreateFixture(&FixtureDef);
	//	//_fixture->SetRestitution(.9)
	//	FixtureDef.restitution = .2;
	//}

	// An ideal Pod/capusle shape should be used for hte player,
	// this isn't built into B2d, but we can combine two shapes to do so.
	// This would allwo the player to go up steps

	b2PolygonShape shape1;
	shape1.SetAsBox(sv2_to_bv2(size).x * 0.45f, sv2_to_bv2(size).y * 0.25f, b2Vec2(0.0f, sv2_to_bv2(size).y * 0.75f), 0.0f);

	b2FixtureDef FixtureDefPoly;

	FixtureDefPoly.friction = _dynamic ? 0.1f : 0.8f;
	FixtureDefPoly.restitution = .2;
	FixtureDefPoly.shape = &shape1;
	_body->CreateFixture(&FixtureDefPoly);

	b2CircleShape circle;
	circle.m_radius = sv2_to_bv2(size).x * 0.5f;
	circle.m_p.Set(0.0f, sv2_to_bv2(size).y * 0.25f);
	b2FixtureDef FixtureDefCircle;
	FixtureDefCircle.friction = _dynamic ? 0.1f : 0.8f;
	FixtureDefCircle.restitution = .0;
	FixtureDefCircle.shape = &circle;
	_fixture = _body->CreateFixture(&FixtureDefCircle);

}

PhysicsComponent::PhysicsComponent(Entity * p, bool dyn, const float size)
	: Component(p), _dynamic(dyn) {

	b2BodyDef BodyDef;
	// Is Dynamic(moving), or static(Stationary)
	BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

	// Create the body
	_body = Physics::GetWorld()->CreateBody(&BodyDef);
	_body->SetActive(true);

	// Create the fixture shape
	b2CircleShape circle;
	// SetAsCircl cricle takes radius
	circle.m_radius = (size * physics_scale_inv);
	circle.m_p.Set(0.0f, 0.0f);
	b2FixtureDef FixtureDefCircle;
	// Fixture properties
	// FixtureDef.density = _dynamic ? 10.f : 0.f;
	FixtureDefCircle.shape = &circle;
	//FixtureDefCircle.filter.maskBits = 8;
	// Add to body
	_body->CreateFixture(&FixtureDefCircle);
	_body->SetGravityScale(0.0f);
}

void PhysicsComponent::setFriction(float r) { _fixture->SetFriction(r); }

void PhysicsComponent::setMass(float m) { _fixture->SetDensity(m); }

void PhysicsComponent::teleport(const sf::Vector2f& v) {
	_body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

const sf::Vector2f PhysicsComponent::getVelocity() const {
	Vector2f out = bv2_to_sv2(_body->GetLinearVelocity(), true);
	out.y *= -1.0f;
	return out;
}
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
	b2Vec2 in = sv2_to_bv2(v, true);
	in.y *= -1.0f;
	_body->SetLinearVelocity(in);
}

b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

PhysicsComponent::~PhysicsComponent() {
	auto a = Physics::GetWorld();
	_body->SetActive(false);
	Physics::GetWorld()->DestroyBody(_body);
	// delete _body;
	_body = nullptr;
}

void PhysicsComponent::render() {}

void PhysicsComponent::impulse(const sf::Vector2f& i) {
	auto a = b2Vec2(i.x, i.y * -1.0f);
	_body->ApplyLinearImpulseToCenter(a, true);
}

void PhysicsComponent::dampen(const sf::Vector2f& i) {
	auto vel = _body->GetLinearVelocity();
	vel.x *= i.x;
	vel.y *= i.y;
	_body->SetLinearVelocity(vel);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc) const {
	b2Contact* bc;
	return isTouching(pc, bc);
}

bool PhysicsComponent::isTouching(const PhysicsComponent& pc,
	b2Contact const* bc) const {
	const auto _otherFixture = pc.getFixture();
	const auto& w = *Physics::GetWorld();
	const auto contactList = w.GetContactList();
	const auto clc = w.GetContactCount();
	for (int32 i = 0; i < clc; i++) {
		const auto& contact = (contactList[i]);
		if (contact.IsTouching() && ((contact.GetFixtureA() == _fixture &&
			contact.GetFixtureA() == _otherFixture) ||
			(contact.GetFixtureA() == _otherFixture &&
				contact.GetFixtureA() == _fixture))) {
			bc = &contact;
			return true;
		}
	}
	return false;
}

std::vector<const b2Contact const*> PhysicsComponent::getTouching() const {
	std::vector<const b2Contact const*> ret;

	b2ContactEdge* edge = _body->GetContactList();
	while (edge != NULL) {
		const b2Contact* contact = edge->contact;
		if (contact->IsTouching()) {
			ret.push_back(contact);
		}
		edge = edge->next;
	}

	return ret;
}

void PhysicsComponent::setRestitution(float r) {
	_fixture->SetRestitution(r);
}
