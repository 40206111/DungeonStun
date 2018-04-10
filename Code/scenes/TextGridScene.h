#pragma once
#include "TextScene.h"
#include <SFML/Graphics.hpp>

class TextGridScene : public TextScene
{
protected:
	int currentX = 0;
	std::vector<std::vector<sf::Text>*> texts;
	int columns;
	int rows;
	std::vector<int> columnRatios;
	int columnTotal = 0;
	std::vector<int> rowRatios;
	int rowTotal = 0;
	int minRatio = 5;
	int maxIndex = 100 / minRatio;
	bool stealUp = false;

	void ChangeCurrentX(int);
	void CalculateSpaceX();

	void SpreadRatios(int count, std::vector<int>& ratios);
	void ChangeOtherRatios(bool increase, int index, int value, std::vector<int>& ratios);
	int ChangeRatio(int& ratio, int change);

public:
	int GetRowRatio(int row) { return rowRatios[row]; }
	int GetRowCount() { return rows; }
	int GetColumnRatio(int column) { return columnRatios[column]; }
	int GetColumnCount() { return columns; }
	sf::Text& GetElement(int column, int row) { return texts[column]->at(row); }

	void SetRowRatio(int column, int ratio);
	void SetRowCount(int value);
	void SetColumnRatio(int column, int ratio);
	void SetColumnCount(int value);
	void SetElement(int column, int row, const sf::Text&);

	TextGridScene() = default;
	void Update(double dt) override;
	void Render() override;
};
