#pragma once
#include "City.h"

class Graph
{
    string region_name;
protected:
    unordered_map<string, int> poz_city;
    vector<City<double>> cities;
public:
    static const int INF = 99999999;
    Graph(string name):region_name(name){}
    ~Graph(){
        cities.clear();
        poz_city.clear();
        region_name.clear();
        cout<<"Region deleted\n\n";
    }
    operator string ();
    void addCity(City<double>);
    bool checkCity(string);
    bool checkCity(City<double>);
    virtual void addRoad(string city1, string city2) = 0;
    virtual double getDistance(string city1, string city2) = 0;

};


bool Graph::checkCity(string city)
{
    if(poz_city.find(city)!=poz_city.end())
        return true;
    else
        return false;
}

bool Graph::checkCity(City<double> city)
{
    return checkCity((string)city);
}


void Graph::addCity(City<double> city)
{
    cities.push_back(city);
    poz_city[city.name] = cities.size()-1;
}

Graph::operator string(){
        return region_name;
};
