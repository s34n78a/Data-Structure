#include <iostream>
#include <sstream> // buat istringstream yg bisa baca string token by token
#include <stack>
#include <string>

int main() {
    int m;
    std::cin >> m;
    std::cin.ignore(); // karena setelah baca m, ada \n

    for (int i = 0; i < m; ++i) {
        std::string expression;
        std::getline(std::cin, expression);

        std::istringstream tokens(expression);
        std::stack<long long> values;
        std::string token;
        bool valid = true;

        while (tokens >> token && valid) { // >> baca token by token, misal "1 2 + 3 *" akan dibaca jadi "1", "2", "+", "3", "*"
            // TODO:
            // 1. Decide whether token is an integer or an operator.
            // 2. Push integers onto values.
            // 3. For an operator, pop the right and left operands.
            // 4. Calculate the result and push it back.

            if (token == "+" || token == "-" || token == "*" || token == "/")
            {
                if (values.size() < 2) // kalau hanya ada 1 operand, tidak bisa dihitung
                {
                    valid = false;
                    continue;
                }
                
                long long right = values.top();
                values.pop();
                long long left = values.top();
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
                try // catch untuk handle error ketika token bukan integer
                {
                    std::size_t parsedlength = 0; // size_t karena panjangnya bisa beda-beda
                    long long value = std::stoll(token, &parsedlength); // stoll = string to long long, &parsedlength = buat ngitung brp karakter yg berhasil di parse jadi integer

                    if (parsedlength != token.length()) // misal token = "12abc", parsedlength = 2, token.length() = 5, berarti ada karakter yg tidak bisa di parse jadi integer, maka valid = false
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
                }
            }
            
        }

        // TODO:
        // The expression is valid only when valid is true and
        // exactly one value remains in values.

        if (valid == false || values.size() != 1)
        {
            std::cout << "bad expression\n";
        }
        else
        {
            std::cout << values.top() << "\n";
            values.pop();
        }
        
    }
}
