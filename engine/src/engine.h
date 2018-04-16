#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <ecm.h>
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

class Scene {
public:
  Scene() = default;
  virtual ~Scene();
  virtual void Load() = 0;
  virtual void LoadAsync();
  virtual void UnLoad();
  virtual void Update(const double& dt);
  virtual void Render();
  virtual void Reset(){}
  virtual void ReSize() {}
  bool isLoaded() const;
  std::shared_ptr<Entity> makeEntity();

  EntityManager ents;

protected:
  void setLoaded(bool);
private:
  mutable bool _loaded;
  mutable std::future<void> _loaded_future;
  mutable std::mutex _loaded_mtx;
};

class Engine {
public:
  Engine() = delete;
  static void Start(unsigned int width, unsigned int height,
                    const std::string& gameName, std::shared_ptr<Scene> scn);
  static void ChangeScene(std::shared_ptr<Scene>);
  static void ChangeMenu(std::shared_ptr<Scene>);
  static sf::RenderWindow& GetWindow();
  static sf::Vector2u getWindowSize();
  static void setVsync(bool b);
  static bool ShowingMenu() { return menuUp; }
  static void Resize();
  static std::shared_ptr<Scene> GetActive() { return _activeScene; }
private:
  static std::shared_ptr<Scene> _activeScene;
  static std::shared_ptr<Scene> _activeMenu;
  static std::string _gameName;
  static bool menuUp;
  static void Update();
  static void Render(sf::RenderWindow& window);
};

namespace timing {
// Return time since Epoc
long long now();
// Return time since last() was last called.
long long last();
} // namespace timing