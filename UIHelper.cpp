// UIHelper.cpp
#include "UIHelper.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>

void UIHelper::printBanner(const std::string& message) {
    clearScreen();
    std::string border = R"(★彡=============================彡★)";
    for (char c : border) {
        std::cout << BOLD << MAGENTA << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
    std::cout << RESET << "\n";
    std::cout << BOLD << CYAN;
    for (char c : message) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }
    std::cout << RESET << "\n";
    for (char c : border) {
        std::cout << BOLD << MAGENTA << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }
    std::cout << RESET << "\n";
}

void UIHelper::printMenu(const std::vector<std::string>& items) {
    std::cout << BOLD << BLUE << "\n🚀 Main Menu 🚀" << RESET << "\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << BOLD << YELLOW << "  [" << i + 1 << "] " << RESET << GREEN << items[i] << RESET << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    std::cout << std::endl;
}

void UIHelper::printList(const std::string& title, const std::vector<std::string>& items) {
    std::cout << BOLD << CYAN << "\n📝 " << title << RESET << ":\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << MAGENTA << "  ➤ [" << i << "] " << RESET << items[i] << "\n";
    }
}

void UIHelper::printWarning(const std::string& message) {
    std::cout << RED << "\n🔥 WARNING: " << BOLD << message << RESET << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(350));
}

std::string UIHelper::prompt(const std::string& label) {
    std::string input;
    std::cout << YELLOW << "🖊️  " << label << RESET << ": ";
    std::getline(std::cin, input);
    return input;
}

int UIHelper::promptInt(const std::string& label) {
    int value;
    while (true) {
        std::cout << YELLOW << "🔢 " << label << RESET << ": ";
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << RED << "❌ Not a number. Try again!" << RESET << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

int UIHelper::selectFromList(const std::string& promptMsg, const std::vector<std::string>& options) {
    printList(promptMsg, options);
    int selection;
    while (true) {
        std::cout << CYAN << "👉 Your Choice: " << RESET;
        if (std::cin >> selection && selection >= 0 && selection < static_cast<int>(options.size())) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return selection;
        } else {
            std::cout << RED << "⚡ Invalid choice. Pick again!" << RESET << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void UIHelper::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}
