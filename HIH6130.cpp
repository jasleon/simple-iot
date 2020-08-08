#ifndef HIH6130_CPP
#define HIH6130_CPP

#include "HIH6130.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

using namespace std;

HIH6130::HIH6130(string device, unsigned int address = 0x27U) : 
    fd(-1), 
    is_open(false),
    is_connected(false), 
    temperature(0.0f), 
    humidity(0.0f)
{
    fd = open(device.c_str(), O_RDWR);
    is_open = fd >= 0;
    
    if(is_open)
    {
        cout << "File descriptor: " << fd << endl;
        is_connected = ioctl(fd, I2C_SLAVE, address) >= 0;
        
        if(is_connected)
        {
            cout << "Sensor connected" << endl;
        }
        else
        {
            cout << "Failed to connect to the sensor" << endl;
        }
    }
    else
    {
        cout << "Failed to open the I2C Bus" << endl;
    }
}

HIH6130::~HIH6130()
{
    if(is_open)
    {
        close(fd);

        cout << "Closed the file descriptor" << endl;
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
