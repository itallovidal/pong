#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SFML/Graphics.hpp>

#define WINDOW_PADDING 12.f
#define BALL_DEFAULT_VELOCITY 100.f
#define BALL_DEFAULT_ACCELERATION 200.f
#define BALL_MAX_SPEED 300.f

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