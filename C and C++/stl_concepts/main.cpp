
#include <iostream>

#include <MyVector.cpp>



int main()
{
    mystl::Vector<int> intVec;
    mystl::Vector<int> otherVec;

    std::cout << "Hello World!!" << std::endl;

    std::cout << "Before Element Generation Other Vector : ";
    for(size_t i = 0; i < otherVec.size(); i++)
    {
        std::cout << otherVec[i] << ",  ";
    }
    std::cout << "\n";

    std::cout << "Before Element Generation Initial Vector : ";
    for(size_t i = 0; i < intVec.size(); i++)
    {
        std::cout << intVec[i] << ",  ";
    }
    std::cout << "\n";

    for(size_t i = 0; i < intVec.size(); i++)
    {
        otherVec[i] = i * 2;
    }

    for(int i = 0; i < intVec.size(); i++)
    {
        intVec[i] = (i * 2) + 5;
    }

    std::cout << "Other Vector : ";
    for(size_t i = 0; i < otherVec.size(); i++)
    {
        std::cout << otherVec[i] << ",  ";
    }
    std::cout << "\n";

    std::cout << "Initial Vector : ";
    for(size_t i = 0; i < intVec.size(); i++)
    {
        std::cout << intVec[i] << ",  ";
    }
    std::cout << "\n";

    std::cout << "Size : " << intVec.size() << std::endl;
    std::cout << "Max Size : " << intVec.capacity() << std::endl;

    std::cout << intVec.data() << std::endl;

    int* ptr = intVec.data();

    std::cout << *ptr++ << "\n" << *ptr << std::endl;

    intVec.resize(16, 0);

    std::cout << "New Resized Vector : ";
    for(int i = 0; i < intVec.capacity(); i++)
    {
        std::cout << intVec[i] << ", ";
    }
    std::cout << "\n";

    // copying one vector onto another
    mystl::Vector<int> copyVec = intVec;
    mystl::Vector<int> copyVec2 (otherVec);

    std::cout << "Copy Vector : ";
    for(size_t i = 0; i < copyVec.size(); i++)
    {
        std::cout << copyVec[i] << ",  ";
    }
    std::cout << "\n";

    std::cout << "Copy Vector 2 : ";
    for(size_t i = 0; i < copyVec2.size(); i++)
    {
        std::cout << copyVec2[i] << ",  ";
    }
    std::cout << "\n";

    return 0;
}
