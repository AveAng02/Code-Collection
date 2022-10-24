#pragma once

#include <iostream>

namespace ayan
{
	class string_manip
	{
	public:
	
		string_manip() : len(0), buffer(nullptr) { }
		
		string_manip(string_manip& passed_str) 
		{
			this->buffer = new char[passed_str.length() + 1];
			
			int i = 0;
			
			while(i < passed_str.length())
			{
				this->buffer[i] = passed_str.buffer[i];
				i++;
			}
			
			this->buffer[i] = '\0';
			
			this->len = this->length() + 1;
		}
		
		string_manip(const char* passed_str) 
		{
			int len_ = sizeof(passed_str), i = 0;
			
			this->buffer = new char[len_ + 1];
			
			while(i < len_)
			{
				this->buffer[i] = passed_str[i];
				i++;
			}
			
			this->buffer[i] = '\0';
			
			this->len = this->length() + 1;
		}
		
		~string_manip() 
		{
			delete [] buffer;
		}
		
		// Iterators
		// char begin();
		// char end();
		
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
		
		char* buffer;
		
	};
}

