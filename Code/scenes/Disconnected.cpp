#include "disconnected.h"
#include "../Game.h"
#include "system_renderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///CONTROLLER DISCONNECTED SCENE///

//Load method
void Disconnected::Load()
{
	if (!loaded)
	{
		//Load Text
		discont = sf::Text();
		discont.setFont(font);
		discont.setString("Controller Disconnected");
		discont.setColor(sf::Color::Red);
	}
	//make text fit screen
	discont.setCharacterSize(Renderer::GetWindow().getSize().x / 10);
	discont.setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (discont.getLocalBounds().width * 0.5f),
		Renderer::GetWindow().getSize().y - (discont.getLocalBounds().height * 4));
	loaded = true;
}

void Disconnected::Update(const double &dt)
{
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
		if (event.type == sf::Event::JoystickConnected)
		{
			player1->controlerid = event.joystickConnect.joystickId;
			Engine::ChangeMenu(menuScene);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		Engine::ChangeMenu(menuScene);
		player1->activeControls = player1->keyMaps[player1->primaryKeyboard];
	}

}

//Render Method
void Disconnected::Render()
{
	Renderer::Queue(Renderer::Layer::UIMID, &discont);
}

void Disconnected::UnLoad() {
}
