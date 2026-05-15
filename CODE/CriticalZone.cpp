#include "CriticalZone.h"
#include <iostream>
#include <iomanip>

// ============================================================
// Constructor
// Purpose : Calls the base class (FloodZone) constructor
//           and sets the additional alertLevel field.
// ============================================================
CriticalZone::CriticalZone(int id, std::string name, std::string municipality,
                            double level, int families, bool evacuated,
                            std::string team, std::string alertLevel)
    : FloodZone(id, name, municipality, level, families, evacuated, team),
      alertLevel(alertLevel) {}

// ============================================================
// Getter
// ============================================================
std::string CriticalZone::getAlertLevel() const {
    return alertLevel;
}

// ============================================================
// Function : getActionPlan  (OVERRIDDEN - Polymorphism)
// Purpose  : CriticalZone gives a more specific, urgent plan
//            than the base class version.
// ============================================================
std::string CriticalZone::getActionPlan() const {
    if (alertLevel == "RED")
        return "[RED ALERT] IMMEDIATE mass evacuation! Deploy all rescue teams. Contact NDRRMC now!";
    else
        return "[ORANGE ALERT] Evacuate vulnerable residents. Pre-position rescue boats. Monitor every 30 mins.";
}

// ============================================================
// Function : printDetails (OVERRIDDEN)
// Purpose  : Shows all base class info + alert level.
// ============================================================
void CriticalZone::printDetails() const {
    FloodZone::printDetails();   // call base class version first
    std::cout << "  Alert Level: " << alertLevel << " (CriticalZone)\n";
}
