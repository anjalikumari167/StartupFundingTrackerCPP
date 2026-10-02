#include <iostream>
#include <string>
#include "StartupManager.h"
#include "Utils.h"

using namespace std;

// The data file is created in the folder you run the program from.
const string DATA_FILE = "startups.txt";

void printMenu() {
    cout << "\n================================\n";
    cout << "     STARTUP FUNDING TRACKER\n";
    cout << "================================\n";
    cout << " 1. Add Startup\n";
    cout << " 2. Display All Startups\n";
    cout << " 3. Search by Name\n";
    cout << " 4. Search by Sector\n";
    cout << " 5. Search by Funding Stage\n";
    cout << " 6. Sort by Funding Amount\n";
    cout << " 7. Highest / Lowest Funded\n";
    cout << " 8. Update Startup\n";
    cout << " 9. Delete Startup\n";
    cout << "10. Save Data\n";
    cout << "11. Exit\n";
}

int main() {
    StartupManager manager;

    // Try to load saved data. If there is no file yet, start with sample data.
    if (!manager.loadFromFile(DATA_FILE)) {
        cout << "No saved file found. Loading sample data.\n";
        manager.loadSampleData();
    }

    int choice;
    do {
        printMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:  manager.addStartup();        break;
            case 2:  manager.displayAll();        break;
            case 3:  manager.searchByName();      break;
            case 4:  manager.searchBySector();    break;
            case 5:  manager.searchByStage();     break;
            case 6:  manager.sortByFunding();     break;
            case 7:  manager.showHighestLowest(); break;
            case 8:  manager.updateStartup();     break;
            case 9:  manager.deleteStartup();     break;
            case 10: manager.saveToFile(DATA_FILE); break;
            case 11:
                if (manager.hasUnsavedChanges()) {
                    string ans = toLower(readLine("You have unsaved changes. Save before exit? (y/n): "));
                    if (!ans.empty() && ans[0] == 'y') manager.saveToFile(DATA_FILE);
                }
                cout << "Goodbye!\n";
                break;
            default: cout << "Invalid choice. Try 1-11.\n";
        }
    } while (choice != 11);

    return 0;
}
