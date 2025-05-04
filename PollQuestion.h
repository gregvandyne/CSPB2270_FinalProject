// PollQuestion.h
#pragma once
#include <string>
#include <vector>
#include "PollManager.h"

class PollQuestion {
private:
    std::string prompt;
    PollManager manager;

public:
    PollQuestion(const std::string& questionText, const std::vector<std::string>& options);
    void ask();
    void displayStats() const;
    void exportToCSV(const std::string& filename) const;
    const std::string& getPrompt() const;
};