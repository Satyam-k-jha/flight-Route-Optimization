#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
#include <string>
#include "Airport.h"
#include "Route.h"
using namespace std;

class Graph {
public:
    unordered_map<int, Airport> airports;
    vector<Route> routes;
    unordered_map<int, vector<pair<int, Route>>> adjacency_list;

    void addAirport(const Airport& airport);
    void addRoute(const Route& route);
    void loadAirports(const string& filename);
    void loadRoutes(const string& filename);

    vector<int> dijkstra(int source_id, int destination_id, const string& criteria);

    // Getter methods
    const unordered_map<int, Airport>& getAirports() const;
    const vector<Route>& getRoutes() const;
};

#endif // GRAPH_H