
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

void print_1d_string_vec(std::vector<std::string> data)
{
    std::cout << "  ";

    for(int i = 0; i < data.size() - 1; i++)
    {
        std::cout << data[i] << "\t";
    }

    std::cout << data[data.size() - 1] << "  \n";
}

std::string trim(std::string str)
{
    std::string str2 = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] != ' ')
            str2 += str[i];
    }

    return str2;
}

std::vector<std::string> concat_1d_vec(std::vector<std::string> token_list1, std::vector<std::string> token_list2)
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

std::vector<std::string> keywords = {"auto", 	"break", 	"case", 	"char", 	"const", 	"continue", 	"default", 	"do",
"double", 	"else", 	"enum", 	"extern", 	"float", 	"for", 	"goto", 	"if", "then", "print",
"int", 	"long", 	"register", 	"return", 	"short", 	"signed", 	"sizeof", 	"static",
"struct", 	"switch", 	"typedef", 	"union", 	"unsigned", 	"void", 	"volatile", 	"while"};

std::vector<char> delimiters = {'(', ')', '{', '}', '[', ']'};

std::vector<char> operators = {'+', '-', '*', '/', '=', '%', '!', '^', '%', '|', ',', ';', '>', '<'};

    bool is_delimiter(char token_)
    {
        for(int i = 0; i < delimiters.size(); i++)
        {
            if(token_ == delimiters[i])
            {
                return true;
            }
        }

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
        {
            if(token_ == operators[i])
            {
                return true;
            }
        }

        return false;
    }

    bool is_operator(std::string token_)
    {
        if(token_.length() > 1)
            return false;
        
        return is_operator(token_[0]);
    }

    bool is_keyword(std::string token_)
    {
        if(token_.length() == 0)
            return false;
        
        for(int i = 0; i < keywords.size(); i++)
        {
            if(token_ == keywords[i])
            {
                return true;
            }
        }

        return false;
    }

    bool is_constant(std::string token_)
    {
        if(token_.length() == 0)
            return false;
        
        for(int i = 0; i < token_.length(); i++)
        {
            if(!(token_[i] >= 48 && token_[i] <= 57))
            // checks if each individual character is a digit or not
            // if it isn't a digit it returns false and terminates 
            // the function
            {
                return false;
            }
        }

        return true;
    }

    bool is_identifier(std::string token_)
    {
        if(token_.length() == 0)
            return false;

        // as the addToken() checks for keywords, delimiters and operators first 
        // thus they are filtered out and doesn't need to be handled here

        if(is_delimiter(token_) || is_operator(token_) 
        || is_constant(token_) || is_keyword(token_))
        // checks for keywords delimiter, operators or constants
        {
            return false;
        }

        if(token_[0] >= 48 && token_[0] <= 57)
        // checks if the first character is a digit or not
        {
            return false;
        }
        
        if(token_.length() > 31)
        // The length of the identifiers should not be 
        // more than 31 characters
        {
            return false;
        }

        for(int i = 0; i < token_.length(); i++)
        {
            if(token_[i] <= 32 || token_[i] == 44)
            // checks to make sure there are no commas or blank spaces
            {
                return false;
            }
        }
        
        return true;
    }

    bool is_token(std::string token_)
    {
        if(token_.length() == 0)
            return false;

        return (is_constant(token_) || is_delimiter(token_)
         || is_identifier(token_) || is_keyword(token_)
         || is_operator(token_));
    }

    std::string remove_comment(std::string str)
    {
        std::string str2 = "";

        bool comment = false;

        for(int i = 0; i < str.length(); i++)
        {
            if(str[i] == '/' && str[i + 1] == '*')
                comment = true;

            if(str[i] == '*' && str[i + 1] == '/')
            {
                comment = false;
                i += 2;
            }

            if(!comment)
            {
                str2 += str[i];
            }
        }

        return str2;
    }


std::vector<std::string> tokenize(std::string str)
{
    std::vector<std::string> list;

    std::string lexem = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(is_delimiter(str[i]) || is_operator(str[i]))
        {
            list.push_back(std::string(1, str[i]));
            
            if(lexem.length() != 0 || lexem != " ")
            {
                list.push_back(trim(lexem));

                // std::cout << lexem << std::endl;

                lexem = "";
            }

            continue;
        }
        
        
        if(is_keyword(trim(lexem)) || is_constant(trim(lexem)))
        {
            list.push_back(trim(lexem));

            lexem = "";
        }

        // std::cout << lexem << "\t" << trim(lexem) << std::endl;

        lexem += str[i];
    }

    return list;
}

std::vector<std::string> load_file(std::string file_name)
{
    std::ifstream file(file_name);
    
    std::vector<std::string> token_list;
	
    std::string line;

    while (std::getline(file, line))
    {
        // std::cout << "\n" << line << std::endl;

        line = remove_comment(line);

        // std::cout << "\n" << line << std::endl;

        token_list = concat_1d_vec(token_list, tokenize(line));

        // print_1d_string_vec(token_list);
    }   

    file.close();

    return token_list;
}


int main()
{
    std::vector<std::string> token_list = load_file("sample.txt");

    std::vector<std::string> validIdentifier;

    std::vector<std::string> validConstant;

    for(int i = 0; i < token_list.size(); i++)
    {
        if(is_identifier(token_list[i]))
            validIdentifier.push_back(token_list[i]);

        if(is_constant(token_list[i]))
            validConstant.push_back(token_list[i]);
    }

    validConstant = reduce_vec(validConstant);
    validIdentifier = reduce_vec(validIdentifier);

    std::cout << "Valid Identifiers :";
    for(int i = 0; i < validIdentifier.size(); i++)
        std::cout << "\t" << validIdentifier[i];

    std::cout << "\nValid Constant :";
    for(int i = 0; i < validConstant.size(); i++)
        std::cout << "\t" << validConstant[i];
    std::cout << "\n";

    return 0;
}


