#include "Startup.h"
#include <iostream>
#include <iomanip>

using namespace std;

Startup::Startup() : id(0), fundingCr(0.0) {}

Startup::Startup(int id, const string& name, const string& sector,
                 const string& stage, double fundingCr, const string& city,
                 const string& founder, const string& investor)
    : id(id), name(name), sector(sector), stage(stage),
      fundingCr(fundingCr), city(city), founder(founder), investor(investor) {}

int Startup::getId() const { return id; }
string Startup::getName() const { return name; }
string Startup::getSector() const { return sector; }
string Startup::getStage() const { return stage; }
double Startup::getFundingCr() const { return fundingCr; }
string Startup::getCity() const { return city; }
string Startup::getFounder() const { return founder; }
string Startup::getInvestor() const { return investor; }

void Startup::setName(const string& n) { name = n; }
void Startup::setSector(const string& s) { sector = s; }
void Startup::setStage(const string& s) { stage = s; }
void Startup::setFundingCr(double f) { fundingCr = f; }
void Startup::setCity(const string& c) { city = c; }
void Startup::setFounder(const string& f) { founder = f; }
void Startup::setInvestor(const string& i) { investor = i; }

void Startup::display() const {
    cout << "--------------------------------------\n";
    cout << "ID       : " << id << "\n";
    cout << "Name     : " << name << "\n";
    cout << "Sector   : " << sector << "\n";
    cout << "Stage    : " << stage << "\n";
    cout << "Funding  : Rs " << fixed << setprecision(2) << fundingCr << " Cr\n";
    cout << "City     : " << city << "\n";
    cout << "Founder  : " << founder << "\n";
    cout << "Investor : " << investor << "\n";
}
