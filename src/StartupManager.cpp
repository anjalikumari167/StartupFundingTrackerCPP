#include "StartupManager.h"
#include "Utils.h"
#include <iostream>
#include <queue>        // priority_queue (heap)
#include <algorithm>   // std::sort
#include <iomanip>
#include <fstream>    // ifstream, ofstream
#include <sstream>    // stringstream

using namespace std;

// ---------- small helpers (only used in this file) ----------

// Splits "a|b|c" into {"a","b","c"}.
static vector<string> splitLine(const string& line, char delim) {
    vector<string> parts;
    string item;
    stringstream ss(line);
    while (getline(ss, item, delim)) parts.push_back(item);
    // getline drops an empty last field, so add it back
    if (!line.empty() && line.back() == delim) parts.push_back("");
    return parts;
}

// '|' is our separator, so it must not appear inside a field.
static string cleanField(string s) {
    for (char& c : s) {
        if (c == '|') c = '/';
    }
    return s;
}

StartupManager::StartupManager() : nextId(1), unsaved(false) {}

int StartupManager::findIndexById(int id) const {
    // Hash map lookup: O(1) on average (it was a linear O(n) loop before).
    auto it = idIndex.find(id);
    if (it == idIndex.end()) return -1;
    return it->second;
}

void StartupManager::rebuildIndexes() {
    idIndex.clear();
    trie.clear();
    for (size_t i = 0; i < startups.size(); i++) {
        idIndex[startups[i].getId()] = static_cast<int>(i);
        trie.insert(startups[i].getName());
    }
}

void StartupManager::loadSampleData() {
    // Demo values only - replace with real public data you collect yourself.
    startups.push_back(Startup(nextId++, "Alpha Health", "HealthTech", "Seed", 12.5, "Bengaluru", "A. Sharma", "Demo Ventures"));
    startups.push_back(Startup(nextId++, "Beta Pay", "FinTech", "Series A", 85.0, "Mumbai", "R. Mehta", "Sample Capital"));
    startups.push_back(Startup(nextId++, "Gamma Learn", "EdTech", "Series B", 210.0, "Delhi", "S. Gupta", "Example Fund"));
    rebuildIndexes();
    unsaved = true;
}

void StartupManager::addStartup() {
    cout << "\n--- Add Startup ---\n";
    string name     = readNonEmpty("Name     : ");
    string sector   = readNonEmpty("Sector   : ");
    string stage    = readNonEmpty("Stage    : ");
    double funding  = readAmount("Funding (Rs Cr): ");
    string city     = readNonEmpty("City     : ");
    string founder  = readNonEmpty("Founder  : ");
    string investor = readNonEmpty("Investor : ");

    startups.push_back(Startup(nextId, name, sector, stage, funding, city, founder, investor));
    idIndex[nextId] = static_cast<int>(startups.size()) - 1;   // keep hash map in sync
    trie.insert(name);                                         // keep trie in sync
    cout << "Added successfully with ID " << nextId << ".\n";
    nextId++;
    unsaved = true;
}

void StartupManager::displayAll() const {
    cout << "\n--- All Startups (" << startups.size() << ") ---\n";
    if (startups.empty()) {
        cout << "No startups yet.\n";
        return;
    }
    for (const Startup& s : startups) s.display();
    cout << "--------------------------------------\n";
}

void StartupManager::searchByName() const {
    cout << "\n--- Search by Name ---\n";
    string key = toLower(readNonEmpty("Enter name (or part of it): "));

    int found = 0;
    for (const Startup& s : startups) {
        if (toLower(s.getName()).find(key) != string::npos) {
            s.display();
            found++;
        }
    }
    if (found == 0) cout << "No startup found.\n";
    else cout << "--------------------------------------\n" << found << " match(es).\n";
}

