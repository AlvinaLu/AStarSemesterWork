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
#include <thread>
#include <future>

void cost(Entity entity, Entity entity1);

using namespace std;

auto read(string str) {
    ifstream inf(str);
    int width, height, countBarrier, countPoints, x, y;

    inf >> width;
    inf >> height;
    inf >> countPoints;
    inf >> countBarrier;
    Grid grid(width, height);


    if (countPoints < 2) {
        std::cerr << "Oops, you entered just one point!" << std::endl;
        exit(1);
    }

    //Start
    vector<Entity> points;
    while (countPoints > 0) {
        inf >> x;
        inf >> y;
        if (x < width && y < height) {
            Entity point = {x, y};
            points.push_back(point);
            countPoints--;
        } else {
            std::cerr << "Oops, you entered point {" << x << ", " << y << "} out of range!" << std::endl;
            exit(1);
        }

    }
    grid.setMPoints(points);

    //Barriers
    vector<Entity> walls;
    while (countBarrier > 0) {
        inf >> x;
        inf >> y;
        if (x < width && y < height) {
            walls.push_back({x, y});
            countBarrier--;
        } else {
            std::cerr << "Oops, you entered point {" << x << ", " << y << "} out of range!" << std::endl;
            exit(1);
        }

    }
    grid.setWalls(walls);
    return grid;

}

template<typename T>
bool Contains(std::vector<T> &Vec, T &element) {
    if (std::find(Vec.begin(), Vec.end(), element) != Vec.end())
        return true;

    return false;
}

int getIndex(vector<Entity> way, Entity entity) {
    auto it = find(way.begin(), way.end(), entity);

    if (it != way.end()) {
        int index = it - way.begin();
        return index;
    } else {
        return -1;
    }
}

void print(Grid grid) {// Starting print
    for (int i = 0; i < grid.getMWight(); i++) {
        for (int j = 0; j < grid.getMHeight(); j++) {
            Entity entity = {i, j};
            if (grid.isNotWall(entity)) {
                if (std::find(grid.getMPoints().begin(), grid.getMPoints().end(), entity) != grid.getMPoints().end()) {
                    int index = getIndex(grid.getMPoints(), entity);
                    cout << " ";
                    printf("%.02i", index);
                    cout << " ";
                } else { cout << " " << "\u00b7" << "  "; }
            } else {
                cout << " " << "#" << "  ";
            }

        }
        cout << endl;

    }
    cout << endl;
}


void sophisticatedPrintWay(Grid grid, vector<Entity> way, Entity start, Entity finish) {
    cout << "\n";
    for (int i = 0; i < grid.getMWight(); i++) {
        for (int j = 0; j < grid.getMHeight(); j++) {
            Entity entity = {i, j};
            int index = getIndex(way, entity);
            if (grid.isNotWall(entity)) {
                if (Contains(way, entity)) {
                    if (start == entity) {
                        cout << "S" << " ";
                    } else if (finish == entity) {
                        cout << "F" << " ";
                    } else if (index != -1) {
                        Entity from = entity;
                        if (index + 1 < way.size()) {
                            Entity to = way.at(index + 1);
                            if (from.m_x == to.m_x && (from.m_y - to.m_y) == -1) {
                                cout << "\u2190" << " ";
                            } else if (from.m_x == to.m_x && (from.m_y - to.m_y) == 1) {
                                cout << "\u2192" << " ";
                            } else if ((from.m_x - to.m_x) == 1 && from.m_y == to.m_y) {
                                cout << "\u2193" << " ";
                            } else if ((from.m_x - to.m_x) == -1 && from.m_y == to.m_y) {
                                cout << "\u2191" << " ";
                            }
                        }
                    } else {
                        cout << "\u00b7" << " ";
                    }
                } else {
                    cout << "\u00b7" << " ";
                }
            } else {
                cout << "#" << " ";
            }

        }
        cout << endl;
    }
}


double heuristic(Entity one, Entity two) {
    return abs(one.m_x - two.m_x) + abs(one.m_y - two.m_y);
}

vector<Entity> getWay(Grid grid, map<Entity, Entity> cameFrom, Entity start, Entity finish) {
    vector<Entity> way;
    Entity current = finish;
    way.push_back(current);
    while (!(current == start)) {
        current = cameFrom.at(current);
        way.push_back(current);
    }
    way.push_back(start);

    return way;

}

