

#include <iostream>
#include <vector>


#include "KDNode.h"


class KDTree
{
	
public:

	KDTree()
	{
		this->root = nullptr;
	}


	KDTree(std::vector<int> CoOrdinateList)
	// Custom constructor to make a tree with a particular coordinate list
	{
		this->CoOrdinateList = CoOrdinateList;
		
		this->root = nullptr;
	}


	~KDTree() { }
	// KD tree destructor to remove the CoOrdinateList and the KDTree from memory

	
	bool build();
	
	bool intersects();
	
	void DFT(int &c);
	
	bool searchCoord(int X, int Y, int Z);
	
private:
	
	const int NUMDIMEN = 3; // Later change the 2 to 3 when we start entering 3d coordinates
	
	std::shared_ptr<KDNode> root;
	
	std::vector<int> CoOrdinateList;
	
	void recursiveDFT(std::shared_ptr<KDNode> traversal, int &c);
};








