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

///INPUT MANAGER CLASS///

const std::map<sf::Keyboard::Key, std::string> InputManager::keyboardControls = {
	{ sf::Keyboard::LShift, "LEFT SHIFT" },
{ sf::Keyboard::RShift, "RIGHT SHIFT" },
{ sf::Keyboard::LControl, "LEFT CONTROL" },
{ sf::Keyboard::RControl, "RIGHT CONTROL" },
{ sf::Keyboard::LAlt, "LEFT ALT" },
{ sf::Keyboard::RAlt, "RIGHT ALT" },
{ sf::Keyboard::Tab, "TAB" },
{ sf::Keyboard::Return, "ENTER" },
{ sf::Keyboard::BackSpace, "BACKSPACE" },
{ sf::Keyboard::F1, "F1" },
{ sf::Keyboard::F2, "F2" },
{ sf::Keyboard::F3, "F3" },
{ sf::Keyboard::F4, "F4" },
{ sf::Keyboard::F5, "F5" },
{ sf::Keyboard::F6, "F6" },
{ sf::Keyboard::F7, "F7" },
{ sf::Keyboard::F8, "F8" },
{ sf::Keyboard::F9, "F9" },
{ sf::Keyboard::F10, "F10" },
{ sf::Keyboard::F11, "F11" },
{ sf::Keyboard::F12, "F12" },
{ sf::Keyboard::Home, "HOME" },
{ sf::Keyboard::End, "END" },
{ sf::Keyboard::PageUp, "PAGE UP" },
{ sf::Keyboard::PageDown, "PAGE DOWN" },
{ sf::Keyboard::Delete, "DEL" },
{ sf::Keyboard::Left, "LEFT ARROW" },
{ sf::Keyboard::Right, "RIGHT ARROW" },
{ sf::Keyboard::Up, "UP ARROW" },
{ sf::Keyboard::Down, "DOWN ARROW" },
{ sf::Keyboard::Menu, "MENU" },
{ sf::Keyboard::Pause, "PAUSE" },
{ sf::Keyboard::Num0, "0" },
{ sf::Keyboard::Num1, "1" },
{ sf::Keyboard::Num2, "2" },
{ sf::Keyboard::Num3, "3" },
{ sf::Keyboard::Num4, "4" },
{ sf::Keyboard::Num5, "5" },
{ sf::Keyboard::Num6, "6" },
{ sf::Keyboard::Num7, "7" },
{ sf::Keyboard::Num8, "8" },
{ sf::Keyboard::Num9, "9" },
{ sf::Keyboard::Numpad0, "NUMPAD 0" },
{ sf::Keyboard::Numpad1, "NUMPAD 1" },
{ sf::Keyboard::Numpad2, "NUMPAD 2" },
{ sf::Keyboard::Numpad3, "NUMPAD 3" },
{ sf::Keyboard::Numpad4, "NUMPAD 4" },
{ sf::Keyboard::Numpad5, "NUMPAD 5" },
{ sf::Keyboard::Numpad6, "NUMPAD 6" },
{ sf::Keyboard::Numpad7, "NUMPAD 7" },
{ sf::Keyboard::Numpad8, "NUMPAD 8" },
{ sf::Keyboard::Numpad9, "NUMPAD 9" },
};

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

const std::map<InputManager::PS4, std::string> InputManager::ps4Controls = {
	{InputManager::SQUARE, "SQUARE" },
	{InputManager::X, "X" },
	{InputManager::O, "CIRCLE" },
	{InputManager::TRIANGLE, "TRIANGLE" },
	{InputManager::L1, "L1" },
	{InputManager::R1, "R1" },
	{InputManager::L2, "L2" },
	{InputManager::R2, "R2" },
	{InputManager::SELECT, "SELECT" },
	{InputManager::START, "START" },
	{InputManager::LEFTA, "LEFT ANALOGUE" },
	{InputManager::RIGHTA, "RIGHT ANOLOGUE" },
	{InputManager::PS, "PLAY STATION" },
	{InputManager::TOUCH, "TOUCH PAD" },
};

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