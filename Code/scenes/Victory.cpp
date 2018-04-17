#include "Victory.h"
#include "../Game.h"
#include "system_renderer.h"
#include "..\Components\cmp_sprite.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///HOME SCENE///

//Load method
void Victory::Load()
{
	//Load text
	text = sf::Text();
	text.setFont(font);
	text.setString(
		"Thank you for Working at\nOVERLORD INC.\nYou have been a wonderful temp\nIf a temp is needed\nwe'll be sure to ask for you in the future\n\nPAID: 25coins");

	ReSize();
}

void Victory::Update(const double &dt)
{
	//Exit
	if (player1->GetButtonDown(player1->ACCEPT))
	{
		Engine::ChangeMenu(nullptr);
		Engine::ChangeScene(homeScene);
	}

	//Poll events
	Event event;
	while (Renderer::GetWindow().pollEvent(event))
	{
		//if window closed
		if (event.type == Event::Closed)
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
			return;
		}
	}
}

//Render method
void Victory::Render()
{
	Renderer::Queue(Renderer::Layer::UIMID, &text);
}

void Victory::ReSize()
{
	//make text fit screen
	text.setCharacterSize(Renderer::GetWindow().getSize().x / 10);
	text.setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text.getGlobalBounds().width * 0.5f),
		Renderer::GetWindow().getSize().y - (text.getGlobalBounds().height) * 1.5);
}