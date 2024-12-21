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

    printf("%d \n", safe);


    return 0;
}