#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;

    std::vector<int> leftList, rightList;

    while(std::getline(inputFile, line))
    {
        leftList.push_back(std::stoi(line.substr(0, line.find(" "))));
        rightList.push_back(std::stoi(line.substr(line.rfind(" ") + 1, line.length())));
    }

    std::map<int, int> occuranceMap;
    for (int number : rightList)
    {
        occuranceMap.try_emplace(number, 0);
        occuranceMap[number]++;
    }

    int total = 0;
    for (int number : leftList)
    {
        total += number * occuranceMap[number];
    }

    printf("%d \n", total);

    return 0;
}