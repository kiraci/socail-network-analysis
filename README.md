# Social Network

This is an computer program that understands the relations in a group of people with the help of a adjecncy list. You can send me an e-mail if you have any questions or suggesstions ( osmanbugraaydin@gmail.com ).

There are three main functions which are: 

-void listFriends(const string personName, const int hopNo)

    It lists the names of all people that are accessible from a given person, whose name is personName, within the given number hopNo of hops (i.e., using at most hopNo edges). If this given person does not take place in the friendship network, give a warning message. If the given number of hops is non- positive, do not list any people. See the output example below for the format. You may assume that the names are unique within the friendship network.
    
-void displayAverageDegrees()

    It calculates and displays the average degree of each connected component within the friendship network. The degree of a vertex is defined as the number of its neighbors. The average degree of a connected component is the mean of the degrees computed for every vertex in this connected component. See the output example below for the format.

-void displayDiameters()

    It calculates and displays the diameter of each connected component within the friendship network. The diameter of a connected component is the longest of the shortest paths between any pair of vertices within this connected component. See the output example below for the format.
    
Details about the program can be found in the pdf file
