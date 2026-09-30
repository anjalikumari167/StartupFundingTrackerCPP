#include "StartupManager.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>   // std::sort
#include <iomanip>

using namespace std;

StartupManager::StartupManager() : nextId(1) {}

int StartupManager::findIndexById(int id) const {
    for (size_t i = 0; i < startups.size(); i++) {
        if (startups[i].getId() == id) return static_cast<int>(i);
    }
    return -1;
}

void StartupManager::loadSampleData() {
    // Demo values only - replace with real public data you collect yourself.
    startups.push_back(Startup(nextId++, "Alpha Health", "HealthTech", "Seed", 12.5, "Bengaluru", "A. Sharma", "Demo Ventures"));
    startups.push_back(Startup(nextId++, "Beta Pay", "FinTech", "Series A", 85.0, "Mumbai", "R. Mehta", "Sample Capital"));
    startups.push_back(Startup(nextId++, "Gamma Learn", "EdTech", "Series B", 210.0, "Delhi", "S. Gupta", "Example Fund"));
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
    cout << "Added successfully with ID " << nextId << ".\n";
    nextId++;
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
