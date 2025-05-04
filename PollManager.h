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
};
