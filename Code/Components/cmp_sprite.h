#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "system_renderer.h"

class SpriteComponent : public Component {
protected:
	Renderer::Layer renderLayer = Renderer::Layer::LEVEL;
	std::shared_ptr<sf::Sprite> _sprite;

public:
	SpriteComponent() = delete;

	explicit SpriteComponent(Entity* p);
	void Update(const double &dt) override;
	void render() override;

	void SetRenderLayer(Renderer::Layer l) { renderLayer = l; }
	sf::Sprite& getSprite() const;

	template <typename... Targs> void setSprite(Targs... params) {
		_sprite.reset(new sf::Sprite(params...));
	}
};

class ShapeComponent : public Component {
protected:
	Renderer::Layer renderLayer = Renderer::Layer::LEVEL;
	std::shared_ptr<sf::Shape> _shape;
	// sf::Shape _shape;

public:
	ShapeComponent() = delete;

	explicit ShapeComponent(Entity* p);

	void Update(const double &dt) override;
	void render() override;
	void SetRenderLayer(Renderer::Layer l) { renderLayer = l; }
	sf::Shape& getShape() const;
	template <typename T, typename... Targs> void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};