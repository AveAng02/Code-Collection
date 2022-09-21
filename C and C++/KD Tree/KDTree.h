

#include <iostream>
#include <vector>


#include "KDNode.h"


class KDTree
{
	
public:

	KDTree();
	
	KDTree(std::vector<std::vector<int>> CoOrdinateList);
	
	~KDTree();
	
	bool build();
	
	bool intersects();
	
	void DFT();
	
	bool searchCoord(int X, int Y, int Z);
	
private:
	
	const int NUMDIMEN = 2; // Later change the 2 to 3 when we start entering 3d coordinates
	
	std::shared_ptr<KDNode> root;
	
	std::vector<std::vector<int>> CoOrdinateList;
	
	void recursiveDFT(std::shared_ptr<KDNode> traversal);
};








