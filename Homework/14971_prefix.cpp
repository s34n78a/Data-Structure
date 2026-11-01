#include <iostream>
#include <sstream>
#include <stack>
#include <string>

int main() {
    int m;
    std::cin >> m;
    std::cin.ignore();

    for (int i = 0; i < m; i++)
    {
        std::string expression;
        std::getline(std::cin, expression);
        
        std::istringstream tokens(expression);
        std::stack<std::string> reversedTokens;
        std::stack<long long> values;
        std::string token;
        bool valid = true;
        
        while (tokens >> token)
        {
            reversedTokens.push(token);
        }
        
        while (!reversedTokens.empty() && valid)
        {
            token = reversedTokens.top();
            reversedTokens.pop();

            if (token == "+" || token == "-" || token == "*" || token == "/")
            {
                if (values.size() < 2)
                {
                    valid = false;
                    continue;
                }
                
                long long left = values.top(); 
                values.pop();

                long long right = values.top(); 
                values.pop();

                if (token == "+")
                {
                    values.push(left + right);
                }
                else if (token == "-")
                {
                    values.push(left - right);
                }
                else if (token == "*")
                {
                    values.push(left * right);
                }
                else
                {
                    values.push(left / right);
                }
            }
            else
            {
                try
                {
                    std::size_t parsedLength = 0;

                    long long value = std::stoll(token, &parsedLength);

                    if (token.length() != parsedLength)
                    {
                        valid = false;
                    }
                    else
                    {
                        values.push(value);
                    }
                }
                catch(const std::exception& e)
                {
                    valid = false;
                    continue;
                }
            }
        }

        if (valid && values.size() == 1)
        {
            std::cout << values.top() << "\n";
            values.pop();
        }
        else
        {
            std::cout << "bad expression\n";
        }
    }
}