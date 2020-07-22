#include <string>

using namespace std;

class FriendNet{

public:
  FriendNet(const string fileName); // constructor
  FriendNet(const FriendNet& aNet); // copy constructor
  ~FriendNet(); // destructor

  void listFriends(const string personName, const int hopNo);
  void displayAverageDegrees();
  void displayDiameters();
private:
  // ...
  // define your data members here
  // define private class functions here, if you have any
  // YOU HAVE TO USE THE ADJACENCY LIST REPRESENTATION

  struct IDNode
  {
    int adjID;
    struct IDNode *next;
  }; // end IDNode

  struct Friend
  {
    int id;
    string name;
    int degree;
    IDNode *head;
    bool visited;
  }; // end Friend

  int size;
  Friend* people;

  void clearVisited();
  int findShortestPath(Friend* people, int u, int v, int n);
  int findMax( const int numberOne, const int numberTwo);
  bool isVisited();


};
