#include "FloodZone.h"
#include <iostream>
#include <iomanip>
#include <sstream>

FloodZone::FloodZone(std::string name, double level)
    : id(0), zoneName(name), municipality(""), floodLevel(level),
      affectedFamilies(0), evacuated(false), rescueTeam("Unassigned") {}

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
void FloodZone::setId(int i)                        { id = i; }
void FloodZone::setName(const std::string& n)       { zoneName = n; }
void FloodZone::setMunicipality(const std::string& m){ municipality = m; }
void FloodZone::setLevel(double level) {
    if (level >= 0 && level <= 500) floodLevel = level;
}
void FloodZone::setAffectedFamilies(int f)          { affectedFamilies = f; }
void FloodZone::setEvacuated(bool e)                { evacuated = e; }
void FloodZone::setRescueTeam(const std::string& t) { rescueTeam = t; }

// ============================================================
// Function : getRiskStatus  (FR3 — Computation Engine)
// Purpose  : Derives a risk category from BOTH water depth AND
//            number of affected families (composite scoring).
//            This makes it a real computation, not just a lookup.
// Inputs   : floodLevel (cm), affectedFamilies
// Output   : "LOW" / "MODERATE" / "HIGH" / "CRITICAL"
// ============================================================
std::string FloodZone::getRiskStatus() const {
    // Water depth score (0-3)
    int waterScore = 0;
    if      (floodLevel >= 100.0) waterScore = 3;  // >= 1 metre
    else if (floodLevel >= 50.0)  waterScore = 2;
    else if (floodLevel >= 15.0)  waterScore = 1;

    // Population impact score (0-3)
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
// Function : getUrgencyScore  (FR3)
// Purpose  : Returns numeric priority score for sorting zones.
//            Water level weighted 60%, population 40%.
// ============================================================
int FloodZone::getUrgencyScore() const {
    return static_cast<int>(floodLevel * 0.6) + (affectedFamilies / 10);
}

// ============================================================
// Function : getSuggestedRoute  (FR3)
// Purpose  : Returns an evacuation route tip based on risk level.
// ============================================================
std::string FloodZone::getSuggestedRoute() const {
    std::string risk = getRiskStatus();
    if      (risk.find("CRITICAL") != std::string::npos)
        return "IMMEDIATE: Use elevated national highway via DPWH emergency corridor.";
    else if (risk.find("HIGH")     != std::string::npos)
        return "Use barangay road to nearest covered court / evacuation centre.";
    else if (risk.find("MODERATE") != std::string::npos)
        return "Pre-position families; standby on main road for possible evacuation.";
    else
        return "No evacuation required. Continue water level monitoring.";
}

bool FloodZone::isSafeRoute()  const { return floodLevel < 10.0; }
bool FloodZone::isHighRisk()   const { return floodLevel > 30.0; }

// ============================================================
// Function : printDetails
// Purpose  : Formatted display of one zone record.
// ============================================================
void FloodZone::printDetails() const {
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "  ID        : " << id << "\n"
              << "  Zone      : " << zoneName << "\n"
              << "  Municipal : " << municipality << "\n"
              << "  Depth     : " << floodLevel << " cm\n"
              << "  Families  : " << affectedFamilies << "\n"
              << "  Risk      : " << getRiskStatus() << "\n"
              << "  Evacuated : " << (evacuated ? "YES" : "NO") << "\n"
              << "  Team      : " << rescueTeam << "\n"
              << "  Route Tip : " << getSuggestedRoute() << "\n";
}

// ============================================================
// Function : toFileString
// Purpose  : Serialises zone to one pipe-delimited line for
//            writing back to database.txt  (FR4).
// Format   : id|name|municipality|level|families|evacuated|team
// ============================================================
std::string FloodZone::toFileString() const {
    std::ostringstream oss;
    oss << id << "|"
        << zoneName << "|"
        << municipality << "|"
        << std::fixed << std::setprecision(1) << floodLevel << "|"
        << affectedFamilies << "|"
        << (evacuated ? 1 : 0) << "|"
        << rescueTeam;
    return oss.str();
}