#include "FloodZone.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// ============================================================
// Constructor (original — backward compatible)
// ============================================================
FloodZone::FloodZone(std::string name, double level)
    : id(0), zoneName(name), municipality(""), floodLevel(level),
      affectedFamilies(0), evacuated(false), rescueTeam("Unassigned") {}

// ============================================================
// Constructor (full — used when loading from database.txt)
// ============================================================
FloodZone::FloodZone(int id, std::string name, std::string municipality,
                     double level, int families, bool evacuated, std::string team)
    : id(id), zoneName(name), municipality(municipality), floodLevel(level),
      affectedFamilies(families), evacuated(evacuated), rescueTeam(team) {}

// ============================================================
// Getters
// ============================================================
int         FloodZone::getId()               const { return id; }
std::string FloodZone::getName()             const { return zoneName; }
std::string FloodZone::getMunicipality()     const { return municipality; }
double      FloodZone::getLevel()            const { return floodLevel; }
int         FloodZone::getAffectedFamilies() const { return affectedFamilies; }
bool        FloodZone::isEvacuated()         const { return evacuated; }
std::string FloodZone::getRescueTeam()       const { return rescueTeam; }

// ============================================================
// Setters
// ============================================================
void FloodZone::setId(int i)                       { id = i; }
void FloodZone::setLevel(double level)             { if (level >= 0 && level <= 500) floodLevel = level; }
void FloodZone::setAffectedFamilies(int f)         { affectedFamilies = f; }
void FloodZone::setEvacuated(bool e)               { evacuated = e; }
void FloodZone::setRescueTeam(const std::string& t){ rescueTeam = t; }

// ============================================================
// Function : getRiskStatus  (FR3 Computation Engine)
// Purpose  : Composite score from water depth + families.
// ============================================================
std::string FloodZone::getRiskStatus() const {
    int waterScore = 0;
    if      (floodLevel >= 100.0) waterScore = 3;
    else if (floodLevel >= 50.0)  waterScore = 2;
    else if (floodLevel >= 15.0)  waterScore = 1;

    int popScore = 0;
    if      (affectedFamilies >= 500) popScore = 3;
    else if (affectedFamilies >= 200) popScore = 2;
    else if (affectedFamilies >= 50)  popScore = 1;

    int composite = waterScore + popScore;

    if      (composite >= 5) return "[CRITICAL - EVACUATE NOW]";
    else if (composite >= 3) return "[HIGH - PREPARE EVACUATION]";
    else if (composite >= 1) return "[MODERATE - BE ALERT]";
    else                     return "[LOW - MONITORING]";
}

// ============================================================
// Function : getUrgencyScore
// ============================================================
int FloodZone::getUrgencyScore() const {
    return static_cast<int>(floodLevel * 0.6) + (affectedFamilies / 10);
}

bool FloodZone::isSafeRoute()  const { return floodLevel < 10.0; }
bool FloodZone::isHighRisk()   const { return floodLevel > 30.0; }

// ============================================================
// Function : getActionPlan  (BASE class version)
// Purpose  : Default action plan — overridden in derived classes.
//            This is the VIRTUAL method enabling polymorphism.
// ============================================================
std::string FloodZone::getActionPlan() const {
    std::string risk = getRiskStatus();
    if      (risk.find("CRITICAL") != std::string::npos)
        return "IMMEDIATE evacuation required. Contact NDRRMC.";
    else if (risk.find("HIGH")     != std::string::npos)
        return "Prepare evacuation. Alert barangay officials.";
    else if (risk.find("MODERATE") != std::string::npos)
        return "Monitor water level every hour. Standby for evacuation.";
    else
        return "Continue monitoring. No action required yet.";
}

// ============================================================
// Function : printDetails
// ============================================================
void FloodZone::printDetails() const {
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "  ID         : " << id           << "\n"
              << "  Zone       : " << zoneName      << "\n"
              << "  Municipal  : " << municipality  << "\n"
              << "  Depth      : " << floodLevel    << " cm\n"
              << "  Families   : " << affectedFamilies << "\n"
              << "  Risk       : " << getRiskStatus()  << "\n"
              << "  Evacuated  : " << (evacuated ? "YES" : "NO") << "\n"
              << "  Team       : " << rescueTeam    << "\n"
              << "  Action Plan: " << getActionPlan() << "\n";
}

// ============================================================
// Function : toFileString
// ============================================================
std::string FloodZone::toFileString() const {
    std::ostringstream oss;
    oss << id << "|" << zoneName << "|" << municipality << "|"
        << std::fixed << std::setprecision(1) << floodLevel << "|"
        << affectedFamilies << "|" << (evacuated ? 1 : 0) << "|" << rescueTeam;
    return oss.str();
}
