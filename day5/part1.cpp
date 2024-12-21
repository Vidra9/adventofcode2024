#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>

int main()
{
    std::ifstream inputFile("input.txt");
    std::string line;
    std::map<int, std::vector<int>> rules;
    int total = 0;

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

    while (std::getline(inputFile, line))
    {
        std::vector<int> pages;
        std::map<int, int> pageOccunrances;
        std::size_t found = 0;
        std::size_t startPos = 0;
        bool good = true;

        while (found = line.find(",", startPos))
        {
            int pageNum = std::stoi(line.substr(startPos, (found == std::string::npos) ? found : found + 1));

            for (int page : rules[pageNum])
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

    return 0;
}