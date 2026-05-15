#include "FloodMonitor.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
FloodMonitor::FloodMonitor() : dataFile(""), reportsLoaded(false) {}

int FloodMonitor::generateNewId() const {
    int maxId = 0;
    for (const auto& z : zones)
        if (z.getId() > maxId) maxId = z.getId();
    return maxId + 1;
}

int FloodMonitor::findIndexById(int id) const {
    for (int i = 0; i < (int)zones.size(); i++)
        if (zones[i].getId() == id) return i;
    return -1;
}

bool FloodMonitor::loadFromFile(const std::string& filename) {
    dataFile = filename;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "\n[!] WARNING: Could not open '" << filename
                  << "'. Starting with empty dataset.\n";
        return false;
    }

    zones.clear();
    std::string line;
    int loaded = 0;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(ss, token, '|'))
            tokens.push_back(token);

        if (tokens.size() < 7) continue;

        try {
            int    id        = std::stoi(tokens[0]);
            double level     = std::stod(tokens[3]);
            int    families  = std::stoi(tokens[4]);
            bool   evacuated = (tokens[5] == "1");
            FloodZone z(id, tokens[1], tokens[2], level, families, evacuated, tokens[6]);
            zones.push_back(z);
            loaded++;
        } catch (...) { /* skip unparseable records */ }
    }

    file.close();
    reportsLoaded = (loaded > 0);
    std::cout << "\n[OK] Loaded " << loaded
              << " flood zone records from '" << filename << "'.\n";
    return reportsLoaded;
}

bool FloodMonitor::saveToFile() const {
    if (dataFile.empty()) {
        std::cout << "\n[!] No file path configured. Cannot save.\n";
        return false;
    }
    std::ofstream file(dataFile);
    if (!file.is_open()) {
        std::cout << "\n[!] ERROR: Could not write to '" << dataFile << "'.\n";
        return false;
    }
    file << "# ResQNet PH Flood Zone Database\n";
    file << "# id|name|municipality|level_cm|families|evacuated|rescueTeam\n";
    for (const auto& z : zones)
        file << z.toFileString() << "\n";
    file.close();
    std::cout << "\n[OK] " << zones.size()
              << " records saved to '" << dataFile << "'.\n";
    return true;
}

void FloodMonitor::displayHeader() const {
    std::cout << "\n================================================\n";
    std::cout << "       ResQNet PH: REAL-TIME FLOOD MONITOR      \n";
    std::cout << "    Hyperlocal Disaster Response & Analytics    \n";
    std::cout << "  SDG 11 & 13 | CC103 BSIT 1Y | 2nd Sem 2025  \n";
    std::cout << "================================================\n";
}

void FloodMonitor::displayMenu() const {
    std::cout << "\nSYSTEM COMMANDS:\n";
    std::cout << "[1]  Input / Add Flood Zone Report\n";
    std::cout << "[2]  Generate Predictive Risk Assessment\n";
    std::cout << "[3]  View Safe Route Suggestions\n";
    std::cout << "[4]  CRUD Zone Management\n";
    std::cout << "[5]  Search Zone by ID\n";
    std::cout << "[6]  Search Zone by Name\n";
    std::cout << "[7]  Statistics Dashboard\n";
    std::cout << "[0]  Save & Exit\n";
}

void FloodMonitor::logFloodReports() {
    std::cout << "\n--- DATA ENTRY: LOCALIZED FLOOD REPORTING ---\n";
    std::string name, municipality, team;
    double level;
    int    families;
    char   evChoice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Zone / Barangay Name : "; std::getline(std::cin, name);
    std::cout << "Municipality         : "; std::getline(std::cin, municipality);

    while (true) {
        std::cout << "Flood Depth (cm, 0-500): ";
        if (std::cin >> level && isValidLevel(level)) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << " [!] Sensor Error: Invalid depth. Must be 0-500 cm. Retry.\n";
    }

    while (true) {
        std::cout << "Affected Families       : ";
        if (std::cin >> families && families >= 0) break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << " [!] Invalid. Enter a whole number >= 0.\n";
    }

    std::cout << "Evacuated? (y/n)         : ";
    std::cin >> evChoice;
    bool evacuated = (evChoice == 'y' || evChoice == 'Y');

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Rescue Team Assigned     : "; std::getline(std::cin, team);

    int newId = generateNewId();
    FloodZone z(newId, name, municipality, level, families, evacuated, team);
    zones.push_back(z);
    reportsLoaded = true;

    std::cout << "\n[OK] Zone #" << newId << " added | Risk: "
              << z.getRiskStatus() << "\n";
}

