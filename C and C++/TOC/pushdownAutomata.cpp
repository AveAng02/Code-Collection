
#include <iostream>
#include <vector>
#include <stack>



class transition_relation
{
public:


private:

};




class pda
{
public:
	
	pda(std::vector<std::string>   Q_,
		std::vector<std::string>   sigma_,
		std::stack<std::string>    gamma_,
		transition_relation        delta_,
		std::vector<std::string>   Q0_,
		std::vector<std::string>   F_):
		Q(Q_),
		sigma(sigma_),
		gamma(gamma_),
		delta(delta_),
		Q0(Q0_),
		F(F_)
	{
		Z = "Z0";
	}
	
	
	
	
private:
	
	std::vector<std::string> Q; // states
	
	std::vector<std::string> sigma; // input alphabet
	
	std::stack<std::string> gamma; // stack alphabet
	
	transition_relation delta; 
	
	std::vector<std::string> Q0; // start state
	
	std::string Z; // initial stack symbol
	
	std::vector<std::string> F; // set of accepting states
	
};





int main()
{
	
	return 0;
}




