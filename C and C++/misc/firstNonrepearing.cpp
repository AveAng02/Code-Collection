/*
 * Print the first non repeating Integer.
 */

#include <iostream>
#include <string>

int main()
{
    int flag = 0, arr[256] = {0};
    std::string st;
    
    std::cout << "Enter a String to check for the first non-repeating term:\n";
    std::cin >> st;
    
    for (int i = 0; i < st.length(); i++)
    {
        arr[(int)st[i]]++;
    }
    
    for (int i = 0; i < st.length(); i++)
    {
        if (arr[(int)st[i]] == 1)
        {
            std::cout << "First non-repeating integer is = " << st[i] << std::endl;
            flag = 1;
            break;
        }
    }
    
    if (flag == 0)
    {
        std::cout << "All characters are repeating\n";
    }
    
    return 0;
}
