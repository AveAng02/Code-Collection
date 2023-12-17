#pragma once

#ifndef VECTOR_CLASS
#define VECTOR_CLASS

#include <cstddef>
#include <cstring>
#include <iostream>
#include <new>


namespace mystl
{
    template <class T>
    class Vector
    {
    public:

        // Member Functions
        Vector() 
        :   len(10),
            maxSz(10)
        {
			try
            {
                buffer = new T[maxSz];
            }
            catch(const std::bad_alloc& e)
            {
                std::cerr << "Error : Failed to allocate memory " << e.what() << std::endl;
                return;   
            }
			
            buffer = new T[maxSz];
        }

        // copy constructor 
        Vector(const Vector& vector) 
        :   len(vector.len),
            maxSz(vector.maxSz) 
        {			
			try
            {
                buffer = new T[maxSz];
            }
            catch(const std::bad_alloc& e)
            {
                std::cerr << "Error : Failed to allocate memory " << e.what() << std::endl;
                return;   
            }
			
            memcpy(buffer, vector.buffer, vector.maxSz * sizeof(T));
        }

        // copy assignment 
        Vector& operator=(const Vector& vector)
        {
            len = vector.len;
            maxSz = vector.maxSz;
						
			try
            {
                buffer = new T[vector.maxSz];
				memcpy(buffer, vector.buffer, vector.maxSz * sizeof(T));
            }
            catch(const std::bad_alloc& e)
            {
                throw std::bad_alloc ("Assignment operator");
            }
        }

        // destructor
        ~Vector()
        {
            delete[] buffer;
        }

        
        // Capacity
        std::size_t size() const;
        std::size_t capacity() const;
        void resize(const std::size_t newSz);
        void resize(const std::size_t newSz, const T value);
        bool empty();
        // max_size
        // reserve
        // shrink to fit


        // Element Access
        T &operator[](const std::size_t i)
        {
			try
            {
				return buffer[i];
            }
            catch(const std::out_of_range& e)
            {
                throw std::out_of_range ("Assignment operator");
            }
        }

        T* data() const;

        // Modifiers
        void push_back(T value);
        void pop_back();


    private:
        std::size_t len;
        std::size_t maxSz;
        T* buffer;
    };
}

#endif // VECTOR CLASS
