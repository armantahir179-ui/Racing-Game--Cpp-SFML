#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    // 1. Create the game window
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }),
        "Racing Game"
    );

    // 2. Create the background
    sf::Color grassGreen(30, 150, 50);

    // 3. Create the road
    sf::RectangleShape road({ 400.f, 600.f });
    road.setPosition({ 200.f, 0.f });
    road.setFillColor(sf::Color(70, 70, 70));

    // 4. Create the left road boundary
    sf::RectangleShape leftLine({ 5.f, 600.f });
    leftLine.setPosition({ 200.f, 0.f });
    leftLine.setFillColor(sf::Color::White);

    // 5. Create the right road boundary
    sf::RectangleShape rightLine({ 5.f, 600.f });
    rightLine.setPosition({ 595.f, 0.f });
    rightLine.setFillColor(sf::Color::White);

    // 6. Create two dashed lines to divide the road into three lanes
    sf::RectangleShape laneLines[12];

    for (int i = 0; i < 6; i++)
    {
        // First dividing line
        laneLines[i].setSize({ 8.f, 40.f });
        laneLines[i].setPosition({ 330.f, 20.f + i * 100.f });
        laneLines[i].setFillColor(sf::Color::White);

        // Second dividing line
        laneLines[i + 6].setSize({ 8.f, 40.f });
        laneLines[i + 6].setPosition({ 463.f, 20.f + i * 100.f });
        laneLines[i + 6].setFillColor(sf::Color::White);
    }

    // 7. Create the main car body
    sf::RectangleShape car({ 85.f, 100.f });
    car.setPosition({ 357.5f, 450.f });
    car.setFillColor(sf::Color::Red);

    // 8. Create the front windshield
    sf::RectangleShape windshield({ 63.f, 24.f });
    windshield.setPosition({ 368.5f, 460.f });
    windshield.setFillColor(sf::Color::Cyan);

    // 9. Create the rear window
    sf::RectangleShape rearWindow({ 63.f, 24.f });
    rearWindow.setPosition({ 368.5f, 506.f });
    rearWindow.setFillColor(sf::Color::Black);

    // 10. Create the four wheels
    sf::RectangleShape wheels[4];

    for (int i = 0; i < 4; i++)
    {
        wheels[i].setSize({ 10.f, 22.f });
        wheels[i].setFillColor(sf::Color::Black);
    }

    // Wheel positions
    wheels[0].setPosition({ 347.5f, 463.f }); // Front left
    wheels[1].setPosition({ 442.5f, 463.f }); // Front right
    wheels[2].setPosition({ 347.5f, 510.f }); // Rear left
    wheels[3].setPosition({ 442.5f, 510.f }); // Rear right

    // 11. Main game loop
    while (window.isOpen())
    {
        // Handle window events
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // 12. Clear the window with the background color
        window.clear(grassGreen);

        // 13. Draw the road and boundaries
        window.draw(road);
        window.draw(leftLine);
        window.draw(rightLine);

        // 14. Draw all lane markings
        for (int i = 0; i < 12; i++)
        {
            window.draw(laneLines[i]);
        }

        // 15. Draw the car body and windows
        window.draw(car);
        window.draw(windshield);
        window.draw(rearWindow);

        // 16. Draw the four wheels
        for (int i = 0; i < 4; i++)
        {
            window.draw(wheels[i]);
        }

        // 17. Display the completed frame
        window.display();
    }

    return 0;
}
