#pragma once


#include "GL/displayable.hpp"
#include "GL/dynamic_object.hpp"
#include "GL/texture.hpp"
#include "airport_type.hpp"
#include "geometry.hpp"
#include "img/image.hpp"
#include "runway.hpp"
#include "terminal.hpp"
#include "tower.hpp"
#include "aircraftManager.hpp"
#include <vector>

class Airport : public GL::Displayable, public GL::DynamicObject
{
private:
    const AirportType& type;
    const Point3D pos;
    const GL::Texture2D texture;
    std::vector<Terminal> terminals;
    Tower tower;
    float fuel_stock        = 0;
    float ordered_fuel      = 0;
    double next_refill_time = 0;
    const AircraftManager& manager;

    // reserve a terminal
    // if a terminal is free, return
    // 1. a sequence of waypoints reaching the terminal from the runway-end and
    // 2. the number of the terminal (used for liberating the terminal later)
    // otherwise, return an empty waypoint-vector and any number
    std::pair<WaypointQueue, size_t> reserve_terminal(Aircraft& aircraft)
    {
        const auto it =
            std::find_if(terminals.begin(), terminals.end(), [](const Terminal& t) { return !t.in_use(); });

        if (it != terminals.end())
        {
            it->assign_craft(aircraft);
            const auto term_idx = std::distance(terminals.begin(), it);
            return { type.air_to_terminal(pos, 0, term_idx), term_idx };
        }
        else
        {
            return { {}, 0u };
        }
    }

    WaypointQueue start_path(const size_t terminal_number)
    {
        assert(terminal_number < terminals.size() && "Out of terminals length");
        return type.terminal_to_air(pos, 0, terminal_number);
    }

    Terminal& get_terminal(const size_t terminal_num) { return terminals.at(terminal_num); }

public:
    Airport(const AirportType& type_, const Point3D& pos_, const img::Image* image, const AircraftManager& aircraftManager, const float z_ = 1.0f) :
        GL::Displayable { z_ },
        type { type_ },
        pos { pos_ },
        texture { image },
        terminals { type.create_terminals() },
        tower { *this },
        manager { aircraftManager }
    {}

    Tower& get_tower() { return tower; }

    void display() const override { texture.draw(project_2D(pos), { 2.0f, 2.0f }); }

    void move() override
    {
        if(next_refill_time <= 0.){
            fuel_stock += ordered_fuel;
            const auto required = manager.get_required_fuel();
            if(fuel_stock >= required + 1000.f){
                ordered_fuel = 0.f;
            }
            else{
                ordered_fuel = std::min(required + 1000.f, 5000.f);
                std::cout << "fuel stock : " << fuel_stock << " ordered fuel : " << ordered_fuel << std::endl;
            }
            next_refill_time = 100.f;
        }
        for (auto& t : terminals)
        {
            t.move(fuel_stock);
        }
        next_refill_time --;
    }

    friend class Tower;
};
