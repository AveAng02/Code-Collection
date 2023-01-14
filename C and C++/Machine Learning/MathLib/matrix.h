

#pragma once

#include <iostream> // remove when testing is done
#include <string>
#include <vector>

// macros
#define IDENTITY "IDENTITY MATRIX"
#define SQUARE "SQUARE MATRIX"




namespace MathLib
{
	struct Matrix
	{
		std::vector<float> mat;
		
		int rowLength, columnLength;
		
		float determinant;
		
		std::vector<float> eigenValues;
		
		std::string lable; 
		
		
		// Constructors
		Matrix(int len = 3, std::string lable_ = IDENTITY); // default constructor
		
		
		Matrix(int row, int col, std::string lable_ = ""); // default constructor
		
		
		Matrix(std::vector<float> mat_, int row, int column, std::string lable_ = "");
		
		
		Matrix(std::vector<std::vector<float>> mat_, int row, int column, std::string lable_ = "");
		
		
		Matrix(float* mat_[], int row, int column, std::string lable_ = "");
		
		
		Matrix(float mat_[], int row, int column, std::string lable_ = "");
		
		
		// copy constructor
		Matrix(const Matrix& passedMat);
		
		// Defining Operators
		// ASSIGNMENT OPERATOR
		Matrix& operator=(const Matrix& mat_);
		
		// MULTIPLICATION BY CONSTANT
		Matrix& operator*(const float val);
		
		// DIVISION BY CONSTANT
		Matrix& operator/(const float val);
		
		// CALCULATING EIGEN VALUES
		std::vector<float> EigenValue();
		
		
	};
	
	//Operators Overloading
	Matrix operator+(const Matrix& mat1, const Matrix& mat2); // ADDITION
	
	Matrix operator-(const Matrix& mat1, const Matrix& mat2); // SUBSTRACTION
	
	Matrix operator*(const Matrix& mat1, const Matrix& mat2); // MULTIPLICATION
	
	// UPPER TRIANGULAR MATRIX
	Matrix upperTriangularMatrix(Matrix& mat);
	
	void print(Matrix& mat_);
	
	void print(std::vector<float> Vect, int row, int column);
	
	Matrix calculateInverse(Matrix& Mat);
	
}












