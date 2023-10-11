
<<<<<<< Updated upstream
#include <vector>
#include <unordered_map>



enum lionType
{
    RESIDENT,
    NOMAD
};


class Prey
{
public:
    Prey()
    {

    }


private:
    std::unordered_map<double, double> currentPos;
    std::vector<std::unordered_map<double, double>> positionList;
};


class Lion
{
public:
    Lion()
    {

    }

private:
    std::unordered_map<double, double> currentPos;
    std::vector<std::unordered_map<double, double>> positionList;
    bool gender;
};


class Pride
{
public:
    Pride()
    {
        // Initialization
    }

    void convergence();
    void populationEqui();

private:
    std::vector<Lion> groups;
    int prideSz;
};


void Hunting(Lion, Prey);
void Roaming(Lion);
void Mating(Lion, Lion);



int main()
{


    return 0;
}
=======
#include <iostream>
#include <vector>
#include <algorithm>






>>>>>>> Stashed changes



