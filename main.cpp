/*
TEAMMATES : 
Benjamin Barrera-Altuna: babarreraaltuna@usf.ed
Richard Zhou: rzhou@usf.edu
Hieu Nguyen: htn12@usf.edu
*/

#include <iostream>
#include "immigrationProcessing.hpp"
#include "Traveler.hpp"
#include "readTravelers.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {

    std::cout << std::endl;

    // read the travelers text file to create an unsorted vector of travelers
    const std::string filename = "travelers_full.txt";
    std::vector<Traveler> travelers = readTravelersFile(filename);

    // print out the unsorted untravelers
    std::cout << "Before sorting:" << std::endl;
    for (const Traveler& traveler : travelers) {
        std::cout << "Name: " << std::left << std::setw(20) << traveler.name;
        std::cout << "Country Staus: " << traveler.countryStatus << std::endl;
    }

    // create instance of immigration processing 
    immigrationProcessing immigrationProcessor;

    // use merge sort to sort the passengers (based off country status)
    std::vector<Traveler> sortedtravelersMS = immigrationProcessor.passengerStatusOrganizerMS(travelers);
    
    // print out the sorted vector after merge sort
    std::cout << std::endl << "After sorting with MergeSort: " << std::endl;
    for (const Traveler& traveler : sortedtravelersMS) {
        std::cout << "Name: " << std::left << std::setw(20) << traveler.name;
        std::cout << "Country Staus: " << traveler.countryStatus << std::endl;
    }

    // use quick sort to sort the travelers (based off country status)
    std::vector<Traveler> sortedTravelersQS = immigrationProcessor.passengerStatusOrganizerQS(travelers);

    // print out the sorted travelers after merge sort 
    std::cout << std::endl << "After sorting with QuickSort: " << std::endl;
    for (const Traveler& traveler : sortedTravelersQS) {
        std::cout << "Name: " << std::left << std::setw(20) << traveler.name;
        std::cout << "Country Staus: " << traveler.countryStatus << std::endl;
    }

    std::cout << std::endl;

    // create 3 sub groups of travelers based off country status: 
    // US citizen, doesn't need visa, needs visa
    std::vector<Traveler> travelersStatus0;
    std::vector<Traveler> travelersStatus1;
    std::vector<Traveler> travelersStatus2;

    // for each respective vector, add the traveler belonging to each group
    for (const Traveler& traveler : sortedTravelersQS) {
        // 0 is US, 1 is no visa, 2 is yes visa
        switch (traveler.countryStatus) {
            case 0:
                travelersStatus0.push_back(traveler);
                break;
            case 1:
                travelersStatus1.push_back(traveler);
                break;
            case 2:
                travelersStatus2.push_back(traveler);
                break;
            default:
                break;
        }
    }

    // peform priority sorting based off all other attributes within the subgroups of the travelers 
    travelersStatus0 = immigrationProcessor.groupPrioritySorting(travelersStatus0);
    travelersStatus1 = immigrationProcessor.groupPrioritySorting(travelersStatus1);
    travelersStatus2 = immigrationProcessor.groupPrioritySorting(travelersStatus2);

    std::cout << std::endl << "US citizen after Heapsort: " << std::endl;
    for (const Traveler& traveler : travelersStatus0) {
        std::cout << "Name: " << std::left << std::setw(20) << traveler.name;
        std::cout << "Country Staus: " << traveler.countryStatus << std::endl;
    }

    std::cout << std::endl << "No visa needed after Heapsort: " << std::endl;
    for (const Traveler& traveler : travelersStatus1) {
        std::cout << "Name: " << std::left << std::setw(20) << traveler.name;
        std::cout << "Country Staus: " << traveler.countryStatus << std::endl;
    }

    std::cout << std::endl << "Visa needed after Heapsort: " << std::endl;
    for (const Traveler& traveler : travelersStatus2) {
        std::cout << "Name: " << std::left << std::setw(20) << traveler.name;
        std::cout << "Country Staus: " << traveler.countryStatus << std::endl;
    }
    std::cout << std::endl;

    // create a vector with all sorted sub groups 
    std::vector<std::vector<Traveler>> statusVectors = {travelersStatus0, travelersStatus1, travelersStatus2};

    // create binary search tree based off prioirty from all travelers sub groups (US most important, Visa need least important)
    travelerNode* root = immigrationProcessor.bstCreation(statusVectors);

    
    std::cout << "Root Node: " << root->getName() << "\t\t" <<"Priority Value: " << root->getPriorityValue();
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Inorder Traversal of BST:" << std::endl;

    // print out binary search tree inorder
    immigrationProcessor.inorder(root);
    std::cout << std::endl;
    
    // delete travelers who couldn't not make it to immigration processing
    root = immigrationProcessor.deleteBSTNode(root, 15);
    root = immigrationProcessor.deleteBSTNode(root, 11);
    root = immigrationProcessor.deleteBSTNode(root, 14);

    // print out updated binary search tree inorder
    std::cout << "Inorder Traversal of BST after node deletions:" << std::endl;
    immigrationProcessor.inorder(root);


    return 0;
}