void StartupManager::updateStartup() {
    cout << "\n--- Update Startup ---\n";
    int id = readInt("Enter Startup ID: ");
    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "No startup with that ID.\n";
        return;
    }

    Startup& s = startups[idx];     // reference: changes affect the real record
    s.display();
    cout << "Press Enter to keep the current value.\n";

    string v;
    v = readLine("New name     : "); if (!v.empty()) s.setName(v);
    v = readLine("New sector   : "); if (!v.empty()) s.setSector(v);
    v = readLine("New stage    : "); if (!v.empty()) s.setStage(v);

    while (true) {
        v = readLine("New funding (Rs Cr): ");
        if (v.empty()) break;
        double amt;
        if (parseAmount(v, amt)) { s.setFundingCr(amt); break; }
        cout << "  Please enter a valid amount.\n";
    }

    v = readLine("New city     : "); if (!v.empty()) s.setCity(v);
    v = readLine("New founder  : "); if (!v.empty()) s.setFounder(v);
    v = readLine("New investor : "); if (!v.empty()) s.setInvestor(v);

    rebuildIndexes();    // the name may have changed, so refresh the trie
    unsaved = true;
    cout << "Updated successfully.\n";
}

void StartupManager::deleteStartup() {
    cout << "\n--- Delete Startup ---\n";
    int id = readInt("Enter Startup ID: ");
    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "No startup with that ID.\n";
        return;
    }
    startups.erase(startups.begin() + idx);
    rebuildIndexes();    // erase shifts positions, so the hash map must be rebuilt
    unsaved = true;
    cout << "Deleted.\n";
}

// ===================== STEP 2 =====================

void StartupManager::printList(const vector<Startup>& list) const {
    for (const Startup& s : list) s.display();
    cout << "--------------------------------------\n";
}

void StartupManager::searchBySector() const {
    cout << "\n--- Search by Sector ---\n";
    string key = toLower(readNonEmpty("Enter sector (e.g. FinTech): "));

    vector<Startup> matches;
    double total = 0;
    for (const Startup& s : startups) {
        if (toLower(s.getSector()) == key) {
            matches.push_back(s);
            total += s.getFundingCr();
        }
    }

    if (matches.empty()) {
        cout << "No startups found in that sector.\n";
        return;
    }
    printList(matches);
    cout << matches.size() << " startup(s), total funding: Rs "
         << fixed << setprecision(2) << total << " Cr\n";
}

void StartupManager::searchByStage() const {
    cout << "\n--- Search by Funding Stage ---\n";
    string key = toLower(readNonEmpty("Enter stage (e.g. Seed, Series A): "));

    vector<Startup> matches;
    double total = 0;
    for (const Startup& s : startups) {
        if (toLower(s.getStage()) == key) {
            matches.push_back(s);
            total += s.getFundingCr();
        }
    }

    if (matches.empty()) {
        cout << "No startups found at that stage.\n";
        return;
    }
    printList(matches);
    cout << matches.size() << " startup(s), total funding: Rs "
         << fixed << setprecision(2) << total << " Cr\n";
}

void StartupManager::sortByFunding() const {
    cout << "\n--- Sort by Funding ---\n";
    if (startups.empty()) {
        cout << "No startups yet.\n";
        return;
    }

    cout << "1. High to Low\n2. Low to High\n";
    int order = readInt("Choose order: ");
    if (order != 1 && order != 2) {
        cout << "Invalid choice.\n";
        return;
    }

    // Sort a COPY so the original list (and its order) stays unchanged.
    vector<Startup> sorted = startups;

    // The lambda compares two startups. 'const Startup&' avoids copying.
    if (order == 1) {
        sort(sorted.begin(), sorted.end(),
             [](const Startup& a, const Startup& b) {
                 return a.getFundingCr() > b.getFundingCr();
             });
    } else {
        sort(sorted.begin(), sorted.end(),
             [](const Startup& a, const Startup& b) {
                 return a.getFundingCr() < b.getFundingCr();
             });
    }

    printList(sorted);
}

void StartupManager::showHighestLowest() const {
    cout << "\n--- Highest and Lowest Funded ---\n";
    if (startups.empty()) {
        cout << "No startups yet.\n";
        return;
    }

    // Manual scan: start with the first one, compare with the rest.
    // This is the classic max/min pattern - O(n).
    int maxIdx = 0, minIdx = 0;
    for (size_t i = 1; i < startups.size(); i++) {
        if (startups[i].getFundingCr() > startups[maxIdx].getFundingCr()) maxIdx = i;
        if (startups[i].getFundingCr() < startups[minIdx].getFundingCr()) minIdx = i;
    }

    cout << "HIGHEST FUNDED:\n";
    startups[maxIdx].display();
    cout << "\nLOWEST FUNDED:\n";
    startups[minIdx].display();
    cout << "--------------------------------------\n";
}

