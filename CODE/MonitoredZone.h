#ifndef MONITOREDZONE_H
#define MONITOREDZONE_H

#include "FloodZone.h"

// ============================================================
// Class   : MonitoredZone  (Derived from FloodZone)
// Purpose : Represents a flood zone being watched but not yet
//           at evacuation level. Overrides getActionPlan() to
//           give a calmer, monitoring-focused response.
// OOP     : Demonstrates INHERITANCE and POLYMORPHISM.
// ============================================================
class MonitoredZone : public FloodZone {
private:
    int monitoringFrequencyHours;  // how often to check (in hours)

public:
    // Constructor
    MonitoredZone(int id, std::string name, std::string municipality,
                  double level, int families, bool evacuated,
                  std::string team, int freqHours = 2);

    // Getter
    int getMonitoringFrequency() const;

    // Override (Polymorphism) — calmer, monitoring-focused plan
    std::string getActionPlan() const override;

    // Override printDetails to show monitoring frequency
    void printDetails() const override;
};

#endif
