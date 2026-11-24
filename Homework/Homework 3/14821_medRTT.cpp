#include <iostream>
#include <string>
#include <functional>
#include <queue>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int m;
    std::cin >> m;

    std::priority_queue<int> lower; // lower half of max-heap
    std::priority_queue<int, std::vector<int>, std::greater<int>> upper; // upper half of min-heap

    for (int i = 0; i < m; i++)
    {
        char firstChar;
        std::cin >> firstChar; 
        // either m from med or numbers

        if (firstChar == 'm')
        {
            std::cin.ignore(2); // buang ed

            if (lower.size() == upper.size()) // even num of rtt --> med = avg
            {
                long long sum = lower.top() + upper.top();
                std::cout << sum / 2 << '\n';
            }
            else // odd num of rtt --> med = lower top
            {
                std::cout << lower.top() << '\n';
            }
            
        }
        else // push num to heap
        {
            std::cin.putback(firstChar); // return first digit of num to be read

            int rtt;
            std::cin >> rtt;

            if (lower.empty() || rtt <= lower.top())
            {
                lower.push(rtt);
            }
            else
            {
                upper.push(rtt);
            }
            
            // keep lower size equal or exactly one larger than upper
            if (lower.size() < upper.size())
            {
                lower.push(upper.top());
                upper.pop();
            }
            else if (lower.size() > upper.size() + 1)
            {
                upper.push(lower.top());
                lower.pop();
            }
        }
    }
    return 0;
}