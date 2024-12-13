#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

struct coord 
{
    int x; int y;
    bool operator==(const coord& rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
};

enum DIRECTION
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    UP_LEFT = 4,
    UP_RIGHT = 5,
    DOWN_LEFT = 6,
    DOWN_RIGHT = 7
};

template<typename T>
bool vectorContains(std::vector<T>& vec, T item)
{
    for (T& elem : vec)
    {
        if(elem == item)
        {
            return true;
        }
    }

    return false;
}

bool checkXMAS(std::vector<std::string>& lines, coord start_coord, DIRECTION dir)
{
    int x = start_coord.x;
    int y = start_coord.y;
    switch (dir)
    {
    case DIRECTION::UP:
        if (x < 3) return false;
        if (lines[x-1][y] == 'M' && lines[x-2][y] == 'A' && lines[x-3][y] == 'S') return true;
        break;
    
    case DIRECTION::DOWN:
        if (x+3 >= lines.size()) return false;
        if (lines[x+1][y] == 'M' && lines[x+2][y] == 'A' && lines[x+3][y] == 'S') return true;
        break;

    case DIRECTION::LEFT:
        if (y < 3) return false;
        if (lines[x][y-1] == 'M' && lines[x][y-2] == 'A' && lines[x][y-3] == 'S') return true;
        break;

    case DIRECTION::RIGHT:
        if (y+3 >= lines[x].size()) return false;
        if (lines[x][y+1] == 'M' && lines[x][y+2] == 'A' && lines[x][y+3] == 'S') return true;
        break;

    case DIRECTION::UP_LEFT:
        if (x < 3 || y < 3) return false;
        if (lines[x-1][y-1] == 'M' && lines[x-2][y-2] == 'A' && lines[x-3][y-3] == 'S') return true;
        break;

    case DIRECTION::UP_RIGHT:
        if (x < 3 || y+3 >= lines[x].size()) return false;
        if (lines[x-1][y+1] == 'M' && lines[x-2][y+2] == 'A' && lines[x-3][y+3] == 'S') return true;
        break;

    case DIRECTION::DOWN_LEFT:
        if (x+3 >= lines.size() || y < 3) return false;
        if (lines[x+1][y-1] == 'M' && lines[x+2][y-2] == 'A' && lines[x+3][y-3] == 'S') return true;
        break;

    case DIRECTION::DOWN_RIGHT:
        if (x+3 >= lines.size() || y+3 >= lines[x].size()) return false;
        if (lines[x+1][y+1] == 'M' && lines[x+2][y+2] == 'A' && lines[x+3][y+3] == 'S') return true;
        break;

    default:
        break;
    }

    return false;
}

int solvePart1(std::vector<std::string> lines)
{
    int total = 0;
    std::vector<coord> used_x;

    for(int i = 0; i < lines.size(); i++)
    {
        for(int j = 0; j < lines[i].size(); j++)
        {
            char x = lines[i][j];
            if (x != 'X' && !vectorContains(used_x, coord{i, j})) continue;
            int num = 0;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::UP)) num++;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::DOWN)) num++;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::LEFT)) num++;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::RIGHT)) num++;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::UP_LEFT)) num++;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::UP_RIGHT)) num++;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::DOWN_LEFT)) num++;
            if(checkXMAS(lines, coord{i ,j}, DIRECTION::DOWN_RIGHT)) num++;
            if(num > 0)
            {
                total += num;
                used_x.push_back(coord{i, j});
            }
        }
    }

    return total;
}

int solvePart2(std::vector<std::string> lines)
{
    return 0;
}

int main()
{
    std::ifstream inputFile("input4.txt");
    std::vector<std::string> _lines;    
    std::string line;

    while(std::getline(inputFile, line))
    {
        _lines.push_back(line);
    }

    printf("Part 1: %d", solvePart1(_lines));

    return 0;
}