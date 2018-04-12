
unsigned int Renderer::currentRes = 3;

//#include "system_renderer.h"
//#include "Game.h"
//#include <queue>
//
//using namespace std;
//using namespace sf;
//
//static queue<const Drawable *> sprites;
//static RenderWindow *rw;
//static bool fullscreen = false;
//
//void Renderer::Initialise(sf::RenderWindow &r) { rw = &r;  }
//
//sf::RenderWindow & Renderer::GetWindow() { return *rw; }
//bool Renderer::GetFullscreen() { return fullscreen; }
//
//void Renderer::Shutdown()
//{
//	while (!sprites.empty())
//		sprites.pop();
//}
//
//void Renderer::Update(const double &) 
//{}
//
//void Renderer::Render()
//{
//	if (rw == nullptr)
//	{
//		throw("No render window set! ");
//	}
//	while (!sprites.empty())
//	{
//		rw->draw(*sprites.front());
//		sprites.pop();
//	}
//}
//
//void Renderer::Queue(const sf::Drawable *s) { sprites.push(s); }
//
//void Renderer::ToggleFullscreen()
//{
//	fullscreen = !fullscreen;
//	if (fullscreen)
//	{
//		int style = sf::Style::Default | sf::Style::Fullscreen;
//		std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();
//		Renderer::GetWindow().create(VModes.at(0), "Workin' 9 to Die", style);
//	}
//	else
//	{
//		Renderer::GetWindow().create(VideoMode(resolutions[currentRes].first, resolutions[currentRes].second), "Workin' 9 to Die");
//	}
//}
//
//void Renderer::setResolution(int res) 
//{
//		currentRes = res;
//		if (!fullscreen)
//		{
//			Renderer::GetWindow().create(VideoMode(resolutions[currentRes].first, resolutions[currentRes].second), "Workin' 9 to Die");
//		}
//}
