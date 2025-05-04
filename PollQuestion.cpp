// PollQuestion.cpp
#include "PollQuestion.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <fstream>

PollQuestion::PollQuestion(const std::string& prompt, const std::vector<std::string>& options)
    : prompt(prompt), manager(options) {}

void PollQuestion::ask() {
    std::cout << "\n" << prompt << "\n";
    for (int i = 0; i < manager.optionCount(); ++i) {
        std::cout << "  " << i << ". " << manager.getOptionLabel(i) << "\n";
    }

    std::cout << "Enter your choice: ";
    int choice;
    if (!(std::cin >> choice) || choice < 0 || choice >= manager.optionCount()) {
        std::cout << "❌ Invalid choice. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return ask(); // recursively re-ask
    }
    manager.castVote(choice);
}

void PollQuestion::displayStats() const {
    std::cout << "\nResults for: " << prompt << "\n";
    manager.displayStats();
}

void PollQuestion::exportToCSV(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "❌ Failed to open file: " << filename << "\n";
        return;
    }

    out << "Question: ," << prompt << "\n";
    out << "Option,Vote Count,Percentage\n";
    int total = manager.totalVotes();
    for (int i = 0; i < manager.optionCount(); ++i) {
        int count = manager.getVoteCount(i);
        double pct = total > 0 ? (count * 100.0 / total) : 0.0;
        out << "\"" << manager.getOptionLabel(i) << "\"," << count << "," << pct << "\n";
    }
    out << "Total," << total << ",100.0\n";
    out.close();

    std::cout << "📁 Exported question results to " << filename << "\n";
}

const std::string& PollQuestion::getPrompt() const {
    return prompt;
}
