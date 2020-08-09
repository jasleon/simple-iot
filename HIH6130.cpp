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

HIH6130::HIH6130(string device, unsigned int address) : 
    fd(-1), 
    is_open(false),
    is_connected(false),
    writeBuffer{0xFF}, 
    readBuffer{0x00},
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

        cout << "File descriptor closed" << endl;
    }
}

bool HIH6130::getMeasurement()
{
    bool retval = WR_BUFFER_SIZE == write(fd, writeBuffer, WR_BUFFER_SIZE);
    if(retval)
    {
        sleep(1);
        retval = RD_BUFFER_SIZE == read(fd, readBuffer, RD_BUFFER_SIZE);
    }
    else
    {
        cout << "Failed to write the Measurement Request (MR) command" << endl;
    }
    
    if(retval)
    {
        cout << "Update private variables" << endl;
        setTemperature();
        setHumidity();
    }
    else
    {
        cout << "Failed to read in the buffer" << endl;
    }
    return retval;
}

void HIH6130::setTemperature()
{
    unsigned int output_count = (readBuffer[2] << 6) | (readBuffer[3] >> 2);
    temperature = (static_cast<double>(output_count) / 16383.0) * 165.0 - 40.0;
}

void HIH6130::setHumidity()
{
    unsigned int output_count = ((readBuffer[0] & ~0xC0) << 8) | readBuffer[1];
    humidity = (static_cast<double>(output_count) / 16383.0) * 100.0;
}

double HIH6130::getTemperature() const
{
    return temperature;
}

double HIH6130::getHumidity() const
{
    return humidity;
}

ostream& operator<<(ostream& output, HIH6130 const& self)
{
  output << "Temperature:\t" << self.getTemperature() << " °C\n";
  output << "Humidity:\t"    << self.getHumidity()    << " %RH";
  return output;
}

#endif /* HIH6130_CPP */
