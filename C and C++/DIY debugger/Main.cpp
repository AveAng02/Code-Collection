
#include <iostream> 
#include <memory>

void* operator new(size_t size)
{
	void* pos = malloc(size);
	
	std::cout << "Allocating " << size << " bytes at " << pos << "\n";
	
	return pos;
}


struct Object
{
	int x, y, z;
};


int main()
{
	std::string string = "Acharya";
	
	// Object* obj = new Object; // allocating Object on the heap
	
	std::unique_ptr<Object> obj = std::make_unique<Object>();
	
	std::cout << "Address recieved is " << &obj << std::endl;
}








