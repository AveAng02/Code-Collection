
// Debugging macro
// #define DEBUGGING_CONFIG

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

#ifdef DEBUGGING_CONFIG
		std::cout << "Marker 0 : Starting Build" << std::endl; // Debugging marker
		
		std::cout << "Creating Root Node with Coordinates : " << CoOrdinateList[0][0] << " " << CoOrdinateList[0][1] << " " << CoOrdinateList[0][2] << std::endl; // Debugging Marker
#endif
		
		root = root->CreateNewNode(CoOrdinateList[0][0], CoOrdinateList[0][1], CoOrdinateList[0][2]);
		
		std::shared_ptr<KDNode> hook = root;
		
		std::vector<int> NodesCoOrd = {};
		
		// NumberOfDimen = CoOrdinateList[i].size();
		
		for(int while_counter = 1, dimen_tracker = 0, counter = 1; counter < CoOrdinateList.size(); counter++)
		{
			// push in the coordinates inside this for loop
			
#ifdef DEBUGGING_CONFIG
			std::cout << "Marker 1 : Initializing all the values." << std::endl; // Debugging Marker
#endif
			
			dimen_tracker = 0; // track of the dimention to be compared against
			
			while_counter = 0; // counter for the while loop
			
			hook = root; // bringing back the hook to the root of the tree
			

			while(hook != nullptr)
			// while loop aims to return the pointer where the new KDNode is attached
			// at the end of the cycle hook is the pointer to this new node
			{
				NodesCoOrd.clear(); // clearing out the vector to enter new coordinates
				
				/*
				* Algo for while loop:
				* 
				* 1. Run a while loop to find the nullptr.
				* 2. Inside the while loop iterate within the dimentions
				* 3. Check for greater or lesser against the dimention chosen
				* 4. If the dimention is greater then right otherwise left pointer gets the value
				* 5. In case the dimentions are equal then give precidence to left pointer
				*/
				
#ifdef DEBUGGING_CONFIG
				std::cout << "Marker 2 : Entering While loop " << while_counter + 1 << std::endl; // Debugging Marker
#endif
				
				// dimen_tracker is assigned the dimention we will check against
				// it iterates through all the position values from 0 to k which signifies the dimentions here
				// the modulus operator keeps the value within the range of 0 to k
				// 
				dimen_tracker = while_counter % NUMDIMEN; 
				
				// get the coordinates stored in the node for comparison
				NodesCoOrd.push_back(hook->X);
				NodesCoOrd.push_back(hook->Y);
				NodesCoOrd.push_back(hook->Z);
				
#ifdef DEBUGGING_CONFIG
				std::cout << "Comparison Node : { " << NodesCoOrd[0] << ", " << NodesCoOrd[1] << ", " << NodesCoOrd[2] << "} " << std::endl;
#endif
				
				// comparison if blocks to check which direction to send the coordinate to
				if(NodesCoOrd[dimen_tracker] > CoOrdinateList[counter][dimen_tracker])
				// less than check leading to the left 
				{
					if(hook->left == nullptr)
					// if the left node is unoccupid then create a new node
					{
						// a new node is created by calling the NewNode function and is sent to create the left branch
						hook->left = hook->CreateNewNode(CoOrdinateList[counter][0], CoOrdinateList[counter][1], CoOrdinateList[counter][2]);
						
#ifdef DEBUGGING_CONFIG
						std::cout << "Marker 4(1) : Going left at { " << hook->X << ", " << hook->Y << ", " << hook->Z << "} " << std::endl; // Debugging Marker
						
						std::cout << "Marker 3 (1): Creating a Node on the left subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
#endif
						
						break;
					}
					else
					// if the left node is occupid then move on with by replacing hook with this new node
					{

#ifdef DEBUGGING_CONFIG
						std::cout << "Marker 4(1) : Going left at { " << hook->X << ", " << hook->Y << ", " << hook->Z << "} " << std::endl; // Debugging Marker
#endif
						
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
						
#ifdef DEBUGGING_CONFIG
						std::cout << "Marker 4(2) : Going right @ at { " << hook->X << ", " << hook->Y << ", " << hook->Z << "} " << std::endl; // Debugging Marker
						
						std::cout << "Marker 3 (2): Creating a Node on the right subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
#endif
						
						break;
					}
					else
					// if the Right node is occupid then move on with by replacing hook with this new node
					{
#ifdef DEBUGGING_CONFIG
						std::cout << "Marker 4(2) : Going right  # at { " << hook->X << ", " << hook->Y << ", " << hook->Z << "} " << std::endl; // Debugging Marker
#endif
						
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
						
#ifdef DEBUGGING_CONFIG
						std::cout << "Marker 4(2) : Going right $ at { " << hook->X << ", " << hook->Y << ", " << hook->Z << "} " << std::endl; // Debugging Marker
						
						std::cout << "Marker 3 (4): Creating a Node on the right subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
#endif
						
						break;
					}
					else
					{
						hook->left = hook->CreateNewNode(CoOrdinateList[counter][0], CoOrdinateList[counter][1], CoOrdinateList[counter][2]);
						
#ifdef DEBUGGING_CONFIG
						std::cout << "Marker 4(1) : Going left  at { " << hook->X << ", " << hook->Y << ", " << hook->Z << "} " << std::endl; // Debugging Marker
						
						std::cout << "Marker 3 (3): Creating a Node on the left subtree with Coordinates : " << CoOrdinateList[counter][0] << " " << CoOrdinateList[counter][1] << " " << CoOrdinateList[counter][2] << std::endl; // Debugging Marker
#endif
						
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
	
	
	void KDTree::DFT()
	{
		if(root == nullptr)
		{
			std::cout << "\nTree not built yet.\n" << std::endl;
			
			return;
		}
		
		std::cout << "\nRoot : ";
		
		recursiveDFT(root);
		
		std::cout << std::endl;
	}


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


bool KDTree::searchCoord(int X, int Y, int Z)
{
	std::shared_ptr<KDNode> traversal = root;
	
	int while_counter = 0; // as 'X' is already checked thus we assign 1 to while and start from 'Y'
	
	int dimen_tracker = 0; // tracks which dimention the nodes will be checked against
	
#ifdef DEBUGGING_CONFIG
	std::cout << "Search Marker 1 : Starting Search" << std::endl; // Debugging marker
#endif
	
	while(traversal != nullptr)
	{
		dimen_tracker = while_counter % NUMDIMEN; 
		
#ifdef DEBUGGING_CONFIG
		std::cout << "Checking against : { " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "} " << std::endl;
#endif
		
		if(dimen_tracker == 0)
		{
			// check against X
			if(traversal->X == X && traversal->Y == Y && traversal->Z == Z)
			// check if the required coordinate is at root
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 2(1) : Node Found" << std::endl; // Debugging marker
#endif
				
				return true;
			}
			else if(traversal->X >= X && traversal->left != nullptr)
			// if X is smaller or equal send to left subtree
			// the build is biased towards left subtree in case X are equal
			// thus search also has the same bias to find the coordinate 
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 3(1) : Going Left" << std::endl; // Debugging marker
				
				std::cout << " { " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "} " << std::endl;
#endif
				
				traversal = traversal->left;
			}
			else if(traversal->X >= X && traversal->left != nullptr)
			// if X is smaller or equal send to left subtree
			// the build is biased towards left subtree in case X are equal
			// thus search also has the same bias to find the coordinate 
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 2(2) : Node Not Found" << std::endl; // Debugging marker
#endif
				
				return false;
			}
			else
			// if X is greater than then send to right subtree
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 3(2) : Going right" << std::endl; // Debugging marker
				
				std::cout << " { " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "} " << std::endl;
#endif
				
				traversal = traversal->right;
			}
		}
		else if(dimen_tracker == 1)
		{
			// check against Y
			if(traversal->X == X && traversal->Y == Y && traversal->Z == Z)
			// check if the required coordinate is at root
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 2(1) : Node Found" << std::endl; // Debugging marker
#endif
				
				return true;
			}
			else if(traversal->Y >= Y && traversal->left != nullptr)
			// if X is smaller or equal send to left subtree
			// the build is biased towards left subtree in case X are equal
			// thus search also has the same bias to find the coordinate 
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 3(1) : Going Left" << std::endl; // Debugging marker
				
				std::cout << " { " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "} " << std::endl;
#endif
				
				traversal = traversal->left;
			}
			else if(traversal->Y >= Y && traversal->left != nullptr)
			// if X is smaller or equal send to left subtree
			// the build is biased towards left subtree in case X are equal
			// thus search also has the same bias to find the coordinate 
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 2(2) : Node Not Found" << std::endl; // Debugging marker
#endif
				
				return false;
			}
			else
			// if X is greater than then send to right subtree
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 3(2) : Going right" << std::endl; // Debugging marker
				
				std::cout << " { " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "} " << std::endl;
