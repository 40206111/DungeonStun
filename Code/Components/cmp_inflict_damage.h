#pragma once

#include "ecm.h"

class InflictDamage : public Component {
protected:
	float damage = 40;
	bool fromPlayer = true;
public:
	InflictDamage() = delete;
	explicit InflictDamage(Entity* p);
	~InflictDamage() = default;

	void Update(const double &dt) override {}
	void render() override {}

	bool IsFriendly() { return fromPlayer; }

	void SetDamage(float value) { damage = value; }
	float GetDamage() { return damage; }
};