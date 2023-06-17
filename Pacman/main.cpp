#include <iostream>
#include<SFML/Graphics.hpp>
#include "Pacman.h"
#include "Cell.h"
#include "Game.h"


int main() {
    sf::Vector2f win_s = Field::pixel_sizes;
    sf::RenderWindow window(sf::VideoMode(win_s.x, win_s.y), "SFML works!", sf::Style::Default);
    Game game;

    while(window.isOpen()) {
        sf::Event event{};
        sf::Vector2f move;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        game.updateGame(125);

        window.clear();
        game.render(window);
        window.display();
    }

    return 0;
}
