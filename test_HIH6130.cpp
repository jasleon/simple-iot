#include "HIH6130.hpp"
#include <iostream>

int main()
{
    HIH6130 mySensor("/dev/i2c-1");
    (void)mySensor.getMeasurement();
    std::cout << mySensor << std::endl;
    return 0;
}
