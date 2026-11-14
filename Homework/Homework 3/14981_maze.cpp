#include <iostream>
#include <stack>
#include <string>

struct node
{
    int v = -1;
    node* l;
    node* r;
};

int main() {
    int m;
    std::cin >> m;

    node empty;
    empty.v = -1;
    empty.l = &empty;
    empty.r = &empty;

    for (int i = 0; i < m; i++)
    {
        int n;
        std::string cmd;
        bool valid = true;

        std::cin >> n;
        std::cin >> cmd;

        if (cmd != "PRE" && cmd != "IN" && cmd != "POST")
        {
            valid = false;

            for (int j = 0; j < 3*n; j++)
            {
                std::string temp;
                std::cin >> temp;
            }

            std::cout << "Invalid command\n";
            continue;
        }

        node* maze_root = new node;
        maze_root->v = -1;
        maze_root->l = &empty;
        maze_root->r = &empty;

        node current;
        current.v = -1;
        current.l = &empty;
        current.r = &empty;

        for (int j = 0; j < n && valid; j++)
        {
            int v, l, r;
            std::cin >> v;
            std::cin >> l;
            std::cin >> r;

            if (maze_root->v == -1)
            {
                maze_root->v = v;

                maze_root->l = new node;
                maze_root->l->v = l;
                maze_root->l->l = &empty;
                maze_root->l->r = &empty;

                maze_root->r = new node;
                maze_root->r->v = r;
                maze_root->r->l = &empty;
                maze_root->r->r = &empty;

                continue;
            }
            
        }        
        
    }
    
}