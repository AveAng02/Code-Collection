
#include <iostream>


#include "KDTree.h"



int main()
{
	int X = 0, Y = 0, Z = 0;
	
	char repeat = 'Y';
	
	std::vector<std::vector<int>> space_points { { 7, 2, 0}, { 5, 4, 0}, { 9, 6, 0}, { 4, 7, 0}, { 8, 1, 0}, { 2, 3, 0}};
	
	KDTree* picture = new KDTree(space_points);
	
	picture->DFT();
	
	picture->build();
	
	picture->DFT();
	
	while(repeat == 'Y' || repeat == 'y')
	{
		std::cout << "\nEnter the Coordinates:\nX Y Z" << std::endl;
		std::cin >> X >> Y >> Z;
		
		std::cout << "Searching for : " << X << " " << Y << " " << Z << std::endl;
		
		if(picture->searchCoord( X, Y, Z) == true)
		{
			std::cout << "\nCoordinate Found" << std::endl;
		}
		else
		{
			std::cout << "\nCoordinate Not Found" << std::endl;
		}
		
		std::cout << "\n Do you want to continue (Y/N) : ";
		std::cin >> repeat;
	}

	
	delete picture;
	
	return 0;
}






