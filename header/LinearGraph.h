#include "Graph.h"

class LinearGraph:public Graph
{
    deque<string> city_queue;
    unordered_map<string, double> sum_left, sum_right; //retin sumele partiale la dreapta si la stanga fata de orasul 0
public:
    LinearGraph(string name):Graph(name) {};
    void addRoad(string city1, string city2);
    double getDistance(string city1, string city2);
};

void LinearGraph::addRoad(string city1, string city2)
{
    City<double> cityA = cities[poz_city[city1]];
    City<double> cityB = cities[poz_city[city2]];
    if(city_queue.empty()) //adaug ambele orase daca coada este goala si setez city1 ca orasul 0
    {
        city_queue.push_back(city1);
        city_queue.push_back(city2);
        sum_left[city1] = 0;
        sum_right[city2] = cityB - cityA;
    }
    else if(city2 == city_queue.front()) //adaug orasul A la inceput
    {
        city_queue.push_front(city1);
        sum_left[city1] = sum_left[city2] + (cityB - cityA);
    }
    else  if(city1 == city_queue.back())//adaug orasul B la final
    {
        city_queue.push_back(city2);
        sum_right[city2] = sum_right[city1] + (cityB - cityA);
    }
    else
        cout<<"Road can not be added to linear graph's end or beginning \n\n";
}

double LinearGraph::getDistance(string city1, string city2)
{
    return abs(max(sum_left[city1], sum_right[city1]) - max(sum_left[city2], sum_right[city2]));
}
