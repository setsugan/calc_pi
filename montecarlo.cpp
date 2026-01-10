#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <cmath>

struct Point
{
    double x;
    double y;
};

int main()
{
    constexpr unsigned int WIDTH  {300};
    constexpr unsigned int HEIGHT {300};

    constexpr double RADIUS { WIDTH / 2.0 };

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "montecarlo");
    window.setFramerateLimit(60);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-RADIUS, RADIUS);

    size_t total_points  {};
    size_t inside_points {};

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
            bool is_inside {false};

            if (pow(point.x, 2.0) + pow(point.y, 2.0) <= pow(RADIUS, 2.0))
            {
                is_inside = true;
                ++inside_points;
            }
            ++total_points;

            sf::Color color {is_inside ? sf::Color::Green : sf::Color::Red};
            points.append(sf::Vertex(sf::Vector2f(point.x + RADIUS, point.y + RADIUS), color));

            window.clear(sf::Color::Black);
            window.draw(points);
            window.display();
        }
    }
}