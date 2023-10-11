
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


std::vector<char> operatorList = {'+', '-', '*', '/', '%', '=',
 '^', '~', '|', '&', '<', '>'};

std::vector<std::string> compoundOperator = {"++", "--", "&&", "||", "<=",
">=", "!=", "==", "+=", "-=", "*=", "/="};

bool isOperator(char opt)
{
    for(int i = 0; i < operatorList.size(); i++)
        if(opt == operatorList[i])
            return true;
    
    return false;
}


bool isOperator(std::string str)
{
    if(str.length() == 1)
        return isOperator(str[0]);

    if(str.length() == 2)
        for(int i = 0; i < compoundOperator.size(); i++)
            if(str == compoundOperator[i])
                return true;

    return false;
}


bool foundInVec(std::vector<std::string>& vec, std::string str)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == str)
        {
            return true;
        }
    }

    return false;
}


std::vector<std::string> reduceVec(std::vector<std::string> vec)
{
    std::vector<std::string> vec2;

    for(int i = 0; i < vec.size(); i++)
    {
        if(!foundInVec(vec2, vec[i]))
        {
            vec2.push_back(vec[i]);
        }
    }

    return vec2;
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

    std::vector<std::string> validOperator;
    std::vector<std::string> invalidOperator;

    loadFile("sample.txt", fileContent);

    for(int j = 0, i = 0; i < fileContent.size(); i++)
    {
        for(j = 0; j < fileContent[i].length() - 1; j++)
        {
            if(isOperator(fileContent[i].substr(j, 1)) &&
            isOperator(fileContent[i].substr(j + 1, 1)))
            {
                if(isOperator(fileContent[i].substr(j, 2)))
                {
                    validOperator.push_back(fileContent[i].substr(j, 2));
                }
                else
                {
                    invalidOperator.push_back(fileContent[i].substr(j, 2));
                }
            }

            if(isOperator(fileContent[i].substr(j, 1)))
            {
                validOperator.push_back(fileContent[i].substr(j, 1));
            }
        }
    }

    validOperator = reduceVec(validOperator);
    invalidOperator = reduceVec(invalidOperator);

    std::cout << "Valid Operators : ";
    for(int i = 0; i < validOperator.size(); i++)
    {
        std::cout << validOperator[i] << "\t";
    }
    std::cout << "\n";

    std::cout << "Invalid Operators : ";
    for(int i = 0; i < invalidOperator.size(); i++)
    {
        std::cout << invalidOperator[i] << "\t";
    }
    std::cout << "\n";

    return 0;
}


