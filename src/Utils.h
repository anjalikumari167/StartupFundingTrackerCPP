#ifndef UTILS_H
#define UTILS_H

// Small input/string helpers so the rest of the code stays clean.
// Everything is 'inline' so this can live in a header file.

#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

// Removes spaces/tabs at the start and end of a string.
inline std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) start++;
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) end--;
    return s.substr(start, end - start);
}

inline std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    if (!std::getline(std::cin, s)) {   // input closed (Ctrl+D / Ctrl+Z)
        std::cout << "\nInput ended. Exiting.\n";
        std::exit(0);
    }
    return trim(s);          // "  Pune  " becomes "Pune"
}

// Keeps asking until the user types something non-empty.
inline std::string readNonEmpty(const std::string& prompt) {
    while (true) {
        std::string s = readLine(prompt);
        if (!s.empty()) return s;
        std::cout << "  Value cannot be empty.\n";
    }
}

inline int readInt(const std::string& prompt) {
    while (true) {
        std::string s = readLine(prompt);
        try {
            size_t used = 0;
            int v = std::stoi(s, &used);
            if (used == s.size()) return v;
        } catch (...) {}
        std::cout << "  Please enter a valid whole number.\n";
    }
}

// Returns true and sets 'out' if s is a valid non-negative number.
inline bool parseAmount(const std::string& s, double& out) {
    try {
        size_t used = 0;
        double v = std::stod(s, &used);
        if (used == s.size() && v >= 0) { out = v; return true; }
    } catch (...) {}
    return false;
}

inline double readAmount(const std::string& prompt) {
    while (true) {
        double v;
        if (parseAmount(readLine(prompt), v)) return v;
        std::cout << "  Please enter a valid amount (0 or more).\n";
    }
}

inline std::string toLower(std::string s) {
    for (char& c : s) c = std::tolower(static_cast<unsigned char>(c));
    return s;
}

#endif
