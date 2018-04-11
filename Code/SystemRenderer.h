#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer
{

	static const std::vector<std::pair<uint16_t, uint16_t>> resolutions{
		std::make_pair(960,540), std::make_pair(1024,576),  std::make_pair(1152,648),
		std::make_pair(1280,720),  std::make_pair(1366,768),  std::make_pair(1600,900),
		std::make_pair(1920,1080)
	};
	extern unsigned int currentRes;

	void Initialise(sf::RenderWindow &);
	sf::RenderWindow &GetWindow();
	bool GetFullscreen();

	void Shutdown();
	void Update(const double &);
	void Queue(const sf::Drawable *s);
	void Render();
	void ToggleFullscreen();
	void setResolution(int res);
};