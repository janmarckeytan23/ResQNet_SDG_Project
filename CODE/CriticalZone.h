#ifndef CRITICALZONE_H
#define CRITICALZONE_H

#include "FloodZone.h"

// ============================================================
// Class   : CriticalZone  (Derived from FloodZone)
// Purpose : Represents a flood zone with water level >= 100 cm
//           OR 500+ affected families. Overrides getActionPlan()
//           to provide a more urgent, specific response.
// OOP     : Demonstrates INHERITANCE and POLYMORPHISM.
// ============================================================
class CriticalZone : public FloodZone {
private:
    std::string alertLevel;   // "RED" or "ORANGE"

public:
    // Constructor
    CriticalZone(int id, std::string name, std::string municipality,
                 double level, int families, bool evacuated,
                 std::string team, std::string alertLevel = "RED");

    // Getter
    std::string getAlertLevel() const;

    // Override (Polymorphism) — more urgent action plan
    std::string getActionPlan() const override;

    // Override printDetails to show alert level
    void printDetails() const override;
};

#endif
