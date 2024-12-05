#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

    std::sort(list1.begin(), list1.end(), [](int left, int right){return left <= right;});
    std::sort(list2.begin(), list2.end(), [](int left, int right){return left <= right;});

    int total = 0;
    for (int i = 0; i < list1.size(); i++)
    {
        total += abs(list1[i] - list2[i]);
    }

    printf("%d", total);

    return 0;
}