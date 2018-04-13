#pragma once
#include "TextGridScene.h"
#include <SFML/Graphics.hpp>

class ControlsScene : public TextGridScene
{
private:
	int controlScheme;
	bool remap = false;
	int action = -1;
	int primary = 1;
	bool newSys = false;
public:
	ControlsScene() = default;
	void Update(const double &dt) override;
	void Render() override;
	void Load() override;
	void UnLoad() override;
	void Reset() override;
};