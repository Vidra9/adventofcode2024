#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include "day4.h"

bool checkCrossMAS(std::vector<std::string>& lines, coord s_coord)
{
    int x = s_coord.x;
    int y = s_coord.y;
    bool first_diag = false;

    if(x < 1 || x + 1 >= lines.size() || y < 1 || y + 1 >= lines[x].size()) return false;

    // check first diagonal
    if((lines[x-1][y-1] == 'M' && lines[x+1][y+1] == 'S') 
    || (lines[x-1][y-1] == 'S' && lines[x+1][y+1] == 'M')) first_diag = true;

    if (((lines[x-1][y+1] == 'M' && lines[x+1][y-1] == 'S') 
    || (lines[x-1][y+1] == 'S' && lines[x+1][y-1] == 'M')) && first_diag) return true;

    return false;
}

int main()
{
    std::ifstream inputFile("input.txt");
    std::vector<std::string> lines;    
    std::string line;

    while(std::getline(inputFile, line))
    {
        lines.push_back(line);
    }

    int total = 0;
    std::vector<coord> used_a;

    for(int i = 0; i < lines.size(); i++)
    {
        for(int j = 0; j < lines[i].size(); j++)
        {
            char x = lines[i][j];
            if (x != 'A' && !vectorContains(used_a, coord{i, j})) continue;
            if(checkCrossMAS(lines, coord{i, j})) total++;
        }
    }

    printf("Part 2: %d \n", total);

    return 0;
}