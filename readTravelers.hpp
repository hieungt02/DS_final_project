#ifndef READ_TRAVELERS_HPP
#define READ_TRAVELERS_HPP

#include "Traveler.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// function to read passenger text file, returns list of all passengers (unsorted)
std::vector<Traveler> readTravelersFile(const std::string& travelersTxt){

    // create travelers list to return with all travelrs
    std::vector<Traveler> travelers;

    // open file and read each line
    std::ifstream file(travelersTxt);
    std::string line;

    // read all lines of text
    while (getline(file, line)) {
        // create stream of line of text
        std::stringstream ss(line);

        // create name variable and tokens to convert string data to correct type
        std::string name, countryToken, classToken, disableToken, veteranToken;

        // create countryStatus and travelClass token
        Traveler::CountryStatus countryStatus;
        Traveler::TravelClass travelClass; 
        bool disabilties, veteran;

        // read name, assume all data divided by ','
        getline(ss, name, ',');
        getline(ss, countryToken, ',');
        getline(ss, classToken, ',');
        getline(ss, disableToken, ',');
        getline(ss, veteranToken, ',');

        // convert text tokens into proper variables types
        countryStatus = static_cast<Traveler::CountryStatus>(stoi(countryToken));
        travelClass = static_cast<Traveler::TravelClass>(stoi(classToken));
        disabilties = disableToken == "true";
        veteran = veteranToken == "true";
        
        // append the traveler instance to end of the vector 
        travelers.emplace_back(name, countryStatus, travelClass, disabilties, veteran);
    }

    // return the vector of travelers read from text
    return travelers;
}

#endif