
#include "KDNode.h"
	
	
	KDNode::KDNode()
	// For creating a default 2D node
	{
		CoOrdinates = {0,0};
		
		left = nullptr;
		
		right = nullptr;
	}
	
	
	
	KDNode::KDNode(std::vector<int> CoOrdinates)
	// For creating a n-d node
	{
		this->CoOrdinates = CoOrdinates;
		
		left = nullptr;
		
		right = nullptr;
	}
	
	
	
	KDNode::~KDNode()
	{
		CoOrdinates.clear();
		CoOrdinates.shrink_to_fit();
	}



	void KDNode::AssignLeftPointer(KDNode* left)
	{
		this->left = left;
	}
	
	
	
	void KDNode::AssignRightPointer(KDNode* right)
	{
		this->right = right;
	}
	
	
	
	KDNode* KDNode::GetLeftPointer()
	{
		return left;
	}
	
	
	
	KDNode* KDNode::GetRightPointer()
	{
		return right;
	}
	
	
	std::vector<int> KDNode::GetCoOrd()
	{
		return CoOrdinates;
	}
	
	
	
	
