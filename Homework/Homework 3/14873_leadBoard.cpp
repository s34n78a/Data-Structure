#include <iostream>
#include <string>
#include <set>

struct Entry
{
    int score;
    std::string name;
};

struct BiggerScore
{
    bool operator()(const Entry& left, const Entry& right) const
    {
        return left.score > right.score;
    };
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int m;
    std::cin >> m;

    std::set<Entry, BiggerScore> leaderboard;

    for (int i = 0; i < m; ++i) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "s")
        {
            int score;
            std::string n;
            std::cin >> n >> score;

            leaderboard.insert({score, n});            
            continue;
        }
        
        if (static_cast<int>(leaderboard.size()) < cmd[1]-'0')
        {
            std::cout << "-1\n";
            continue;
        }
        
        std::set<Entry, BiggerScore>::iterator winner = leaderboard.begin();
        for (int i = 1; i < cmd[1]-'0'; i++)
        {
            winner++;
        }
        
        std::cout << winner->name << '\n';
        leaderboard.erase(winner);
    }

    return 0;
}