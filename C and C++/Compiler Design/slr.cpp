
#include <iostream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// Production rule
struct Rule {
    char lhs;    // Left-hand side of the production
    string rhs;  // Right-hand side of the production
};

// LR(0) Item
struct Item {
    int ruleIndex;  // Index of the rule in the grammar
    int dotPos;     // Position of the dot in the rule

    bool operator==(const Item& other) const {
        return ruleIndex == other.ruleIndex && dotPos == other.dotPos;
    }
};

// Hash function for LR(0) Item
struct ItemHash {
    size_t operator()(const Item& item) const {
        return hash<int>()(item.ruleIndex) ^ hash<int>()(item.dotPos);
    }
};

// SLR(1) Parser class
class SLRParser {
private:
    vector<Rule> grammar;                                 // Grammar rules
    unordered_map<char, unordered_set<char>> firstSets;   // First sets
    unordered_map<char, unordered_set<char>> followSets;  // Follow sets
    unordered_map<char, unordered_map<char, int>> actionTable;  // Action table
    unordered_map<char, unordered_map<char, int>> gotoTable;    // Goto table
    stack<int> parseStack;                                 // Parse stack

public:
    SLRParser(vector<Rule> grammar)
        : grammar(grammar) {}

    void calculateFirstSets() {
        for (const auto& rule : grammar) {
            char lhs = rule.lhs;
            char rhsFirst = rule.rhs[0];

            if (!isNonTerminal(rhsFirst)) {
                firstSets[lhs].insert(rhsFirst);
            }
        }

        bool updated;
        do {
            updated = false;

            for (const auto& rule : grammar) {
                char lhs = rule.lhs;
                const string& rhs = rule.rhs;

                for (size_t i = 0; i < rhs.length(); i++) {
                    char symbol = rhs[i];

                    if (isNonTerminal(symbol)) {
                        for (char firstSymbol : firstSets[symbol]) {
                            if (firstSets[lhs].count(firstSymbol) == 0) {
                                firstSets[lhs].insert(firstSymbol);
                                updated = true;
                            }
                        }

                        if (!isNullable(symbol))
                            break;
                    } else {
                        break;
                    }
                }
            }
        } while (updated);
    }

    void calculateFollowSets() {
        followSets[grammar[0].lhs].insert('$');  // Start symbol

        bool updated;
        do {
            updated = false;

            for (const auto& rule : grammar) {
                char lhs = rule.lhs;
                const string& rhs = rule.rhs;

                for (size_t i = 0; i < rhs.length(); i++) {
                    char symbol = rhs[i];

                    if (isNonTerminal(symbol)) {
                        bool symbolNullable = true;
                        for (size_t j = i + 1; j < rhs.length(); j++) {
                            char nextSymbol = rhs[j];

                            if (!isNullable(nextSymbol)) {
                                symbolNullable = false;

                                for (char followSymbol : followSets[lhs]) {
                                    if (followSets[symbol].count(followSymbol) == 0) {
                                        followSets[symbol].insert(followSymbol);
                                        updated = true;
                                    }
                                }

                                break;
                            }
                        }

                        if (symbolNullable) {
                            for (char followSymbol : followSets[lhs]) {
                                if (followSets[symbol].count(followSymbol) == 0) {
                                    followSets[symbol].insert(followSymbol);
                                    updated = true;
                                }
                            }
                        }
                    }
                }
            }
        } while (updated);
    }

    void calculateLR0Items(vector<unordered_set<Item, ItemHash>>& itemSets) {
        Item initialItem{0, 0};
        unordered_set<Item, ItemHash> initialSet{initialItem};
        itemSets.push_back(initialSet);

        bool updated;
        do {
            updated = false;

            for (size_t i = 0; i < itemSets.size(); i++) {
                const unordered_set<Item, ItemHash>& itemSet = itemSets[i];

                unordered_set<char> lookaheadSymbols;
                for (const Item& item : itemSet) {
                    int ruleIndex = item.ruleIndex;
                    int dotPos = item.dotPos;

                    if (dotPos < grammar[ruleIndex].rhs.length()) {
                        char symbol = grammar[ruleIndex].rhs[dotPos];
                        lookaheadSymbols.insert(symbol);
                    }
                }

                for (char symbol : lookaheadSymbols) {
                    unordered_set<Item, ItemHash> newItemSet;

                    for (const Item& item : itemSet) {
                        int ruleIndex = item.ruleIndex;
                        int dotPos = item.dotPos;

                        if (dotPos < grammar[ruleIndex].rhs.length()) {
                            char nextSymbol = grammar[ruleIndex].rhs[dotPos];

                            if (nextSymbol == symbol) {
                                Item newItem{ruleIndex, dotPos + 1};
                                newItemSet.insert(newItem);
                            }
                        }
                    }

                    if (!newItemSet.empty() && itemSets[i].count(*newItemSet.begin()) == 0) {
                        itemSets[i].insert(newItemSet.begin(), newItemSet.end());
                        updated = true;
                    }
                }
            }
        } while (updated);
    }

