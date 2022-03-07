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

const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

/*TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) }
{
    MediaPath::initialize(argv[0]);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    GL::init_gl(argc, argv, "Airport Tower Simulation");

    create_keystrokes();
}*/

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

/*void TowerSimulation::create_aircraft(const AircraftType& type) const
{
    assert(airport); // make sure the airport is initialized before creating aircraft

    const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
    const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
    const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
    const Point3D direction = (-start).normalize();

    //Aircraft* aircraft = new Aircraft { type, flight_number, start, direction, airport->get_tower() };
    //GL::Displayable::display_queue.emplace_back(aircraft);
    //GL::move_queue.emplace(aircraft);
    aircraft_manager->add_aircraft(std::make_unique<Aircraft>(type,flight_number, start, direction, airport->get_tower()));
}

void TowerSimulation::create_random_aircraft() const
{
    create_aircraft(*(aircraft_types[rand() % 3]));
}
*/

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
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    //GL::Displayable::display_queue.emplace_back(airport);
    GL::move_queue.emplace(airport);
}

void TowerSimulation::init_manager()
{
    //aircraft_manager = std::make_unique<AircraftManager>();
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
    // init_aircraft_types();
    GL::loop();
}
