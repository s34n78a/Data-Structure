#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int m;
    std::cin >> m;

    for (int i = 0; i < m; i++)
    {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "med")
        {
            /* code */
        }
        else
        {
            int num = std::stoi(cmd);

        }
        
    }
    
    return 0;
}