#include "Cell.h"

Cell::Cell(float x, float y, float s, CellCategory _category){
    size = s;
    position = {x, y};
    category = _category;

    if (category == CellCategory::ROAD){
        shape.setFillColor(sf::Color::Black);
    }
    else{
        shape.setFillColor(sf::Color(80, 26, 250));
    }

    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(position);
}

void Cell::render(sf::RenderWindow &window){
    window.draw(shape);
}

sf::FloatRect Cell::getGlobalBounds(){
    return shape.getGlobalBounds();
}

CellCategory Cell::getCellCategory(){
    return category;
}

bool Cell::isWall() {
    return category == CellCategory::WALL;
}

bool Cell::isRoad() {
    return category == CellCategory::ROAD;
}