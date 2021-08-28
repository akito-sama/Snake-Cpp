#pragma once
#include <deque>
#include <SFML/Graphics.hpp>
#include "apple.hpp"

class Apple;

class Snake
{

private:
    sf::Vector2i dead_pos;
    std::deque<sf::Vector2i> body = {sf::Vector2i(0, 0), sf::Vector2i(1, 0)};
    sf::RectangleShape shape;
    std::array<sf::Vector2i, 4> mouvements = {sf::Vector2i(0, -1), sf::Vector2i(1, 0), sf::Vector2i(0, 1), sf::Vector2i(-1, 0)};
    sf::Vector2i mouvement;
    Apple* apple;
    int size;

public:
    bool dead = false;

    Snake()
    {
        
    }
    Snake(int size, Apple* apple);

    sf::Vector2i getHead();

    sf::Vector2i getLast();

    void draw(sf::RenderWindow& window);

    void move(sf::Vector2u windowSize);

    void event(sf::Event _event);

    std::deque<sf::Vector2i>& getBody();
};
