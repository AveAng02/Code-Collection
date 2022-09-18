
#include "KDTree.h"


	KDTree::KDTree()
	{
		this->CoOrdinateList = {{}};
		
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
		CoOrdinateList.clear();
		CoOrdinateList.shrink_to_fit();
	}


	bool KDTree::build()
	{
		std::cout << "Marker 0 : Starting Build" << std::endl; // Debugging marker
		
		KDNode* hook = root;
		
		std::vector<int> NodesCoOrd = {};
		
		// NumberOfDimen = CoOrdinateList[i].size();
		
		for(int while_counter = 0, dimen_tracker = 0, counter = 0; counter < CoOrdinateList.size(); counter++)
		{
			// push in the coordinates inside this for loop
			
			std::cout << "Marker 1 : Initializing all the values." << std::endl; // Debugging Marker
			
			dimen_tracker = 0; // track of the dimention to be compared against
			
			while_counter = 0; // counter for the while loop
			
			hook = this->root; // bringing back the hook to the root of the tree
			

			while(hook != nullptr)
			// while loop aims to return the pointer where the new KDNode is attached
			// at the end of the cycle hook is the pointer to this new node
			{
				/*
				* Algo for while loop:
				* 
				* 1. Run a while loop to find the nullptr.
				* 2. Inside the while loop iterate within the dimentions
				* 3. Check for greater or lesser against all dimentions except the one chosen
				* 4. If the dimention is greater then right otherwise left pointer gets the value
				* 5. In case the dimentions are equal then give precidence to left pointer
				*/
				
				
				std::cout << "Marker 2 : Entering While loop" << std::endl; // Debugging Marker
				
				// dimen_tracker is assigned the dimention we will check against
				// it iterates through all the position values from 0 to k which signifies the dimentions here
				// the modulus operator keeps the value within the range of 0 to k
				// 
				dimen_tracker = while_counter % CoOrdinateList[counter].size();
				
				
				// get the coordinates stored in thew node for comparison
				NodesCoOrd = hook->GetCoOrd();
				
				
				// comparison if blocks to check which direction to send the coordinate to
				if(NodesCoOrd[dimen_tracker] < CoOrdinateList[counter][dimen_tracker])
				// less than check leading to the left 
				{
					if(hook->GetLeftPointer() == nullptr)
					// if the left node is unoccupid then create a new node
					{
						// a new node is created by calling the NewNode function and is sent to create the left branch
						hook->AssignLeftPointer(NewNode(CoOrdinateList[counter]));
						
						hook = hook->GetLeftPointer();
						
						break;
					}
					else
					// if the left node is occupid then move on with by replacing hook with this new node
					{
						hook = hook->GetLeftPointer();
					}
				}
				else if(NodesCoOrd[dimen_tracker] > CoOrdinateList[counter][dimen_tracker])
				// Greater than checks leading to the right
				{
					if(hook->GetRightPointer() == nullptr)
					// if the Right node is unoccupid then create a new node
					{
						// a new node is created by calling the NewNode function and is sent to create the Right branch
						hook->AssignRightPointer(NewNode(CoOrdinateList[counter]));
						
						hook = hook->GetRightPointer();
						
						break;
					}
					else
					// if the Right node is occupid then move on with by replacing hook with this new node
					{
						hook = hook->GetRightPointer();
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
					if(hook->GetRightPointer() == nullptr)
					{
						hook->AssignRightPointer(NewNode(CoOrdinateList[counter]));
						
						hook = hook->GetRightPointer();
						
						break;
					}
					else
					{
						hook->AssignLeftPointer(NewNode(CoOrdinateList[counter]));
						
						hook = hook->GetLeftPointer();
						
						break;
					}
				}
				
				while_counter++; // to move on to the next dimention while checking
			}

		}
		
		
		return true;
	}


	bool KDTree::intersects()
	{
		return true;
	}


	KDNode* KDTree::NewNode(std::vector<int> coord)
	{
		std::cout << "Marker leaf : Creating a new node." << std::endl; // Debugging Marker
		
		// creating a new node
		KDNode* leaf = new KDNode(coord);
		
		// returning a reference to leaf
		return leaf;
	}

