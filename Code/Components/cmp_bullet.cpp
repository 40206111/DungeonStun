#include "cmp_bullet.h"
using namespace std;
using namespace sf;

void BulletComponent::Update(const double &dt) {
  _lifetime -= dt;
  if (_lifetime <= 0.f) {
    _parent->setForDelete();
  }
}

BulletComponent::BulletComponent(Entity* p, float lifetime)
    : Component(p), _lifetime(lifetime) {}
