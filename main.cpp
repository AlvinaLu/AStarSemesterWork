#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <queue>
#include "Entity.h"
#include "Mapa.h"
#include "Result.h"
#include "Grid.h"
#include "Priority.h"
#include <unordered_map>

void cost(Entity entity, Entity entity1);

using namespace std;

auto read(string str) {
    ifstream inf(str);
    int width, height, countBarrier, x, y;

    inf >> width;
    inf >> height;
    inf >> countBarrier;
    Grid grid(width, height);


    //Start
    inf >> x;
    inf >> y;
    Entity start = {x, y};
    grid.setStart(start);
    //Finish
    inf >> x;
    inf >> y;
    Entity finish = {x, y};
    grid.setFinish(finish);

    //Barriers
    vector<Entity> walls;
    while (countBarrier > 0) {
        inf >> x;
        inf >> y;
        walls.push_back({x, y});
        countBarrier--;
    }
    grid.setWalls(walls);
    return grid;

}

void print(Grid grid) {
    for(int i=0; i< grid.getMWight(); i++){
        for(int j=0; j< grid.getMHeight(); j++){
            Entity entity = {i, j};
            if(grid.isNotWall(entity)){
                if(grid.getFinish().m_x == entity.m_x && grid.getFinish().m_y == entity.m_y){
                    cout << "F" << " ";
                }else if(grid.getStart().m_x == entity.m_x && grid.getStart().m_y == entity.m_y){
                    cout << "S" << " ";
                } else{cout << "\u00b7" << " ";}
            }else{
                cout << "#" << " ";
            }

        }
        cout << endl;
    }
}
void print(Grid grid, map<Entity, Entity> cameFrom) {
    for(int i=0; i< grid.getMWight(); i++){
        for(int j=0; j< grid.getMHeight(); j++){
            Entity entity = {i, j};
            if(grid.isNotWall(entity)){
                if(cameFrom.count({i, j})){
                    Entity from = cameFrom.find({i, j})->first;
                    Entity to = cameFrom.find({i, j})->second;
                    if(grid.getStart() == entity) {
                        cout << "S" << " ";
                    }
                    else if(grid.getFinish() == entity) {
                        cout << "F" << " ";
                    }else if(from.m_x == to.m_x && (from.m_y-to.m_y)==1){
                        cout << "\u2190" << " ";
                    }
                    else if(from.m_x == to.m_x && (from.m_y-to.m_y)==-1){
                        cout << "\u2192" << " ";
                    }
                    else if((from.m_x-to.m_x)==-1 && from.m_y == to.m_y){
                        cout << "\u2193" << " ";
                    }
                    else if((from.m_x-to.m_x)==1 && from.m_y == to.m_y){
                        cout << "\u2191" << " ";
                    }else {
                        cout << "\u00b7" << " ";
                    }
                } else{
                    cout << "\u00b7" << " ";
                }
            }else{
                cout << "#" << " ";
            }

        }
        cout << endl;
    }
}
void printFormStart(Grid grid, map<Entity, Entity> cameFrom) {
    for(int i=0; i< grid.getMWight(); i++){
        for(int j=0; j< grid.getMHeight(); j++){
            Entity entity = {i, j};
            if(grid.isNotWall(entity)){
                if(cameFrom.count({i, j})){
                    Entity from = cameFrom.find({i, j})->first;
                    Entity to = cameFrom.find({i, j})->second;
                    if(grid.getStart() == entity) {
                        cout << "S" << " ";
                    }
                    else if(grid.getFinish() == entity) {
                        cout << "F" << " ";
                    }else if(from.m_x == to.m_x && (from.m_y-to.m_y)==-1){
                        cout << "\u2190" << " ";
                    }
                    else if(from.m_x == to.m_x && (from.m_y-to.m_y)==1){
                        cout << "\u2192" << " ";
                    }
                    else if((from.m_x-to.m_x)==1 && from.m_y == to.m_y){
                        cout << "\u2193" << " ";
                    }
                    else if((from.m_x-to.m_x)==-1 && from.m_y == to.m_y){
                        cout << "\u2191" << " ";
                    }else {
                        cout << "\u00b7" << " ";
                    }
                } else{
                    cout << "\u00b7" << " ";
                }
            }else{
                cout << "#" << " ";
            }

        }
        cout << endl;
    }
}
const bool Contains( std::vector<Entity>& Vec, const Entity& Element )
{
    if (std::find(Vec.begin(), Vec.end(), Element) != Vec.end())
        return true;

    return false;
}
void printWay(Grid grid, vector<Entity> way) {
    for(int i=0; i< grid.getMWight(); i++){
        for(int j=0; j< grid.getMHeight(); j++){
            Entity entity = {i, j};
            if(grid.isNotWall(entity)){
                if(Contains(way, entity)){
                    if(grid.getStart() == entity) {
                        cout << "S" << " ";
                    }
                    else if(grid.getFinish() == entity) {
                        cout << "F" << " ";
                    }else {
                        cout << "*" << " ";
                    }
                } else{
                    cout << "\u00b7" << " ";
                }
            }else{
                cout << "#" << " ";
            }

        }
        cout << endl;
    }
}

void simpleFind(Grid grid){
    std::queue<Entity> queue;
    queue.push(grid.getStart());
    Entity tmp = {-1, -1};

    std::map<Entity, Entity> cameFrom;
    cameFrom.insert(std::make_pair(grid.getStart(), grid.getStart()));

    while (!queue.empty()){
        auto current = queue.front();
        queue.pop();
        if(current == grid.getFinish()){
            break;
        }

        auto neighbors = grid.neighbors(current);

        for(auto item : neighbors){

            if(!cameFrom.count(item)){
                queue.push(item);
                cameFrom.insert(pair<Entity, Entity>(item, current));
            }
        }
    }
    cout << "\n";
    print(grid, cameFrom);
}
vector<Entity> getWay(Grid grid,  map<Entity, Entity> cameFrom){
    vector<Entity> way;
    Entity current = grid.getFinish();
    way.push_back(current);
    while (!(current == grid.getStart())){
        current = cameFrom.at(current);
        way.push_back(current);
    }
    way.push_back(grid.getStart());

    return way;

}

int main() {

    string path = "../datapub/pub02.in";

    auto grid = read(path);
    print(grid);

    //std::priority_queue<Entity> queue;
    std::priority_queue<Priority, std::vector<Priority>, std::greater<Priority>> priorityQueue;
    priorityQueue.push({grid.getStart(), 0});

    std::map<Entity, Entity> cameFrom;
    cameFrom.insert(std::make_pair(grid.getStart(), grid.getStart()));
    std::map<Entity, int> totalCost;

    while (!priorityQueue.empty()){
        auto current = priorityQueue.top().entity;
        priorityQueue.pop();
        if(current == grid.getFinish()){
            break;
        }

        auto neighbors = grid.neighbors(current);

        for(auto item : neighbors){
            int new_cost = totalCost[current] +1;
            if(!cameFrom.count(item) || new_cost < totalCost[item]){
                totalCost[item] = new_cost;
                priorityQueue.push({item, new_cost});
                cameFrom.insert(pair<Entity, Entity>(item, current));
            }
        }
    }
    cout << "\n";
    printFormStart(grid, cameFrom);
    cout << "\n";
    vector<Entity> way = getWay(grid, cameFrom);
    printWay(grid, way);







    return 0;
}


