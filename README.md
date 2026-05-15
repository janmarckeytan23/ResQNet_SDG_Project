# ResQNet PH
### Real-Time Flood Monitoring & Hyperlocal Disaster Response System

**SDG 11** – Sustainable Cities and Communities
**SDG 13** – Climate Action
**Course:** CC103 – Computer Programming 2 | BSIT 1st Year | 2nd Semester 2025–2026

---

## Project Description

ResQNet PH is a console-based C++ disaster response utility that helps LGUs and barangay officials monitor flood levels across multiple zones in real time. It addresses the lack of a centralized tool for tracking flood-affected areas during typhoon season in the Philippines.

---

## Features

- Auto Data Load: Reads 20+ records from INPUT_DATA/database.txt on startup
- Full CRUD: Add, View, Update, Delete zones
- Search: Find zones by ID or barangay name
- Risk Assessment: Zones ranked by urgency score
- Safe Route Mapping: Evacuation route tips
- Statistics Dashboard: Totals, averages, risk counts
- Data Persistence: Saves changes on exit
- Input Validation: No crashes on bad input
- Critical Zone Classification: Zones flagged as critical trigger RED ALERT with immediate evacuation protocols
- Monitored Zone Classification: Zones under watch receive scheduled monitoring advisories every 2 hours
- Polymorphic Alert System: Zone-specific responses via inheritance (CriticalZone / MonitoredZone)

---

## Class Hierarchy

```
FloodZone (base class)
├── CriticalZone : public FloodZone
│     └── RED ALERT – Immediate mass evacuation, deploys rescue teams, contacts NDRRMC
└── MonitoredZone : public FloodZone
      └── Advisory – Monitor water level every 2 hours, residents prepare go-bags
```

---

## How to Compile and Run

```bash
cd CODE
g++ main.cpp FloodZone.cpp FloodMonitor.cpp CriticalZone.cpp MonitoredZone.cpp -o resqnet -std=c++11
./resqnet
```

---

## Menu

```
[1]  Input / Add Flood Zone Report
[2]  Generate Predictive Risk Assessment
[3]  View Safe Route Suggestions
[4]  CRUD Zone Management
[5]  Search Zone by ID
[6]  Search Zone by Name
[7]  Statistics Dashboard
[0]  Save & Exit
```

---

## Alert Levels

| Zone Type      | Alert Level | Action                                              |
|----------------|-------------|-----------------------------------------------------|
| CriticalZone   | RED ALERT | IMMEDIATE mass evacuation. Deploy all rescue teams. Contact NDRRMC now! |
| MonitoredZone  | ADVISORY  | Monitor water level every 2 hours. Alert residents to prepare go-bags. No evacuation yet. |

---

## File Structure

```
resqnet/
├── CODE/
│   ├── main.cpp
│   ├── FloodZone.cpp / FloodZone.h
│   ├── FloodMonitor.cpp / FloodMonitor.h
│   ├── CriticalZone.cpp / CriticalZone.h
│   ├── MonitoredZone.cpp / MonitoredZone.h
│   └── resqnet (compiled binary)
├── INPUT_DATA/
│   └── database.txt
└── README.md
```

---

## OOP Concepts Applied

- **Inheritance**: `CriticalZone` and `MonitoredZone` extend `FloodZone`
- **Polymorphism**: Each zone type overrides alert behavior dynamically
- **Encapsulation**: Zone data and logic contained within respective classes
- **Abstraction**: `FloodMonitor` manages zone operations through a unified interface
