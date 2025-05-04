// main.cpp
#include <iostream>
#include "PollManager.h"

int main() {
    std::vector<std::string> options = {
        "Yes, very helpful",
        "Somewhat helpful",
        "Not helpful"
    };

    PollManager poll(options);
    int choice;

    while (true) {
        poll.displayStats();
        std::cout << "\nChoose an option to vote (0-" << options.size() - 1
                  << "), or -1 to exit: ";
        std::cin >> choice;

        if (choice == -1) break;
        if (choice >= 0 && choice < options.size()) {
            poll.castVote(choice);
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    std::cout << "\nFinal Results:\n";
    poll.displayStats();
    return 0;
}
