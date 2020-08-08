#include "HIH6130.hpp"

int main()
{
    HIH6130 mySensor("/dev/i2c-1");
    (void)mySensor.getMeasurement();
    return 0;
}
