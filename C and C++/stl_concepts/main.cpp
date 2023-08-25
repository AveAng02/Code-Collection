
#include <iostream>
#include "MyVector.hpp"


int main()
{
    Vector<int> intVec;

    intVec.push_back(5);
    intVec.push_back(7);
    intVec.push_back(9);
    intVec.push_back(11);

    for(int i = 0; i < intVec.size(); i++)
    {
        std::cout << intVec[i] << std::endl;
    }

    return 0;
}


