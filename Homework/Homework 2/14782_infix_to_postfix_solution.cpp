#include <cctype>
#include <iostream>
#include <limits>
#include <stack>
#include <string>

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }

    return 2;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int expressionCount;
    std::cin >> expressionCount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int expressionIndex = 0; expressionIndex < expressionCount; ++expressionIndex) {
        std::string infix;
        std::getline(std::cin, infix);

        std::string postfix;
        postfix.reserve(infix.size() * 2);
        std::stack<char> operators;

        auto appendToken = [&postfix](const std::string& token) {
            if (!postfix.empty()) {
                postfix += ' ';
            }
            postfix += token;
        };

        auto appendOperator = [&appendToken](char op) {
            appendToken(std::string(1, op));
        };

        std::size_t position = 0;
        while (position < infix.size()) {
            const char current = infix[position];

            if (std::isdigit(static_cast<unsigned char>(current))) {
                const std::size_t numberStart = position;

                while (position < infix.size() &&
                       std::isdigit(static_cast<unsigned char>(infix[position]))) {
                    ++position;
                }

                appendToken(infix.substr(numberStart, position - numberStart));
            } else if (current == '(') {
                operators.push(current);
                ++position;
            } else if (current == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    appendOperator(operators.top());
                    operators.pop();
                }

                operators.pop();
                ++position;
            } else {
                while (!operators.empty() && operators.top() != '(' &&
                       precedence(operators.top()) >= precedence(current)) {
                    appendOperator(operators.top());
                    operators.pop();
                }

                operators.push(current);
                ++position;
            }
        }

        while (!operators.empty()) {
            appendOperator(operators.top());
            operators.pop();
        }

        std::cout << postfix << '\n';
    }

    return 0;
}
