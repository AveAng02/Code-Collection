
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>


/*
* Reference : https://www.w3schools.com/python/python_ml_decision_tree.asp
*/

// node
struct node
{
    float comparator;
    std::shared_ptr<node> left;
    std::shared_ptr<node> right;
    bool choice;
};


// tree
class decisionTree
{
public:

    decisionTree()
    {
        root = std::make_shared<node>();
    }

    decisionTree(std::vector<std::vector<float>> data, std::vector<bool> goal)
    {
        root = this->fitTree(std::make_shared<node>(), data, goal, 0);
    }

    std::shared_ptr<node> fitTree(std::shared_ptr<node> point, std::vector<std::vector<float>> data, std::vector<bool> goal, int n = 0);
    bool decide(std::vector<float> data);

private:
    std::shared_ptr<node> root;

};



std::shared_ptr<node> decisionTree::fitTree(std::shared_ptr<node> point, std::vector<std::vector<float>> data, std::vector<bool> goal, int n)
{
    /*
    * ALGORITHM:
    * Calculate comparator as the average of the nth field
    * Calculate sample size
    * Calculate value
    * Calculate gini index
    * if gini == 0 then mark as LEAF node and exit
    * Divide data in to parts over comparator
    * Less than comparator goes to left
    * Greater than comparator goes to right
    */


    // if the number of features are exhausted then segrigation is stopped
    if(n >= data.size())
    {
        return nullptr;
    }

    // lambda function to calculate average
    auto average = [](std::vector<float> data) 
    {
        float sum = 0.0;

        for(int i = 0; i < data.size(); i++)
        {
            sum += data[i];
        }

        sum /= data.size();

        return sum;
    };

    // lambda function to calculate the number of tru and false values
    auto value = [](std::vector<bool> goal)
    {
        int true_val = 0;

        for(int i = 0; i < goal.size(); i++)
        {
            if(goal[i] == true)
            {
                true_val++;
            }
        }

        std::vector<int> arr {true_val, (int)(goal.size() - true_val)};

        return arr;
    };

    // calculate gini value
    auto giniCalc = [](float x, float y, float n) 
    {
        return 1 - (x / n)*(x / n) - (y / n)*(y / n);
    };

    int sampleSize = goal.size();
    float compare = average(data[n]);
    std::vector<int> val = value(goal);
    float gini = giniCalc(val[0], val[1], goal.size());

    std::cout << "Data :\narr[0] = " << val[0] << "\narr[1] = " << val[1] << "\n size = " << goal.size() << "\n gini = " << gini << std::endl;

    // if the gini index hits zero then all the goals are same and no more nodes necessary
    if(gini == 0)
    {
        point->choice = goal[0];        
        point->comparator = compare;
        point->left = nullptr;
        point->right = nullptr;

        std::cout << "Data :\nCompare = " << point->comparator << "\nChoice = " << point->choice << std::endl;

        return point;
    }

    /*
    * segregate the data and goal into two parts according to the comparator
    */
    std::vector<float> temp;
    std::vector<std::vector<float>> data_left;
    std::vector<bool> goal_left;
    std::vector<std::vector<float>> data_right;
    std::vector<bool> goal_right;
    
    point->comparator = compare;

    for(int i = 0; i < data.size(); i++)
    {
        data_left.push_back(temp);
        data_right.push_back(temp);
    }

    for(int j = 0, i = 0; i < goal.size(); i++)
    {
        if(compare < data[n][i])
        {
            for(j = 0; j < data.size(); j++)
            {
                data_right[j].push_back(data[n][i]);
            }

            goal_right.push_back(goal[i]);
        }
        else
        {
            for(j = 0; j < data.size(); j++)
            {
                data_left[j].push_back(data[n][i]);
            }

            goal_left.push_back(goal[i]);
        }
    }

    // initializing left and right node with segrigated data
    point->left = this->fitTree(std::make_shared<node>(), data_left, goal_left, n + 1);
    point->right = this->fitTree(std::make_shared<node>(), data_right, goal_right, n + 1);

    // if this happens to be a leaf node then there needs to make a decision
    /*
    if(point->left == nullptr)
    {

    }
    */

    std::cout << "Data :\nCompare = " << point->comparator << "\nChoice = " << point->choice << std::endl;

    return point;
}


bool decisionTree::decide(std::vector<float> data)
{
    std::shared_ptr<node> point = root;
    bool decision = false;
    int c = 0;

    while(point != nullptr)
    {
        if(point->comparator > data[c])
        {
            point = point->left;
        }
        else
        {
            point = point->right;
        }

        c++; 

        if(c == data.size())
        {
            break;
        }

        if(point->left == nullptr && point->right ==nullptr)
        {
            decision = point->choice;
            break;
        }
    }

    return decision;
}


int main()
{
    std::vector<std::vector<float>> data {{2.5, 1.0, 3.0, 2.5, 1.5, 3.5, 2.0, 3.0}, // feature 1
                                        {3.0, 2.0, 1.5, 2.5, 3.5, 1.0, 2.0, 2.0},   // feature 2
                                        {1.5, 3.5, 2.0, 2.5, 1.0, 3.0, 2.0, 1.0}};  // feature 3

    std::vector<bool> goal {0, 1, 0, 0, 1, 0, 0, 1}; // target

    decisionTree tree1(data, goal);

    return 0;
}



