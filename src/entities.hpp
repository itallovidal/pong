#include <iostream>
#include <cmath>
#include "utility.hpp"

class Player
{
    int id;
    int score = 0;
    float velocity;
    std::string name;

    sf::RectangleShape shape;
    float shapeWidth = 15.f;
    float shapeHeight = 120.f;
    struct ShapeBounds shapeBounds;

public:
    Player(int id, float velocity, std::string name)
    {
        this->id = id;
        this->name = name;
        this->velocity = velocity;
        this->shape.setSize({this->shapeWidth, this->shapeHeight});
        this->shape.setFillColor(sf::Color::White);
    }

    void updateBounds()
    {
        sf::FloatRect shapeBounds = this->shape.getGlobalBounds();
        this->shapeBounds = {
            .minX = shapeBounds.position.x,
            .maxX = shapeBounds.position.x + shapeBounds.size.x,
            .minY = shapeBounds.position.y,
            .maxY = shapeBounds.position.y + shapeBounds.size.y};
    };

    struct ShapeBounds *getShapeBounds()
    {
        return &this->shapeBounds;
    };

    sf::RectangleShape getShape()
    {
        return this->shape;
    }

    void place(WindowUtilityInfo *windowInfo)
    {
        float y = windowInfo->halfWindowY - (this->shape.getLocalBounds().size.y / 2.f);

        if (this->id == 1)
        {
            this->shape.setPosition({WINDOW_PADDING, y});
            this->updateBounds();
            return;
        }

        float spaceFromBorder = WINDOW_PADDING + this->shape.getLocalBounds().size.x;
        float x = windowInfo->fullWindowX - (spaceFromBorder);
        this->shape.setPosition({x, y});
        this->updateBounds();
    }

    int getScore()
    {
        return this->score;
    }

    void increaseScore()
    {
        this->score++;
    }

    void handleMoviment(PlayerMoviment moveTo)
    {
        sf::Vector2f currentPosition = this->shape.getPosition();
        if (moveTo == PlayerMoviment::UP)
        {
            this->shape.move({0, -100.f});
        }

        if (moveTo == PlayerMoviment::DOWN)
        {
            this->shape.move({0, 100.f});
        }

        this->updateBounds();
    }
};

class Ball
{
    sf::CircleShape shape;
    float accel;
    float velocity;
    struct ShapeBounds shapeBounds;

public:
    Ball(sf::Color color, float size)
    {
        this->shape.setRadius(size);
        this->shape.setFillColor(color);
        this->updateBounds();
    };

    void place(WindowUtilityInfo *windowInfo)
    {
        float x = windowInfo->halfWindowX - (this->shape.getLocalBounds().size.x / 2);
        float y = windowInfo->halfWindowY - (this->shape.getLocalBounds().size.y / 2);

        this->shape.setPosition({x, y});

        this->velocity = BALL_DEFAULT_VELOCITY;
        this->accel = BALL_DEFAULT_ACCELERATION;
    }

    void updateBounds()
    {
        sf::FloatRect shapeBounds = this->shape.getGlobalBounds();
        this->shapeBounds = {
            .minX = shapeBounds.position.x,
            .maxX = shapeBounds.position.x + shapeBounds.size.x,
            .minY = shapeBounds.position.y,
            .maxY = shapeBounds.position.y + shapeBounds.size.y};
    };

    struct ShapeBounds *getShapeBounds()
    {
        return &this->shapeBounds;
    };

    void move(float deltatime)
    {
        float displacement;

        // todo: what if velocity is -310?
        if (this->velocity < BALL_MAX_SPEED)
        {
            // uniformly accelerated rectilinear moviment
            // velocity * delta * time + 1/2 * acceleration * deltatime²
            displacement = this->velocity * deltatime + (.5f * this->accel * pow(deltatime, 2));

            // update velocity to increase velocity in next frame
            this->velocity += this->accel * deltatime;
        }
        else
        {
            std::cout << "max velocity reached" << "\n";
            std::cout << this->velocity << "\n";

            // we limit hour velocity to 300
            this->velocity = 300.f;
            // if we reach max speed, we will maintain our displacement constant
            displacement = this->velocity * deltatime;
        }

        this->shape.move({displacement, 0});
        this->updateBounds(); // updating where the ball is
    }

    sf::CircleShape getShape()
    {
        return this->shape;
    }

    void invertDirection()
    {
        this->velocity *= -1;
        this->accel *= -1;
    }

    void handleCollision(WindowUtilityInfo *windowInfo, Player *player1, Player *player2)
    {
        float ballPositionX = this->shape.getPosition().x;

        if (ballPositionX >= windowInfo->fullWindowX)
        {
            player1->increaseScore();
            this->place(windowInfo);
        }

        // left border
        if (ballPositionX <= 0)
        {
            player2->increaseScore();
            this->place(windowInfo);
        }

        if (this->getShapeBounds()->maxX >= player2->getShapeBounds()->minX &&
            this->getShapeBounds()->maxY >= player2->getShapeBounds()->minY &&
            this->getShapeBounds()->minY <= player2->getShapeBounds()->maxY)
        {
            this->invertDirection();
        }

        if (this->getShapeBounds()->minX <= player1->getShapeBounds()->maxX &&
            this->getShapeBounds()->maxY >= player1->getShapeBounds()->minY &&
            this->getShapeBounds()->minY <= player1->getShapeBounds()->maxY)
        {
            this->invertDirection();
        }
    }
};