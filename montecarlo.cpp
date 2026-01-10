#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

struct Point
{
    double x;
    double y;
};

int main()
{
    constexpr unsigned int WIDTH  {800};
    constexpr unsigned int HEIGHT {800};

    constexpr double RADIUS { WIDTH / 2.0 };

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "montecarlo");
    window.setFramerateLimit(60);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-RADIUS, RADIUS);

    sf::VertexArray points(sf::Points);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            Point point {dist(gen), dist(gen)};

            sf::Color color {sf::Color::Green};
            points.append(sf::Vertex(sf::Vector2f(point.x + RADIUS, point.y + RADIUS), color));

            window.clear(sf::Color::Black);
            window.draw(points);
            window.display();
        }
    }
}