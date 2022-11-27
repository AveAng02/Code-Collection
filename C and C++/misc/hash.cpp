

#include <iostream>
#include <list>
#include <algorithm>


template<class T>

class hashTable 
{
public :

	hashTable()
	{
		buffer = new std::list<T>[10];
		
		bufferLen_ = 10;
	}
	
	hashTable(int bufferLen_)
	{
		this->bufferLen_ = bufferLen_;
		
		buffer = new std::list<T>[bufferLen_];
	}
	
	
	
	
	void pushVal(const T &newVal)
	{
		int hashkey = 0;
		
		if(searchVal(newVal)) // checks if the hashTable index is already full or not
		{
			while(searchVal(newVal)) 
			
			hashkey = hashfunc1(newVal);
		}		
		
		buffer[hashfunc1(newVal)].push_back(newVal);
	}
	
	bool searchVal(const T &newVal)
	{
		return false;
	}
	
	void delVal(const T &newVal)
	{
		
	}
	
	void printTable()
	{
		for(int i = 0; i < bufferLen_; i++)
		{
			std::cout << "[ ";
			
			for(T n : buffer[i])
			{
				std::cout << n << ", ";
			}
			
			std::cout << "] " << std::endl;
		}
	}
	
	
	
private :

	std::list<T> *buffer;
	
	int bufferLen_;
	
	
	
protected :
	
	int hashfunc1(int key)
	{
		return key % bufferLen_;
	}
	
	int hashfunc2()
	{
		return 0;
	}
	
	bool collisionDetection(int key)
	{
		
	}
};





int main()
{
	hashTable<int> table1;
	
	table1.pushVal( 30 );
	table1.pushVal( 15 );
	table1.pushVal( 47 );
	table1.pushVal( 86 );
	table1.pushVal( 12 );
	table1.pushVal( 71 );
	table1.pushVal( 89 );
	table1.pushVal( 70 );
	
	table1.printTable();
	
	return 0;
}









