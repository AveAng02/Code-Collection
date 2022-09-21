

// references
// heap
// stack 
// raii
// rule of 3
// rule of 5
// ownership semantics
// const correctness
// mutable keyword

// write a string class

class Buffer
{
	
public:
	
	Buffer(size_t len_) : buffSize(len_) 
	{
		// initializer list initialization
		storage = new uint8_t[buffSize];
	}
	
	~Buffer()
	{
		delete [] storage;
	}
	
private:

	uint8_t* storage;

	size_t buffSize;

};



int main()
{
	float x;
	
	int* y = new int;
	
	Buffer buffer1;
	
	Buffer* buffer2 = new Buffer;
	
	std::shared_ptr<Buffer> buffer3 = std::make_shared<Buffer>(512);
}



