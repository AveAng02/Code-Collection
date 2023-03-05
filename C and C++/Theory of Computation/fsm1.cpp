
#include <iostream>
#include <vector>


// S = (b+a)a(aa)* 
// S = c+a+bdd


class DFA
{
public:
	
	DFA() {}
	
	DFA(std::vector<std::string>              states_,
		std::vector<std::string>              alphabet_,
		std::vector<std::string>              iniState_,
		std::vector<std::string>              finalState_,
		std::vector<std::vector<std::string>> transTable_) : 
		states(states_),
		alphabet(alphabet_),
		iniState(iniState_),
		finalState(finalState_),
		transTable(transTable_)  {}
		
	~DFA()
	
	// std::string gen_Accept_String();
	// std::string gen_Unaccpt_String();
	bool check_str_accept(std::string);
	
private:
		
	std::vector<std::string>              states;
	std::vector<std::string>              alphabet;
	std::vector<std::string>              iniState;
	std::vector<std::string>              finalState;
	std::vector<std::vector<std::string>> transTable;
}


/*
std::string DFA::gen_Accept_String()
{
	
}


std::string DFA::gen_Unaccpt_String()
{
	
}
*/

bool DFA::check_str_accept(std::string)
{
	bool accept = false;
	
	std::string presState = iniState[0];
	
	
	
	
	
	
}






int main(int argc, char** argv) {
		
	std::cout << "Have " << argc << " arguments:" << std::endl;
		
	for (int i = 0; i < argc; i++) {
			
		std::cout << argv[i] << std::endl;
			
	}
		
		
}




