#include "InputManager.h"
#include "SystemRenderer.h"
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
	{ InputManager::LEFTA, "LEFT ANALOGUE" },
	{ InputManager::RIGHTA, "RIGHT ANOLOGUE" },
	{ InputManager::PS, "PLAY STATION" },
	{ InputManager::TOUCH, "TOUCH PAD" },
};

//Action string
const std::vector<string> InputManager::Actions{ "Left", "Right", "SVM", "Jump",
									"Aim", "Fire", "Sheild", "Active",
									"Menu Up", "Menu Down", "Menu Left",
									"MenuRight", "Back", "Accept",
									"Fullscreen"};

//Input manager constructor
InputManager::InputManager()
{
	InputManager::CreateControlers();

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

//method to create default controls
void InputManager::CreateControlers()
{
	//create playstation control system
	ControlSystem pscontroller;
	//set basic ps4 controls
	pscontroller.controls = {
		{LEFT, std::make_pair(NONE, NONE)},{RIGHT, std::make_pair(NONE, NONE)},
		{SVM, std::make_pair(R1, NONE)},{JUMP, std::make_pair(L1, O)},
		{FIRE, std::make_pair(R2, NONE)},{SHIELD, std::make_pair(L2, NONE)},
		{ACTIVE, std::make_pair(X, NONE)},{AIM, std::make_pair(NONE, NONE)},
		{MENUUP, std::make_pair(NONE, NONE)},{MENUDOWN, std::make_pair(NONE, NONE)},
		{MENULEFT, std::make_pair(NONE, NONE)},{MENURIGHT, std::make_pair(NONE, NONE)},
		{BACK, std::make_pair(O, NONE)},{ACCEPT, std::make_pair(X, NONE)},
		{FULLSCREEN, std::make_pair(START, NONE)}
	};
	pscontroller.controlType = "PS4";
	pscontroller.mouseControls = {
		{LEFT, L},{RIGHT, R},
		{SVM, U},{JUMP, NONE},
		{FIRE, NONE},{SHIELD, NONE},
		{ACTIVE, NONE},{AIM, NONE},
		{MENUUP, U}, {MENUDOWN, D},
		{MENULEFT, L}, {MENURIGHT, R},
		{BACK, NONE}, {ACCEPT, NONE},
		{FULLSCREEN, NONE}
	};
	keyMaps.push_back(pscontroller);
	keyMaps[keyMaps.size() - 1].mapKey = keyMaps.size() - 1;

	//create keyboard control system
	ControlSystem keyboard;
	//set basic keyboard controls
	keyboard.controls = {
		{LEFT, std::make_pair(sf::Keyboard::A, sf::Keyboard::Unknown)},{RIGHT, std::make_pair(sf::Keyboard::D, sf::Keyboard::Unknown)},
		{SVM, std::make_pair(sf::Keyboard::W, sf::Keyboard::Unknown)},{JUMP, std::make_pair(sf::Keyboard::Space, sf::Keyboard::Unknown)},
		{FIRE, std::make_pair(sf::Keyboard::Unknown, sf::Keyboard::Unknown)},{SHIELD, std::make_pair(sf::Keyboard::Unknown, sf::Keyboard::Unknown)},
		{ACTIVE, std::make_pair(sf::Keyboard::E, sf::Keyboard::Unknown)},{AIM, std::make_pair(sf::Keyboard::Unknown, sf::Keyboard::Unknown)},
		{MENUUP, std::make_pair(sf::Keyboard::W, sf::Keyboard::Up)},{MENUDOWN, std::make_pair(sf::Keyboard::S, sf::Keyboard::Down)},
		{MENULEFT, std::make_pair(sf::Keyboard::A, sf::Keyboard::Left)},{MENURIGHT, std::make_pair(sf::Keyboard::D, sf::Keyboard::Right)},
		{BACK, std::make_pair(sf::Keyboard::Escape, sf::Keyboard::Unknown)},{ACCEPT, std::make_pair(sf::Keyboard::Space, sf::Keyboard::Return)},
		{FULLSCREEN, std::make_pair(sf::Keyboard::F, sf::Keyboard::Unknown)}
	};
	keyboard.controlType = "keyboard";

	keyboard.mouseControls = {
		{LEFT, sf::Keyboard::Unknown},{RIGHT, sf::Keyboard::Unknown},
		{SVM, sf::Keyboard::Unknown},{JUMP, sf::Keyboard::Unknown},
		{FIRE, sf::Mouse::Left},{SHIELD, sf::Mouse::Right},
		{ACTIVE, sf::Keyboard::Unknown},{AIM, sf::Keyboard::Unknown},
		{MENUUP, sf::Keyboard::Unknown},{MENUDOWN, sf::Keyboard::Unknown },
		{MENULEFT, sf::Keyboard::Unknown},{MENURIGHT, sf::Keyboard::Unknown},
		{BACK, sf::Keyboard::Unknown},{ACCEPT, sf::Mouse::Left},
		{FULLSCREEN, sf::Keyboard::Unknown}
	};
	keyMaps.push_back(keyboard);
	keyMaps[keyMaps.size() - 1].mapKey = keyMaps.size() - 1;

}

// method to remap controls
void InputManager::Remap(Action action, bool primary, int key)
{
	Event event;
	//poll events
	while (Renderer::GetWindow().pollEvent(event))
	{
		//intitialise codes
		int code = -1;
		std::string pressed = "";

		//check controller type
		if (keyMaps[key].controlType == "keyboard")
		{
			//check if key pressed
			if (event.type == sf::Event::KeyPressed)
			{
				code = event.key.code;
			}

			//check if text entered
			if (event.type == sf::Event::TextEntered)
			{
				key = (char)(event.text.unicode);
			}

			//set text if nothing in key entered
			if (pressed.find_first_not_of(" \t\n\v\f\r") != std::string::npos)
			{
				//set key sting to be that in keyboard map
				pressed = keyboardControls.at((sf::Keyboard::Key)code);
			}
		}
		else if (keyMaps[key].controlType == "PS4")
		{
			//check if joystick button pressed
			if (event.type == sf::Event::JoystickButtonPressed)
			{
				code = event.joystickButton.button;
				pressed = ps4Controls.at((PS4)code);
			}
		}

		//set action to code
		if (code != -1)
		{
			if (primary)
				keyMaps[key].controls[action].first = code;
			else
				keyMaps[key].controls[action].second = code;
		}
	}
}

//Update method
void InputManager::Update(double dt)
{
	//loop through actions
	for (int i = 0; i < ACTIONSIZE; ++i)
	{
		//primary control
		int first = activeControls.controls[i].first;
		//secondary control
		int second = activeControls.controls[i].second;
		//check if button down
		if (buttonDown.test(i)) {
			buttonDown.reset(i);
		}
		//check if button released
		if (buttonReleased.test(i)) {
			buttonReleased.reset();
		}
		// check if primary button pressed
		if (first != -1 && (activeControls.controlType == "PS4" && sf::Joystick::isButtonPressed(controlerid, first) ||
			activeControls.controlType == "keyboard" && sf::Keyboard::isKeyPressed((sf::Keyboard::Key)first)))
		{
			// if action not held
			if (!buttonHeld.test(i)) {
				buttonDown.set(i);
				buttonHeld.set(i);
			}
		}
		// check if secondary button pressed
		else if (second != -1 && (activeControls.controlType == "PS4" && sf::Joystick::isButtonPressed(controlerid, second) ||
			activeControls.controlType == "keyboard" && sf::Keyboard::isKeyPressed((sf::Keyboard::Key)second)))
		{
			//check if action not held
			if (!buttonHeld.test(i)) {
				buttonDown.set(i);
				buttonHeld.set(i);
			}
		}
		//check if mouse controls are down
		else if (activeControls.mouseControls[i] != -1 &&
			(activeControls.controlType == "keyboard" && sf::Mouse::isButtonPressed((sf::Mouse::Button)activeControls.mouseControls[i]) ||
				activeControls.controlType == "PS4" && GetDpadDir(controlerid, (Dir)activeControls.mouseControls[i])))
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
	if (!(activeControls.controls[action].first == -1 && activeControls.controls[action].second == -1 && activeControls.mouseControls[action] == -1) &&
		buttonDown.test(action))
		return true;
	return false;
}

//method to check if button is held
bool InputManager::GetButtonHeld(unsigned int action) {
	if (!(activeControls.controls[action].first == -1 && activeControls.controls[action].second == -1) &&
		buttonHeld.test(action))
		return true;
	return false;
}

//method to check if button is released
bool InputManager::GetButtonReleased(unsigned int action) {
	if (!(activeControls.controls[action].first == -1 && activeControls.controls[action].second == -1) &&
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
		printf("%d : %d\n", mousePos.x, mousePos.y);
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