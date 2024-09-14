
Abstract/Overview:
Airport immigration processing has always been one of the most time-consuming processes for travelers due to the huge number of people entering the United States every day. This program aims to improve efficiency by reducing the time taken to sort people and decide the priority of certain groups based on their information, including: country status (US citizen, doesn’t need a visa, needs a visa), traveler class (first class, business, economy), presence of disabilities, and veteran status. 

This program first begins by taking a text file and reading the data (formatted with comma separators) to create a vector of traveler instances. From this vector of traveler instances, the data is first sorted via either merge or quick sort based solely on their country status. The reasoning for this is that we wish to create separate subgroups of travelers based on their citizenship and visa status. From this sorted vector, we further split the vector into three sub-vectors based on each respective country status group previously mentioned. From each created sub-vector, further sorting is performed based on the other attributes the travelers have (including all but country status, as it was already used). To sort the travelers with the same country status, a priority queue and heap sort are used for sorting. We sort the travelers based on their attributes, which are as follows (in order): disabilities, first-class, veteran, business, and economy. A traveler node class is also used to construct a binary tree at first, which is used later in the heap sort process. Once the sub-group vector of the travelers had been sorted, an implementation of a binary search tree was created using all three sub-groups. From this binary search tree, priority values were given to each passenger (based on their sorted vector and their respective sub-group). These priority values were used as keys to create the binary search tree. This data structure was selected to allow efficient data access and deletion in case a passenger needs to be removed due to travel challenges or detention and to print out all travelers (based on their priority) with in-order traversal. Ultimately, this program allows for an applied showcase implementation of both efficient sorting algorithms (merge sort, quick sort, and heap sort) and data structures for data retrieval and deletion management (binary search tree). 

Future improvements to the program could possibly include a comparison of different sorting algorithms to make conclusions on which would be most suitable (which is dependent on the traveler data) and creating AVL trees rather than binary search trees to ensure a balanced tree (allowing for stable data retrieval or deletion).

Contributions:

Hieu Nguyen:
I am responsible for section I of the ImmigrationProcessing process which involves the implementation of mergeSort and quickSort to sort our dataset of traveler instances based on CountryStatus, enabling section II and III to take place.

Richard Zhou:
For this project, my job was to figure out how to sort the travelers efficiently. Heap sort immediately came to mind when I was deciding on a sorting algorithm to implement. I created a priority queue class for the use of heapsort, then proceeded to complete the class method for immigrationProcessing, completing the sorting for travelers based on their attributes. 

Benjamin Barrera-Altuna: 
My contributions to the project are as follows: I created the traveler class along with the read traveler file function which was utilized as the primary data unit. I also created the traveler node used for the heap and binary tree construction. Beyond that, my central contribution to this project was the creation of the binary search tree (including its helper functions). Finally, I assembled all the code together for a final and cohesive project. 

More details on the project can be found in the report document.

How to Run Instructions:

1. Connect to the student cluster 
2. Transfer folder with all files in zip and cd into the folder 
3. Inside the folder, run the following command: g++ -std=c++11 -Wall *.cpp
4. Once the command has finished compiling, run the following to check the outputs of the program: ./a.out -s

Side Note: if you are having trouble connecting to the student cluster, ensure you are connected to the USF VPN to access the cluster. Additionally, we recommend WinSCP to transfer the folder. 