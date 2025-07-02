/*
start with std::vector
 
write a std::vector and manage your own memory 
 
and write these APIs:
 
push_back()
emplace_back()
back()
 
and try these algorithms
 
if_any
accumulate
nth_partition 
 
 
at once
 
write an iterator and try out the parallel execution policy on your vector class
 
see why it fails and try to fix it

implement rule of 3
*/


#ifndef MYSTL_VECTOR
#define MYSTL_VECTOR

#include <cstddef>
#include <iostream>
#include <cstring>
#include <vector>
#include <numeric>
#include <algorithm>



namespace mystl
{
    template<typename T>
    class myvector
    {
    public:

        myvector()
        {
            buffer = new(std::nothrow) T[10];

            if (!buffer)
            {
                throw std::bad_alloc{};
            }

            bufferSize = 10;
            vecSize = 0;
        }

        myvector(size_t n)
        {
            buffer = new(std::nothrow) T[n];

            if (!buffer)
            {
                throw std::bad_alloc{};
            }

            bufferSize = (n > 10)? n : 10;
            vecSize = 0;
        }

        /*
        myvector(const T givenBuffer[])
        {
            vecSize = sizeof(givenBuffer) / sizeof(givenBuffer[0]);
            bufferSize = vecSize * 2;
            buffer = new(std::nothrow) T[bufferSize];

            if(!buffer)
            {
                throw std::bad_alloc{};
            }

            for (std::size_t i = 0; i < vecSize; i++)
            {
                buffer[i] = givenBuffer[i];
            }
        }
        */

        myvector(const myvector& other)
        {
            vecSize = other.vecSize;
            bufferSize = other.bufferSize;

            buffer = new(std::nothrow) T[bufferSize];

            if(!buffer)
            {
                throw std::bad_alloc{};
            }

            for(std::size_t i = 0; i < other.vecSize; i++)
            {
                buffer[i] = other.buffer[i];
            }
        }

        myvector& operator=(const myvector& vec)
        {
            vecSize = vec.vecSize;
            bufferSize = vec.bufferSize;

            buffer = new(std::nothrow) T[bufferSize];

            if(!buffer)
            {
                throw std::bad_alloc{};
            }

            for(std::size_t i = 0; i < vec.vecSize; i++)
            {
                buffer[i] = vec.buffer[i];
            }

            return *this;
        }

        T operator[](std::size_t pos) const
        {
            return buffer[pos];
        }
        
        ~myvector()
        {
            delete[] buffer;
        }
        
        class iterator
        {
        public:
            using reference = T&;
            using pointer = T*;
            using iterator_catagory = std::random_access_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            
            explicit iterator(T* var_) : var(var_) {}

            iterator operator++(int)
            {
                iterator temp = *this;
                (*this) + sizeof(T);
                return temp;
            }

            iterator& operator++()
            {
                var++;
                return *this;
            }

            bool operator!=(iterator& other) const
            {
                return *this->var != *other.var;
            }

            reference operator*() const
            {
                return *var;
            }
            
            T* var;
        };

        iterator begin() const 
        { 
            return iterator(buffer); 
        }

        iterator end() const 
        { 
            return iterator(buffer + vecSize - 1); 
        }

        inline std::size_t size() const
        {
            return vecSize;
        }

        inline std::size_t capacity() const
        {
            return bufferSize;
        }

        inline T at(const size_t& pos) const
        {
            if (pos >= vecSize)
            {
                throw std::out_of_range("Out of Range. Vector not big enough.");
            }

            return buffer[pos];
        }

        void push_back(const T& value);
        void emplace_back(const T& value);
        void back();

    private:
        T* buffer;
        std::size_t bufferSize;
        std::size_t vecSize;
    };
}

#endif // MYSTL_VECTOR


namespace mystl
{
    template<typename T>
    void myvector<T>::push_back(const T& value)
    {
        if (vecSize >= bufferSize)
        {
            T* tempBuffer = new(std::nothrow) T[bufferSize * 2];
            
            if (!tempBuffer)
            {
                throw std::bad_alloc{};
            }

            for (std::size_t i = 0; i < vecSize; i++)
            {
                tempBuffer[i] = buffer[i];
            }

            delete[] buffer;

            buffer = tempBuffer;
            bufferSize *= 2;
        }

        buffer[vecSize] = value;
        vecSize++;
    }

    template<typename T>
    void myvector<T>::emplace_back(const T& value)
    {

    }

    template<typename T>
    void myvector<T>::back()
    {
        
    }
}


template<typename T>
void print(const mystl::myvector<T>& vec)
{
    for(const auto& i : vec)
    {
        std::cout << i << ", ";
    }

    std::cout << "\n";
}

int main()
{
    mystl::myvector<std::string> newvec;

    std::string str = "";

    for(int i = (int)'a'; i <= (int)'z'; i++)
    {
        str += (char)i;
        newvec.push_back(str);
        // print(newvec);
    }

    mystl::myvector<int> tempvec;
    mystl::myvector<int> tempvec1;

    for(int i = 0; i < 15; i++)
    {
        tempvec.push_back(i + 1);
    }

    for(int i = 0; i < 15; i++)
    {
        std::cout << tempvec[i] << ", ";
    }

    std::cout << "\n";

    tempvec1 = tempvec;

    for(int i = 0; i < 15; i++)
    {
        std::cout << tempvec1[i] << ", ";
    }

    std::cout << "\n";

    mystl::myvector<int> tempvec2(tempvec);

    for(const auto& i : tempvec2)
    {
        std::cout << i << ", ";
    }

    std::cout << "\n";

    int sum = std::accumulate(tempvec.begin(), tempvec.end(), 0);

    std::cout << "Sum is = " << sum << std::endl;

    /*
    std::vector<int>* arrofvec = new std::vector<int>[10];

    for (int i = 0; i < 10; i++)
    {
        arrofvec[i] = {i, i*i, i*i*i, i*i*i*i};
    }

    mystl::myvector<std::vector<int>> vecofvec (arrofvec);
    */



    return 0;
}
