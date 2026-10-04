# Startup Funding Tracker (C++)

A console-based application that manages startup funding records.
Built in C++ to practice OOP and data structures and algorithms (DSA).

## Features
- Add, display, update and delete startups (with delete confirmation)
- Search by name, sector or funding stage
- Sort by funding amount, find highest and lowest funded
- Find a startup by ID instantly (hash map)
- Top-N funded startups (heap)
- Name autocomplete (trie)
- Funding report with totals per sector and stage, exportable to report.txt
- Data is saved to and loaded from a file

## Data Structures and Algorithms Used
| Feature | Concept |
|---|---|
| Storage | vector |
| Find by ID | unordered_map (hash map), O(1) average |
| Top-N funded | priority_queue (heap) |
| Name autocomplete | Trie (prefix tree) |
| Sort by funding | std::sort with a lambda |
| Highest / lowest | linear scan, O(n) |
| Report grouping | std::map |
| Persistence | file handling (ifstream / ofstream) |

## Project Structure
- src/Startup.h, Startup.cpp : data model for one startup
- src/StartupManager.h, StartupManager.cpp : all operations and data structures
- src/Trie.h, Trie.cpp : prefix tree for autocomplete
- src/Utils.h : input validation helpers
- src/main.cpp : menu-driven interface

## Build and Run
    g++ -std=c++17 -o tracker src/*.cpp
    ./tracker

## Data File Format
Saved to startups.txt, one startup per line, fields separated by a pipe character:

    id|name|sector|stage|fundingCr|city|founder|investor

## Roadmap
- [x] Step 1: Classes, menu, basic CRUD
- [x] Step 2: Sorting, filtering by sector/stage, min/max funding
- [x] Step 3: Save/load data using files
- [x] Step 4: Hash map lookup, heap for top-N, trie for search
- [x] Step 5: Reports and polish

## Data Disclaimer
Sample data is for demonstration only. This is an independent educational project, not affiliated with any website or company.
