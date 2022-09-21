
#include <iostream>
#include <memory>


int main()
{
	std::shared_ptr<int> node1 = nullptr;
	std::shared_ptr<int> node2 = nullptr;
	
	if(node1 == nullptr || node2 == nullptr)
	{
		std::cout << "enters the loop" << std::endl;
	}
	
	return 0;
}



