
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

void calculateFrequencyPercentages(const std::string& str, 
            std::vector<std::pair<char, double>>& pairList)
{
    std::vector<double> freqList (26, 0.0);
    double sum = 0.0;
    pairList = std::vector<std::pair<char, double>>(26);

    for(uint32_t i = 0; i < str.length(); i++)
    {
        if(str[i] >= 65 && str[i] <= 90)
        {
            freqList[(uint32_t)str[i] - 65]++;
            sum++;
        }
    }

    for(int i = 0; i < pairList.size(); i++)
    {
        pairList[i].first = (char)(i + 65);
        pairList[i].second = (freqList[i] * 100.0 / sum);
    }
    
    std::sort(pairList.begin(), pairList.end(), 
    [](std::pair<char, double> inp1, std::pair<char, double> inp2){
        return inp1.second > inp2.second;
    });
}

void getSet(const std::vector<std::pair<char, double>>& genPairList,
            const std::vector<std::pair<char, double>>& loadedPairList, 
            std::set<int>& diffSet)
{
    std::vector<int> difference;

    for(int i = 0; i < 26; i++)
        difference.push_back(loadedPairList[i].first - genPairList[i].first);

    diffSet = std::set<int>(difference.begin(), difference.end());
}

std::string decriptionPerWord(std::string word, int shift)
{
    shift = (shift < 0)? shift + 26 : shift;

    std::string str = "";
    int temp = 0;

    for(uint32_t newChar = 0, i = 0; i < word.length(); i++)
    {
        temp = ((word[i] - 65 + shift) < 0) ? word[i] - 65 - shift + 26 : word[i] - 65 - shift;
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
    std::string loadData = "", temp = "";
    std::set<int> diffSet;
    std::vector<std::pair<char, double>> genPairList;
    std::vector<std::pair<char, double>> loadedPairList (26);
    std::vector<double> loadedPairListValues = { 8.12, 1.49, 2.71, 4.32, 
    12.02, 2.30, 2.03, 5.92, 7.31, 0.10, 0.69, 3.98, 2.61, 6.95, 7.68, 
    1.82, 0.11, 6.02, 6.28, 9.10, 2.88, 1.11, 2.09, 0.17, 2.11, 0.07 };

    std::ifstream myRead("encripted.txt");

    while (std::getline(myRead, temp))
    {
        loadData += temp;
    }

    myRead.close();

    calculateFrequencyPercentages(loadData, genPairList);
    
    for(int i = 0; i < genPairList.size(); i++)
    {
        loadedPairList[i].first = (char)(i + 65);
        loadedPairList[i].second = loadedPairListValues[i];
    }

    std::sort(loadedPairList.begin(), loadedPairList.end(), 
    [](std::pair<char, double> inp1, std::pair<char, double> inp2){
        return inp1.second > inp2.second;
    });

    getSet(genPairList, loadedPairList, diffSet);

    
    for(std::set<int>::iterator i = diffSet.begin(); i != diffSet.end(); ++i)
        std::cout << *i << ", ";

    std::cout << "\n";
   
    return 0;
}
