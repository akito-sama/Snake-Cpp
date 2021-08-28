#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "snake.hpp"

class Snake;

class Apple 
{
public:
    sf::Vector2i position;
    sf::RenderWindow* window;
    int square_size;
    unsigned int* score;
    Snake* snake;
    sf::RectangleShape rect;

    Apple()
    {
        
    }
    
    Apple(sf::RenderWindow* window, int square_size, Snake* snake, unsigned int* score);

    void draw();

    void reset();

    void randomize();
};
