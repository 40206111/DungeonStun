#include "textScene.h"
#include "../Game.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///ABSTRACT TEXT SCENE///

void TextScene::Load()
{
	ReSize();
}

//Update method
void TextScene::Update(const double &dt)
{
	//if keyboard controls allow mouse input
	if (player1->activeControls->controlType == "keyboard")
	{
		for (int i = 0; i < textAmount; ++i)
		{
			//if mouse over text 0
			if (player1->mMoved && player1->onText(text[i]))
			{
				ChangeCurrent(i);
			}
		}
	}

	//if menu down
	if (player1->GetButtonDown(player1->MENUDOWN) || player1->GetAnaDown(player1->D))
	{
		//loop round text
		ChangeCurrent(current + 1);
	}
	if (player1->GetButtonDown(player1->MENUUP) || player1->GetAnaDown(player1->U))
	{
		//loop round text
		ChangeCurrent(current - 1);
	}
	//Back
	if (player1->GetButtonDown(player1->BACK))
	{
		//set active screen
		Engine::ChangeMenu(previousScene);
	}

	//poll events
	Event event;
	while (Renderer::GetWindow().pollEvent(event))
	{
		//Close window
		if (event.type == Event::Closed)
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
			return;
		}
		//If controller disconected
		if (event.type == sf::Event::JoystickDisconnected)
		{
			if (player1->activeControls->controlType == "PS4" && player1->controlerid == event.joystickMove.joystickId)
			{
				ChangeCurrent(0);
				//set active screen
				Engine::ChangeMenu(disconnected);
			}
		}
	}
}

//render Method
void TextScene::Render()
{
	//set text positions to fit screen
	for (int i = 0; i < textAmount; ++i)
	{
		//render text
		Renderer::Queue(&text[i]);
	}
}

void TextScene::CalculateSpace() {
	int count = 8; // Number to fit on screen by default
	float gap = Renderer::GetWindow().getSize().y / (textAmount < count ? (float)count + 1.0f : textAmount + 1);
	space = gap;
}

void TextScene::ChangeCurrent(int value) 
{
	int lastCurrent = current;
	if (value < 0) {
		current = textAmount + (value % textAmount);
	}
	else if (value >= textAmount) {
		current = value % textAmount;
	}
	else {
		current = value;
	}
	if (current != lastCurrent)
	{
		text[lastCurrent].setColor(sf::Color::White);
		text[current].setColor(sf::Color::Yellow);
	}
}

void TextScene::UnLoad() {
	//set current to 0
	ChangeCurrent(0);
}
void TextScene::ReSize()
{
	CalculateSpace();
	for (int i = 0; i < textAmount; ++i)
	{
		text[i].setCharacterSize(Renderer::GetWindow().getSize().x / 10);

		float xval = (Renderer::GetWindow().getSize().x * 0.25);
		int co = i - textAmount / 2;
		float yval = Renderer::GetWindow().getSize().y * 0.5f;
		yval = yval + (co * space);
		text[i].setPosition(Vector2f(xval, yval) - Vector2f(text[i].getLocalBounds().left, text[i].getLocalBounds().top));
		if (false) {
			Vector2f globPos = Vector2f(text[i].getGlobalBounds().left, text[i].getGlobalBounds().top);
			Vector2f posPos = text[i].getPosition();
			Vector2f locPos = Vector2f(text[i].getLocalBounds().left, text[i].getLocalBounds().top);
		}
	}
}