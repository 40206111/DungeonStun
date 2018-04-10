#pragma once
#include "textScene.h"
#include <SFML/Graphics.hpp>

class GraphicsScene : public TextScene
{
private:
	bool fullscreen;
public:
	GraphicsScene() = default;
	void Update(double dt) override;
	void Render() override;
	void Load() override;
};
