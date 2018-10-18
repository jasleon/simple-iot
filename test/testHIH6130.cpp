/** Simple I2C example to read the first address of a device in C++
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<iostream>
#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
#include<iomanip>
#include<unistd.h>
#include <string>
using namespace std;

// Small macro to display value in hexadecimal with 2 places
#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)
#define DEVID       0x00
#define BUFFER_SIZE 4

const char HIH_SLAVE_ADDR = 0x27U;

static string getDiagnostic(unsigned char dataByte[4])
{
    string message;
    switch(dataByte[0] >> 6)
    {
        case 0:
            message.assign("Normal operation");
            break;
        case 1:
            message.assign("Stale data");
            break;
        case 2:
            message.assign("Command mode");
            break;
        case 3:
            message.assign("Diagnostic condition");
            break;
        default:
            message.assign("Invalid operation");
            break;
    }
    return message;
}

static double getTemperature(unsigned char dataByte[4])
{
    unsigned int output_count = (dataByte[2] << 6) | (dataByte[3] >> 2);
    double temperature = (static_cast<double>(output_count) / 16383.0) * 165.0 - 40.0;
    return temperature;
}

static double getHumidity(unsigned char dataByte[4])
{
    unsigned int output_count = ((dataByte[0] & ~0xC0) << 8) | dataByte[1];
    double humidity = (static_cast<double>(output_count) / 16383.0) * 100.0;
    return humidity;
}

int main()
{
    // 1. Configure I2C communication with HIH-6130.
    int file;
    cout << "Starting the HIH-6130 test application" << endl;
    if((file = open("/dev/i2c-2", O_RDWR)) < 0)
    {
        cout << "Failed to open the I2C Bus" << endl;
        return 1;
    }

    if(ioctl(file, I2C_SLAVE, HIH_SLAVE_ADDR) < 0)
    {
        cout << "Failed to connect to the sensor" << endl;
        return 1;
    }
    
    unsigned char writeBuffer[1] = { 0xFF };
    unsigned char readBuffer[BUFFER_SIZE] = { 0x00 };

    for(size_t k = 1U; k < 6; k++)
    {
        cout << "===== Measurement #" << k << " =====" << endl; 
        // 2. Send a measurement request to the sensor.
        if( write(file, writeBuffer, 1) != 1 )
        {
            cout << "Failed to write the Measurement Request (MR) command" << endl;
            return 1;
        }

        sleep(1);

        // 3. Fetch humidity and temperature data from the sensor.
        if( read(file, readBuffer, BUFFER_SIZE) != BUFFER_SIZE)
        {
            cout << "Failed to read in the buffer" << endl;
            return 1;
        }
        
        cout << "Diagnostic:\t"  << getDiagnostic(readBuffer)            << endl;
        cout << "Temperature:\t" << getTemperature(readBuffer) << " °C"  << endl;
        cout << "Humidity:\t"    << getHumidity(readBuffer)    << " %RH" << endl;
    }
    
    close(file);
    
    return 0;
}
