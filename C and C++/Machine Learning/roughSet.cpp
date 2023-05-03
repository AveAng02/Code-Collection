
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
    }

    std::cout << "\n";
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

// convert the function to a templated function
std::vector<std::string> subset(std::vector<std::vector<std::string>> data, int line)
{
    std::vector<std::string> sub;

    for(int i = 0; i < data.size(); i++)
    {
        sub.push_back(data[i][line]);
    }

    return sub;
}


// convert this to a templated function
bool equal(std::vector<std::string> a, std::vector<std::string> b)
{
    if(a.size() != b.size())
    {
        return false;
    }

    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] != b[i])
        {
            return false;
        }
    }

    return true;
}


std::vector<std::string> cut_vec(std::vector<std::string> data, int begin, int end)
{
    std::vector<std::string> sub_set1;

    for(int i = begin; i < end; i++)
    {
        sub_set1.push_back(data[i]);
    }

    return sub_set1;
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



std::vector<std::vector<std::string>> indiscernibility
(std::vector<std::vector<std::string>> data, int decision_line)
{
    std::vector<std::vector<std::string>> indis;
    
    bool* flag = new bool[data.size()]{false};

    for(int i = 0; i < data.size(); i++)
    {
        if(flag[i] == false)
        {
            std::string decision = data[i][decision_line];

            std::vector<std::string> sub_set;
            
            for(int j = 0; j < data.size(); j++)
            {
                if(data[j][decision_line] == decision && flag[j] == false)
                {
                    sub_set.push_back(data[j][0]);
                    flag[j] = true;
                }
            }
            indis.push_back(sub_set);
            sub_set.resize(0);
        }
    }

    return indis;
}



std::vector<std::vector<std::string>> complete_indiscernibility
(std::vector<std::vector<std::string>> data)
{
    std::vector<std::vector<std::string>> indis;
    
    bool* flag = new bool[data.size()]{false};

    for(int i = 0; i < data.size(); i++)
    {
        std::vector<std::string> sub_set1 = cut_vec(data[i], 1, data[i].size());

        std::vector<std::string> sub_set;

        if(flag[i] == false)
        {
            for(int j = 0; j < data.size(); j++)
            {
                std::vector<std::string> sub_set2 = cut_vec(data[j], 1, data[j].size());

                if(equal(sub_set1, sub_set2))
                {
                    sub_set.push_back(data[j][0]);
                    flag[j] = true;
                }
            }

            indis.push_back(sub_set);
        }
    }

    return indis;
}



// generating equivalance classes
// convert this function to a class
// this function creates a roughset
void create_rough_set(std::vector<std::vector<std::string>> data)
{
    std::vector<std::vector<std::string>> get_set = indiscernibility(data, 1);

    std::cout << "indiscernibility of field 1 : " << std::endl;
    print_2d_string_vec(get_set);

    get_set = indiscernibility(data, 2);

    std::cout << "indiscernibility of field 2 : " << std::endl;
    print_2d_string_vec(get_set);

    get_set = indiscernibility(data, 3);

    std::cout << "indiscernibility of field 3 : " << std::endl;
    print_2d_string_vec(get_set);

    get_set = complete_indiscernibility(data);

    std::cout << "indiscernibility of field : " << std::endl;
    print_2d_string_vec(get_set);
}





int main()
{
    // add argc arg v in main 

    std::string file_name = "data1.csv";

    std::vector<std::vector<std::string>> data = load_csv_data(file_name);

    print_2d_string_vec(data);

    create_rough_set(data);

    // print_2d_string_vec(data);

    // std::cout << data.size() << "   " << data[0].size() << std::endl;
}






