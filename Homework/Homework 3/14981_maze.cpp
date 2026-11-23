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
    std::cin.tie(0);

    int m;
    std::cin >> m;

    for (int i = 0; i < m; i++)
    {
        int n;
        std::string cmd;
        std::cin >> n >> cmd;

        if (cmd != "PRE" && cmd != "IN" && cmd != "POST")
        {
            for (int j = 0; j < n; j++) // flush input
            {
                int val, left, right;
                std::cin >> val >> left >> right;
            }

            std::cout << "Invalid command\n";
            continue;
        }

        std::vector<int> values(n);
        std::vector<int> rightValues(n);
        std::vector<int> leftValues(n);

        std::unordered_map<int, int> indexOf;
        indexOf.reserve(static_cast<std::size_t>(n)*2);

        for (int j = 0; j < n; j++)
        {
            std::cin >> values[j] >> leftValues[j] >> rightValues[j];

            indexOf[values[j]] = j;
        }        
        
        std::vector<Node> nodes(n);
        for (int j = 0; j < n; j++) // make tree
        {
            nodes[j] = {values[j], -1, -1};// value, left, right

            if (leftValues[j] != -1)
            {
                nodes[j].left = indexOf[leftValues[j]];
            }
            
            if (rightValues[j] != -1)
            {
                nodes[j].right = indexOf[rightValues[j]];
            }
        }
        
        std::vector<int> output;
        output.reserve(n);
        std::vector<int> stack;
        stack.reserve(n);

        const int root = 0;

        if (cmd == "PRE")
        {
            stack.push_back(root); 

            while (!stack.empty())
            {
                int cur = stack.back();
                stack.pop_back();
                output.push_back(nodes[cur].value); // store value

                if (nodes[cur].right != -1) // check right
                {
                    stack.push_back(nodes[cur].right);
                } // right first because stack filo
                
                if (nodes[cur].left != -1) // check left
                {
                    stack.push_back(nodes[cur].left);
                }
            }
        }
        else if (cmd == "IN")
        {
            int cur = root;

            while (cur != -1 || !stack.empty())
            {
                while (cur != -1) // go the most left
                {
                    stack.push_back(cur);
                    cur = nodes[cur].left;
                }
                
                cur = stack.back();
                stack.pop_back();
                output.push_back(nodes[cur].value); // store left, value, right
                cur = nodes[cur].right;
            }
        }
        else // post sama kaya pre, cuma ganti urutan left right terus reverse
        {
            stack.push_back(root);

            while (!stack.empty())
            {
                int cur = stack.back();
                stack.pop_back();
                output.push_back(nodes[cur].value); // store value

                if (nodes[cur].left != -1) // check left
                {
                    stack.push_back(nodes[cur].left);
                } // left first because stack filo
                
                if (nodes[cur].right != -1) // check right
                {
                    stack.push_back(nodes[cur].right);
                }
            }
            
            for (size_t j = 0, k = output.size()-1; j < k; j++, k--)
            {
                std::swap(output[j], output[k]);
            }
        }
        
        for (int j = 0; j < n; j++)
        {
            if (j != 0)
            {
                std::cout << ' ';
            }
            std::cout << output[j];
        }
        std::cout << '\n';
    }
}