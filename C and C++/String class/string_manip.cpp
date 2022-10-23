
#include "string_manip.h"


namespace ayan
{
	char string_manip::begin()
	{
		return str[0];
	}

	char string_manip::end()
	{
		return str[length() - 1];
	}
	
	unsigned int string_manip::length()
	{
		len = 0;
		
		do
		{
			len++;
		}while(str[len] != '\0');
		
		return len;
	}
	
	string_manip& string_manip::operator=(const char* c)
	{
		this->str = c;
		
		return *this;
	}
	
	string_manip& operator<<(std::ostream&, const string_manip&)
	{
		while(&str != '\0')
		{
			os << &str;
			str += 4;
		}
	}
}	
	
	