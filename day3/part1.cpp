#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

int main()
{
    std::ifstream input("input.txt");
    std::streambuf* sb = input.rdbuf();

    int output = 0;
    int max = 5;

    while(input.ignore(256, 'm'))
    {
        char c;

        input.get(c);
        if (c != 'u') continue;
        input.get(c);
        if (c != 'l') continue;
        input.get(c);
        if (c != '(') continue;

        bool isBad = false;
        char* left = new char [3];
        int count = 0;
        char* right = new char [3];
        while(input.get(c))
        {
            if(isdigit(c)) { left[count++] = c;}
            else if(c == ',') break;
            else {isBad = true; break;}
        }
        if (isBad) continue;
        else
        {
            isBad = false;
            count = 0;
            while(input.get(c))
            {
                if(isdigit(c)) right[count++] = c;
                else if(c == ')') break;
                else {isBad = true; break;}
            }
            if (isBad) continue;
            else
            {
                printf("%d * %d \n", std::atoi(left), std::atoi(right));
                output += std::atoi(left) * std::atoi(right);
            }
        }
    }
    
    printf("%d", output);

    return 0;
}