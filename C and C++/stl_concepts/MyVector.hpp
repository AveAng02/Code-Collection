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
			// remove try catch and 
			// add nothrow and check if its nullptr
			try
            {
                buffer = new T[maxSz];
            }
            catch(const std::bad_alloc& e)
            {
                std::cerr << "Error : Failed to allocate memory " << e.what() << std::endl;   
            }
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
            }
			
			// move memcopy to when the buffer successfully allocates memory
            memcpy(buffer, vector.buffer, vector.maxSz * sizeof(T));
        }

        // copy assignment 
        Vector& operator=(const Vector& vector)
        {
            len = vector.len;
            maxSz = vector.maxSz;
						
			try
            {
				// delete the buffer before allocating new memory
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
			if(i >= len)
            {
                throw std::out_of_range ("Assignment operator");
            }
			else 
			{
				return buffer[i];
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
