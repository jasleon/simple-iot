#ifndef HIH6130_CPP
#define HIH6130_CPP

#include "HIH6130.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

HIH6130::HIH6130(const string device) : fd(-1), is_open(false), temperature(0.0f), humidity(0.0f)
{
    fd = open(device.c_str(), O_RDWR);
    is_open = fd < 0;
    
    if(is_open)
    {
        cout << "Failed to open the I2C Bus" << endl;
    }
}

HIH6130::~HIH6130()
{
    if(is_open)
    {
        close(fd);
    }
}

double HIH6130::getTemperature() const
{
    return temperature;
}

double HIH6130::getHumity() const
{
    return humidity;
}

#endif /* HIH6130_CPP */
