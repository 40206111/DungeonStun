#pragma once

#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
  b2Vec2 _size;
  sf::Vector2f _maxVelocity;
  bool _grounded;
  float _groundspeed;
  bool _inSVM = false;
  int _antiMoves = 0;

  bool isGrounded() const;

public:
  void Update(const double &dt) override;

  explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

  PlayerPhysicsComponent() = delete;
};
