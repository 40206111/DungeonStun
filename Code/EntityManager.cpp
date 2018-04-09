#include "EntityManager.h"
#include "SystemRenderer.h"
using namespace std;
using namespace sf;

void EntityManager::Update(double dt) 
{
	for (shared_ptr<Entity> e : list) {
		e->Update(dt);
	}
}

void EntityManager::Render() 
{
	for (shared_ptr<Entity> e : list) {
		e->Render();
	}
}