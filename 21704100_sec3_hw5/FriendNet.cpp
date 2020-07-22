#include <iostream>
#include "FriendNet.h"
#include "Queue.h"
#include <string>
#include <fstream>

using namespace std;

/*
* Constructor From File
* Checkpoint 1 -> Opens the file
* Checkpoint 2 -> Takes inputs from file
* Checkpoint 3 -> If the degree is non-zero, it loops degree times and creates a linked list
*/
FriendNet::FriendNet(const string fileName){

  //<---------Checkpoint 1---------->

  ifstream file( fileName.c_str() );

  file >> size;

  people = new Friend[ size ];

  int id;
  string name;
  int degree;
  int counter = 0;

  //<---------Checkpoint 2---------->

  while(file >> id >> name >> degree){

    Friend human;
    human.id = id;
    human.name = name;
    human.degree = degree;

    //<---------Checkpoint 3---------->

    if( degree == 0 ){
      human.head = NULL;
    }else{
        IDNode* head = new IDNode;
        human.head = head;
        bool first = true;

        while ( degree != 0) {
          int friendIDs;
          file >> friendIDs;

          if( first ){
            first = false;
            head->adjID = friendIDs;
            head->next = NULL;
          }else{
            IDNode* newNode = new IDNode;
            newNode->adjID = friendIDs;
            newNode->next = NULL;

            head->next = newNode;
            head = head->next;
          }

          degree--;
      }
    }
    people[ counter ] = human;
    counter++;
  }

} // constructor
/*
* Constructor From Another Object
* Copies the people array and size
*/
FriendNet::FriendNet(const FriendNet& aNet){
  this->size = aNet.size;

  people = new Friend[ size ];

  for (int i = 0; i < size; i++) {
    people[i] = aNet.people[i];
  }

} // copy constructor
/*
* First clears the linked list which is adjacents of every person
* Second delete the people
*/
FriendNet::~FriendNet(){

  for (int i = 0; i < size; i++) {
    IDNode* head = people[i].head;
    while ( head != NULL) {
      IDNode* temp = head->next;
      delete head;
      head = temp;
    }
  }

    delete[] people;

} // destructor
/*
* Constructor From File
* Checkpoint 1 -> Finds the people with the given name and returns his id
* Checkpoint 2 -> Checks for the exceptions
* Checkpoint 3 -> Finds the distance between people with the help of BFS
* Checkpoint 4 -> Prints the people who are reachable with given hop numbers
*/
void FriendNet::listFriends(const string personName, const int hopNo){

  //<---------Checkpoint 1---------->

  clearVisited();

  // Traverses a graph beginning at vertex v
  // by using breadth-first strategy: Iterative Version
  Queue q;
	// add v to the queue and mark it
  int v = -1;
  for (int i = 0; i < size; i++) {
    if ( people[i].name == personName ) {
      people[i].visited = true;
      v = people[i].id;
    }
  }

  //<---------Checkpoint 2---------->

  if ( v == -1) {
    cout << personName << " does not exist in the network." << endl;
    return;
  }else if( hopNo <= 0 ){
    cout << "People accessible from " << personName << " within " << hopNo << " hops: NOBODY" << endl;
    return;
  }else if( people[v].degree == 0 ){
    cout << "People accessible from " << personName << " within " << hopNo << " hops: NOBODY" << endl;
    return;
  }

  //<---------Checkpoint 3---------->

  cout << "People accessible from " << personName << " within " << hopNo << " hops: ";

  int distance[size];
  for (int i = 0; i < size; i++) {
    distance[i] = 0;
  }

  q.enqueue(v);
  int front = 0;
  while (!q.isEmpty())
  {
      q.getFront( front );
      q.dequeue();

      IDNode* head = people[front].head;
      while ( head != NULL ) {
        if( !people[ head->adjID ].visited ){
          people[ head->adjID ].visited = true;
          q.enqueue( head->adjID );
          distance[head->adjID] = distance[front] + 1;
        }
        head = head->next;
      }
  }

  //<---------Checkpoint 4---------->

  for (int i = 0; i < size; i++) {
    if ( distance[i] <= hopNo && distance[i] != 0) {
      cout << people[i].name << " ";
    }

  }
  cout << endl;
}
/*
* Constructor From File
* Checkpoint 1 -> It goes in the given graph with BFS and tags component numbers until all people is visited
* Checkpoint 2 -> Prints the results
*/
void FriendNet::displayAverageDegrees(){

  //<---------Checkpoint 1---------->

  clearVisited();

  int compNumbers[size];
  int compNumber = 0;

  int itemToStart = 0;

  bool allVisited = false;

  while ( !allVisited ) {
    for (itemToStart = 0; itemToStart < size && people[itemToStart].visited == true; itemToStart++) {}

    compNumbers[itemToStart] = compNumber;

    Queue q;

    q.enqueue(itemToStart);
    people[itemToStart].visited = true;
    int front = 0;
    while (!q.isEmpty())
    {
        q.getFront( front );
        q.dequeue();

        IDNode* head = people[front].head;
        while ( head != NULL ) {
          if( !people[ head->adjID ].visited ){
            people[ head->adjID ].visited = true;
            q.enqueue( head->adjID );
            compNumbers[head->adjID] = compNumber;
          }
          head = head->next;
        }
    }

    compNumber++;
    allVisited = isVisited();
  }

  //<---------Checkpoint 2---------->

  double averages[ compNumber ];
  int num[compNumber];

  for (int i = 0; i < compNumber; i++) {
    averages[i] = 0;
    num[i] = 0;
  }

  for (int i = 0; i < size; i++) {
    averages[ compNumbers[i] ] += people[ i ].degree;
    num[ compNumbers[i] ] += 1;
  }

  for (int i = 0; i < compNumber; i++) {
    averages[ i ] = averages[ i ] / num[ i ];
  }

  cout << "There are " << compNumber << " connected components. The average degrees are:" << endl;

  for (int i = 0; i < compNumber; i++) {
    cout << "For component " << i << ": " << averages[i] << endl;
  }
}
/*
* Constructor From File
* Checkpoint 1 -> It goes in the given graph with BFS and tags component numbers until all people is visited
* Checkpoint 2 -> It finds the shortest path between all possible vertices in the same components and assigns maximum path
*/
void FriendNet::displayDiameters(){

  //<---------Checkpoint 1---------->

  clearVisited();

  int compNumbers[size];
  int compNumber = 0;

  int itemToStart = 0;

  bool allVisited = false;

  while ( !allVisited ) {
    for (itemToStart = 0; itemToStart < size && people[itemToStart].visited == true; itemToStart++) {}

    compNumbers[itemToStart] = compNumber;

    Queue q;

    q.enqueue(itemToStart);
    people[itemToStart].visited = true;
    int front = 0;
    while (!q.isEmpty())
    {
        q.getFront( front );
        q.dequeue();

        IDNode* head = people[front].head;
        while ( head != NULL ) {
          if( !people[ head->adjID ].visited ){
            people[ head->adjID ].visited = true;
            q.enqueue( head->adjID );
            compNumbers[head->adjID] = compNumber;
          }
          head = head->next;
        }
    }

    compNumber++;
    allVisited = isVisited();
  }

  //<---------Checkpoint 2---------->

  int diameters[ compNumber ];

  for (int i = 0; i < compNumber; i++) {
    diameters[i] = 0;
  }


  int max = 0;

  for (int i = 0; i < size; i++) {
    for (int a = i; a < size; a++) {
      if( a != i && compNumbers[a] == compNumbers[i]){
        int path = findShortestPath( people, people[i].id, people[a].id, size);
        max = findMax( path, diameters[compNumbers[i]]);
        diameters[compNumbers[i]] = max;
      }
    }
  }

  cout << "There are " << compNumber << " connected components. The diameters are:" << endl;

  for (int i = 0; i < compNumber; i++) {
    cout << "For component " << i << ": " << diameters[i] << endl;
  }

}
/*
* Checks if all people are visited
*/
bool FriendNet::isVisited(){
  bool allVisited = true;

  for (int i = 0; i < size; i++) {
    if ( people[i].visited != true) {
      allVisited = false;
    }
  }

  return allVisited;
}
/*
* Returns the maximum number between two
*/
int FriendNet::findMax( const int numberOne, const int numberTwo){

  int max = numberTwo;

  if ( numberOne > numberTwo) {
    max = numberOne;
  }

  return max;
}
/*
* Clears all people's visited property
*/
void FriendNet::clearVisited(){
  for (int i = 0; i < size; i++) {
    people[i].visited = false;
  }
}
/*
* Finds the shortest path from source to destination with the help of BFS
*/
int FriendNet::findShortestPath(Friend* people, int source, int destination, int n){

    clearVisited();

    int distance[size];
    Queue q;
    distance[source] = 0;

    q.enqueue(source);
    people[source].visited = true;
    int front = 0;
    while (!q.isEmpty())
    {
        q.getFront( front );
        q.dequeue();

        IDNode* head = people[front].head;
        while ( head != NULL ) {
          if( !people[ head->adjID ].visited ){
            people[ head->adjID ].visited = true;
            q.enqueue( head->adjID );
            distance[head->adjID] = distance[front] + 1;
          }
          head = head->next;
        }

    }
    return distance[destination];
}
