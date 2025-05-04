// Survey.h
#pragma once

#include <string>
#include <vector>
#include <memory>
#include "PollManager.h"

class Survey {
private:
    std::string title;
    std::vector<std::string> questions;
    std::vector<std::unique_ptr<PollManager>> pollManagers;

public:
    Survey(const std::string& title);

    void addQuestion(const std::string& questionText, const std::vector<std::string>& options);
    void takeSurvey();
    void viewSurveyResults() const;
    void exportSurveyToCSV(const std::string& filename) const;

    std::string getTitle() const;
    int questionCount() const;
    std::string getQuestionText(int index) const;
    const PollManager& getPollManager(int index) const;
};