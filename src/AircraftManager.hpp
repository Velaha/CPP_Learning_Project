#pragma once

#include "aircraft.hpp"

#include <algorithm>
#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    AircraftManager(/* args */) {};
    ~AircraftManager() {};

    bool move()
    {
        auto aircraftToDelete = std::remove_if(aircrafts.begin(), aircrafts.end(),
                                               [](const auto& item) { return !item->move(); });
        aircrafts.erase(aircraftToDelete, aircrafts.end());

        return true;
    }

    void add(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace_back(std::move(aircraft)); }
};