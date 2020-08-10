#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <iostream>

class Sensor
{
    public:
        Sensor();
        ~Sensor();
        bool read();
        std::ostream display(std::ostream& output) const;
};

#endif /* SENSOR_HPP */
