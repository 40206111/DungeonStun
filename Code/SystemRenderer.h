#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer
{
	void Initialise(sf::RenderWindow &);
	sf::RenderWindow &GetWindow();

	void Shutdown();
	void Update(const double &);
	void Queue(const sf::Drawable *s);
	void Render();
};