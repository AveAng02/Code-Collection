
#include <iostream>
#include <MyVector.cpp>


int main()
{
    mystl::Vector<int> intVec;

    intVec.push_back(5);
    intVec.push_back(7);
    intVec.push_back(9);
    intVec.push_back(11);

    for(int i = 0; i < intVec.size(); i++)
    {
        std::cout << intVec[i] << std::endl;
    }

    std::cout << intVec.data() << std::endl;

    int* ptr = intVec.data();

    std::cout << *ptr++ << "\n" << *ptr << std::endl;

    return 0;
}
