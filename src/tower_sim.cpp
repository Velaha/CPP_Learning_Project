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
#include <memory>
#include <utility>

using namespace std::string_literals;

TowerSimulation::TowerSimulation(int argc, char** argv) :
    help { (argc > 1) && (std::string { argv[1] } == "--help"s || std::string { argv[1] } == "-h"s) },
    context_initializer(argc, argv)
{
    create_keystrokes();
}

TowerSimulation::~TowerSimulation()
{
    delete airport;
}

void TowerSimulation::create_keystrokes()
{
    GL::keystrokes.emplace('x', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('q', []() { GL::exit_loop(); });
    GL::keystrokes.emplace('c',
                           [this]()
                           {
                               auto newAircraft = aircraft_factory.create_random_aircraft(airport);
                               aircraft_manager.add(std::move(newAircraft));
                           });
    GL::keystrokes.emplace('+', []() { GL::change_zoom(0.95f); });
    GL::keystrokes.emplace('-', []() { GL::change_zoom(1.05f); });
    GL::keystrokes.emplace('f', []() { GL::toggle_fullscreen(); });

    GL::keystrokes.emplace('a', []() { GL::change_framerate(1); });
    GL::keystrokes.emplace('s', []() { GL::change_framerate(-1); });
    GL::keystrokes.emplace('p', []() { GL::toggle_pause(); });

    GL::keystrokes.emplace('0', [this]() { std::cout << aircraft_factory.print_airlines(0) << std::endl; });
    GL::keystrokes.emplace('1', [this]() { std::cout << aircraft_factory.print_airlines(1) << std::endl; });
    GL::keystrokes.emplace('2', [this]() { std::cout << aircraft_factory.print_airlines(2) << std::endl; });
    GL::keystrokes.emplace('3', [this]() { std::cout << aircraft_factory.print_airlines(3) << std::endl; });
    GL::keystrokes.emplace('4', [this]() { std::cout << aircraft_factory.print_airlines(4) << std::endl; });
    GL::keystrokes.emplace('5', [this]() { std::cout << aircraft_factory.print_airlines(5) << std::endl; });
    GL::keystrokes.emplace('6', [this]() { std::cout << aircraft_factory.print_airlines(6) << std::endl; });
    GL::keystrokes.emplace('7', [this]() { std::cout << aircraft_factory.print_airlines(7) << std::endl; });
}

void TowerSimulation::display_help() const
{
    std::cout << "This is an airport tower simulator" << std::endl
              << "the following keysstrokes have meaning:" << std::endl;

    for (const auto& [key, function] : GL::keystrokes)
    {
        std::cout << key << ' ';
    }

    std::cout << std::endl;
}

void TowerSimulation::init_airport()
{
    airport = new Airport { one_lane_airport, Point3D { 0, 0, 0 },
                            new img::Image { one_lane_airport_sprite_path.get_full_path() } };

    GL::move_queue.emplace(airport);
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

    GL::loop();
}
