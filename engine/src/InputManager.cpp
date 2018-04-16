#include "InputManager.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
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

//Keyboard controls to string
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
{ sf::Keyboard::Space, "SPACE" },
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

//ps4 controls to string
const std::map<InputManager::PS4, std::string> InputManager::ps4Controls = {
	{ InputManager::SQUARE, "SQUARE" },
	{ InputManager::X, "X" },
	{ InputManager::O, "CIRCLE" },
	{ InputManager::TRIANGLE, "TRIANGLE" },
	{ InputManager::L1, "L1" },
	{ InputManager::R1, "R1" },
	{ InputManager::L2, "L2" },
	{ InputManager::R2, "R2" },
	{ InputManager::SELECT, "SELECT" },
	{ InputManager::START, "START" },
	{ InputManager::LEFTA, "LEFT ANALOGUE IN" },
	{ InputManager::RIGHTA, "RIGHT ANOLOGUE IN" },
	{ InputManager::PS, "PLAY STATION" },
	{ InputManager::TOUCH, "TOUCH PAD" },
};

//Action string
const std::vector<string> InputManager::Actions{ "Left", "Right", "SVM", "Jump",
									"Aim", "Fire", "Sheild", "Active",
									"Menu Up", "Menu Down", "Menu Left",
									"MenuRight", "Back", "Accept",
									"Fullscreen", "Menu"};

//Input manager constructor
InputManager::InputManager()
{
	/// DEBUG///
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
	///END OF DEBUG
}

//method to output what has been pressed
void InputManager::ButtonDebug()
{
	// LEFT, RIGHT, SVM, JUMP, AIM, FIRE, SHIELD, ACTIVE, Back, Accept
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
	if (GetButtonDown(BACK))
	{
		cout << "BACK" << endl;
	}
	if (GetButtonDown(ACCEPT))
	{
		cout << "ACCEPT" << endl;
	}


}

// method to remap controls
bool InputManager::Remap(Action action, int primary, int key)
{
	Event event;
	//intitialise codes
	int code = -1;
	std::string pressed = "";
	bool kPressed = false;

	//poll events
	while (Renderer::GetWindow().pollEvent(event))
	{
		//check controller type
		if (keyMaps[key]->controlType == "keyboard")
		{
			//check if key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				code = event.key.code;
				kPressed = true;
				printf("%d\n", event.key.control);
			}

			//check if text entered
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode > 32 && event.text.unicode < 127)
				{
					int unic = event.text.unicode;
					//make character capital
					if (unic >= 97 && unic <= 122)
					{
						unic -= 32;
					}
					//exclude numbers
					if (unic < 48 || unic > 57)
					{
						pressed = static_cast<char>(unic);
					}
				}
			}

			//get mouse press
			if (!kPressed && event.type == sf::Event::MouseButtonPressed)
			{
				code = event.mouseButton.button;
				if (code == sf::Mouse::Left)
				{
					pressed = "LEFT MOUSE";
				}
				else if (code == sf::Mouse::Middle)
				{
					pressed = "MIDDLE MOUSE";
				}
				else if (code == sf::Mouse::Right)
				{
					pressed = "RIGHT MOUSE";
				}
				else
				{
					pressed = "MOUSE " + to_string(code);
				}
			}
		}
		if (keyMaps[key]->controlType == "PS4")
		{
			//check if joystick button pressed
			if (event.type == sf::Event::JoystickButtonPressed)
			{
				code = event.joystickButton.button;
				pressed = ps4Controls.at((PS4)code);
				kPressed = true;
			}
		}
	}
	//set text if nothing in key entered
	if ((code != -1 && kPressed) && (pressed.find_first_not_of(" \t\n\v\f\r") == std::string::npos || pressed == ""))
	{
		//set key sting to be that in keyboard map
		pressed = keyboardControls.at((sf::Keyboard::Key)code);
	}
	if (!kPressed)
	{
		if (GetDpadDir(controlerid, U))
		{
			code = U;
			pressed = "DPAD UP";
		}
		else if (GetDpadDir(controlerid, D))
		{
			code = D;
			pressed = "DPAD DOWN";
		}
		else if (GetDpadDir(controlerid, L))
		{
			code = L;
			pressed = "DPAD LEFT";
		}
		else if (GetDpadDir(controlerid, R))
		{
			code = R;
			pressed = "DPAD RIGHT";
		}

	}
	if (code != -1)
	{
		//set action to code
		if (kPressed)
		{
			if (primary == 1)
			{
				keyMaps[key]->controls[action].first = code;
				keyMaps[key]->controlWords[action].first = pressed;
			}
			else
			{
				keyMaps[key]->controls[action].second = code;
				keyMaps[key]->controlWords[action].second = pressed;
			}
			return true;
		}
		else
		{
			if (primary == 1)
			{
				keyMaps[key]->mouseControls[action] = code;
				keyMaps[key]->controlWords[action].first = pressed;
				if (keyMaps[key]->controls[action].first != -1)
				{
					keyMaps[key]->controls[action].first = -1;
				}
			}
			else
			{
				keyMaps[key]->controls[action].second = code;
				keyMaps[key]->controlWords[action].second = pressed;
				if (keyMaps[key]->controls[action].second != -1)
				{
					keyMaps[key]->controls[action].second = -1;
				}
			}
			return true;
		}
	}
	return false;
}

