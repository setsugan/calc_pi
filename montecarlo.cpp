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

    constexpr size_t POINTS_PER_FRAME {10000};

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "montecarlo");
    window.setFramerateLimit(60);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-RADIUS, RADIUS);

    size_t total_points  {};
    size_t inside_points {};

    double pi {};

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
        }

        for (size_t i{}; i < POINTS_PER_FRAME; ++i)
        {
            Point point {dist(gen), dist(gen)};
            bool is_inside {false};

            if (point.x*point.x + point.y*point.y <= RADIUS*RADIUS)
            {
                is_inside = true;
                ++inside_points;
            }
            ++total_points;

            sf::Color color {is_inside ? sf::Color::Green : sf::Color::Red};
            points.append(sf::Vertex(sf::Vector2f(point.x + RADIUS, point.y + RADIUS), color));
        }
        
        pi = static_cast<double>(inside_points) / static_cast<double>(total_points) * 4.0;
        if (total_points % 10000 == 0)
        {
            std::cout <<"total : " << total_points << "points. pi : " << pi << std::endl;
        }

        window.clear(sf::Color::Black);
        window.draw(points);
        window.display();
    }
}