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
    char ch;
    bool enabled = true;

    while(input.get(ch))
    {
        char c;

        if(ch == 'm')
        {
            if (!enabled) continue;
            input.get(c);
            if (c != 'u') continue;
            input.get(c);
            if (c != 'l') continue;
            input.get(c);
            if (c != '(') continue;
        }
        else if (ch == 'd')
        {
            input.get(c);
            if (c != 'o') continue;
            input.get(c);
            if (c == '(')
            {
                input.get(c);
                if (c == ')')
                {
                    enabled = true;
                    continue;
                }
            }
            else if (c == 'n')
            {
                input.get(c);
                if (c != '\'') continue;
                input.get(c);
                if (c != 't') continue;
                input.get(c);
                if (c != '(') continue;
                input.get(c);
                if (c == ')') 
                {
                    enabled = false;
                    continue;
                }
            }
            else continue;
        }
        else continue;

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
                output += std::atoi(left) * std::atoi(right);
            }
        }
    }
    
    printf("%d", output);

    return 0;
}