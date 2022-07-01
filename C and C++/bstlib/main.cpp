#include <iostream>
#include "bstlib.h"

int main() {
	int n = 0, data = 0;
	intbinaryTree tree1;

	std::cout << "Enter number of nodes: ";
	std::cin >> n;
	
	// int* arr = (int*)malloc(n * sizeof(int));

	std::cout << "Enter the data: \n";

	for(int i = 0; i < n; i++) {
		std::cin >> data;
		tree1.addNode(data);
	}

	std::cout << "\nInorder:\n";
	tree1.depthFirstInorder();

	return 0;
}



