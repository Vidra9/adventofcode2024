#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int FindReportError(std::vector<int> rep)
{
    bool descending = rep[0] > rep[1];
    for (int i = 1; i < rep.size() - 1; i++)
    {
        if (abs(rep[i-1] - rep[i]) > 3 || abs(rep[i-1] - rep[i]) == 0) return i;
        if (abs(rep[i+1] - rep[i]) > 3 || abs(rep[i+1] - rep[i]) == 0) return i;
        if (descending)
        {
            if(rep[i-1] < rep[i] || rep[i] < rep[i+1]) return i;
        }
        else
        {
            if(rep[i-1] > rep[i] || rep[i] > rep[i+1]) return i;
        }
    }
    return -1;
}

int main()
{
    std::ifstream inputFile("input.txt");
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

    int safe = 0;
    for (std::vector<int> _report : reports)
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

    printf("%d \n", safe);


    return 0;
}