//
// Created by Brayan Marié on 21/02/2022.
//

#include "aircraftManager.hpp"

void AircraftManager::move()
{
    for (auto it = aircrafts.begin(); it != aircrafts.end();)
    {
        auto &aircraft = **it;
        aircraft.move();
        if (!aircraft.should_destroy())
            ++it;
        else
        {
            it = aircrafts.erase(it);
        }
    }
}


void AircraftManager::create_aircraft(const AircraftType& type,Airport* airport)
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    std::unique_ptr<Aircraft> aircraft = std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
    aircrafts.push_back(std::move(aircraft));
}

void AircraftManager::create_random_aircraft(Airport* airport)
{
    create_aircraft(*(aircraft_types[rand() % 3]),airport);
}
