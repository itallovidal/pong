#include "utility.hpp"
#include "entities.hpp"

sf::Text scoreBoardBuilder(sf::Font font, struct WindowUtilityInfo *window, struct Score score)
{
    sf::Text text(font);
    std::string player1Score = std::to_string(score.player1);
    std::string player2Score = std::to_string(score.player2);
    std::string board = "Placar: " + player1Score + " - " + player2Score;

    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    float textSize = text.getLocalBounds().size.x;
    float halfText = floor(textSize / 2);

    text.setPosition({window->halfWindowX - halfText, WINDOW_PADDING});

    return text;
}

sf::Font loadFont()
{
    sf::Font font;
    if (!font.openFromFile("src/assets/roboto.ttf"))
    {
        std::cout << "Error importing font" << "\n";
        return font;
    }

    return font;
}

int main()
{
    sf::VideoMode windowConfig = sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT});
    sf::RenderWindow window = sf::RenderWindow(windowConfig, "Porongo Pong");
    window.setFramerateLimit(144);

    sf::Clock clock;
    float deltatime;

    sf::Vector2u windowSize = window.getSize();
    struct WindowUtilityInfo windowInfo = {
        .halfWindowX = windowSize.x / 2.f,
        .halfWindowY = windowSize.y / 2.f,
        .fullWindowX = windowSize.x,
        .fullWindowY = windowSize.y,
    };

    sf::Font font = loadFont();

    Ball ball(sf::Color::White, 16.f);
    Player player1(1, 20, "Player 1");
    Player player2(2, 20, "Player 2");

    player1.place(&windowInfo);
    player2.place(&windowInfo);
    ball.place(&windowInfo);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const sf::Event::KeyPressed *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {

                // create a event handler class?
                if (keyPressed->code == sf::Keyboard::Key::W)
                {
                    player1.handleMoviment(PlayerMoviment::UP);
                }

                if (keyPressed->code == sf::Keyboard::Key::S)
                {
                    player1.handleMoviment(PlayerMoviment::DOWN);
                }

                if (keyPressed->code == sf::Keyboard::Key::Up)
                {
                    player2.handleMoviment(PlayerMoviment::UP);
                }

                if (keyPressed->code == sf::Keyboard::Key::Down)
                {
                    player2.handleMoviment(PlayerMoviment::DOWN);
                }
            }
        }

        deltatime = clock.restart().asSeconds();
        window.clear();

        sf::Text scoreBoard = scoreBoardBuilder(
            font,
            &windowInfo,
            Score{
                .player1 = player1.getScore(),
                .player2 = player2.getScore()});

        window.draw(scoreBoard);

        ball.move(deltatime);
        ball.handleCollision(&windowInfo, &player1, &player2);
        window.draw(ball.getShape());
        window.draw(player1.getShape());
        window.draw(player2.getShape());

        window.display();
    }
}