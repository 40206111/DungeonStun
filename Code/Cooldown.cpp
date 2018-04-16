#include "Cooldown.h"

Cooldown::Cooldown(double cd) {
	cooldown = cd;
	ready = false;
	timeLeft = cooldown;
}

void Cooldown::SetTimer(double time) {
	cooldown = time;
}

void Cooldown::Update(const double &dt) {
	if (!ready) {
		timeLeft -= dt;
		if (timeLeft <= 0.0) {
			ready = true;
		}
	}
}

bool Cooldown::Ready() {
	return ready;
}

void Cooldown::Reset() {
	timeLeft = cooldown;
	ready = false;
}