#pragma once

#ifndef VECTOR_CLASS
#define VECTOR_CLASS

template <class T>
class Vector
{
public:

    Vector()
    {
        buffer = nullptr;
        len = 0;
    }

    ~Vector()
    {
        if(buffer != nullptr)
        {
            delete[] buffer;
        }
    }

    T &operator[](const int i)
    {
        return buffer[i];
    }

    void push_back(T value);
    void pop_back();
    void resize(const int newSz);
    void resize(const int newSz, const int value);
    int size();
    int max_size();
    bool empty();

private:
    int len;
    int maxSz;
    T* buffer;
};

#endif // VECTOR CLASS
