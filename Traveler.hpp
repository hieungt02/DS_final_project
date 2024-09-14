#ifndef TRAVELER_HPP
#define TRAVELER_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// traveler class for all passangers 
class Traveler {
public:

    // create country status of person: US citizen, No visa required, Requires Visa
    enum CountryStatus { US = 0, NO_VISA, YES_VISA };

    // create travel status: first class, business, economy 
    enum TravelClass { FIR = 0, BUS, ECO };

    // public variables: name, country status, travel class, disabilites, veteran
    std::string name;
    CountryStatus countryStatus;
    TravelClass travelClass;
    bool disabilities;
    bool veteran;

    // piroirtyValue will be decided in sorting algorithms
    int priorityValue = 0;

    // create constructor for person
    Traveler(std::string n, CountryStatus cs, TravelClass tc, bool d, bool v)
        : name(n), countryStatus(cs), travelClass(tc), disabilities(d), veteran(v) {}

    // create a function to display the information of the passanger 
    void displayInfo() const {
        std::cout << "Name: " << name 
                  << "\nCountry Status: " << countryStatus 
                  << "\nClass: " << travelClass 
                  << "\nDisabilities: " << (disabilities ? "Yes" : "No")
                  << "\nVeteran: " << (veteran ? "Yes" : "No") << std::endl;
    }
};


#endif