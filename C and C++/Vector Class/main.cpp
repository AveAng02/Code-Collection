
#include <iostream>


template <class T>
class Vector
{
public:

    Vector()
    {
        buffer = nullptr;
        len = 0;
    }

    T &operator[](const int i)
    {
        return buffer[i];
    }

    void push_back(T value)
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

    void pop_back()
    {
        len--;

        if(len == 0)
            delete(buffer);
    }

    void resize(const int newSz)
    {
        T* newBuffer = new T[newSz];

        for(int i = 0; i < len && i < newSz; i++)
        {
            newBuffer[i] = buffer[i];
        }

        delete(buffer);
        buffer = newBuffer;
    }

    void resize(const int newSz, const int value)
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

    int size()
    {
        return len;
    }

    int max_size()
    {
        return maxSz;
    }

    bool empty()
    {
        return (buffer == nullptr);
    }

private:
    int len;
    int maxSz;
    T* buffer;
};



int main()
{
    Vector<int> intVec;

    intVec.push_back(5);
    intVec.push_back(7);
    intVec.push_back(9);
    intVec.push_back(11);

    for(int i = 0; i < intVec.max_size(); i++)
    {
        std::cout << intVec[i] << std::endl;
    }

    return 0;
}


