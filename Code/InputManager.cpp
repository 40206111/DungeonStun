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

void InputManager::Update(double dt)
{
	if (sf::Joystick::isButtonPressed(0, SQUARE))
	{
		cout << "SQUARE" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, X))
	{
		cout << "X" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, O))
	{
		cout << "O" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, TRIANGLE))
	{
		cout << "TRIANGLE" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, L1))
	{
		cout << "L1" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, R1))
	{
		cout << "R1" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, L2))
	{
		cout << "L2" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, R2))
	{
		cout << "R2" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, SELECT))
	{
		cout << "SELECT" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, START))
	{
		cout << "START" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, LEFTA))
	{
		cout << "LEFTA" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, RIGHTA))
	{
		cout << "RIGHTA" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, PS))
	{
		cout << "PS" << endl;
	}
	if (sf::Joystick::isButtonPressed(0, TOUCH))
	{
		cout << "TOUCH" << endl;
	}

}