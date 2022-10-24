#include "string_manip.h"


namespace ayan
{
	/*
	char string_manip::begin()
	{
		return str[0];
	}

	char string_manip::end()
	{
		return str[length() - 1];
	}
	*/
	
	unsigned int string_manip::length()
	{
		len = 0;
		
		do
		{
			len++;
		}while(buffer[len] != '\0');
		
		return len;
	}
	
	string_manip& string_manip::operator=(const char* c)
	{
		int i = 0;
		
		while(buffer[i] != '\0')
		{
			buffer[i] = c[i];
			i++;
		}
		
		return *this;
	}
	
	std::ostream& operator<<(std::ostream& os, const string_manip& passed_str)
	{
		int i = 0;
		
		while(passed_str.buffer[i] != '\0')
		{
			os << passed_str.buffer[i];
			i++;
		}
		
		/*
		while(*str != '\0')
		{
			os << str;
			str += 4;
		}
		*/
		
		return os;
	}
}	
	
	