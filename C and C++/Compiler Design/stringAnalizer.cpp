
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <fstream>


bool parser(std::string str, int i, int state_id)
{
    // If block to check if the string can be accepted of not
    if(i == (str.length() - 1))
        if(state_id == 2 || state_id == 3)
            return true;
        else
            return false;
    

    switch(state_id)
    {
        case 1:
            // State 1
            if(str[i] == 'a')
                return parser(str, i+1, 3);
            else if(str[i] == 'b')
                return parser(str, i+1, 2);
            else    
            {
                std::cout << "Invalid Input found" << std::endl;
                return false;
            }
            break;

        case 2:
            // 2nd State
            if(str[i] == 'a')
                return parser(str, i+1, 4);
            else if(str[i] == 'b')
                return parser(str, i+1, 2);
            else
                return false;
            break;

        case 3:
            // 3rd state
            if(str[i] == 'a')
                return parser(str, i+1, 3);
            else if(str[i] == 'b')
                return parser(str, i+1, 2);
            else
                return false;
            break;

        case 4:
            // 4th state
            if(str[i] == 'a')
                return parser(str, i+1, 4);
            else if(str[i] == 'b')
                return parser(str, i+1, 4);
            else
                return false;
            break;

        default:
            std::cout << "Error detected : Trying to access invalid state." << std::endl;
            return false;
    }
}



void loadFile( std::string fileName, std::vector<std::string>& fileCont)
{
    std::ifstream newLoad(fileName);

    std::string temp;

    while(std::getline(newLoad, temp))
        fileCont.push_back(temp);
}



int main()
{
    std::vector<std::string> fileContent;

    loadFile("lines.txt", fileContent);

    for(int i = 0; i < fileContent.size(); i++)
    {
        std::cout << "String : " << fileContent[i] << std::endl; 
        
        if(parser(fileContent[i], 0, 1))
            std::cout << "Accepted";
        else
            std::cout << "Rejected";
        

        std::cout << "\n\n";
    }

    return 0;
}



