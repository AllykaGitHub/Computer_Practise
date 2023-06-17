#include<SFML/Graphics.hpp>
#include<iostream>

#ifndef PACMAN_FIELD_H
#define PACMAN_FIELD_H

struct Field{
    inline static const float f_block_size = 35.0f;
    inline static const size_t block_size = 35;

    inline static const size_t width = 23;
    inline static const size_t height = 14;

    inline static const sf::Vector2f pixel_sizes = {f_block_size * width, f_block_size * height};


    inline static sf::Vector2f upper_left = {block_size + 1,
                                             block_size + 1};

    inline static sf::Vector2f upper_right = {(width - 1) * block_size - 1,
                                              block_size + 1};

    inline static sf::Vector2f lower_left = {block_size + 1,
                                             (height - 1) - 1};

    inline static sf::Vector2f lower_right = {(width - 1) * block_size - 1,
                                              (height - 1) * block_size - 1};

    std::string maze[height] = {
            "#####S############S####",
            "#PoooooooooooooooooooB#",
            "#oo#S######S######S#oo#",
            "Soo#o#ooooooooooo#o#ooS",
            "#oo#o#ooooooooooo#o#oo#",
            "#oo#o#o#########o#o#oo#",
            "#oo#oSo#o# T #o#oSo#oo#",
            "#oo#oSo#o#####o#oSo#oo#",
            "#oo#o#o#   M   #o#o#oo#",
            "#oo#o#oS       So#o#oo#",
            "Soo#o#ooooooooooo#o#ooS",
            "#oo#S######S######S#oo#",
            "#IoooooooooooooooooooC#",
            "####S#############S####"
    };
};

#endif //PACMAN_FIELD_H
