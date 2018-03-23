#pragma once
#include <map>

struct ControlSystem {
	std::map<unsigned int, unsigned int> controls;
	string controlType;
};

class InputManager
{
public:
	static enum PS4 { SQUARE, X, O, TRIANGLE, L1, R1, L2, R2, SELECT, START, LEFTA, RIGHTA, PS, TOUCH};
	static enum Action { LEFT, RIGHT, SVM, JUMP, AIM, FIRE, SHIELD, ACTIVE };
	InputManager();
	~InputManager() = default;
	void Update(double dt);
	bool GetButtonDown(unsigned int button);
	bool GetButtonHeld(unsigned int button);
	bool GetButtonReleased(unsigned int button);
protected:
	bool buttonDown[14];
	bool buttonHeld[14];
	bool buttonReleased[14];
	ControlSystem activeControls;
	void ButtonDebug();
};