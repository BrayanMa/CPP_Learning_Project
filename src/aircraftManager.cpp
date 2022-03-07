//
// Created by Brayan Marié on 21/02/2022.
//

#include "aircraftManager.hpp"

void AircraftManager::move()
{
    std::function<bool(std::unique_ptr<Aircraft>&)> predicat = []( std::unique_ptr<Aircraft>& aircraft){
        aircraft->update();
        return aircraft->should_destroy();
    };

    auto tmp = std::remove_if(aircrafts.begin(), aircrafts.end(), predicat);
    aircrafts.erase(tmp, aircrafts.end());
    /*for (auto it = aircrafts.begin(); it != aircrafts.end();)
    {
        auto &aircraft = **it;
        aircraft.move();

        if (!aircraft.should_destroy())
            ++it;
        else
        {
            it = aircrafts.erase(it);
        }
    }*/
}

void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.push_back(std::move(aircraft));
}

int AircraftManager::recup_airlines(const std::string_view& model)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [model](const std::unique_ptr<Aircraft>& aircraft_it)
                         { return model == aircraft_it->get_flight_num().substr(0, 2); });
}
    /*int count = 0;
    std::all_of(airlines->begin(), airlines->end(), )
    for(auto &aircraft : aircrafts){
        auto airline = aircraft->get_flight_num().substr(0, 2);
        if(airline == airlines[value])
            count++;
    }
    std::cout << "Airlines " << airlines[value] << " = " << count << std::endl;
}*/
