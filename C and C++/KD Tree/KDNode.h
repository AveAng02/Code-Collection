

#include <vector>

class KDNode
{
	std::vector<int> CoOrdinates;
	
	KDNode* left;
	
	KDNode* right;

public:
	
	KDNode();
	
	KDNode(std::vector<int> CoOrdinates);
	
	~KDNode();
	
	void AssignLeftPointer(KDNode* left);
	
	void AssignRightPointer(KDNode* right);
	
	KDNode* GetLeftPointer();
	
	KDNode* GetRightPointer();
	
	std::vector<int> GetCoOrd();
	
};

