
#include <iostream>
#include <vector>
#include <climits>



std::vector<std::vector<int>> fwShortestPathLength(std::vector<std::vector<int>> arr)
{
	int len = arr.size();	
	
	for(int j = 0, i = 0, k = 0; k < len; k++)
	{
		for(i = 0; i < len; i++)
		{
			for(j = 0; j < len; j++)
			{
				if(arr[i][j] > arr[i][k] + arr[k][j] && arr[i][k] != INT_MAX && arr[k][j] != INT_MAX)
				{
					arr[i][j] = arr[i][k] + arr[k][j];
				}
			}
		}
	}
	
	return arr;
}




int main()
{
	std::vector<std::vector<int>> graph {{      0,       3,       8, INT_MAX,      -4},
										 {INT_MAX,       0, INT_MAX,       1,       7},
										 {INT_MAX,       4,       0,      -5, INT_MAX},
										 {      2, INT_MAX, INT_MAX,       0, INT_MAX},
										 {INT_MAX, INT_MAX, INT_MAX,       6,       0}};
	
	std::vector<std::vector<int>> path = fwShortestPathLength(graph);
	
	int len = path.size();
	
	for(int j = 0, i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			std::cout << path[i][j] << " ";
		}
		
		std::cout << "\n";
	}
	
	return 0;	
}



