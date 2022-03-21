//
// Created by Brayan Marié on 21/02/2022.
//

#include "aircraftManager.hpp"

void AircraftManager::move()
{
    std::sort(aircrafts.begin(), aircrafts.end(),
              [](const std::unique_ptr<Aircraft>& it1, const std::unique_ptr<Aircraft>& it2)
              {
                  if (it2->has_terminal())
                      return false;

                  if (it1->has_terminal())
                      return true;

                  return (it1->get_fuel() < it2->get_fuel());
              });

    std::function<bool(std::unique_ptr<Aircraft>&)> predicat = [this](const std::unique_ptr<Aircraft>& aircraft){
        try {
            aircraft->update();
        } catch (const AircraftCrash& err) {
            this->aircraft_crashed++;
            std::cerr << err.what() << std::endl;
        }
        return aircraft->should_destroy();
    };

    auto tmp = std::remove_if(aircrafts.begin(), aircrafts.end(), predicat);
    aircrafts.erase(tmp, aircrafts.end());
}

void AircraftManager::add_aircraft(std::unique_ptr<Aircraft> aircraft)
{
    assert(aircraft && "Aircraft cannot be empty");
    aircrafts.push_back(std::move(aircraft));
}

int AircraftManager::recup_airlines(const std::string_view& model)
{
    return std::count_if(aircrafts.begin(), aircrafts.end(),
                         [model](const std::unique_ptr<Aircraft>& aircraft_it)
                         { return model == aircraft_it->get_flight_num().substr(0, 2); });
}

float AircraftManager::get_required_fuel() const
{
    return std::accumulate(aircrafts.begin(), aircrafts.end(), 0.f,
                           [](float acc, const std::unique_ptr<Aircraft>& aircraft_it)
                           {
                               if (aircraft_it->is_on_ground() && aircraft_it->is_low_on_fuel())
                               {
                                   return acc + aircraft_it->fuel_to_be_full();
                               }
                               return acc;
                           });
}
