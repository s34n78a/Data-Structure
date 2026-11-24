#include <iostream>
#include <functional>
#include <queue>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int operationCount;
    std::cin >> operationCount;

    // lower stores the smaller half as a max-heap.
    std::priority_queue<int> lower;

    // upper stores the larger half as a min-heap.
    std::priority_queue<int, std::vector<int>, std::greater<int>> upper;

    for (int i = 0; i < operationCount; ++i) {
        char firstCharacter;
        std::cin >> firstCharacter;

        if (firstCharacter == 'm') {
            if (std::cin.peek() == 'e') {
                std::cin.ignore(2); // Consume "ed" after 'm'.
            }

            if (lower.size() == upper.size()) {
                // Even number of RTTs: average the two middle values.
                long long sum = static_cast<long long>(lower.top()) + upper.top();
                std::cout << sum / 2 << '\n';
            } else {
                // Odd number of RTTs: lower contains the median.
                std::cout << lower.top() << '\n';
            }
        } else {
            std::cin.putback(firstCharacter);

            int rtt;
            std::cin >> rtt;

            if (lower.empty() || rtt <= lower.top()) {
                lower.push(rtt);
            } else {
                upper.push(rtt);
            }

            // Keep lower equal in size or exactly one larger.
            if (lower.size() < upper.size()) {
                lower.push(upper.top());
                upper.pop();
            } else if (lower.size() > upper.size() + 1) {
                upper.push(lower.top());
                lower.pop();
            }
        }
    }

    return 0;
}
