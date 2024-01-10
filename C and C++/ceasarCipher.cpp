
#include <iostream>
#include <fstream>
#include <string>

std::string encription(std::string word, int shift)
{
    shift = (shift < 0)? shift + 26 : shift;

    std::string str = "";

    for(uint32_t newChar = 0, i = 0; i < word.length(); i++)
    {
        newChar = ((word[i] - 65 + shift) % 26) + 65;

        if(word[i] == ' ')
            newChar = ' ';
        else if (word[i] == '-')
            newChar = '-';
        else if (word[i] == '\'')
            newChar = '\'';

        str += (char)newChar;
    }

    return str;
}

std::string decription(std::string word, int shift)
{
    shift = (shift < 0)? shift + 26 : shift;

    std::string str = "";
    int temp = 0;

    for(uint32_t newChar = 0, i = 0; i < word.length(); i++)
    {
        temp = ((word[i] - 65 - shift) < 0) ? word[i] - 65 - shift + 26 : word[i] - 65 - shift;
        newChar = (temp % 26) + 65;

        if (word[i] == ' ')
            newChar = ' ';
        else if (word[i] == '-')
            newChar = '-';
        else if (word[i] == '\'')
            newChar = '\'';

        str += (char)newChar;
    }

    return str;
}

int main()
{
    std::string file = "message.txt";
    std::string loadData = "", temp = "";
    int shift = 5;

    std::ifstream myFile(file);

    while (std::getline(myFile, temp))
    {
        loadData += temp;
    }

    std::cout << "Actual sentence : " << loadData << std::endl;

    std::string newWord = encription(loadData, shift);
    std::cout << "\n\nEncripted Word : " << newWord << std::endl;

    std::string oldWord = decription(newWord, shift);
    std::cout << "\n\nDecripting the Word : " << oldWord << std::endl;

    return 0;
}
