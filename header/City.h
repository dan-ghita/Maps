#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <deque>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#define enter cout<<'\n'

using namespace std;

template<class coord_type>
class City
{
    friend class Graph;
    friend class CompleteGraph;
    friend class LinearGraph;
    friend class GeneralGraph;
    friend class DAG;
    friend class Tree;

    coord_type x, y; //city coordinates
    string name;

public:
    double operator - (const City &B)
    {
        return sqrt((x-B.x)*(x-B.x)+(y-B.y)*(y-B.y));
    }
    City(string city_name, coord_type x, coord_type y)
    {
        name=city_name;
        this->x=x;
        this->y=y;
    }
    operator string (){
        return name;
    };
};
