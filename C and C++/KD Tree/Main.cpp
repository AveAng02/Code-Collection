
#include <iostream>


#include "KDTree.cpp"



int main()
{
	std::vector<std::vector<int>> space_points { { 7, 2}, { 5, 4}, { 9, 6}, { 4, 7}, { 8, 1}, { 2, 3}};
	
	KDTree* picture = new KDTree(space_points);
	
	picture->build();
	
	return 0;
}






