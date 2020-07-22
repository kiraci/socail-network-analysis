# Social Network

This is an computer program that reveals the relations in a group of people with the help of a adjacency list. The program uses breadth first search algorithm to understand the links between people in the group. Please look at the pdf file to understand how it works and what is the output. You can send me an e-mail if you have any questions or suggesstions ( osmanbugraaydin@gmail.com ).

### Installation

- Type just "make" in the terminal
- Type "./simulator_Q1" or type "." and press tab to auto complete
- THEN YOU HAVE THE OUTPUT :)


#### There are three main functions which are:

-void listFriends(const string personName, const int hopNo)

    It lists the names of all people that are accessible from a given person, whose name is personName, within the given number hopNo of hops (i.e., using at most hopNo edges). If this given person does not take place in the friendship network, give a warning message. If the given number of hops is non- positive, do not list any people. See the output example below for the format. You may assume that the names are unique within the friendship network.
    
-void displayAverageDegrees()

    It calculates and displays the average degree of each connected component within the friendship network. The degree of a vertex is defined as the number of its neighbors. The average degree of a connected component is the mean of the degrees computed for every vertex in this connected component. See the output example below for the format.

-void displayDiameters()

    It calculates and displays the diameter of each connected component within the friendship network. The diameter of a connected component is the longest of the shortest paths between any pair of vertices within this connected component. See the output example below for the format.
    
Details about the program can be found in the pdf file.

###### This is an project-homework of Bilkent University CS202 class.