//Update method
void InputManager::Update(const double &dt)
{
	//loop through actions
	for (int i = 0; i < ACTIONSIZE; ++i)
	{
		//primary control
		int first = activeControls->controls[i].first;
		//secondary control
		int second = activeControls->controls[i].second;
		//check if button down
		if (buttonDown.test(i)) {
			buttonDown.reset(i);
		}
		//check if button released
		if (buttonReleased.test(i)) {
			buttonReleased.reset();
		}
		// check if primary button pressed
		if (first != -1 && (activeControls->controlType == "PS4" && sf::Joystick::isButtonPressed(controlerid, first) ||
			activeControls->controlType == "keyboard" && sf::Keyboard::isKeyPressed((sf::Keyboard::Key)first)))
		{
			// if action not held
			if (!buttonHeld.test(i)) {
				buttonDown.set(i);
				buttonHeld.set(i);
			}
		}
		// check if secondary button pressed
		else if (second != -1 && (activeControls->controlType == "PS4" && sf::Joystick::isButtonPressed(controlerid, second) ||
			activeControls->controlType == "keyboard" && sf::Keyboard::isKeyPressed((sf::Keyboard::Key)second)))
		{
			//check if action not held
			if (!buttonHeld.test(i)) {
				buttonDown.set(i);
				buttonHeld.set(i);
			}
		}
		//check if mouse controls are down
		else if (activeControls->mouseControls[i] != -1 &&
			(activeControls->controlType == "keyboard" && sf::Mouse::isButtonPressed((sf::Mouse::Button)activeControls->mouseControls[i]) ||
				activeControls->controlType == "PS4" && GetDpadDir(controlerid, (Dir)activeControls->mouseControls[i])))
		{
			//if aaction not held
			if (!buttonHeld.test(i)) {
				buttonDown.set(i);
				buttonHeld.set(i);
			}
		}
		// if button held
		else if (buttonHeld.test(i)) {
			buttonHeld.reset(i);
			buttonReleased.set(i);
		}
	}

	//loop through digital analogue stick directions
	for (int i = 0; i < 4; ++i)
	{
		// if analouge has been pushed in direction i
		if (digiAnalogue.test(i)) {
			digiAnalogue.reset(i);
		}
		// if analogue released from direction i
		if (digiAnaReleased.test(i)) {
			digiAnaReleased.reset();
		}
		// if analogue pushed in directicion i
		if (GetDigiAnalogue(controlerid, (Dir)i))
		{
			if (!digiAnaHeld.test(i)) {
				digiAnalogue.set(i);
				digiAnaHeld.set(i);
			}
		}
		// if analogue held in direction i
		else if (digiAnaHeld.test(i)) {
			digiAnaHeld.reset(i);
			digiAnaReleased.set(i);
		}
	}
	mMoved = mouseMoved();
	///DEBUG///
	ButtonDebug();
}

