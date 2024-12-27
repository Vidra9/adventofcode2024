#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "day6.h"

enum STEP_RESULT {MOVED, OBSTACLE_HIT, MAP_EDGE, LOOPED};

std::pair<int, int> originalStart;
std::vector<std::vector<int>> map;
std::vector<std::pair<int, int>> attempted_obs;
int total = 0;

struct visited_tile
{
    std::pair<int, int> pos;
    DIRECTION dir;

    visited_tile(const std::pair<int, int>& t, const DIRECTION& d)
    {
        pos = t;
        dir = d;
    }

    bool operator==(const visited_tile& t) const
    {
        return pos == t.pos && dir == t.dir;
    }
};

STEP_RESULT guardStep(std::pair<int, int>& pos, DIRECTION& dir, const std::vector<std::pair<int, int>>& _obstacles, std::vector<visited_tile>& visited)
{
    std::pair<int, int> step = getPointAfter(pos, dir);

    if (step.first >= map.size() || step.second >= map[0].size())
    {
        return STEP_RESULT::MAP_EDGE;
    }
    bool obsHit = false;
    for (const auto& obs : _obstacles)
    {
        if (obs == step)
        {
            rotate90(dir);
            return STEP_RESULT::OBSTACLE_HIT;
        }
    }
    
    visited_tile v = visited_tile(pos, dir);
    for(visited_tile& tile : visited)
    {
        if(tile == v)
        {
            return STEP_RESULT::LOOPED;
        }
    }
    visited.push_back(v);

    pos = step;
    return STEP_RESULT::MOVED;
}

bool tryLooping(std::pair<int, int> pos, DIRECTION dir, std::vector<std::pair<int, int>> _obstacles, std::vector<visited_tile> visited)
{
    std::pair<int, int> point = getPointAfter(pos, dir);

    if (point.first >= map.size() || point.second >= map[0].size() || point == originalStart) return false;
    for (auto& obs : _obstacles)
    {
        if (obs == point) return false;
    }
    for (auto& obs : attempted_obs)
    {
        if (obs == point) return false;
    }

    // place obstacle in front of guard
    _obstacles.push_back(point);
    attempted_obs.push_back(point);

    while(true)
    {
        STEP_RESULT step = guardStep(pos, dir, _obstacles, visited);
        switch (step)
        {
        case STEP_RESULT::MAP_EDGE: return false;
        case STEP_RESULT::LOOPED: return true;
        default: break;
        }
    }
    return false;
}

int main()
{
    // std::ifstream inputFile("../test.txt");
    std::ifstream inputFile("input.txt");
    std::string line;
    
    std::vector<std::pair<int, int>> obstacles;
    std::pair<int, int> startPos;
    DIRECTION movementDir = DIRECTION::UP;
    std::vector<visited_tile> visited_tiles;
    
    int lineNum = 0;
    while(std::getline(inputFile, line))
    {
        map.push_back(std::vector<int>());
        for(int i = 0; i < line.length(); i++)
        {
            const char& c = line[i];
            if (c == '^') startPos = std::pair<int, int>(lineNum, i);
            if (c == '#') obstacles.push_back(std::pair<int, int>(lineNum, i));

            map[lineNum].push_back(0);
        }
        lineNum++;
    }
    originalStart = startPos;
    int i;

    if(tryLooping(startPos, movementDir, obstacles, visited_tiles))
        total++;

    while(guardStep(startPos, movementDir, obstacles, visited_tiles) != STEP_RESULT::MAP_EDGE)
    {
        printf_s("Path iteration: %d\n", i++);
        if(tryLooping(startPos, movementDir, obstacles, visited_tiles))
            total++;
    }

    // while(pathGuard(movementDir, startPos, obstacles, false))
    {
        // printf_s("guard pos: %d %d - %s\n", startPos.first, startPos.second, getDirectionName(movementDir).c_str());
    }

    // pathGuard(movementDir, startPos, obstacles, true);

    printf_s("%d", total);
    
    return 0;
}