#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class TextScene : public Scene
{
protected:
	std::vector<sf::Text> text;
	int textAmount;
	float space;
	//currently selected
	int current = 0;
	std::shared_ptr<Scene> previousScene;
	
	void CalculateSpace();
	virtual void ChangeCurrent(int);
public:
	TextScene() = default;
	void Update(double dt) override;
	void Render() override;
};
