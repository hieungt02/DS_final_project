#ifndef IMMIGRATION_HPP
#define IMMIGRATION_HPP

// import necessary libraries and files
#include "Traveler.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


// traveler class node 
class travelerNode {

public:

  // constructor method for traveler node
  travelerNode(Traveler traveler, travelerNode *p, travelerNode *l, travelerNode *r) : traveler(traveler), parent(p), left(l), right(r) {};
  travelerNode(Traveler traveler) : traveler(traveler) {};

  // getter and setter methods for attributes of traveler
  std::string getName() const;
  Traveler::CountryStatus getCountryStatus() const;
  Traveler::TravelClass getTravelClass() const;
  bool getdisabilities() const;
  bool getVeteran() const;

  void setPriorityValue(int priority);
  int getPriorityValue() const;

  // compare function for traveler node
  class Compare {
  public:
    Compare(bool lessThan = true) : lessThan(lessThan) {};
    bool operator()(const travelerNode &n1, const travelerNode &n2) const;
    bool operator()(const travelerNode *n1, const travelerNode *n2) const;
  private:
    bool lessThan;
  };

public:
    // public attributes for traveler node
    Traveler traveler;
    travelerNode *parent = NULL;
    travelerNode  *left = NULL;
    travelerNode *right = NULL;

};


// immigration processing class
class immigrationProcessing {

    public:

    // Section I Sorting : methods for country status sorting

    // merge sort main and helper methods
    void merge(std::vector<Traveler>& arr, std::vector<Traveler>& left, int leftSize, std::vector<Traveler>& right, int rightSize);
    void mergeSort(std::vector<Traveler>& arr, int left, int right);

    // compare country status method for sorting methods 
    bool compareByCountryStatus(const Traveler& a, const Traveler& b);

    // quicksort and partition methods
    int partition(std::vector<Traveler>& arr, int low, int high);
    void quicksort(std::vector<Traveler>& arr, int low, int high);

    // merge and quick sort methods for country status vector sorting 
    std::vector<Traveler> passengerStatusOrganizerQS(std::vector<Traveler> travelers);
    std::vector<Traveler> passengerStatusOrganizerMS(std::vector<Traveler> travelers);

    // Section II Sorting: sub-group sorting based off traveler attributes
    std::vector<Traveler> groupPrioritySorting(std::vector<Traveler>& travelers);

    // Section III Search Table: binary search tree for ease of all passenger sorting
    void inorder(travelerNode *root);

    // delete, insert, and create binary search tree (nodes)
    travelerNode* deleteBSTNode(travelerNode* root, int priority);
    travelerNode* bstInsert(travelerNode* root, travelerNode* node); 
    travelerNode* bstCreation(std::vector<std::vector<Traveler>> statusVectors);
};


#endif