void FloodMonitor::calculateRiskStats(double& avgLevel, int& highRiskCount) const {
    double total = 0;
    highRiskCount = 0;
    for (const auto& z : zones) {
        total += z.getLevel();
        if (z.isHighRisk()) highRiskCount++;
    }
    avgLevel = zones.empty() ? 0 : total / zones.size();
}

void FloodMonitor::generateRiskAssessment() const {
    if (zones.empty()) { std::cout << "\n[!] No data loaded.\n"; return; }

    double avgLevel;
    int highRiskCount;
    calculateRiskStats(avgLevel, highRiskCount);

    // Sort copy by urgency score (highest first)
    std::vector<FloodZone> sorted = zones;
    std::sort(sorted.begin(), sorted.end(),
              [](const FloodZone& a, const FloodZone& b) {
                  return a.getUrgencyScore() > b.getUrgencyScore();
              });

    std::cout << "\n--- PREDICTIVE RISK INDICATOR REPORT ---\n";
    std::cout << std::fixed << std::setprecision(1);
    int rank = 1;
    for (const auto& z : sorted) {
        std::cout << "\nPRIORITY #" << rank++ << "\n";
        z.printDetails();
        std::cout << "---\n";
    }
    std::cout << "Community Average Depth : " << avgLevel << " cm\n";
    std::cout << "High-Risk Zones Count   : " << highRiskCount << "\n";
}

void FloodMonitor::suggestSafeRoutes() const {
    if (zones.empty()) { std::cout << "\n[!] No data loaded.\n"; return; }

    std::cout << "\n--- SAFE ROUTE MAPPING ---\n";
    bool foundSafe = false;
    for (const auto& z : zones) {
        if (z.isSafeRoute()) {
            std::cout << "[SAFE] " << z.getName()
                      << " is currently passable for all vehicles.\n";
            foundSafe = true;
        }
    }
    if (!foundSafe)
        std::cout << "[WARNING] No zones currently meet the 'Safe Route' threshold.\n";

    std::cout << "\n--- EVACUATION ROUTE TIPS (HIGH/CRITICAL ZONES) ---\n";
    bool anyDanger = false;
    for (const auto& z : zones) {
        if (z.isHighRisk()) {
            std::cout << "\n[" << z.getName() << "]\n"
                      << "  " << z.getSuggestedRoute() << "\n";
            anyDanger = true;
        }
    }
    if (!anyDanger)
        std::cout << "[OK] No high-risk zones requiring route redirection.\n";
}

void FloodMonitor::showStatsDashboard() const {
    if (zones.empty()) { std::cout << "\n[!] No data loaded.\n"; return; }

    int critical = 0, high = 0, moderate = 0, low = 0;
    int totalFamilies = 0, evacuatedCount = 0;
    double totalDepth = 0.0;

    for (const auto& z : zones) {
        std::string r = z.getRiskStatus();
        if      (r.find("CRITICAL") != std::string::npos) critical++;
        else if (r.find("HIGH")     != std::string::npos) high++;
        else if (r.find("MODERATE") != std::string::npos) moderate++;
        else                                              low++;

        totalFamilies  += z.getAffectedFamilies();
        totalDepth     += z.getLevel();
        if (z.isEvacuated()) evacuatedCount++;
    }

    int n = (int)zones.size();
    std::cout << "\n================================================\n";
    std::cout << "        RESQNET STATISTICS DASHBOARD\n";
    std::cout << "================================================\n";
    std::cout << "  Total Zones Monitored  : " << n            << "\n";
    std::cout << "  Total Affected Families: " << totalFamilies << "\n";
    std::cout << "  Average Water Depth    : " << std::fixed
              << std::setprecision(1) << totalDepth / n      << " cm\n";
    std::cout << "  Zones Evacuated        : " << evacuatedCount << "\n";
    std::cout << "------------------------------------------------\n";
    std::cout << "  CRITICAL : " << critical << "\n";
    std::cout << "  HIGH     : " << high     << "\n";
    std::cout << "  MODERATE : " << moderate << "\n";
    std::cout << "  LOW      : " << low      << "\n";
    std::cout << "================================================\n";
}

