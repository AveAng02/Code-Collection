
#include <iostream>
#include <MyVector.cpp>


int main()
{
    mystl::Vector<int> intVec;

    bool escape = false;

    intVec.push_back(5);
    intVec.push_back(7);
    intVec.push_back(9);
    intVec.push_back(11);
    intVec.push_back(13);
    intVec.push_back(15);

    for(int i = 0; i < intVec.size(); i++)
    {
        std::cout << intVec[i] << ", ";
    }
    std::cout << "\n";

    std::cout << "Size : " << intVec.size() << std::endl;
    std::cout << "Max Size : " << intVec.max_size() << std::endl;

    std::cout << intVec.data() << std::endl;

    int* ptr = intVec.data();

    std::cout << *ptr++ << "\n" << *ptr << std::endl;

    intVec.resize(16, 0);

    std::cout << "New Resized Vector : ";
    for(int i = 0; i < intVec.max_size(); i++)
    {
        std::cout << intVec[i] << ", ";
    }
    std::cout << "\n";

    return 0;
}
