#include "Graph.h"

class DAG:public Graph
{
    unordered_map<string, vector<string> > lv, lv_transpus;
    unordered_map<string, double> dist;
    deque<string> sorted;
    unordered_set<string> checked;
public:
    DAG(string name):Graph(name) {}
    void addRoad(string city1, string city2);
    void topologicalSort(string city);
    double getDistance(string city1, string city2);
};

void DAG::addRoad(string city1, string city2)
{
    lv[city1].push_back(city2);
    lv_transpus[city2].push_back(city1);
}

double DAG::getDistance(string city1, string city2)
{
    for(int i=0; i<(int)cities.size(); ++i)
        if(checked.find((string)cities[i])==checked.end())
            topologicalSort((string)cities[i]);

    for(int i=0; i<(int)cities.size(); ++i)
        dist[(string)cities[i]] = Graph::INF;

    dist[city1] = 0;
    deque<string>::iterator qt;
    vector<string>::iterator it;
    for(qt=sorted.begin(); qt!=sorted.end(); ++qt)
        for(it=lv_transpus[*qt].begin(); it!=lv_transpus[*qt].end(); ++it)
            dist[*qt]=min(dist[*qt], dist[*it]+ (cities[poz_city[*qt]] - cities[poz_city[*it]]));
    return abs(dist[city1]-dist[city2]);
}

void DAG::topologicalSort(string city)
{
    checked.insert(city);
    vector<string>::iterator it;
    for(it=lv[city].begin(); it!=lv[city].end(); ++it)
        if(checked.find(*it)==checked.end())
            topologicalSort(*it);
    sorted.push_front(city);
}
