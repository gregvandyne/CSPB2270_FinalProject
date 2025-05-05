# Real-Time Voting & Survey CLI System

## 📄 Overview

Welcome to **Oler's Real-Time Voting System**, a colorful, dynamic, and animated Command Line Interface (CLI) app for conducting polls and surveys. Built with C++ and designed to be both fun and educational, this system lets users:

* Create and manage polls
* Cast and undo votes
* View and export statistics
* Create and take surveys (a series of multiple questions)
* Export surveys to a CSV

This project integrates several C++ concepts like dynamic memory management, input handling, file I/O, and the Fenwick Tree

---

## ⚙️ How to Build & Run

### 1. Prerequisites

Make sure you have CMake and a C++ compiler (like g++) installed.

### 2. Building the App

```bash
rm -rf build
mkdir build && cd build
cmake ..
make
```

### 3. Running

To run the app:

```bash
./voting_app
```

To run the tests:

```bash
./run_tests
```

---

## 🌐 App Features

### 📊 Polls

* `create` - Define a new poll with any number of options.
* `vote` - Select a poll and cast a vote.
* `stats` - View real-time statistics.
* `undo` - Revert the last vote.
* `delete` - Remove a poll.
* `export` - Save poll results as a CSV.

### 📖 Surveys

* `survey_new` - Create a survey with multiple questions.
* `survey_take` - Answer each question in sequence.
* `survey_stats` - View stats for all survey questions.
* `survey_export` - Export results to a CSV.

### 🎉 Interface

* Fully styled with colors, emojis, and ASCII banners
* Validates all input types robustly (numbers, strings, out-of-range choices)
* Animations in the CLI to improve the UX

---

## 🪡 Fenwick Tree: Why & How

### What is a Fenwick Tree?

A **Fenwick Tree**, also called a Binary Indexed Tree (BIT), is a data structure that allows us to **efficiently perform range sum queries and point updates** on an array.

### Why Use It Here?

In this app, we track the number of votes each poll option gets. Instead of recalculating totals every time someone wants to see stats, we use a Fenwick Tree to keep the totals up to date.

This lets us:

* Update votes in `O(log n)`
* Get the number of votes for any option in `O(log n)`
* Compute total votes in `O(log n)`

### Where is it used?

* Every `PollManager` instance uses a `FenwickTree votes` member.
* `castVote(index)` calls `votes.update(index + 1, 1)`
* `undoVote()` subtracts from the vote count using the tree.
* `displayStats()` queries the tree to get per-option and total votes.

By offsetting indices (+1), we keep things consistent with the 1-based indexing required by Fenwick Trees.

---

## 🚀 Behind the Scenes

### Key Classes

* **PollManager**: Manages one poll
* **PollCollection**: Holds and manages all polls
* **Survey**: Represents a multi-question survey
* **FenwickTree**: Core data structure for vote counting
* **UIHelper**: Makes the CLI stylish and friendly

---

## 💪 Sample Commands

```text
> create
Poll name: Best programming language?
Number of options: 3
Option 0: C++
Option 1: Python
Option 2: JavaScript

> vote
Select a poll to vote in:
  0. Best programming language?
Enter poll number: 0
Options for "Best programming language?":
  0. C++
  1. Python
  2. JavaScript
Enter option index to vote for: 1

📈 Updated Results:
 0. C++: 0 votes (0.00%)
 1. Python: 1 votes (100.00%)
 2. JavaScript: 0 votes (0.00%)
```

---

## 🚀 Future Improvements

* User login and saving session data
* Export entire app state (polls + surveys) to a file
* Import polls/surveys from a file
* Web UI powered by C++ backend (maybe??)
