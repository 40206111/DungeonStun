#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <bitset>

//Control System struct
struct ControlSystem {
	//map of controls
	std::map<unsigned int, std::pair<int, int>> controls;
	//string for control type
	std::string controlType;
};

//Input Manager Class
class InputManager
{
public:
	//PS4 Enum
	static enum PS4 { SQUARE, X, O, TRIANGLE, L1, R1, L2, R2, SELECT, START, LEFTA, RIGHTA, PS, TOUCH, NONE = -1};
	//Enum for actions
	static enum Action { LEFT, RIGHT, SVM, JUMP, AIM, FIRE, SHIELD, ACTIVE };

	//string Controls
	static const std::map<PS4, std::string> ps4Controls;
	static const std::map<sf::Keyboard::Key, std::string> keyboardControls;

	//Control Systems
	std::map<std::string, ControlSystem> keyMaps;
	
	//Constructor and Destructor
	InputManager();
	~InputManager() = default;

	//methods
	void Update(double dt);
	void Remap(sf::RenderWindow &window, Action action, bool primary, std::string mapKey);
	bool GetButtonDown(unsigned int button);
	bool GetButtonHeld(unsigned int button);
	bool GetButtonReleased(unsigned int button);
protected:
	std::bitset<16> buttonDown;
	std::bitset<16> buttonHeld;
	std::bitset<16> buttonReleased;
	
	ControlSystem activeControls;

	//methods
	void ButtonDebug();
	void CreateControlers();
};