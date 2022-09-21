
#include "KDNode.h"
	
	
KDNode::KDNode(int X = 0, int Y = 0, int Z = 0)
// For creating a node at a custom point
{
	this->X = X;
	this->Y = Y;
	this->Z = Z;
		
	left = nullptr;
		
	right = nullptr;
}
	
	
	
KDNode::~KDNode()
{
		
}



std::shared_ptr<KDNode> KDNode::CreateNewNode(int X = 0, int Y = 0, int Z = 0)
{
	std::shared_ptr<KDNode> leaf(new KDNode());
	
	leaf->X = X;
	leaf->Y = Y;
	leaf->Z = Z;
	
	leaf->left = nullptr;
	leaf->right = nullptr;
	
	return leaf;
}
	
	
	
