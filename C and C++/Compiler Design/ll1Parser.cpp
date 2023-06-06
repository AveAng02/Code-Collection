
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>
#include <map>


/*
    DEFINING LANGUAGE
*/

#define EPSILON (char)949 

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
//////////////////////////////////



/*
    UTILITY FUNCTIONS 
*/
void print_1d_string_vec(std::vector<std::string> data)
{
    if(data.empty())
        return;

    std::cout << "  ";

    for(int i = 0; i < data.size() - 1; i++)
    {
        std::cout << data[i] << "\t";
    }

    std::cout << data[data.size() - 1] << "  \n";
}

std::vector<std::string> concatVec(std::vector<std::string> token_list1, std::vector<std::string> token_list2)
{
    std::vector<std::string> token_list;

    for(int i = 0; i < token_list1.size(); i++)
    {
        token_list.push_back(token_list1[i]);
    }

    for(int i = 0; i < token_list2.size(); i++)
    {
        token_list.push_back(token_list2[i]);
    }

    return token_list;
}

std::string trimSpace(std::string str)
{
    if(str.length() == 1 && str[0] != ' ')
        return str;

    std::string newStr = "";

    for(int i = 0; i < str.length(); i++)
        if(str[i] != ' ' && str[i] != 13)
            newStr += str[i];

    return newStr;
}

std::vector<std::string> removeRedundancy(std::vector<std::string> vec)
{
    // TODO : use algorithms here to reduce redundancy 
    // TODO : use iterators and remove extra vector
    // TODO : convert to templated class and take value by reference
    std::vector<std::string> vec2;
    std::vector<std::string>::iterator itr;

    for(int i = 0; i < vec.size(); i++)
    {
        itr = std::find(vec2.begin(), vec2.end(), vec[i]);

        if(itr == vec2.end())
        {
            vec2.push_back(vec[i]);
        }
    }

    return vec2;
}
////////////////////////////



/*
    DEFINING GRAMMER
*/

class grammer
{
public:
    grammer()
    {
        leftRecursive = false;
    }

    grammer operator=(const grammer& obj)
    {
        this->first = obj.first;
        this->follow = obj.follow;
        this->productions = obj.productions;

        return *this;
    }

    void genTerminals();
    void genFirst();
    void genFollow();
    void addVariables(const std::string);
    bool addProduction(const std::string);
    bool doesAcceptStr(const std::string);
    bool generateParseTable();
    bool isVariable(const std::string);
    bool isTerminal(const std::string);
    std::vector<std::vector<std::vector<std::string>>> getProductions();
    std::vector<std::vector<std::string>> getFirst();
    std::vector<std::vector<std::string>> getFollow();
    std::vector<std::string> getVariables();
    std::vector<std::string> getTerminals();

private:
    std::vector<std::string> recursiveFirst(std::vector<std::string>);

    bool leftRecursive;
    std::vector<std::string> variables;
    std::vector<std::string> terminals;
    std::vector<std::vector<std::vector<std::string>>> productions;
    std::vector<std::vector<std::string>> first;
    std::vector<std::vector<std::string>> follow;
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
             || isVariable(std::string(1, prodList[i][j])) || prodList[i][j] == ' ')
            {
                if(temp != "") // check to make sure string is not empty
                    listitr.push_back(temp);

                if(prodList[i][j] != ' ')
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

bool grammer::isTerminal(const std::string str)
{
    for(int i = 0; i < terminals.size(); i++)
        if(terminals[i] == str)
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
                    if(productions[k][j][i][0] != 13)
                    {
                        terminals.push_back(trimSpace(productions[k][j][i]));
                    }
                }
            }
        }
    }

    terminals = removeRedundancy(terminals);
    terminals.push_back("$");

    /*
    for(int i = 0; i < terminals.size(); i++)
    {
        std::cout << terminals[i] <<  "\t";
    }

    std::cout << "\n";
    */
    
}


