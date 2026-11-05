#include <cctype>
#include <iostream>
#include <string>

class Parser {
public:
    explicit Parser(const std::string& expression)
        : expression_(expression), position_(0), valid_(true) {}

    bool parse(long long& result) {
        result = parseExpression();
        return valid_ && position_ == expression_.size();
    }

private:
    long long parseExpression() {
        long long result = parseTerm();

        while (valid_ && position_ < expression_.size()) {
            const char operation = expression_[position_];
            if (operation != '+' && operation != '-') {
                break;
            }

            ++position_;
            const long long right = parseTerm();
            if (operation == '+') {
                result += right;
            } else {
                result -= right;
            }
        }

        return result;
    }

    long long parseTerm() {
        long long result = parseFactor();

        while (valid_ && position_ < expression_.size()) {
            const char operation = expression_[position_];
            if (operation != '*' && operation != '/') {
                break;
            }

            ++position_;
            const long long right = parseFactor();
            if (operation == '*') {
                result *= right;
            } else {
                result /= right;
            }
        }

        return result;
    }

    long long parseFactor() {
        if (position_ >= expression_.size()) {
            valid_ = false;
            return 0;
        }

        if (expression_[position_] == '-') {
            ++position_;
            if (position_ >= expression_.size() ||
                !std::isdigit(static_cast<unsigned char>(expression_[position_]))) {
                valid_ = false;
                return 0;
            }
            return -parseInteger();
        }

        if (std::isdigit(static_cast<unsigned char>(expression_[position_]))) {
            return parseInteger();
        }

        if (expression_[position_] == '(') {
            ++position_;
            const long long result = parseExpression();
            if (!valid_ || position_ >= expression_.size() ||
                expression_[position_] != ')') {
                valid_ = false;
                return 0;
            }
            ++position_;
            return result;
        }

        valid_ = false;
        return 0;
    }

    long long parseInteger() {
        long long value = 0;
        while (position_ < expression_.size() &&
               std::isdigit(static_cast<unsigned char>(expression_[position_]))) {
            value = value * 10 + (expression_[position_] - '0');
            ++position_;
        }
        return value;
    }

    const std::string& expression_;
    std::size_t position_;
    bool valid_;
};

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

        Parser parser(expression);
        long long result = 0;
        if (parser.parse(result)) {
            std::cout << result << '\n';
        } else {
            std::cout << "bad expression\n";
        }
    }

    return 0;
}
