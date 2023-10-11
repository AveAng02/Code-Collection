#include <iostream>
#include <stack>
#include <string>


std::string trimSpace(std::string str)
{
    if(str.length() == 1 && str[0] != ' ')
        return str;

    std::string newStr = "";

    for(int i = 0; i < str.length(); i++)
        if(str[i] != ' ' && str[i] != 13)
            newStr += str[i];

    return newStr;
}

int calculateExpression(const std::string& expression) {
    std::stack<int> operands;
    std::stack<char> operators;

    int operand = 0;

    for (int i = 0; i < expression.length(); i++) {
        char currentChar = expression[i];

        if (isdigit(currentChar)) {
            operand = (operand * 10) + (currentChar - '0');
            // operands.push(operand);
        } else if (currentChar == '+' || currentChar == '*') {

            // reset operand
            operands.push(operand);
            std::cout << "New Operand = " << operand << std::endl;
            operand = 0;

            while (!operators.empty() && operators.top() == '*') {
                int operand2 = operands.top();
                operands.pop();
                int operand1 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();

                if (op == '*') {
                    std::cout << "Operands at hand : " << operand1 << "    " << operand2 << std::endl;
                    std::cout << "Operation at hand : " << op << std::endl; 
                    int result = operand1 * operand2;
                    operands.push(result);
                }
            }
            operators.push(currentChar);
        }
    }

    operands.push(operand);

    while (!operators.empty()) {
        int operand2 = operands.top();
        operands.pop();
        int operand1 = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();

        std::cout << "Operands at hand : " << operand1 << "    " << operand2 << std::endl;
        std::cout << "Operation at hand : " << op << std::endl;

        if (op == '+') {
            int result = operand1 + operand2;
            operands.push(result);
            std::cout << "Result : " << result << std::endl;
        } else if (op == '*') {
            int result = operand1 * operand2;
            operands.push(result);
            std::cout << "Result : " << result << std::endl;
        }
    }

    return operands.top();
}

int main() {
    std::string expression;
    std::cout << "Enter an expression: ";
    std::cin >> expression;

    int result = calculateExpression(expression);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
