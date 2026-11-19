#include <iostream>
#include <map>

bool isValidTime(long long time, const std::map<std::string, long long>& appointments) {
    for (const auto& appointment : appointments) {
        if (appointment.second == time) {
            return false; // Time is already taken
        }
    }
    return true; // Time is available
}

int main() {
    long long m;
    std::cin >> m;

    std::map<std::string, long long> appointments;
    
    for (long long i = 0; i < m; i++)
    {
        std::string cmd;
        std::string name;
        long long time1;
        long long time2;

        std::cin >> cmd;
        if (cmd == "add")
        {
            std::cin >> name >> time1;
            if (isValidTime(time1, appointments))
            {
                appointments[name] = time1;
            }
            else
            {
                std::cout << "-1\n";
            }
            
        }
        else if (cmd == "change")
        {
            std::cin >> name >> time1 >> time2;
            
            if (isValidTime(time2, appointments))
            {
                appointments[name] = time2;
            }
            else
            {
                std::cout << "-1\n";
            }
        }
        else if (cmd == "delete")
        {
            std::cin >> name >> time1;
            if (appointments.find(name) != appointments.end() && appointments[name] == time1)
            {
                appointments.erase(name);
            }
            else
            {
                std::cout << "-1\n";
            }
        }
        else if (cmd == "search")
        {
            std::cin >> time1;

            bool found = false;
            for (const auto& appointment : appointments) {
                if (appointment.second > time1) {
                    std::cout << appointment.first << "\n";
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cout << "-1\n";
            }
        }

    }
    
    return 0;
}