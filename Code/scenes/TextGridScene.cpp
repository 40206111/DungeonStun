#include "TextGridScene.h"
#include "../Game.h"
#include "../SystemRenderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///ABSTRACT TEXT GRID SCENE///

TextGridScene::TextGridScene() {
	texts.push_back(&text);
	columns = texts.size();
	rows = texts[0]->size();

}

void TextGridScene::SpreadRatios(int count, std::vector<int>& ratios) {
	for (int& val : ratios) {
		val = 0;
	}
	ChangeOtherRatios(true, -1, 100, ratios);
}

// increase - True adds value, false takes it away
// index - the ratio to avoid, set to -1 to avoid none
// value - the value to distribute or remove
// ratios - the set of ratios to edit
void TextGridScene::ChangeOtherRatios(bool increase, int index, int value, std::vector<int>& ratios) {
	int k = (increase ? 1 : -1);
	int total = 0;
	while (total < value) {
		int change = (value - total) / (ratios.size() - (index >= 0 ? 1 : 0));
		for (int i = 0; i < ratios.size() && total < value; ++i) {
			if (i != index) {
				total += ChangeRatio(ratios[i], k * change);
			}
		}
	}
}

int TextGridScene::ChangeRatio(int& ratio, int change) {
	if (ratio + change < minRatio) {
		change = minRatio - ratio;
	}
	ratio += change;
	return change;
}

//Update method
void TextGridScene::Update(double dt)
{
	//update input
	player1->Update(dt);

	//if keyboard controls allow mouse input
	if (player1->activeControls.controlType == "keyboard")
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
	//Fullscreen window
	if (player1->GetButtonDown(player1->FULLSCREEN))
	{
		Renderer::ToggleFullscreen();
	}
	//Back
	if (player1->GetButtonDown(player1->BACK))
	{
		//set current to 0
		ChangeCurrent(0);
		//set active screen
		activeScene = previousScene;
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
			if (player1->activeControls.controlType == "PS4" && player1->controlerid == event.joystickMove.joystickId)
			{
				ChangeCurrent(0);
				//set active screen
				activeScene = homeScene;
			}
		}
	}
}

//render Method
void TextGridScene::Render()
{
	Vector2u screenSize = Renderer::GetWindow().getSize();
	float yPos = 0.0f;
	float xPos = 0.0f;
	Vector2f border = Vector2f((float)screenSize.x / 100.0f, (float)screenSize.y / 100.0f);
	for (int y = 0; y < rows; ++y) {
		float ySpace = (float)screenSize.y * (float)rowRatios[y] / 100.0f;
		float yMid = yPos + ySpace / 2.0f;
		for (int x = 0; x < columns; ++x) {
			float xSpace = (float)screenSize.x * (float)columnRatios[x] / 100.0f;
			float xMid = xPos + xSpace / 2.0f;

			Vector2f localpos = Vector2f(texts[x]->at(y).getLocalBounds().left, texts[x]->at(y).getLocalBounds().top);

			texts[x]->at(y).setPosition(Vector2f(xMid, yMid) - localpos);
			Renderer::Queue(&texts[x]->at(y));


			xPos += xSpace; // At end of loop only
		}
		yPos += ySpace; // At end of loop only
	}


	//render text
	//for (int i = 0; i < textAmount; ++i)
	//{
	//	text[i].setCharacterSize(Renderer::GetWindow().getSize().x / 10);

	//	float xval = (Renderer::GetWindow().getSize().x * 0.25);
	//	int co = i - textAmount / 2;
	//	float yval = Renderer::GetWindow().getSize().y * 0.5f;
	//	yval = yval + (co * space);
	//	//set text positions to fit screen
	//	text[i].setPosition(Vector2f(xval, yval) - Vector2f(text[i].getLocalBounds().left, text[i].getLocalBounds().top));

	//	Renderer::Queue(&text[i]);
	//}
}

void TextGridScene::CalculateSpaceX() {
	int count = 3; // Number to fit on screen by default
	float gap = Renderer::GetWindow().getSize().y / (textAmount < count ? (float)count + 1.0f : textAmount + 1);
	space = gap;
}

void TextGridScene::ChangeCurrentX(int value)
{
	int lastX = currentX;
	if (value < 0) {
		currentX = rows + (value % rows);
	}
	else if (value >= textAmount) {
		currentX = value % rows;
	}
	else {
		currentX = value;
	}
	if (currentX != lastX)
	{
		texts[lastX]->at(current).setColor(sf::Color::White);
		texts[currentX]->at(current).setColor(sf::Color::Yellow);
	}
}
