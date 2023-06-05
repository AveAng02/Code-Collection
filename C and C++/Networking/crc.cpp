
#include <iostream>
#include <cstdlib>
#include <climits>
#include <bitset>

#define DIV_SIZE 5
#define DIVISOR std::bitset<DIV_SIZE>(std::string("11001"))
#define SIZE 64


void crcEncoder(std::bitset<SIZE>& message)
{
    std::bitset<DIV_SIZE> part;
    message<<=(DIV_SIZE-1);
    int pos = SIZE;

    // finding the first bit where 
    // the division begins
    for(; pos >= 0; pos--)
        if(message[pos] == 1)
            break;

    // cutting out the first bits which are '0'
    for(int i = 0; i < DIV_SIZE; i++)
        part[DIV_SIZE - i - 1] = message[pos - i];

    // Division loop
    for(int j = DIV_SIZE - 1, i = pos - DIV_SIZE; i >= 0; i--)
    {
        for(j = DIV_SIZE - 1; j >= 0; j--)
        {
            part[j] = part[j] ^ DIVISOR[j];
        }
        part<<=1;
        part[0] = message[i];
    }

    // calculating the remainder
    // and attaching it at the end of the message
    for(int i = 0; i < DIV_SIZE - 1; i++)
        message[i] = part[i] ^ DIVISOR[i];
}

bool transmitter(std::bitset<SIZE>& message)
{
    crcEncoder(message);
    return true;
}

std::bitset<DIV_SIZE> crcDecoder(std::bitset<SIZE>& message)
{
    std::bitset<DIV_SIZE> remainder;
    std::bitset<DIV_SIZE> part;
    int pos = SIZE - 1;

    // finding the first bit where 
    // the division begins
    for(; pos >= 0; pos--)
        if(message[pos] == 1)
            break;

    // cutting out the first bits which are '0'
    for(int i = 0; i < DIV_SIZE; i++)
        part[DIV_SIZE - i - 1] = message[pos - i];

    // Division loop
    for(int j = DIV_SIZE - 1, i = pos - DIV_SIZE; i >= 0; i--)
    {
        for(j = DIV_SIZE - 1; j >= 0; j--)
        {
            part[j] = part[j] ^ DIVISOR[j];
        }
        part<<=1;
        part[0] = message[i];
    }

    // calculating the remainder
    // and attaching it at the end of the message
    for(int i = 0; i < DIV_SIZE; i++)
        remainder[i] = part[i] ^ DIVISOR[i];

    return remainder;
}

bool receiver(std::bitset<SIZE>& message)
{
    std::bitset<SIZE> copy = message;
    std::bitset<DIV_SIZE> rem = crcDecoder(copy);

    for(int i = 0; i < SIZE; i++)
        if(rem[i] == 1)
            return false;

    return true;
}


void corrupt(std::bitset<SIZE>& message)
{
    int pos = SIZE - 1;
    srand((unsigned) time(nullptr));
    int random = rand();

    // finding the first bit where 
    // the division begins
    for(; pos >= 0; pos--)
        if(message[pos] == 1)
            break;

    pos = (int)(((float)random / INT_MAX) * pos);
    message[pos].flip();
}


int main(int argc, char* argv[])
{
    std::bitset<SIZE> message(argv[1]);
    int doCorrupt = 0;
    
    if(transmitter(message))
        std::cout << "Message transmitted" << std::endl;

    std::cout << "Do you want to test corruption?\n1 for corruption\n0 for no corruption" << std::endl;
    std::cin >> doCorrupt;
    
    if(doCorrupt)
        corrupt(message);

    if(receiver(message))
        std::cout << "Message received" << std::endl;
    else
        std::cout << "Message corrupted" << std::endl;

    std::cout << message << std::endl;

    return 0;
}

