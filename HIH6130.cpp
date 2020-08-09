#ifndef HIH6130_CPP
#define HIH6130_CPP

#include "HIH6130.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

HIH6130::HIH6130(std::string device, unsigned int address) : 
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
        std::cout << "File descriptor: " << fd << std::endl;
        is_connected = ioctl(fd, I2C_SLAVE, address) >= 0;
        
        if(is_connected)
        {
            std::cout << "Sensor connected" << std::endl;
        }
        else
        {
            std::cout << "Failed to connect to the sensor" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to open the I2C Bus" << std::endl;
    }
}

HIH6130::~HIH6130()
{
    if(is_open)
    {
        close(fd);

        std::cout << "File descriptor closed" << std::endl;
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
        std::cout << "Failed to write the Measurement Request (MR) command" << std::endl;
    }
    
    if(retval)
    {
        std::cout << "Update private variables" << std::endl;
        setTemperature();
        setHumidity();
    }
    else
    {
        std::cout << "Failed to read in the buffer" << std::endl;
    }
    return retval;
}

void HIH6130::setTemperature()
{
    unsigned int output_count = (readBuffer[2] << 6) | (readBuffer[3] >> 2);
    temperature = (static_cast<double>(output_count) / 16383.0f) * 165.0f - 40.0f;
}

void HIH6130::setHumidity()
{
    unsigned int output_count = ((readBuffer[0] & ~0xC0) << 8) | readBuffer[1];
    humidity = (static_cast<double>(output_count) / 16383.0f) * 100.0f;
}

double HIH6130::getTemperature() const
{
    return temperature;
}

double HIH6130::getHumidity() const
{
    return humidity;
}

std::ostream& operator<<(std::ostream& output, HIH6130 const& self)
{
  output << "Temperature:\t" << self.getTemperature() << " °C\n";
  output << "Humidity:\t"    << self.getHumidity()    << " %RH";
  return output;
}

#endif /* HIH6130_CPP */
