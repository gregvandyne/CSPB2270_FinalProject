#include <gtest/gtest.h>
#include "../FenwickTree.h"
#include "../PollManager.h"

// ---------- Fenwick Tree Tests ----------
TEST(FenwickTreeTest, BasicUpdateAndQuery) {
    FenwickTree tree(5);
    tree.update(1, 3);
    tree.update(2, 2);
    tree.update(3, 1);

    EXPECT_EQ(tree.query(1), 3);
    EXPECT_EQ(tree.query(2), 5);
    EXPECT_EQ(tree.query(3), 6);
}

TEST(FenwickTreeTest, RangeQuery) {
    FenwickTree tree(5);
    tree.update(1, 4);
    tree.update(2, 5);
    tree.update(3, 6);

    EXPECT_EQ(tree.rangeQuery(2, 3), 11); // 5 + 6
    EXPECT_EQ(tree.rangeQuery(1, 1), 4);
}

// ---------- Poll Manager Tests ----------
TEST(PollManagerTest, VoteCounting) {
    PollManager poll({"A", "B", "C"});

    poll.castVote(0);
    poll.castVote(0);
    poll.castVote(1);

    EXPECT_EQ(poll.totalVotes(), 3);
}

TEST(PollManagerTest, UndoVote) {
    PollManager poll({"A", "B"});
    poll.castVote(1);  // lastVoteIndex = 1
    poll.castVote(1);  // lastVoteIndex = 1
    poll.undoVote();   // undo the last vote for index 1

    EXPECT_EQ(poll.totalVotes(), 1);  // Should remove one vote
}
