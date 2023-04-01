
#include <iostream>
#include <vector>
#include <queue>
#include <climits>


bool bfs(std::vector<std::vector<int> graph, int source, int sink, std::vector<int>& path)
{
	std::queue q;
	bool flag = false;

	q.push(source);

	while(!q.empty())
	{
		for(int i = 0; i < graph[q.front()].size(); i++)
		{
			if(graph[q.front()][i] != INT_MAX)
		}

		if(q.back() == sink)
		{
			
		}
	}
}


int maxCapacity(std::vector<std::vector<int> graph, int source, int sink)
{
	std::vector<int> path;
	std::vector<std::vector<int> graph2 = graph;
	int max = 0;

	// Main loop
	while(bfs(graph2, source, sink, path))
	{
		int pathFlow = INT_MAX;

		for(int i = 1; i < path.size(); i++)
		{
			if(pathFlow > graph2[i - 1][i])
			{
				pathFlow = graph2[i - 1][i];
			}
		}

		max += pathFlow;

		for(int i = 1; i < path.size(); i++)
		{
			graph2[i - 1][i] -= pathFlow;
		}
	}

	return max;

	
}


int main()
{
	std::vector<std::vector<int>> graph {{      0,       2,       4, INT_MAX},
										 {INT_MAX,       0,       3,       1},
										 {INT_MAX, INT_MAX,       0,       5},
										 {INT_MAX, INT_MAX, INT_MAX,       6}};

	int maxCap = maxCapacity(graph, 0, 3);

	std::cout << "Max Capacity of the network = " << maxCap << std::endl;

	return 0;
}









