#ifndef FLOODZONE_H
#define FLOODZONE_H

#include <string>

// ============================================================
// Class   : FloodZone
// Purpose : Represents one flood-affected barangay/zone.
//           Stores location, water depth, affected families,
//           evacuation status, and rescue team assignment.
// SDG     : SDG 11 (Sustainable Cities) & SDG 13 (Climate Action)
// ============================================================
class FloodZone {
private:
    int         id;
    std::string zoneName;
    std::string municipality;
    double      floodLevel;      // water depth in cm
    int         affectedFamilies;
    bool        evacuated;
    std::string rescueTeam;

public:
    // Constructors
    FloodZone(std::string name = "", double level = 0.0);
    FloodZone(int id, std::string name, std::string municipality,
              double level, int families, bool evacuated, std::string team);

    // Getters
    int         getId()               const;
    std::string getName()             const;
    std::string getMunicipality()     const;
    double      getLevel()            const;
    int         getAffectedFamilies() const;
    bool        isEvacuated()         const;
    std::string getRescueTeam()       const;

    // Setters
    void setId(int id);
    void setName(const std::string& name);
    void setMunicipality(const std::string& m);
    void setLevel(double level);
    void setAffectedFamilies(int f);
    void setEvacuated(bool e);
    void setRescueTeam(const std::string& team);

    // Computation engine (FR3)
    std::string getRiskStatus()     const;  // LOW / MODERATE / HIGH / CRITICAL
    int         getUrgencyScore()   const;  // numeric priority for sorting
    std::string getSuggestedRoute() const;  // evacuation route advice
    bool        isSafeRoute()       const;
    bool        isHighRisk()        const;

    // Display & serialisation
    void        printDetails()    const;
    std::string toFileString()    const;  // pipe-delimited for database.txt
};

#endif