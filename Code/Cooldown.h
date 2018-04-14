#pragma once

class Cooldown {
private:
	double cooldown;
	double timeLeft;
	bool ready;
public:
	Cooldown(double);
	void SetTimer(double);
	void Update(const double &dt);
	bool Ready();
	void Reset();
};