bool FloodMonitor::addZone(const std::string& name, double level) {
    if (!isValidLevel(level)) return false;
    int newId = generateNewId();
    FloodZone z(name, level);
    z.setId(newId);
    zones.push_back(z);
    reportsLoaded = true;
    return true;
}

void FloodMonitor::viewZones() const {
    if (zones.empty()) { std::cout << "\n[!] No zones on record.\n"; return; }

    std::cout << "\n--- ZONE LIST ---\n";
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(22) << "NAME"
              << std::setw(18) << "MUNICIPALITY"
              << std::setw(10) << "DEPTH(cm)"
              << std::setw(10) << "FAMILIES"
              << std::setw(6)  << "EVAC"
              << "RISK\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& z : zones) {
        std::string risk = z.getRiskStatus();
        // strip brackets for compact display
        if (risk.size() > 2) risk = risk.substr(1, risk.find(']') - 1);
        std::cout << std::left
                  << std::setw(5)  << z.getId()
                  << std::setw(22) << z.getName().substr(0, 21)
                  << std::setw(18) << z.getMunicipality().substr(0, 17)
                  << std::setw(10) << std::fixed << std::setprecision(1) << z.getLevel()
                  << std::setw(10) << z.getAffectedFamilies()
                  << std::setw(6)  << (z.isEvacuated() ? "YES" : "NO")
                  << risk << "\n";
    }
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Total: " << zones.size() << " zone(s)\n";
}

bool FloodMonitor::updateZone(int index, double newLevel) {
    if (index < 1 || index > (int)zones.size()) return false;
    if (!isValidLevel(newLevel)) return false;
    zones[index - 1].setLevel(newLevel);
    return true;
}

bool FloodMonitor::deleteZone(int index) {
    if (index < 1 || index > (int)zones.size()) return false;
    zones.erase(zones.begin() + (index - 1));
    return true;
}

void FloodMonitor::searchById() const {
    int id;
    std::cout << "\nEnter Zone ID to search: ";
    while (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "[!] Invalid input. Enter a number: ";
    }
    int idx = findIndexById(id);
    if (idx == -1) {
        std::cout << "\n[!] Zone ID #" << id << " not found.\n";
        return;
    }
    std::cout << "\n--- Zone Details ---\n";
    zones[idx].printDetails();
}

void FloodMonitor::searchByName() const {
    std::string keyword;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nEnter zone name (or partial): ";
    std::getline(std::cin, keyword);

    std::string kLower = keyword;
    std::transform(kLower.begin(), kLower.end(), kLower.begin(), ::tolower);

    bool found = false;
    for (const auto& z : zones) {
        std::string nLower = z.getName();
        std::transform(nLower.begin(), nLower.end(), nLower.begin(), ::tolower);
        if (nLower.find(kLower) != std::string::npos) {
            std::cout << "\n--- Match Found ---\n";
            z.printDetails();
            found = true;
        }
    }
    if (!found)
        std::cout << "\n[!] No zone matching '" << keyword << "' found.\n";
}

bool FloodMonitor::isDataLoaded()             const { return reportsLoaded; }
bool FloodMonitor::isValidLevel(double level) const { return (level >= 0 && level <= 500); }

void FloodMonitor::exitAndSave() {
    std::cout << "\nSaving all changes to file...\n";
    saveToFile();
    std::cout << "\nTerminating ResQNet PH Session. Stay safe and alert!\n";
}