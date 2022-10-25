#include <iostream>
#include <stack>


/*
* 
*/


// this function checks if the sent input is a symbol or not
bool is_symbol (char passed_sym) {
	
	if (passed_sym == '/' || passed_sym == '*' || passed_sym == '-' || passed_sym == '+') {
		
		return true;
	
	} else {
		
		return false;
		
	}
}

// the precidence function is defined to implement the bodmas rule 
int precidence (char passed_sym) {
	
	if (passed_sym == '/' || passed_sym == '*') {
		
		return 2; // Hisghest precidence
		
	} else if (passed_sym == '+' || passed_sym == '-') {
		
		return 1; // Lowest precidence
	
	} else {
		
		return -3333; // default value
		
	}
	
}

std::string return_postfix(std::string passed_string) {
	
	std::string postfix_exp = "", sub_expression = "";
	
	std::stack<char> opstack;
	
	std::stack<char> parenthesis_stack;
	
	
	for (int ichar = 0; ichar < passed_string.length(); ichar++) {
		
		std::cout << postfix_exp << std::endl;
		
		// the recursive block
		// this block cuts out the expression between parenthesis and sends it inside return_postfix
		if ( passed_string[ ichar ] == '(' ) {
			
			parenthesis_stack.push( passed_string[ ichar ] );
			ichar++; // increments the value of ichar to ignore the first '('
			
			while ( !parenthesis_stack.empty() ) {
				
				if ( passed_string[ ichar ] == '(' ) {
			
					parenthesis_stack.push( passed_string[ ichar ] );
				}
				
				if ( passed_string[ ichar ] == ')' ) {
			
					parenthesis_stack.pop();
				}
					
				sub_expression += passed_string[ ichar ];
				
				ichar++;
			}
			// after the while-loop sub_expression will have a extra ')' at its end. 
			sub_expression.pop_back(); // this statement removes this
			
			postfix_exp += return_postfix(sub_expression);

		}
		
		// this if-else block 
		if ( is_symbol( passed_string[ ichar ] ) ) {
					
			if (!opstack.empty()) { // aborts the block is the stack is empty, thus preventing a segmentation fault
				
				if ((precidence( passed_string[ ichar ] ) < precidence( opstack.top() ) ) ) { // if the 
				
					while (!opstack.empty()) {
			
						postfix_exp += opstack.top();
						
						opstack.pop();
						
					}
				}
			}
			
			opstack.push( passed_string[ ichar ] );
			
		} else { // if it is an operand it gets added to the expression directly
			
			if ( passed_string[ ichar ] != '(' && passed_string[ ichar ] != ')' ) {
				
				postfix_exp += passed_string[ ichar ];
			}
			
		}
		
	}
	
	while (!opstack.empty()) {
		
		postfix_exp += opstack.top();
		
		opstack.pop();
		
	}
	
	return postfix_exp;
}


int main() {
	
	// Variable definition
	
	std::string postfix_expression = "", input_string = "";
	
	std::cout << "Enter Expression : ";
	std::cin >> input_string;
	
	///////////////////////////////////////////////////////////////////
	
	
	postfix_expression = return_postfix( input_string );
	
	
	
	for (int iprint = 0; iprint < postfix_expression.length(); iprint++) {
			
		std::cout << postfix_expression[ iprint ];
		
	}
	std::cout << "\n";
	
	return 0;
}



