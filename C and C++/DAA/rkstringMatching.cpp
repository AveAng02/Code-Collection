
#include <iostream>

/*

Rabin-Karp-Function(Text Given, Pattern to be searched, Hash Function)

*/


int hashFunc(std::string n)
{
	int sum = 0;
	
	for(int i = 0; i < n.length(); i++)
	{
		sum += (int)n[i];
	}
	
	return sum;
}


bool rabinKarp(std::string text, std::string pattern, int func(std::string))
{
	std::string subString; // cutting a substring
	
	int patlen = pattern.length(); // calculating the length of the pattern
	
	int patHash = func(pattern); // calculating the hash of the pattern
	
	for(int i = 0; i < text.length() - patlen; i++)
	{
		subString = text.substr(i, patlen);
		
		if(func(subString) == patHash && subString == pattern)
		{
			return true;
		}
	}
	
	return false;	
}



int main()
{
	std::string text = "sgfhbsdiugfwuefgweufweufbihuFGiywgfwqeubfdd";
	
	std::string pattern = "gweu";
	std::string pattern2 = "gweua";
	
	if(rabinKarp(text, pattern, hashFunc))
	{
		std::cout << "String " << pattern << " Found!!" << std::endl;
	}
	else
	{
		std::cout << "String " << pattern << " not found!!" << std::endl;
	}
	
	if(rabinKarp(text, pattern2, hashFunc))
	{
		std::cout << "String " << pattern2 << " Found!!" << std::endl;
	}
	else
	{
		std::cout << "String " << pattern2 << " not found!!" << std::endl;
	}
	
	return 0;
}



