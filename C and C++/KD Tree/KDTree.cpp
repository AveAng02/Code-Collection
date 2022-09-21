
#include "KDTree.h"


	KDTree::KDTree()
	{
		this->root = nullptr;
	}


	KDTree::KDTree(std::vector<std::vector<int>> CoOrdinateList)
	// Custom constructor to make a tree with a particular coordinate list
	{
		this->CoOrdinateList = CoOrdinateList;
		
		this->root = nullptr;
	}


	KDTree::~KDTree()
	// KD tree destructor to remove the CoOrdinateList and the KDTree from memory
	{
		
	}


	// balance the KDTree while building 	

	bool KDTree::build()
	{
		std::cout << "Marker 0 : Starting Build" << std::endl; // Debugging marker
		
		root = root->CreateNewNode(CoOrdinateList[0][0], CoOrdinateList[0][1], CoOrdinateList[0][2]);
		
		std::shared_ptr<KDNode> hook = root;
		
		std::vector<int> NodesCoOrd = {};
		
		// NumberOfDimen = CoOrdinateList[i].size();
		
		for(int while_counter = 0, dimen_tracker = 0, counter = 1; counter < CoOrdinateList.size(); counter++)
		{
			// push in the coordinates inside this for loop
			
			std::cout << "Marker 1 : Initializing all the values." << std::endl; // Debugging Marker
			
			dimen_tracker = 0; // track of the dimention to be compared against
			
			while_counter = 0; // counter for the while loop
			
			hook = root; // bringing back the hook to the root of the tree
			

			while(hook != nullptr)
			// while loop aims to return the pointer where the new KDNode is attached
			// at the end of the cycle hook is the pointer to this new node
			{
				/*
				* Algo for while loop:
				* 
				* 1. Run a while loop to find the nullptr.
				* 2. Inside the while loop iterate within the dimentions
				* 3. Check for greater or lesser against the dimention chosen
				* 4. If the dimention is greater then right otherwise left pointer gets the value
				* 5. In case the dimentions are equal then give precidence to left pointer
				*/
				
				
				std::cout << "Marker 2 : Entering While loop" << std::endl; // Debugging Marker
				
				// dimen_tracker is assigned the dimention we will check against
				// it iterates through all the position values from 0 to k which signifies the dimentions here
				// the modulus operator keeps the value within the range of 0 to k
				// 
				dimen_tracker = while_counter % 2; // later change this to 3 for 3D
				
				
				// get the coordinates stored in the node for comparison
				NodesCoOrd.push_back(hook->X);
				NodesCoOrd.push_back(hook->Y);
				NodesCoOrd.push_back(hook->Z);
				
				
				// comparison if blocks to check which direction to send the coordinate to
				if(NodesCoOrd[dimen_tracker] > CoOrdinateList[counter][dimen_tracker])
				// less than check leading to the left 
				{
					if(hook->left == nullptr)
					// if the left node is unoccupid then create a new node
					{
						// a new node is created by calling the NewNode function and is sent to create the left branch
						hook->left = hook->CreateNewNode(CoOrdinateList[counter][0], CoOrdinateList[counter][1], CoOrdinateList[counter][2]);
						
						std::cout << "Marker 3 (1): Creating a Node on the left subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
						
						hook = hook->left;
						
						break;
					}
					else
					// if the left node is occupid then move on with by replacing hook with this new node
					{
						hook = hook->left;
					}
				}
				else if(NodesCoOrd[dimen_tracker] < CoOrdinateList[counter][dimen_tracker])
				// Greater than checks leading to the right
				{
					if(hook->right == nullptr)
					// if the Right node is unoccupid then create a new node
					{
						// a new node is created by calling the NewNode function and is sent to create the Right branch
						hook->right = hook->CreateNewNode(CoOrdinateList[counter][0], CoOrdinateList[counter][1], CoOrdinateList[counter][2]);
						
						std::cout << "Marker 3 (2): Creating a Node on the right subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
						
						hook = hook->right;
						
						break;
					}
					else
					// if the Right node is occupid then move on with by replacing hook with this new node
					{
						hook = hook->right;
					}
				}
				else
				// Equality block
				{
					/*
					* when both the values of the coordinate are equal 
					* then first it is checked which side is empty
					* if both are full then left is given precidence
					*
					* !!! CHANGE THIS PART TO CHECK FOR THE WEIGHT ON BOTH SIDES AND THEN ASSIGN !!!
					* !!! SO AS TO CREATE A BALANCED TREE !!!
					*
					*/
					if(hook->right == nullptr)
					{
						hook->right = hook->CreateNewNode(CoOrdinateList[counter][0], CoOrdinateList[counter][1], CoOrdinateList[counter][2]);
						
						std::cout << "Marker 3 (4): Creating a Node on the right subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
						
						hook = hook->right;
						
						break;
					}
					else
					{
						hook->left = hook->CreateNewNode(CoOrdinateList[counter][0], CoOrdinateList[counter][1], CoOrdinateList[counter][2]);
						
						std::cout << "Marker 3 (3): Creating a Node on the left subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
						
						hook = hook->left;
						
						break;
					}
				}
				
				while_counter++; // to move on to the next dimention while checking
			}

			
		}
		
		
		return true;
	}



	/*
	*	check if the tree works with
	*	> nearest neighbour
	*	> DFS
	*/


	bool KDTree::intersects()
	{
		/*
		*	takes a ray as a parameter
		*	and intersection info(payload)
		*
		*	checks if the ray hits any one of the nodes
		*	if it does then puts the closest intersection and updates it to the payload
		*
		*	returns true or false
		*/
		
		return true;
	}







