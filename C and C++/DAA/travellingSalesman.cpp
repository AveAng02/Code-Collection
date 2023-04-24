
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
#define V 5

int travllingSalesmanProblem(int graph[V][V], int s)
{
    std::vector<int> vertex;
    std::vector<int> permu;
    std::vector<int> min_vertex;

    vertex.push_back(s);

    for (int i = 0; i < V; i++)
    {
        if (i != s)
        {
            permu.push_back(i);
            vertex.push_back(i);
        }
    }

    vertex.push_back(s);

    int min_path = INT_MAX;

    // permutation algorithm is impractical for large graphs
    do {
        int current_pathweight = 0;
        int k = s;

        // updating vertex vector with new permulation 
        for(int i = 0; i < V - 1; i++)
        {
            vertex[i + 1] = permu[i];
        }

        // calculating current weight
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }

        current_pathweight += graph[k][s];
 
        // update minimum
        if(min_path > current_pathweight)
        {
            min_path = current_pathweight;
            min_vertex = vertex;
        }

        // printing
        for(int i = 0; i < V + 1; i++)
        {
            std::cout << vertex[i] << ", ";
        }

        std::cout << current_pathweight << " \n";

    } while (std::next_permutation(permu.begin(), permu.end()));
    
    for(int i = 0; i < V + 1; i++)
    {
        std::cout << min_vertex[i] << ", ";
    }

    std::cout << "\n";

    return min_path;
}

int main()
{
    int graph[V][V] = {{ 0, 10, 15, 40, 20 },
                       { 10, 0, 35, 15, 12 },
                       { 15, 35, 0, 10, 25 },
                       { 40, 15, 10, 0, 30 },
                       { 20, 12, 25, 30, 0 }};
    int s = 0;
    int dist = travllingSalesmanProblem(graph, s);
    std::cout << dist << std::endl;
    return 0;
}