#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <functional>

#include "Day1.h" 
#include "Day2.h"
#include "Day3.h"
#include "Day5.h"
#include "Day6.h"
#include "Day7.h"

struct MenuEntry {
    std::string filename;
    std::string functionName;
    std::string displayName;
    std::string language;
    std::string command;
};

class LanguageExecutor {
private:
    std::map<std::string, std::function<void(const MenuEntry&)>> executors;
    std::map<std::string, std::function<void()>> cppFunctions;

public:
    LanguageExecutor() {
        // C++ Functions
        cppFunctions = {
            {"NotQuiteLisp", NotQuiteLisp},
            {"IWasToldThereWouldBeNoMath", IWasToldThereWouldBeNoMath},
            {"PerfectlySphericalHousesInAVacuum", PerfectlySphericalHousesInAVacuum},
            {"DoesntHeHaveInternElvesForThis", DoesntHeHaveInternElvesForThis},
            {"ProbablyAFireHazard", ProbablyAFireHazard},
            {"SomeAssemblyRequired", SomeAssemblyRequired}
        };

        // C++ Executor
        executors["cpp"] = [this](const MenuEntry& entry) {
            std::cout << "Executing C++ function: " << entry.functionName << std::endl;
            auto it = cppFunctions.find(entry.functionName);
            if (it != cppFunctions.end()) {
                it->second(); // call
            }
            else {
                std::cerr << "Error: C++ function '" << entry.functionName << "' not found!" << std::endl;
            }
            };

        
        // Java
        executors["java"] = [](const MenuEntry& entry) {
            std::string className = entry.filename.substr(0, entry.filename.find(".java"));
            std::string command = "java " + className;
            std::system(command.c_str());
            };
        

        executors["custom"] = [](const MenuEntry& entry) {
            std::system(entry.command.c_str());
            };
    }

    void execute(const MenuEntry& entry) {
        auto it = executors.find(entry.language);
        if (it != executors.end()) {
            it->second(entry);
        }
        else {
            std::cerr << "Unsupported language: " << entry.language << std::endl;
        }
    }

    void addLanguage(const std::string& lang, std::function<void(const MenuEntry&)> executor) {
        executors[lang] = executor;
    }

    void addCppFunction(const std::string& name, std::function<void()> func) {
        cppFunctions[name] = func;
    }
};

int main() {
    std::vector<MenuEntry> menu;
    std::ifstream config("config.txt");
    std::string line;

    LanguageExecutor executor;

    while (getline(config, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::vector<std::string> parts;
        size_t start = 0;
        size_t end = line.find(';');

        while (end != std::string::npos) {
            parts.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(';', start);
        }
        parts.push_back(line.substr(start));

        if (parts.size() >= 3) {
            MenuEntry entry;
            entry.filename = parts[0];
            entry.functionName = parts[1];
            entry.language = parts[2];
            entry.command = (parts.size() > 3) ? parts[3] : "";

            size_t dotPos = entry.filename.find_last_of('.');
            if (dotPos != std::string::npos) {
                entry.displayName = entry.filename.substr(0, dotPos);
            }
            else {
                entry.displayName = entry.filename;
            }
            menu.push_back(entry);
        }
    }

    std::cout << "Advent of Code 2015\n";

    bool exit = false;
    while (!exit) {
        std::cout << "\n--------------------";
        std::cout << "\nChoose the day\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << (i + 1) << ". " << menu[i].displayName << " - " << menu[i].language << "\n";
        }
        std::cout << "0. Quit\n";
        std::cout << "--------------------\n";

        int number;
        std::cin >> number;

        if (number == 0) {
            exit = true;
        }
        else if (number > 0 && number <= static_cast<int>(menu.size())) {
            const MenuEntry& entry = menu[number - 1];

            std::cout << "\n--- " << entry.displayName << " ---\n";
            executor.execute(entry);
            std::cout << "-------------------\n";
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
        else {
            std::cout << "Ungültige Auswahl\n";
        }
    }
    return 0;
}