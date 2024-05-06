
#include <iostream>
#include <vector>
#include <random>

std::string generateRandomString(int size)
{
    std::string str = "";

    std::random_device dev;
    std::mt19937 random(dev());
    std::uniform_int_distribution<std::mt19937::result_type> engSmall(97, 122);

    for(int i = 0; i < size; i++)
    {
        str += (char)engSmall(random);
    }

    return str;
}

std::string backtract(const std::vector<std::vector<int>>& length,
                    const std::string& a,
                    const std::string& b,
                    int i, int j)
{
    if(i == 0 || j == 0)
    {
        return "";
    }
    else if(a[i - 1] == b[j - 1])
    {
        return backtract(length, a, b, i - 1, j - 1) + a[i];
    }
    else if(length[i - 1][j] < length[i][j - 1])
    {
        return backtract(length, a, b, i, j - 1);
    }
    
    return backtract(length, a, b, i - 1, j);
}

std::string lcsLinear(std::string a, 
                    std::string b)
{
    int sizea = a.size();
    int sizeb = b.size();

    std::string str = "";

    std::vector<std::vector<int>> length 
    (sizea + 1, std::vector<int>(sizeb + 1, 0));

    for(int j, i = 1; i < sizea + 1; i++)
    {
        for(j = 1; j < sizeb + 1; j++)
        {
            if(a[i - 1] == b[j - 1])
            {
                length[i][j] = length[i - 1][j - 1] + 1;
            }
            else
            {
                length[i][j] = std::max(length[i - 1][j], 
                                        length[i][j - 1]);
            }
        }
    }

    return backtract(length, a, b, sizea, sizeb);
}


int main()
{
    std::string a = generateRandomString(10000);
    std::string b = generateRandomString(10000);
    std::cout << a << "\n" << b << "\n" 
    << lcsLinear(a, b) << std::endl;

    return 0;
}