    void calculateCanonicalLR1Items(vector<unordered_set<Item, ItemHash>>& canonicalItemSets) {
        vector<unordered_set<Item, ItemHash>> itemSets;
        calculateLR0Items(itemSets);

        for (const unordered_set<Item, ItemHash>& itemSet : itemSets) {
            unordered_map<char, unordered_set<char>> lookaheadSets;
            for (const Item& item : itemSet) {
                int ruleIndex = item.ruleIndex;
                int dotPos = item.dotPos;

                if (dotPos < grammar[ruleIndex].rhs.length()) {
                    char symbol = grammar[ruleIndex].rhs[dotPos];
                    char lookaheadSymbol = grammar[ruleIndex].rhs[dotPos + 1];

                    unordered_set<char> lookaheadSet;
                    if (lookaheadSets.count(symbol) > 0) {
                        lookaheadSet = lookaheadSets[symbol];
                    }

                    if (!isNonTerminal(lookaheadSymbol)) {
                        lookaheadSet.insert(lookaheadSymbol);
                    } else {
                        lookaheadSet.insert(firstSets[lookaheadSymbol].begin(), firstSets[lookaheadSymbol].end());
                        lookaheadSet.erase('e');  // Remove epsilon
                    }

                    lookaheadSets[symbol] = lookaheadSet;
                }
            }

            for (const auto& lookaheadSet : lookaheadSets) {
                char symbol = lookaheadSet.first;
                const unordered_set<char>& lookahead = lookaheadSet.second;

                for (char lookaheadSymbol : lookahead) {
                    unordered_set<Item, ItemHash> canonicalItemSet;

                    for (const Item& item : itemSet) {
                        int ruleIndex = item.ruleIndex;
                        int dotPos = item.dotPos;

                        if (dotPos < grammar[ruleIndex].rhs.length()) {
                            char nextSymbol = grammar[ruleIndex].rhs[dotPos];

                            if (nextSymbol == symbol) {
                                Item canonicalItem{ruleIndex, dotPos + 1};
                                canonicalItemSet.insert(canonicalItem);
                            }
                        }
                    }

                    if (!canonicalItemSet.empty() && canonicalItemSets[i].count(*canonicalItemSet.begin()) == 0) {
                        canonicalItemSets[i].insert(canonicalItemSet.begin(), canonicalItemSet.end());
                    }
                }
            }
        }
    }

    void constructActionTable(const vector<unordered_set<Item, ItemHash>>& canonicalItemSets) {
        for (size_t i = 0; i < canonicalItemSets.size(); i++) {
            const unordered_set<Item, ItemHash>& canonicalItemSet = canonicalItemSets[i];

            for (const Item& item : canonicalItemSet) {
                int ruleIndex = item.ruleIndex;
                int dotPos = item.dotPos;

                if (dotPos == grammar[ruleIndex].rhs.length()) {
                    char symbol = grammar[ruleIndex].lhs;

                    if (symbol == grammar[0].lhs) {
                        actionTable[i]['$'] = 0;  // Accept
                    } else {
                        for (char lookaheadSymbol : followSets[symbol]) {
                            actionTable[i][lookaheadSymbol] = ruleIndex;
                        }
                    }
                }
            }

            for (const Item& item : canonicalItemSet) {
                int ruleIndex = item.ruleIndex;
                int dotPos = item.dotPos;

                if (dotPos < grammar[ruleIndex].rhs.length()) {
                    char symbol = grammar[ruleIndex].rhs[dotPos];

                    if (isNonTerminal(symbol)) {
                        unordered_set<Item, ItemHash> nextItemSet;

                        for (const Item& nextItem : canonicalItemSet) {
                            int nextRuleIndex = nextItem.ruleIndex;
                            int nextDotPos = nextItem.dotPos;

                            if (nextDotPos < grammar[nextRuleIndex].rhs.length() && grammar[nextRuleIndex].rhs[nextDotPos] == symbol) {
                                Item nextItem{nextRuleIndex, nextDotPos + 1};
                                nextItemSet.insert(nextItem);
                            }
                        }

                        int nextState = findItemSetIndex(canonicalItemSets, nextItemSet);
                        gotoTable[i][symbol] = nextState;
                    }
                }
            }
        }
    }

    int findItemSetIndex(const vector<unordered_set<Item, ItemHash>>& itemSets, const unordered_set<Item, ItemHash>& itemSet) {
        for (size_t i = 0; i < itemSets.size(); i++) {
            if (itemSets[i] == itemSet) {
                return i;
            }
        }

        return -1;
    }

    bool parse(string input) {
        input += '$';  // Append end-of-input marker

        parseStack.push(0);  // Initial state

        size_t inputIndex = 0;
        while (true) {
            int currentState = parseStack.top();
            char currentSymbol = input[inputIndex];

            int action = actionTable[currentState][currentSymbol];

            if (action == 0) {
                cout << "Input successfully parsed!" << endl;
                return true;
            } else if (action > 0) {
                const Rule& rule = grammar[action];
                int numPopSymbols = grammar[rule.lhs].rhs.length();

                for (int i = 0; i < numPopSymbols; i++) {
                    parseStack.pop();
                }

                int nextState = gotoTable[parseStack.top()][rule.lhs];
                parseStack.push(nextState);

                cout << rule.lhs << " -> " << rule.rhs << endl;
            } else {
                cout << "Error: Parsing failed at symbol '" << currentSymbol << "'" << endl;
                return false;
            }

            if (currentSymbol != '$') {
                parseStack.push(inputIndex + 1);
            }

            inputIndex++;
        }
    }

    bool isNonTerminal(char symbol) {
        return symbol >= 'A' && symbol <= 'Z';
    }

    bool isNullable(char symbol) {
        return symbol == 'e';
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
        {'F', "id"}
    };

    // Create an instance of the SLR parser
    SLRParser parser(grammar);

    // Calculate the first sets
    parser.calculateFirstSets();

    // Calculate the follow sets
    parser.calculateFollowSets();

    // Calculate the canonical LR(1) item sets
    vector<unordered_set<Item, ItemHash>> canonicalItemSets;
    parser.calculateCanonicalLR1Items(canonicalItemSets);

    // Construct the action and goto tables
    parser.constructActionTable(canonicalItemSets);

    // Parse an input
    parser.parse("id+id*id");

    return 0;
}
