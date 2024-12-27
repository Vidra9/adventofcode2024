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

void rotate90(DIRECTION& dir)
{
    switch (dir)
    {
    case DIRECTION::UP:
        dir = DIRECTION::RIGHT;
        break;
    case DIRECTION::RIGHT:
        dir = DIRECTION::DOWN;
        break;
    case DIRECTION::DOWN:
        dir = DIRECTION::LEFT;
        break;
    case DIRECTION::LEFT:
        dir = DIRECTION::UP;
        break;
    }
}

DIRECTION rotated90(const DIRECTION& dir)
{
    switch (dir)
    {
    case DIRECTION::UP: return DIRECTION::RIGHT;
    case DIRECTION::RIGHT: return DIRECTION::DOWN;
    case DIRECTION::DOWN: return DIRECTION::LEFT;
    case DIRECTION::LEFT: return DIRECTION::UP;
    }
    return DIRECTION::UP;
}

void print2DArray(const std::vector<std::vector<int>>& vec)
{
    printf_s("\n");
    for(const std::vector<int>& v : vec)
    {
        for(const int& num : v)
        {
            printf_s("%d", num);
        }
        printf_s("\n");
    }
}

std::pair<int, int> findClosestObstacleInDir(DIRECTION dir, const std::vector<std::pair<int, int>> _obstacles, const std::pair<int, int>& pos)
{
    std::pair<int, int> closetObs = pos;
    int closestDist = INT_MAX;
    switch (dir)
    {
    case DIRECTION::UP:
        for (std::pair<int, int> obs : _obstacles)
        {
            if(obs.second == pos.second && abs(obs.first - pos.first) < closestDist && obs.first < pos.first)
            {
                closestDist = abs(obs.first - pos.first);
                closetObs = obs;
            }
        }
        break;
    case DIRECTION::RIGHT:
        for (std::pair<int, int> obs : _obstacles)
        {
            if(obs.first == pos.first && abs(obs.second - pos.second) < closestDist && obs.second > pos.second)
            {
                closestDist = abs(obs.second - pos.second);
                closetObs = obs;
            }
        }
        break;
    case DIRECTION::DOWN:
        for (std::pair<int, int> obs : _obstacles)
        {
            if(obs.second == pos.second && abs(obs.first - pos.first) < closestDist && obs.first > pos.first)
            {
                closestDist = abs(obs.first - pos.first);
                closetObs = obs;
            }
        }
        break;
    case DIRECTION::LEFT:
        for (std::pair<int, int> obs : _obstacles)
        {
            if(obs.first == pos.first && abs(obs.second - pos.second) < closestDist && obs.second < pos.second)
            {
                closestDist = abs(obs.second - pos.second);
                closetObs = obs;
            }
        }
    }
    return closetObs;
}

std::pair<int, int> getPointBefore(std::pair<int, int> point, DIRECTION dir)
{
    switch (dir)
    {
    case DIRECTION::UP:    return std::pair<int, int>(point.first + 1, point.second);
    case DIRECTION::RIGHT: return std::pair<int, int>(point.first, point.second - 1);
    case DIRECTION::DOWN:  return std::pair<int, int>(point.first - 1, point.second);
    case DIRECTION::LEFT:  return std::pair<int, int>(point.first, point.second + 1);
    }
    return std::pair<int, int>();
}

std::pair<int, int> getPointAfter(std::pair<int, int> point, DIRECTION dir)
{
    switch (dir)
    {
    case DIRECTION::UP:    return std::pair<int, int>(point.first - 1, point.second);
    case DIRECTION::RIGHT: return std::pair<int, int>(point.first, point.second + 1);
    case DIRECTION::DOWN:  return std::pair<int, int>(point.first + 1, point.second);
    case DIRECTION::LEFT:  return std::pair<int, int>(point.first, point.second - 1);
    }
    return std::pair<int, int>();
}