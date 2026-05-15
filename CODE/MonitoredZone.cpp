#include "MonitoredZone.h"
#include <iostream>
#include <iomanip>

// ============================================================
// Constructor
// ============================================================
MonitoredZone::MonitoredZone(int id, std::string name, std::string municipality,
                             double level, int families, bool evacuated,
                             std::string team, int freqHours)
    : FloodZone(id, name, municipality, level, families, evacuated, team),
      monitoringFrequencyHours(freqHours) {}

// ============================================================
// Getter
// ============================================================
int MonitoredZone::getMonitoringFrequency() const {
    return monitoringFrequencyHours;
}

// ============================================================
// Function : getActionPlan  (OVERRIDDEN - Polymorphism)
// Purpose  : MonitoredZone gives a calmer, watch-and-wait plan
//            compared to the base class or CriticalZone.
// ============================================================
std::string MonitoredZone::getActionPlan() const {
    std::string plan = "Monitor water level every ";
    plan += std::to_string(monitoringFrequencyHours);
    plan += " hour(s). Alert residents to prepare go-bags. No evacuation yet.";
    return plan;
}

// ============================================================
// Function : printDetails (OVERRIDDEN)
// ============================================================
void MonitoredZone::printDetails() const {
    FloodZone::printDetails();   // call base class version first
    std::cout << "  Check every: " << monitoringFrequencyHours
              << " hour(s) (MonitoredZone)\n";
}
