#include "TextGridScene.h"
#include "../Game.h"
#include "../SystemRenderer.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

///ABSTRACT TEXT GRID SCENE///

void TextGridScene::Load() {
	texts.push_back(&text);
	columns = texts.size();
	rows = texts[0]->size();
	for (int i = 0; i < columns; ++i) {
		columnRatios.push_back(0);
	}
	for (int i = 0; i < rows; ++i) {
		rowRatios.push_back(0);
	}
	SpreadRatios(columns, columnRatios);
	SpreadRatios(rows, rowRatios);
}
// Equally spread out ratios in list
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
	int loopCount = 0;
	while (total < value && loopCount < 4) {
		int change = (value - total) / (ratios.size() - (index >= 0 ? 1 : 0));
		for (int i = 0; i < ratios.size() && total < value; ++i) {
			if (i != index) {
				total += k * ChangeRatio(ratios[i], k * change);
			}
		}
		loopCount++;
	}
	if (total != value && index >= 0) {
		int shortfall = value - total;
		ChangeRatio(ratios[index], k * shortfall);
	}
}
// Change the value of one specific ratio
int TextGridScene::ChangeRatio(int& ratio, int change) {
	if (ratio + change < minRatio) {
		change = minRatio - ratio;
	}
	ratio += change;
	return change;
}
// Fix ratios if they don't make 100
void TextGridScene::VerifyRatios() {
	int total;
	vector<int>& ratios = rowRatios;
	for (int i = 0; i < 2; ++i) {
		total = 0;
		for (int val : ratios) {
			total += val;
		}
		if (total != 100) {
			int diff = 100 - total;
			ChangeOtherRatios((diff > 0), -1, (int)fabsf(diff), ratios);
		}
		ratios = columnRatios;
	}
}

void TextGridScene::SetRowRatio(int row, int value) {
	if (!(row < rows)) {
		return;
	}
	int before = rowRatios[row];
	rowRatios[row] = value;
	int diff = rowRatios[row] - before;
	ChangeOtherRatios((diff > 0), row, (int)abs(diff), rowRatios);
	VerifyRatios();
}
void TextGridScene::SetColumnRatio(int column, int value) {
	if (!(column < columns)) {
		return;
	}
	int before = columnRatios[column];
	columnRatios[column] = value;
	int diff = columnRatios[column] - before;
	ChangeOtherRatios((diff > 0), column, (int)abs(diff), columnRatios);
	VerifyRatios();
}

