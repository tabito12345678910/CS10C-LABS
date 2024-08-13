#include "Jug.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std ;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {
    
    //vertices for each action possible

    //vertices for filling up each jug
    Vertex fillA("cfA");
    Vertex fillB("cfB");
    
    //vertices for emptying each jug
    Vertex emptyA("ceA");
    Vertex emptyB("ceB");

    //vertices for pouring from each jug to the other
    Vertex pourAB("cpAB");
    Vertex pourBA("cpBA");


    //push back steps and cost into list
    fillA.pairs.push_back(pair<int, int>(1, cfB));
    fillA.pairs.push_back(pair<int, int>(4, cpAB));
    fillB.pairs.push_back(pair<int, int>(0, cfA));
    fillB.pairs.push_back(pair<int, int>(5, cpBA));
    emptyA.pairs.push_back(pair<int, int>(1, cfB));
    emptyA.pairs.push_back(pair<int, int>(3, ceB));
    emptyA.pairs.push_back(pair<int, int>(5, cpBA));
    emptyB.pairs.push_back(pair<int, int>(0, cfA));
    emptyB.pairs.push_back(pair<int, int>(2, ceA));
    emptyB.pairs.push_back(pair<int, int>(4, cpAB));
    pourAB.pairs.push_back(pair<int, int>(0, cfA));
    pourAB.pairs.push_back(pair<int, int>(3, ceB));
    pourAB.pairs.push_back(pair<int, int>(5, cpBA));
    pourBA.pairs.push_back(pair<int, int>(0, cfA));
    pourBA.pairs.push_back(pair<int, int>(1, cfB));
    pourBA.pairs.push_back(pair<int, int>(2, ceA));
    pourBA.pairs.push_back(pair<int, int>(3, ceB));
    pourBA.pairs.push_back(pair<int, int>(4, cpAB));

    graph.push_back(fillA);  
    graph.push_back(fillB);  
    graph.push_back(emptyA);  
    graph.push_back(emptyB);  
    graph.push_back(pourAB);
    graph.push_back(pourBA); 
}

    //solve is used to check input and find the solution if one exists
    //returns -1 if invalid inputs. solution set to empty string.
    //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
    //returns 1 if solution is found and stores solution steps in solution string.
        
int Jug::solve(string& solution) {
    if (!isValidInputs()) {
        solution.clear();
        return -1;
    }

    vector<int> steps = puzzleSolved();
    if (steps.empty()) {
        solution.clear();
        return 0;
    }

    processString(steps, solution);
    return 1;
}

Jug::~Jug(){}

bool Jug::isValidInputs() const{
    return (N >= 0 && cfA >= 0 && cfB >= 0 && ceA >= 0 && ceB >= 0 && cpAB >= 0 && cpBA >= 0)
        && (Ca > 0 && Ca <= Cb) && (N <= Cb && Cb <= 1000);
}




int Jug::processString(vector<int>& steps, string& solution) const {
    ostringstream outSS;
    int total = 0;

    for (unsigned i = 0; i < steps.size(); ++i) {
        if (steps.at(i) == 0) {
            total += cfA;
            outSS << "fill A" << endl;
        } else if (steps.at(i) == 1) {
            total += cfB;
            outSS << "fill B" << endl;
        } else if (steps.at(i) == 2) {
            total += ceA;
            outSS << "empty A" << endl;
        } else if (steps.at(i) == 3) {
            total += ceB;
            outSS << "empty B" << endl;
        } else if (steps.at(i) == 4) {
            total += cpAB;
            outSS << "pour A B" << endl;
        } else if (steps.at(i) == 5) {
            total += cpBA;
            outSS << "pour B A" << endl;
        }
    }

    outSS << "success " << total;
    solution = outSS.str();

    return total;
}

int Jug::TotalCost(vector<int> steps) {
    int total = 0;

    int stepCosts[] = {cfA, cfB, ceA, ceB, cpAB, cpBA};

    for (unsigned i = 0; i < steps.size(); ++i) {
        int step = steps.at(i);
        if (step >= 0 && step < 6) {
            total += stepCosts[step];
        }
    }

    return total;
}


vector<int> Jug::puzzleSolved() {
    list<pair<int, int>> route;
    vector<int> aSteps;
    vector<int> bSteps;

    route.push_back(make_pair(0, 0));
    aSteps = traverse(0, aSteps, route);
    bSteps = traverse(1, bSteps, route);

    if (aSteps.empty())
    {
        return bSteps;
    }
    else if (bSteps.empty())
    {
        return aSteps;
    }

    return TotalCost(aSteps) < TotalCost(bSteps) ? aSteps : bSteps;
}


int Jug::doStep(int& aAmount, int& bAmount, const int& stepIndex) {
    const auto& key = graph.at(stepIndex).cost;

    if (key == "cfA") {
        aAmount = Ca;
    } else if (key == "cfB") {
        bAmount = Cb;
    } else if (key == "ceA") {
        aAmount = 0;
    } else if (key == "ceB") {
        bAmount = 0;
    } else if (key == "cpAB") {
        const int space = Cb - bAmount;
        const int transfer = min(space, aAmount);
        bAmount += transfer;
        aAmount -= transfer;
    } else if (key == "cpBA") {
        const int space = Ca - aAmount;
        const int transfer = min(space, bAmount);
        aAmount += transfer;
        bAmount -= transfer;
    }

    return stepIndex;
}

bool Jug::correctCap(list<pair<int, int>> route) {
    return route.back().first == 0 && route.back().second == N;
}

vector<int> Jug::traverse(int stepIndex, vector<int> steps, list<pair<int, int>> route) {
    vector<int> vect;
    vector<int> vectAlt;

    int aAmount;
    int bAmount;
    int stepTaken;

    if (correctCap(route)){
        return steps;
    }
    
    auto it = graph.at(stepIndex).pairs.begin();

    while (it != graph.at(stepIndex).pairs.end()) {
        aAmount = route.back().first;
        bAmount = route.back().second;
        stepTaken = doStep(aAmount, bAmount, it->first);

        if (!cycle(aAmount, bAmount, route)) {
            steps.push_back(stepTaken);
            route.push_back(pair<int, int>(aAmount, bAmount));
            
            if (vect.size() == 0) {
                vect = traverse(stepTaken, steps, route);
            } else {
                vectAlt = traverse(stepTaken, steps, route);
                if (TotalCost(vect) > TotalCost(vectAlt)) {
                    vect = vectAlt;
                }
            }

            steps.pop_back();
            route.pop_back();
        }

        it++;
    }

    return vect;
}

bool Jug::cycle(int aAmount, int bAmount, list<pair<int, int>> route) {
    auto it = route.begin();

    while (it != route.end()) {
        if (it->first == aAmount && it->second == bAmount) {
            return true;
        }

        it++;
    }

    return false;
}