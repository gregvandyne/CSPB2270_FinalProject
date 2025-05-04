#include "PollCollection.h"
#include <iostream>

void PollCollection::createPoll(const std::string& pollName, const std::vector<std::string>& options) {
    if (polls.find(pollName) != polls.end()) {
        std::cout << "Poll \"" << pollName << "\" already exists.\n";
        return;
    }
    polls[pollName] = std::make_unique<PollManager>(options);
}

bool PollCollection::castVote(const std::string& pollName, int optionIndex) {
    auto it = polls.find(pollName);
    if (it == polls.end()) {
        std::cout << "Poll \"" << pollName << "\" not found.\n";
        return false;
    }
    it->second->castVote(optionIndex);
    return true;
}

void PollCollection::showStats(const std::string& pollName) const {
    auto it = polls.find(pollName);
    if (it == polls.end()) {
        std::cout << "Poll \"" << pollName << "\" not found.\n";
        return;
    }
    it->second->displayStats();
}

const PollManager& PollCollection::getPollManager(const std::string& name) const {
    return *polls.at(name);  // will throw if poll doesn't exist — can add guards later
}

std::vector<std::string> PollCollection::listPolls() const {
    std::vector<std::string> names;
    for (const auto& pair : polls) {
        names.push_back(pair.first);
    }
    return names;
}

bool PollCollection::deletePoll(const std::string& name) {
    auto it = polls.find(name);
    if (it == polls.end()) {
        std::cout << "⚠️ Poll \"" << name << "\" not found.\n";
        return false;
    }
    polls.erase(it);
    std::cout << "✅ Poll \"" << name << "\" deleted.\n";
    return true;
}

void PollCollection::undoVote(const std::string& name) {
    auto it = polls.find(name);
    if (it == polls.end()) {
        std::cout << "⚠️ Poll \"" << name << "\" not found.\n";
        return;
    }
    it->second->undoVote();
}

void PollCollection::exportPollToCSV(const std::string& name, const std::string& filename) const {
    auto it = polls.find(name);
    if (it != polls.end()) {
        it->second->exportToCSV(filename);
    } else {
        std::cout << "❌ Poll \"" << name << "\" not found.\n";
    }
}

