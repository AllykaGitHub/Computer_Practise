#include "Pacman.h"

Pacman::Pacman(float x, float y): MovingEntity(x, y){
    shape.setRadius(pacman_radius);
    shape.setFillColor(pacman_color);
    shape.setPosition(position);
}

void Pacman::updatePacmanDirection() {
    direction = Direction::NONE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        direction = Direction::UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
             || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        direction = Direction::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        direction = Direction::LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
             || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        direction = Direction::RIGHT;
    }
}

void Pacman::setPacmanPosition(float x, float y){
    position = {x, y};
    shape.setPosition(position);
}

float Pacman::getPacmanRadius() const{
    return pacman_radius;
}

void Pacman::updatePosition(float elapsedTime) {
    updatePacmanDirection();
    position += getDirectionMove();
}

void Pacman::update(float elapsedTime, std::vector<Cell*>& cells){
    updatePacmanDirection();
    if(checkDirectionCollision(cells)){
        return;
    }
    position += getDirectionMove();
}

void Pacman::render(sf::RenderWindow &window){
    shape.setPosition(position);
    window.draw(shape);
}

Direction Pacman::getPacmanDirection() const{
    return direction;
}

sf::Vector2f Pacman::getPacmanPosition() const{
    return position;
}

sf::FloatRect Pacman::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

bool Pacman::checkDirectionCollision(std::vector<Cell*>& cells) const{
    sf::CircleShape circ;
    circ.setRadius(pacman_radius);
    circ.setPosition(position);

    sf::Vector2f move = getDirectionMove();
    circ.move(move);

    for (auto cell: cells){
        if (cell->isWall() && cell->getGlobalBounds().intersects(circ.getGlobalBounds())){
            return true;
        }
    }
    return false;
}

sf::Vector2f Pacman::getDirectionMove() const {
    if (direction == Direction::UP){
        return {0.0f, -pacman_speed};
    }
    if (direction == Direction::DOWN){
        return {0.0f, pacman_speed};
    }
    if (direction == Direction::LEFT){
        return {-pacman_speed, 0.0f};
    }
    if (direction == Direction::RIGHT){
        return {pacman_speed, 0.0f};
    }
    return {0.0f, 0.0f};
}

