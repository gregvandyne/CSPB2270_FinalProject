#include <iostream>
#include <limits>
#include "PollCollection.h"
#include "Survey.h"
#include "UIHelper.h"

int main() {
    PollCollection pc;
    std::vector<Survey> surveys;

    UIHelper::printBanner("\U0001F5F3️  Welcome to the Real-Time Voting System!");

    while (true) {
        UIHelper::printMenu({
            "create       - Create a new poll",
            "vote         - Cast a vote in a poll",
            "stats        - Show poll statistics",
            "list         - List all polls",
            "undo         - Undo last vote in a poll",
            "delete       - Delete a poll",
            "export       - Export poll results to CSV \U0001F4C4",
            "survey_new   - Create a new survey",
            "survey_take  - Take a survey",
            "survey_stats - View survey results",
            "survey_export- Export survey results to CSV \U0001F4C4",
            "exit         - Exit the program"
        });

        std::string command = UIHelper::prompt("Enter command");

        if (command == "exit") {
            std::cout << "👋 Exiting. Goodbye!\n";
            break;
        } else if (command == "create") {
            std::string name = UIHelper::prompt("Poll name");
            int count = UIHelper::promptInt("Number of options");
            std::vector<std::string> options;
            for (int i = 0; i < count; ++i) {
                options.push_back(UIHelper::prompt("Option " + std::to_string(i)));
            }
            pc.createPoll(name, options);
        } else if (command == "vote") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                UIHelper::printWarning("No polls available to vote on.");
                continue;
            }
            int pollIndex = UIHelper::selectFromList("Select a poll to vote in:", polls);
            std::string selectedPoll = polls[pollIndex];

            const auto& manager = pc.getPollManager(selectedPoll);
            std::vector<std::string> labels;
            for (int i = 0; i < manager.optionCount(); ++i) {
                labels.push_back(manager.getOptionLabel(i));
            }
            int optionIndex = UIHelper::selectFromList("Options for \"" + selectedPoll + "\":", labels);

            pc.castVote(selectedPoll, optionIndex);
            std::cout << "\n\U0001F5F3️ Updated Results:\n";
            pc.showStats(selectedPoll);
        } else if (command == "stats") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                UIHelper::printWarning("No polls available.");
                continue;
            }
            int pollIndex = UIHelper::selectFromList("Select a poll to view stats:", polls);
            pc.showStats(polls[pollIndex]);
        } else if (command == "undo") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                UIHelper::printWarning("No polls available.");
                continue;
            }
            int pollIndex = UIHelper::selectFromList("Select a poll to undo vote from:", polls);
            pc.undoVote(polls[pollIndex]);
        } else if (command == "list") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                UIHelper::printWarning("No polls available.");
            } else {
                UIHelper::printList("Available Polls:", polls);
            }
        } else if (command == "delete") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                UIHelper::printWarning("No polls to delete.");
                continue;
            }
            int pollIndex = UIHelper::selectFromList("Select a poll to delete:", polls);
            pc.deletePoll(polls[pollIndex]);
        } else if (command == "export") {
            auto polls = pc.listPolls();
            if (polls.empty()) {
                UIHelper::printWarning("No polls available to export.");
                continue;
            }
            int pollIndex = UIHelper::selectFromList("Select a poll to export:", polls);
            std::string filename = UIHelper::prompt("Filename (e.g., results.csv)");
            pc.exportPollToCSV(polls[pollIndex], filename);
        } else if (command == "survey_new") {
            std::string title = UIHelper::prompt("Survey title");
            Survey s(title);
            int qCount = UIHelper::promptInt("Number of questions");
            for (int i = 0; i < qCount; ++i) {
                std::string qText = UIHelper::prompt("Question " + std::to_string(i + 1));
                int oCount = UIHelper::promptInt("Number of options for this question");
                std::vector<std::string> options;
                for (int j = 0; j < oCount; ++j) {
                    options.push_back(UIHelper::prompt("Option " + std::to_string(j)));
                }
                s.addQuestion(qText, options);
            }
            surveys.push_back(std::move(s));
            std::cout << "✅ Survey created successfully.\n";
        } else if (command == "survey_take") {
            if (surveys.empty()) {
                UIHelper::printWarning("No surveys available.");
                continue;
            }
            std::vector<std::string> titles;
            for (const auto& s : surveys) titles.push_back(s.getTitle());
            int idx = UIHelper::selectFromList("Select a survey to take:", titles);
            surveys[idx].takeSurvey();
        
            // 🛠️ FIX: Flush buffer after survey completion
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');        
        } else if (command == "survey_stats") {
            if (surveys.empty()) {
                UIHelper::printWarning("No surveys available.");
                continue;
            }
            std::vector<std::string> titles;
            for (const auto& s : surveys) titles.push_back(s.getTitle());
            int idx = UIHelper::selectFromList("Select a survey to view stats:", titles);
            surveys[idx].viewSurveyResults();
        } else if (command == "survey_export") {
            if (surveys.empty()) {
                UIHelper::printWarning("No surveys available.");
                continue;
            }
            std::vector<std::string> titles;
            for (const auto& s : surveys) titles.push_back(s.getTitle());
            int idx = UIHelper::selectFromList("Select a survey to export:", titles);
            std::string filename = UIHelper::prompt("Filename (e.g., survey.csv)");
            surveys[idx].exportSurveyToCSV(filename);
        } else {
            std::cout << "❌ Unknown command. Please try again.\n";
        }
    }
    return 0;
}
