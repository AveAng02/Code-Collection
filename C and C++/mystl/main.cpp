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
*/


#ifndef MYSTL_VECTOR
#define MYSTL_VECTOR

#include <cstddef>
#include <iostream>
#include <cstring>



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
        
        ~myvector()
        {
            delete buffer;
        }
        
        class iterator : public std::iterator<
            std::input_iterator_tag,
            int,
            int,
            const int*,
            int>
        {
        public:
            iterator() {}
        
        private:
            
        };

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
                // throw error
            }

            return buffer[pos];
        }

        void push_back(const T& value);
        void emplace_back(const T& value);
        void back();
        T at(const size_t pos);

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
            T* newBuffer = new T[bufferSize * 2];
            memcpy(newBuffer, buffer, bufferSize * 8);
            bufferSize *= 2;
            T* tempBuffer = buffer;
            buffer = newBuffer;
            delete tempBuffer;
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


void print(const mystl::myvector<int>& vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        std::cout << vec.at(i) << ", ";
    }

    std::cout << "\n";
}





int main()
{
    mystl::myvector<int> newvec;

    for(int i = 0; i < 20; i++)
    {
        newvec.push_back(i);
        print(newvec);
    }



    return 0;
}






