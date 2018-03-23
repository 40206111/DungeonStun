#include "InputManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

/*
PS4 button codes
0 - square
1 - x
2 - o
3 - triangle
4 - L1
5 - R1
6 - L2
7 - R2
8 - select
9 - start
10 - left analogue down
11 - right analogue down
12 - PS button
13 - touch pad down

X Axis - Left Analogue -100 left, 100 right, 0 center
Y Axis - Left Analogue -100 up, 100 down, 0 center
Z Axis - Right Analogue -100 left, 100 right, 0 center
R Axis - Right Analogue -100 up, 100 down, 0 center
PovX Axis - D-pad -100 left, 100 right, 0 none
PovY Axis - D-pad -100 down, 100 up, 0 none
V Axis - L2 -100 not pressed, 100 fully pressed
U Axis - R2 -100 not pressed, 100 fully pressed
*/

InputManager::InputManager()
{
	ControlSystem pscontroller;
	pscontroller.controls = {
		{R1, SVM}, {L1, JUMP}, {O, JUMP},
		{R2, FIRE}, {L2, SHIELD}, {X, ACTIVE} };
	activeControls = pscontroller;
	sf::Joystick::Identification id = sf::Joystick::getIdentification(0);
	cout << "\nVendor ID: " << id.vendorId << "\nProduct ID: " << id.productId << endl;

	string controller("Joystick Use: " + id.name);
	cout << controller << endl;

	if (sf::Joystick::isConnected(0))
	{
		unsigned int buttonCount = sf::Joystick::getButtonCount(0);

		bool hasZ = sf::Joystick::hasAxis(0, sf::Joystick::Z);

		cout << "Button count: " << buttonCount << std::endl;
		cout << "Has a z-axis: " << hasZ << std::endl;
	}
}

void InputManager::ButtonDebug()
{
	if (GetButtonDown(SQUARE))
	{
		cout << "SQUARE" << endl;
	}
	if (GetButtonDown(X))
	{
		cout << "X" << endl;
	}
	if (GetButtonDown(O))
	{
		cout << "O" << endl;
	}
	if (GetButtonDown(TRIANGLE))
	{
		cout << "TRIANGLE" << endl;
	}
	if (GetButtonDown(L1))
	{
		cout << "L1" << endl;
	}
	if (GetButtonDown(R1))
	{
		cout << "R1" << endl;
	}
	if (GetButtonDown(L2))
	{
		cout << "L2" << endl;
	}
	if (GetButtonDown(R2))
	{
		cout << "R2" << endl;
	}
	if (GetButtonDown(SELECT))
	{
		cout << "SELECT" << endl;
	}
	if (GetButtonDown(START))
	{
		cout << "START" << endl;
	}
	if (GetButtonDown(LEFTA))
	{
		cout << "LEFTA" << endl;
	}
	if (GetButtonDown(RIGHTA))
	{
		cout << "RIGHTA" << endl;
	}
	if (GetButtonDown(PS))
	{
		cout << "PS" << endl;
	}
	if (GetButtonDown(TOUCH))
	{
		cout << "TOUCH" << endl;
	}
}

void InputManager::Update(double dt)
{
	for (int i = 0; i < 14; ++i)
	{
		if (buttonDown[i]) {
			buttonDown[i] = false;
		}
		if (buttonReleased[i]) {
			buttonReleased[i] = false;
		}
		if (sf::Joystick::isButtonPressed(0, i))
		{
			if (!buttonHeld[i]) {
				buttonDown[i] = true;
				buttonHeld[i] = true;
			}
		}
		else if (buttonHeld[i]) {
			buttonHeld[i] = false;
			buttonReleased[i] = true;
		}
	}

	ButtonDebug();
}

bool InputManager::GetButtonDown(unsigned int button) {
	return buttonDown[button];
}

bool InputManager::GetButtonHeld(unsigned int button) {
	return buttonHeld[button];
}

bool InputManager::GetButtonReleased(unsigned int button) {
	return buttonReleased[button];
}