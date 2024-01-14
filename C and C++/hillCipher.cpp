
#include <iostream>
#include <vector>

std::vector<uint32_t> multiSquareColumn(std::vector<std::vector<uint32_t>> square,
                                        std::vector<uint32_t> column)
{
    std::vector<uint32_t> res (column.size(), 0);

    for(uint32_t j = 0, i = 0; i < column.size(); i++)
    {
        for(j = 0; j < column.size(); j++)
            res[i] += (column[j] * square[i][j]);

        res[i] %= 26;
    }

    return res;
}

void chopText(std::string text, uint32_t size, 
            std::vector<std::vector<uint32_t>>& choppedVec)
{
    uint32_t c = 0;
    std::vector<uint32_t> tempVec;

    while(c + size < text.length())
    {
        tempVec.clear();

        for(uint32_t i = c; i < c + size; i++)
            tempVec.push_back(text[i] - 65);

        choppedVec.push_back(tempVec);
        c += size;
    }

    tempVec.clear();

    for(uint32_t i = c; i < text.length(); i++)
        tempVec.push_back(text[i] - 65);

    for(uint32_t i = text.length(); i < c + size; i++)
        tempVec.push_back(25);

    choppedVec.push_back(tempVec);
}

void kernelMulti(std::vector<std::vector<uint32_t>>& choppedVec,
                const std::vector<std::vector<uint32_t>>& kernel)
{
    for(uint32_t i = 0; i < choppedVec.size(); i++)
        choppedVec[i] = multiSquareColumn(kernel, choppedVec[i]);
}

int main()
{
    uint32_t size = 2;
    std::string text = "";
    std::string encryptedText = "";
    std::vector<std::vector<uint32_t>> choppedVec;
    std::vector<std::vector<uint32_t>> kernel;

    std::cout << "Enter the size of the square matrix : ";
    std::cin >> size;
    std::cout << "Enter the message : ";
    std::cin >> text;

    kernel = std::vector<std::vector<uint32_t>>(size, std::vector<uint32_t>(size));

    for(int32_t i = 0; i < size; i++)
    {
        std::cout << "New Row" << std::endl;
        for(uint32_t j = 0; j < size; j++)
            std::cin >> kernel[i][j];
    }

    chopText(text, size, choppedVec);

    kernelMulti(choppedVec, kernel);

    for(uint32_t j = 0, i = 0; i < choppedVec.size(); i++)
        for(j = 0; j < choppedVec[i].size(); j++)
            encryptedText += (char)(choppedVec[i][j] + 65);

    std::cout << "Encrypted Text : " << encryptedText << std::endl;

    return 0;
}
