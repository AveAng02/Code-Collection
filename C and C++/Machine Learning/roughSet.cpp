
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>




// Importing required libraries
// Load the dataset
// Convert the dataset to a array
std::vector<std::vector<std::string>> load_csv_data(std::string file_name)
{
    // throw error it it is not csv file
    
    std::ifstream file(file_name);
    std::vector<std::vector<std::string>> data;
    std::string line, cell;
    std::vector<std::string> row;

    while(std::getline(file, line))
    {
        std::stringstream lineStream(line);

        while(std::getline(lineStream, cell, ','))
        {
            row.push_back(cell);
        }

        data.push_back(row);
        row.clear();
    }

    file.close();

    return data;
}


// convert the function to a templated function
std::vector<std::string> unique(std::vector<std::string> field)
{
    std::vector<std::string> unique_elements;
    std::string val;
    std::vector<std::string>::iterator itr;
    
    for(int i = 1; i < field.size(); i++)
    {
        val = field[i];
        itr = std::find(unique_elements.begin(), unique_elements.end(), val);

        if(itr == unique_elements.end())
        {
            // std::cout << *itr << std::endl;
            unique_elements.push_back(val);
        }
        
    }

    return unique_elements;
}


// Define the lower and upper approximation functions


// Define the universe of discourse
// Define the number of attributes
// Define the main function to compute rough sets
// Compute the rough sets for the dataset
// Print the results

class RoughSet
{
public:

private:

};

// convert this function to a class
void create_rough_set(std::vector<std::vector<std::string>> data)
{
    int attributes = data[0].size(); // stores the number of attributes

    std::vector<std::string> universe;

    for(int i = 1; i < data.size(); i++)
    {
        // this loop defines the universe 
        std::string val = data[i][data[0].size() - 1];
        universe.push_back(val);
    }

    universe = unique(universe); // vector only retains the unique elements

    /*
    for(int i = 0; i < universe.size(); i++)
    {
        std::cout << universe[i] << std::endl;
    }
    */


}





int main()
{
    // add argc arg v in main 

    std::string file_name = "emp_performance.csv";

    std::vector<std::vector<std::string>> data = load_csv_data(file_name);

    create_rough_set(data);

    /*
    for(int j = 0, i = 0; i < data.size(); i++)
    {
        for(j = 0; j < data[i].size(); j++)
        {
            std::cout << data[i][j] << "  ";
        }

        std::cout << "\n";
    }
    */

    // std::cout << data.size() << "   " << data[0].size() << std::endl;
}






