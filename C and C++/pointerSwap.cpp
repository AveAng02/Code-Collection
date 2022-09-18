#include <iostream>

void swap(int* xptr, int* yptr) {
	
	int temp = 0;
	
	temp = *xptr;
	*xptr = *yptr;
	*yptr = temp;
	
}

int main() {
	
	int x = 2, y = 5;

	swap( &x, &y);
	
	std::cout << "x = " << x << " y = " << y << std::endl;
	
	int* ptr = 0;
	++ptr;
	
	std::cout << ptr << "\n";
	std::cout << sizeof(void*) << std::endl;
	std::cout << *ptr;
	
	return 0;
	
}



