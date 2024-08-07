#include <iostream>
#include <fstream>
#include <unistd.h>
#include "Graph.h"

using namespace std;

int main()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cout << "Current working directory: " << cwd << endl;
    } else {
        perror("getcwd() error");
        return 1;
    }

    Graph graph;

    // Adjust paths to correctly reference the src directory
    cout << "Trying to load ../data/airports.dat" << endl;
cout << "Trying to load ../data/routes.dat" << endl;

    // Load data
    graph.loadAirports("../data/airports.dat");
graph.loadRoutes("../data/routes.dat");

    // Verify data loading
    cout << "Loaded " << graph.getAirports().size() << " airports." << endl;
    cout << "Loaded " << graph.getRoutes().size() << " routes." << endl;

    // Print details of some airports for verification
    int limit = 5; // Define a limit to control the number of printed items
    for (const auto &airport : graph.getAirports())
    {
        cout << "Airport: " << airport.second.getName() << " (" << airport.second.getIata() << ")" << endl;
        if (--limit == 0)
            break; // Print only a few airports for verification
    }

    // Reset the limit for routes
    limit = 5;
    for (const auto &route : graph.getRoutes())
    {
        cout << "Route: " << route.getAirline() << " from " << route.getSourceAirport() << " to " << route.getDestinationAirport() << endl;
        if (--limit == 0)
            break; // Print only a few routes for verification
    }

    // Test Dijkstra's algorithm
    int source_id = 1;        // Example source airport ID
    int destination_id = 2;   // Example destination airport ID
    string criteria = "time"; // Example criteria (time, cost, stops)

    vector<int> path = graph.dijkstra(source_id, destination_id, criteria);

    // Print the path
    cout << "Shortest path from airport " << source_id << " to airport " << destination_id << ":" << endl;
    for (int id : path)
    {
        cout << id << " ";
    }
    cout << endl;

    return 0;
}
