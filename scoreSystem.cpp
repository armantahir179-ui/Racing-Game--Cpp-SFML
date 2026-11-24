#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    // Random number generator
    srand(static_cast<unsigned int>(time(0)));

    // 1. Create the game window
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }),
        "Racing Game"
    );

    window.setFramerateLimit(60);

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

    // 6. Create two dashed lines
    sf::RectangleShape laneLines[12];

    for (int i = 0; i < 6; i++)
    {
        laneLines[i].setSize({ 8.f, 40.f });
        laneLines[i].setPosition({ 330.f, 20.f + i * 100.f });
        laneLines[i].setFillColor(sf::Color::White);

        laneLines[i + 6].setSize({ 8.f, 40.f });
        laneLines[i + 6].setPosition({ 463.f, 20.f + i * 100.f });
        laneLines[i + 6].setFillColor(sf::Color::White);
    }

    // 7. Create the player car body
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

    // 10. Create four player wheels
    sf::RectangleShape wheels[4];

    for (int i = 0; i < 4; i++)
    {
        wheels[i].setSize({ 10.f, 22.f });
        wheels[i].setFillColor(sf::Color::Black);
    }

    wheels[0].setPosition({ 347.5f, 463.f });
    wheels[1].setPosition({ 442.5f, 463.f });
    wheels[2].setPosition({ 347.5f, 510.f });
    wheels[3].setPosition({ 442.5f, 510.f });

    // 11. Create three enemy car bodies
    sf::RectangleShape enemyCars[3];

    // Create three front windshields
    sf::RectangleShape enemyWindshields[3];

    // ceate three rear windows
    sf::RectangleShape enemyRearWindows[3];

    //Create four wheels for each enemy car
    sf::RectangleShape enemyWheels[3][4];

    //Three lane positions
    float enemyX[3] = { 220.f, 355.f, 490.f };

    // Enemy car speed
    float enemySpeed = 4.f;

    // SCORE SYSTEM
    int score = 0;

    // 12. Set enemy car specifications
    for (int i = 0; i < 3; i++)
    {
        // Enemy car body
        enemyCars[i].setSize({ 85.f, 100.f });
        enemyCars[i].setFillColor(sf::Color::Blue);

        // Enemy front windshield
        enemyWindshields[i].setSize({ 63.f, 24.f });
        enemyWindshields[i].setFillColor(sf::Color::Cyan);

        // Enemy rear window
        enemyRearWindows[i].setSize({ 63.f, 24.f });
        enemyRearWindows[i].setFillColor(sf::Color::Black);

        // Enemy wheels
        for (int j = 0; j < 4; j++)
        {
            enemyWheels[i][j].setSize({ 10.f, 22.f });
            enemyWheels[i][j].setFillColor(sf::Color::Black);
        }

        // Random lane
        int randomLane = rand() % 3;

        // Enemy starting position
        float x = enemyX[randomLane];
        float y = -150.f - (i * 220.f);

        enemyCars[i].setPosition({ x, y });

        // Position front windshield
        enemyWindshields[i].setPosition({
            x + 11.f, y + 10.f
            });

        // Position rear window
        enemyRearWindows[i].setPosition({
            x + 11.f, y + 56.f
            });

        // Position four wheels
        enemyWheels[i][0].setPosition({
            x - 10.f, y + 13.f
            });

        enemyWheels[i][1].setPosition({
            x + 85.f, y + 13.f
            });

        enemyWheels[i][2].setPosition({
            x - 10.f, y + 60.f
            });

        enemyWheels[i][3].setPosition({
            x + 85.f, y + 60.f
            });
    }

    // PART 5: COLLISION DETECTION
    bool gameOver = false;

    // 13. Main game loop
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

        // 14. Move enemy cars
        if (!gameOver)
        {
            for (int i = 0; i < 3; i++)
            {
                // Move enemy body
                enemyCars[i].move({ 0.f, enemySpeed });

                // Move front windshield
                enemyWindshields[i].move({ 0.f, enemySpeed });

                // Move rear window
                enemyRearWindows[i].move({ 0.f, enemySpeed });

                // Move four wheels
                for (int j = 0; j < 4; j++)
                {
                    enemyWheels[i][j].move({ 0.f, enemySpeed });
                }

                // Check if enemy leaves screen
                if (enemyCars[i].getPosition().y > 600.f)
                {
                    // SCORE SYSTEM
                    score++;

                    cout << "Score: " << score << endl;

                    // Select random lane
                    int randomLane = rand() % 3;

                    // New position
                    float x = enemyX[randomLane];
                    float y = -150.f;

                    // Respawn enemy body
                    enemyCars[i].setPosition({ x, y });

                    // Respawn front windshield
                    enemyWindshields[i].setPosition({
                        x + 11.f, y + 10.f
                        });

                    // Respawn rear window
                    enemyRearWindows[i].setPosition({
                        x + 11.f, y + 56.f
                        });

                    // Respawn four wheels
                    enemyWheels[i][0].setPosition({
                        x - 10.f, y + 13.f
                        });

                    enemyWheels[i][1].setPosition({
                         x + 85.f, y + 13.f
                        });

                    enemyWheels[i][2].setPosition({
                        x - 10.f, y + 60.f
                        });

                    enemyWheels[i][3].setPosition({
                        x + 85.f, y + 60.f
                        });
                }
            }

            // PART 5: CHECK COLLISION
            for (int i = 0; i < 3; i++)
            {
                if (car.getGlobalBounds().findIntersection(
                    enemyCars[i].getGlobalBounds()))
                {
                    gameOver = true;

                    cout << "GAME OVER! Collision Detected" << endl;
                    cout << "FINAL SCORE: " << score << endl;

                    break;
                }
            }
        }

        // 15. Clear background
        window.clear(grassGreen);

        // 16. Draw road and boundaries
        window.draw(road);
        window.draw(leftLine);
        window.draw(rightLine);

        // 17. Draw lane markings
        for (int i = 0; i < 12; i++)
        {
            window.draw(laneLines[i]);
        }

        // 18.Draw player car
        window.draw(car);
        window.draw(windshield);
        window.draw(rearWindow);

        // Draw player wheels
        for (int i = 0; i < 4; i++)
        {
            window.draw(wheels[i]);
        }

        // 19.Draw enemy cars
        for (int i = 0; i < 3; i++)
        {
            //enemy body
            window.draw(enemyCars[i]);

            // Enemy windows
            window.draw(enemyWindshields[i]);
            window.draw(enemyRearWindows[i]);

            // Enemy wheels
            for (int j = 0; j < 4; j++)
            {
                window.draw(enemyWheels[i][j]);
            }
        }

        // 20. Display frame
        window.display();
    }

    return 0;
}