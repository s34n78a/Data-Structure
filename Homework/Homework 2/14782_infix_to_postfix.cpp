#include <iostream>
#include <stack>
#include <string>

int precedence (char op) {
    if (op == '-' || op == '+')
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int main() {
    int m;
    std::cin >> m;
        std::cin.ignore();

    for (int i = 0; i < m; i++)
    {
        std::stack<char> operators;
        std::string infix;
        std::string postfix = "";

        std::getline(std::cin, infix);

        for (long long i = 0; i < infix.size(); i++) {
            
            char c = infix[i];
            if (std::isalnum(c)) {
                if (postfix != "")
                {
                    postfix += " ";
                }

                while (std::isalnum(infix[i]) && i < infix.size()) {
                    c = infix[i];
                    postfix += c;
                    i++;
                }
                i--; // Adjust index since we read one character too far
            } else if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                if (postfix != "")
                {
                    postfix += " ";
                }

                while (!operators.empty() && operators.top() != '(') {
                    postfix += operators.top();
                    operators.pop();
                }
                if (!operators.empty()) {
                    operators.pop(); // Remove the '('
                }
            } else {
                while (!operators.empty() && operators.top() != '(' && precedence(operators.top()) >= precedence(c)) {
                    if (postfix != "")
                    {
                        postfix += " ";
                    }
                    postfix += operators.top();
                    operators.pop();
                }
                operators.push(c);
            }
        }

        while (!operators.empty() && operators.top() != '(') {
            if (postfix != "")
            {
                postfix += " ";
            }

            postfix += operators.top();
            operators.pop();
        }

        std::cout << postfix << std::endl;
    }
    

    return 0;
}