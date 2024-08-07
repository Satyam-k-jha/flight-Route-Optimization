#include "Route.h"

// Constructor implementation
Route::Route(const std::string& airline, int airline_id, const std::string& source_airport, int source_airport_id,
             const std::string& destination_airport, int destination_airport_id, int stops, double time, double cost)
    : airline(airline), airline_id(airline_id), source_airport(source_airport), source_airport_id(source_airport_id),
      destination_airport(destination_airport), destination_airport_id(destination_airport_id), stops(stops),
      time(time), cost(cost) {}

// Getter for airline
std::string Route::getAirline() const { return airline; }

// Getter for airline_id
int Route::getAirlineId() const { return airline_id; }

// Getter for source_airport
std::string Route::getSourceAirport() const { return source_airport; }

// Getter for source_airport_id
int Route::getSourceAirportId() const { return source_airport_id; }

// Getter for destination_airport
std::string Route::getDestinationAirport() const { return destination_airport; }

// Getter for destination_airport_id
int Route::getDestinationAirportId() const { return destination_airport_id; }

// Getter for stops
int Route::getStops() const { return stops; }

// Getter for time
double Route::getTime() const { return time; }

// Getter for cost
double Route::getCost() const { return cost; }
