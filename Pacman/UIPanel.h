#pragma once
#include<SFML/Graphics.hpp>
#include "Field.h"

class UIPanel{
private:
    size_t score;

    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;
public:
    UIPanel(float x, float y, float s);
    void increaseScore(size_t points);
    void resetScore();
    void render(sf::RenderWindow& window) const;
    size_t getScore() const;
    void setGameOverText();
};
