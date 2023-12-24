
#include "MyVector.hpp"

namespace mystl
{
    template <class T>
	// convert to bool to check if the operations succeds or fails
    void Vector<T>::push_back(T value)
    {
        if(!buffer)
        {
			// throw an error accordingly
            try
            {
                buffer = new T[10];
            }
            catch(const std::bad_alloc& e)
            {
                std::cerr << "Error : Failed to allocate memory " << e.what() << std::endl;
                return;   
            }
			
            maxSz = 10;
            len = 1;
            buffer[len - 1] = value;
            return;
        }

        if(len == maxSz)
        {
            T* newbuf = nullptr;

            // check if new succeded and 
            // throw an error accordingly
            try
            {
                newbuf = new T[maxSz * 2];
            }
            catch(const std::bad_alloc& e)
            {
                std::cerr << "Error : Failed to allocate memory " << e.what() << std::endl;
                return;   
            }
            
            // here newbuf is the new container
            memcpy(newbuf, buffer, len * sizeof(T));

            delete[] buffer;
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
		
		// when len is less than 0 then it has undefined behaviour

        // remove this part
        if(!len)
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
        T* newBuffer = nullptr;

        // check if new succeded and 
        // throw an error accordingly
        try
        {
            newBuffer = new T[maxSz * 2];
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << "Error : Failed to allocate memory " << e.what() << std::endl;
            return;
        }

        // choose the smaller of the two lengths
        std::size_t resizeLen = (len < newSz) ? len : newSz;
        // copy the smaller buffer to the new buffer
        memcpy(newBuffer, buffer, resizeLen * sizeof(T));

        // delete the old memory
        delete[] buffer;
        // resign new memory 
        buffer = newBuffer;
        len = resizeLen;
        maxSz = newSz;
    }

    template <class T>
    void Vector<T>::resize(const std::size_t newSz, const T value)
    {
        T* newBuffer = nullptr;

        // check if new succeded and 
        // throw an error accordingly
        try
        {
            newBuffer = new T[maxSz * 2];
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << "Error : Failed to allocate memory " << e.what() << std::endl;
            return;
        }

        // choose the smaller of the two lengths
        std::size_t resizeLen = (len < newSz) ? len : newSz;
        // copy the smaller buffer to the new buffer
        memcpy(newBuffer, buffer, resizeLen * sizeof(T));

        // if the resized vector is larger 
        // populate the rest of the spaces with the default value
        if(newSz > len)
        {
			// replace for loop with memset
            for(std::size_t i = len; i < newSz; i++)
            {
                newBuffer[i] = value;
            }
        }
        
        // delete the old memory
        delete[] buffer;
        // resign new memory 
        buffer = newBuffer;
        len = resizeLen;
        maxSz = newSz;
    }

    template <class T>
    std::size_t Vector<T>::size() const
    {
        return len;
    }

    template <class T>
    std::size_t Vector<T>::capacity() const
    {
        return maxSz;
    }

    template <class T>
    bool Vector<T>::empty()
    {
        return !buffer;
    }
}

