//
// Created by Brayan Marié on 21/02/2022.
//
#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "aircraft.hpp"

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    unsigned int aircraft_crashed = 0;
public:
    void move() override;
    void add_aircraft(std::unique_ptr<Aircraft> aircraft);
    int recup_airlines(const std::string_view& model);
    float get_required_fuel() const;
    unsigned int get_aircraft_crashed() const{
        return aircraft_crashed;
    }
};

