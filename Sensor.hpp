#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <iostream>

class Sensor
{
    public:
        Sensor();
        ~Sensor();
        virtual bool read() = 0;
};

#endif /* SENSOR_HPP */
