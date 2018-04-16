#include "cmp_enemy_condition.h"

using namespace std;
using namespace sf;

EnemyCondition::EnemyCondition(Entity * p)
	: Component(p) {}

void EnemyCondition::Update(const double & dt)
{
	if (torporVal >= torporMax) {
		awake = false;
		torporVal = torporMax;
	}
	else if (torporVal <= torporMax * wakingThreshold) {
		awake = true;
	}
	torporVal -= dt * torporMax / (100.0f / recoverySpeed);
}

void EnemyCondition::InflictTorpor(float value)
{
	torporVal += value;
}
