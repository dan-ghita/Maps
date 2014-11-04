#include "Graph.h"

class CompleteGraph:public Graph
{
public:
    CompleteGraph(string name):Graph(name) {};
    double getDistance(string city1, string city2);
    void addRoad(string city1, string city2) { return; }
};

double CompleteGraph::getDistance(string city1, string city2)
{
    City<double> cityA = cities[poz_city[city1]];
    City<double> cityB = cities[poz_city[city2]];
    return (cityA - cityB);
}
