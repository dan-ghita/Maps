#include "header/CompleteGraph.h"
#include "header/LinearGraph.h"
#include "header/GeneralGraph.h"
#include "header/DAG.h"
#include "header/Tree.h"
#include <new>

void printMenu(){
cout<<"Menu: \n";
    cout<<"* create-region (create new region)\n";
    cout<<"* add-road (add road between two existing cities)\n";
    cout<<"* get-distance (returns distance between two existing cities)\n";
    cout<<"* STOP (ends program)";
    enter; enter; enter;
}

class CustomException{
string message;
public:
    CustomException(string msg):message(msg){};
    string getMessage(){ return message; }
};

int main()
{
    ifstream f("harti.in");
    printMenu();

    vector< Graph* > Regions;
    unordered_map<string, int> poz_regions; //pozitia orasului in Regions

    string graph_type, command, region_name, city_name, tree_root, city1, city2;
    double x, y, distance; //coordonatele orasului
    int nr_cities;

    do
    {
        cout<<"Command type: ";
        cin>>command; enter;
        if(command == "create-region")
        {
            cout<<"Region name: "; cin>>region_name; enter;
            if(poz_regions.find(region_name)!=poz_regions.end())
            {
                cout<<"Region already exists!\n\n";
                continue;
            }

            cout<<"Region type: "; cin>>graph_type; enter;

            Graph *new_region;

            try{
                if(graph_type == "complete")
                    new_region = new CompleteGraph(region_name);
                else if(graph_type == "linear")
                    new_region = new LinearGraph(region_name);
                else if(graph_type == "general")
                    new_region = new GeneralGraph(region_name);
                else if(graph_type == "dag")
                    new_region = new DAG(region_name);
                else if(graph_type == "tree")
                    new_region = new Tree(region_name);
                else throw new CustomException("Region type not defined! \n\n");
            }
            catch(bad_alloc& ex){
                cout<<"Bad memory allocation exception caught!\n\n";
            }
            catch(CustomException* exc){
                cout<<exc->getMessage();
                continue;
            }

            Regions.push_back(new_region);

            poz_regions[region_name] = Regions.size()-1;
            int i=poz_regions[region_name];

            cout<<"Number of cities: "; cin>>nr_cities; enter;
            while(!nr_cities){
                cout<<"Region can not be empty!\n\n";
                cout<<"Number of cities: "; cin>>nr_cities; enter;
            }
            while(nr_cities--)
            {
                cout<<"City name: "; cin>>city_name; enter;
                if(Regions[i]->checkCity(city_name)){
                    cout<<city_name<<" is already inserted in "<<region_name, enter;
                    continue;
                }
                cout<<"City cordinates: "; cin>>x>>y; enter;
                City<double> oras(city_name, x, y);
                Regions[i]->addCity(oras);
            }
            if(graph_type == "tree"){
                cout<<"Root will be randomly selected: "; enter; enter;
                dynamic_cast<Tree*>(Regions[i])->setRoot();
            }

            cout<<(string)(*Regions[i])<<" - region added\n\n";

        }

        else if(command == "add-road")
        {
            cout<<"Region name: "; cin>>region_name; enter;
            if(poz_regions.find(region_name)==poz_regions.end())
            {
                cout<<"Region does not exist!\n\n";
                continue;
            }
            int i=poz_regions[region_name];
            cout<<"Road start: "; cin>>city1; enter;
            if(!Regions[i]->checkCity(city1)){
                cout<<"Error: city "<<city1<<" is not in this region\n\n";
                continue;
            }
            cout<<"Road end: "; cin>>city2; enter;
            if(!Regions[i]->checkCity(city2)){
                cout<<"Error: city "<<city2<<" is not in this region\n\n";
                continue;
            }
            Regions[i]->addRoad(city1, city2);
            cout<<"Road added between "<<city1<<" and "<<city2; enter; enter;
        }
        else if(command == "get-distance")
        {
            cout<<"Region name: ";
            cin>>region_name;
            enter;
            if(poz_regions.find(region_name)==poz_regions.end())
            {
                cout<<"Region does not exist!\n\n";
                continue;
            }
            int i=poz_regions[region_name];
            cout<<"First city: "; cin>>city1; enter;
            if(!Regions[i]->checkCity(city1)){
                cout<<city1<<" is not in region "<<region_name; enter; enter;
                continue;
            }
            cout<<"Second city: "; cin>>city2; enter;
            if(!Regions[i]->checkCity(city2)){
                cout<<city2<<" is not in region "<<region_name; enter; enter;
                continue;
            }

            distance = Regions[i]->getDistance(city1, city2);
            if(distance != Graph::INF)
                cout<<"Minimum distance between "<<city1<<" and "<<city2<<" is "<<distance, enter, enter;
            else
                cout<<city2<<" is not reachable from "<<city1, enter, enter;
        }
        else
            if(command != "STOP") cout<<"Error: undefined action!\n\n";
    }
    while(command != "STOP");
    return 0;
}
