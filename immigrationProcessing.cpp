// import need libraries and files
#include "immigrationProcessing.hpp"
#include "PriorityQueue.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

/* THE FOLLOWING FUNCTIONS ARE METHODS FOR THE TRAVELER NODE */


// set the priority value of the node
void travelerNode::setPriorityValue(int priority){
    traveler.priorityValue = priority;
    return;
}

// get the piority (int) value of the node
int travelerNode::getPriorityValue() const{
    return traveler.priorityValue;
}

// get the name (string) of the traveler node
std::string travelerNode::getName() const{
    return traveler.name;
}

// get the country status (int) of the node
Traveler::CountryStatus travelerNode::getCountryStatus() const{
    return traveler.countryStatus;
}

// get the traveler class (int)
Traveler::TravelClass travelerNode::getTravelClass() const{
    return traveler.travelClass;
}

// get the disabilites status (bool) of the traveler
bool travelerNode::getdisabilities() const {
    return traveler.disabilities;
}

// get the veteran status of the traveler
bool travelerNode::getVeteran() const {
    return traveler.veteran;
} 

// create a compare operator between the traveler nodes (pointer)
bool travelerNode::Compare::operator()(const travelerNode *n1, const travelerNode *n2) const {
    // Compare based on disabilities
    if (n1->getdisabilities() && !n2->getdisabilities()) {
        return lessThan; 
    } else if (!n1->getdisabilities() && n2->getdisabilities()) {
        return !lessThan; 
    }

    // If both have disabilities or both do not have disabilities, compare based on other criteria
    // First-class
    if (n1->getTravelClass() == Traveler::TravelClass::FIR && n2->getTravelClass() != Traveler::TravelClass::FIR) {
        return lessThan; 
    } else if (n2->getTravelClass() == Traveler::TravelClass::FIR && n1->getTravelClass() != Traveler::TravelClass::FIR) {
        return !lessThan; 
    }

    // Veteran status
    if (n1->getVeteran() && !n2->getVeteran()) {
        return lessThan; 
    } else if (!n1->getVeteran() && n2->getVeteran()) {
        return !lessThan;
    }

    // Business class
    if (n1->getTravelClass() == Traveler::TravelClass::BUS && n2->getTravelClass() == Traveler::TravelClass::ECO) {
        return lessThan; 
    } else if (n2->getTravelClass() == Traveler::TravelClass::BUS && n1->getTravelClass() == Traveler::TravelClass::ECO) {
        return !lessThan; 
    }

    // Economy class
    return false; 
}


/* THE FOLLOWING FUNTIONS ARE METHODS FOR THE IMMIGRATION PROCESSING CLASS */


/* the following immigration processing section is for the first sorting process :
   country status based sorting. Meaning whether the person belong in a subgroup of
   US citizen, visting foreigner that requires no visa, or foreigner that requires visa
   (the grouping are based on descending piority with US citizen being most important) 
*/


