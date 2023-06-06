
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
    DEFINING GRAMMER CLASS
*/

class grammer
{
public:
    grammer()
    {
        leftRecursive = false;
        rightRecursive = false;
    }

    grammer operator=(const grammer& obj)
    {
        this->first = obj.first;
        this->follow = obj.follow;
        this->productions = obj.productions;

        return *this;
    }

    bool isLeftRecursive()
    {
        return leftRecursive;
    }

    void genTerminals();
    void genFirst();
    void genFollow();
    void addVariables(const std::string, bool direct);
    bool addProduction(const std::string);
    bool addProduction(const std::vector<std::vector<std::string>>);
    bool doesAcceptStr(const std::string);
    bool generateParseTable();
    bool isVariable(const std::string);
    bool isTerminal(const std::string);
    std::vector<std::vector<std::vector<std::string>>> getProductions();
    std::vector<std::vector<std::string>> getFirst();
    std::vector<std::vector<std::string>> getFollow();
    std::vector<std::string> getVariables();
    std::vector<std::string> getTerminals();
    std::vector<std::string> getDelimiter();
    std::vector<std::string> getOperator();

private:
    std::vector<std::string> recursiveFirst(const std::string);
    std::vector<std::string> recursiveFollow(const std::string);
    std::vector<std::string> equalityResolution(const std::string);

