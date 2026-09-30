#include <iostream>
#include "StartupManager.h"
#include "Utils.h"

using namespace std;

void printMenu() {
    cout << "\n================================\n";
    cout << "     STARTUP FUNDING TRACKER\n";
    cout << "================================\n";
    cout << "1. Add Startup\n";
    cout << "2. Display All Startups\n";
    cout << "3. Search Startup by Name\n";
    cout << "4. Update Startup\n";
    cout << "5. Delete Startup\n";
    cout << "6. Exit\n";
}

int main() {
    StartupManager manager;
    manager.loadSampleData();

    int choice;
    do {
        printMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1: manager.addStartup();     break;
            case 2: manager.displayAll();     break;
            case 3: manager.searchByName();   break;
            case 4: manager.updateStartup();  break;
            case 5: manager.deleteStartup();  break;
            case 6: cout << "Goodbye!\n";      break;
            default: cout << "Invalid choice. Try 1-6.\n";
        }
    } while (choice != 6);

    return 0;
}
