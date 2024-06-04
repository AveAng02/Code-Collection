#include <iostream>
#include <vector>
#include <functional>

namespace ayan
{
    template<typename T>
    class set
    {
    public:

        // Capacity
        bool empty();
        uint32_t size();
        uint32_t max_size();

        // Modifiers
        void insert(T val);
        void clear();
        void erase(T val);
        void swap();

        // Lookup
        void count();
        bool find(T val);
        void print();

        std::function<void ()> compare;
        std::vector<T> buffer;

    private:
        void hash();
    };

    // Capacity
    template<typename T>
    bool set<T>::empty()
    {
        return buffer.empty();
    }

    template<typename T>
    uint32_t set<T>::size()
    {
        return buffer.size();
    }

    // Modifiers
    template<typename T>
    void set<T>::insert(T val)
    {
        // TODO: Parse input and throw error accordingly

        if(!find(val))
        {
            buffer.push_back(val);
        }
    }

    template<typename T>
    void set<T>::clear()
    {
        // overwriting present memory
        buffer = std::vector<T>();
    }

    template<typename T>
    void set<T>::erase(T val)
    {
        // TODO: Parse input and throw error accordingly

        if(find(val))
        {
            buffer.erase(val);
        }
    }

    // Lookup
    template<typename T>
    bool set<T>::find(T val)
    {
        for(auto c : buffer)
            if(c == val)
                return true;

        return false;
    }

    template<typename T>
    void set<T>::print()
    {
        std::cout << "Set : ";
        
        for(const auto& c : buffer)
            std::cout << c << ", ";

        std::cout << "\n";
    }
}

struct geometries
{
    float x, y, z;
    std::string name;
};

int main()
{
    ayan::set<int> newSet;

    for(const auto& c : "Say My Name")
    {
        newSet.insert(c);
        newSet.print();
    }

    for(const auto& c : newSet.buffer)
    {
        newSet.erase(c);
        newSet.print();
    }


    ayan::set<geometries> geoSet;

    return 0;
}

