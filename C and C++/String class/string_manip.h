#pragma once

#include <iostream>

namespace ayan
{
	class string_manip
	{
	public:
	
		string_manip() : len(0), str(nullptr) { }
		
		string_manip(const char* str) 
		{
			this->str = str;
			this->len = this->length();
		}
		
		~string_manip() 
		{
			delete [] this->str;
		}
		
		// Iterators
		
		char begin();
		char end();
		
		// Capacity
		
		unsigned int length();
		
		// Modifiers
		
		string_manip& operator=(const char* c);
		
		// io stream
		friend std::ostream& operator<<(std::ostream&, const string_manip&);
		
		// operator>>
		// strcpy
			
	private:
		
		unsigned int len;
		
		const char* str;
		
	};
}

