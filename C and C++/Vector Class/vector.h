
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

    void push_back(T);
    void pop_back();
    int resize(const int);
    int resize(const int, const int);
    int size();
    bool empty();

private:
    int len;
    T* buffer;
};

