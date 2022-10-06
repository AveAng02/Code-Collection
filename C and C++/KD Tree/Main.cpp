

#define SIZE 100


#include <iostream>
#include <random>
#include <vector>
#include <chrono>


#include "KDTree.h"



int main()
{
	std::chrono::duration<double> avg_kdtree, avg_linear;
	
	bool found = false;
	
	/*
	* convert the vector to row major order
	*/
	
	std::vector<int> space_points;

	int sample_run[10] = {0};
	
	int c = 0;


	//////// Generating random coordinates ///////////////////////////////////

	std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(0, SIZE * 5);


    for(int i = 0; i < SIZE * SIZE * SIZE; i++)
    {
		space_points.push_back(distr(generator));
		space_points.push_back(distr(generator));
		space_points.push_back(distr(generator));
		
		c++;
	}
	/////////////////////////////////////////////////////////////////////////
	
	std::cout << "Number of random numbers : " << space_points.size() << std::endl;
	
	std::cout << "Number of nodes defined : " << c << std::endl;
	
	
	/*
	for(const auto &v : space_points)
	{
		std::cout << "{ " << v[0] << ", " << v[1] << ", " << v[2] << "} " << std::endl;
	}
	
	std::exit(1);
	*/
	
	
	
	std::uniform_int_distribution<int>  samples(0, space_points.size());
	
	for(int i = 0; i < 10; i++)
	{
		sample_run[i] = samples(generator);
	}
	
	
	
	int X = 0, Y = 0, Z = 0;
	
	// char repeat = 'Y';
	
	// std::vector<std::vector<int>> space_points;  { { 7, 2, 0}, { 5, 4, 0}, { 9, 6, 0}, { 4, 7, 0}, { 8, 1, 0}, { 2, 3, 0}};
	
	
	KDTree* picture = new KDTree(space_points);
	
	// picture->DFT();
	
	picture->build();
	
	std::cout << "Build Complete........" << std::endl;
	
	c = 0;
	
	// picture->DFT(c);

	std::cout << "Number of Nodes Built : " << c << std::endl;
	
	for(int i = 0; i < 10; i++)
	{
		X = space_points[sample_run[i]];
		Y = space_points[sample_run[i] + 1];
		Z = space_points[sample_run[i] + 2];
		
		std::cout << "\nSearching for : " << X << " " << Y << " " << Z << std::endl;
		
		//////////////////////////////////Searching with KD Tree//////////////////////////////////
		// start timer for KDTree search
		auto start_kdtree = std::chrono::high_resolution_clock::now();
		
		if(picture->searchCoord( X, Y, Z) == true)
		{
			std::cout << "Coordinate Found in KD Tree" << std::endl;
		}
		else
		{
			std::cout << "Coordinate Not Found in KD Tree" << std::endl;
		}
		
		auto end_kdtree = std::chrono::high_resolution_clock::now();
		
		auto diffMSec = std::chrono::duration_cast<std::chrono::nanoseconds>(end_kdtree - start_kdtree);
		// end timer for KDTree search
		
		
		//////////////////////////////////Linear Searching//////////////////////////////////
		// start timen for linear search
		auto start_linear = std::chrono::high_resolution_clock::now();
		
		for(int i = 0; i < SIZE * SIZE * SIZE; i++)
		{
			if(space_points[i] == X && space_points[i + 1] == Y && space_points[i + 2] == Z)
			{
				found = true;
				break;
			}	
		}
		
		if(found == true)
		{
			std::cout << "Coordinate Found" << std::endl;
		}
		else
		{
			std::cout << "Coordinate Not Found" << std::endl;
		}	
		
		auto end_linear = std::chrono::high_resolution_clock::now();
		
		auto diffMSec_linear = std::chrono::duration_cast<std::chrono::nanoseconds>(end_linear - start_linear);
		// end timer for linear search
		
		
		
		std::cout << "KD Tree Search Time : " << diffMSec.count() << "\nLinear Search Time : " << diffMSec_linear.count() << std::endl;

		
		found = false; // resetting
	}
	
	
	/*
	while(repeat == 'Y' || repeat == 'y')
	{
		std::cout << "\nEnter the Coordinates:\nX Y Z" << std::endl;
		std::cin >> X >> Y >> Z;
		
		std::cout << "Searching for : " << X << " " << Y << " " << Z << std::endl;
		
		//////////////////////////////////Searching with KD Tree//////////////////////////////////
		// start timer for KDTree search
		auto start_kdtree = std::chrono::steady_clock::now();
		
		if(picture->searchCoord( X, Y, Z) == true)
		{
			std::cout << "\nCoordinate Found in KD Tree" << std::endl;
		}
		else
		{
			std::cout << "\nCoordinate Not Found in KD Tree" << std::endl;
		}
		
		auto end_kdtree = std::chrono::steady_clock::now();
		
		std::chrono::duration<double> kdtime = end_kdtree - start_kdtree;
		// end timer for KDTree search
		
		
		//////////////////////////////////Linear Searching//////////////////////////////////
		// start timen for linear search
		auto start_linear = std::chrono::steady_clock::now();
		
		for(int i = 0; i < SIZE * SIZE * SIZE; i++)
		{
			if(space_points[i][0] == X && space_points[i][1] == Y && space_points[i][2] == Z)
			{
				found = true;
			}	
		}
		
		if(found == true)
		{
			std::cout << "\nCoordinate Found" << std::endl;
		}
		else
		{
			std::cout << "\nCoordinate Not Found" << std::endl;
		}	
		
		auto end_linear = std::chrono::steady_clock::now();
		
		std::chrono::duration<double> lineartime = end_linear - start_linear;
		// end timer for linear search
		
		
		
		std::cout << "\nKD Tree Search Time : " << kdtime.count() << "\nLinear Search Time : " << lineartime.count() << std::endl;
		
		
		std::cout << "\n Do you want to continue (Y/N) : ";
		std::cin >> repeat;
		
		found = false; // resetting 
	}
*/
	
	
	std::cin.get();
	
	delete picture;
	
	return 0;
}






