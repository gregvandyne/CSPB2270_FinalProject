// PollManager.h
#pragma once
#include <string>
#include <vector>
#include "FenwickTree.h"

class PollManager {
private:
    std::vector<std::string> options;
    FenwickTree votes;

public:
    PollManager(const std::vector<std::string>& options);
    void castVote(int optionIndex);
    void undoVote(int optionIndex);
    void displayStats() const;
    int totalVotes() const;
    int optionCount() const;
    std::string getOptionLabel(int index) const;
    int lastVoteIndex = -1; // to track last vote
    void undoVote();
    void exportToCSV(const std::string& filename) const;
    int getVoteCount(int optionIndex) const;
};
