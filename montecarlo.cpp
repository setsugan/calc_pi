#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    constexpr unsigned int WIDTH  {800};
    constexpr unsigned int HEIGHT {800};

    constexpr double RADIUS { WIDTH / 2.0 };

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "montecarlo");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            window.clear(sf::Color::Black);
            window.display();
        }
    }
}