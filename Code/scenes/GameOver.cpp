#include "GameOver.h"
#include "../Game.h"
#include "system_renderer.h"
#include "..\Components\cmp_sprite.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///HOME SCENE///

//Load method
void GameOver::Load()
{
	//Load text
	text = sf::Text();
	text.setFont(font);
	text.setString("GAME OVER");
	text.setColor(Color::Red);

	ReSize();
}

void GameOver::Update(const double &dt)
{
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
void GameOver::Render()
{
	Renderer::Queue(Renderer::Layer::UIMID, &text);
}

void GameOver::ReSize()
{
	//make text fit screen
	text.setCharacterSize(Renderer::GetWindow().getSize().x / 10);
	text.setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text.getGlobalBounds().width * 0.5f),
		Renderer::GetWindow().getSize().y * 0.5f - (text.getGlobalBounds().height * 2));
}