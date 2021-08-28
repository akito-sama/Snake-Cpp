#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.cpp"

#pragma region overload_vector
std::ostream& operator<<(std::ostream& o, sf::Vector2i vector)
{
    o << vector.x << ", " << vector.y;
    return o;
}

#pragma endregion

int main()
{
    srand((unsigned)time(0));
    Game game = Game();
    float Fps = 1.0f/15;
    std::cout << sf::Vector2i(5, 10);
    while (game.window.isOpen()) {
        game.event();
        game.draw();
        game.update();
        sf::sleep(sf::seconds(Fps));
    }
    return 0;
}