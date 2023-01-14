

#include "matrix.h"


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
	
		
		// Constructors
		Matrix::Matrix(int len = 3, std::string lable_ = IDENTITY) // default constructor
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
			
			eigenValues = this->EigenValue();
		}
		
		Matrix::Matrix(int row, int col, std::string lable_ = "") // default constructor
		{
			this->rowLength = row;
			this->columnLength = col;
			
			this->lable = lable_;
			
			for(int j = 0, i = 0, c = 0; c < rowLength * columnLength; c++)
			{
				this->mat.push_back(0);
			}
		}
		
		Matrix::Matrix(std::vector<float> mat_, int row, int column, std::string lable_ = "") 
		{
			this->mat = mat_;
			this->rowLength = row;
			this->columnLength = column;
			this->lable = lable_;
		}
		
		Matrix::Matrix(std::vector<std::vector<float>> mat_, int row, int column, std::string lable_ = "") 
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
		
		Matrix::Matrix(float* mat_[], int row, int column, std::string lable_ = "")
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
		
		Matrix::Matrix(float mat_[], int row, int column, std::string lable_ = "")
		{
			this->rowLength = row;
			this->columnLength = column;
			this->lable = lable_;
			
			for(int c = 0; c < row * column; c++)
			{
				this->mat.push_back(mat_[c]);
			}
		}
		
		// copy constructor
		Matrix::Matrix(const Matrix& passedMat) 
		{
			this->mat = passedMat.mat;
			this->rowLength = passedMat.rowLength;
			this->columnLength = passedMat.columnLength;
			this->lable = passedMat.lable;
		}
		
		
		// Defining Operators
		// ASSIGNMENT OPERATOR
		Matrix::Matrix& operator=(const Matrix& mat_) 
		{
			this->mat = mat_.mat;
			this->lable = mat_.lable;
			this->rowLength = mat_.rowLength;
			this->columnLength = mat_.columnLength;
			return (*this);
		}
		
		// MULTIPLICATION BY CONSTANT
		Matrix::Matrix& operator*(const float val) 
		{
			for(int c = 0; c < this->rowLength * this->columnLength; c++)
			{
				this->mat[c] = this->mat[c] * val;
			}
			
			return (*this);
		}
		
		// DIVISION BY CONSTANT
		Matrix::Matrix& operator/(const float val) 
		{
			for(int c = 0; c < this->rowLength * this->columnLength; c++)
			{
				this->mat[c] = this->mat[c] / val;
			}
			
			return (*this);
		}
		
		
		// CALCULATING EIGEN VALUES
		std::vector<float> Matrix::EigenValue() 
		{
			Matrix newMat = upperTriangularMatrix(mat) ;
			
			std::vector<float> upper ;
			
			for(int i = 0; i < newMat.rowLength; i++)
			{
				upper.push_back( newMat.mat[ i * newMat.rowLength + i ] );
			}
			
			return upper;
		}

	
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
	
	// UPPER TRIANGULAR MATRIX
		Matrix upperTriangularMatrix(Matrix& mat) 
		{
			Matrix upper = mat; // WIP
														   // NEEDS REFACTORING
			double product = 1.0, product2 = 1.0;
			
			for(int i = 0, j = 0, c = 0; c < upper.rowLength - 1; c++)
			{
				for(i = c + 1; i < upper.rowLength; i++)
				{
					for(j = c + 1; j < upper.columnLength; j++)
					{
						upper.mat[ i * upper.rowLength + j ] = ( upper.mat[ c * upper.rowLength + c ] * upper.mat[ i * upper.rowLength + j ] ) - ( upper.mat[ c * upper.rowLength + j ] * upper.mat[ upper.rowLength * i + c ] ) ;
					}
					
					upper.mat[ i * upper.rowLength + c ] = 0;
				}
			}
			
			product = product * upper.mat[ 0 ] ;
			
			for(int i = 0, j = 1; j < upper.rowLength; j++)
			{
				product2 = product * upper.mat[ (j) * upper.rowLength + (j) ] ;
				
				for(i = j; i < upper.columnLength; i++)
				{
					upper.mat[ j * upper.rowLength + i ] = upper.mat[ j * upper.rowLength + i ] / product ;
				}
				
				product = product2;
			}
			
			return upper;
		}
	
	void print(Matrix& mat_)
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
	
	void print(std::vector<float> Vect, int row, int column)
	{
		for(int c = 0; c < row * column; c++)
		{
			if(c % column == 0)
			{
				std::cout << "\n";
			}
			
			std::cout << Vect[c] << " ";
		}
		
		std::cout << "\n";
	}
	
	Matrix calculateInverse(Matrix& Mat)
	{
		Matrix temp(Mat.rowLength, Mat.columnLength);
			
		Matrix Inv(Mat.rowLength, Mat.columnLength);
			
		for(int i = 0, j = Mat.rowLength; j > 0; j--)
		{
			temp = Mat;
			
			for(i = 1; i < Mat.rowLength; i++)
			{
				temp = temp * Mat;
			}
				
			Inv = Inv + temp * Mat.eigenValues[Mat.rowLength - j];
		}
			
		Inv = Inv + Matrix(Mat.rowLength, Mat.columnLength, IDENTITY) * Mat.eigenValues[Mat.rowLength - 1];
			
		return Inv;
	}
	
}


int main()
{
	MathLib::Matrix a = MathLib::Matrix(4), b = MathLib::Matrix(4), c, d(std::vector<float>{1, 0, 2, 3, 0, 0, 8, 3, 0, 5, 0, 1, 1, 2, 1, 1}, 4, 4);
	
	MathLib::print(a);
	MathLib::print(b);
	MathLib::print(c);
	MathLib::print(d);
	
	c = d + a * 4;
	
	MathLib::print(c);
	
	MathLib::print(MathLib::upperTriangularMatrix(c));
	
	MathLib::print(c);
	
	return 0;
}