#endif
				
				traversal = traversal->right;
			}
		}
		else
		{
			// check against Z
			// check against X
			if(traversal->X == X && traversal->Y == Y && traversal->Z == Z)
			// check if the required coordinate is at root
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 2(1) : Node Found" << std::endl; // Debugging marker
#endif
				
				return true;
			}
			else if(traversal->Z >= Z && traversal->left != nullptr)
			// if X is smaller or equal send to left subtree
			// the build is biased towards left subtree in case X are equal
			// thus search also has the same bias to find the coordinate 
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 3(1) : Going Left" << std::endl; // Debugging marker
				
				std::cout << " { " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "} " << std::endl;
#endif
				
				traversal = traversal->left;
			}
			else if(traversal->Z >= Z && traversal->left != nullptr)
			// if X is smaller or equal send to left subtree
			// the build is biased towards left subtree in case X are equal
			// thus search also has the same bias to find the coordinate 
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 2(2) : Node Not Found" << std::endl; // Debugging marker
#endif
				
				return false;
			}
			else
			// if X is greater than then send to right subtree
			{
#ifdef DEBUGGING_CONFIG
				std::cout << "Search Marker 3(2) : Going right" << std::endl; // Debugging marker
				
				std::cout << " { " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "} " << std::endl;
#endif
			
				traversal = traversal->right;
			}
		}
		
		
		while_counter++;
	}
	
#ifdef DEBUGGING_CONFIG
	std::cout << "Search Marker 2(3) : Node Not Found" << std::endl; // Debugging marker
#endif
	
	return false; // if the control falls out of the loop then the point is possibly not there
}


void KDTree::recursiveDFT(std::shared_ptr<KDNode> traversal)
{
	std::cout << "{ " << traversal->X << ", " << traversal->Y << ", " << traversal->Z << "}" << std::endl;
	
	if(traversal->left != nullptr)
	{
		std::cout << "Left Node : ";
		
		recursiveDFT(traversal->left);
	}
	
	if(traversal->right != nullptr)
	{
		std::cout << "Right Node : ";
		
		recursiveDFT(traversal->right);
	}
}



