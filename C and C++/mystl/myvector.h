#pragma once
#ifndef MYSTL_VECTOR
#define MYSTL_VECTOR

#include <cstddef>


namespace mystl
{
    template<typename T>
    class myvector
    {
    public:

        myvector()
        {
            buffer = new T[10];
            bufferSize = 10;
            vecSize = 0;
        }

        myvector(size_t n)
        {
            buffer = new T[n];
            bufferSize = n;
            vecSize = 0;
        }

        myvector(T givenBuffer[])
        {
            buffer = givenBuffer;
            vecSize = bufferSize = sizeof(givenBuffer) / sizeof(givenBuffer[0]);
        }
        

        ~myvector();

        void push_back(const T& value);
        void emplace_back(const T& value);
        void back();

        inline std::size_t size()
        {
            return bufferSize;
        }

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




int main()
{
    mystl::myvector<int> newvec;



    return 0;
}




