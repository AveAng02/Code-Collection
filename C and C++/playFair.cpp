#include <iostream>
#include <vector>

void createPlayfairSquare(std::vector<char>& square,
                          const std::string key)
{
    square = std::vector<char>(25, 63);

    auto isInSquare = [&square](const char letter){
        for(auto i : square)
            if(i == letter)
                return true;
        return false;
    };

    uint32_t c = 0;

    for(auto i : key)
    {
        if(i != ' ' && !isInSquare(i))
        {
            square[c] = i;
            c++;
        }
    }

    for(uint32_t i = 0; i < 26; i++)
    {
        char temp = i + 65;
        if(!isInSquare(temp) && temp != 'J')
        {
            square[c] = temp;
            c++;
        }
    }
}

// Loads the position of the encripted characters in the variables
void getCoordinates(const std::vector<char>& square, 
                    const char letter1, const char letter2,
                    uint32_t& pos1, uint32_t& pos2)
{
    uint32_t x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    auto letterPos = [&square](const char letter){
        for(int i = 0; i < square.size(); i++)
            if(letter == square[i])
                return i;
        return -1;
    };

    x1 = letterPos(letter1) % 5;
    y1 = (uint32_t)(letterPos(letter1) / 5);

    x2 = letterPos(letter2) % 5;
    y2 = (uint32_t)(letterPos(letter2) / 5);

    if(y1 == y2) // Elements in same row
    {
        x1 = (x1 + 1) % 5;
        x2 = (x2 + 1) % 5;
    }
    else if(x1 == x2) // Elements in same column
    {
        y1 = (y1 + 1) % 5;
        y2 = (y2 + 1) % 5;
    }
    else // The Rectangle senario
    {
        uint32_t temp = x1;
        x1 = x2;
        x2 = temp;
    }

    pos1 = y1 * 5 + x1;
    pos2 = y2 * 5 + x2;
}

std::string encrypt(const std::vector<char>& square,
                    std::string message)
{
    std::string str = "", temp = "";
    std::vector<std::string> pairVec;
    uint32_t c = 0;

    while(c < message.length())
    {
        if(message[c] == message[c + 1] || c == (message.length() - 1))
        {
            temp += message[c];
            temp += "X";
            pairVec.push_back(temp);
            c++;
            temp = "";
        }
        else
        {
            temp += message[c]; 
            temp += message[c + 1];
            pairVec.push_back(temp);
            c += 2;
            temp = "";
        }
    }

    uint32_t pos1 = 0, pos2 = 0;

    for(auto i : pairVec)
    {
        getCoordinates(square, i[0], i[1], pos1, pos2);
        str += square[pos1];
        str += square[pos2];
    }

    return str;
}




int main()
{
    std::vector<char> square;
    std::string key = "", text = "";
    uint32_t pos1 = 0, pos2 = 0;

    std::cout << "Enter Key : ";
    std::cin >> key;
    std::cout << "Enter Text : ";
    std::cin >> text;

    // Generating encription square
    createPlayfairSquare(square, key);

    std::string encryptedText = encrypt(square, text);

    std::cout << "Encrypted String : " << encryptedText << std::endl;

    return 0;
}
