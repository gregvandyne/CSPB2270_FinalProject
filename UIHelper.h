
// UIHelper.h
#pragma once
#include <string>
#include <vector>

// ANSI color macros for styling
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

class UIHelper {
public:
    static void printBanner(const std::string& message);
    static void printMenu(const std::vector<std::string>& items);
    static void printList(const std::string& title, const std::vector<std::string>& items);
    static void printWarning(const std::string& message);

    static std::string prompt(const std::string& label);
    static int promptInt(const std::string& label);

    static int selectFromList(const std::string& promptMsg, const std::vector<std::string>& options);
    static void clearScreen();
};