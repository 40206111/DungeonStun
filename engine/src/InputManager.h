#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <list>
#include <bitset>

//Control System struct
struct ControlSystem {
	//map of controls
	std::map<unsigned int, std::pair<int, int>> controls;
	//string for control type
	std::string controlType;
	int mapKey;
	std::map<unsigned int, int> mouseControls;
	std::map<unsigned int, std::pair<std::string, std::string>> controlWords;
};

//Input Manager Class
class InputManager
{
public:
	//PS4 Enum
	enum PS4 { SQUARE, X, O, TRIANGLE, L1, R1, L2, R2, SELECT, START, LEFTA, RIGHTA, PS, TOUCH, NONE = -1};
	//Dpad Enum
	enum Dir{ U, D, L, R};
	//Enum for actions
	enum Action { LEFT, RIGHT, SVM, JUMP,
						AIM, FIRE, SHIELD, ACTIVE,
						MENUUP, MENUDOWN, MENULEFT, 
						MENURIGHT, BACK, ACCEPT,
						FULLSCREEN, MENU, ACTIONSIZE}; //action size shows how many actions there are in the enum

	static const std::vector<std::string> Actions;

	//string Controls
	static const std::map<PS4, std::string> ps4Controls;
	static const std::map<sf::Keyboard::Key, std::string> keyboardControls;

	//Control Systems
	std::vector<ControlSystem*> keyMaps;
	ControlSystem *activeControls = nullptr;

	//controller ID
	unsigned int controlerid = 0;
	unsigned int primaryPS4 = 0;
	unsigned int primaryKeyboard = 1;
	
	//Constructor and Destructor
	InputManager();
	~InputManager() = default;

	//mouse moved bool
	bool mMoved = false;

	//methods
	bool Remap(Action action, int primary, int key);
	void Update(const double &dt);
	bool GetDpadDir(unsigned int jid, Dir dir);
	bool GetDigiAnalogue(unsigned int jid, Dir dir);
	bool GetAnaDown(Dir dir);
	bool GetAnaHeld(Dir dir);
	bool GetAnaReleased(Dir dir);
	bool GetButtonDown(unsigned int button);
	bool GetButtonHeld(unsigned int button);
	bool GetButtonReleased(unsigned int button);
	bool onText(sf::Text t);
	void ChangeActive(int controlScheme);
protected:
	//bools for button presses
	std::bitset<ACTIONSIZE> buttonDown;
	std::bitset<ACTIONSIZE> buttonHeld;
	std::bitset<ACTIONSIZE> buttonReleased;
	std::bitset<4> digiAnalogue;
	std::bitset<4> digiAnaHeld;
	std::bitset<4> digiAnaReleased;

	//mouse position
	sf::Vector2i lastMousePos;

	//methods
	void ButtonDebug();
	void CreateControlers();
	bool mouseMoved();
};