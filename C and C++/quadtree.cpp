

struct quadnode {
	
	// Data
	int data;
	
	// Links to next generation of nodes
	quadnode* topleft;
	quadnode* topright;
	quadnode* downright;
	quadnode* downleft;
	
};


class quadtree {
	
	// Pointer to the quadtree
	quadnode top;
	
	
	
	public:
	
		quadtree() {
			
			// setting root data to 0
			top.data = 0;
			
			// anchouring root's pointers to NULL
			top.topleft = NULL;
			top.topright = NULL;
			top.downright = NULL;
			top.downleft = NULL;
			
		}
		
		
		
		void newNode( 
		
		
		// quadtree traversal
	
};