// ===================== STEP 3 =====================

bool StartupManager::saveToFile(const string& filename) {
    ofstream out(filename);              // creates the file / overwrites it
    if (!out) {
        cout << "Could not open " << filename << " for writing.\n";
        return false;
    }

    out << fixed << setprecision(2);     // funding always saved as 85.00
    for (const Startup& s : startups) {
        out << s.getId() << '|'
            << cleanField(s.getName()) << '|'
            << cleanField(s.getSector()) << '|'
            << cleanField(s.getStage()) << '|'
            << s.getFundingCr() << '|'
            << cleanField(s.getCity()) << '|'
            << cleanField(s.getFounder()) << '|'
            << cleanField(s.getInvestor()) << '\n';
    }

    if (!out) {
        cout << "Error while writing to " << filename << ".\n";
        return false;
    }
    unsaved = false;
    cout << "Saved " << startups.size() << " startup(s) to " << filename << ".\n";
    return true;
}

bool StartupManager::loadFromFile(const string& filename) {
    ifstream in(filename);
    if (!in) return false;               // file not found (e.g. first run)

    startups.clear();
    nextId = 1;

    string line;
    int skipped = 0;
    while (getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();  // Windows line ending
        if (line.empty()) continue;

        vector<string> f = splitLine(line, '|');
        if (f.size() != 8) {             // wrong number of fields -> bad line
            skipped++;
            continue;
        }

        try {
            int id = stoi(f[0]);
            double funding = stod(f[4]);
            startups.push_back(Startup(id, f[1], f[2], f[3], funding, f[5], f[6], f[7]));
            if (id >= nextId) nextId = id + 1;   // keep IDs unique after loading
        } catch (...) {
            skipped++;                   // id or funding was not a number
        }
    }

    rebuildIndexes();
    unsaved = false;
    cout << "Loaded " << startups.size() << " startup(s) from " << filename << ".\n";
    if (skipped > 0) cout << "Warning: " << skipped << " bad line(s) were skipped.\n";
    return true;
}

bool StartupManager::hasUnsavedChanges() const {
    return unsaved;
}

// ===================== STEP 4 =====================

// 1) HASH MAP: find a startup by ID in O(1).
void StartupManager::findById() const {
    cout << "\n--- Find by ID ---\n";
    int id = readInt("Enter Startup ID: ");
    int idx = findIndexById(id);
    if (idx == -1) {
        cout << "No startup with that ID.\n";
        return;
    }
    startups[idx].display();
    cout << "--------------------------------------\n";
}

// 2) HEAP: top N funded startups.
//    priority_queue is a max-heap, so the biggest funding is always on top.
//    Push everything: O(n log n). Pop N times: O(N log n).
void StartupManager::showTopN() const {
    cout << "\n--- Top N Funded Startups ---\n";
    if (startups.empty()) {
        cout << "No startups yet.\n";
        return;
    }

    int n = readInt("How many (N)? ");
    if (n <= 0) {
        cout << "N must be at least 1.\n";
        return;
    }
    if (n > static_cast<int>(startups.size())) n = static_cast<int>(startups.size());

    // pair = (funding, index in vector). A pair compares by funding first.
    priority_queue<pair<double, int>> heap;
    for (size_t i = 0; i < startups.size(); i++) {
        heap.push({startups[i].getFundingCr(), static_cast<int>(i)});
    }

    for (int rank = 1; rank <= n; rank++) {
        int idx = heap.top().second;    // biggest funding left
        heap.pop();
        cout << "#" << rank << "\n";
        startups[idx].display();
    }
    cout << "--------------------------------------\n";
}

// 3) TRIE: suggest names that start with what you type.
void StartupManager::autocompleteName() const {
    cout << "\n--- Name Autocomplete ---\n";
    string prefix = readNonEmpty("Type the start of a name: ");

    vector<string> results = trie.autocomplete(prefix, 10);
    if (results.empty()) {
        cout << "No names start with \"" << prefix << "\".\n";
        return;
    }
    cout << "Suggestions:\n";
    for (size_t i = 0; i < results.size(); i++) {
        cout << "  " << (i + 1) << ". " << results[i] << "\n";
    }
}
