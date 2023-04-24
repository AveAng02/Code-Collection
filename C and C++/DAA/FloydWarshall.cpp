
#include <iostream>
#include <cfloat>
#include <vector>



std::vector<std::vector<double>> floydWarshall(std::vector<std::vector<double>> graph)
{
	std::vector<std::vector<double>> dist = graph;
	
	int len = dist.size();
	
	for(int i = 0, j = 0, k = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			for(k = 0; k < len; k++)
			{
				if(dist[j][k] > (dist[k][i] + dist[i][j]) &&
					dist[k][i] != DBL_MAX && dist[i][j] != DBL_MAX)
					{
						dist[j][k] = dist[k][i] + dist[i][j];
					}
			}
		}
	}
	
	return dist;
}


int main()
{
	
	std::vector<std::vector<double>> graph {{0.0, 5.0, DBL_MAX, 10.0},
											{DBL_MAX, 0.0, 3.0, DBL_MAX},
											{DBL_MAX, DBL_MAX, 0.0, 1.0},
											{DBL_MAX, DBL_MAX, DBL_MAX, 0.0}};
												
	std::vector<std::vector<double>> dist = floydWarshall(graph);
	
	for(int i = 0, j = 0; i < dist.size(); i++)
	{
		for(j = 0; j < dist[i].size(); j++)
		{
			if(dist[i][j] == DBL_MAX)
			{
				std::cout << " DBL_MAX ";
				continue;
			}
			
			std::cout << " " << dist[i][j] << " ";
		}
		
		std::cout << "\n";
	}
	
	return 0;
	
}













