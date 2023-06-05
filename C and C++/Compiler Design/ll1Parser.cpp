
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <map>


std::vector<char> delimiters = {'(', ')', '{', '}', '[', ']'};

std::vector<char> operators = {'+', '-', '*', '/', '=', '%', '!', '^', '%', '|', ',', ';', '>', '<'};

bool is_delimiter(char token_)
{
    for(int i = 0; i < delimiters.size(); i++)
        if(token_ == delimiters[i])
            return true;

    return false;
}

bool is_delimiter(std::string token_)
{
    if(token_.length() > 1)
        return false;

    return is_delimiter(token_[0]);
}

bool is_operator(char token_)
{
    for(int i = 0; i < operators.size(); i++)
        if(token_ == operators[i])
            return true;

    return false;
}

bool is_operator(std::string token_)
{
    if(token_.length() > 1)
        return false;
        
    return is_operator(token_[0]);
}

std::string trimSpace(std::string str)
{
    if(str.length() == 1 && str[0] != ' ')
        return str;

    std::string newStr = "";

    for(int i = 0; i < str.length(); i++)
        if(str[i] != ' ')
            newStr += str[i];

    return newStr;
}


class grammer
{
public:
    grammer() {}

    grammer operator=(const grammer& obj)
    {
        this->first = obj.first;
        this->follow = obj.follow;
        this->productions = obj.productions;

        return *this;
    }

    void addVariables(const std::string);
    bool addProduction(const std::string);
    bool doesAcceptStr(const std::string);
    bool generateParseTable();
    bool isVariable(const std::string);
    std::vector<std::vector<std::vector<std::string>>> getProductions();
    std::vector<std::string> getFirst();
    std::vector<std::string> getFollow();
    std::vector<std::string> getVariables();
    std::vector<std::string> getTerminals();

private:
    void genTerminals();
    void genFirst();
    void genFollow();

    std::vector<std::string> variables;
    std::vector<std::string> terminals;
    std::vector<std::vector<std::vector<std::string>>> productions;
    std::vector<std::string> first;
    std::vector<std::string> follow;
};

bool grammer::addProduction(const std::string str)
{
    std::vector<std::vector<std::string>> newProds;
    std::vector<std::string> prodList, listitr;
    std::string temp = "", itr = "";
    int i = 0;

    // Extracting variable from production
    for(i = 0; i < str.length(); i++)
        if(str[i] == '-')
            break;

    i += 2;
    ///////////////////////////////////////

    // Extracting productions seperated by '|'
    for(; i < str.length(); i++)
    {
        if(str[i] == '|')
        {
            prodList.push_back(itr);
            itr = "";
            continue;
        }
        itr += str[i];
    }
    prodList.push_back(itr);
    //////////////////////////////////////////

    // Extracting tokens from each possible production
    for(int j = 0, i = 0; i < prodList.size(); i++) // loop to iterate through each production
    {
        for(j = 0; j < prodList[i].size(); j++) // loop for the string
        {
            if(is_delimiter(prodList[i][j]) || is_operator(prodList[i][j])
             || isVariable(std::string(1, prodList[i][j])))
            {
                if(temp != "") // check to make sure string is not empty
                    listitr.push_back(temp);

                listitr.push_back(std::string(1, prodList[i][j]));
                temp = "";
                continue;
            }

            temp += prodList[i][j];
        }

        if(temp != "") // check to make sure string is not empty
            listitr.push_back(temp);

        newProds.push_back(listitr);
        listitr.clear();
        temp = "";
    }

    ///////////////////////////////////////////////////

    productions.push_back(newProds);

    return true;
}

bool grammer::isVariable(const std::string str)
{
    for(int i = 0; i < variables.size(); i++)
        if(variables[i] == str)
            return true;

    return false;
}

void grammer::addVariables(const std::string str)
{
    int i = 0;
    std::string var = "";

    // Extracting variable from production
    for(; i < str.length(); i++)
        if(str[i] == '-')
            break;

    var = trimSpace(str.substr(0, i));
    i += 2;
    variables.push_back(var);
    ///////////////////////////////////////
}

void grammer::genTerminals()
{
    for(int i = 0, j = 0, k = 0; k < productions.size(); k++)
    {
        for(j = 0; j < productions[k].size(); j++)
        {
            for(i = 0; i < productions[k][j].size(); i++)
            {
                if(!isVariable(productions[k][j][i]) &&
                 !is_delimiter(productions[k][j][i]) &&
                  !is_operator(productions[k][j][i]))
                {
                    std::cout << productions[k][j][i] << std::endl;
                    terminals.push_back(productions[k][j][i]);
                }
            }
        }
    }
}

bool grammer::generateParseTable()
{
    genTerminals();
    // genFirst();
    // genFollow();
    return true;
}

std::vector<std::vector<std::vector<std::string>>> grammer::getProductions()
{
    return productions;
}

std::vector<std::string> grammer::getVariables()
{
    return variables;
}

std::vector<std::string> grammer::getTerminals()
{
    return terminals;
}


void printProductions(grammer newGram)
{
    std::vector<std::vector<std::vector<std::string>>> prods = newGram.getProductions();
    std::vector<std::string> var = newGram.getVariables();

    for(int i = 0; i < var.size(); i++)
    {
        std::cout << var[i] << std::endl;
    }

    for(int j = 0, k = 0, i = 0; i < prods.size(); i++)
    {
        std::vector<std::vector<std::string>> temp = prods[i];

        for(k = 0; k < temp.size(); k++)
        {
            for(j = 0; j < temp[k].size(); j++)
            {
                std::cout << " " << k << " " << j << "\"" << temp[k][j] << "\"";
            }

            std::cout << " | ";
        }

        std::cout << "\n";
    }
}


grammer fileToGrammer(const std::string str)
{
    grammer newGram;
    std::string newLine;
    std::vector<std::string> list;

    std::ifstream file(str);

    while(std::getline(file, newLine))
    {
        list.push_back(newLine);
    }

    for(int i = 0; i < list.size(); i++)
    {
        newLine = trimSpace(list[i]);

        newGram.addVariables(newLine);
    }

    for(int i = 0; i < list.size(); i++)
    {
        newLine = trimSpace(list[i]);

        if(!newGram.addProduction(newLine))
        {
            // checks if the grammer cannot be parsed
            std::cout << "Error in Grammer." << std::endl;
            exit(0);
        }
    }

    return newGram;
}



/*
bool isAmbiguous(grammer objGram)
{

}

grammer removeLeftRecursion(grammer objGram)
{

}
*/

int main(int argc, char* argv[])
{
    grammer newGram = fileToGrammer("grammer.txt");

    newGram.generateParseTable();

    printProductions(newGram);

    grammer newGram2 = fileToGrammer("grammer2.txt");

    newGram2.generateParseTable();

    printProductions(newGram2);

    return 0;
}




