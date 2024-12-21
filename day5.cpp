#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

void solvePart1(std::ifstream& input, std::map<int, std::vector<int>>& _rules)
{
    int total = 0;
    std::string _line;

    while (std::getline(input, _line))
    {
        std::vector<int> pages;
        std::map<int, int> pageOccunrances;
        std::size_t found = 0;
        std::size_t startPos = 0;

        bool good = true;

        while (found = _line.find(",", startPos))
        {

            int pageNum = std::stoi(_line.substr(startPos, (found == std::string::npos) ? found : found + 1));

            for (int page : _rules[pageNum])
            {
                bool foundx = false;
                for (int x : pages)
                {
                    if (x == page) 
                    {
                        foundx = true;
                        break;
                    }
                }
                if (foundx)
                {
                    good = false;
                    break;
                }
            }

            pages.push_back(pageNum);

            if (found == std::string::npos) break;

            startPos = found + 1;
        }

        if (good)
        {
            total += pages[pages.size() / 2];
        }
    }

    std::cout<<total<<std::endl;
}

void solvePart2(std::ifstream& input, std::map<int, std::vector<int>>& _rules)
{
    int total = 0;
    std::string _line;

    while (std::getline(input, _line))
    {
        std::vector<int> pages;
        std::map<int, int> pageOccunrances;
        std::size_t found = 0;
        std::size_t startPos = 0;

        bool good = true;

        // pages array
        while (found = _line.find(",", startPos))
        {
            const int pageNum = std::stoi(_line.substr(startPos, (found == std::string::npos) ? found : found + 1));

            pages.push_back(pageNum);

            if (found == std::string::npos) break;

            startPos = found + 1;
        }
        
        for (int i = 0; i < pages.size(); i++)
        {
            const int ruleNum = pages[i];
            for (int rule : _rules[ruleNum])
            {
                bool foundx = false;
                for (int j = 0; j < i; j++)
                {
                    if (pages[j] == rule) 
                    {
                        int tmp = pages[i];
                        pages[i] = pages[j];
                        pages[j] = tmp;
                        i = j;
                        foundx = true;
                        break;
                    }
                }
                if (foundx)
                {
                    good = false;
                    
                }
            }
        }

        if (!good)
        {
            total += pages[pages.size() / 2];
        }
    }

    std::cout<<total<<std::endl;
}

int main()
{
    std::ifstream inputFile("input5.txt");
    std::string line;
    std::map<int, std::vector<int>> rules;
    int i = 1;

    while (std::getline(inputFile, line))
    {
        if (line.empty()) break;
        else 
        {
            int x = std::stoi(line.substr(0, line.find('|')));
            int y = std::stoi(line.substr(line.find('|') + 1));
            rules[x].push_back(y);

        }
    }

    solvePart1(inputFile, rules);
    solvePart2(inputFile, rules);

    return 0;
}