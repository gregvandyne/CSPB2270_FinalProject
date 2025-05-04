#include "Survey.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Survey::Survey(const std::string& title) : title(title) {}

void Survey::addQuestion(const std::string& questionText, const std::vector<std::string>& options) {
    questions.push_back(questionText);
    pollManagers.push_back(std::make_unique<PollManager>(options));
}

void Survey::takeSurvey() {
    for (size_t i = 0; i < questions.size(); ++i) {
        std::cout << "\nQuestion " << (i + 1) << ": " << questions[i] << "\n";
        auto& manager = pollManagers[i];

        for (int j = 0; j < manager->optionCount(); ++j) {
            std::cout << "  " << j << ". " << manager->getOptionLabel(j) << "\n";
        }

        int answer;
        std::cout << "Your answer (index): ";
        std::cin >> answer;

        manager->castVote(answer);
    }
}

void Survey::viewSurveyResults() const {
    for (size_t i = 0; i < questions.size(); ++i) {
        std::cout << "\nResults for: " << questions[i] << "\n";
        pollManagers[i]->displayStats();
    }
}

void Survey::exportSurveyToCSV(const std::string& baseFilename) const {
    for (size_t i = 0; i < questions.size(); ++i) {
        std::string filename = baseFilename + "_q" + std::to_string(i + 1) + ".csv";
        pollManagers[i]->exportToCSV(filename);
    }
}

std::string Survey::getTitle() const {
    return title;
}

int Survey::questionCount() const {
    return questions.size();
}

std::string Survey::getQuestionText(int index) const {
    return index >= 0 && index < (int)questions.size() ? questions[index] : "[Invalid Question]";
}

const PollManager& Survey::getPollManager(int index) const {
    return *pollManagers.at(index);
}
