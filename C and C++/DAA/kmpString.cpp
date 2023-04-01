
#include <iostream>
#include <vector>







int main()
{
    std::string s = "aaaabbbbcbbbbcaaaababa";

    std::string pat = "bbcaa";

    std::vector<int> pos = KMP(s, pat);

    for(int i = 0; i < pos.size(); i++)
    {
        std::cout << s[i];
    }

    std::cout << "\n";

    for(int i = 0; i < pos.size(); i++)
    {
        std::cout << pos[i];
    }

    std::cout << "\n";

    return 0;
}



