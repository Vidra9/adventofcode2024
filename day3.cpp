#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>

int main()
{
    std::ifstream input("input3.txt");
    std::streambuf* sb = input.rdbuf();

    int output = 0;
    int max = 5;

    while(input.ignore(256, 'm'))
    {
        // int c = input.peek();
        
        // refactor to maybe get c?

        sb->pubseekoff(-1, input.cur);
        // input.read(str, 11);
        std::streamsize size = sb->pubseekoff(4, input.cur); // ) - breaks if out of file
        sb->pubseekoff(-4, input.cur); // this stream is stupid
        char* str = new char [size];
        sb->sgetn(str, size);
        // input.get(c);
        std::string part(str);
        std::string temp;
        
        std::cout<<"part : "<<part<<std::endl;
        // temp = part.substr(0,4);
        // if (temp != "mul(") continue;
        // int comma = part.find(',');
        // // std::cout<<"comma : "<<comma<<std::endl;
        // temp = part.substr(4, comma - 4);
        // // std::cout<<"temp before left "<<temp<<std::endl;
        // int leftNum = std::stoi(temp);
        // temp = part.substr(comma + 1, part.find(')') - comma - 1);
        // // std::cout<<"temp before right "<<temp<<std::endl;
        // int rightNum = std::stoi(temp);

        // std::cout<<"left: "<<leftNum<<" right: "<<rightNum<<std::endl;
        // output += leftNum * rightNum;
        bool badPattern = false;

        if(part == "mul(")
        {
            std::string left, right;
            char c;
            while(input.get(c))
            {
                std::cout<<"we're fucked \n";
                if (isdigit(c))
                {
                    left.push_back(c);
                }
                else if (c == ',')
                {
                    break;
                }
                else
                {
                    badPattern = true;
                    break;
                }
            }
            if(badPattern) continue;
            while(input.get(c))
            {
                if (isdigit(c))
                {
                    right.push_back(c);
                }
                else if (c == ')')
                {
                    break;
                }
                else
                {
                    badPattern = true;
                    break;
                }
            }
            std::cout<<"left: "<<left<<" | right: "<<right<<std::endl;
        }

        // if (c == EOF) break;

        if(max-- == 0) break;
    }
    
    printf("%d", output);

    return 0;
}