void TextGridScene::SetRowCount(int value) {
	if (rows > value) {
		int excess = rows - value;
		for (vector<Text>* vec : texts) {
			for (int i = 0; i < excess; ++i) {
				vec->pop_back();
			}
		}
		for (int i = 0; i < excess; ++i) {
			rowRatios.pop_back();
		}
	}
	else if (rows < value) {
		Text basic = Text();
		basic.setFont(font);
		basic.setString("-");
		int shortfall = value - rows;
		for (vector<Text>* vec : texts) {
			for (int i = 0; i < shortfall; ++i) {
				Text* copy = new Text();
				*copy = basic;
				vec->push_back(*copy);
			}
		}
		for (int i = 0; i < shortfall; ++i) {
			rowRatios.push_back(0);
			SetRowRatio(rowRatios.size() - 1, 0);
		}
	}
	rows = value;
}
void TextGridScene::SetColumnCount(int value) {
	if (columns > value) {
		int excess = columns - value;
		for (int i = 0; i < excess; ++i) {
			texts.pop_back();
		}
		for (int i = 0; i < excess; ++i) {
			columnRatios.pop_back();
		}
	}
	else if (columns < value) {
		Text basic = Text();
		basic.setFont(font);
		basic.setString("");
		int shortfall = value - columns;
		for (int i = 0; i < shortfall; ++i) {
			vector<Text>* column = new vector<Text>();
			for (int i = 0; i < rows; ++i) {
				Text* copy = new Text();
				copy->setFont(font);
				copy->setString("");
				column->push_back(*copy);
			}
			texts.push_back(column);
		}
		for (int i = 0; i < shortfall; ++i) {
			columnRatios.push_back(0);
			SetColumnRatio(columnRatios.size() - 1, 0);
		}
	}
	columns = value;
}
// Set element as a text object
bool TextGridScene::SetElement(int column, int row, const Text& text) {
	if (column < columns && row < rows) {
		texts[column]->at(row) = text;
		return true;
	}
	return false;
}
//Update method
void TextGridScene::Update(double dt)
{
	// store current
	int currWatch = current;
	TextScene::Update(dt);
	//check current
	if (currWatch != current && currentX != 0) {
		while (GetElement(currentX, current).getString() == "")
		{
			int value = currentX - 1;
			if (value < 0) {
				currentX = columns + (value % columns);
			}
			else
			{
				currentX = value;
			}
		}
		// respond to change
		GetElement(currentX, current).setColor(Color::White);
		int newCurr = current;
		current = currWatch;
		ChangeCurrent(newCurr);
	}

	//if keyboard controls allow mouse input
	if (player1->activeControls->controlType == "keyboard")
	{
		for (int i = 0; i < columns; ++i) {
			for (int j = 0; j < rows; ++j)
			{
				//if mouse over text 0
				if (player1->mMoved && player1->onText(GetElement(i, j)))
				{
					ChangeCurrentBoth(i, j);
				}
			}
		}
	}

	//if menu down
	if (player1->GetButtonDown(player1->MENURIGHT) || player1->GetAnaDown(player1->R))
	{
		//loop round text
		ChangeCurrentX(currentX + 1);
	}
	if (player1->GetButtonDown(player1->MENULEFT) || player1->GetAnaDown(player1->L))
	{
		//loop round text
		ChangeCurrentX(currentX - 1);
	}
}
//render Method
void TextGridScene::Render()
{
	Vector2u screenSize = Renderer::GetWindow().getSize();
	float yPos = 0.0f;
	float xPos = 0.0f;
	Vector2f border = Vector2f((float)screenSize.x / 100.0f, (float)screenSize.y / 100.0f);
	for (int x = 0; x < columns; ++x) {
		float xSpace = (float)screenSize.x * (float)columnRatios[x] / 100.0f;
		//float xMid = xPos + xSpace / 2.0f;
		float xMid = xPos + border.x;
		for (int y = 0; y < rows; ++y) {
			float ySpace = (float)screenSize.y * (float)rowRatios[y] / 100.0f;
			//float yMid = yPos + ySpace / 2.0f;
			float yMid = yPos + border.y;
			if (x == 0) {
				xMid = xPos + xSpace - GetElement(x, y).getGlobalBounds().width - border.x;
			}

			Vector2f localpos = Vector2f(texts[x]->at(y).getLocalBounds().left, texts[x]->at(y).getLocalBounds().top);

			texts[x]->at(y).setPosition(Vector2f(xMid, yMid) - localpos);
			texts[x]->at(y).setCharacterSize(Renderer::GetWindow().getSize().x / (rows > 10 ? rows : 10));
			Renderer::Queue(&texts[x]->at(y));


			yPos += ySpace; // At end of loop only
		}
		yPos = 0.0f;
		xPos += xSpace; // At end of loop only
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
// Change row highlighting
void TextGridScene::ChangeCurrent(int value) {
	int lastY = current;
	if (value < 0) {
		current = rows + (value % rows);
	}
	else if (value >= columns) {
		current = value % rows;
	}
	else {
		current = value;
	}
	if (current != lastY)
	{
		texts[currentX]->at(lastY).setColor(sf::Color::White);
		texts[currentX]->at(current).setColor(sf::Color::Yellow);
	}
}
// Change column highlighting
void TextGridScene::ChangeCurrentX(int value)
{
	int lastX = currentX;
	if (value < 0) {
		currentX = columns + (value % columns);
	}
	else if (value >= columns) {
		currentX = value % columns;
	}
	else {
		currentX = value;
	}
	if (texts[currentX]->at(current).getString() == "")
	{
		ChangeCurrentX(currentX + 1);
		if (currentX == lastX)
		{
			ChangeCurrentX(currentX - 2);
		}
	}
	if (currentX != lastX)
	{
		texts[lastX]->at(current).setColor(sf::Color::White);
		texts[currentX]->at(current).setColor(sf::Color::Yellow);
	}
}
// Change row and column highlight
void TextGridScene::ChangeCurrentBoth(int valX, int valY) {
	ChangeCurrent(valY);
	ChangeCurrentX(valX);
}
