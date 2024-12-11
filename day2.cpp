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

void printVec(std::vector<int> vec , int error_index)
{
    for(int i = 0; i < vec.size(); i++)
    {
        printf("%d ", vec[i]);
        if (i + 1 != vec.size() && (abs(vec[i] - vec[i+1]) > 3 || abs(vec[i] - vec[i+1]) == 0))
        {
            printf("- |%d| - ", abs(vec[i] - vec[i+1]));
        }
    }
    printf(" <- error_index: %d\n", error_index);
}

// One bad "level" in report allowed
// After hours of debugging brute forcing the check on elements around the error seems like the only decent solution
int solvePart2(std::vector<std::vector<int>> _reports)
{
    int safe = 0;
    for (std::vector<int> _report : _reports)
    {
        int error_index = FindReportError(_report);
        std::vector<int> temp;
        if (error_index == -1) 
        {
            safe++;
        }
        else
        {
            for (int i = 0; i < _report.size(); i++)
            {
                if (i != error_index + 1)
                    temp.push_back(_report[i]);
            }

            if(FindReportError(temp) == -1)
            {
                safe++;
                continue;
            }
            else
            {
                temp.clear();
                for (int i = 0; i < _report.size(); i++)
                {
                    if (i != error_index)
                        temp.push_back(_report[i]);
                }
                
                if(FindReportError(temp) == -1)
                {
                    safe++;
                    continue;
                }
                else
                {
                    temp.clear();
                    for (int i = 0; i < _report.size(); i++)
                    {
                        if (i != error_index - 1)
                            temp.push_back(_report[i]);
                    }
                    
                    if(FindReportError(temp) == -1)
                    {
                        safe++;
                        continue;
                    }                    
                }
            }
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

    printf("Part 1 output : %d \n", solvePart1(reports));

    printf("Part 2 output : %d \n", solvePart2(reports));


    return 0;
}