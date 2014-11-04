#include "Graph.h"
#include <stdlib.h>
#include <time.h>

class Tree:public Graph
{
    unordered_map<string, vector<string> > lv;
    unordered_map<string, int> lvl, lca;
    unordered_map<string, double> dist;
    unordered_set<string> checked;
    vector<string> a[20];
    string root;
    int sz;
    void RMQ();
    void getLvl(string city);
    void getRoadCost(string city);
    void euler_tour(string city);
    string LCA(string city1, string city2);
public:
    void setRoot();
    Tree(string name):Graph(name) {};
    void addRoad(string city1, string city2);
    double getDistance(string city1, string citi2);
};

void Tree::setRoot(){
    int random_root;
    srand (time(NULL));
    random_root = rand() % cities.size();
    root = (string)cities[random_root];
    cout<<"Root set to: "<<root; enter; enter;
}

void Tree::addRoad(string city1, string city2)
{
    lv[city1].push_back(city2);
    lv[city2].push_back(city1);
    lvl[root]=0;

    checked.clear();
    getLvl(root);

    checked.clear();
    a[0].clear();
    euler_tour(root);

    checked.clear();
    RMQ();

    lca.clear();
    for(int i=0; i<sz; ++i)
        if(lca.find(a[0][i])==lca.end()) lca[a[0][i]]=i; //prima aparitie a orasului in parcurgerea euler

    checked.clear();
    dist.clear();
    dist[root] = 0;
    getRoadCost(root);
}

void Tree::euler_tour(string city)
{
    checked.insert(city);
    a[0].push_back(city);
    vector<string>::iterator it;
    for(it=lv[city].begin(); it!=lv[city].end(); ++it)
        if(checked.find(*it)==checked.end())
            euler_tour(*it), a[0].push_back(city);
}

void Tree::getLvl(string city)
{
    checked.insert(city);
    vector<string>::iterator it;
    for(it=lv[city].begin(); it!=lv[city].end(); ++it)
        if(checked.find(*it)==checked.end())
            lvl[*it]=lvl[city]+1, getLvl(*it);
}

void Tree::getRoadCost(string city)
{
    checked.insert(city);
    vector<string>::iterator it;
    for(it=lv[city].begin(); it!=lv[city].end(); ++it)
        if(checked.find(*it)==checked.end())
            dist[*it]=dist[city]+(cities[poz_city[city]]-cities[poz_city[*it]]), getRoadCost(*it);
}

void Tree::RMQ()
{
    sz = a[0].size();
    for(int i=0; i<20; ++i)
        a[i].resize(sz*sz);
    for(int i=sz-1; i>=0; --i)
        for(int k=1; (1<<k)<=sz; ++k)
            if(lvl[a[k-1][i]]<lvl[a[k-1][i+(1<<(k-1))]])
                a[k][i]=a[k-1][i];
            else
                a[k][i]=a[k-1][i+(1<<(k-1))];
}

string Tree::LCA(string city1, string city2)
{
    int x=lca[city1];
    int y=lca[city2];
    if(y<x) swap(x,y);
    int p=(int)log2(y-x+1);
    if(lvl[a[p][x]]<lvl[a[p][y-(1<<p)+1]])
        return a[p][x];
    else
        return a[p][y-(1<<p)+1];
}

double Tree::getDistance(string city1, string city2)
{
    string stramos = LCA(city1, city2);
    return dist[city1]+dist[city2]-2*dist[stramos];
}
