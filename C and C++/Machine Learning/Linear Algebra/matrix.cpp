#pragma once

#include <string>
#include <vector>

namespace MathLib
{
	/*
	The matrix is column wise stored in the vector
		
	Ways to create a matrix:
	* identity matrix of arbitrary size created by default (default size is 3X3)
	* from another matrix, i.e. another pointer
	* from a vector
	* from an array
	* another variable of Matrix type
		
	Overloading the following operators(needs further optimizations later):
	+, -, *(multiplication with a matrix), 
	* and /(multiplication and division with a constant),
	<< operator to print, >> operator for iostream input,
	== operator for checking equality, 
	[][] operator for accessing a particular position in the matrix
		
	Prooviding the following functionalities(to be precomputed and stored during construction):
	* compute determinant 
	* compute inverse 
	* Eigen values
	*/
	
	struct Matrix
	{
		std::vector<float> mat;
		
		int rowLength, columnLength;
		
		std::string lable; 
		
		
		
		Matrix(int len = 3, std::string lable_ = "IDENTITY")
		{
			rowLength = columnLength = len;
			
			this->lable = lable_;
			
			for(int j = 0, i = 0, c = 0; c < rowLength * columnLength; c++)
			{
				i = c / columnLength;
				j = c % columnLength;
				
				if (i == j)
				{
					mat.push_back(1);
				}
				else
				{
					mat.push_back(0);
				}
			}
		}
	};
}







