#pragma once
#include <SFML/Graphics.hpp>

enum struct Direction{
	NONE, UP, DOWN, LEFT, RIGHT
};

class Entity{
protected:
    sf::Vector2f position;
public:
	virtual sf::FloatRect getBounds() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
    virtual ~Entity() = default;
};

class StaticEntity : public Entity{
protected:
    float size;
	sf::FloatRect bounds;
	sf::RectangleShape shape;
public:
    sf::FloatRect getBounds() final;
};

class PacGum : public StaticEntity {
protected:
    sf::CircleShape little_circle;
public:
	PacGum(float x, float y, float s);
	void render(sf::RenderWindow& window) final;
};


class SuperPacGum : public StaticEntity {
protected:
    sf::CircleShape circle;
public:
	SuperPacGum(float x, float y, float s);
	void render(sf::RenderWindow& window) final;
};


class MovingEntity : public Entity {
protected:
	sf::Vector2f speedVec;
	Direction direction;
	sf::CircleShape shape;
public:
    explicit MovingEntity(float x = 0, float y = 0);
	virtual void updatePosition(float elapsedTime);
	void render(sf::RenderWindow& window) override;
	sf::FloatRect getBounds() final;
};