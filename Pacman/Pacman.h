#pragma once
#include <vector>
#include <list>
#include "Entity.h"
#include "Field.h"
#include "Cell.h"

class Pacman: public MovingEntity{
private:
    const sf::Color pacman_color = sf::Color::Yellow;
    const float pacman_radius = Field::f_block_size * 0.4f;
    const float pacman_speed = 0.15f;
public:
	explicit Pacman(float x = 0, float y = 0);
	void updatePacmanDirection();
    void setPacmanPosition(float x, float y);
    float getPacmanRadius() const;
    void updatePosition(float elapsedTime) override;
    void update(float elapsedTime, std::vector<Cell*>& cells);
    void render(sf::RenderWindow& window) override;
    Direction getPacmanDirection() const;

    sf::Vector2f getPacmanPosition() const;
    sf::FloatRect getGlobalBounds() const;
private:
    sf::Vector2f getDirectionMove() const;
    bool checkDirectionCollision(std::vector<Cell*>& cells) const;
};

