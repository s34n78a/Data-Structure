#include <iostream>
#include <map>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int commandCount;
    std::cin >> commandCount;

    std::map<long long, std::string> appointmentByTime;

    for (int i = 0; i < commandCount; ++i) {
        std::string command;
        std::cin >> command;

        if (command == "add") {
            std::string name;
            long long time;
            std::cin >> name >> time;

            if (appointmentByTime.find(time) != appointmentByTime.end()) {
                std::cout << "-1\n";
                continue;
            }

            appointmentByTime[time] = name;
            continue;
        }

        if (command == "change") {
            std::string name;
            long long oldTime, newTime;
            std::cin >> name >> oldTime >> newTime;

            std::map<long long, std::string>::iterator oldIt =
                appointmentByTime.find(oldTime);
            if (oldIt == appointmentByTime.end() || oldIt->second != name ||
                appointmentByTime.find(newTime) != appointmentByTime.end()) {
                std::cout << "-1\n";
                continue;
            }

            appointmentByTime.erase(oldIt);
            appointmentByTime[newTime] = name;
            continue;
        }

        if (command == "delete") {
            std::string name;
            long long time;
            std::cin >> name >> time;

            std::map<long long, std::string>::iterator it =
                appointmentByTime.find(time);
            if (it == appointmentByTime.end() || it->second != name) {
                std::cout << "-1\n";
                continue;
            }

            appointmentByTime.erase(it);
            continue;
        }

        // command == "search"
        long long time;
        std::cin >> time;

        std::map<long long, std::string>::iterator nextIt =
            appointmentByTime.upper_bound(time);
        if (nextIt == appointmentByTime.end()) {
            std::cout << "-1\n";
        } else {
            std::cout << nextIt->second << '\n';
        }
    }

    return 0;
}
