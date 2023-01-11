#pragma once

#include <iostream> // remove when testing is done
#include <string>
#include <vector>

// macros
#define IDENTITY "IDENTITY MATRIX"

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
		
		
		// Constructors
		Matrix(int len = 3, std::string lable_ = IDENTITY) // default constructor
		{
			this->rowLength = this->columnLength = len;
			
			this->lable = lable_;
			
			for(int j = 0, i = 0, c = 0; c < rowLength * columnLength; c++)
			{
				i = c / columnLength;
				j = c % columnLength;
				
				if (i == j)
				{
					this->mat.push_back(1);
				}
				else
				{
					this->mat.push_back(0);
				}
			}
		}
		
		Matrix(int row, int col, std::string lable_ = "") // default constructor
		{
			this->rowLength = row;
			this->columnLength = col;
			
			this->lable = lable_;
			
			for(int j = 0, i = 0, c = 0; c < rowLength * columnLength; c++)
			{
				this->mat.push_back(0);
			}
		}
		
		Matrix(std::vector<float> mat_, int row, int column, std::string lable_ = "") 
		{
			this->mat = mat_;
			this->rowLength = row;
			this->columnLength = column;
			this->lable = lable_;
		}
		
		Matrix(std::vector<std::vector<float>> mat_, int row, int column, std::string lable_ = "") 
		{
			this->rowLength = row;
			this->columnLength = column;
			this->lable = lable_;
			
			for(int i = 0, j = 0, c = 0; c < row * column; c++)
			{
				i = c / column;
				j = c % column;
				
				this->mat[c] = mat_[i][j];
			}
		}
		
		Matrix(float* mat_[], int row, int column, std::string lable_ = "")
		{
			this->rowLength = row;
			this->columnLength = column;
			this->lable = lable_;
			
			for(int i = 0, j = 0, c = 0; c < row * column; c++)
			{
				i = c / columnLength;
				j = c % columnLength;
				
				this->mat.push_back(mat_[i][j]);
			}
		}
		
		Matrix(float mat_[], int row, int column, std::string lable_ = "")
		{
			this->rowLength = row;
			this->columnLength = column;
			this->lable = lable_;
			
			for(int c = 0; c < row * column; c++)
			{
				this->mat.push_back(mat_[c]);
			}
		}
		
		Matrix(const Matrix& passedMat) // copy constructor
		{
			this->mat = passedMat.mat;
			this->rowLength = passedMat.rowLength;
			this->columnLength = passedMat.columnLength;
			this->lable = passedMat.lable;
		}
		
		
		// Defining Operators
		Matrix& operator=(const Matrix& mat_) // ASSIGNMENT OPERATOR
		{
			this->mat = mat_.mat;
			this->lable = mat_.lable;
			this->rowLength = mat_.rowLength;
			this->columnLength = mat_.columnLength;
			return (*this);
		}
		
		Matrix& operator*(const float val) // MULTIPLICATION BY CONSTANT
		{
			for(int c = 0; c < this->rowLength * this->columnLength; c++)
			{
				this->mat[c] = this->mat[c] * val;
			}
			
			return (*this);
		}
		
		Matrix& operator/(const float val) // DIVISION BY CONSTANT
		{
			for(int c = 0; c < this->rowLength * this->columnLength; c++)
			{
				this->mat[c] = this->mat[c] / val;
			}
			
			return (*this);
		}
		
	};
	
	//Operators Overloading
	Matrix operator+(const Matrix& mat1, const Matrix& mat2) // ADDITION
	{
		Matrix sum(mat1.rowLength, mat1.columnLength);
		
		if(mat1.rowLength != mat2.rowLength || mat1.columnLength != mat2.columnLength)
		{
			// display or return error
			return sum;
		}
			
		for(int c = 0; c < mat1.rowLength * mat1.columnLength; c++)
		{
			sum.mat[c] = mat1.mat[c] + mat2.mat[c];
		}
			
		sum.rowLength = mat1.rowLength;
		sum.columnLength = mat1.columnLength;
			
		return sum;
	}
	
	Matrix operator-(const Matrix& mat1, const Matrix& mat2) // SUBSTRACTION
	{
		Matrix diff(mat1.rowLength, mat1.columnLength);
		
		if(mat1.rowLength != mat2.rowLength || mat1.columnLength != mat2.columnLength)
		{
			// display or return error
			return diff;
		}
			
		for(int c = 0; c < mat1.rowLength * mat1.columnLength; c++)
		{
			diff.mat[c] = mat1.mat[c] - mat2.mat[c];
		}
			
		diff.rowLength = mat1.rowLength;
		diff.columnLength = mat1.columnLength;
			
		return diff;
	}
	
	Matrix operator*(const Matrix& mat1, const Matrix& mat2) // MULTIPLICATION
	{
		Matrix prod(mat1.rowLength, mat2.columnLength);
		
		float sum;
		
		if(mat1.columnLength != mat2.rowLength)
		{
			// display or return error
			return prod;
		}
			
		for(int l = 0, n = 0, i = 0, j = 0, c = 0; c < prod.rowLength * prod.columnLength; c++)
		{
			sum = 0.0;
			
			l = c / mat1.rowLength;
			n = c % mat2.columnLength;
			
			for(i = 0; i < mat1.columnLength; i++)
			{
				// std::cout << " " << (l * mat1.columnLength) + i << " " << (mat2.columnLength * i) + n << " " << std::endl;
				
				sum += (mat1.mat[(l * mat1.columnLength) + i] * mat2.mat[(mat2.columnLength * i) + n]);
			}
			
			// std::cout << sum << std::endl;
			
			prod.mat[c] = sum;
		}
			
		return prod;
	}
}


void print(MathLib::Matrix mat_)
{
	for(int c = 0; c < mat_.rowLength * mat_.columnLength; c++)
	{
		if(c % mat_.columnLength == 0)
		{
			std::cout << "\n";
		}
		
		std::cout << mat_.mat[c] << " ";
	}
	
	std::cout << "\n";
}


int main()
{
	MathLib::Matrix a = MathLib::Matrix(4), b = MathLib::Matrix(4), c, d(std::vector<float>{1, 0, 2, 3, 0, 0, 8, 3, 0, 5, 0, 1, 1, 2, 1, 1}, 4, 4);
	
	print(a);
	print(b);
	print(c);
	print(d);
	
	c = d + a;
	
	print(c);
	
	return 0;
}



