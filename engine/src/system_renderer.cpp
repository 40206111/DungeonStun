#include "system_renderer.h"
#include <queue>

using namespace std;
using namespace sf;

static vector<queue<const Drawable*>> sprites;
static RenderWindow* rw;
static bool fullscreen = false;

unsigned int Renderer::currentRes = 3;

void Renderer::Initialise(sf::RenderWindow& r) {
	rw = &r;
	for (int i = 0; i <= Layer::UIFORE; ++i) {
		sprites.push_back(move(queue<const Drawable*>()));
	}
}

sf::RenderWindow & Renderer::GetWindow() { return *rw; }
bool Renderer::GetFullscreen() { return fullscreen; }

void Renderer::Shutdown() {
	for (int i = 0; i < sprites.size(); i++)
	{
		while (!sprites[i].empty())
			sprites[i].pop();
	}
}

void Renderer::Update(const double& dt) {}

void Renderer::Render() {
	if (rw == nullptr) {
		throw("No render window set! ");
	}
	for (int i = 0; i < sprites.size(); ++i) {
		while (!sprites[i].empty()) {
			rw->draw(*sprites[i].front());
			sprites[i].pop();
		}
	}
}

void Renderer::Queue(Layer l, const sf::Drawable* s) { sprites[l].push(s); }

void Renderer::ToggleFullscreen()
{
	fullscreen = !fullscreen;
	if (fullscreen)
	{
		int style = sf::Style::Default | sf::Style::Fullscreen;
		std::vector<sf::VideoMode> VModes = sf::VideoMode::getFullscreenModes();
		Renderer::GetWindow().create(VModes.at(0), "Workin' 9 to Die", style);
	}
	else
	{
		Renderer::GetWindow().create(VideoMode(resolutions[currentRes].first, resolutions[currentRes].second), "Workin' 9 to Die");
	}
}

void Renderer::setResolution(int res)
{
	currentRes = res;
	if (!fullscreen)
	{
		Renderer::GetWindow().create(VideoMode(resolutions[currentRes].first, resolutions[currentRes].second), "Workin' 9 to Die");
	}
}