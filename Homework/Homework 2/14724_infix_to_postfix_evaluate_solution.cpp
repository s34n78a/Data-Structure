#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int precedence(const std::string& operation) {
    return (operation == "+" || operation == "-") ? 1 : 2;
}

bool convertToPostfix(const std::string& expression,
                      std::vector<std::string>& postfix) {
    std::stack<std::string> operators;
    bool expectOperand = true;
    std::size_t position = 0;

    while (position < expression.size()) {
        const char current = expression[position];

        if (expectOperand) {
            if (std::isdigit(static_cast<unsigned char>(current))) {
                const std::size_t start = position;
                while (position < expression.size() &&
                       std::isdigit(static_cast<unsigned char>(expression[position]))) {
                    ++position;
                }
                postfix.push_back(expression.substr(start, position - start));
                expectOperand = false;
            } else if (current == '-' && position + 1 < expression.size() &&
                       std::isdigit(static_cast<unsigned char>(expression[position + 1]))) {
                const std::size_t start = position++;
                while (position < expression.size() &&
                       std::isdigit(static_cast<unsigned char>(expression[position]))) {
                    ++position;
                }
                postfix.push_back(expression.substr(start, position - start));
                expectOperand = false;
            } else if (current == '(') {
                operators.push("(");
                ++position;
            } else {
                return false;
            }
        } else if (current == ')') {
            bool foundOpeningParenthesis = false;
            while (!operators.empty()) {
                if (operators.top() == "(") {
                    foundOpeningParenthesis = true;
                    operators.pop();
                    break;
                }
                postfix.push_back(operators.top());
                operators.pop();
            }
            if (!foundOpeningParenthesis) {
                return false;
            }
            ++position;
        } else if (isOperator(std::string(1, current))) {
            const std::string operation(1, current);
            while (!operators.empty() && operators.top() != "(" &&
                   precedence(operators.top()) >= precedence(operation)) {
                postfix.push_back(operators.top());
                operators.pop();
            }
            operators.push(operation);
            ++position;
            expectOperand = true;
        } else {
            return false;
        }
    }

    if (expectOperand) {
        return false;
    }

    while (!operators.empty()) {
        if (operators.top() == "(") {
            return false;
        }
        postfix.push_back(operators.top());
        operators.pop();
    }
    return true;
}

bool evaluatePostfix(const std::vector<std::string>& postfix, long long& result) {
    std::stack<long long> values;

    for (const std::string& token : postfix) {
        if (!isOperator(token)) {
            long long value = 0;
            bool negative = !token.empty() && token[0] == '-';
            const std::size_t firstDigit = negative ? 1 : 0;
            if (firstDigit == token.size()) {
                return false;
            }
            for (std::size_t i = firstDigit; i < token.size(); ++i) {
                if (!std::isdigit(static_cast<unsigned char>(token[i]))) {
                    return false;
                }
                value = value * 10 + (token[i] - '0');
            }
            values.push(negative ? -value : value);
            continue;
        }

        if (values.size() < 2) {
            return false;
        }
        const long long right = values.top();
        values.pop();
        const long long left = values.top();
        values.pop();

        if (token == "+") {
            values.push(left + right);
        } else if (token == "-") {
            values.push(left - right);
        } else if (token == "*") {
            values.push(left * right);
        } else {
            if (right == 0) {
                return false;
            }
            values.push(left / right);
        }
    }

    if (values.size() != 1) {
        return false;
    }
    result = values.top();
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int expressionCount;
    std::cin >> expressionCount;
    std::string expression;
    std::getline(std::cin, expression);

    for (int i = 0; i < expressionCount; ++i) {
        std::getline(std::cin, expression);
        if (!expression.empty() && expression.back() == '\r') {
            expression.pop_back();
        }

        std::vector<std::string> postfix;
        long long result = 0;
        if (convertToPostfix(expression, postfix) &&
            evaluatePostfix(postfix, result)) {
            std::cout << result << '\n';
        } else {
            std::cout << "bad expression\n";
        }
    }

    return 0;
}