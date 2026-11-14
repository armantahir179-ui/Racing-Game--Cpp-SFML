#include <SFML/Graphics.hpp>
using namespace std;
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Racing Game");

    sf::RectangleShape player({50, 90});
    player.setFillColor(sf::Color::Red);
    player.setPosition({375, 450});

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            player.move({-5, 0});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            player.move({5, 0});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            player.move({0, -5});

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            player.move({0, 5});

        window.clear(sf::Color::Green);
        window.draw(player);
        window.display();
    }

    return 0;
}

