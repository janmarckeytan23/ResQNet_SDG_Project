#ifndef FLOODMONITOR_H
#define FLOODMONITOR_H

#include "FloodZone.h"
#include "CriticalZone.h"
#include "MonitoredZone.h"
#include <vector>
#include <string>

// ============================================================
// Class   : FloodMonitor
// Purpose : Manager class. Uses a vector of FloodZone POINTERS
//           so it can store FloodZone, CriticalZone, and
//           MonitoredZone objects — enabling POLYMORPHISM.
//           Owns all memory and deletes pointers on exit.
// ============================================================
class FloodMonitor {
private:
    std::vector<FloodZone*> zones;  // pointers = polymorphism + memory management
    std::string             dataFile;
    bool                    reportsLoaded;

    // Private helpers
    int  generateNewId()       const;
    int  findIndexById(int id) const;

public:
    // Constructor & Destructor
    FloodMonitor();
    ~FloodMonitor();   // deletes all pointers (memory management)

    // FR1 — Data Initialisation
    bool loadFromFile(const std::string& filename);

    // FR4 — Persistent State Storage
    bool saveToFile() const;

    // Display
    void displayHeader() const;
    void displayMenu()   const;

    // FR2 — CRUD
    void logFloodReports();
    bool addZone(const std::string& name, double level);
    void viewZones()          const;
    bool updateZone(int index, double newLevel);
    bool deleteZone(int index);

    // FR2 — Search
    void searchById()    const;
    void searchByName()  const;

    // FR3 — Computation & Reports
    void calculateRiskStats(double& avgLevel, int& highRiskCount) const;
    void generateRiskAssessment() const;
    void suggestSafeRoutes()      const;
    void showStatsDashboard()     const;

    // Utility
    bool isDataLoaded()             const;
    bool isValidLevel(double level) const;

    // FR4 — Save on exit
    void exitAndSave();
};

#endif
