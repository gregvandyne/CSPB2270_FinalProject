#include <iostream>
#include "PollCollection.h"

int main() {
    PollCollection pc;
    std::string command;

    std::cout << "🗳️  Welcome to the Real-Time Voting System!\n";

    while (true) {
        std::cout << "\nAvailable Commands:\n"
          << "  create  - Create a new poll\n"
          << "  vote    - Cast a vote in a poll\n"
          << "  stats   - Show poll statistics\n"
          << "  list    - List all polls\n"
          << "  undo    - Undo last vote in a poll\n"
          << "  delete  - Delete a poll\n"
          << "  export  - Export poll results to CSV 📄\n"
          << "  exit    - Exit the program\n> ";

        std::cin >> command;

        if (command == "create") {
            std::string name;
            int count;
            std::vector<std::string> options;
        
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // flush leftover input
            std::cout << "Poll name: ";
            std::getline(std::cin, name);  // now supports spaces
        
            std::cout << "Number of options: ";
            if (!(std::cin >> count) || count <= 0) {
                std::cout << "❌ Invalid number of options. Try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
            for (int i = 0; i < count; ++i) {
                std::string opt;
                std::cout << "Option " << i << ": ";
                std::getline(std::cin, opt);
                if (opt.empty()) {
                    std::cout << "❌ Option text cannot be empty. Try again.\n";
                    --i;
                    continue;
                }
                options.push_back(opt);
            }
        pc.createPoll(name, options);
    
        } else if (command == "vote") {
            auto polls = pc.listPolls();
        
            if (polls.empty()) {
                std::cout << "⚠️ No polls available to vote on.\n";
                continue;
            }
        
            std::cout << "Select a poll to vote in:\n";
            for (size_t i = 0; i < polls.size(); ++i) {
                std::cout << "  " << i << ". " << polls[i] << "\n";
            }
        
            std::cout << "Enter poll number: ";
            int pollIndex;
            if (!(std::cin >> pollIndex) || pollIndex < 0 || pollIndex >= (int)polls.size()) {
                std::cout << "❌ Invalid poll selection. Try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        
            std::string selectedPoll = polls[pollIndex];
        
            // ⛔ Do not show stats yet — just show the options
            std::cout << "\nOptions for \"" << selectedPoll << "\":\n";
        
            const auto& manager = pc.getPollManager(selectedPoll);
            for (int i = 0; i < manager.optionCount(); ++i) {
                std::cout << "  " << i << ". " << manager.getOptionLabel(i) << "\n";
            }
        
            std::cout << "Enter option index to vote for: ";
            int optionIndex;
            std::cin >> optionIndex;
        
            pc.castVote(selectedPoll, optionIndex);
        
            std::cout << "\n🗳️ Updated Results:\n";
        pc.showStats(selectedPoll);
    
        } else if (command == "stats") {
            auto polls = pc.listPolls();
        
            if (polls.empty()) {
                std::cout << "⚠️ No polls available.\n";
                continue;
            }
        
            std::cout << "Select a poll to view stats:\n";
            for (size_t i = 0; i < polls.size(); ++i) {
                std::cout << "  " << i << ". " << polls[i] << "\n";
            }
        
            std::cout << "Enter poll number: ";
            int pollIndex;
            if (!(std::cin >> pollIndex) || pollIndex < 0 || pollIndex >= (int)polls.size()) {
                std::cout << "❌ Invalid selection. Try again.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        
            std::string selectedPoll = polls[pollIndex];
        pc.showStats(selectedPoll);

        } else if (command == "undo") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                std::cout << "⚠️ No polls available.\n";
                continue;
            }
        
            std::cout << "Select a poll to undo vote from:\n";
            for (size_t i = 0; i < polls.size(); ++i)
                std::cout << "  " << i << ". " << polls[i] << "\n";
        
            std::cout << "Enter poll number: ";
            int index;
            std::cin >> index;
        
            if (index < 0 || index >= (int)polls.size()) {
                std::cout << "❌ Invalid selection.\n";
                continue;
            }
        pc.undoVote(polls[index]);

        } else if (command == "list") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                std::cout << "No polls available.\n";
            } else {
                std::cout << "Available Polls:\n";
                for (const auto& name : polls)
                    std::cout << "- " << name << "\n";
            }
        } else if (command == "delete") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                std::cout << "⚠️ No polls to delete.\n";
                continue;
            }
        
            std::cout << "Select a poll to delete:\n";
            for (size_t i = 0; i < polls.size(); ++i)
                std::cout << "  " << i << ". " << polls[i] << "\n";
        
            std::cout << "Enter poll number: ";
            int index;
            std::cin >> index;
        
            if (index < 0 || index >= (int)polls.size()) {
                std::cout << "❌ Invalid selection.\n";
                continue;
            }
        
        pc.deletePoll(polls[index]);

        } else if (command == "export") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                std::cout << "⚠️  No polls available to export.\n";
                continue;
            }
        
            std::cout << "Select a poll to export:\n";
            for (size_t i = 0; i < polls.size(); ++i) {
                std::cout << "  " << i << ". " << polls[i] << "\n";
            }
        
            std::cout << "Enter poll number: ";
            size_t index;
            std::cin >> index;
        
            if (index >= polls.size()) {
                std::cout << "❌ Invalid poll number.\n";
                continue;
            }
        
            std::string filename;
            std::cout << "Filename (e.g., results.csv): ";
            std::cin >> filename;
        
        pc.exportPollToCSV(polls[index], filename);

        } else if (command == "exit") {
            std::cout << "👋 Exiting. Goodbye!\n";
            break;
        
        } else {
            std::cout << "❌ Unknown command. Please try again.\n";
        }
    }

    return 0;
}