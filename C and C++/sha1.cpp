
#include <iostream>
#include <vector>
#include <new>

/*
* References:
* [1] https://en.wikipedia.org/wiki/SHA-1#SHA-1_pseudocode
* [2] http://www.faqs.org/rfcs/rfc3174.html
*/

// defining a unsigned integer of 160 bits
/*
class uint160bit
{
public:
    uint160bit()
    {
        buffer = new (std::nothrow) uint8_t[20];
    }

    ~uint160bit()
    {
        delete[] buffer;
    }

    uint160bit(const uint160bit& optr)
    {
        if(this == &optr)
            return &this;
    }

    uint160bit& operator=(const uint160bit& optr)
    {


        return *this;
    }

private:
    uint8_t* buffer;
};
*/

// Hex digit
/*
* Addition
* toString
* All bitwise operations
*/

// Word
/*
* Addition
* toString
* circular Lift Shift
* All bitwise operations
* Implement functions and constant words 
  as in page (6) point (5) of the paper
*/

// Block
/*
* Initialization with message of length between 0 to 512 bits
*/

uint32_t SHA1(const std::string str)
{
    // Initialize Variables
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    uint64_t ml = sizeof(str[0]) * str.length() * 8;

    std::cout << ml << "  " << sizeof(str[0])  << std::endl;

    // Pre-processing
    // std::vector<bool> 
}


int main()
{
    std::string text = "The quick brown fox jumps over the lazy dog";

    std::cout << SHA1(text) << std::endl;

    return 0;
}

