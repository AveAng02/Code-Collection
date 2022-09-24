
// basic file operations

// #include <fstream>
#include <iostream>
#include <random>
#include <vector>


#define SIZE 100





int main() 
{
	std::vector<int> row;
	
	std::vector<std::vector<int>> coordinates(SIZE * SIZE * SIZE, row);

    // std::ofstream myfile;
    // myfile.open ("CoordinateInfo.txt");

	std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(0, SIZE * 5);


    for(int i = 0; i < SIZE * SIZE * SIZE; i++)
    {
		// myfile << "{ " << distr(generator) << ", " << distr(generator) << ", " << distr(generator) << " } \n";
		
		coordinates[i].push_back(distr(generator));
		coordinates[i].push_back(distr(generator));
		coordinates[i].push_back(distr(generator));
	}

	for(int i = 0; i < SIZE; i++)
    {
		std::cout << "{" << coordinates[i][0];
		std::cout << ", " << coordinates[i][1];
        std::cout << ", " << coordinates[i][2] << "}" << std::endl;
	}
  
    // myfile.close();
	
    return 0;
}


