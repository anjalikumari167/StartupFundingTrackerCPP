#ifndef STARTUP_MANAGER_H
#define STARTUP_MANAGER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "Startup.h"
#include "Trie.h"

// Owns all startups and does all the operations on them.
//
// Data structures used:
//   vector<Startup>              - the main storage
//   unordered_map<int,int>       - hash map: startup ID -> position in the vector (O(1) lookup)
//   priority_queue (in .cpp)     - heap for Top-N funded
//   Trie                         - name autocomplete
class StartupManager {
private:
    std::vector<Startup> startups;
    int nextId;                          // auto-increment ID
    bool unsaved;                        // true if data changed since last save

    std::unordered_map<int, int> idIndex;   // ID -> index in 'startups'
    Trie trie;                              // all startup names

    // O(1) lookup using the hash map. Returns index or -1.
    int findIndexById(int id) const;

    // Rebuilds idIndex and trie from 'startups'.
    // Needed after delete / update / load, because positions or names changed.
    void rebuildIndexes();

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
    void searchBySector() const;
    void searchByStage() const;
    void sortByFunding() const;
    void showHighestLowest() const;

    // ---- Step 3: file handling ----
    // Format: id|name|sector|stage|fundingCr|city|founder|investor
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename);
    bool hasUnsavedChanges() const;

    // ---- Step 4: DSA ----
    void findById() const;               // hash map lookup
    void showTopN() const;               // heap
    void autocompleteName() const;       // trie
};

#endif
