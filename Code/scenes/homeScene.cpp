#include "homeScene.h"
#include "../Game.h"
#include "system_renderer.h"
#include "..\Components\cmp_sprite.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///HOME SCENE///

//Load method
void HomeScene::Load()
{
	//Make screen
	screen = makeEntity();
	screen->setVisible(false);
	screen->setPosition(Vector2f(0, 0));
	auto s = screen->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(Renderer::GetWindow().getSize()));
	s->getShape().setFillColor(Color(0, 0, 0, 200));
	//load background
	if (!homescreen.loadFromFile("Assets/imgs/9 to die home.png")) {}
	background = sf::Sprite(homescreen);
	//Load text
	text = sf::Text();
	text.setFont(font);
	text.setString("Press Any Button To Continue");

	ReSize();

	showBehind = true;
}

void HomeScene::Update(const double &dt)
{
	if (player1->activeControls != nullptr)
	{
		//Exit
		if (player1->GetButtonDown(player1->BACK))
		{
			Renderer::Shutdown();
			Renderer::GetWindow().close();
		}
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

		///check if any key is pressed///
		bool anyKey = false;
		int testVal = -1;
		//if controller button pressed
		if (event.type == sf::Event::JoystickButtonPressed)
		{
			player1->controlerid = event.joystickMove.joystickId;
			player1->activeControls = player1->keyMaps[player1->primaryPS4];
			anyKey = true;
			testVal = event.key.alt;
		}

		//if keyboard key pressed
		if (event.type == sf::Event::KeyPressed)
		{
			player1->activeControls = player1->keyMaps[player1->primaryKeyboard];
			anyKey = true;
			testVal = event.key.code;
		}

		// if any key pressed
		if (anyKey) {
			//exit if back pressed
			if (testVal == player1->activeControls->controls[player1->BACK].first
				|| testVal == player1->activeControls->controls[player1->BACK].second)
			{
				Renderer::Shutdown();
				Renderer::GetWindow().close();
			}
			//next scene if not fullscreen
			if (testVal != player1->activeControls->controls[player1->FULLSCREEN].first
				|| testVal != player1->activeControls->controls[player1->FULLSCREEN].second)
			{
				player1->Update(dt);
				Engine::ChangeMenu(menuScene);
			}
		}
	}
}

//Render method
void HomeScene::Render()
{
	//Render Background
	Renderer::Queue(&background);

	if (!Engine::ShowingMenu()) {
		//render text
		Renderer::Queue(&text);
		screen->setVisible(false);
		Scene::Render();
	}
	else if (showBehind) {
		screen->setVisible(true);
		Scene::Render();
	}
}

void HomeScene::UnLoad()
{

}

void HomeScene::ReSize()
{
	//make background fit screen
	background.setScale(
		Renderer::GetWindow().getSize().x / background.getLocalBounds().width,
		Renderer::GetWindow().getSize().y / background.getLocalBounds().height);

	//make text fit screen
	text.setCharacterSize(Renderer::GetWindow().getSize().x / 10);
	text.setPosition((Renderer::GetWindow().getSize().x * 0.5f) - (text.getLocalBounds().width * 0.5f),
		Renderer::GetWindow().getSize().y - (text.getLocalBounds().height * 4));

	auto s = screen->get_components<ShapeComponent>()[0];
	s->setShape<RectangleShape>(Vector2f(Renderer::GetWindow().getSize()));
	s->getShape().setFillColor(Color(0, 0, 0, 200));
}