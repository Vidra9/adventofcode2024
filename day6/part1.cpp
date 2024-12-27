#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "day6.h"

std::vector<std::vector<int>> map;
int total = 0;

bool pathGuard(DIRECTION& dir, std::pair<int, int>& start, const std::vector<std::pair<int, int>> _obstacles, bool exit)
{
    bool obsHit = false;
    std::pair<int, int> obs = findClosestObstacleInDir(dir, _obstacles, start);
    switch (dir)
    {
    case DIRECTION::UP:
        if (obs != start || exit)
        {
            for (int i = start.first; i >= (exit ? 0 : obs.first + 1); i--)
            {
                if (map[i][start.second] == 0)
                {
                    total++;
                    map[i][start.second] = 1;
                }
            }
            rotate90(dir);
            start = obs;
            start.first++;
            obsHit = true;
        }
        break;
    case DIRECTION::RIGHT:
        if (obs != start || exit)
        {
            for (int i = start.second; i < (exit ? map[start.first].size() : obs.second); i++)
            {
                if (map[start.first][i] == 0)
                {
                    total++;
                    map[start.first][i] = 1;
                }
            }
            rotate90(dir);
            start = obs;
            start.second--;
            obsHit = true;
        }
        break;
    case DIRECTION::DOWN:
        if (obs != start || exit)
        {
            for (int i = start.first; i < (exit ? map.size() : obs.first); i++)
            {
                if (map[i][start.second] == 0)
                {
                    total++;
                    map[i][start.second] = 1;
                }
            }
            rotate90(dir);
            start = obs;
            start.first--;
            obsHit = true;
        }
        break;
    case DIRECTION::LEFT:
        if (obs != start || exit)
        {
            for (int i = start.second; i >= (exit ? 0 : obs.second + 1); i--)
            {
                if (map[start.first][i] == 0)
                {
                    total++;
                    map[start.first][i] = 1;
                }
            }
            rotate90(dir);
            start = obs;
            start.second++;
            obsHit = true;
        }
        break;
    default:
        break;
    }
    return obsHit;
}

int main()
{
    // std::ifstream inputFile("../test.txt");
    std::ifstream inputFile("input.txt");
    std::string line;
    
    std::vector<std::pair<int, int>> obstacles;
    std::pair<int, int> startPos;

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
    
    DIRECTION movementDir = DIRECTION::UP;
    while(pathGuard(movementDir, startPos, obstacles, false))
    {
        // printf_s("guard pos: %d %d - %s\n", startPos.first, startPos.second, getDirectionName(movementDir).c_str());
    }

    pathGuard(movementDir, startPos, obstacles, true);

    printf_s("%d", total);
    // print2DArray(map);

    return 0;
}