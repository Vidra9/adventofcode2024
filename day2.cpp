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

// One bad "level" in report allowed
// Completely fucked - too many false safes???
int solvePart2(std::vector<std::vector<int>> _reports)
{
    int safe = 0;
    for (std::vector<int> _report : _reports)
    {
        int last_counter = 0;
        int last = _report[last_counter];
        int current_counter = 1;
        int current = _report[current_counter];

        bool is_safe = true;
        bool error_found = false;
        bool descending = false;

        if (abs(last - current) > 3 || abs(last - current) == 0)
        {
            error_found = true;
            last = current;
            last_counter = current_counter;
            current = _report[++current_counter];
        }

        if (last > current) descending = true;
        else if (last == current) // Handle case where first two are equal
        {
            error_found = true;
            last = current;
            last_counter = current_counter;
            current = _report[++current_counter];
            descending = last > current;
        }

        while (current_counter < _report.size())
        {
            if (abs(last - current) == 0)
            {
                if (error_found)
                {
                    is_safe = false;
                    break;
                }
                else 
                {
                    error_found = true;
                    // printf("error found: order: %s | %d[%d] : %d[%d] \n", descending ? "DESC" : "ASC", _report[last_counter], last_counter, _report[current_counter], current_counter);
                    current = _report[++current_counter];
                    continue;
                }
            } else if (abs(last - current) > 3)
            {
                if (error_found)
                {
                    is_safe = false;
                    break;
                }
                else 
                {
                    error_found = true;
                    // printf("error found: order: %s | %d[%d] : %d[%d] \n", descending ? "DESC" : "ASC", _report[last_counter], last_counter, _report[current_counter], current_counter);
                    current = _report[++current_counter];
                    continue;
                }
            }
            else if ((descending && last < current) || (!descending && last > current))
            {
                if (error_found)
                {
                    is_safe = false;
                    break;
                }
                else
                {
                    error_found = true;
                    // printf("error found: order: %s | %d[%d] : %d[%d] \n", descending ? "DESC" : "ASC", _report[last_counter], last_counter, _report[current_counter], current_counter);

                    current = _report[++current_counter];
                    descending = last > current;
                    continue;
                }
            }
            last_counter = current_counter;
            last = current;
            current = _report[++current_counter];
        }
        if (is_safe) safe++;
        if (error_found && false)
        {
            printf("Report: ");
            for (int num : _report)
            {
                printf("%d ", num);
            }
            printf("- %s \n", is_safe ? "SAFE" : "UNSAFE");
        }
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

    printf("Part 2 output :%d \n", solvePart2(reports));


    return 0;
}