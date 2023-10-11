
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// Production rule
struct Rule {
    char lhs;    // Left-hand side of the production
    string rhs;  // Right-hand side of the production
};

// LR(0) Parser class
class LRParser {
private:
    vector<Rule> grammar;                     // Grammar rules
    unordered_map<char, unordered_map<char, int>> actionTable;  // Action table
    unordered_map<char, unordered_map<char, int>> gotoTable;    // Goto table
    stack<int> parseStack;                     // Parse stack

public:
    LRParser(vector<Rule> grammar)
        : grammar(grammar) {}

    void addAction(int state, char symbol, int action) {
        actionTable[state][symbol] = action;
		// cout << "Symbol : " << symbol << " ; State : " << state << " ; Action : "
		// << action << endl;
    }

    void addGoto(char state, char symbol, int nextState) {
        gotoTable[state][symbol] = nextState;
    }

    bool parse(string input) {
        input += '$';  // Append end-of-input marker

        parseStack.push(0);  // Initial state

        size_t inputIndex = 0;
        while (true) {
            int currentState = parseStack.top();
            char currentSymbol = input[inputIndex];

            int action = actionTable[currentState][currentSymbol];

			cout << "Symbol : " << currentSymbol << " ; State : " << currentState
			<< " ; Action : " << action << endl;

            if (action == 0) {
                cout << "Error: Invalid action for state " << currentState 
				<< " and symbol " << currentSymbol << endl;
                return false;
            } else if (action == -1) {
                cout << "Error: Unexpected symbol " << currentSymbol << " at state " 
				<< currentState << endl;
                return false;
            } else if (action > 0) {
                parseStack.push(action);
                inputIndex++;
            } else if (action < 0) {
                const Rule& rule = grammar[-action];
                for (size_t i = 0; i < rule.rhs.length(); i++) {
                    parseStack.pop();
                }

                int nextState = gotoTable[parseStack.top()][rule.lhs];
                parseStack.push(nextState);

                cout << rule.lhs << " -> " << rule.rhs << endl;

                if (rule.lhs == 'S' && inputIndex == input.length() - 1) {
                    cout << "Input successfully parsed!" << endl;
                    return true;
                }
            }
        }
    }
};

int main() {
    // Define the grammar rules
    vector<Rule> grammar = {
        {'S', "E"},
        {'E', "E+T"},
        {'E', "T"},
        {'T', "T*F"},
        {'T', "F"},
        {'F', "(E)"},
        {'F', "id"},
    };

    // Create an LR(0) parser
    LRParser parser(grammar);

    // Add the action and goto entries for the parser's tables
    parser.addAction(0, '(', 4);
    parser.addAction(0, 'id', 5);
    parser.addGoto(0, 'E', 1);
    parser.addGoto(0, 'T', 2);
    parser.addGoto(0, 'F', 3);
    parser.addAction(1, '+', 6);
    parser.addAction(1, '$', -1);
    parser.addAction(2, '+', -3);
    parser.addAction(2, '*', 7);
    parser.addAction(2, '$', -3);
    parser.addAction(3, '+', -6);
    parser.addAction(3, '*', -6);
    parser.addAction(3, ')', -6);
    parser.addAction(3, '$', -6);
    parser.addAction(4, '(', 4);
    parser.addAction(4, 'id', 5);
    parser.addGoto(4, 'E', 8);
    parser.addGoto(4, 'T', 2);
    parser.addGoto(4, 'F', 3);
    parser.addAction(5, '+', -2);
    parser.addAction(5, '*', -2);
    parser.addAction(5, ')', -2);
    parser.addAction(5, '$', -2);
    parser.addAction(6, '(', 4);
    parser.addAction(6, 'id', 5);
    parser.addAction(7, '(', 4);
    parser.addAction(7, 'id', 5);
    parser.addAction(8, '+', 6);
    parser.addAction(8, ')', 9);
    parser.addAction(8, '$', -3);
    parser.addAction(9, '+', -5);
    parser.addAction(9, '*', 7);
    parser.addAction(9, ')', -5);
    parser.addAction(9, '$', -5);

    // Parse an input
    parser.parse("d+d*d");

    return 0;
}
