#ifndef SENSOR_CPP
#define SENSOR_CPP

#include "Sensor.hpp"
#include <iostream>

Sensor::Sensor()
{
    std::cout << "Parent class constructor" << std::endl;
}

Sensor::~Sensor()
{
    std::cout << "Parent class destructor " << std::endl;
}

#endif /* SENSOR_CPP */
