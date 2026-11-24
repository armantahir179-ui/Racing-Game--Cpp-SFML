#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

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

    // Load font
    sf::Font font;

    bool fontLoaded = font.openFromFile(
        "C:/Windows/Fonts/arial.ttf"
    );

    if (!fontLoaded)
    {
        cout << "Font not loaded! Check Arial.ttf path." << endl;
    }

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

    // 11. Create three enemy cars
    sf::RectangleShape enemyCars[3];
    sf::RectangleShape enemyWindshields[3];
    sf::RectangleShape enemyRearWindows[3];
    sf::RectangleShape enemyWheels[3][4];

    // Three lane positions
    float enemyX[3] = { 220.f, 355.f, 490.f };

    // Enemy and player speed
    float enemySpeed = 4.f;
    float playerSpeed = 6.f;

    // Score system
    int score = 0;

    // 12. Set enemy car specifications
    for (int i = 0; i < 3; i++)
    {
        enemyCars[i].setSize({ 85.f, 100.f });
        enemyCars[i].setFillColor(sf::Color::Blue);

        enemyWindshields[i].setSize({ 63.f, 24.f });
        enemyWindshields[i].setFillColor(sf::Color::Cyan);

        enemyRearWindows[i].setSize({ 63.f, 24.f });
        enemyRearWindows[i].setFillColor(sf::Color::Black);

        for (int j = 0; j < 4; j++)
        {
            enemyWheels[i][j].setSize({ 10.f, 22.f });
            enemyWheels[i][j].setFillColor(sf::Color::Black);
        }

        int randomLane = rand() % 3;

        float x = enemyX[randomLane];
        float y = -150.f - (i * 220.f);

        enemyCars[i].setPosition({ x, y });

        enemyWindshields[i].setPosition({ x + 11.f, y + 10.f });
        enemyRearWindows[i].setPosition({ x + 11.f, y + 56.f });

        enemyWheels[i][0].setPosition({ x - 10.f, y + 13.f });
        enemyWheels[i][1].setPosition({ x + 85.f, y + 13.f });
        enemyWheels[i][2].setPosition({ x - 10.f, y + 60.f });
        enemyWheels[i][3].setPosition({ x + 85.f, y + 60.f });
    }

    // PART 5: COLLISION DETECTION
    bool gameOver = false;

    // PART 7: MAIN MENU GUI
    bool gameStarted = false;

    // Main menu background
    sf::RectangleShape menuBackground({ 800.f, 600.f });
    menuBackground.setFillColor(sf::Color(30, 100, 40));

    // Game title
    sf::Text titleText(font, "RACING GAME", 48);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition({ 210.f, 90.f });

    // Start button
    sf::RectangleShape startButton({ 200.f, 70.f });
    startButton.setPosition({ 300.f, 220.f });
    startButton.setFillColor(sf::Color::Green);

    // Start button text
    sf::Text startText(font, "PLAY", 30);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition({ 365.f, 235.f });

    // Red button
    sf::RectangleShape exitButton({ 200.f, 70.f });
    exitButton.setPosition({ 300.f, 330.f });
    exitButton.setFillColor(sf::Color::Red);

    // Red button text
    sf::Text menuGameOverText(font, "GAME OVER", 25);
    menuGameOverText.setFillColor(sf::Color::White);
    menuGameOverText.setPosition({ 325.f, 348.f });

    // Instructions
    sf::Text instructionText(
        font,
        "Use LEFT and RIGHT arrow keys to move",
        20
    );
    instructionText.setFillColor(sf::Color::White);
    instructionText.setPosition({ 190.f, 470.f });

    // PART 8: GAME OVER AND RESTART

    sf::RectangleShape gameOverBackground({ 800.f, 600.f });
    gameOverBackground.setFillColor(sf::Color(20, 20, 20));

    // Game over heading
    sf::Text gameOverTitle(font, "GAME OVER!", 48);
    gameOverTitle.setFillColor(sf::Color::Red);
    gameOverTitle.setPosition({ 255.f, 120.f });

    // Final score text
    sf::Text finalScoreText(font, "Final Score: 0", 30);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setPosition({ 300.f, 220.f });

    // Restart button
    sf::RectangleShape restartButton({ 200.f, 70.f });
    restartButton.setPosition({ 300.f, 300.f });
    restartButton.setFillColor(sf::Color::Green);

    sf::Text restartText(font, "RESTART", 27);
    restartText.setFillColor(sf::Color::Black);
    restartText.setPosition({ 335.f, 318.f });

    // Exit button
    sf::RectangleShape gameOverExitButton({ 200.f, 70.f });
    gameOverExitButton.setPosition({ 300.f, 400.f });
    gameOverExitButton.setFillColor(sf::Color::Red);

    sf::Text gameExitText(font, "EXIT", 27);
    gameExitText.setFillColor(sf::Color::White);
    gameExitText.setPosition({ 370.f, 418.f });

    // Score display during game
    sf::Text scoreText(font, "Score: 0", 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({ 20.f, 20.f });

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

            // MENU AND BUTTON CLICK
            if (const auto* mouse =
                event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouse->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePosition(
                        static_cast<float>(mouse->position.x),
                        static_cast<float>(mouse->position.y)
                    );

                    // MAIN MENU
                    if (!gameStarted)
                    {
                        if (startButton.getGlobalBounds().contains(mousePosition))
                        {
                            gameStarted = true;
                            cout << "GAME STARTED!" << endl;
                        }
                    }

                    // GAME OVER SCREEN
                    else if (gameOver)
                    {
                        // RESTART BUTTON
                        if (restartButton.getGlobalBounds().contains(mousePosition))
                        {
                            gameOver = false;
                            score = 0;

                            cout << "GAME RESTARTED!" << endl;

                            // Reset player car
                            car.setPosition({ 357.5f, 450.f });
                            windshield.setPosition({ 368.5f, 460.f });
                            rearWindow.setPosition({ 368.5f, 506.f });

                            wheels[0].setPosition({ 347.5f, 463.f });
                            wheels[1].setPosition({ 442.5f, 463.f });
                            wheels[2].setPosition({ 347.5f, 510.f });
                            wheels[3].setPosition({ 442.5f, 510.f });

                            // Reset enemy cars
                            for (int i = 0; i < 3; i++)
                            {
                                int randomLane = rand() % 3;

                                float x = enemyX[randomLane];
                                float y = -150.f - (i * 220.f);

                                enemyCars[i].setPosition({ x, y });

                                enemyWindshields[i].setPosition({
                                    x + 11.f, y + 10.f
                                });

                                enemyRearWindows[i].setPosition({
                                    x + 11.f, y + 56.f
                                });

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

                        // EXIT BUTTON
                        if (gameOverExitButton.getGlobalBounds().contains(mousePosition))
                        {
                            window.close();
                        }
                    }
                }
            }
        }

        // PART 2: PLAYER CAR MOVEMENT
        if (gameStarted && !gameOver)
        {
            // Move left
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                if (car.getPosition().x - playerSpeed >= 205.f)
                {
                    car.move({ -playerSpeed, 0.f });
                    windshield.move({ -playerSpeed, 0.f });
                    rearWindow.move({ -playerSpeed, 0.f });

                    for (int i = 0; i < 4; i++)
                    {
                        wheels[i].move({ -playerSpeed, 0.f });
                    }
                }
            }

            // Move right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                if (car.getPosition().x + playerSpeed <= 510.f)
                {
                    car.move({ playerSpeed, 0.f });
                    windshield.move({ playerSpeed, 0.f });
                    rearWindow.move({ playerSpeed, 0.f });

                    for (int i = 0; i < 4; i++)
                    {
                        wheels[i].move({ playerSpeed, 0.f });
                    }
                }
            }
        }

        // 14. Move enemy cars
        if (gameStarted && !gameOver)
        {
            for (int i = 0; i < 3; i++)
            {
                enemyCars[i].move({ 0.f, enemySpeed });
                enemyWindshields[i].move({ 0.f, enemySpeed });
                enemyRearWindows[i].move({ 0.f, enemySpeed });

                for (int j = 0; j < 4; j++)
                {
                    enemyWheels[i][j].move({ 0.f, enemySpeed });
                }

                // Check if enemy leaves screen
                if (enemyCars[i].getPosition().y > 600.f)
                {
                    score++;

                    cout << "Score: " << score << endl;

                    int randomLane = rand() % 3;

                    float x = enemyX[randomLane];
                    float y = -150.f;

                    enemyCars[i].setPosition({ x, y });

                    enemyWindshields[i].setPosition({
                        x + 11.f, y + 10.f
                    });

                    enemyRearWindows[i].setPosition({
                        x + 11.f, y + 56.f
                    });

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

                    finalScoreText.setString(
                        "Final Score: " + to_string(score)
                    );

                    break;
                }
            }
        }

        // Update score text
        scoreText.setString("Score: " + to_string(score));

        // PART 15: DRAW SCREENS

        if (!gameStarted)
        {
            // MAIN MENU
            window.clear();

            window.draw(menuBackground);
            window.draw(titleText);

            window.draw(startButton);
            window.draw(startText);

            window.draw(exitButton);
            window.draw(menuGameOverText);

            window.draw(instructionText);
        }
        else if (gameOver)
        {
            // GAME OVER SCREEN
            window.clear(sf::Color::Black);

            window.draw(gameOverBackground);
            window.draw(gameOverTitle);
            window.draw(finalScoreText);

            window.draw(restartButton);
            window.draw(restartText);

            window.draw(gameOverExitButton);
            window.draw(gameExitText);
        }
        else
        {
            // GAME BACKGROUND
            window.clear(grassGreen);

            // Draw road and boundaries
            window.draw(road);
            window.draw(leftLine);
            window.draw(rightLine);

            // Draw lane markings
            for (int i = 0; i < 12; i++)
            {
                window.draw(laneLines[i]);
            }

            // Draw player car
            window.draw(car);
            window.draw(windshield);
            window.draw(rearWindow);

            for (int i = 0; i < 4; i++)
            {
                window.draw(wheels[i]);
            }

            // Draw enemy cars
            for (int i = 0; i < 3; i++)
            {
                window.draw(enemyCars[i]);
                window.draw(enemyWindshields[i]);
                window.draw(enemyRearWindows[i]);

                for (int j = 0; j < 4; j++)
                {
                    window.draw(enemyWheels[i][j]);
                }
            }

            // Draw score
            window.draw(scoreText);
        }

        // Display frame
        window.display();
    }

    return 0;
}