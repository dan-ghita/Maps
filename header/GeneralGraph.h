#include "Graph.h"

class Cost
{
protected:
    unordered_map<string, double> cost;
public:
    bool operator()(const string &X, const string &Y)
    {
        return cost[X]<cost[Y];
    }
};

class GeneralGraph:public Graph, public Cost
{
    priority_queue<string, vector<string>, Cost> city_queue;
    unordered_map<string, vector< pair<string, double> > > lv; //lista de vecini/adiacenta
    double dijkstra(string city1, string city2);
public:
    GeneralGraph(string name):Graph(name) {}
    void addRoad(string city1, string city2);
    double getDistance(string city1, string city2)
    {
        return dijkstra(city1, city2);
    };
};

void GeneralGraph::addRoad(string city1, string city2)
{
    double dist = cities[poz_city[city1]] - cities[poz_city[city2]];
    lv[city1].push_back(make_pair(city2, dist));
    lv[city2].push_back(make_pair(city1, dist));
}

double GeneralGraph::dijkstra(string city1, string city2)
{
    string current_city;
    vector< pair<string, double> >::iterator it;
    for(int i=0; i<(int)cities.size(); ++i) cost[cities[i].name] = Graph::INF; //init
    cost[city1]=0;
    city_queue.push(city1);
    while(city_queue.size())
    {
        current_city=city_queue.top();
        city_queue.pop();
        for(it=lv[current_city].begin(); it!=lv[current_city].end(); ++it)
            if(cost[(*it).first]>cost[current_city]+(*it).second)
                cost[(*it).first]=cost[current_city]+(*it).second, city_queue.push((*it).first);
    }
    return cost[city2];
}
