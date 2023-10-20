#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(600, 600), "Pong Game - Jason");

    // CREATES FONT
    sf::Font Space_Invaders_Font;
    Space_Invaders_Font.loadFromFile("space_invaders.ttf");

    // Creates Score Text
    sf::Text Score;
    Score.setString("Player 1: 0, Player 2: 0");
    Score.setFillColor(sf::Color::White);
    Score.setCharacterSize(16);
    Score.setPosition(sf::Vector2f(185, 5));
    Score.setFont(Space_Invaders_Font);

    // CREATES THE LEFT RECTANGLE
    sf::RectangleShape LeftShape;
    LeftShape.setFillColor(sf::Color::White);
    LeftShape.setSize(sf::Vector2f(25, 175));
    LeftShape.setPosition(sf::Vector2f(50, 50));

    // CREATES THE RIGHT RECTANGLE
    sf::RectangleShape RightShape;
    RightShape.setFillColor(sf::Color::White);
    RightShape.setSize(sf::Vector2f(25, 175));
    RightShape.setPosition(sf::Vector2f(525, 50));

    // Calculate the center of the screen
    sf::Vector2f centerOfScreen(app.getSize().x / 2, app.getSize().y / 2);

    // CREATES THE BALL
    sf::CircleShape Ball;
    Ball.setFillColor(sf::Color::White);
    Ball.setRadius(15);
    Ball.setPosition(centerOfScreen);

    // Ball movement variables
    sf::Vector2f ballVelocity(0.08f, 0.08f); // Slower ball speed

    // Score variables
    int player1Score = 0;
    int player2Score = 0;

    // Create an ending screen font
    sf::Font endingFont;
    endingFont.loadFromFile("space_invaders.ttf");

    // Create an ending screen text
    sf::Text endingText;
    endingText.setFont(endingFont);
    endingText.setCharacterSize(40);
    endingText.setFillColor(sf::Color::White);
    endingText.setPosition(150, 250);

    // Set the game-ending score to 10
    const int gameEndingScore = 10;

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            // Keyboard input for paddle movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                RightShape.move(0, -6);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                RightShape.move(0, 6);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                LeftShape.move(0, -6);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                LeftShape.move(0, 6);
            }
        }

        // Ball movement
        Ball.move(ballVelocity);

        // Ball collision with top and bottom
        if (Ball.getPosition().y <= 0 || Ball.getPosition().y >= app.getSize().y - Ball.getRadius() * 2)
        {
            ballVelocity.y = -ballVelocity.y;
        }

        // Ball collision with paddles
        if (Ball.getGlobalBounds().intersects(LeftShape.getGlobalBounds()) ||
                Ball.getGlobalBounds().intersects(RightShape.getGlobalBounds()))
        {
            ballVelocity.x = -ballVelocity.x;
        }

        // Ball out of bounds (player scores)
        if (Ball.getPosition().x < 0)
        {
            player2Score++;
            Ball.setPosition(centerOfScreen);
            ballVelocity = sf::Vector2f(0.08f, 0.08f); // Reset ball speed
        }
        else if (Ball.getPosition().x > app.getSize().x)
        {
            player1Score++;
            Ball.setPosition(centerOfScreen);
            ballVelocity = sf::Vector2f(-0.08f, -0.08f); // Reset ball speed
        }

        // Update the score text
        Score.setString("Player 1: " + std::to_string(player1Score) + ", Player 2: " + std::to_string(player2Score));

        // Clear screen
        app.clear();
        app.draw(LeftShape);
        app.draw(RightShape);
        app.draw(Ball);
        app.draw(Score);

        // Check for game end conditions
        if (player1Score == gameEndingScore)
        {
            endingText.setString("Player 1 Wins!");
            app.draw(endingText);
            app.display();
            sf::sleep(sf::seconds(3)); // Display ending screen for 3 seconds
            app.close();
        }
        else if (player2Score == gameEndingScore)
        {
            endingText.setString("Player 2 Wins!");
            app.draw(endingText);
            app.display();
            sf::sleep(sf::seconds(3)); // Display ending screen for 3 seconds
            app.close();
        }
        else
        {
            app.display();
        }
    }

    return EXIT_SUCCESS;
}
