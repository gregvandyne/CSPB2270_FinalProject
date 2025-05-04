#include <gtest/gtest.h>
#include "../PollCollection.h"

TEST(PollCollectionTest, CreateAndListPolls) {
    PollCollection pc;
    pc.createPoll("feedback", {"Yes", "No"});
    pc.createPoll("layout", {"A", "B", "C"});

    auto names = pc.listPolls();
    EXPECT_EQ(names.size(), 2);
    EXPECT_NE(std::find(names.begin(), names.end(), "feedback"), names.end());
    EXPECT_NE(std::find(names.begin(), names.end(), "layout"), names.end());
}

TEST(PollCollectionTest, VoteAndGetStats) {
    PollCollection pc;
    pc.createPoll("tools", {"Helpful", "Not Helpful"});

    // Cast 2 votes to "Helpful", 1 vote to "Not Helpful"
    pc.castVote("tools", 0);
    pc.castVote("tools", 0);
    pc.castVote("tools", 1);

    testing::internal::CaptureStdout();
    pc.showStats("tools");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Helpful: 2"), std::string::npos);
    EXPECT_NE(output.find("Not Helpful: 1"), std::string::npos);
    EXPECT_NE(output.find("Total votes: 3"), std::string::npos);
}

TEST(PollCollectionTest, HandleMissingPollGracefully) {
    PollCollection pc;

    testing::internal::CaptureStdout();
    bool success = pc.castVote("nonexistent", 1);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(success);
    EXPECT_NE(output.find("Poll \"nonexistent\" not found"), std::string::npos);
}
