#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics.hpp>

#define WINDOW_PADDING 12.f
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define BALL_DEFAULT_VELOCITY 100.f
#define BALL_DEFAULT_ACCELERATION 50.f
#define BALL_MAX_SPEED 1400.f

enum BallDirection
{
    X,
    Y
};

struct ShapeBounds
{
    float minX;
    float maxX;
    float minY;
    float maxY;
};

struct Score
{
    int player1;
    int player2;
};

enum PlayerMoviment
{
    UP,
    DOWN
};

struct WindowUtilityInfo
{
    float halfWindowX;
    float halfWindowY;
    float fullWindowX;
    float fullWindowY;
};

#endif // UTILITY_HPP