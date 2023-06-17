#pragma once
#include "Entity.h"

enum struct CellCategory{
    WALL, ROAD
};

class Cell: public StaticEntity{
protected:
    CellCategory category;
public:
	Cell(float x, float y, float s, CellCategory _category);
	void render(sf::RenderWindow& window) override;
    sf::FloatRect getGlobalBounds();
    CellCategory getCellCategory();
    bool isWall();
    bool isRoad();
};
