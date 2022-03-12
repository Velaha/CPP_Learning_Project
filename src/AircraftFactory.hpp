#pragma once

#include "aircraft.hpp"
#include "aircraft_types.hpp"
#include "airport.hpp"

class AircraftFactory
{
private:
    const std::string airlines[8] = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" };

    const static size_t NUM_AIRCRAFT_TYPES = 3;
    AircraftType* aircraft_types[NUM_AIRCRAFT_TYPES] {};

    void init_aircraft_types()
    {
        aircraft_types[0] = new AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } };
        aircraft_types[1] = new AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } };
        aircraft_types[2] = new AircraftType { .02f, .08f, .02f, MediaPath { "concorde_af.png" } };
    }

    std::unique_ptr<Aircraft> create_aircraft(Airport* airport, const AircraftType& type)
    {
        const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
        const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
        const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
        const Point3D direction = (-start).normalize();

        return std::make_unique<Aircraft>(type, flight_number, start, direction, airport->get_tower());
    }

public:
    AircraftFactory(/* args */) { init_aircraft_types(); };
    /* init AircraftFactory with :
     * aircraft_types
     * */
    ~AircraftFactory() {};

    std::unique_ptr<Aircraft> create_random_aircraft(Airport* airport)
    {
        return create_aircraft(airport, *(aircraft_types[rand() % 3]));
    }
};