std::map<Entity, Entity> findWay(Grid grid, Entity start, Entity finish) {
    std::priority_queue<Priority, std::vector<Priority>, std::greater<Priority>> priorityQueue;
    priorityQueue.push({start, 0.0});

    std::map<Entity, Entity> cameFrom;
    cameFrom.insert(std::make_pair(start, start));
    std::map<Entity, int> totalCost;

    while (!priorityQueue.empty()) {
        auto current = priorityQueue.top().entity;
        priorityQueue.pop();

        if (current == finish) {
            break;
        }

        auto neighbors = grid.neighbors(current);

        for (auto item : neighbors) {
            double new_cost = totalCost[current] + 1;
            if (!cameFrom.count(item) || new_cost < totalCost[item]) {
                totalCost[item] = new_cost;
                new_cost += heuristic(item, finish);
                priorityQueue.push({item, new_cost});
                cameFrom.insert(pair<Entity, Entity>(item, current));
            }
        }
    }
    return cameFrom;

}

vector<Entity> compute(Grid grid, int i) {
    Entity start = grid.getMPoints().at(i);
    Entity finish = grid.getMPoints().at(i + 1);
    std::map<Entity, Entity> cameFrom = findWay(grid, start, finish);
    vector<Entity> way = getWay(grid, cameFrom, start, finish);
    return way;
}

void oneThread(Grid grid) {


    for (int i = 0; i < (grid.getMPoints().size() - 1); i++) {
        Entity start = grid.getMPoints().at(i);
        Entity finish = grid.getMPoints().at(i + 1);
        cout << "Way from: {" << start.m_x << ", " << start.m_y << "} " << "to: {" << finish.m_x << ", " << finish.m_y
             << "} " << endl;

        sophisticatedPrintWay(grid, compute(grid, i), start, finish);
    }
}

void multiThread(Grid grid) {
    vector<std::future<vector<Entity>>> result;
    for (int i = 0; i < (grid.getMPoints().size() - 1); i++) {
        result.push_back(async(compute, grid, i));
    }
    for (int i = 0; i < (grid.getMPoints().size() - 1); i++) {
        result.at(i).wait();
    }

    for (int i = 0; i < (grid.getMPoints().size() - 1); i++) {
        Entity start = grid.getMPoints().at(i);
        Entity finish = grid.getMPoints().at(i + 1);
        cout << "Way from: {" << start.m_x << ", " << start.m_y << "} " << "to: {" << finish.m_x << ", " << finish.m_y
             << "} " << endl;


        sophisticatedPrintWay(grid, result.at(i).get(), start, finish);
    }
}

template<typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

int main(int argc, char *argv[]) {
    vector<std::string> allowedArguments = { "--one_thread", "--multi_thread",  "--help"};
    vector<std::string> arguments(argv + 1, argv + argc);
    string isOneThread = "--one_thread";
    string isMultiThread = "--multi_thread";
    string isHelp = "--help";
    long processingTimeOneThread;
    long processingTimeMultiThread;


    for(auto arg : arguments){
        if(!Contains(allowedArguments, arg) && arg!=arguments.at(0)){
            std::cerr << "Oops, argument not allowed!" << std::endl;
            exit(1);
        }
    }
    if (Contains(arguments, isHelp) || arguments.size()==0) {
        cout << "Usage semestalni_prace_pjc:\n semestalni_prace_pjc <map file> [--one_thread] [--multi_thread] [--help] \n --one_thread: For single thread mode \n --multi_thread: For multiple thread mode \n --help: For help" << endl;
        exit(0);
    }

    if (arguments.size() >= 1) {

        auto grid = read(arguments.at(0));

        if (Contains(arguments, isOneThread)) {
            auto start = std::chrono::high_resolution_clock::now();
            cout << "Running in one thread" << endl;
            print(grid);
            oneThread(grid);
            auto end = std::chrono::high_resolution_clock::now();
            processingTimeOneThread = to_ms(end - start).count();
            cout << "Needed " << processingTimeOneThread << " ms to finish.\n";
        }
        if (Contains(arguments, isMultiThread)) {
            auto start = std::chrono::high_resolution_clock::now();
            cout << "Running in multiple thread" << endl;
            print(grid);
            multiThread(grid);
            auto end = std::chrono::high_resolution_clock::now();
            processingTimeMultiThread = to_ms(end - start).count();
            cout << "Needed " << processingTimeMultiThread << " ms to finish.\n";
        }
        if (Contains(arguments, isMultiThread) && Contains(arguments, isOneThread)) {
            cout << "\n";
            cout << "One thread needs " << processingTimeOneThread << " ms to finish.\n";
            cout << "Multiple threads need " << processingTimeMultiThread << " ms to finish.\n";
        }
    }
    return 0;
}


