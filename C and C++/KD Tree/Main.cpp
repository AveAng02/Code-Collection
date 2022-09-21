
#include <iostream>


#include "KDTree.h"



int main()
{
	std::vector<std::vector<int>> space_points { { 7, 2, 0}, { 5, 4, 0}, { 9, 6, 0}, { 4, 7, 0}, { 8, 1, 0}, { 2, 3, 0}};
	
	KDTree* picture = new KDTree(space_points);
	
	picture->build();
	
	delete picture;
	
	return 0;
}






