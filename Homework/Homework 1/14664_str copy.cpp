#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>

struct node {
    char name;
    node* next;
    node* prev;
};

struct queue {
    node* head;
    node* tail;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int m, pos, reverse, len;
    reverse = 0;
    len = 0;
    char input;

    node* empty_node = new node;
    empty_node->next = empty_node;
    empty_node->prev = empty_node;
    empty_node->name = '\0';

    queue q;
    q.head = new node;
    q.head->next = empty_node;
    q.head->prev = empty_node;
    q.head->name = '\0';
    q.tail = q.head;

    std::string cmd;

    std::cin >> m;

    for (int i = 0; i < m; i++)
    {
        std::cin >> cmd;

        node* current_node = q.head;
        
        if (cmd == "insert")
        {
            std::cin >> input;
            std::cin >> pos;

            if (pos > len)
            {
                std::cout << "invalid pos\0";
            }
            

            // std::cout << "Middle " << cmd << '\n';

            if (len == 0)
            {
                q.head->name = input;
                len++;
                continue;
            }

            node* new_node = new node;
            new_node->name = input;

            if (reverse == 1)
            {
                // std::cout << "reversed" << '\n';
                current_node = q.tail;

                if (pos == 0)
                {
                    q.tail->next = new_node;
                    new_node->prev = q.tail;
                    new_node->next = empty_node;
                    q.tail = new_node;
                    len++;
                    continue;
                }
                else if (pos == len)
                {
                    q.head->prev = new_node;
                    new_node->next = q.head;
                    new_node->prev = empty_node;
                    q.head = new_node;
                    len++;
                    continue;
                }

                for (int i = 0; i < pos-1; i++)
                {
                    current_node = current_node->prev;
                }
                
                new_node->prev = current_node->prev;
                new_node->next = current_node;
                current_node->prev->next = new_node;
                current_node->prev = new_node;
                len++;
            }
            else
            {
                if (pos == 0)
                {
                    q.head->prev = new_node;
                    new_node->next = q.head;
                    new_node->prev = empty_node;
                    q.head = new_node;
                    len++;
                    continue;
                }
                else if (pos == len)
                {
                    q.tail->next = new_node;
                    new_node->prev = q.tail;
                    new_node->next = empty_node;
                    q.tail = new_node;
                    len++;
                    continue;
                }
                
                for (int i = 0; i < pos-1; i++)
                {
                    current_node = current_node->next;
                }
                
                new_node->next = current_node->next;
                new_node->prev = current_node;
                current_node->next->prev = new_node;
                current_node->next = new_node;
                len++;
            }
        }
        else if (cmd == "insert_front")
        {
            std::cin >> input;

            // std::cout << "Front " << cmd << '\n';

            if (len == 0)
            {
                q.head->name = input;
                len++;
                continue;
            }
            
            node* new_node = new node;
            new_node->name = input;

            if (reverse == 1)
            {
                // std::cout << "reversed" << '\n';
                new_node->next = empty_node;
                new_node->prev = q.tail;
                q.tail->next = new_node;
                q.tail = new_node;
                len++;
            }
            else
            {
                new_node->prev = empty_node;
                new_node->next = q.head;
                q.head->prev = new_node;
                q.head = new_node;
                len++;
            }
        }
        else if (cmd == "insert_back")
        {
            // std::cout << "Back " << cmd << '\n';

            std::cin >> input;

            if (len == 0)
            {
                q.head->name = input;
                len++;
                continue;
            }
            
            node* new_node = new node;
            new_node->name = input;

            if (reverse == 1)
            {
                // std::cout << "reversed" << '\n';
                new_node->prev = empty_node;
                new_node->next = q.head;
                q.head->prev = new_node;
                q.head = new_node;
                len++;
            }
            else
            {
                new_node->next = empty_node;
                new_node->prev = q.tail;
                q.tail->next = new_node;
                q.tail = new_node;
                len++;
            }
            
        }
        else if (cmd == "delete")
        {
            // std::cout << "Middle " << cmd << '\n';

            std::cin >> pos;

            if (pos >= len)
            {
                std::cout << "invalid pos\0";
            }
            

            if (len == 0)
            {
                continue;
            }
            else if (len == 1)
            {
                q.head->name = '\0';
                len--;
                continue;
            }

            if (reverse == 1)
            {
                // std::cout << "reversed" << '\n';
                current_node = q.tail;

                if (pos == 0)
                {
                    q.tail = q.tail->prev;
                    delete q.tail->next;
                    q.tail->next = empty_node;
                    len--;
                    continue;
                }
                else if (pos == len - 1)
                {
                    q.head = q.head->next;
                    delete q.head->prev;
                    q.head->prev = empty_node;
                    len--;
                    continue;
                }
                

                for (int i = 0; i < pos; i++)
                {
                    current_node = current_node->prev;
                }
                
                current_node->prev->next = current_node->next;
                current_node->next->prev = current_node->prev;
                delete current_node;
                len--;
            }
            else
            {
                if (pos == 0)
                {
                    q.head = q.head->next;
                    delete q.head->prev;
                    q.head->prev = empty_node;
                    len--;
                    continue;
                }
                else if (pos == len - 1)
                {
                    q.tail = q.tail->prev;
                    delete q.tail->next;
                    q.tail->next = empty_node;
                    len--;
                    continue;
                }
                
                for (int i = 0; i < pos; i++)
                {
                    current_node = current_node->next;
                }
                
                current_node->next->prev = current_node->prev;
                current_node->prev->next = current_node->next;
                delete current_node;
                len--;
            }
        }
        else if (cmd == "delete_front")
        {
            // std::cout << "Front " << cmd << '\n';

            if (len == 0)
            {
                continue;
            }
            else if (len == 1)
            {
                q.head->name = '\0';
                len--;
                continue;
            }
            

            if (reverse == 1)
            {
                // std::cout << "reversed" << '\n';
                
                q.tail = q.tail->prev;
                delete q.tail->next;
                q.tail->next = empty_node;
                len--;
            }
            else
            {
                q.head = q.head->next;
                delete q.head->prev;
                q.head->prev = empty_node;
                len--;
            }
        }
        else if (cmd == "delete_back")
        {
            // std::cout << "Back " << cmd << '\n';

            if (len  == 0)
            {
                continue;
            }
            else if (len == 1)
            {
                q.head->name = '\0';
                len--;
                continue;
            }

            if (reverse == 1)
            {
                // std::cout << "reversed" << '\n';
                
                q.head = q.head->next;
                delete q.head->prev;
                q.head->prev = empty_node;
                len--;
            }
            else
            {
                q.tail = q.tail->prev;
                delete q.tail->next;
                q.tail->next = empty_node;
                len--;
            }
        }
        else if (cmd == "reverse")
        {
            // std::cout << cmd << '\n';

            reverse = 1 - reverse;
        }
        else if (cmd == "print")
        {
            // std::cout << cmd << '\n';

            if (reverse == 1)
            {
                // std::cout << "reversed" << '\n';
                
                current_node = q.tail;
                while (current_node->name != '\0' && current_node != empty_node)
                {
                    std::cout << current_node->name;
                    current_node = current_node->prev;
                }
            }
            else
            {
                // std::cout << "not reversed" << '\n';
                current_node = q.head;
                while (current_node->name != '\0' && current_node != empty_node)
                {
                    std::cout << current_node->name;
                    current_node = current_node->next;
                }
                
            }

            std::cout << '\n';
        }
        else
        {
            std::cout << "Invalid command: " << cmd << '\n';

        }
        
    }
    
    return 0;
}