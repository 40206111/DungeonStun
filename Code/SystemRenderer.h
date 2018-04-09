#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer
{
	void Initialise(sf::RenderWindow &);
	sf::RenderWindow &GetWindow();
	bool GetFullscreen();

	void Shutdown();
	void Update(const double &);
	void Queue(const sf::Drawable *s);
	void Render();
	void ToggleFullscreen();
};