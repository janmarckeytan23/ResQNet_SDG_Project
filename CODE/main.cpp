#include "FloodMonitor.h"
#include <iostream>
#include <string>

int main() {
    FloodMonitor monitor;

    monitor.displayHeader();

    // FR1 — Auto-load database on startup
    if (!monitor.loadFromFile("database.txt"))
        monitor.loadFromFile("../INPUT_DATA/database.txt");

    int choice;

    do {
        monitor.displayMenu();
        std::cout << "Action Required: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            choice = -1;
        }

        switch (choice) {

            case 1:
                monitor.logFloodReports();
                break;

            case 2:
                if (monitor.isDataLoaded())
                    monitor.generateRiskAssessment();
                else
                    std::cout << "\n[!] ALERT: No flood data. Please add a report first (Option 1).\n";
                break;

            case 3:
                if (monitor.isDataLoaded())
                    monitor.suggestSafeRoutes();
                else
                    std::cout << "\n[!] ALERT: Cannot map routes without flood data.\n";
                break;

            case 4: {
                int sub;
                std::cout << "\nCRUD Menu: [1] View  [2] Add  [3] Update  [4] Delete: ";
                if (!(std::cin >> sub)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "[!] Invalid selection.\n";
                    break;
                }

                if (sub == 1) {
                    monitor.viewZones();
                } else if (sub == 2) {
                    std::string name; double lvl;
                    std::cout << "New zone name: ";
                    std::cin.ignore();
                    std::getline(std::cin, name);
                    std::cout << "Initial flood level (cm): ";
                    std::cin >> lvl;
                    if (monitor.addZone(name, lvl))
                        std::cout << "[OK] Zone added.\n";
                    else
                        std::cout << "[!] Failed. Check that level is 0-500 cm.\n";
                } else if (sub == 3) {
                    monitor.viewZones();
                    int idx; double lvl;
                    std::cout << "Zone number to update: "; std::cin >> idx;
                    std::cout << "New flood level (cm) : "; std::cin >> lvl;
                    if (monitor.updateZone(idx, lvl))
                        std::cout << "[OK] Zone updated.\n";
                    else
                        std::cout << "[!] Update failed.\n";
                } else if (sub == 4) {
                    monitor.viewZones();
                    int idx;
                    std::cout << "Zone number to delete: "; std::cin >> idx;
                    if (monitor.deleteZone(idx))
                        std::cout << "[OK] Zone deleted.\n";
                    else
                        std::cout << "[!] Delete failed.\n";
                } else {
                    std::cout << "[!] Invalid CRUD selection.\n";
                }
                break;
            }

            case 5:
                monitor.searchById();
                break;

            case 6:
                monitor.searchByName();
                break;

            case 7:
                monitor.showStatsDashboard();
                break;

            case 0:
                monitor.exitAndSave();
                break;

            default:
                std::cout << "\n[!] Invalid Selection. Please choose a valid system action.\n";
        }

    } while (choice != 0);

    return 0;
}
