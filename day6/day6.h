#include <string>
enum DIRECTION
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
};

std::string getDirectionName(DIRECTION dir)
{
    switch (dir)
    {
    case DIRECTION::UP: return "UP";
    case DIRECTION::RIGHT: return "RIGHT";
    case DIRECTION::DOWN: return "DOWN";
    case DIRECTION::LEFT: return "LEFT";
    default: return "UNKNOWN";
    }
}