#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>
#include <functional>
#include <filesystem>
#include <iomanip>

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

    void compileJavaIfNeeded(const std::string& className, const std::string& javaDir) {
        std::string javaFile = javaDir + "/" + className + ".java";
        std::string classFile = javaDir + "/" + className + ".class";

        // Check if .java file exists
        if (!fs::exists(javaFile)) {
            std::cerr << "Java file not found: " << javaFile << std::endl;
            return;
        }

        // Check if .class file exists and is up to date
        bool needsCompile = true;
        if (fs::exists(classFile)) {
            auto javaTime = fs::last_write_time(javaFile);
            auto classTime = fs::last_write_time(classFile);
            if (javaTime <= classTime) {
                needsCompile = false;
            }
        }

        if (needsCompile) {
            std::cout << "Compiling " << className << ".java..." << std::endl;
            std::string compileCmd = "javac \"" + javaFile + "\"";
            int result = std::system(compileCmd.c_str());
            if (result != 0) {
                std::cerr << "Compilation failed!" << std::endl;
            }
        }
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
        executors["java"] = [this](const MenuEntry& entry) {
            std::string className = entry.filename;
            // Remove .java extension if present
            size_t dotPos = className.find(".java");
            if (dotPos != std::string::npos) {
                className = className.substr(0, dotPos);
            }

            std::cout << "Executing Java class: " << className << std::endl;

            // Look for Java file in java directory
            std::string javaDir = "java";
            if (!fs::exists(javaDir)) {
                std::cerr << "Error: java directory not found!" << std::endl;
                return;
            }

            // Compile if needed
            compileJavaIfNeeded(className, javaDir);

            // Execute Java program
            std::string command = "java -cp \"" + javaDir + "\" " + className;
            std::cout << "Running: " << command << std::endl;
            std::system(command.c_str());
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

int main() {
    std::vector<MenuEntry> menu;
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
        }
    }

    std::cout << "========================================\n";
    std::cout << "       Advent of Code 2015\n";
    std::cout << "========================================\n";

    bool exit = false;
    while (!exit) {
        std::cout << "\n========================================\n";

        for (size_t i = 0; i < menu.size(); ++i) {
            std::cout << std::setw(3) << (i + 1) << ". " << menu[i].displayName << "\n";
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
        else if (number > 0 && number <= static_cast<int>(menu.size())) {
            const MenuEntry& entry = menu[number - 1];
            executor.execute(entry);
        }
        else {
            std::cout << "Invalid selection. Please try again.\n\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    }
    return 0;
}