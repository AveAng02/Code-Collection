
// #define DEBUGGING


#include <iostream>

// heapify


// insert node


// delete node


// find peak


// heap sort


class Heap
{

public:

	Heap() {}
	
	~Heap() {}
	
	
	void swap(int &a, int &b)
	{
		int temp = a;
		a = b;
		b = temp;
		
#ifdef DEBUGGING
		std::cout << "Debugging Marker : Swapping" << std::endl;
#endif
	}
	
	
	bool comparator(int a, int b, bool choice)
	{
#ifdef DEBUGGING
		std::cout << "Debugging Marker : Comparator" << std::endl;
#endif
		
		if(choice) // choice == true check for greater than
		{
#ifdef DEBUGGING
			std::cout << "Debugging Marker : Checking for Greater than" << std::endl;
#endif
			if(a > b)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else // choice == false check for less than
		{
#ifdef DEBUGGING
			std::cout << "Debugging Marker : Checking for less than" << std::endl;
#endif
			if(a < b)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	void heapify(int array[], int n, int i, bool choice)
	{
#ifdef DEBUGGING
		std::cout << "\n\nCounter sent : " << i << std::endl;
#endif
		
		int l_pos = (2 * i) + 1;
		int r_pos = (2 * i) + 2;
		int largest = i;
		
		if(l_pos < n &&  comparator(array[l_pos], array[i], choice))
		{
#ifdef DEBUGGING
			std::cout << "Debugging Marker : Comparing with left" << std::endl;
#endif
			
			largest = l_pos;
		}
		
		if(r_pos < n &&  comparator(array[r_pos], array[largest], choice))
		{
#ifdef DEBUGGING
			std::cout << "Debugging Marker : Comparing with right" << std::endl;
#endif
			
			largest = r_pos;
		}
		
		if(largest != i)
		{
			heapify(array, n, largest, choice);
			
			swap(array[i], array[largest]);
		}
		
#ifdef DEBUGGING
		std::cout << "largest : " << largest << "     i : " << i << std::endl;
		
		std::cout << "Step : ";
		for(int i = 0; i < 8; i++)
		{
			std::cout << array[i] << " ";
		}
		std::cout << std::endl;
#endif
	}
	
	
	void buildMaxHeap(int array[], int n)
	{
		for(int i = (n / 2); i >= 0; i--)
		{
			heapify(array, n, i, true);
		}
	}
	
	void buildMinHeap(int array[], int n)
	{
#ifdef DEBUGGING
		std::cout << "Debugging Marker : Building Minimum heap" << std::endl;
#endif
		
		for(int i = (n / 2); i >= 0; i--)
		{
			heapify(array, n, i, false);
		}

	}
	
	void heapSort(int array[], int n)
	{
		for(int i = n - 1; i > 0; i--)
		{
			swap(array[0], array[i]);
			
			n--;
			
			buildMaxHeap(array, n);
		}
	}
	
};




int main()
{
	Heap newheap;

	
	int array[] = {3, 41, 52, 26, 38, 57, 9, 49};
	int array2[] = {3, 41, 52, 26, 38, 57, 9, 49};
	
	std::cout << "Array : ";
	for(int i = 0; i < 8; i++)
	{
		std::cout << array[i] << " ";
	}
	
	newheap.buildMaxHeap(array, 8);
	newheap.buildMinHeap(array2, 8);
	
	
	
	
	
	
	std::cout << "\n Max Heap : ";
	for(int i = 0; i < 8; i++)
	{
		std::cout << array[i] << " ";
	}
	
	std::cout << "\n Min Heap : ";
	for(int i = 0; i < 8; i++)
	{
		std::cout << array2[i] << " ";
	}
	
	newheap.heapSort(array, 8);
	
	std::cout << "\n Heap Sort : ";
	for(int i = 0; i < 8; i++)
	{
		std::cout << array[i] << " ";
	}
	
	std::cout << std::endl;
	
	return 0;
}





