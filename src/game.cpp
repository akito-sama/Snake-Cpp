#include <iostream>
#include <SFML/Graphics.hpp>
#include "snake.hpp"
#include "apple.hpp"



class Game {
    private:
        int const grid_size = 20;
        sf::Image ico;
        Snake snake;
        Apple apple;
        sf::RenderTexture backgroundTexture = sf::RenderTexture();
        sf::Sprite background;

        void drawGrid()
        {
            backgroundTexture.create(WindowWidth, WindowHeight);
            backgroundTexture.clear(sf::Color(255, 255, 255));
            for (int x = 0; x < WindowWidth; x += grid_size)
            {
                sf::VertexArray line(sf::LinesStrip, 2);
                line[0].position = sf::Vector2f(x, 0);
                line[1].position = sf::Vector2f(x, WindowHeight);
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
                backgroundTexture.draw(line);

            }
            for (int y = 0; y < WindowHeight; y += grid_size)
            {
                sf::VertexArray line(sf::LinesStrip, 2);
                line[0].position = sf::Vector2f(0, y);
                line[1].position = sf::Vector2f(WindowWidth, y);
                line[0].color = sf::Color::Black;
                line[1].color = sf::Color::Black;
                backgroundTexture.draw(line);
            }
            background = sf::Sprite(backgroundTexture.getTexture());
        }

        void reset() {
            this->score = 0;
        }

    public:
        unsigned int score = 0;
        int const WindowWidth = 600;
        int const WindowHeight = 600;
        sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WindowWidth, WindowHeight), "My Screen");

    Game()
    {
        ico.loadFromFile("src/snake.png");
        window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
        apple = Apple(&window, grid_size, &snake, &score);
        snake = Snake(grid_size, &apple);
        drawGrid();
    }

    void event()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape && snake.dead)
                {
                    reset();
                    snake.reset();
                    apple.reset();
                }
                break;
            default:
                break;
            }
            snake.event(event);
        }
    }

    void draw()
    {
        window.clear(sf::Color(255, 255, 255));
        window.draw(background);
        apple.draw();
        snake.draw(window);
    }

    void update()
    {
        if (!snake.dead)
            snake.move(&window, &score);
        window.display();
    }
};
