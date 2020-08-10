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

bool Sensor::read()
{
    return false;
}

std::ostream Sensor::display(std::ostream& output) const
{
    output << "helloWorld";
}

#endif /* SENSOR_CPP */
