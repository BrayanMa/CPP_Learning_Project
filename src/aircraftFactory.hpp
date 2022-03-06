//
// Created by Brayan Marié on 28/02/2022.
//

#ifndef TOWER_SIM_AIRCRAFTFACTORY_HPP
#define TOWER_SIM_AIRCRAFTFACTORY_HPP

#include "aircraftManager.hpp"



class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};
    void init_aircraft_types();
    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type,Airport* airport);
    std::set<std::string> uniqueAircrafts;

public:
    AircraftFactory(){
        init_aircraft_types();
    }
    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport);
    void add_name(const std::string& basicString);
    std::set<std::string> getUniqueAircrafts() {return uniqueAircrafts;}
};

#endif // TOWER_SIM_AIRCRAFTFACTORY_HPP
