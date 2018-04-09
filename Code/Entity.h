#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Entity
{
protected:
	std::unique_ptr<sf::Shape> shape;
	sf::Vector2f position;
	Entity(std::unique_ptr<sf::Shape> shp);
public:
	Entity() = delete;
	virtual ~Entity() = default;

	virtual void Update(const double dt);
	virtual void render() const = 0;
	const sf::Vector2f GetPosition();
	void SetPosition(const sf::Vector2f &pos);
	void Move(const sf::Vector2f &pos);
};