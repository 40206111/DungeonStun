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
	std::map<unsigned int, int> mouseControls;
};

//Input Manager Class
class InputManager
{
public:
	//PS4 Enum
	static enum PS4 { SQUARE, X, O, TRIANGLE, L1, R1, L2, R2, SELECT, START, LEFTA, RIGHTA, PS, TOUCH, NONE = -1};
	//Dpad Enum
	static enum Dir{ U, D, L, R};
	//Enum for actions
	static enum Action { LEFT, RIGHT, SVM, JUMP,
						AIM, FIRE, SHIELD, ACTIVE,
						MENUUP, MENUDOWN, MENULEFT, 
						MENURIGHT, BACK, ACCEPT,
						ACTIONSIZE}; //action size shows how many actions there are in the enum

	//string Controls
	static const std::map<PS4, std::string> ps4Controls;
	static const std::map<sf::Keyboard::Key, std::string> keyboardControls;

	//Control Systems
	std::map<std::string, ControlSystem> keyMaps;
	ControlSystem activeControls;

	//controller ID
	unsigned int controlerid = 0;
	
	//Constructor and Destructor
	InputManager();
	~InputManager() = default;

	//methods
	void Update(double dt);
	void Remap(sf::RenderWindow &window, Action action, bool primary, std::string mapKey);
	bool GetDpadDir(unsigned int jid, Dir dir);
	bool GetDigiAnalogue(unsigned int jid, Dir dir);
	bool GetAnaDown(Dir dir);
	bool GetAnaHeld(Dir dir);
	bool GetAnaReleased(Dir dir);
	bool GetButtonDown(unsigned int button);
	bool GetButtonHeld(unsigned int button);
	bool GetButtonReleased(unsigned int button);
protected:
	std::bitset<ACTIONSIZE> buttonDown;
	std::bitset<ACTIONSIZE> buttonHeld;
	std::bitset<ACTIONSIZE> buttonReleased;
	std::bitset<4> digiAnalogue;
	std::bitset<4> digiAnaHeld;
	std::bitset<4> digiAnaReleased;

	//methods
	void ButtonDebug();
	void CreateControlers();
};