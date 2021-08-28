#include <deque>
#include <SFML/Graphics.hpp>
#include "apple.hpp"
#include "snake.hpp"

// std::ostream& operator<<(std::ostream& o, sf::Vector2i vector);


Snake::Snake(int size, Apple* apple)
{
    shape = sf::RectangleShape();
    this->size = size;
    shape.setSize(sf::Vector2f(size - size / 10, size - size / 10));
    shape.setFillColor(sf::Color::Green);
    mouvement = mouvements[1];
    this->apple = apple;
}

sf::Vector2i Snake::getHead()
{
    return body.back();
}

sf::Vector2i Snake::getLast()
{
    return body.front();
}

void Snake::draw(sf::RenderWindow& window)
{

    for (auto i: body)
    {
        shape.setPosition(i.x * size, i.y * size);
        window.draw(shape);
    }
    if (dead)
    {
        shape.setPosition(dead_pos.x * size, dead_pos.y * size);
        shape.setFillColor(sf::Color::Blue);
        window.draw(shape);
        shape.setFillColor(sf::Color::Green);
    }
    shape.setPosition(0, 0);
}

void Snake::move(sf::Vector2u windowSize)
{
    sf::Vector2i last = getLast();
    sf::Vector2i const head = getHead();
    int x = (head.x + mouvement.x), y = (head.y + mouvement.y);

    x = (x >= 0) ? x  % (windowSize.x / size): windowSize.x / size;
    y = (y >= 0) ? y  % (windowSize.y / size): windowSize.y / size;
    
    last = sf::Vector2i(x, y);
    if (head.x != apple->position.x || head.y != apple->position.y)
    {
        body.pop_front();
    }
    else 
    {
        apple->randomize();
    }
    if (std::find(body.begin(), body.end(), last) != body.end())
    {
        this->dead = true;
        this->dead_pos = last;
    }
    body.push_back(last);
} 

void Snake::event(sf::Event _event)
{
    switch (_event.type)
    {
        case sf::Event::KeyPressed:
            switch (_event.key.code)
            {
                case sf::Keyboard::Up:
                    if (mouvement != mouvements[2])
                        mouvement = mouvements[0];
                    break;
                case sf::Keyboard::Right:
                    if (mouvement != mouvements[3])
                        mouvement = mouvements[1];
                    break;
                case sf::Keyboard::Down:
                    if (mouvement != mouvements[0])
                        mouvement = mouvements[2];
                    break;
                case sf::Keyboard::Left:
                    if (mouvement != mouvements[1])
                        mouvement = mouvements[3];
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

}
std::deque<sf::Vector2i>& Snake::getBody()
{
    return this->body;
}
