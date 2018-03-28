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
	InputManager::CreateControlers();
	activeControls = keyMaps["PS4"];
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
	// LEFT, RIGHT, SVM, JUMP, AIM, FIRE, SHIELD, ACTIVE
	if (GetButtonDown(LEFT))
	{
		cout << "LEFT" << endl;
	}
	if (GetButtonDown(RIGHT))
	{
		cout << "RIGHT" << endl;
	}
	if (GetButtonDown(SVM))
	{
		cout << "SVM" << endl;
	}
	if (GetButtonDown(JUMP))
	{
		cout << "JUMP" << endl;
	}
	if (GetButtonDown(AIM))
	{
		cout << "AIM" << endl;
	}
	if (GetButtonDown(FIRE))
	{
		cout << "FIRE" << endl;
	}
	if (GetButtonDown(SHIELD))
	{
		cout << "SHEILD" << endl;
	}
	if (GetButtonDown(ACTIVE))
	{
		cout << "ACTIVE" << endl;
	}

}

void InputManager::CreateControlers()
{
	//create playstation control system
	ControlSystem pscontroller;
	//set basic ps4 controls
	pscontroller.controls = {
		{LEFT, std::make_pair(NONE, NONE)},{RIGHT, std::make_pair(NONE, NONE)},
		{SVM, std::make_pair(R1, NONE)},{JUMP, std::make_pair(L1, O)},
		{FIRE, std::make_pair(R2, NONE)},{SHIELD, std::make_pair(L2, NONE)},
		{ACTIVE, std::make_pair(X, NONE)},{AIM, std::make_pair(NONE, NONE)}
	};
	pscontroller.controlType = "PS4";
	keyMaps.insert({ "PS4", pscontroller });

	ControlSystem keyboard;

	keyboard.controls = {
		{LEFT, std::make_pair(sf::Keyboard::A, sf::Keyboard::Unknown)},{RIGHT, std::make_pair(sf::Keyboard::D, sf::Keyboard::Unknown)},
		{SVM, std::make_pair(sf::Keyboard::W, sf::Keyboard::Unknown)},{JUMP, std::make_pair(sf::Keyboard::Space, sf::Keyboard::Unknown)},
		{FIRE, std::make_pair(sf::Mouse::Left, sf::Keyboard::Unknown)},{SHIELD, std::make_pair(sf::Mouse::Right, sf::Keyboard::Unknown)},
		{ACTIVE, std::make_pair(sf::Keyboard::E, sf::Keyboard::Unknown)},{AIM, std::make_pair(NONE, NONE)}
	};
	keyboard.controlType = "Keyboard";

	keyMaps.insert({ "Keyboard", keyboard });
}

void InputManager::Remap(sf::RenderWindow &window, Action action, bool primary, std::string mapkey)
{
	Event event;
	while (window.pollEvent(event))
	{
		unsigned int code = NULL;
		std::string key = "";

		if (keyMaps[mapkey].controlType == "keyboard")
		{
			if (event.type == sf::Event::KeyPressed)
			{
				code = event.key.code;
			}

			if (event.type == sf::Event::TextEntered)
			{
				key = (char)(event.text.unicode);
			}

			if (key == "")
			{
			}
		}
		else if (keyMaps[mapkey].controlType == "PS4")
		{
			if (event.type == sf::Event::JoystickButtonPressed)
			{
				code = event.joystickButton.button;
				key = ps4Controls.at((PS4)code);
			}
		}

		if (code != NULL)
		{
			if (primary)
				keyMaps["keyboard"].controls[action].first = code;
			else
				keyMaps["keyboard"].controls[action].second = code;
		}
	}
}

void InputManager::Update(double dt)
{
	for (int i = 0; i < 16; ++i)
	{
		if (buttonDown.test(i)) {
			buttonDown.reset(i);
		}
		if (buttonReleased.test(i)) {
			buttonReleased.reset(i);
		}
		if (sf::Joystick::isButtonPressed(0, i))
		{
			if (!buttonHeld.test(i)) {
				buttonDown.set(i);
				buttonHeld.set(i);
			}
		}
		else if (buttonHeld.test(i)) {
			buttonHeld.reset(i);
			buttonReleased.set(i);
		}
	}
	ButtonDebug();
}

bool InputManager::GetButtonDown(unsigned int action) {
	if ((activeControls.controls[action].first != -1 && buttonDown.test(activeControls.controls[action].first)) ||
		(activeControls.controls[action].second != -1 && buttonDown.test(activeControls.controls[action].second)))
		return true;
	return false;
}

bool InputManager::GetButtonHeld(unsigned int action) {
	if ((activeControls.controls[action].first != -1 && buttonHeld.test(activeControls.controls[action].first)) ||
		(activeControls.controls[action].second != -1 && buttonHeld.test(activeControls.controls[action].second)))
		return true;
	return false;
}

bool InputManager::GetButtonReleased(unsigned int action) {
	if ((activeControls.controls[action].first != -1 && buttonHeld.test(activeControls.controls[action].first)) ||
		(activeControls.controls[action].second != -1 && buttonHeld.test(activeControls.controls[action].second)))
		return true;
	return false;
}