
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <string>
#include <map>

void print_1d_string_vec(std::vector<std::string> data)
{
    std::cout << "  ";

    for(int i = 0; i < data.size() - 1; i++)
    {
        std::cout << data[i] << "\t";
    }

    std::cout << data[data.size() - 1] << "  \n";
}

void print_2d_string_vec(std::vector<std::vector<std::string>> data)
{
    std::cout << "  ";

    for(int i = 0; i < data.size(); i++)
    {
        print_1d_string_vec(data[i]);
    }

    std::cout << "\n";
}

std::string trimSpace(std::string str)
{
    std::string str1 = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] != ' ')
        {
            str1 += str[i];
        }
    }

    return str1;
}

std::vector<char> delimiters = {'(', ')', '{', '}', '[', ']'};

std::vector<char> operators = {'+', '-', '*', '/', '=', '%', '!', '^', '%', '|', ',', ';', '>', '<', '$'};

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

bool is_in_vec(std::vector<std::string> vec, std::string str)
{
    for(int i = 0; i < vec.size(); i++)
    {
        if(vec[i] == str)
            return true;
    }

    return false;
}

std::vector<std::string> reduce_vec(std::vector<std::string> vec)
{
    std::vector<std::string> vec2;

    for(int i = 0; i < vec.size(); i++)
    {
        // std::cout << vec[i] << "\t" << is_in_vec(vec2, vec[i]) << std::endl;

        if(!is_in_vec(vec2, vec[i]))
        {
            vec2.push_back(vec[i]);
        }
    }

    return vec2;
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

    bool addProduction(const std::string);
    bool doesAcceptStr(const std::string);
    void printProductions();
    void printFirst();
    void printLast();

private:
    std::map<std::string, std::vector<std::vector<std::string>>> productions;
    std::map<std::string, std::vector<std::string>> first;
    std::map<std::string, std::vector<std::string>> follow;
};

bool grammer::addProduction(const std::string str)
{
    int i = 0;
    std::string variable = "", var2 = "";
    std::vector<std::string> subVec;
    std::vector<std::vector<std::string>> prods;

    for(i = 0; i < str.length(); i++)
    {
        if(str[i] == '-')
        {
            i += 2;
            break;
        }

        variable += str[i];
    }

    variable = trimSpace(variable);

    if(variable == "")
        return false;

    for(; i < str.length(); i++)
    {
        if(str[i] == '|')
        {
            if(var2 != "" && var2 != " ")
                subVec.push_back(trimSpace(var2));

            var2 = "";

            // print_1d_string_vec(subVec);
            prods.push_back(subVec);
            subVec.clear();
            continue;
        }

        if(is_operator(str[i]) || is_delimiter(str[i]) || str[i] == ' ')
        {
            // if a delimiter or operator is encountered
            // add the word generated so far and the operator 
            // or delimiter encountered to the production list
            if(var2 != "" && var2 != " ")
                subVec.push_back(trimSpace(var2));

            subVec.push_back(std::string{str[i]});
            var2 = "";
            continue;
        }

        var2 += str[i];
    }

    subVec.push_back(trimSpace(var2));
    prods.push_back(subVec);
    subVec.clear();

    productions.insert(std::make_pair(variable, prods));

    return true;
}

void grammer::printProductions()
{
    for(auto i = productions.begin(); i != productions.end(); i++)
    {
        print_2d_string_vec(i->second);
    }
}

/*
bool grammer::doesAcceptStr(const std::string);
void grammer::printProductions();
void grammer::printFirst();
void grammer::printLast();
*/

grammer fileToGrammer(const std::string str)
{
    grammer newGram;
    std::string newLine;

    std::ifstream file(str);

    while(std::getline(file, newLine))
    {
        // std::cout << newLine << "\n" << trimSpace(newLine) << std::endl;

        if(!newGram.addProduction(trimSpace(newLine)))
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
    grammer newGram = fileToGrammer(argv[1]);

    newGram.printProductions();

    return 0;
}




