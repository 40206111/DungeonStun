#pragma once

#include "ecm.h"

class EnemyCondition : public Component {
protected:
	float torporMax = 200.0f; // max "health"
	float torporVal = 0.0f; // current "health"
	float recoverySpeed = 8.0f; // percent per second
	float wakingThreshold = 0.2f; // fraction of max
	bool awake = true;

public:
	EnemyCondition() = delete;
	explicit EnemyCondition(Entity* p);
	~EnemyCondition() = default;

	void Update(const double &dt) override;
	void render() override {}

	void InflictTorpor(float value);
	bool IsAwake() { return awake; }
};