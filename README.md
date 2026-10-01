# Startup Funding Tracker (C++)

A console-based application that manages startup funding records.
Built in C++ to practice OOP and data structures and algorithms (DSA).

## Features
- Add, display, update and delete startups
- Search startups by name (partial, case-insensitive)
- Each record stores: ID, name, sector, funding stage, funding amount (Rs Cr), city, founder, investor

## Tech Stack
C++17, STL (vector), OOP (classes, encapsulation)

## Build and Run
    g++ -std=c++17 -o tracker src/*.cpp
    ./tracker

## Roadmap
- [x] Step 1: Classes, menu, basic CRUD
- [x] Step 2: Sorting, filtering by sector/stage, min/max funding
- [ ] Step 3: Save/load data using files
- [ ] Step 4: Hash map lookup, heap for top-N, trie for search
- [ ] Step 5: Reports and polish

## Data Disclaimer
Sample data is for demonstration only. This is an independent educational project, not affiliated with any website or company.
