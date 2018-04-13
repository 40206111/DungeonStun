#pragma once
#include "textScene.h"
#include <SFML/Graphics.hpp>

class GraphicsScene : public TextScene
{
private:
	bool fullscreen;
	int shownRes;
public:
	GraphicsScene() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void Reset() override;
};
