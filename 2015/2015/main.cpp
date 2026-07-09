#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <functional>
#include <filesystem>
#include <iomanip>
#include <cctype>

namespace fs = std::filesystem;

// Forward declarations for C++ functions
void NotQuiteLisp();
void IWasToldThereWouldBeNoMath();
void PerfectlySphericalHousesInAVacuum();
void DoesntHeHaveInternElvesForThis();
void ProbablyAFireHazard();
void SomeAssemblyRequired();

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

    std::string findFileInSubdir(const std::string& filename, const std::string& subdir) {
        // First check in current directory
        if (fs::exists(filename)) {
            return filename;
        }

        // Ccheck in subdirectory
        std::string path = subdir + "/" + filename;
        if (fs::exists(path)) {
            return path;
        }

        return "";
    }

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
            std::cout << "\n";

            std::string filePath = findFileInSubdir(entry.filename, "c++");

            if (filePath.empty()) {
                std::cerr << "Error: File '" << entry.filename << "' not found in c++ directory!" << std::endl;
                return;
            }

            auto it = cppFunctions.find(entry.functionName);
            if (it != cppFunctions.end()) {
                it->second(); // Call function
            }
            else {
                std::cerr << "Error: C++ function '" << entry.functionName << "' not found!" << std::endl;
            }
            };

        // Java Executor
        executors["java"] = [](const MenuEntry& entry) {
            std::string className = entry.filename;

            // Remove .java extension if present
            size_t dotPos = className.find(".java");
            if (dotPos != std::string::npos) {
                className = className.substr(0, dotPos);
            }

            std::cout << "Executing Java class via Maven JAR: " << className << std::endl;

            std::string jarPath = "java/target/advent-java.jar";

            if (!fs::exists(jarPath)) {
                std::cerr << "Error: Java JAR not found: " << jarPath << std::endl;
                std::cerr << "Build it first with:" << std::endl;
                std::cerr << "  cd java" << std::endl;
                std::cerr << "  .\\mvnw.cmd package" << std::endl;
                return;
            }

            std::string command = "java -jar \"" + jarPath + "\" " + className;

            std::cout << "Running: " << command << std::endl;

            int result = std::system(command.c_str());

            if (result != 0) {
                std::cerr << "Java execution failed!" << std::endl;
            }
            };

        // Custom Executor
        executors["custom"] = [](const MenuEntry& entry) {
            std::cout << "Executing custom command: " << entry.command << std::endl;
            if (!entry.command.empty()) {
                std::system(entry.command.c_str());
            }
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

int extractDayNumber(const std::string& filename) {
    std::string prefix = "Day";

    size_t pos = filename.find(prefix);
    if (pos == std::string::npos) {
        return -1;
    }

    pos += prefix.length();

    std::string numberText;
    while (pos < filename.length() && std::isdigit(static_cast<unsigned char>(filename[pos]))) {
        numberText += filename[pos];
        pos++;
    }

    if (numberText.empty()) {
        return -1;
    }

    return std::stoi(numberText);
}


int main() {
    std::vector<MenuEntry> menu;
    std::map<int, MenuEntry> menuByDay;
    std::ifstream config("config.txt");

    if (!config.is_open()) {
        std::cerr << "Error: config.txt not found!" << std::endl;
        return 1;
    }

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

            // Create display name: DayX - FunctionName - language
            size_t dotPos = entry.filename.find_last_of('.');
            std::string dayName;
            if (dotPos != std::string::npos) {
                dayName = entry.filename.substr(0, dotPos);
            }
            else {
                dayName = entry.filename;
            }

            // Format: Day1 - NotQuiteLisp - cpp
            entry.displayName = dayName + " - " + entry.functionName + " - " + entry.language;
            menu.push_back(entry);

            int dayNumber = extractDayNumber(entry.filename);

            if (dayNumber != -1) {
                menuByDay[dayNumber] = entry;
            }
        }
    }

    std::cout << "========================================\n";
    std::cout << "       Advent of Code 2015\n";
    std::cout << "========================================\n";

    bool exit = false;
    while (!exit) {
        std::cout << "\n========================================\n";

        for (const auto& pair : menuByDay) {
            int day = pair.first;
            const MenuEntry& entry = pair.second;

            std::cout << std::setw(3) << day << ". " << entry.displayName << "\n";
        }

        std::cout << "\n" << std::setw(3) << "0" << ". Quit\n";
        std::cout << "\n========================================";
        std::cout << "\nChoose the day\n";

        int number;
        std::cin >> number;

        if (number == 0) {
            exit = true;
            std::cout << "\nGoodbye!\n";
        }
        else if (number > 0) {
            auto it = menuByDay.find(number);

            if (it != menuByDay.end()) {
                const MenuEntry& entry = it->second;
                executor.execute(entry);
            }
            else {
                std::cout << "No entry found for Day " << number << ". Please try another day.\n\n";
            }
        }
        else {
            std::cout << "Invalid selection. Please try again.\n\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
    return 0;
}