#include <iostream>
#include <map>
#include <string>

int main() {
    long long m;
    std::cin >> m;

    std::map<long long, std::string> appointments;
    
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
            if (appointments.find(time1) == appointments.end())
            {
                appointments[time1] = name;
            }
            else
            {
                std::cout << "-1\n";
            }
        }
        else if (cmd == "change")
        {
            std::cin >> name >> time1 >> time2;
            
            if (appointments.find(time2) != appointments.end() || appointments.find(time1) == appointments.end() || appointments.find(time1)->second != name)
            {
                std::cout << "-1\n";
            }
            else
            {
                appointments[time2] = name;
                appointments.erase(time1);
            }
        }
        else if (cmd == "delete")
        {
            std::cin >> name >> time1;
            if (appointments.find(time1) == appointments.end() || appointments.find(time1)->second != name)
            {
                std::cout << "-1\n";
            }
            else
            {
                appointments.erase(appointments.find(time1));
            }
        }
        else if (cmd == "search")
        {
            std::cin >> time1;

            if (appointments.upper_bound(time1) != appointments.end())
            {
                std::cout << appointments.upper_bound(time1)->second << '\n';
            }
            else
            {
                std::cout << "-1\n";
            }
            
        }

    }
    
    return 0;
}