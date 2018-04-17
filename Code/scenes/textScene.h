#pragma once
#include "engine.h"
#include <SFML/Graphics.hpp>

class TextScene : public Scene
{
protected:
	bool loaded = false;
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
	void Load() override;
	void Update(const double &dt) override;
	void Render() override;
	void UnLoad() override;
	void ReSize() override;
};
