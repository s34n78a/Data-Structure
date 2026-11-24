#include <iostream>
#include <stack>
#include <string>

int precedence (char checkOp) {
    if (checkOp == '-' || checkOp == '+')
    {
        return 1;
    }
    else
    {
        return 2;
    }    
}

int main() {
    long long m;
    std::cin >> m ;
    std::cin.ignore();

    for (long long i = 0; i < m; i++)
    {
        std::string expression = "";
        std::stack<long long> values;
        std::stack<char> op;
        long long openBracketCount = 0;
        bool valid = true;
        bool hasBracket = false;
        bool prevOp = false;
        bool negative = false;

        std::getline(std::cin, expression);

        for (long long i = 0; i < expression.size() && valid; i++)
        {
            char c = expression[i];
            

            std::cout << "i: " << i << " c: " << c << " valid: " << valid << " values: " << values.size() << " op: " << op.size() << '\n';

            std::string next;
            std::cin >> next;

            if (std::isalnum(c))
            {
                prevOp = false;
                std::string value;
                
                while (std::isalnum(c) && i < expression.size())
                {
                    c = expression[i];
                    value += c;
                    i++;
                }
                i = i - 2;

                std::cout << "i: " << i << " c: " << c << " valid: " << valid << " values: " << values.size() << " op: " << op.size() << '\n';


                if (negative)
                {
                    values.push(-1 * std::stoll(value));
                    negative = false;
                }
                else
                {
                    values.push(std::stoll(value));
                }
                
                while (!op.empty() && op.top() != '(' && valid)
                {
                    if (values.size() < 2)
                    {
                        valid = false;
                    }
                    
                    long long right = values.top();
                    values.pop();
                    long long left = values.top();
                    values.pop();

                    if (op.top() == '+')
                    {
                        values.push(left + right);
                    }
                    else if (op.top() == '-')
                    {
                        values.push(left - right);
                    }
                    else if (op.top() == '*')
                    {
                        values.push(left * right);
                    }
                    else
                    {
                        values.push(left / right);
                    }
                    op.pop();
                }
                
            }
            else if (c == '(')
            {
                op.push(c);
                openBracketCount++;
                hasBracket = true;
                prevOp = false;
            }
            else if (c == ')')
            {
                prevOp = false;

                if (openBracketCount <= 0 && hasBracket)
                {
                    valid = false;
                }
                else
                {
                    if (!op.empty() && op.top() == '(')
                    {
                        op.pop();
                        openBracketCount--;
                    }
                    else
                    {
                        valid = false;
                    }
                }
            }
            else
            {
                if (prevOp && c=='-' && !negative)
                {
                    negative = true;
                    prevOp = false;
                }
                else if (!prevOp && c=='-' && negative)
                {
                    negative = false;
                    prevOp = true;
                }
                else
                {
                    prevOp = true;
                    op.push(c);
                }
            }

            std::cout << "i: " << i << " c: " << c << " valid: " << valid << " values: " << values.size() << " op: " << op.size() << '\n'<< '\n';
            
        }
        
        if (valid && values.size() == 1)
        {
            std::cout << values.top() << '\n';
            values.pop();
        }
        else
        {
            std::cout << "bad exppression\n";
            std::cout << values.size() << '\n';
        }
        
    }
    
}