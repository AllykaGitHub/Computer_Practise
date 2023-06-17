#include "Entity.h"
#include <iostream>

//Static Entity
sf::FloatRect StaticEntity::getBounds(){
    return shape.getGlobalBounds();
}

//PacGum
PacGum::PacGum(float x, float y, float s){
    position = {x, y};
    size = s;

    shape.setFillColor(sf::Color::Black);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(position);

    little_circle.setFillColor(sf::Color::White);
    little_circle.setRadius(0.125f * size);
    little_circle.setPosition({position.x + 0.375f * s, position.y + 0.375f * s});
}
void PacGum::render(sf::RenderWindow &window) {
    window.draw(shape);
    window.draw(little_circle);
}

//SuperPacGum
SuperPacGum::SuperPacGum(float x, float y, float s) {
    position = {x, y};
    size = s;

    shape.setFillColor(sf::Color::Black);
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(position);

    circle.setFillColor(sf::Color(247, 211, 250));
    circle.setRadius(0.25f * size);
    circle.setPosition({position.x + 0.25f * s, position.y + 0.25f * s});

}
void SuperPacGum::render(sf::RenderWindow &window){
    window.draw(shape);
    window.draw(circle);
}

//Moving Entity
MovingEntity::MovingEntity(float x, float y){
    position = {x, y};
    speedVec = {0.0f , 0.0f};
    direction = Direction::NONE;
}

void MovingEntity::updatePosition(float elapsedTime){}
void MovingEntity::render(sf::RenderWindow &window){}
sf::FloatRect MovingEntity::getBounds(){
    return shape.getGlobalBounds();
}

