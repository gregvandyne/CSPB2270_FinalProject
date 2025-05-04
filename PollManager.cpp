// PollManager.cpp
#include "PollManager.h"
#include <iostream>
#include <iomanip>

int PollManager::totalVotes() const {
    return votes.total();
}

PollManager::PollManager(const std::vector<std::string>& opts)
    : options(opts), votes(opts.size()) {}

void PollManager::castVote(int optionIndex) {
    if (optionIndex >= 0 && optionIndex < options.size()) {
        votes.update(optionIndex + 1, 1);
    }
}

void PollManager::undoVote(int optionIndex) {
    if (optionIndex >= 0 && optionIndex < options.size()) {
        votes.update(optionIndex + 1, -1);
    }
}

void PollManager::displayStats() const {
    int total = votes.total();
    std::cout << "\n--- Poll Results ---\n";
    for (size_t i = 0; i < options.size(); ++i) {
        int count = votes.rangeQuery(i + 1, i + 1);
        double percentage = total > 0 ? (count * 100.0 / total) : 0;
        std::cout << std::setw(2) << i << ". " << options[i]
                  << ": " << count << " votes (" << std::fixed << std::setprecision(2)
                  << percentage << "%)\n";
    }
    std::cout << "Total votes: " << total << "\n";
}
