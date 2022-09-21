

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
	
private:
	
	std::shared_ptr<KDNode> root;
	
	std::vector<std::vector<int>> CoOrdinateList;
};








