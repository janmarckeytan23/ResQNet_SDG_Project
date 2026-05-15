#ifndef FLOODMONITOR_H
#define FLOODMONITOR_H

#include "FloodZone.h"
#include <vector>
#include <string>

class FloodMonitor {
private:
    std::vector<FloodZone> zones;   // replaces fixed array — supports 20+ records
    std::string            dataFile;
    bool                   reportsLoaded;

    // Private helpers
    int  generateNewId()        const;
    int  findIndexById(int id)  const;

public:
    FloodMonitor();

    bool loadFromFile(const std::string& filename);

    bool saveToFile() const;

    void displayHeader() const;
    void displayMenu()   const;

    void logFloodReports();           
    bool addZone(const std::string& name, double level);  // original CRUD add
    void viewZones()              const;                  // original CRUD view
    bool updateZone(int index, double newLevel);          // original CRUD update
    bool deleteZone(int index);                           // original CRUD delete

    void searchById()         const;
    void searchByName()       const;

    void calculateRiskStats(double& avgLevel, int& highRiskCount) const;
    void generateRiskAssessment() const;
    void suggestSafeRoutes()      const;
    void showStatsDashboard()     const;

    bool isDataLoaded()             const;
    bool isValidLevel(double level) const;

    void exitAndSave();
};

#endif