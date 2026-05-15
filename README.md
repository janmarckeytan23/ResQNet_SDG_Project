# ResQNet PH
### Real-Time Flood Monitoring & Hyperlocal Disaster Response System

**SDG 11** - Sustainable Cities and Communities
**SDG 13** - Climate Action
**Course:** CC103 - Computer Programming 2 | BSIT 1st Year | 2nd Semester 2025-2026

## Project Description
ResQNet PH is a console-based C++ disaster response utility that helps LGUs and barangay officials monitor flood levels across multiple zones in real time. It addresses the lack of a centralized tool for tracking flood-affected areas during typhoon season in the Philippines.

## Features
- Auto Data Load: Reads 20+ records from INPUT_DATA/database.txt on startup
- Full CRUD: Add, View, Update, Delete zones
- Search: Find zones by ID or barangay name
- Risk Assessment: Zones ranked by urgency score
- Safe Route Mapping: Evacuation route tips
- Statistics Dashboard: Totals, averages, risk counts
- Data Persistence: Saves changes on exit
- Input Validation: No crashes on bad input

## How to Compile and Run
cd CODE
g++ main.cpp FloodZone.cpp FloodMonitor.cpp -o resqnet -std=c++11
./resqnet

## Menu
[1] Input / Add Flood Zone Report
[2] Generate Predictive Risk Assessment
[3] View Safe Route Suggestions
[4] CRUD Zone Management
[5] Search Zone by ID
[6] Search Zone by Name
[7] Statistics Dashboard
[0] Save & Exit

## Contributors
- Tan: FloodZone class, computation engine, file serialisation
- Padilla: FloodMonitor CRUD operations, search functions
- Co: File I/O, input validation, main menu
- Doromal: Risk assessment report, safe route mapping, statistics
- Domandam: Documentation, README, database records, flowchart

## SDG Alignment
- SDG 11: Sustainable Cities - ResQNet helps LGUs respond faster to flooding
- SDG 13: Climate Action - Early flood monitoring reduces casualties
