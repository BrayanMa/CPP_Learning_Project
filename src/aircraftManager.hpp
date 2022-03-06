//
// Created by Brayan Marié on 21/02/2022.
//

#ifndef TOWER_SIM_AIRCRAFTMANAGER_HPP
#define TOWER_SIM_AIRCRAFTMANAGER_HPP

#include <vector>
#include <memory>
#include "aircraft.hpp"
#include "airport.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
};

#endif // TOWER_SIM_AIRCRAFTMANAGER_HPP
