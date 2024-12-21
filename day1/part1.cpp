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

    std::sort(leftList.begin(), leftList.end(), [](int left, int right){return left <= right;});
    std::sort(rightList.begin(), rightList.end(), [](int left, int right){return left <= right;});

    int total = 0;
    for (int i = 0; i < leftList.size(); i++)
    {
        total += abs(leftList[i] - rightList[i]);
    }

    printf("%d \n", total);

    return 0;
}