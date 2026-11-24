#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <string>

struct node {
    int ticket;
    node* next;
};

struct queue {
    node* head;
    node* tail;
};

int main() {
    int m, n, p, len;
    len = 0;
    std::string input;

    node* empty_node = new node;
    empty_node->ticket = -1;
    empty_node->next = empty_node;

    queue q;
    q.head = empty_node;
    q.tail = empty_node;

    q.head = new node;
    q.tail = q.head;
    q.head->next = empty_node;
    q.head->ticket = -1;

    node* current = q.head;

    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        current = q.head;
        // std::cout << i << std::endl;
        
        std::cin >> input;
        if (input == "print") {
            if (len == 0) {
                std::cout << std::endl;
                continue;
            }
            
            while (current != empty_node && current != q.tail && current->ticket != -1) {
                std::cout << current->ticket << " ";
                current = current->next;
            }
            std::cout << q.tail->ticket << std::endl;
        }
        else if (input == "new_normal_customer") {
            std::cin >> n;

            if (q.head->ticket == -1) {
                q.head->ticket = n;
                // std::cout << "New normal customer with value: " << q.head->ticket << std::endl;
                len++;
                continue;
            }

            current = new node;
            current->ticket = n;
            current->next = empty_node;
            q.tail->next = current;
            q.tail = current;
            len++;

            // std::cout << "New normal customer with value: " << current->ticket << std::endl;
        } else if (input == "new_selfish_customer") {
            std::cin >> n;
            std::cin >> p;

            if (p == 0)
            {
                node* new_customer = new node;
                new_customer->ticket = n;
                new_customer->next = current;
                q.head = new_customer;
                len++;
                
                continue;
            }
            
            
            for (int i = 0; i < p-1 && current != empty_node; ++i) {
                current = current->next;
            }
            node* new_customer = new node;
            new_customer->ticket = n;
            new_customer->next = current->next;
            current->next = new_customer;
            len++;
            
            // std::cout << "New selfish customer with value: " << n << " and priority: " << p << std::endl;
        } else if (input == "done_customer") {
            if (q.head->next == empty_node) {
                q.head->ticket = -1;
                len--;
                continue;
            }

            node* temp = q.head;
            q.head = q.head->next;
            delete temp;
            len--;

            // std::cout << "Done customer." << std::endl;
        } else {
            std::cout << "Unknown command: " << input << std::endl;
        }
    }
    while (q.head != empty_node) {
        node* temp = q.head;
        q.head = q.head->next;
        delete temp;
    }
    delete empty_node;
    return 0;
}