#include <cstdio>
#include <functional>
#include <queue>
#include <vector>

class FastInput {
private:
    static constexpr std::size_t bufferSize = 1 << 20;
    char buffer[bufferSize];
    std::size_t position = 0;
    std::size_t length = 0;

    char getChar() {
        if (position == length) {
            length = std::fread(buffer, 1, bufferSize, stdin);
            position = 0;
            if (length == 0) {
                return '\0';
            }
        }
        return buffer[position++];
    }

public:
    int readInt() {
        char ch = getChar();
        while (ch <= ' ') {
            ch = getChar();
        }

        int value = 0;
        while (ch >= '0' && ch <= '9') {
            value = value * 10 + (ch - '0');
            ch = getChar();
        }
        return value;
    }

    bool readCommand(int& value) {
        char ch = getChar();
        while (ch <= ' ') {
            ch = getChar();
        }

        if (ch == 'm') {
            while (ch > ' ') {
                ch = getChar();
            }
            return true;
        }

        value = 0;
        while (ch >= '0' && ch <= '9') {
            value = value * 10 + (ch - '0');
            ch = getChar();
        }
        return false;
    }
};

class FastOutput {
private:
    static constexpr std::size_t bufferSize = 1 << 20;
    char buffer[bufferSize];
    std::size_t position = 0;

public:
    ~FastOutput() {
        flush();
    }

    void writeInt(long long value) {
        char digits[24];
        int count = 0;

        do {
            digits[count++] = static_cast<char>('0' + value % 10);
            value /= 10;
        } while (value > 0);

        if (position + count + 1 > bufferSize) {
            flush();
        }

        while (count > 0) {
            buffer[position++] = digits[--count];
        }
        buffer[position++] = '\n';
    }

    void flush() {
        if (position > 0) {
            std::fwrite(buffer, 1, position, stdout);
            position = 0;
        }
    }
};

int main() {
    FastInput input;
    FastOutput output;
    const int m = input.readInt();

    // The max-heap stores the smaller half of the RTTs.
    std::priority_queue<int> lower;

    // The min-heap stores the larger half of the RTTs.
    std::priority_queue<int, std::vector<int>, std::greater<int>> upper;

    for (int i = 0; i < m; ++i) {
        int rtt;
        if (input.readCommand(rtt)) {
            if (lower.size() == upper.size()) {
                const long long sum =
                    static_cast<long long>(lower.top()) + upper.top();
                output.writeInt(sum / 2);
            } else {
                output.writeInt(lower.top());
            }
            continue;
        }

        if (lower.empty() || rtt <= lower.top()) {
            lower.push(rtt);
        } else {
            upper.push(rtt);
        }

        // Keep lower the same size as upper, or one element larger.
        if (lower.size() < upper.size()) {
            lower.push(upper.top());
            upper.pop();
        } else if (lower.size() > upper.size() + 1) {
            upper.push(lower.top());
            lower.pop();
        }
    }

    return 0;
}
