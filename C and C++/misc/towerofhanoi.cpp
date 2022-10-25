#include <iostream>
#include <stack>


/*
* donot put larger disk on smaller disk
* if num == even move from start to spare
* if num == odd move from start to target
* donot put even disk on even disk
* donot put odd disk on odd disk
*
* six possible moves :
* start => target ( when num is odd | when target.top() > start.top() | when target.top() and start.top() has different parity )
* start => spare ( | when target.top() > start.top() | when target.top() and start.top() has different parity )
* target => start
* target => spare
* spare => target
* spare => start
*/



void shiftTower(stack<int> &start, stack<int> &target, stack<int> &spare, int num) {
	
	if (num != 1) {
		
		target.push( start.top() );
		
		start.pop();
		
	} else { 
	
		
	
	}
	
}


int main() {
	
	stack<int> start, target, spare;
	
	int num = 0; // number of dicks
	
	std::cin >> num;
	
	for (int i = 0; i < num; i++) {
		
		start.push(num - i);
		
	}
	
	shiftTower(start, target, spare, num);
	
	return 0;
	
}

