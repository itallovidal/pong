#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define WELCOME_MESSAGE "Bem vindo ao Porongo Pong"

sf::Text titleComponent(sf::Font font, sf::RenderWindow *window){
    sf::Text text(font);
    text.setString(WELCOME_MESSAGE);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    float textSize = text.getLocalBounds().size.x;
    float centerScreen = window->getSize().x / 2;
    float halfText = floor(textSize / 2);

    text.setPosition({centerScreen - halfText , 10});

    return text;
}

int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600u}), "Porongo Pong");
    window.setFramerateLimit(144);
    
    sf::Font font;
    if (!font.openFromFile("src/assets/roboto.ttf"))
    {
        std::cout << "Error importing font" << "\n" ;
        return 1;
    }


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        window.draw(titleComponent(font, &window));

        window.display();
    }
}
