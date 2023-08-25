#pragma once

#ifndef VECTOR_CLASS
#define VECTOR_CLASS

#include <cstddef>

namespace mystl
{
    template <class T>
    class Vector
    {
    public:

        // Member Functions
        Vector()
        {
            buffer = nullptr;
            len = 0;
        }

        ~Vector()
        {
            delete[] buffer;
        }

        Vector& operator=(const Vector& vector)
        {
            buffer = vector->data();
            len = vector->size();
            maxSz = vector->max_size();
        }


        // Capacity
        std::size_t size() const;
        std::size_t max_size() const;
        void resize(const std::size_t newSz);
        void resize(const std::size_t newSz, const T value);


        // Element Access
        T &operator[](const std::size_t i)
        {
            return buffer[i];
        }

        T* data() const;

        // Modifiers
        void push_back(T value);
        void pop_back();

        // Iterators
        bool empty();



    private:
        std::size_t len;
        std::size_t maxSz;
        T* buffer;
    };
}

#endif // VECTOR CLASS
