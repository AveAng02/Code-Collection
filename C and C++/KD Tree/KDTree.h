

#include <iostream>

#include "KDNode.cpp"


class KDTree
{
public:

	KDTree();
	
	KDTree(std::vector<std::vector<int>> CoOrdinateList);
	
	~KDTree();
	
	bool build();
	
	bool intersects();
	
private:
	
	KDNode* root;
	
	KDNode* NewNode(std::vector<int> coord);
	
	std::vector<std::vector<int>> CoOrdinateList;
};








