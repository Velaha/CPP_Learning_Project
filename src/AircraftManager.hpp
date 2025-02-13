#pragma once

#include "aircraft.hpp"

#include <algorithm>
#include <cassert>
#include <memory>
#include <numeric>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;
    int nbCrash = 0;

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
                                               [this](const auto& item)
                                               {
                                                   try
                                                   {
                                                       return !item->move();
                                                   } catch (const AircraftCrash& e)
                                                   {
                                                       std::cerr << "[!]" << e.what() << "[!]\n";
                                                       nbCrash++;
                                                       return true;
                                                   }
                                               });
        aircrafts.erase(aircraftToDelete, aircrafts.end());

        return true;
    }

    void add(std::unique_ptr<Aircraft> aircraft)
    {
        assert(aircraft);
        aircrafts.emplace_back(std::move(aircraft));
    }

    int get_required_fuel() const
    {
        int required = std::accumulate(aircrafts.begin(), aircrafts.end(), 0,
                                       [](int acc, const auto& cur_aircraft)
                                       {
                                           if (!cur_aircraft->is_low_on_fuel() || cur_aircraft->has_served())
                                           {
                                               return acc;
                                           }
                                           return acc + (3000 - cur_aircraft->current_fuel());
                                       });
        return required;
    }

    void get_crash() { std::cout << "Crashes since the beginning : " << nbCrash << std::endl; }
};