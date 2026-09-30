#ifndef STARTUP_H
#define STARTUP_H

#include <string>

// One startup record. Funding is stored as a number (in Crores)
// so that sorting / heap / max-min logic stays simple later.
class Startup {
private:
    int id;
    std::string name;
    std::string sector;
    std::string stage;
    double fundingCr;      // funding amount in Rs Crore
    std::string city;
    std::string founder;
    std::string investor;

public:
    Startup();
    Startup(int id, const std::string& name, const std::string& sector,
            const std::string& stage, double fundingCr, const std::string& city,
            const std::string& founder, const std::string& investor);

    // Getters (const = they don't change the object)
    int getId() const;
    std::string getName() const;
    std::string getSector() const;
    std::string getStage() const;
    double getFundingCr() const;
    std::string getCity() const;
    std::string getFounder() const;
    std::string getInvestor() const;

    // Setters (used by Update)
    void setName(const std::string& n);
    void setSector(const std::string& s);
    void setStage(const std::string& s);
    void setFundingCr(double f);
    void setCity(const std::string& c);
    void setFounder(const std::string& f);
    void setInvestor(const std::string& i);

    void display() const;   // prints one startup nicely
};

#endif
