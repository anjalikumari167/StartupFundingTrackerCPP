#include <iostream>
#include "StartupManager.h"
#include "Utils.h"

using namespace std;

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
    cout << "10. Exit\n";
}

int main() {
    StartupManager manager;
    manager.loadSampleData();

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
            case 10: cout << "Goodbye!\n";        break;
            default: cout << "Invalid choice. Try 1-10.\n";
        }
    } while (choice != 10);

    return 0;
}