    bool leftRecursive;
    bool rightRecursive;
    std::vector<std::string> delimiterList;
    std::vector<std::string> operatorList;
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

bool grammer::addProduction(const std::vector<std::vector<std::string>> vec)
{
    // function for directly adding a new production to the grammer
    productions.push_back(vec);
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

void grammer::addVariables(const std::string str, bool direct = false)
{
    if(direct)
    {
        // std::cout << "directly adding variable" << std::endl;
        variables.push_back(str);
        return;
    }
    else
    {
        int i = 0;
        std::string var = "";

        // Extracting variable from production
        for(; i < str.length(); i++)
            if(str[i] == '-')
                break;

        var = trimSpace(str.substr(0, i));
        variables.push_back(var);
        ///////////////////////////////////////
    }
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
    std::vector<std::string> var;

    for(int j = 0, i = 0; i < variables.size(); i++)
    {
        var = recursiveFirst(variables[i]);
        var = removeRedundancy(var);
        first.push_back(var);
    }

    std::cout << "FIRST : " << std::endl;
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

std::vector<std::string> grammer::recursiveFirst(const std::string token)
{
    std::vector<std::string> tknList; // list of firsts
    std::vector<std::vector<std::string>> prods;

    // Load productions for the given token
    for(int i = 0; i < variables.size(); i++)
    {
        if(variables[i] == token)
        {
            prods = productions[i];
            // std::cout << "Loading productions for : " << token << std::endl;
            break;
        }
    }
    ///////////////////////////////////////

    for(int i = 0; i < prods.size(); i++)
    {
        if(prods[i][0] == token)
        {
            leftRecursive = true;
            // std::cout << "Skipping Recursive productions" << std::endl;
            continue;
        }

        std::vector<std::string> temp;

        for(int j = 0; j < prods[i].size(); j++)
        {
            if(isVariable(prods[i][j]))
            {
                // TODO : consider for epsilon productions in the variable

                // std::cout << "Variable : " << prods[i][j] << std::endl;

                temp = recursiveFirst(prods[i][j]);

                // print_1d_string_vec(temp);

                tknList = concatVec(tknList, temp);

                break;
            }

            if(is_delimiter(prods[i][j]) || is_operator(prods[i][j]) || isTerminal(prods[i][j]))
            {
                // std::cout << "Other : " << prods[i][j] << std::endl;
                tknList.push_back(prods[i][j]);
                break;
            }
        }
    }

    return tknList;
}

void grammer::genFollow()
{
    // TODO: throw error message if First is empty
    //       and call the first function 

    std::vector<std::string> var;

    for(int j = 0, i = 0; i < variables.size(); i++)
    {
        var = recursiveFollow(variables[i]);
        var = removeRedundancy(var);
        follow.push_back(var);
    }

    // Searching for equality productions
    for(int i = 0; i < follow.size(); i++)
    {
        var = equalityResolution(variables[i]);
        follow[i] = concatVec(follow[i], var);
        follow[i] = removeRedundancy(follow[i]);
    }
    /////////////////////////////////////

    std::cout << "FOLLOW : " << std::endl;
    for(int j = 0, i = 0; i < follow.size(); i++)
    {
        std::cout << variables[i] << " -> ";

        for(j = 0; j < follow[i].size(); j++)
        {
            std::cout << follow[i][j] << " ";
        }
        std::cout << "\n";
    }
}

std::vector<std::string> grammer::recursiveFollow(const std::string token)
{
    // TODO: throw error message if First is empty
    //       and call the first function 
    // std::cout << "Generating for : " << token << std::endl;

    std::vector<std::string> tknList; // list of follows
    std::vector<std::vector<std::string>> prods;


    for(int i = 0; i < productions.size(); i++)
    {
        // load production
        prods = productions[i];
        //////////////////

        // std::cout << "Loaded the productions of : " << variables[i] << std::endl;

        std::vector<std::string> temp;

        for(int k = 0, j = 0; j < prods.size(); j++)
        {
            for(k = 0; k < prods[j].size() - 1; k++)
            {
                // std::cout << "Ran till here :: " << prods[j][k] << std::endl;

                if(prods[j][k] == token)
                {
                    // std::cout << "Encountered token : " << prods[j][k] << std::endl;

                    std::string next = prods[j][k + 1];

                    // std::cout << "Next Encountered token : " << next << std::endl;

                    if(isVariable(next))
                    {
                        // TODO : consider for epsilon productions in the variable

                        std::vector<std::string> postFirst;
                        int pos = 0;
                        // Loading firsts of the next element
                        for(int i = 0; i < variables.size(); i++)
                        {
                            if(variables[i] == next)
                            {
                                postFirst = first[i];
                                pos = i;
                                break;
                            }
                        }
                        /////////////////////////////////////

                        // print_1d_string_vec(postFirst);
                        tknList = concatVec(tknList, postFirst);
                        break;
                    }

                    if(is_delimiter(next) || is_operator(next) || isTerminal(next))
                    {
                        // std::cout << "Other : " << next << std::endl;
                        tknList.push_back(next);
                        break;
                    }
                }
            }
        }

        tknList = concatVec(tknList, temp);
    }

    tknList.push_back("$");

    return tknList;
}

std::vector<std::string> grammer::equalityResolution(const std::string token)
{
    std::vector<std::string> loadFollow;
    std::vector<std::string> tknlist;

    for(int i = 0, j = 0, k = 0; i < productions.size(); i++)
    {
        loadFollow = follow[i];

        for(j = 0; j < productions[i].size(); j++)
        {
            if(productions[i][j].size() == 1 && productions[i][j][k] == token)
            {
                tknlist = concatVec(tknlist, loadFollow);
            }
        }
    }

    return tknlist;
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

std::vector<std::string> grammer::getDelimiter()
{
    return delimiterList;
}

std::vector<std::string> grammer::getOperator()
{
    return operatorList;
}

////////////////////////////////




/*
    LL1 PARSER
*/
bool productionIsRecursive(std::string var, std::vector<std::vector<std::string>> prod)
{
    for(int i = 0; i < prod.size(); i++)
        if(prod[i][0] == var)
            return true;

    return false;
}

grammer removeLeftRecursion(grammer oldGram)
{
    // eliminating the condition where newGram is not left recursive
    if(!oldGram.isLeftRecursive())
        return oldGram;

    grammer newGram;

    std::vector<std::string> oldGramVar = oldGram.getVariables();
    std::vector<std::vector<std::vector<std::string>>> oldProds = oldGram.getProductions();

    for(int i = 0; i < oldProds.size(); i++)
    {
        // std::cout << "Parsing the production for : " << oldGramVar[i] << std::endl;

        if(productionIsRecursive(oldGramVar[i], oldProds[i]))
        {
            // std::cout << "Recursion Detected" << std::endl;

            std::vector<std::vector<std::string>> oldModProds;
            std::vector<std::vector<std::string>> newModProds;

            std::string newVar = oldGramVar[i] + "_";

            // std::cout << newVar << std::endl;

            for(int j = 0; j < oldProds[i].size(); j++)
            {
                if(oldProds[i][j][0] == oldGramVar[i])
                {
                    // std::cout << "This production had recursion" << std::endl;

                    std::vector<std::string> subVec;

                    for(int a = 1; a < oldProds[i][j].size(); a++)
                    {
                        subVec.push_back(oldProds[i][j][a]);
                    }

                    subVec.push_back(newVar);

                    newModProds.push_back(subVec);
                }
                else
                {
                    // std::cout << "This production did not have recursion" << std::endl;
                    oldModProds.push_back(oldProds[i][j]);
                    oldModProds[oldModProds.size() - 1].push_back(newVar);
                }
            }

            // std::cout << "All productions attended" << std::endl;

            newModProds.push_back(std::vector<std::string>{std::string{EPSILON}});

            // old production updated
            newGram.addVariables(oldGramVar[i], true);
            newGram.addProduction(oldModProds);

            // new production added
            newGram.addVariables(newVar, true);
            newGram.addProduction(newModProds);
        }
        else
        {
            // std::cout << "No Recursions Detected" << std::endl;

            newGram.addVariables(oldGramVar[i], true);
            newGram.addProduction(oldProds[i]);
        }

        // std::cout << newGram.getVariables().size() << std::endl;
    }

    newGram.genTerminals();
    newGram.genFirst();
    newGram.genFollow();

    return newGram;
}

/////////////////////////////////





void printProductions(grammer newGram)
{
    std::cout << "LOADED GRAMMER :\n";
    std::vector<std::vector<std::vector<std::string>>> prods = newGram.getProductions();
    std::vector<std::string> var = newGram.getVariables();

    std::cout << "Number of variables : " << var.size() << "\nNumber of Productions : " << prods.size() << std::endl;

    for(int j = 0, k = 0, i = 0; i < prods.size(); i++)
    {
        std::cout << "  " << var[i] << " -> ";

        std::vector<std::vector<std::string>> temp = prods[i];

        for(j = 0; j < temp[0].size(); j++)
        {
            std::cout << " " << temp[0][j] << " ";
        }

        for(k = 1; k < temp.size(); k++)
        {
            std::cout << " | ";

            for(j = 0; j < temp[k].size(); j++)
            {
                std::cout << " " << temp[k][j] << " ";
            }
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
    std::cout << "\n GRAMMER 1\n";

    grammer newGram = fileToGrammer("grammer.txt");

    newGram.generateParseTable();

    printProductions(newGram);

    grammer noRecursive = removeLeftRecursion(newGram);

    std::cout << "\n NEW NON-RECURSIVE GRAMMER\n";

    printProductions(noRecursive);

    std::cout << "\n GRAMMER 2\n";

    grammer newGram2 = fileToGrammer("grammer2.txt");

    newGram2.generateParseTable();

    printProductions(newGram2);

    return 0;
}




