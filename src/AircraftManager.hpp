#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    AircraftManager(/* args */);
    ~AircraftManager();
};

AircraftManager::AircraftManager(/* args */)
{}

AircraftManager::~AircraftManager()
{}
