
#include <iostream>
#include <vector>

struct matrix
{
	int row;
	int col;
};


void optimise(matrix* mat, int** value, int i, int j)
{
	
}













int main()
{
	int n = 5;
	
	// std::cout << "Enter number of matrices : ";
	// std::cin >> n;
	
	std::vector<matrix> arra = {(4,10)};
	
	matrix arr[5] = {4,10,10,3,3,12,12,20,20,7};
	
	int executions[5][5] = {0};
	
	// matrix* arr = new matrix[n];
	
	// int** executions = new int*[n];
	
	/*
	for(int j = 0, i = 0; i < n; i++)
	{
		std::cout << "Enter row of matrix " << i + 1 << " : ";
		std::cin >> arr[i].row;
		std::cout << "Enter column of matrix " << i + 1 << " : ";
		std::cin >> arr[i].col;
		
		executions[i] = new int[n];
		
		for(j = 0; j < n; j++)
		{
			executions[i][j] = 0;
		}
	}
	*/
	
	for(int i = 0; i < n; i++)
	{
		std::cout << "Matrix " << i + 1 << " Row = " << arr[i].row << " ; Column = " << arr[i].col << std::endl;
	}
	
	for(int i = 0, j = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			std::cout << executions[i][j] << " ";
		}
		std::cout << "\n";
	}
	
	optimise(arr, executions, 5, 5);
	
	for(int i = 0, j = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			std::cout << executions[i][j] << " ";
		}
		std::cout << "\n";
	}
	
	
	return 0;
}