//Method to get if dPad has been pressed in direction
bool InputManager::GetDpadDir(unsigned int jid, Dir dir)
{
	// dpad x axis
	float povX = sf::Joystick::getAxisPosition(jid, sf::Joystick::PovX);
	// dpad y axis
	float povY = sf::Joystick::getAxisPosition(jid, sf::Joystick::PovY);

	switch (dir)
	{
	case U: //Up
		if (povY > 50)
		{
			return true;
		}
		break;
	case D: //Down
		if (povY < -50)
		{
			return true;
		}
		break;
	case L: //Left
		if (povX < -50)
		{
			return true;
		}
		break;
	case R: //Right
		if (povX > 50)
		{
			return true;
		}
		break;
	}
	return false;
}

//Method to get if anologue stick is pushed in cardinal direction
bool InputManager::GetDigiAnalogue(unsigned int jid, Dir dir)
{
	// analogue stick x axis
	float x = sf::Joystick::getAxisPosition(jid, sf::Joystick::X);
	// analogue stick y axis
	float y = sf::Joystick::getAxisPosition(jid, sf::Joystick::Y);

	switch (dir)
	{
	case U: //Up
		if (y < -50)
		{
			return true;
		}
		break;
	case D: //Down
		if (y > 50)
		{
			return true;
		}
		break;
	case L: //Left
		if (x < -50)
		{
			return true;
		}
		break;
	case R: //Right
		if (x > 50)
		{
			return true;
		}
		break;
	}
	return false;
}

//Method to check if analogue stick has been pushed in direction
bool InputManager::GetAnaDown(Dir dir)
{
	if (digiAnalogue.test(dir))
		return true;
	return false;
}
//Method to check if analogue stick is being held in direction
bool InputManager::GetAnaHeld(Dir dir)
{
	if (digiAnaHeld.test(dir))
		return true;
	return false;
}
//method to check if analogue stick has been released from direction
bool InputManager::GetAnaReleased(Dir dir)
{
	if (digiAnaReleased.test(dir))
		return true;
	return false;
}

//method to chek if button is down
bool InputManager::GetButtonDown(unsigned int action) {
	if (!(activeControls->controls[action].first == -1 && activeControls->controls[action].second == -1 && activeControls->mouseControls[action] == -1) &&
		buttonDown.test(action))
		return true;
	return false;
}

//method to check if button is held
bool InputManager::GetButtonHeld(unsigned int action) {
	if (!(activeControls->controls[action].first == -1 && activeControls->controls[action].second == -1 && activeControls->mouseControls[action] == -1) &&
		buttonHeld.test(action))
		return true;
	return false;
}

//method to check if button is released
bool InputManager::GetButtonReleased(unsigned int action) {
	if (!(activeControls->controls[action].first == -1 && activeControls->controls[action].second == -1 && activeControls->mouseControls[action] == -1) &&
		buttonReleased.test(action))
		return true;
	return false;
}

//Method to check if mouse is over text
bool InputManager::onText(sf::Text t)
{
	//get mouse positon
	Vector2i mousePos = sf::Mouse::getPosition(Renderer::GetWindow());

	//check if in bounds
	if (t.getGlobalBounds().contains(Vector2f(mousePos)))
	{
		return true;
	}

	return false;
}

//method to check if mouse has moved since last check
bool InputManager::mouseMoved()
{
	// if it has changed position return true
	if (lastMousePos != sf::Mouse::getPosition())
	{
		lastMousePos = sf::Mouse::getPosition();
		return true;
	}
	return false;
}

void InputManager::ChangeActive(int controlScheme)
{
	ControlSystem *newCont = keyMaps[controlScheme];
	activeControls = newCont;
	if (activeControls->controlType == "PS4")
	{
		primaryPS4 = newCont->mapKey;
	}
	else
	{
		primaryKeyboard = newCont->mapKey;
	}
}