#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cstdlib>
#include <climits>
#include <limits>
#include <cctype>


bool safe_add(int a, int b, int& result)
{
    if ((b > 0) && (a > std::numeric_limits<int>::max() - b))
        return false;
    if ((b < 0) && (a < std::numeric_limits<int>::min() - b))
        return false;
    result = a + b;
    return true;
}


bool safe_subtract(int a, int b, int& result) {
    if ((b < 0) && (a > std::numeric_limits<int>::max() + b))
        return false;
    if ((b > 0) && (a < std::numeric_limits<int>::min() + b))
        return false;
    result = a - b;
    return true;
}

bool safe_multiply(int a, int b, int& result) {
    if (a == 0 || b == 0)
    {
        result = 0;
        return true;
    }
    if (a == -1 && b == std::numeric_limits<int>::min())
        return false;
    if (b == -1 && a == std::numeric_limits<int>::min())
        return false;

    if (a > 0)
    {
        if (b > 0)
        {
            if (a > std::numeric_limits<int>::max() / b)
                return false;
        }
        else
        {
            if (b < std::numeric_limits<int>::min() / a) return false;
        }
    } 
    else
    {
        if (b > 0)
        {
            if (a < std::numeric_limits<int>::min() / b)
                return false;
        }
        else
        {
            if (a != 0 && b < std::numeric_limits<int>::max() / a) return false;
        }
    }

    result = a * b;
    return true;
}

bool safe_divide(int a, int b, int& result) {
    if (b == 0)
    {
        return false;
    }
    if (a == std::numeric_limits<int>::min() && b == -1)
    {
        return false;
    }
    result = a / b;
    return true;
}

bool is_valid_input(const std::string& input)
{
    if(input.empty())
    {
        return false;
    }
    for (size_t i = 0; i < input.size(); ++i)
    {
        if (!std::isdigit(input[i]))
        {
            return false;
        }
    }
    char* endptr;
    long value = std::strtol(input.c_str(), &endptr, 10);

    if (*endptr != '\0')
    {
        return false;
    }

    if (value < 0 || value > INT_MAX)
    {
        return false;
    }

    return true;
}

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
            {
                if (!safe_add(operand1, operand2, operationResult))
                {
                    std::cout << "Error: Overflow." << std::endl;
                    return 1;
                }
            }
            else if (token == "-")
            {
                if (!safe_subtract(operand1, operand2, operationResult))
                {
                    std::cout << "Error: Overflow." << std::endl;
                    return 1;
                }
            }
            else if (token == "*")
            {
                if (!safe_multiply(operand1, operand2, operationResult))
                {
                    std::cout << "Error: Overflow." << std::endl;
                    return 1;
                }
            }
            else if (token == "/") {
                if (operand2 == 0) {
                    std::cout << "Error: Division by zero." << std::endl;
                    return 1;
                }
                if (!safe_divide(operand1, operand2, operationResult))
                {
                    std::cout << "Error: Overflow." << std::endl;
                    return 1;
                }
            }
            operandStack.push(operationResult);
        } else {
            if (!is_valid_input(token))
            {
                std::cout << "Error: bad input." << std::endl;
                return 1;
            }
            int num = atoi(token.c_str());
            operandStack.push(num);
        }
    }

    if (operandStack.size() != 1) {
        std::cout << "Error: Invalid input expression." << std::endl;
        return 1;
    }

    std::cout << operandStack.top() << std::endl;
    return 0;
}