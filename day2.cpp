#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int solvePart1(std::vector<std::vector<int>> _reports)
{
    int safe = 0;
    for (std::vector<int> _report : _reports)
    {
        bool descending = _report[0] > _report[1]; //presumably we have at least two elems
        bool is_safe = true;
        for (int i = 1; i < _report.size(); i++)
        {
            if (abs(_report[i-1] - _report[i]) > 3 || abs(_report[i-1] - _report[i]) == 0) {is_safe = false; break;}
            if (descending && _report[i-1] < _report[i]) {is_safe = false; break;}
            else if (!descending && _report[i-1] > _report[i]) {is_safe = false; break;}
        }
        if (is_safe) safe++;
    }
    return safe;
}

int main()
{
    std::ifstream inputFile("input2.txt");
    std::string line;

    std::vector<std::vector<int>> reports;

    // Construct report matrix
    while(std::getline(inputFile, line))
    {
        std::vector<int> report;
        std::stringstream sstream(line);
        int num;
        while (sstream >> num)
        {
            report.push_back(num);
        }
        reports.push_back(report);
    }

    printf("Part 1 output :%d \n", solvePart1(reports));

    return 0;
}