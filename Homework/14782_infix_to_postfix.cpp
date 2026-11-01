#include <iostream>
#include <stack>

int main() {
    std::stack<char> operators;
    std::string infix = "7-12/14";
    std::string postfix = "";

    for (char c : infix) {
        if (std::isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop(); // Remove the '('
            }
        } else {
            while (!operators.empty() && operators.top() != '(' && 
                   (c == '+' || c == '-' || c == '*' || c == '/')) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    std::cout << "Infix: " << infix << std::endl;
    std::cout << "Postfix: " << postfix << std::endl;

    return 0;
}