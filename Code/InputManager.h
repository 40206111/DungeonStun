#pragma once

class InputManager
{
public:
	static enum PS4 { SQUARE, X, O, TRIANGLE, L1, R1, L2, R2, SELECT, START, LEFTA, RIGHTA, PS, TOUCH};
	InputManager();
	~InputManager() = default;
	void Update(double dt);
};