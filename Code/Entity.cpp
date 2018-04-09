#include "Entity.h"
using namespace std;
using namespace sf;

const Vector2f Entity::GetPosition() { return position; }
void Entity::SetPosition(const Vector2f &pos) { position = pos; }
void Entity::Update(const double dt)
{
	shape->setPosition(position);
}

Entity::Entity(unique_ptr<Shape> s) : shape(std::move(s)) {}