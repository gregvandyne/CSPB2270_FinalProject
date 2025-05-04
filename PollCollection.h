#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "PollManager.h"

class PollCollection {
private:
    std::unordered_map<std::string, std::unique_ptr<PollManager>> polls;

public:
    void createPoll(const std::string& pollName, const std::vector<std::string>& options);
    bool castVote(const std::string& pollName, int optionIndex);
    void showStats(const std::string& pollName) const;
    std::vector<std::string> listPolls() const;
    const PollManager& getPollManager(const std::string& name) const;
    bool deletePoll(const std::string& name);
    void undoVote(const std::string& name);
    void exportPollToCSV(const std::string& name, const std::string& filename) const;
};
