#ifndef STARTUP_MANAGER_H
#define STARTUP_MANAGER_H

#include <vector>
#include <string>
#include "Startup.h"

// Owns all startups and does all the operations on them.
//
// Later upgrades (keep main.cpp unchanged, only add here):
//   - Hashing : add unordered_map<int,int> idIndex  -> O(1) findIndexById
//   - Sorting : add sortByFunding()
//   - Heap    : add showTopN(int n) using priority_queue
//   - Trie    : add a Trie member for name autocomplete
class StartupManager {
private:
    std::vector<Startup> startups;
    int nextId;                          // auto-increment ID

    // Linear search by ID. Returns index or -1. (Replace with hashing later.)
    int findIndexById(int id) const;

    // Prints every startup in the given list (used by filter and sort).
    void printList(const std::vector<Startup>& list) const;

public:
    StartupManager();

    void loadSampleData();               // a few demo records
    void addStartup();
    void displayAll() const;
    void searchByName() const;           // linear search, partial + case-insensitive
    void updateStartup();
    void deleteStartup();

    // ---- Step 2 ----
    void searchBySector() const;         // exact match, case-insensitive
    void searchByStage() const;          // exact match, case-insensitive
    void sortByFunding() const;          // shows sorted COPY, original order kept
    void showHighestLowest() const;      // manual max / min scan
};

#endif
