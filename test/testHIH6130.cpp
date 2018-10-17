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
using namespace std;

// Small macro to display value in hexadecimal with 2 places
#define HEX(x) setw(2) << setfill('0') << hex << (int)(x)
#define DEVID       0x00
#define BUFFER_SIZE 4

const char HIH_SLAVE_ADDR = 0x27U;

int main()
{
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
    
    // 1. Humidity and Temperature Measurement Request
    char writeBuffer[1] = { 0xFF };
    if( write(file, writeBuffer, 1) != 1 )
    {
        cout << "Failed to write the Measurement Request (MR) command" << endl;
        return 1;
    }

    sleep(1);

    // 2. Humidity and Temperature Data Fetch
    char readBuffer[BUFFER_SIZE] = { 0x00 };
    if( read(file, readBuffer, BUFFER_SIZE) != BUFFER_SIZE)
    {
        cout << "Failed to read in the buffer" << endl;
        return 1;
    }
    
    // Diagnostic states.
    char state = readBuffer[0] >> 6;
    switch(state)
    {
        case 0:
            printf("Diagnostic State: Normal operation\n");
            break;
        case 1:
            printf("Diagnostic State: Stale data\n");
            break;
        case 2:
            printf("Diagnostic State: Command mode\n");
            break;
        case 3:
            printf("Diagnostic State: Diagnostic condition\n");
            break;
        default:
            printf("Diagnostic State: Invalid operation\n");
            break;
    }

    close(file);
    
    return 0;
}
