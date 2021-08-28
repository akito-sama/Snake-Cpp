#include <iostream>
#include <SFML/Graphics.hpp>
#include "apple.hpp"
#include <string>

// std::ostream& operator<<(std::ostream& o, sf::Vector2i vector);

Apple::Apple(sf::RenderWindow* window, int square_size, Snake* snake, unsigned int* score) {
    this->window = window;
    this->snake = snake;
    this->square_size = square_size;
    this->score = score;
    position = sf::Vector2i(0, 0);
    rect = sf::RectangleShape();
    rect.setSize(sf::Vector2f(square_size, square_size));
    rect.setFillColor(sf::Color::Red);
    rect.setOutlineColor(sf::Color::Black);
    rect.setOutlineThickness(0.5f);
    randomize();
}

void Apple::draw()
{
    window->draw(rect);
}

void Apple::randomize()
{
    std::deque<sf::Vector2i> body = snake->getBody();
    do
    {
        sf::Vector2u size = window->getSize();
        position.x = rand() % (size.x / square_size);
        position.y = rand() % (size.y / square_size);

    } while (std::find(body.begin(), body.end(), position) != body.end());
    rect.setPosition(sf::Vector2f(position.x * square_size, position.y * square_size));
    *(this->score) += 1;
    window->setTitle("Score = " + std::to_string(*this->score));
}

void Apple::reset()
{
    randomize();
}

