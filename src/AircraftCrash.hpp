#pragma once

#include "geometry.hpp"

#include <stdexcept>

class AircraftCrash : public std::runtime_error
{
private:
    std::string build_error_message(std::string flight_number, Point3D position, Point3D speed,
                                    std::string msg)
    {
        std::string err_msg;

        err_msg += flight_number;
        err_msg += " " + msg + " at position (";
        err_msg += std::to_string(position.x());
        err_msg += ", ";
        err_msg += std::to_string(position.y());
        err_msg += ", ";
        err_msg += std::to_string(position.z());
        err_msg += ") with speed (";
        err_msg += std::to_string(speed.x());
        err_msg += ", ";
        err_msg += std::to_string(speed.y());
        err_msg += ", ";
        err_msg += std::to_string(speed.z());
        err_msg += ")";

        return err_msg;
    }

public:
    AircraftCrash(std::string flight_number, Point3D position, Point3D speed, std::string msg) :
        std::runtime_error { build_error_message(flight_number, position, speed, msg) } {};
};
