#include "engine.h"
#include "maths.h"
#include "system_physics.h"
#include "system_renderer.h"
#include "system_resources.h"
#include <SFML/Graphics.hpp>
#include <future>
#include <iostream>
#include <stdexcept>
#include "../Code/Game.h"

using namespace sf;
using namespace std;
shared_ptr<Scene> Engine::_activeScene = nullptr;
shared_ptr<Scene> Engine::_activeMenu = nullptr;
std::string Engine::_gameName;
bool Engine::menuUp = false;

static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;

void Loading_Update(float dt, const shared_ptr<Scene> const scn) {
	//  cout << "Eng: Loading Screen\n";
	if (scn->isLoaded()) {
		cout << "Eng: Exiting Loading Screen\n";
		loading = false;
	}
	else {
		loadingspinner += 220.0f * dt;
		loadingTime += dt;
	}
}
void Loading_render() {
	// cout << "Eng: Loading Screen Render\n";
	static CircleShape octagon(80, 8);
	octagon.setOrigin(80, 80);
	octagon.setRotation(loadingspinner);
	octagon.setPosition(Vcast<float>(Engine::getWindowSize()) * .5f);
	octagon.setFillColor(Color(255, 255, 255, min(255.f, 40.f*loadingTime)));
	static Text t("Loading", *Resources::get<sf::Font>("rm_typerighter_old.ttf"));
	t.setFillColor(Color(255, 255, 255, min(255.f, 40.f*loadingTime)));
	t.setPosition(Vcast<float>(Engine::getWindowSize()) * Vector2f(0.4f, 0.3f));
	Renderer::Queue(Renderer::Layer::UIMID, &t);
	Renderer::Queue(Renderer::Layer::UIBACK, &octagon);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
		frametimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 60 == 0) {
			double davg = 0;
			for (const auto t : frametimes) {
				davg += t;
			}
			davg = 1.0 / (davg / 255.0);
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	if (loading) {
		Loading_Update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		if (player1->activeControls != nullptr)
		{
			// Update the inputs for player 1
			player1->Update(dt);
		}
		// If no menu is open
		if (!menuUp) {
			// Update physics engine
			Physics::Update(dt);
			// Update active scene
			_activeScene->Update(dt);
			// If the player pauses open the menu
			if (player1->activeControls != nullptr && player1->GetButtonDown(InputManager::MENU)) {
				ChangeMenu(menuScene);
			}
		}
		else {
			// Update active menu screen
			_activeMenu->Update(dt);
		}
		//check if fullscreen
		if (player1->activeControls != nullptr && player1->GetButtonDown(player1->FULLSCREEN))
		{
			Renderer::ToggleFullscreen();
			if (_activeMenu != nullptr)
				_activeMenu->ReSize();
			_activeScene->ReSize();
		}
	}
}

void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
		if (menuUp) {
			_activeMenu->Render();
		}
	}

	Renderer::Render();
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, shared_ptr<Scene> scn) {
	RenderWindow window(VideoMode(width, height), gameName);
	_gameName = gameName;
	_window = &window;
	Renderer::Initialise(window);
	Physics::initialise();
	ChangeScene(scn);
	while (window.isOpen()) {
		window.clear();
		Update();
		Render(window);
		window.display();
	}
	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}
	window.close();
	Physics::shutdown();
	// Render::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	ents.list.push_back(e);
	return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(shared_ptr<Scene> s) {
	cout << "Eng: changing scene: " << s << endl;
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad(); // todo: Unload Async
	}

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0;
		_activeScene->LoadAsync();
		loading = true;
	}
}

void Engine::ChangeMenu(shared_ptr<Scene> m) {
	cout << "Eng: changing scene: " << m << endl;
	shared_ptr<Scene> old = _activeMenu;
	_activeMenu = m;

	if (old != nullptr) {
		old->UnLoad();
	}
	else {
		menuUp = true;
	}
	if (m != nullptr) {
		_activeMenu->Load();
	}
	else {
		menuUp = false;
	}
}

void Engine::Resize()
{
	_activeMenu->ReSize();
	_activeScene->ReSize();
}


///SCENE///
void Scene::Update(const double& dt) { ents.Update(dt); }

void Scene::Render() {
	ents.render();
}

bool Scene::isLoaded() const {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		// Are we already loading asynchronously?
		if (_loaded_future.valid() // yes
			&&                     // Has it finished?
			_loaded_future.wait_for(chrono::seconds(0)) ==
			future_status::ready) {
			// Yes
			_loaded_future.get();
			_loaded = true;
		}
		return _loaded;
	}
}
void Scene::setLoaded(bool b) {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		_loaded = b;
	}
}

void Scene::UnLoad() {
	ents.list.clear();
	setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing

Scene::~Scene() { UnLoad(); }