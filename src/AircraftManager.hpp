#pragma once

#include "aircraft.hpp"

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
        for (auto it = aircrafts.begin(); it != aircrafts.end();)
        {
            if ((*it)->move())
            {
                it++;
            }
            else
            {
                it = aircrafts.erase(it);
            }
        }

        return true;
    }

    void add(std::unique_ptr<Aircraft> aircraft) { aircrafts.emplace_back(std::move(aircraft)); }
};