#include "Sensor.hpp"
#include "HIH6130.hpp"
#include <iostream>

int main()
{
  HIH6130 mySensor("/dev/i2c-1");
  for(unsigned int k = 0; k < 10; k++)
  {
    (void)mySensor.getMeasurement();
    std::cout << mySensor << std::endl;
  }
  return 0;
}