void grammer::genFirst()
{
    for(int j = 0, i = 0; i < variables.size(); i++)
    {
        std::cout << variables[i] << std::endl;

        std::vector<std::string> vec, vec2;

        for(j = 0; j < productions[i].size(); j++)
        {
            vec2 = recursiveFirst(productions[i][j]);
            vec = concatVec(vec, vec2);
        }

        first.push_back(removeRedundancy(vec));
        vec.clear();
        vec2.clear();
    }

    for(int j = 0, i = 0; i < first.size(); i++)
    {
        std::cout << variables[i] << " -> ";

        for(j = 0; j < first[i].size(); j++)
        {
            std::cout << first[i][j] << " ";
        }
        std::cout << "\n";
    }
}

/*
if(isVariable(prods[i]))
        {
            // getting the productions for the variable
            std::vector<std::vector<std::string>> varProds;

            for(int i = 0; i < variables.size(); i++)
            {
                if(variables[i] == prods[i])
                {
                    varProds = productions[i];
                    break;
                }
            }
            //////////////////////////////////////////////

            for(int i = 0; i < varProds.size(); i++)
            {
                // iterating through each productions and getting their first
                std::vector<std::string> vec2 = recursiveFirst(varProds[i]);
                vec = concatVec(vec, vec2);
                // std::merge(vec.begin(), vec.end(), vec2.begin(), vec2.end(), std::back_inserter(temp));
            }

            if(std::find(vec.begin(), vec.end(), EPSILON) == vec.end())
            {
                // if the first doesnot have a epsilon production then we break out of the loop
                break;
            }
        }
        */

std::vector<std::string> grammer::recursiveFirst(std::vector<std::string> prods)
{
    std::vector<std::string> temp;

    for(int i = 0; i < prods.size(); i++)
    {
        std::cout << "Debug : " << prods[i] << std::endl;

        if(isVariable(prods[i]))
        {
            bool recursionFlag = false;
            std::cout << "inside variable : " << prods[i] << std::endl;
            // getting the productions for the variable
            std::vector<std::vector<std::string>> varProds;
            std::string vari;

            for(int i = 0; i < variables.size(); i++)
            {
                if(variables[i] == prods[i])
                {
                    varProds = productions[i];
                    vari = variables[i];
                    break;
                }
            }
            //////////////////////////////////////////////

            std::cout << varProds.size() << std::endl;

            for(int i = 0; i < varProds.size(); i++)
            {
                if(vari == varProds[i][0])
                {
                    // preventing recursion
                    leftRecursive = true;
                    recursionFlag = true;
                    continue;
                }

                print_1d_string_vec(varProds[i]);
                temp = concatVec(temp, recursiveFirst(varProds[i]));
            }

            if(recursionFlag)
                continue;
        }

        if(is_delimiter(prods[i]) || is_operator(prods[i]) || isTerminal(prods[i]))
        {
            std::cout << "other one : " << prods[i] << std::endl;
            temp.push_back(prods[i]);
            break;
        }
    }

    std::cout << "\n";

    temp = removeRedundancy(temp);

    return temp;
}


void grammer::genFollow()
{

}

bool grammer::generateParseTable()
{
    if(terminals.empty())
        return false;



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

////////////////////////////////




/*
    LL1 PARSER
*/
void removeLeftRecursion(grammer newGram);

/////////////////////////////////



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

    newGram.genTerminals();
    newGram.genFirst();
    newGram.genFollow();

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

int main()
{
    std::cout << "Epsilon : " << EPSILON << "\n" << std::endl;
    
    if(EPSILON == (char)949)
        std::cout << "matched" << std::endl;

    grammer newGram = fileToGrammer("grammer.txt");

    newGram.generateParseTable();

    printProductions(newGram);

    grammer newGram2 = fileToGrammer("grammer2.txt");

    newGram2.generateParseTable();

    printProductions(newGram2);

    return 0;
}




