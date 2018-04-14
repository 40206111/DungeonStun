#include "controlsScene.h"
#include "../Game.h"
#include "system_renderer.h"
#include "Serializer.h"
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

///SETTINGS SCENE///

//Load method
void ControlsScene::Load()
{
	if (!loaded)
	{
		//Load Text
		text.push_back(sf::Text());
		text[0].setFont(font);
		for (int i = 1; i < player1->ACTIONSIZE; i++)
		{
			text.push_back(sf::Text());
			text[i].setFont(font);
		}
		text.push_back(sf::Text());
		textAmount = text.size();
		text[textAmount - 1].setFont(font);
		previousScene = settingsScene;
		TextGridScene::Load();
		SetColumnCount(3);
		SpreadRatios(columns, columnRatios);
		SpreadRatios(rows, rowRatios);
		GetElement(0, textAmount - 1).setString("Back");
		GetElement(2, textAmount - 1).setString("Use");
		loaded = true;
	}
	text[0].setColor(sf::Color::Yellow);
	controlScheme = player1->activeControls->mapKey;
	GetElement(0, 0).setString(player1->keyMaps[controlScheme]->controlType + " " + to_string(controlScheme));
	for (int i = 1; i < player1->ACTIONSIZE; i++)
	{
		GetElement(0, i).setString(player1->Actions[i] + ":");
		GetElement(1, i).setString(player1->activeControls->controlWords[i].first);
		GetElement(2, i).setString(player1->activeControls->controlWords[i].second);
	}
	TextGridScene::ReSize();
}


//Update method
void ControlsScene::Update(const double &dt)
{
	if (remap)
	{	
		bool test = sf::Joystick::isConnected(player1->controlerid);
		if (action == player1->AIM || (!sf::Joystick::isConnected(player1->controlerid) && player1->keyMaps[controlScheme]->controlType == "PS4"))
		{
			GetElement(primary, action).setColor(sf::Color::Red);
			remap = false;
		}
		else
		{
			remap = !player1->Remap((InputManager::Action)(action), primary, controlScheme);
		}
		if (!remap)
		{
			wait = true;
			if (primary == 1)
			{
				GetElement(primary, action ).setString(player1->keyMaps[controlScheme]->controlWords[action].first);
			}
			else if (primary == 2)
			{
				GetElement(primary, action).setString(player1->keyMaps[controlScheme]->controlWords[action].second);
			}
			if (newSys)
			{
				player1->ChangeActive(controlScheme);
				GetElement(0, 0).setString(player1->keyMaps[controlScheme]->controlType + " " + to_string(controlScheme));
			}
		}
	}
	else if (wait) {
		wait = false;
	}
	else
	{
		TextGridScene::Update(dt);
		if (current == 0 && (player1->GetButtonDown(player1->MENURIGHT) || player1->GetAnaDown(player1->R)))
		{
			controlScheme += 1;
			if (controlScheme >= player1->keyMaps.size())
			{
				controlScheme = 0;
			}
			GetElement(0, 0).setString(player1->keyMaps[controlScheme]->controlType + " " + to_string(controlScheme));
			for (int i = 1; i < player1->ACTIONSIZE; i++)
			{
				GetElement(0, i).setString(player1->Actions[i] + ":");
				GetElement(1, i).setString(player1->keyMaps[controlScheme]->controlWords[i].first);
				GetElement(2, i).setString(player1->keyMaps[controlScheme]->controlWords[i].second);
			}
		}
		if (current == 0 && (player1->GetButtonDown(player1->MENULEFT) || player1->GetAnaDown(player1->L)))
		{
			controlScheme -= 1;
			if (controlScheme < 0)
			{
				controlScheme = player1->keyMaps.size() - 1;
			}
			GetElement(0, 0).setString(player1->keyMaps[controlScheme]->controlType + " " + to_string(controlScheme));
			for (int i = 1; i < player1->ACTIONSIZE; i++)
			{
				GetElement(0, i).setString(player1->Actions[i] + ":");
				GetElement(1, i).setString(player1->keyMaps[controlScheme]->controlWords[i].first);
				GetElement(2, i).setString(player1->keyMaps[controlScheme]->controlWords[i].second);
			}
		}
		//accept option
		if (player1->GetButtonDown(player1->ACCEPT))
		{
			if (currentX > 0 && current != 0 && current != textAmount - 1)
			{
				action = current;
				primary = currentX;
				if ((controlScheme == 0 || controlScheme == 1) && action != player1->AIM)
				{
					if (player1->keyMaps[controlScheme]->controlType == player1->activeControls->controlType)
						newSys = true;

					ControlSystem *newMap = new ControlSystem;
					*newMap = *player1->keyMaps[controlScheme];
					player1->keyMaps.push_back(newMap);
					player1->keyMaps[player1->keyMaps.size() - 1]->mapKey = player1->keyMaps.size() - 1;
					controlScheme = player1->keyMaps.size() - 1;
				}
				else
				{
					newSys = false;
				}
				remap = true;
			}
			if (current == textAmount - 1 && currentX == 0)
			{
				ChangeCurrent(0);
				Reset();
			Engine::ChangeMenu(previousScene);
			}
			if ((current == textAmount - 1 && currentX == 2))
			{
				ControlSystem *newCont = player1->keyMaps[controlScheme];
				if (newCont->controlType == "PS4" && !sf::Joystick::isConnected(player1->controlerid))
				{
					GetElement(2, textAmount - 1).setColor(sf::Color::Red);
				}
				else
				{
					player1->ChangeActive(controlScheme);
					GetElement(2, textAmount - 1).setColor(sf::Color::Green);
				}
			}
		}
	}
}

//render Method
void ControlsScene::Render()
{
	TextGridScene::Render();
}

void ControlsScene::UnLoad()
{
	TextGridScene::UnLoad();
	Serializer::Serialize("Assets/save/player1.txt", *player1);
}