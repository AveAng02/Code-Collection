
#include <iostream>
#include <vector>
#include <climits>

/*
	Dijkstra's Algorithm : An algorithm to find the shortest path between 
	                       one node and the rest of the nodes.
						
	Referred to : https://www.freecodecamp.org/news/dijkstras-shortest-path-algorithm-visual-introduction/
	
*/



template<class T>

	class Graph
	{
		
	private:
		
		std::vector<std::vector<int>> AdjMatrix;  // a 2D Vector that stores the node weights of the graph
		
		int NodesNum; // Number of nodes
		
		std::vector<T> Nodes; // Vector of nodes
		
		std::vector<T> UnVisited; // Vector of nodes not yet visited
		
		
	public:
		
		Graph() // Default Constructor to initialize the values
		{
			AdjMatrix = {{}};
			
			NodesNum = 0;
			
			Nodes = {};
			
			UnVisited = {};
		}
		
		
		
		Graph(int NodesNum, std::vector<T> Nodes, std::vector<std::vector<int>> AdjMatrix)
		// Parameterized constructer to initialize class with particular values
		{
			this->NodesNum = NodesNum;
			
			this->Nodes = Nodes;
			
			this->AdjMatrix = AdjMatrix;	
			
			UnVisited = {};
		}
		
		
		
		void display()
		// function to display the matrix and nodes on the console
		{
			
			for(int i = 0; i < NodesNum; i++)
			{
				std::cout << " " << Nodes[i] << " ";
			}
			
			std::cout << "\n" << std::endl;
			
			for(int j = 0, i = 0; i < NodesNum; i++)
			{
				for(j = 0; j < NodesNum; j++)
				{
					std::cout << "| " << AdjMatrix[i][j] << " |";
				}
				
				std::cout << std::endl;
			}
		}
			
		
		
		void Dijkstra(T source)
		{
			T Vt = source;
			
			int dist[NodesNum];
			
			for(int i = 0; i < NodesNum; i++)
			// forloop to update unvisited nodes and their distance
			{
				if(Nodes[i] != Vt)
				{
					UnVisited.push_back(Nodes[i]);
					
					dist[i] = INT_MAX;
				}
				else
				{
					dist[i] = 0;
				}
			}
			
			
			
			
			
		}
		
		
	};



int main()
{
	std::vector<char> nodes {'S', 'T', 'X', 'Y', 'Z'};
	
	int NumberOfNodes = 5;
	
	std::vector<std::vector<int>> matrix {{INT_MAX, 10, INT_MAX, 5, INT_MAX}, 
										  {INT_MAX, INT_MAX, 1, 2, INT_MAX}, 
										  {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 4}, 
										  {INT_MAX, 3, 9, INT_MAX, 2}, 
										  {7, INT_MAX, 6, INT_MAX, INT_MAX}};
	
	Graph<char> gph1(NumberOfNodes, nodes, matrix);
	
	gph1.display();
	
	
	
	return 0;
}