//MergeSort helper method: Sorting of the travelers based on CountryStatus
void immigrationProcessing::merge(std::vector<Traveler>& arr, std::vector<Traveler>& left, int leftSize, std::vector<Traveler>& right, int rightSize) {
    int i = 0, j = 0, k = 0;

    // Merge the two sorted subarrays into arr
    while (i < leftSize && j < rightSize) {
        if (left[i].countryStatus <= right[j].countryStatus) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Add remaining elements from left subarray (if any)
    while (i < leftSize) {
        arr[k++] = left[i++];
    }

    // Add remaining elements from right subarray (if any)
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

//MergeSort main method : Sorting of the travelers based on CountryStatus
void immigrationProcessing::mergeSort(std::vector<Traveler>& arr, int left, int right) {
    if (left >= right) {
        return;  // Base case: subarray has at most one element
    }

    int mid = left + (right - left) / 2;

    // Create temporary subarrays
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    std::vector<Traveler> leftArr(leftSize, Traveler("", Traveler::US, Traveler::ECO, false, false));  //default initialization
    std::vector<Traveler> rightArr(rightSize, Traveler("", Traveler::US, Traveler::ECO, false, false));

    // Copy data to temporary subarrays
    for (int i = 0; i < leftSize; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < rightSize; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // Recursively sort the subarrays
    mergeSort(leftArr, 0, leftArr.size() - 1);
    mergeSort(rightArr, 0, rightArr.size() - 1);

    // Merge the sorted subarrays
    merge(arr, leftArr, leftSize, rightArr, rightSize);
}

//MergeSort method caller: Sorting of the travelers based on CountryStatus
std::vector<Traveler> immigrationProcessing::passengerStatusOrganizerMS(std::vector<Traveler> travelers) {
    mergeSort(travelers, 0, travelers.size() - 1);
    return travelers;
}

//Quicksort comparison method: Sorting of the travelers based on CountryStatus
bool immigrationProcessing::compareByCountryStatus(const Traveler& a, const Traveler& b) { //function to compare each traveler's country status
    return a.countryStatus < b.countryStatus; 
}

// Quicksort partition method:Sorting of the travelers based on CountryStatus
int immigrationProcessing::partition(std::vector<Traveler>& arr, int low, int high) {
    Traveler pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (compareByCountryStatus(arr[j], pivot)) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quicksort main method : Sorting of the travelers based on CountryStatus
void immigrationProcessing::quicksort(std::vector<Traveler>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Quicksort method calller: Sorting of the travelers based on CountryStatus
std::vector<Traveler> immigrationProcessing::passengerStatusOrganizerQS(std::vector<Traveler> travelers) {
        quicksort(travelers, 0, travelers.size() - 1);
    return travelers;
}


/* the following immigration processing section is for the second sorting process :
   within each created sub-group of traveler country class, the travelers will again 
   be sorted (within only their own sub-groups) for piroitization based off the other
   attributes the travelers posses (traveler class, veteran, disability)
*/

std::vector<Traveler> immigrationProcessing::groupPrioritySorting(std::vector<Traveler>& travelers) {
    HeapQueue<travelerNode*, travelerNode::Compare> priorityQueue;

    // Create TravelerNode instances for each traveler and insert them into the priority queue
    for (const auto& traveler : travelers) {
        travelerNode* node = new travelerNode(traveler); // Assuming you have a constructor in TravelerNode to accept Traveler
        priorityQueue.insert(node);
    }

    // A vector for sorted travelers
    std::vector<Traveler> sortedTravelers;

    // Dequeue travelers from the priority queue in order of priority (disabilities first)
    while (!priorityQueue.empty()) {
        travelerNode* node = priorityQueue.min();
        sortedTravelers.emplace_back(node->getName(), node->getCountryStatus(), node->getTravelClass(), node->getdisabilities(), node->getVeteran());
        priorityQueue.removeMin();
        delete node; // Free memory allocated for TravelerNode
    }

    return sortedTravelers;
}


/* the following immigration processing section is for the second sorting process :
   within each created sub-group of traveler country class, the travelers will again 
   be sorted (within only their own sub-groups) for prioritization based off the other
   attributes the travelers posses (traveler class, veteran, disability)
*/

// function to insert new node into a binary search tree based off priority value
travelerNode*  immigrationProcessing::bstInsert(travelerNode* root, travelerNode* node){

    if (root == NULL) return node;

    //std:: cout << root->getName() << node->getPriorityValue() << node->getName() <<  root->getPriorityValue() << std::endl;

    if (node->getPriorityValue() < root->getPriorityValue())
        root->left = bstInsert(root->left, node);
    else
        root->right = bstInsert(root->right, node);
    return root; // Return updated node
}


/* the following immigration processing section is for the third and final step, asearch structure creation :
   using all 3 sub-groups, a single binary search tree structure will be created with the root node 
   representating the passenger with the a piority value in the middle between the lowest and highest.
   This binary search tree will be used to display all the passenger based off their relative importance
   and to potentially remove passengers who were unable to make it to the immigration processing stage
*/

// function to create a binary search tree
travelerNode* immigrationProcessing::bstCreation(std::vector<std::vector<Traveler>> statusVectors) {

    // get total size of all sub groups
    size_t total_size = statusVectors[0].size() + statusVectors[1].size() + statusVectors[2].size();

    // get the middle index based off all sub-groups
    size_t secondVectorLength = statusVectors[1].size();
    size_t middleValue = secondVectorLength / 2;

    // create a new traveler node with the middle value index 
    travelerNode* root = new travelerNode(statusVectors[1][middleValue]);
    root->setPriorityValue(total_size/2);
    int count = 0 ;

    // loop through each subgroup to add to binary search tree
    for (size_t i = 0; i < statusVectors.size(); ++i) {
        for (size_t j = 0; j < statusVectors[i].size(); ++j) {

            // don't insert the middle node again
            if (i == 1 && j == middleValue) {
              continue;
            }

            // create traveler node with piority value set to the count variable
            travelerNode* node = new travelerNode(statusVectors[i][j]);
            node->setPriorityValue(count);

            // insert to binary search tree and increment count
            root = bstInsert(root, node);
            count++;
            
        }
    }

    return root;

}

// function to delete node from binary search tree
travelerNode* immigrationProcessing::deleteBSTNode(travelerNode* root, int priority) {
  // return the root node if it is null
  if (root == NULL) return root;

  // go to left node if piority value is less than
  if (priority < root->getPriorityValue())
    root->left = deleteBSTNode(root->left, priority );

  // go to right node if pirority value is greater than
  else if (priority > root->getPriorityValue())
    root->right = deleteBSTNode(root->right, priority);
  else {
    
    // if node has only one child 
    if (root->left == NULL) {
      travelerNode* temp = root->right;
      delete root;
      return temp;
    } else if (root->right == NULL) {
      travelerNode* temp = root->left;
      delete root;
      return temp;
    }
    // if node has two children
    travelerNode* temp = new travelerNode(root->right->traveler);
    while (temp->left != NULL)
      temp = temp->left;

    // replace node with inorder successor
    root->setPriorityValue(temp->getPriorityValue());
    // delete node in inorder successor
    root->right = deleteBSTNode(root->right, temp->getPriorityValue());
  }

  // return the updated root node
  return root;
}

// inorder traversal of binary search tree
void immigrationProcessing::inorder(travelerNode *root) {
  if (root != NULL) {
    // go to left subtree 
    inorder(root->left);

    // print out name and piority value of the current node
    std::cout << "Name: " << std::left << std::setw(20) << root->getName()
          << "Priority Value: " << root->getPriorityValue() << std::endl;

    // go to right subtree
    inorder(root->right);
  }
}




