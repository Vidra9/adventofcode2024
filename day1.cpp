#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

int solvePart1(std::vector<int> leftList, std::vector<int> rightList)
{
    std::sort(leftList.begin(), leftList.end(), [](int left, int right){return left <= right;});
    std::sort(rightList.begin(), rightList.end(), [](int left, int right){return left <= right;});

    int total = 0;
    for (int i = 0; i < leftList.size(); i++)
    {
        total += abs(leftList[i] - rightList[i]);
    }

    return total;
}

int solvePart2(std::vector<int> leftList, std::vector<int> rightList)
{
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

    return total;
}

int main()
{
    std::ifstream inputFile("input1.txt");
    std::string line;

    std::vector<int> list1, list2;

    while(std::getline(inputFile, line))
    {
        list1.push_back(std::stoi(line.substr(0, line.find(" "))));
        list2.push_back(std::stoi(line.substr(line.rfind(" ") + 1, line.length())));
    }

    printf("Part 1 output: %d \n", solvePart1(list1, list2));
    printf("Part 2 output: %d \n", solvePart2(list1, list2));

    return 0;
}