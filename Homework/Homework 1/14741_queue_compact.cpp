#include <iostream>
#include <string>

struct Node {
    int ticket;
    Node* next;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    Node sentinel = {-1, &sentinel};
    Node* tail = &sentinel;
    int length = 0;
    int command_count;
    std::string command;

    auto insert_at = [&](int ticket, int position) {
        if (position == length) {
            Node* node = new Node{ticket, &sentinel};
            tail->next = node;
            tail = node;
            ++length;
            return;
        }

        Node* previous = &sentinel;
        for (int i = 0; i < position; ++i)
            previous = previous->next;

        Node* node = new Node{ticket, previous->next};
        previous->next = node;
        if (previous == tail)
            tail = node;
        ++length;
    };

    auto remove_front = [&]() {
        Node* node = sentinel.next;
        sentinel.next = node->next;
        delete node;
        if (--length == 0)
            tail = &sentinel;
    };

    std::cin >> command_count;
    while (command_count--) {
        std::cin >> command;

        if (command == "print") {
            Node* node = sentinel.next;
            while (node != &sentinel) {
                std::cout << node->ticket;
                node = node->next;
                if (node != &sentinel)
                    std::cout << ' ';
            }
            std::cout << '\n';
        } else if (command == "new_normal_customer") {
            int ticket;
            std::cin >> ticket;
            insert_at(ticket, length);
        } else if (command == "new_selfish_customer") {
            int ticket, priority;
            std::cin >> ticket >> priority;
            insert_at(ticket, priority);
        } else if (command == "done_customer" && length) {
            remove_front();
        }
    }
}