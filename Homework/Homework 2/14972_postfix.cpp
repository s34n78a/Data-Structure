#include <iostream>
#include <stack>
#include <sstream>
#include <string>

bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int main() {
    int m;
    std::cin >> m;
    std::cin.ignore();

    for (int i = 0; i < m; ++i) {
        std::string expression;
        std::getline(std::cin, expression);

        std::istringstream tokens(expression);
        std::stack<long long> values;
        bool valid = true;
        std::string token;

        while (tokens >> token && valid) {
            if (!isOperator(token)) {
                try {
                    std::size_t parsedLength = 0;
                    long long value = std::stoll(token, &parsedLength);

                    if (parsedLength != token.length()) {
                        valid = false;
                    } else {
                        values.push(value);
                    }
                } catch (const std::invalid_argument&) {
                    valid = false;
                } catch (const std::out_of_range&) {
                    valid = false;
                }
                continue;
            }

            if (values.size() < 2) {
                valid = false;
                continue;
            }

            long long right = values.top();
            values.pop();
            long long left = values.top();
            values.pop();

            if (token == "+") {
                values.push(left + right);
            } else if (token == "-") {
                values.push(left - right);
            } else if (token == "*") {
                values.push(left * right);
            } else {
                values.push(left / right);
            }
        }

        if (!valid || values.size() != 1) {
            std::cout << "bad expression\n";
        } else {
            std::cout << values.top() << '\n';
        }
    }
}