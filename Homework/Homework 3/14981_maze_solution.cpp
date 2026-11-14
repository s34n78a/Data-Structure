#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
    int value;
    int left;
    int right;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int mazeCount;
    std::cin >> mazeCount;

    while (mazeCount--) {
        int nodeCount;
        std::string command;
        std::cin >> nodeCount >> command;

        if (command != "PRE" && command != "IN" && command != "POST") {
            for (int i = 0; i < nodeCount; ++i) {
                int value, left, right;
                std::cin >> value >> left >> right;
            }

            std::cout << "Invalid command\n";
            continue;
        }

        std::vector<int> values(nodeCount);
        std::vector<int> leftValues(nodeCount);
        std::vector<int> rightValues(nodeCount);
        std::unordered_map<int, int> indexOf;
        indexOf.reserve(static_cast<std::size_t>(nodeCount) * 2);

        for (int i = 0; i < nodeCount; ++i) {
            std::cin >> values[i] >> leftValues[i] >> rightValues[i];
            indexOf[values[i]] = i;
        }

        std::vector<Node> nodes(nodeCount);
        for (int i = 0; i < nodeCount; ++i) {
            nodes[i] = {values[i], -1, -1};

            if (leftValues[i] != -1) {
                nodes[i].left = indexOf[leftValues[i]];
            }
            if (rightValues[i] != -1) {
                nodes[i].right = indexOf[rightValues[i]];
            }
        }

        std::vector<int> traversal;
        traversal.reserve(nodeCount);
        std::vector<int> stack;
        stack.reserve(nodeCount);

        const int root = 0;

        if (command == "PRE") {
            stack.push_back(root);

            while (!stack.empty()) {
                int current = stack.back();
                stack.pop_back();
                traversal.push_back(nodes[current].value);

                if (nodes[current].right != -1) {
                    stack.push_back(nodes[current].right);
                }
                if (nodes[current].left != -1) {
                    stack.push_back(nodes[current].left);
                }
            }
        } else if (command == "IN") {
            int current = root;

            while (current != -1 || !stack.empty()) {
                while (current != -1) {
                    stack.push_back(current);
                    current = nodes[current].left;
                }

                current = stack.back();
                stack.pop_back();
                traversal.push_back(nodes[current].value);
                current = nodes[current].right;
            }
        } else {
            stack.push_back(root);

            while (!stack.empty()) {
                int current = stack.back();
                stack.pop_back();
                traversal.push_back(nodes[current].value);

                if (nodes[current].left != -1) {
                    stack.push_back(nodes[current].left);
                }
                if (nodes[current].right != -1) {
                    stack.push_back(nodes[current].right);
                }
            }

            for (std::size_t i = 0, j = traversal.size() - 1; i < j; ++i, --j) {
                std::swap(traversal[i], traversal[j]);
            }
        }

        for (int i = 0; i < nodeCount; ++i) {
            if (i != 0) {
                std::cout << ' ';
            }
            std::cout << traversal[i];
        }
        std::cout << '\n';
    }

    return 0;
}
