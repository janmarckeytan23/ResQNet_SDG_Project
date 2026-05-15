#ifndef FLOODZONE_H
#define FLOODZONE_H

#include <string>

// ============================================================
// Class   : FloodZone
// Purpose : Base class representing one flood-affected zone.
//           Derived classes (CriticalZone, MonitoredZone)
//           override getActionPlan() for polymorphism.
// ============================================================
class FloodZone {
private:
    int         id;
    std::string zoneName;
    std::string municipality;
    double      floodLevel;       // water depth in cm
    int         affectedFamilies;
    bool        evacuated;
    std::string rescueTeam;

public:
    // Constructors
    FloodZone(std::string name = "", double level = 0.0);
    FloodZone(int id, std::string name, std::string municipality,
              double level, int families, bool evacuated, std::string team);

    // Virtual destructor (required for base classes)
    virtual ~FloodZone() {}

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
    void setLevel(double level);
    void setAffectedFamilies(int f);
    void setEvacuated(bool e);
    void setRescueTeam(const std::string& team);

    // Regular methods
    std::string getRiskStatus()   const;
    int         getUrgencyScore() const;
    bool        isSafeRoute()     const;
    bool        isHighRisk()      const;

    // -------------------------------------------------------
    // Virtual method — overridden in derived classes (Polymorphism)
    // Purpose: Returns the recommended action plan for this zone.
    //          CriticalZone and MonitoredZone give different responses.
    // -------------------------------------------------------
    virtual std::string getActionPlan() const;

    // Display & file I/O
    virtual void        printDetails()  const;
    std::string         toFileString()  const;
};

#endif
