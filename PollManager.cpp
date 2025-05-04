// PollManager.cpp
#include "PollManager.h"
#include <iostream>
#include <iomanip>
#include <fstream>

void PollManager::exportToCSV(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "❌ Failed to open file for writing: " << filename << "\n";
        return;
    }

    out << "Option,Vote Count,Percentage\n";
    int total = votes.total();
    for (size_t i = 0; i < options.size(); ++i) {
        int count = votes.rangeQuery(i + 1, i + 1);
        double percentage = total > 0 ? (count * 100.0 / total) : 0.0;
        out << "\"" << options[i] << "\"," << count << "," << percentage << "\n";
    }

    out << "Total," << total << ",100.0\n";
    out.close();

    std::cout << "📁 Poll results exported to " << filename << "\n";
}


int PollManager::totalVotes() const {
    return votes.total();
}

PollManager::PollManager(const std::vector<std::string>& opts)
    : options(opts), votes(opts.size()) {}

void PollManager::castVote(int index) {
    if (index < 0 || index >= options.size()) {
        std::cout << "❌ Invalid vote option.\n";
        return;
    }
    votes.update(index + 1, 1);  // Use 'votes' instead of 'tree'
    lastVoteIndex = index;
}
    
void PollManager::undoVote() {
    if (lastVoteIndex == -1) {
        std::cout << "⚠️ No vote to undo.\n";
        return;
    }
    votes.update(lastVoteIndex + 1, -1);  // Use 'votes' here too
    std::cout << "↩️ Undid last vote for option " << lastVoteIndex
                << ": " << options[lastVoteIndex] << "\n";
    lastVoteIndex = -1;
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

int PollManager::optionCount() const {
    return options.size();
}

std::string PollManager::getOptionLabel(int index) const {
    if (index >= 0 && index < options.size()) {
        return options[index];
    }
    return "[Invalid Option]";
}

int PollManager::getVoteCount(int optionIndex) const {
    if (optionIndex < 0 || optionIndex >= optionCount()) return 0;
    return votes.rangeQuery(optionIndex + 1, optionIndex + 1);
}
