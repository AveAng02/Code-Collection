
#include <iostream>
#include <climits>
#include <vector>


std::vector<double> bellmanFord(std::vector<std::vector<double>> graph, int vertex)
{
	std::vector<double> dist = graph[vertex];
	
	// Setting all the distance values to INT_MAX
	for(int i = 0; i < dist.size(); i++)
		dist[i] = INT_MAX;
	
	dist[vertex] = 0;
	
	// Calculating the distance
	for(int u = 0, v = 0, wt = 0, j = 0, i = 1; i < dist.size(); i++)
	{
		for(j = 0; j < dist.size() * dist.size(); j++)
		{
			u = (int)(j / dist.size());
			v = j % dist.size();
			wt = graph[u][v];
			
			if(wt == INT_MAX | u == v)
				continue;
			
			if(dist[u] != INT_MAX && (dist[u] + wt) < dist[v])
				dist[v] = dist[u] + wt;
		}
	}
	
	// Checking for negative-weight cycles
	for(int u = 0, v = 0, wt = 0, j = 0; j < dist.size() * dist.size(); j++)
	{
		u = (int)(j / dist.size());
		v = j % dist.size();
		wt = graph[u][v];
			
		if(wt == INT_MAX | u == v)
			continue;
			
		if(dist[u] != INT_MAX && (dist[u] + wt) < dist[v])
		{
			std::cout << "Graph contains negative weighted cycle." << std::endl;
			return dist;
		}
	}
	
	
	return dist;
}



int main()
{
	                                     //     A 	     B 	     C 	       D 	    E
	std::vector<std::vector<double>> graph {{      0,      -1,       4, INT_MAX, INT_MAX},   // A
											{INT_MAX,       0,       3,       2,       2},   // B
											{INT_MAX, INT_MAX,       0, INT_MAX, INT_MAX},   // C
											{INT_MAX,       1,       5,       0, INT_MAX},   // D
											{INT_MAX, INT_MAX, INT_MAX,      -3,       0}};  // E
											
	std::vector<double> dist = bellmanFord(graph, 0);

	for(int i = 0; i < dist.size(); i++)
	{
		std::cout << " " << i << " --> ";
		
		if(dist[i] == INT_MAX)
		{
			std::cout << "INT_MAX" << std::endl;
			continue;
		}
		
		std::cout << dist[i]<< std::endl;
	}
	
	return 0;
}




