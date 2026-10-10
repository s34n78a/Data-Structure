#include <iostream>
#include <string>

struct Node {
    char value;
    Node* next;
    Node* previous;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    Node sentinel = {'\0', &sentinel, &sentinel};
    int command_count, length = 0;
    bool reversed = false;
    std::string command;

    auto insert_before = [&](Node* position, char value) {
        Node* node = new Node{value, position, position->previous};
        position->previous->next = node;
        position->previous = node;
        return node;
    };

    auto insert_after = [&](Node* position, char value) {
        Node* node = new Node{value, position->next, position};
        position->next->previous = node;
        position->next = node;
        return node;
    };

    auto erase = [&](Node* node) {
        node->previous->next = node->next;
        node->next->previous = node->previous;
        delete node;
    };

    auto at = [&](int position) {
        Node* node = reversed ? sentinel.previous : sentinel.next;
        for (int i = 0; i < position; ++i)
            node = reversed ? node->previous : node->next;
        return node;
    };

    auto insert_at = [&](char value, int position) {
        if (reversed && position < length) {
            insert_after(at(position), value);
        } else if (reversed) {
            insert_before(sentinel.next, value);
        } else {
            Node* target = position == length ? &sentinel : at(position);
            insert_before(target, value);
        }
        ++length;
    };

    std::cin >> command_count;
    while (command_count--) {
        std::cin >> command;

        if (command == "insert") {
            char value;
            int position;
            std::cin >> value >> position;
            insert_at(value, position);
        } else if (command == "insert_front") {
            char value;
            std::cin >> value;
            insert_at(value, 0);
        } else if (command == "insert_back") {
            char value;
            std::cin >> value;
            insert_at(value, length);
        } else if (command == "delete") {
            int position;
            std::cin >> position;
            if (length) {
                erase(at(position));
                --length;
            }
        } else if (command == "delete_front") {
            if (length) {
                erase(at(0));
                --length;
            }
        } else if (command == "delete_back") {
            if (length) {
                erase(at(length - 1));
                --length;
            }
        } else if (command == "reverse") {
            reversed = !reversed;
        } else if (command == "print") {
            Node* node = reversed ? sentinel.previous : sentinel.next;
            while (node != &sentinel) {
                std::cout << node->value;
                node = reversed ? node->previous : node->next;
            }
            std::cout << '\n';
        }
    }
}