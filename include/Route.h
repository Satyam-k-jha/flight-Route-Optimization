#ifndef ROUTE_H
#define ROUTE_H

#include <string>

class Route {
public:
    // Constructor
    Route(const std::string& airline, int airline_id, const std::string& source_airport, int source_airport_id,
          const std::string& destination_airport, int destination_airport_id, int stops, double time, double cost);

    // Getters
    std::string getAirline() const;
    int getAirlineId() const;
    std::string getSourceAirport() const;
    int getSourceAirportId() const;
    std::string getDestinationAirport() const;
    int getDestinationAirportId() const;
    int getStops() const;
    double getTime() const;
    double getCost() const;

private:
    std::string airline;
    int airline_id;
    std::string source_airport;
    int source_airport_id;
    std::string destination_airport;
    int destination_airport_id;
    int stops;
    double time;
    double cost;
};

#endif // ROUTE_H