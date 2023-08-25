
#include "MyVector.hpp"

template <class T>
void Vector<T>::push_back(T value)
{
    if(buffer == nullptr)
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
void Vector<T>::resize(const int newSz)
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
void Vector<T>::resize(const int newSz, const int value)
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
int Vector<T>::size()
{
    return len;
}

template <class T>
int Vector<T>::max_size()
{
    return maxSz;
}

template <class T>
bool Vector<T>::empty()
{
    return (buffer == nullptr);
}



