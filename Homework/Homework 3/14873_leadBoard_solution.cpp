#include <iostream>
#include <set>
#include <string>

struct Entry {
    int score;
    std::string name;
};

struct HigherScore {
    bool operator()(const Entry& left, const Entry& right) const {
        return left.score > right.score;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int commandCount;
    std::cin >> commandCount;

    std::set<Entry, HigherScore> leaderboard;

    for (int i = 0; i < commandCount; ++i) {
        std::string command;
        std::cin >> command;

        if (command == "s") {
            std::string name;
            int score;
            std::cin >> name >> score;
            leaderboard.insert({score, name});
            continue;
        }

        int place = command[1] - '0';
        if (static_cast<int>(leaderboard.size()) < place) {
            std::cout << "-1\n";
            continue;
        }

        std::set<Entry, HigherScore>::iterator winner = leaderboard.begin();
        for (int rank = 1; rank < place; ++rank) {
            ++winner;
        }

        std::cout << winner->name << '\n';
        leaderboard.erase(winner);
    }

    return 0;
}

/*
Hints and main ideas:
1. The board must stay sorted by score after every insertion.
2. Use std::set with a comparator that orders entries from highest score
   to lowest score. Scores are guaranteed to be unique, so each entry has
   a unique ordering key.
3. The first, second, and third places are the first three iterators in the
   set. If the requested place does not exist, print -1 and do not erase.
4. Otherwise, advance an iterator to the requested place, print its name,
   and erase that iterator.

Complexity:
- Adding a score: O(log M)
- Awarding a prize: O(1) for w1, O(1) for w2, or O(1) for w3 because the
  requested rank is at most three; erasing from the set is O(log M).
- Memory: O(M)
*/
