#include "Graph.h"
#include "Airport.h"
#include "Route.h"
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

void Graph::addAirport(const Airport& airport) {
    if (airports.find(airport.getId()) == airports.end()) {
        airports[airport.getId()] = airport;
    }
}

void Graph::addRoute(const Route& route) {
    routes.push_back(route);
    adjacency_list[route.getSourceAirportId()].emplace_back(route.getDestinationAirportId(), route);
}

void Graph::loadAirports(const string& filename) {
    ifstream file(filename); // No need to prepend "data/"
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    int line_count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() < 8) {
            cerr << "Error: Invalid format in line: " << line << endl;
            continue;
        }
        try {
            int id = stoi(fields[0]);
            string name = fields[1];
            string city = fields[2];
            string country = fields[3];
            string iata = fields[4];
            double latitude = stod(fields[6]);
            double longitude = stod(fields[7]);

            Airport airport(id, name, city, country, iata, latitude, longitude);
            addAirport(airport);
            line_count++;
        } catch (const std::invalid_argument& e) {
            cerr << "Error: Invalid data in line: " << line << ". Exception: " << e.what() << endl;
        } catch (const std::out_of_range& e) {
            cerr << "Error: Out of range data in line: " << line << ". Exception: " << e.what() << endl;
        }
    }
    cout << "Loaded " << line_count << " airports." << endl;
}

void Graph::loadRoutes(const string& filename) {
    ifstream file(filename); // No need to prepend "data/"
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }
    string line;
    int line_count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;
        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() < 8) {
            cerr << "Error: Invalid format in line: " << line << endl;
            continue;
        }
        try {
            string airline = fields[0];
            int airline_id = (fields[1] == "\\N" || fields[1].empty()) ? 0 : stoi(fields[1]);
            string source_airport = fields[2];
            int source_airport_id = (fields[3] == "\\N" || fields[3].empty()) ? 0 :stoi(fields[3]);
            string destination_airport = fields[4];
            int destination_airport_id = (fields[5] == "\\N" || fields[5].empty()) ? 0 :stoi(fields[5]);
            int stops = (fields[7] == "\\N" || fields[7].empty()) ? 0 : stoi(fields[7]); // Handle empty stops field

            double time = 1.0;   // Placeholder for time
            double cost = 100.0; // Placeholder for cost

            Route route(airline, airline_id, source_airport, source_airport_id, destination_airport, destination_airport_id, stops, time, cost);
            addRoute(route);
            line_count++;
        } catch (const std::invalid_argument& e) {
            cerr << "Error: Invalid data in line: " << line << ". Exception: " << e.what() << endl;
        } catch (const std::out_of_range& e) {
            cerr << "Error: Out of range data in line: " << line << ". Exception: " << e.what() << endl;
        }
    }
    cout << "Loaded " << line_count << " routes." << endl;
}



vector<int> Graph::dijkstra(int source_id, int destination_id, const string& criteria) {
    unordered_map<int, double> dist;
    unordered_map<int, int> prev;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    for (const auto& airport : airports) {
        dist[airport.first] = numeric_limits<double>::infinity();
        prev[airport.first] = -1;
    }

    dist[source_id] = 0.0;
    pq.push({0.0, source_id});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == destination_id) break;

        for (const auto& neighbor : adjacency_list[u]) {
            int v = neighbor.first;
            const Route& route = neighbor.second;

            double weight;
            if (criteria == "time") {
                weight = route.getTime();  // Using the 'time' field in Route
            } else if (criteria == "cost") {
                weight = route.getCost();  // Using the 'cost' field in Route
            } else {
                weight = route.getStops();  // Default to using stops
            }

            double alt = dist[u] + weight;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }

    vector<int> path;
    for (int at = destination_id; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    if (path.size() == 1 && path[0] != source_id) {
        return {}; // No path found
    }

    return path;
}

const unordered_map<int, Airport>& Graph::getAirports() const {
    return airports;
}

const vector<Route>& Graph::getRoutes() const {
    return routes;
}
