
#include "MyVector.hpp"

namespace mystl
{
    template <class T>
    void Vector<T>::push_back(T value)
    {
        if(!buffer)
        {
            buffer = new T[1];
            maxSz = 1;
        }

        if(len == maxSz)
        {
            T* newbuf = new T[maxSz * 2];

            for(int i = 0; i < len; i++)
            {
                newbuf[i] = buffer[i];
            }

            delete(buffer);
            buffer = newbuf;
            maxSz *= 2;
        }

        len++;
        buffer[len - 1] = value;
    }

    template <class T>
    void Vector<T>::pop_back()
    {
        len--;

        if(len == 0)
            delete(buffer);
    }

    template <class T>
    T* Vector<T>::data() const
    {
        return buffer;
    }
    

    template <class T>
    void Vector<T>::resize(const std::size_t newSz)
    {
        T* newBuffer = new T[newSz];

        for(int i = 0; i < len && i < newSz; i++)
        {
            newBuffer[i] = buffer[i];
        }

        delete(buffer);
        buffer = newBuffer;
    }

    template <class T>
    void Vector<T>::resize(const std::size_t newSz, const T value)
    {
        T* newBuffer = new T[newSz];

        for(int i = 0; i < len && i < newSz; i++)
        {
            newBuffer[i] = buffer[i];
        }

        if(newSz > len)
        {
            for(int i = len; i < newSz; i++)
            {
                newBuffer[i] = value;
            }
        }

        delete(buffer);
        buffer = newBuffer;
    }

    template <class T>
    std::size_t Vector<T>::size() const
    {
        return len;
    }

    template <class T>
    std::size_t Vector<T>::max_size() const
    {
        return maxSz;
    }

    template <class T>
    bool Vector<T>::empty()
    {
        return (buffer == nullptr);
    }
}



