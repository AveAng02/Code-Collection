
#include <iostream>
#include <vector>
#include <climits>



std::vector<int> bellmanFord(std::vector<std::vector<int>> graphDist, std::vector<std::vector<int>>& path, int source, int len)
{
	std::vector<int> dist;
	std::vector<int> pred;
	
	// Initialization
	
	for(int i = 0; i < len; i++)
	{
		dist.push_back(INT_MAX); // initializing all the distances to Max
		path.push_back(pred); // Definig a vector for all the paths
	}
	
	dist[source] = 0;
	
	// Distance and path calculation
	
	for(int u = 0, v = 0, i = 1; i < len; i++) // outer most loop for running it \V\ - 1 times
	{
		for(u = 0; u < len; u++)
		{
			for(v = 0; v < len; v++)
			{
				if(graphDist[u][v] != INT_MAX && dist[u] != INT_MAX) // to check for edges
				{
					if(dist[v] > dist[u] + graphDist[u][v]) // replacing path if shorter
					{
						dist[v] = dist[u] + graphDist[u][v];
						path[v].push_back(u); // generating the path
					}
				}
			}
		}
	}
	
	// Checking for negative weighted cycles
	
	return dist;
}



int main()
{
	std::vector<std::vector<int>> graph {{      0,      10,      20, INT_MAX, INT_MAX, INT_MAX},
										 {INT_MAX,       0, INT_MAX,      50,      10, INT_MAX},
										 {INT_MAX, INT_MAX,       0,      20,      33, INT_MAX},
										 {INT_MAX, INT_MAX, INT_MAX,       0,     -20,      -2},
										 {INT_MAX, INT_MAX, INT_MAX, INT_MAX,       0,       1},
										 {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,       0}};
	
	std::vector<std::string> tag = {"a", "b", "c", "d", "e", "f"};
	
	std::vector<std::vector<int>> path;
	
	std::vector<int> pathLen = bellmanFord(graph, path, 0, graph.size());
	
	std::cout << "Path Length : ";
	
	for(int i = 0; i < graph.size(); i++)
	{
		std::cout << pathLen[i] << " ";
	}
	
	std::cout << "\n";
	
	for(int j = 0, i = 1; i < path.size(); i++)
	{
		std::cout << "Path for " << tag[i] << " : ";
		
		for(j = 0; j < path[i].size(); j++)
		{
			std::cout << tag[path[i][j]] << " ";
		}
		
		std::cout << "\n";
	}
	
	std::cout << "\n";
	
	return 0;
}



