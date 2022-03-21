#include "tower_sim.hpp"

#include "GL/opengl_interface.hpp"
#include "aircraft.hpp"
#include "airport.hpp"
#include "config.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"

#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std::string_literals;

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_aircraft()
{
    assert(airport);
    std::unique_ptr<Aircraft> aircraft = aircraft_factory.create_random_aircraft(airport);
    auto set = aircraft_factory.getUniqueAircrafts();
    if(set.find(aircraft->get_flight_num()) != set.end()){
        std::cout<<"sorry this aircraft are already create !"<<std::endl;
        return;
    }
    aircraft_factory.add_name(aircraft->get_flight_num());
    aircraft_manager.add_aircraft(std::move(aircraft));
}


void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c', [this]() { create_aircraft(); });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });
    GL::keystrokes.emplace('u', []() { GL::up_down_framerate(1); });
    GL::keystrokes.emplace('d', []() { GL::up_down_framerate(-1); });
    GL::keystrokes.emplace('b', []() { GL::break_resume(); });
    GL::keystrokes.emplace('0', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(0))<< std::endl; });
    GL::keystrokes.emplace('1', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(1))<< std::endl; });
    GL::keystrokes.emplace('2', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(2))<< std::endl; });
    GL::keystrokes.emplace('3', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(3))<< std::endl; });
    GL::keystrokes.emplace('4', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(4))<< std::endl; });
    GL::keystrokes.emplace('5', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(5))<< std::endl; });
    GL::keystrokes.emplace('6', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(6))<< std::endl; });
    GL::keystrokes.emplace('7', [this]() { std::cout<< aircraft_manager.recup_airlines(aircraft_factory.get_airlines(7))<< std::endl; });
    GL::keystrokes.emplace('m', [this]() { std::cout<< aircraft_manager.get_aircraft_crashed() << std::endl; });

}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, value] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    assert(!airport && "Our airport is already initialized");
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() },
        aircraft_manager,
    };

    //GL::Displayable::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_manager()
{
    GL::move_queue.emplace(&aircraft_manager);
}

void TowerSimulation::launch()
{
    if (help)
    {
        display_help();
        return;
    }

    init_airport();
    init_manager();
    GL::loop();
}
