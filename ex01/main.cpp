#include <iostream>
#include <stack>
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "ERROR: Invalid number of inputs." << std::endl;
        return 1;
    }

    std::stack<int> operandStack;
    std::istringstream inputExpression(argv[1]);

    std::string token;
    while (inputExpression >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (operandStack.size() < 2) {
                std::cout << "Error: Insufficient operands for operator " << token << "." << std::endl;
                return 1;
            }
            int operand2 = operandStack.top();
            operandStack.pop();
            int operand1 = operandStack.top();
            operandStack.pop();
            int operationResult;

            if (token == "+")
                operationResult = operand1 + operand2;
            else if (token == "-")
                operationResult = operand1 - operand2;
            else if (token == "*")
                operationResult = operand1 * operand2;
            else if (token == "/") {
                if (operand2 == 0) {
                    std::cout << "Error: Division by zero." << std::endl;
                    return 1;
                }
                operationResult = operand1 / operand2;
            }

            operandStack.push(operationResult);
        } else {
            try {
                int number = std::stoi(token);
                operandStack.push(number);
            } catch (const std::invalid_argument &) {
                std::cerr << "Error: Invalid token '" << token << "' in expression." << std::endl;
                return 1;
            } catch (const std::out_of_range &) {
                std::cerr << "Error: Number out of range in token '" << token << "'." << std::endl;
                return 1;
            }
        }
    }

    if (operandStack.size() != 1) {
        std::cout << "Error: Invalid input expression." << std::endl;
        return 1;
    }

    std::cout << operandStack.top() << std::endl;
    return 0;
}
