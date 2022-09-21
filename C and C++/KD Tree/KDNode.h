
#include <memory>


class KDNode
{

public:

	KDNode(int X, int Y, int Z);
	
	~KDNode();

	std::shared_ptr<KDNode> CreateNewNode(int X, int Y, int Z);

	int X;
	int Y;
	int Z;
	
	std::shared_ptr<KDNode> left;
	
	std::shared_ptr<KDNode> right;
	
};

