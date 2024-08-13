#ifndef JUG_H
#define JUG_H

#include <list>
#include <string>
#include <vector>

using namespace std;

//Creat vertices for the graph
struct Vertex {
  string cost;
  list<pair<int , int >> pairs;
  Vertex(string c) : cost(c) {} //constructor
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        //anything else you need

        //capacity of Jugs A and B
        int Ca; 
        int Cb;
        //Target gallon
        int N;
        //cost to fill Jugs A and B
        int cfA;
        int cfB;
        //cost to empty Jugs A and B
        int ceA;
        int ceB;
        //cost to pour from Jug A to B and Jug B to A
        int cpAB;
        int cpBA;
        vector<Vertex> graph;

        bool isValidInputs() const; // Check if the inputs are valid
        bool correctCap(list<pair<int, int>>); //confirms if capacity and goal checks out
        int processString(vector<int>&, string&) const;
        int TotalCost(vector<int> steps); //tallys total cost
        vector<int> puzzleSolved(); //checks if solvable
        int doStep(int&, int&, const int&); //executes step
        vector<int> traverse(int, vector<int>, list<pair<int, int>>); //traverses through graph
        bool cycle(int, int, list<pair<int, int>>); //checks if it cycled
        
};






#endif