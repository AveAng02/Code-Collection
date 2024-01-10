
#include <iostream>

std::string encription(std::string word, int shift)
{
    shift = (shift < 0)? shift + 26 : shift;

    std::string str = "";

    for(uint32_t newChar = 0, i = 0; i < word.length(); i++)
    {
        newChar = ((((int)word[i] - 64) + shift) % 26) + 64;
        str += (char)newChar;
    }

    return str;
}

std::string decription(std::string word, int shift)
{
    shift = (shift < 0)? shift + 26 : shift;

    std::string str = "";

    for(uint32_t newChar = 0, i = 0; i < word.length(); i++)
    {
        newChar = ((((int)word[i] - 64) - shift) % 26) + 64;
        str += (char)newChar;
    }

    return str;
}

int main()
{
    std::string str = "";
    int shift = 0;

    std::cout << "Enter String : ";
    std::cin >> str;
    std::cout << "Enter Shift : ";
    std::cin >> shift;

    std::string newWord = encription(str, shift);
    std::cout << "Encripted Word : " << newWord << std::endl;

    std::string oldWord = decription(newWord, shift);
    std::cout << "Decripting the Word : " << oldWord << std::endl;

    return 0;
}
