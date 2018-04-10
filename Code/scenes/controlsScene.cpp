#include "controlsScene.h"
#include "../Game.h"
#include "../SystemRenderer.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

///SETTINGS SCENE///

//Load method
void ControlsScene::Load()
{
	//Load Text

	text.push_back(sf::Text());
	text[0].setString("CONTROLS");
	text[0].setFont(font);
	text[0].setColor(sf::Color::Yellow);
	for (int i = 1; i < player1->ACTIONSIZE; i++)
	{
		text.push_back(sf::Text());
		text[i].setFont(font);
	}
	text.push_back(sf::Text());
	textAmount = text.size();
	text[textAmount - 1].setString("Back");
	text[textAmount - 1].setFont(font);
	previousScene = settingsScene;
}


//Update method
void ControlsScene::Update(double dt)
{
	if (text[0].getString() == "CONTROLS")
	{
	}
	TextScene::Update(dt);

	//accept option
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		if (current == textAmount - 1)
		{
			ChangeCurrent(0);
			Reset();
			activeScene = previousScene;
		}
	}
}

//render Method
void ControlsScene::Render()
{
	TextScene::Render();
}

void ControlsScene::Reset()
{
	text[0].setString(player1->keyMaps[player1->activeControls.mapKey].controlType + " " + to_string(player1->activeControls.mapKey));
	for (int i = 1; i < player1->ACTIONSIZE; i++)
	{
		string theText = player1->Actions[i] + ": ";
		if (player1->keyMaps[player1->activeControls.mapKey].controlType == "keyboard")
		{
			if (player1->keyboardControls.find((sf::Keyboard::Key)(player1->activeControls.controls[i].first)) == player1->keyboardControls.end())
			{
				theText += " ";
			}
			else if ((player1->activeControls.controls[i].first) != -1)
			{
				theText += player1->keyboardControls.at((sf::Keyboard::Key)(player1->activeControls.controls[i].first));
			}
			else
			{
				theText += "-";
			}
			theText += "\t";
			if (player1->keyboardControls.find((sf::Keyboard::Key)(player1->activeControls.controls[i].second)) == player1->keyboardControls.end())
			{
				//theText += char(player1->activeControls.controls[i].second);
			}
			else if ((player1->activeControls.controls[i].second) != -1)
			{
				theText += player1->keyboardControls.at((sf::Keyboard::Key)(player1->activeControls.controls[i].second));
			}
			else
			{
				theText += "-";
			}
		}
		else if (player1->keyMaps[player1->activeControls.mapKey].controlType == "PS4")
		{

			if ((player1->activeControls.controls[i].first) != -1)
			{
				theText += player1->ps4Controls.at((InputManager::PS4)(player1->activeControls.controls[i].first));
			}
			else
			{
				theText += "-";
			}
			theText += "\t";
			if ((player1->activeControls.controls[i].second) != -1)
			{
				theText += player1->ps4Controls.at((InputManager::PS4)(player1->activeControls.controls[i].second));
			}
			else
			{
				theText += "-";
			}
		}

		text[i].setString(theText);
	}
}