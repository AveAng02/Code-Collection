
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>




void print_1d_string_vec(std::vector<std::string> data)
{
    std::cout << " { ";

    for(int i = 0, j = 0; i < data.size() - 1; i++)
    {
        std::cout << data[i] << ", ";
    }

    std::cout << data[data.size() - 1] << " } " << std::endl;
}


void print_2d_string_vec(std::vector<std::vector<std::string>> data)
{
    for(int i = 0, j = 0; i < data.size(); i++)
    {
        print_1d_string_vec(data[i]);

        std::cout << "\n";
    }
}



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
std::vector<std::string> lower_approx
(std::vector<std::vector<std::string>> data, int universe_line,
std::string decision, int decision_line)
{
    std::vector<std::string> lower_set;

    for(int i = 0; i < data.size(); i++)
    {
        if(data[i][decision_line] == decision)
        {
            lower_set.push_back(data[i][universe_line]);
        }
    }

    // std::cout << "Lower Set for " << decision << std::endl;
    // print_1d_string_vec(lower_set);

    return lower_set;
}


std::vector<std::string> upper_approx
(std::vector<std::vector<std::string>> data, 
int universe_line, std::string decision, int decision_line)
{
    std::vector<std::string> upper_set;

    return upper_set;
}


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
// this function creates a roughset
void create_rough_set(std::vector<std::vector<std::string>> data)
{
    int attributes = data[0].size(); // stores the number of attributes

    std::vector<std::string> universe;
    std::vector<std::string> decision;

    for(int i = 1; i < data.size(); i++)
    {
        std::string val;

        // this block defines the decision 
        val = data[i][data[0].size() - 1];
        decision.push_back(val);

        // this block defines the universe
        val = data[i][0];
        universe.push_back(val);
    }

    universe = unique(universe); // vector only retains the unique elements
    decision = unique(decision);

    std::vector<std::vector<std::string>> lower_set;
    std::vector<std::vector<std::string>> upper_set;

    for(int i = 0; i < decision.size(); i++)
    {
        lower_set.push_back(lower_approx(data, 1, decision[i], data[0].size() - 1));
        upper_set.push_back(lower_approx(data, 1, decision[i], data[0].size() - 1));
    }

    /*
    std::cout << "Universe:\n";
    print_1d_string_vec(universe);

    std::cout << "Decision:\n";
    print_1d_string_vec(decision);
    */


}





int main()
{
    // add argc arg v in main 

    std::string file_name = "emp_performance.csv";

    std::vector<std::vector<std::string>> data = load_csv_data(file_name);

    create_rough_set(data);

    // print_2d_string_vec(data);

    // std::cout << data.size() << "   " << data[0].size() << std::endl;
}






