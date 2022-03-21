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
        std::sort(aircrafts.begin(), aircrafts.end(),
                  [](const std::unique_ptr<Aircraft>& a, const std::unique_ptr<Aircraft>& b)
                  {
                      if (a->has_terminal())
                      {
                          return true;
                      }
                      if (b->has_terminal())
                      {
                          return false;
                      }
                      return a->current_fuel() < b->current_fuel();
                  });

        auto aircraftToDelete = std::remove_if(aircrafts.begin(), aircrafts.end(),
                                               [](const auto& item) { return !item->move(); });
        aircrafts.erase(aircraftToDelete, aircrafts.end());

        return true;
    }

    void add(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace_back(std::move(aircraft)); }
};